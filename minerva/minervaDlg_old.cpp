  
// minervaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "minerva.h"
#include "minervaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_CORE 1000
#define TIMER_THERMOSTAT 60000   // Stefano changed 10000 to 60000 for smoothing 
#define RESISTANCE_THERMOSTAT 40000
#define DERIVATIVE_POWER 10000 // microwatt


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP() 
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CminervaDlg dialog



CminervaDlg::CminervaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CminervaDlg::IDD, pParent)
	, m_adr_k2400(0)
	, m_string(NULL)
	, m_adr_k6220_core(0)
	, m_adr_k2182_core(0)
	, m_adr_k2182_multi(0)
	, m_adr_k6220_multi(0)
	, m_micro_ampere_core(0)
	, m_secondi_core(0)
	, m_directory(_T(""))
	, m_number_of_cycles(0)
	, m_pause_cycle(0)
	, m_flag_cycle_power_core(0)
	, m_done_cycles(0)
	, m_aux_text(_T(""))
	, m_pause_start(0)
	, m_set_point(0)
	, m_p_pid(0)
	, m_d_PID(0)
	, m_core_current(0)
	, m_core_probe_curr(0)
	
	, m_flag_measure_core(0)
	, m_elements_into_mean_core(0)
	, m_anti_block_core(0)
	, m_jacket_probe_current(0)
	, m_skip_points_thermostat(0)
	, m_mean_thermostat(0)
	, m_anti_block_general(0)
	, m_multi_probe_current(0)
	 
	, m_anti_block_multi(0)
	, m_old_thermo_temperature(0)
	, m_p_CDC(NULL)
	, m_derivative_power(0)
	, m_I_PID(0)
	, m_do_noting(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CminervaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_message_box_C);
	DDX_Control(pDX, IDC_STATIC_ERR, m_ERR_C);
	DDX_Control(pDX, IDC_STATIC_ERR2, m_TIMO);
	DDX_Control(pDX, IDC_STATIC_ERR3, m_END_C);
	DDX_Control(pDX, IDC_STATIC_ERR4, m_CMPL_C);
	//DDX_Control(pDX, IDC_STATIC_test, m_test_C);
	DDX_Text(pDX, IDC_EDIT1, m_micro_ampere_core);
	DDV_MinMaxInt(pDX, m_micro_ampere_core, 0, 10000);
	DDX_Text(pDX, IDC_EDIT2, m_secondi_core);
	DDV_MinMaxInt(pDX, m_secondi_core, 0, 100000);
	DDX_Control(pDX, IDC_EDIT3, m_microwatt_core_C);
	DDX_Control(pDX, IDC_EDIT4, m_joule_core_C);
	DDX_Control(pDX, IDC_EDIT5, m_seconds_core_C);
	DDX_Control(pDX, IDC_EDIT6, m_volt_core_C);
	DDX_Text(pDX, IDC_EDIT7, m_number_of_cycles);
	DDV_MinMaxInt(pDX, m_number_of_cycles, 0, 1000);
	DDX_Text(pDX, IDC_EDIT8, m_pause_cycle);
	DDV_MinMaxLong(pDX, m_pause_cycle, 0, 10000);
	DDX_Control(pDX, IDC_BUTTON_RUN_CYCLE, m_button_start_cycles_C);
	DDX_Control(pDX, IDC_BUTTON_STOP_CYCLE, m_button_stop_cycle_C);
	DDX_Control(pDX, IDC_EDIT_CYCLES, m_done_C);
	DDX_Control(pDX, IDC_EDIT_PAUSE, m_pause_C);
	DDX_Text(pDX, IDC_EDIT_SET_POINT, m_set_point);
	DDX_Text(pDX, IDC_EDIT10, m_p_pid);
	DDX_Text(pDX, IDC_EDIT11, m_d_PID);
	DDX_Control(pDX, IDC_EDIT_SET_POINT2, m_shield_ohm_C);
	DDX_Control(pDX, IDC_EDIT12, m_delta_k_C);
	DDX_Control(pDX, IDC_EDIT13, m_microW_shield_C);
	DDX_Control(pDX, IDC_EDIT_SET_POINT3, m_speed_shield_C);
	DDX_Control(pDX, IDC_EDIT14, m_ETA_C);
	DDX_Text(pDX, IDC_EDIT_PROBE_CURRENT, m_core_probe_curr);
	DDX_Control(pDX, IDC_EDIT9, m_core_resistance_C);
	DDX_Control(pDX, IDC_EDIT15, m_core_resistance_mean_C);
	DDX_Control(pDX, IDC_EDIT16, m_core_resistance_STD_C);
	DDX_Control(pDX, IDC_EDIT17, m_core_resistance_trend_C);
	DDX_Control(pDX, IDC_STATIC_core_color, m_core_color_C);
	DDX_Control(pDX, IDC_COMBO_CORE_THERM_ELEMENTS, m_select_media_core_C);
	DDX_Control(pDX, IDC_COMBO_CORE_THERM_ELEMENTS2, m_select_mean_jacket_C);
	//	DDX_Control(pDX, IDC_EDIT_PROBE_CURRENT2, m_jacket_probe_curr);
	DDX_Text(pDX, IDC_EDIT_PROBE_CURRENT2, m_jacket_probe_current);
	DDX_Control(pDX, IDC_STATIC_ANTILOOP, m_antiloop_C);
	DDX_Text(pDX, IDC_EDIT22, m_skip_points_thermostat);
	DDV_MinMaxInt(pDX, m_skip_points_thermostat, 0, 10);
	DDX_Control(pDX, IDC_COMBO_CORE_THERM_ELEMENTS3, m_elements_mean_therrmo_C);
	DDX_Control(pDX, IDC_STATIC_LED_THERMO, m_ledred_termo_medium_C);
	DDX_Control(pDX, IDC_STATIC_thermo_color3, m_therm_color_C);
	DDX_Control(pDX, IDC_STATIC_thermo_message, m_thermo_message_C);
	DDX_Control(pDX, IDC_EDIT11, m_PID_D_C);
	DDX_Control(pDX, IDC_STATIC_GRAPH, m_graph_C);
	DDX_Control(pDX, IDC_STATIC_CORE_GRAPH, m_graph_core_C);
	DDX_Text(pDX, IDC_EDIT23, m_I_PID);
}

BEGIN_MESSAGE_MAP(CminervaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CminervaDlg::OnBnClickedButtonTest)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CminervaDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_start_jacket, &CminervaDlg::OnBnClickedButtonstartjacket)
	ON_BN_CLICKED(IDC_BUTTON_RUN_CYCLE, &CminervaDlg::OnBnClickedButtonRunCycle)
	ON_BN_CLICKED(IDC_BUTTON_STOP_CYCLE, &CminervaDlg::OnBnClickedButtonStopCycle)
	ON_BN_CLICKED(IDC_BUTTON_SET_POINT, &CminervaDlg::OnBnClickedButtonSetPoint)
	ON_BN_CLICKED(IDC_BUTTON_PROBE_CURR_SET, &CminervaDlg::OnBnClickedButtonProbeCurrSet)
	ON_BN_CLICKED(IDC_BUTTON_START_CORE_MEASUREMENT, &CminervaDlg::OnBnClickedButtonStartCoreMeasurement)
	ON_BN_CLICKED(IDC_BUTTON_STOP_CORE_MEASUREMENT2, &CminervaDlg::OnBnClickedButtonStopCoreMeasurement2)
	ON_BN_CLICKED(IDC_BUTTON_PROBE_CURR_SET2, &CminervaDlg::OnBnClickedButtonProbeCurrSet2)
	ON_BN_CLICKED(IDC_BUTTON_START_THERMO, &CminervaDlg::OnBnClickedButtonStartThermo)
	ON_CBN_SELCHANGE(IDC_COMBO_CORE_THERM_ELEMENTS3, &CminervaDlg::OnCbnSelchangeComboCoreThermElements3)
	ON_BN_CLICKED(IDC_BUTTON_STOP_THERMO, &CminervaDlg::OnBnClickedButtonStopThermo)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CminervaDlg::OnDeltaposSpin1)
	// ON_BN_CLICKED(IDC_STATIC_GRAPH, &CminervaDlg::OnBnClickedStaticGraph)
	ON_BN_CLICKED(IDC_BUTTON_STOP_SHIELD_INJECT, &CminervaDlg::OnBnClickedButtonStopShieldInject)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CminervaDlg::OnDeltaposSpin2)
END_MESSAGE_MAP()


// CminervaDlg message handlers

BOOL CminervaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_string = new char[200];
//	 if (inizializza_GPIB())
		{
			assign_GPIBaddress();
			check_instruments();
			instruments_configuration();

		}
	 m_directory = L"C:\\Calorimeter\\Minerva\\";
	 m_set_point=10000; // Ohm
	 m_p_pid=10000;
	 m_d_PID=20000;
	 m_I_PID = 10000;
	 m_core_probe_curr = 50; // microAmpere
	 m_jacket_probe_current = 50; // microAmpere
	 load_elements_media();
	 m_media_core = NULL;
	 m_grafico_termo = NULL;
	 m_grafico_core = NULL;
	 UpdateData(FALSE);

	 m_seconds_beginning_Dec_2013 = CTime(2013, 12, 1, 0, 0, 0); // T_0 is December 1st, 2013, 00:00:00 
	 m_p_CDC = NULL;
	 m_p_CDC_CORE = NULL;
	 m_vector_thermo =  new (double[DIM_VET_TERMO+2][2]);;
	 m_vector_core = new (double[DIM_VET_CORE + 2][2]);;
	 m_points_vector_thermo = 0;
	 m_points_vector_core = 0;
	 m_scale_plot_thermo = 1;
	 m_scale_plot_core = 1;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CminervaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CminervaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CminervaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CminervaDlg::OnBnClickedButtonTest()
{
	// TODO: Add your control notification handler code here
		

	CFileDialog finestra_file(FALSE, L"*.dat", NULL, NULL, L"Data Files (*.dat)|*.dat|All Files (*.*)|*.*||"); // FALSE potrebbe stare per lettura; true per scrittura
	if (IDOK != finestra_file.DoModal()) return;
	CString name, path;
	name = finestra_file.GetFileName();
	path = finestra_file.GetPathName();
	//m_nome_C.SetWindowText(nome);
	CString ext = finestra_file.GetFileExt();
	CStdioFile matrice;
	;
	if (!matrice.Open(name, CFile::modeWrite | CFile::modeCreate))
	{
		AfxMessageBox(L" Sorry! I Can't create the Test File!", MB_ICONSTOP | MB_OK);
		return;
	}
	//create_thermo_graph();

}


BOOL CminervaDlg::inizializza_GPIB()
{
	SendIFC(GPIB0);
	IBSTA();

	CString testo;
	if (ibsta & ERR)
	{

		testo = " GPIB Inizialization Error ";

		AfxMessageBox(testo);
		return FALSE;


	}
	else
	{
		testo = " GPIB Inizialization OK ";
		
		add_message(testo);

	}


//	DevClear(0, NOADDR);
	IBSTA();
	if (ibsta & ERR)
	{
		
		testo = " No Devices connected!!  ";

		AfxMessageBox(testo);
		return FALSE;
	}

	return TRUE;
}


bool CminervaDlg::assign_GPIBaddress()
{
	m_adr_k2400 = assign_device(22);
	m_adr_k2400_core = assign_device(23);
	m_adr_k2400_jacket = assign_device(24);
	m_adr_k2182_core = assign_device(7);
	m_adr_k2182_multi = assign_device(8);

	m_adr_k6220_core = assign_device(11);
	m_adr_k6220_multi = assign_device(12);

		return false;
}


int CminervaDlg::assign_device(int GPIB_address)
{
	CString text;
	//	int dispositivo= ibdev(BDINDEX, address, NO_SECONDARY_ADDR,
	//                TIMEOUT, EOTMODE, EOSMODE);

	int device = ibdev(BDINDEX, GPIB_address, NO_SECONDARY_ADDR,
		TIMEOUT, 1, 0);

	if (ibsta & ERR)
	{
		text.Format(L"Unable to open device PAD= %d", GPIB_address);
		add_message(text);
		return FALSE;
	}
	text.Format(L" Instrument PAD=%d, m_dev = %d", GPIB_address, device);
	add_message(text);
	return device;
}


int CminervaDlg::add_message(CString text)
{
	CTime hour = CTime::GetCurrentTime();

	CString message;
	message.Format(L" %s: %s.", hour.Format(L"%x %X"), text);
	m_message_box_C.AddString(message);
	
	m_message_box_C.SetTopIndex(m_message_box_C.GetCount() - 4);
	return 1;
}

int CminervaDlg::IBSTA()
{
	int flag  ;
	(ibsta & ERR) ? flag = SW_SHOW : flag = SW_HIDE;
	m_ERR_C.ShowWindow(flag);
	m_ERR_C.RedrawWindow();

	(ibsta & TIMO) ? flag = SW_SHOW : flag = SW_HIDE;
	m_TIMO.ShowWindow(flag);
	m_TIMO.RedrawWindow();

	(ibsta & END) ? flag = SW_SHOW : flag = SW_HIDE;
	m_END_C.ShowWindow(flag);
	m_END_C.RedrawWindow();

	(ibsta & CMPL) ? flag = SW_SHOW : flag = SW_HIDE;
	m_CMPL_C.ShowWindow(flag);
	m_CMPL_C.RedrawWindow();

	return 0;
}


int CminervaDlg::poll(int address)
{
	char spr;
	BOOL esito = ibrsp(address, &spr);
	//m_poll = spr;
	IBSTA();
	if (ibsta & ERR)
	{
		CString text;
		text.Format(L"Error in polling for %d", address);
		add_message(text);
		return 0;
	}
	return 1;
}


int CminervaDlg::check_instruments()
{
	CString testo;
	if (!poll(m_adr_k2400))
	{
		testo = "Please Check K2400 Address 22";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}

	if (!poll(m_adr_k2400_core))
	{
		testo = "Please Check K2400 Address 23";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}
		
	if (!poll(m_adr_k2400_jacket))
	{
		testo = "Please Check K2400 Address 24";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}

	if (!poll(m_adr_k2182_core))
	{
		testo = "Please Check K2182 Address 7";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}

	if (!poll(m_adr_k2182_multi))
	{
		testo = "Please Check K2182 Address 8";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}

		;
	if (!poll(m_adr_k6220_core))
	{
		testo = "Please Check K6220 Address 11";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}

	if (!poll(m_adr_k6220_multi))
	{
		testo = "Please Check K6220 Address 12";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}
	;

	return 0;
}


BOOL CminervaDlg::write_GPIB(int address, CString command)
{
	CString text;
	 
	 
	 int length = conv_CS_CH(command);
	 m_string[length] = '\r';
	

	int result = ibwrt(address, m_string, length+1);
	IBSTA();
	if (result&ERR)

	{
		int errore = iberr;
		text.Format(L"*ERROR ERR=%d result=%d, Ibsta=%d", ERR, result, ibsta);
		add_message(text);
	}
	return result;
}


BOOL CminervaDlg::K2400_configuration(int address)
{
	CString text;
	text = L"SOUR:FUNC:MODE CURR";
	write_GPIB(address, text);

	text = L"SOUR:CURR:MODE FIX";
	write_GPIB(address, text);


	text.Format(L"SENS:FUNC 'VOLT'");
	write_GPIB(address, text);

	text.Format(L"SOUR:CURR:LEV 0");
	write_GPIB(address, text);

	
	if (address = m_adr_k2400)
	{
	text.Format(L"SENS:VOLT:RANG 200");
     write_GPIB(address, text);
	 text.Format(L"SENS:CURR:PROT 1");
	 write_GPIB(address, text);
	text.Format(L"SENS:VOLT:PROT 80");
	write_GPIB(address, text);

	}
	else
	{
	
	text.Format(L"SENS:VOLT:RANG 20");
	write_GPIB(address, text);

	text.Format(L"SENS:CURR:PROT 300E-3");
	write_GPIB(address, text);

	}

	k_2400_onoff(true, address);

	return 1;
}


int CminervaDlg::conv_CS_CH(CString text)
{
	int length = min(text.GetLength(),200);
		int ctr = 0;

		while (ctr < length)
		{
			m_string[ctr] = text[ctr];
			ctr++;
		}
		return length;
}


bool CminervaDlg::current_inject_k2400(int microampere, long address)
{
	CString text;

	text.Format(L"SOUR:CURR:RANG  %g ", microampere / 1000000.);
	write_GPIB(address, text);
	
	text.Format(L"SOUR:CURR:LEV %g", microampere / 1000000.);
	write_GPIB(address, text);
	return 1;
	

	
}

bool CminervaDlg::current_inject_k2400(double ampere, long address)
{
	CString text;

	text.Format(L"SOUR:CURR:RANG  %12.8f ", ampere );
	write_GPIB(address, text);

	text.Format(L"SOUR:CURR:LEV  %12.8f", ampere );
	write_GPIB(address, text);
	return 1;



}


bool CminervaDlg::k_2400_onoff(bool on, long address)
{
	CString text;
	if (on)
	{
	text = L":OUTPUT ON";
	}
	else
	{
	text = L":OUTPUT OFF";
	}
	write_GPIB(address, text);
	return on;
}


void CminervaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	k_2400_onoff(0, m_adr_k2400);
	k_2400_onoff(0, m_adr_k2400_core);
	k_2400_onoff(0, m_adr_k2400_jacket);
	k_2400_onoff(0, m_adr_k6220_core);
	delete[] m_string;
	if (m_media_core)
	{
		delete[] m_media_core;
	}

	// TODO: Add your message handler code here
}


int CminervaDlg::instruments_configuration()
{
	K2400_configuration(m_adr_k2400);
	K2400_configuration(m_adr_k2400_core);
	K2400_configuration(m_adr_k2400_jacket);
	K2182_configuration(m_adr_k2182_core);
	K2182_configuration(m_adr_k2182_multi);
	K6220_configuration(m_adr_k6220_core);
	K6220_configuration(m_adr_k6220_multi);
	return 0;
}


BOOL CminervaDlg::read_GPIB(int address, CString * p_text)
{
	int result = ibrd(address, m_string, 200);
	IBSTA();
	int ctr = 0;
	p_text->Delete(0,1000);
	while (ctr < ibcntl)
	{
		p_text->AppendChar( m_string[ctr]);
		ctr++;
	}
	
	return ibcntl;
}


int CminervaDlg::K2182_configuration(int address)
{
	
	CString text;
	text = L":SENS:VOLT:RANGE:AUTO ON";
	write_GPIB(address, text);

	text = L":SENS:VOLT:NPLC 5";
	write_GPIB(address, text);

	text = L":SENS:VOLT:DFIL:COUNT 5";
	write_GPIB(address, text);

	text = L":SENS:VOLT:DFIL:WIND 0.01";
	write_GPIB(address, text);

	text = L":SENS:VOLT:DFIL:TCON REP";
	write_GPIB(address, text);

	text = L":SENS:VOLT:CHAN1:DFIL:STAT ON";
	write_GPIB(address, text);
	//  m_richiesta_mandata=FALSE;


	return 0;
}


double CminervaDlg::read_k2182(int address,BOOL send_request)
{
	CString text;
	double volt = -9999;
	if (send_request)
	{
		text = L":sens:data:fres?";
		write_GPIB(address, text);
		//Sleep(200);
	}
	BOOL status = read_GPIB(address, &text);
	if (status)
	{
		volt = wcstod(text, NULL);
	}
	return volt;
}


void CminervaDlg::K6220_configuration(int address)
{
	CString text;
	text.Format(L"CURR  %6.3g", 100. / 1000000.);
	write_GPIB(address, text);

	text = L"CURR:FILT ON";
	write_GPIB(address, text);

	//   	 scrivi_GPIB(m_adr_k6220_continuo,"INIT:IMM");


	text = L"CURR:RANG:auto ON";
	write_GPIB(address, text);
	
	return ;
}


void CminervaDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	 

	
	if (m_secondi_core <= 0 || m_micro_ampere_core <= 0 || m_micro_ampere_core >500 || m_secondi_core>15000)
	{
		AfxMessageBox(L"*** ERRORE NEI PARAMETRI IMPOSTATI", MB_OK | MB_ICONSTOP);
		return;
	}
	 

	/*
	if (m_start_togheter)
	{
		scrivi_GPIB(m_adr_k2400_2, testo);
		m_corrente_jacket = m_corrente_core;
		testo.Format("%5.5g", m_corrente_jacket);
		m_microamp_jacket_C.SetWindowText(testo);
		m_percento_jacket_C.GetWindowText(testo);
		m_percento_jacket = strtod(testo, NULL);
		if (m_percento_jacket<0 || m_percento_jacket>2)
		{
			AfxMessageBox("*** ERRORE NEL PARAMETRO PERCENTUALE ", MB_OK | MB_ICONSTOP);
			return;
		}

	}
    if (m_start_togheter)  scrivi_GPIB(m_adr_k2400_2, testo);
	m_core_riferimento = m_core_ultima;
	m_set_point_riferimento = m_medium_set_point;
	*/

	
	
	m_button_start_cycles_C.EnableWindow(FALSE);
	 m_flag_core = 1;
	//crea_file_ciclo();

	//controllo_potenza_core();
	 k_2400_onoff(0, m_adr_k2400_core);
	 current_inject_k2400(m_micro_ampere_core, m_adr_k2400_core);

	 core_power();
	return;


}


void CminervaDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1001) // power to core
	{
		core_power();
	}
	else if (nIDEvent == 1002)
	{
		cycle_core_power(); // cycle of power to core
	}
	else if (nIDEvent == 2001) // read core resistores
	{
		manage_core_measure();
	}
	else if (nIDEvent == 2002)
	{
		read_core(); 
	}
	else if (nIDEvent == 3000)
	{
		manage_thermostat();
	}
		
	CDialogEx::OnTimer(nIDEvent);
}


int CminervaDlg::core_power()
{
	double volt;
	CString text;
	if (m_flag_core == 1)
	{
		SetTimer(1001, 100, NULL);
		 m_timer_core = clock();
		 k_2400_onoff(1, m_adr_k2400_core);
		m_joule_core = 0;
		m_flag_core = 2;
		create_cycle_file();
	}
	
		
		 long cronometer = (clock() - m_timer_core);
		 double seconds = (double)(cronometer) / 1000.;
		 text.Format(L"%6.2f", seconds);
		 m_seconds_core_C.SetWindowTextW(text);
		
	
		 volt = k_2400_read_volt(m_adr_k2400_core);
		 text.Format(L"%g", volt);
		 m_volt_core_C.SetWindowTextW(text);
  		 double micro_watt = microwatt(m_micro_ampere_core, volt, &m_microwatt_core_C);

 if (m_flag_core == 2)
		 {

			 microjoule(micro_watt, cronometer, &m_joule_core, &m_joule_core_C);
			 write_file_cycle(cronometer, m_joule_core, m_micro_ampere_core, volt, 0, 0, 0);
		 } 

   if (seconds >= m_secondi_core)
		 {
			 k_2400_onoff(0, m_adr_k2400_core);
			 KillTimer(1001);
			 m_flag_core = 3;
			 m_file_cycle.Close();
			 m_button_start_cycles_C.EnableWindow(TRUE);
		 }
		
		
			
		
	return 0;
}



double CminervaDlg::k_2400_read_volt(int address)
{
	CString text;
	text = L":READ?";
	double volt;
	write_GPIB(address, text);
	BOOL status = read_GPIB(address, &text);
	if (status)
	{
		volt= wcstod(text, NULL);
	

	}
	else
	{
		volt = -999.;
	}
	 
	return volt;
}


double CminervaDlg::microwatt(double current, double volt,  CWnd * window)
{
	double microwatt;
	microwatt = current*volt;
	CString text;
	text.Format(L"%g", microwatt);
	window->SetWindowTextW(text);
	return microwatt;
}


double CminervaDlg::microjoule(double watt, long live_time, double *joule, CWnd * window)
{
	static long old_time;
	double microjoule;
	
	if (!*joule)
	{
		microjoule = watt*live_time / 1000.;
		
	}
	else
	{
		microjoule = watt*(  live_time-old_time) / 1000.;
	}
	*joule += microjoule;
	old_time = live_time;
	CString text;
	text.Format(L"%g", *joule);
	window->SetWindowTextW(text);

	return microjoule;
}


void CminervaDlg::OnBnClickedButtonstartjacket()
{
	// TODO: Add your control notification handler code here
}


bool CminervaDlg::create_cycle_file()
{
	CTime time = CTime::GetCurrentTime();

	CString file_name = m_directory + time.Format("%Y_%m_%d_%H_%M_%S_cycle.dat");
	m_file_cycle.Abort();
	
	BOOL esito = m_file_cycle.Open(file_name, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (m_file_cycle.m_hFile != CFile::hFileNull)
	{
		add_message(L" Cycle file opened " + file_name);
		//m_file_name_C.SetWindowText(finestra_file.GetFileName());
		CString aux = L"  Seconds    Energy_in_core    Current(microA)   Volt_core    Energy_in_jacket   Current(microA)   Volt_jacket \n";
		m_file_cycle.WriteString(aux);

	}
	else
	{
		add_message(L"Could not Open" + file_name);
	}
	
	return 0;
}


double CminervaDlg::write_file_cycle(long cronometer, double joule_core, double current_core, double volt, double joule_jacket, double current_jacket, double volt_jacket)
{
	CTime  absolute_seconds = CTime::GetCurrentTime();
	long seconds = absolute_seconds.GetTime();
	CString aux;
	aux.Format(L" %6.3f    %7.5g    %7.5g   %7.5g    %7.5g   %7.5g    %7.5g   \n", (double)cronometer/1000., joule_core, current_core, volt
		, joule_jacket, current_jacket, volt_jacket);
	m_file_cycle.WriteString(aux);

	return 0;
}


void CminervaDlg::OnBnClickedButtonRunCycle()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_button_stop_cycle_C.EnableWindow(TRUE);
	m_button_start_cycles_C.EnableWindow(FALSE);
	SetTimer(1002, 1000, NULL);
	m_flag_cycle_power_core = 1;
	m_done_cycles = 0;
	cycle_core_power();
	
}


void CminervaDlg::OnBnClickedButtonStopCycle()
{
	// TODO: Add your control notification handler code here
	m_button_stop_cycle_C.EnableWindow(FALSE);
	m_button_start_cycles_C.EnableWindow(TRUE);
	KillTimer(1002);
}


void CminervaDlg::cycle_core_power()
{
	if (m_flag_cycle_power_core == 1)
	{
		OnBnClickedButton2();
		m_done_cycles++;
		m_aux_text.Format(L"%d", m_done_cycles);
		m_done_C.SetWindowTextW(m_aux_text);
		m_flag_cycle_power_core = 2;

	}
	else if (m_flag_cycle_power_core == 2)
	{
		if (m_flag_core == 3)
		{
			if (m_done_cycles >= m_number_of_cycles)
			{
				OnBnClickedButtonStopCycle();
				m_flag_cycle_power_core =0;

			}
			else
			{
				m_pause_start = clock();
				control_pause();
				m_flag_cycle_power_core = 3;
			}


		}
		
	}
	else if (m_flag_cycle_power_core == 3)
	{
		if (!control_pause())
		{
			m_flag_cycle_power_core = 1;

		}

	}
}


// checks whether pasue time has been reached before a new cycle is launched
BOOL CminervaDlg::control_pause()
{
	int seconds = (clock() - m_pause_start) / 1000;
	m_aux_text.Format(L"%d", m_pause_cycle - seconds);
	m_pause_C.SetWindowTextW(m_aux_text);
	return (m_pause_cycle>seconds);
}


void CminervaDlg::OnBnClickedButtonSetPoint()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

}


double CminervaDlg::read_core() /* cAMBIARE NOME QUI E CHIAMARLA requesT_CORE */

{
	char spr;
	BOOL esito = ibrsp(m_adr_k2182_core, &spr);
	double resistance = 0;
	m_anti_block_core++;

	BOOL pronto = spr & 16;
	if (pronto)
	{
		resistance = read_resistance(m_adr_k2182_core);
		manage_data_core(resistance);
	}
	if (pronto || m_anti_block_core>100)
	{

		if (m_anti_block_core > 100)
		{
			m_anti_block_core = 0;
			CString text = L":ABORT";
			write_GPIB(m_adr_k2182_core, text);

		}
		KillTimer(2002);
		SetTimer(2001, TIMER_CORE, NULL); 
	}
	
	
	m_aux_text.Format(L"%d", m_anti_block_core);
	m_antiloop_C.SetWindowTextW(m_aux_text);
	
	return resistance;
}
	


void CminervaDlg::OnBnClickedButtonProbeCurrSet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	k6220_set_current(m_core_probe_curr, m_adr_k6220_core);
	

}


int CminervaDlg::load_elements_media()
{
	int ctr = 1;
	CString testo;

	while (ctr<=20)
	{
		testo.Format(L"%d", ctr);
		m_select_media_core_C.AddString(testo);
		m_select_mean_jacket_C.AddString(testo);
		m_elements_mean_therrmo_C.AddString(testo);
		ctr++;

	}
	m_select_media_core_C.SetCurSel(10);
	m_select_mean_jacket_C.SetCurSel(10);
	m_elements_mean_therrmo_C.SetCurSel(2);
	m_mean_thermostat = m_elements_mean_therrmo_C.GetCurSel()+1;
	return 0;
}


void CminervaDlg::OnBnClickedButtonStartCoreMeasurement()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_p_CDC_CORE = m_core_color_C.GetDC();
	k6220_set_current(m_core_probe_curr, m_adr_k6220_core);
	k6220_onoff(TRUE, m_adr_k6220_core);
	SetTimer(2001, 1000,NULL);
	m_flag_measure_core = 0;
	if (m_media_core)
	{
		delete[] m_media_core;
	}
	m_elements_into_mean_core = m_select_media_core_C.GetCurSel()+1;
	if (m_elements_into_mean_core>0)
	{
		m_media_core = new  (double[m_elements_into_mean_core+2][2]);
		int ctr = 0;
		while (ctr < m_elements_into_mean_core)
		{ /* cleans all mean elements and their acquisition times */
			m_media_core[ctr][0] = 0;
			m_media_core[ctr][1] = 0;
			ctr++;
		}
	}
	create_file_core();
	manage_core_measure();
	create_core_graph();
}


int CminervaDlg::k6220_set_current(double microamp, long address)
{
	CString text;
	text.Format(L"CURR  %6.3g", microamp / 1000000.);
	write_GPIB(address, text);

	return 0;
}


BOOL CminervaDlg::k6220_onoff(bool on, long address)
{
	CString text;
	if (on)
	{
		text = L"OUTPUT ON";
	}
	else
	{
		text = L"OUTPUT OFF";
	}
	write_GPIB(address, text);
	return on;
	
}


void CminervaDlg::OnBnClickedButtonStopCoreMeasurement2()
{
	// TODO: Add your control notification handler code here
	k6220_onoff(FALSE, m_adr_k6220_core);
	KillTimer(2001);
	KillTimer(2002);
}


int CminervaDlg::manage_core_measure() /* Manages how the core measurements are handled, instantaneously and averaged out */
									 
{
	KillTimer(2001); /* sends control to timer 2002*/
	m_anti_block_core = 0;
	if (!request_data_core())
	{
		SetTimer(2001, TIMER_CORE, NULL); 
		return 0; 
	}
	
	SetTimer(2002, TIMER_CORE / 10, NULL); /* set the faster timer for check whether a new measurement is ready to be retrieved */

    read_core();
	return 0;
}


double CminervaDlg::manage_core_media(double resistance)
{
	if (m_elements_into_mean_core<1) return 0;
	CString text;

	// shifts the positions of the vector's content, by one step at each call
	int ctr = 0;
	while (ctr<m_elements_into_mean_core - 1)
	{
		m_media_core[ctr][0] = m_media_core[ctr+1][0]; // time
		m_media_core[ctr][1] = m_media_core[ctr + 1][1]; // resistance
		ctr++;
	}
	m_media_core[m_elements_into_mean_core - 1][1] = resistance; /*occhio che qui c'è stata una conversione di data type*/
	m_media_core[m_elements_into_mean_core - 1][0] = m_seconds_continuous; /* Time when resistance value was fetched by K2182A*/ 
	// m_vettore_tempo[m_contatore_punti] = (clock()+500)/1000 -m_secondi_start;

	// Calculations of mean, stdev, and trend

	ctr = 0;
	double mean = 0, sigma = 999, trend = 999;
	double accumulator = 0;

	if (m_elements_into_mean_core>1)
	{
		
		m_linear_regression.calcola_regressione(m_media_core, 0, m_elements_into_mean_core-1);
		
		/* Calculate mean value and send it to its window */
		mean = m_linear_regression.m_y_medio;
		m_aux_text.Format(L"%9.9f", mean);
		m_core_resistance_mean_C.SetWindowTextW(m_aux_text);

		
		/* Calculate Stdev value and send it to its window */
		sigma = m_linear_regression.m_standard_dev;
		
		
		m_aux_text.Format(L"%6.5g", sigma);
		m_core_resistance_STD_C.SetWindowTextW(m_aux_text);

		/* Calculate trend value and send it to its window */
		trend = -60 * m_linear_regression.m_coefficiente_angolare / (.04*mean);
		m_aux_text.Format(L"%6.5g", trend);
		m_core_resistance_trend_C.SetWindowTextW(m_aux_text);
		
		thermo(trend, m_p_CDC_CORE);
		save_core(m_seconds_continuous, mean, sigma, trend); 


		/*
		
		termo(trend, trend_CDC);
		testo.Format("%9.9f", trend);
		m_trend_continuo_C.SetWindowText(testo);
		ctr = 0;
		while (ctr<m_elementi_media_continuo)
		{
			accumulatore += pow((m_puntatore_media_continuo[ctr] - media), 2);
			ctr++;
		}
		sigma = sqrt(accumulatore / m_elementi_media_continuo);
		testo.Format("%5.5f", sigma);
		m_stdcontinium_C.SetWindowText(testo);
		*/
		
	}

	//*p_trend_finestre[m_sensore_in_misura] = -60 *m_regressione_lineare.m_coefficiente_angolare/(.04*media);
	// UpdateData(FALSE);
	return 0;

}




BOOL CminervaDlg::request_data_core()
{
	CString text = L":sens:data:fres?";
	return write_GPIB(m_adr_k2182_core, text);
}


double CminervaDlg::read_resistance(int address,BOOL core)
{

	double volt = read_k2182(address, FALSE);

	if (volt == -9999)

	{
	int error = iberr;
	m_aux_text.Format(L"*ERROR on Continuous Reading ERR=%d result=%d, Ibsta=%d", error, 0, ibsta);
	add_message(m_aux_text);

	return -999999999;
	}
	double current = 0;
	core ? current = m_core_probe_curr : current = m_jacket_probe_current;
	double R = RESISTENZA_PONTE_WHEATSTONE;
	double i = current / 1000000.;
	double V = volt;
	double resistance = R *(i*R - 3 * V) / (V + i*R);

	return resistance;
	
	
}


double CminervaDlg::manage_data_core(double resistance)
{
	CString text;

	CTime today = CTime::GetCurrentTime(); /* potrebbe non esser necessario */

	/* m_seconds_beginning_2013 = CTime(today.GetYear, today.GetMonth, today.GetDay, 0, 0, 0); */


	/* m_secondi_assoluti = CTime::GetCurrentTime(); */
	m_seconds_absolute = CTime::GetCurrentTime();
	m_seconds_continuous = m_seconds_absolute.GetTime() - m_seconds_beginning_Dec_2013.GetTime();
	manage_core_media(resistance);

	text.Format(L"%9.9f", resistance);
	m_core_resistance_C.SetWindowTextW(text);

	/*gestisci_media_continuo(resistenza);*/

	//text.Format(L"%d", m_seconds_continuous);
	//m_core_resistance_mean_C.SetWindowTextW(text);

	
	return resistance;
}


void CminervaDlg::OnBnClickedButtonProbeCurrSet2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	k6220_set_current(m_jacket_probe_current, m_adr_k6220_multi);
}


void CminervaDlg::OnBnClickedButtonStartThermo()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_do_noting = -3;
	m_p_CDC = m_therm_color_C.GetDC();

	k6220_onoff(1, m_adr_k6220_multi);
		m_status_thermostat = INIT;
		m_old_thermo_temperature = 0;
	manage_thermostat();// start reading 
	k_2400_onoff(TRUE, m_adr_k2400);

	Create_Thermostat_Shield_File();
	create_thermo_graph(); // CRASH dopo alcune ore. Potremmo valutare di sospendere il grafico


}


BOOL CminervaDlg::manage_thermostat()
{
	// KillTimer(3001); /* anti-block on the multi-purpose end of thermostat management*/
	// No need to use a dedicated timer here as the reading will be continuous for a few measurements.
	if (m_status_thermostat == INIT)
	{	
		m_ledred_termo_medium_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		m_ledred_termo_medium_C.ShowWindow(SW_SHOW);
		m_ledred_termo_medium_C.RedrawWindow();
		m_derivative_power = DERIVATIVE_POWER;
		m_status_thermostat = START;
		// AlTRE INIZIALIZZAZIONI GRAFICO ECC ECC 
		
	}

	if (m_status_thermostat == START)
	{
		KillTimer(3000);
		request_data_multi();
		m_ledred_termo_medium_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		m_ledred_termo_medium_C.ShowWindow(SW_SHOW);
		m_ledred_termo_medium_C.RedrawWindow();
		m_status_thermostat = WAITING;
		SetTimer(3000, 100, NULL);
		m_anti_block_multi = 0;

	}
	else if (m_status_thermostat == WAITING)
	{
		double resistance = read_multi();
		if (resistance>1)
		{

			m_anti_block_multi = 0;
			m_ledred_termo_medium_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
			m_ledred_termo_medium_C.ShowWindow(SW_SHOW);
			m_ledred_termo_medium_C.RedrawWindow();

			if (manage_mean_thermostat(resistance))
			{			
				KillTimer(3000);
				m_status_thermostat = START;
				SetTimer(3000, TIMER_THERMOSTAT, NULL);
				


			}
			else
			{
				request_data_multi();
				m_ledred_termo_medium_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
				m_ledred_termo_medium_C.ShowWindow(SW_SHOW);
				m_ledred_termo_medium_C.RedrawWindow();
			}

			
	
		}
		else
		{
			if (m_anti_block_multi > 100)
			{
				KillTimer(3000);
				CString text = L":ABORT";
				 write_GPIB(m_adr_k2182_multi, text);
				m_status_thermostat = START;

				m_anti_block_multi = 0;
				SetTimer(3000, 100, NULL);


			}

		}

	}

	
	/*
	SetTimer(3000, 10000, NULL);/* Timer specific for thermostat, 10s*/
	// SetTimer(2002, TIMER_CORE / 10, NULL); /* set the faster timer for check whether a new measurement is ready to be retrieved 

	//double thermostat_resistance = read_thermostat();
	//m_aux_text.Format(L"%9.9f", thermostat_resistance);

	//m_shield_ohm_C.SetWindowTextW(m_aux_text);

	return 0;
}


double CminervaDlg::read_thermostat() /* handles repeated readings of the thermostat resistance without 
									  invoking any additional timer */
{
	CString text;
	int ctr = 0;
	double resistance = 0.;
	while (ctr < m_mean_thermostat)
	{
		resistance += read_resistance_multi(m_adr_k2182_multi); /* Acquires a series of resistance measurements */
		ctr++;
	}

	resistance /= m_mean_thermostat; /* calculate average resistance */
	return resistance;
}


void CminervaDlg::OnCbnSelchangeComboCoreThermElements3()
{
	m_mean_thermostat = m_elements_mean_therrmo_C.GetCurSel()+1;
	return;
}


double CminervaDlg::read_resistance_multi(int address, BOOL send_request)
{
	double volt = read_k2182(m_adr_k2182_multi, send_request);

	if (volt == -9999)
	{
		int error = iberr;
		m_aux_text.Format(L"*ERROR on Multi Reading ERR=%d result=%d, Ibsta=%d", error, 0, ibsta); /* !! Need another specifier to inform where on the multi we are now */
		add_message(m_aux_text);
		return -999999999;
	}

	/* Calculates the thermistor's resistance value*/
	double R = RESISTENZA_PONTE_WHEATSTONE;
	// double i = m_multi_probe_current / 1000000.;
	double i = m_jacket_probe_current / 1000000.;
	double V = volt;
	double resistance = R *(i*R - 3 * V) / (V + i*R);

	return resistance;

}


BOOL CminervaDlg::request_data_multi()
{
	CString text = L":sens:data:fres?";
	return write_GPIB(m_adr_k2182_multi, text);
}


double CminervaDlg::read_multi()
{
	char spr;
	BOOL esito = ibrsp(m_adr_k2182_multi, &spr);
	double resistance = 0;
	m_anti_block_multi++;

	BOOL pronto = spr & 16;
	if (pronto)
	{
		resistance = read_resistance(m_adr_k2182_multi,FALSE);
		m_anti_block_multi = 0;
	
	}
	


	m_aux_text.Format(L"%d", m_anti_block_multi);
	m_antiloop_C.SetWindowTextW(m_aux_text);

	return resistance;
}


void CminervaDlg::OnBnClickedButtonStopThermo()
{
	
	k6220_onoff(0, m_adr_k6220_multi);
	KillTimer(3000);
}


BOOL CminervaDlg::manage_mean_thermostat(double resistance)
{
	static int ctr = 0, discharge =0;
	static double  integrator = 0;
	static double mean_resistance = 0;
	if (m_status_thermostat == INIT)
	{
		ctr = 0;
		integrator = 0;
		discharge = 0;
		return 0;
	}
	 
	if (discharge < m_skip_points_thermostat)
	{
		discharge++;
		return 0;

	}

	ctr++;
	integrator += resistance;
		mean_resistance = integrator / ctr;
		m_aux_text.Format(L"%9.9f", mean_resistance);
		m_shield_ohm_C.SetWindowTextW(m_aux_text);

	if (ctr >= m_mean_thermostat)
	{
		PID(mean_resistance);
		discharge = 0;
		ctr = 0;
		integrator = 0;
		return 1;

	}


	;
	return 0;
}


// Per Stefano:
// In Calorimetro questa era un funzione che serviva solo a calcolare la corrente da erogare per la termostatazione. 
// Qui invece PID() vuole fare anche il lavoro di CcalorimetroDlg::gestisci_termostato(void) ? 
// NB in Calorimetro era CcalorimetroDlg::PID_medium(double delta_T,double velocita)

int CminervaDlg::PID(double resistance)
{
	static long old_time = 0;
	double speed = .1;
	long time = clock();
	double delta_T = (((m_set_point - resistance) / fabs(m_set_point)) / 0.04);
	m_aux_text.Format(L"%g", delta_T);
	m_delta_k_C.SetWindowText(m_aux_text);
	if (m_old_thermo_temperature)
	{
		speed = 60000 * (delta_T - m_old_thermo_temperature) / (time - old_time); // 60000: convertion factor from milliseconds to minutes. Speed is given in Kelvin / minute
		m_aux_text.Format(L"%6.3g ", speed);
		//termo(speed, p_termo);
		m_speed_shield_C.SetWindowText(m_aux_text);
	
		thermo(speed, m_p_CDC);

	}
	m_old_thermo_temperature = delta_T;
	double thermostat_resistance =  RESISTANCE_THERMOSTAT;
	double milliampere= 0;
	double power=0;
		double eta = -delta_T / speed;
		if (m_do_noting < 0)
		{
			m_do_noting++;
			m_aux_text.Format(L"DO Nothing ETA %d min", int(-delta_T / speed));
			m_ETA_C.SetWindowText(m_aux_text);
			m_ETA_C.UpdateWindow();
			if (m_do_noting < -1)
			{
				power = m_d_PID ;
			}
			else
			{
				power = m_d_PID - 10 * m_p_pid*delta_T;

			}
			
		}

	else if (delta_T<-0.05 && /*(speed > 0. && speed < 2.) )*/ (fabs(speed)<2) && eta>0 )  /*questa era quella di Stefano */  // Constant DERIVATIVE Mode: Slower than 2 K/min and farther away than -100 mK from target.         
		// Adds or removes power in order to maintain a constant speed, measured as temperature/time, of 0.1 K/min. 
		// 20 Genn 2014: il controllo sul segno della velocità non ha funzionato: ha ripristinato il dente di sega derivativo. Occorre tornare al fabs(speed)<2 e risolvere separatamente 
		// il problema della caduta libera da cui non si esce più.
	{
		double eta_desiderato = 20.;
		double delta_mW = 1000*((eta - eta_desiderato)/eta)  *(delta_T ) / (eta_desiderato * 6);
		m_d_PID -= delta_mW; // Stefano changed 100 to 10 for smoothing 
		power = m_d_PID - 10 * m_p_pid*delta_T;
		//power = m_d_PID;
			m_aux_text.Format(L" Derivative ETA= %g", eta);
			m_ETA_C.SetWindowTextW(m_aux_text);
		m_ETA_C.UpdateWindow();
		UpdateData(FALSE);
		// Potremmo dover metter qui un controllo che faccia uscire il software dalla caduta libera, in PID Derivative mode. 
	}
	else if (delta_T<-0.1 && speed >= 2. /*fabs(speed)>=2.*/ ) // It positive speed too high then power off
	{
		power = 0;
		m_ETA_C.SetWindowTextW(L" Going up too fast, power off "); // Trying to identify what switches off power. Wasn't this though.
		m_ETA_C.UpdateWindow();
	}
	else
	{
		if (((delta_T>0 && speed>0) || fabs(speed) < 0.00001 || delta_T / speed < -30. || (delta_T < 0 && speed < 0)) /* && (TRUE || m_flag_core==2) */ ) // ultima condizione rimossa perché inattiva
		{ 
			// CONDITIONS that access the DISSIPATIVE routine
			// 1) Temperature greater than set point and still rising
			// 2) Speed below 10 microK / min: steady state
			// 3) Temperature below set point, positive speed and time of arrival greater than 30 min
			// 4) Temperature below set point and negative temperature speed (falling temperature)

			double fattore = 1;  // fattore  // Stefano changed 5 to 1 for smoothing 
			if (fabs(delta_T) < .001) fattore = .5; // scaling factor becomes 10x smaller if temperature within 1 mK from target (higher or lower) // Stefano changed .5 to .1 for smoothing 

			//		if (delta_T/velocita<-5) fattore*=-1;
			double delta_PID = fattore*m_I_PID*delta_T*(clock() - old_time) / 60000.; // INTEGRAL MODE;  dimensions: [fattore] * [m_p_PID] * K * min  
			m_d_PID -= delta_PID;

			//		int pippo = m_tempo_termostato;
			m_aux_text.Format(L"%g", m_d_PID);
			m_PID_D_C.SetWindowText(m_aux_text);
			m_aux_text.Format(L" Diss. ETA %d min", int(-delta_T / speed));
			m_ETA_C.SetWindowText(m_aux_text);
			m_ETA_C.UpdateWindow();

		}
		else if (eta< 10.) // If ETA is within 10 minutes? May need to re-write this to consider what happens when either DeltaT>0 or speed<0
			// cambiato da -10 a -20: la procedura di slowing avviene per tempi più lunghi.
		{
			// m_d_PID += .1*m_I_PID*delta_T*(clock() - old_time) / 60000; /* il coefficiente moltiplicativo era .5 fino al 21 Genn 2014*/
			m_d_PID -= (10 - eta)*m_d_PID*.005;  // Stefano changed 11/2/2014 

			// if (delta_T > 0) m_d_PID *= -1.; // Massimo e Marco: 16/01/2014 proviamo a vedere se, superato il set point, in questo modo ci scendiamo di nuovo.
			m_aux_text.Format(L"%g", m_d_PID);
			m_PID_D_C.SetWindowText(m_aux_text);

			m_aux_text.Format(L"Slowing ETA %d min", int(-delta_T / speed));
			m_ETA_C.SetWindowText(m_aux_text);
			m_ETA_C.UpdateWindow();
		}
		else
		{

			m_aux_text.Format(L" Prop. ETA %d min", int(-delta_T / speed));
			m_ETA_C.SetWindowText(m_aux_text);
			m_ETA_C.UpdateWindow();
		}
		
		power = m_d_PID - 10 * m_p_pid*delta_T; // Derivative and proportional term; 
	}
	  
	
	if (power>0)
	{
		milliampere = sqrt(power / thermostat_resistance);
	}
	else milliampere = 0;

	milliampere = min(milliampere, 1.5); // Massimo e Marco: Setting maximum injection current to 1.5 mA
	m_aux_text.Format(L"%6.5g", power);
	m_microW_shield_C.SetWindowTextW(m_aux_text);

	current_inject_k2400(milliampere / 1000., m_adr_k2400);
	k_2400_read_volt(m_adr_k2400);
	Write_To_File_Thermostat_Shield(m_set_point, resistance, delta_T, power, speed);
	old_time = time;

	return 0;

	/*
	 
	CString testo;
	// if (delta_T >0) return 0;
 	
	


     potenza = m_PID_D_Medium-10*m_PID_P_Medium*delta_T;
	}

	if (potenza>0)
	{
		microampere=sqrt(potenza/resistenza)*1000;
	}
	else microampere=0;
	m_tempo_termostato=clock();
//	testo.Format("ETA = %d min",int(-delta_T/velocita)); 
	 m_ETA_C.SetWindowText(testo);
  	return min(microampere,100000);  // 11/3/2011 introdotta sqrt() per mantenere la proporzionalità con Watt
	*/


	return 0;
}



int CminervaDlg::thermo(double speed, CDC * pCDC) // Color coding of the thermostat status
{
	
	double estremo = .001;

	int r = max(min(255 * (speed / estremo), 255), 0);
	int b = max(min(255 * (-speed / estremo), 255), 0);
int g = max(min(255 - r * 10 - b * 10, 255), 0);
CRect rectangle;
pCDC->GetWindow()->GetClientRect(&rectangle);
COLORREF color = RGB(r, g, b);
//finestra->SetBkColor(colore);
pCDC->FillSolidRect(rectangle, color);

return 0;
}


void CminervaDlg::Save_Measurements_Data(void) // Saves all measurement setup data to a SetUp file;
{
	UpdateData(TRUE);
	CStdioFile SetUpFile; /* where are we going to write data */
	BOOL whatsup = SetUpFile.Open(L"C:\\Calorimeter\\Minerva\\Setup_Minerva.txt", CFile::modeCreate | CFile::modeWrite);
	if (!whatsup)
	{
		AfxMessageBox(L"Problems with the SetUp File: Cannot Read or Write");
		return;
	}
}

// =================================================================================
// Roba su cui ha smanettato Massimo da solo Martedi 17 Dicembre
// Non mi è ancora chiaro come si invocano queste due funzioni 
// mi sembra ci siano delle differenze tra questa implementazione
// e quella fatta in CcalorimetroDlg dove PID_medium(double delta_T,double velocita)
// e termo_medium() non sono uguali a PID(double resistance) di qui
// =================================================================================

void CminervaDlg::Create_Thermostat_Shield_File(void)
{
	CTime  time_now = CTime::GetCurrentTime();

	CString now = m_directory + time_now.Format(L"%Y_%m_%d_%H_%M_%S_thermostat_shield.dat");
	m_file_thermo_shield.Abort(); 
	BOOL whatsup = m_file_thermo_shield.Open(now, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (m_file_thermo_shield.m_hFile != CFile::hFileNull)
	{
		AfxMessageBox(L"Thermostat Shield Log File Open", MB_OK | MB_ICONINFORMATION);
		//m_file_name_C.SetWindowText(finestra_file.GetFileName());
		CString aux = L" Seconds \t deltaT \t speed (K/min) \t Power(mW) \t Sensor(ohm) \t Target(ohm) \t PID_propor \t PID_dissip\n";
		m_file_thermo_shield.WriteString(aux);
	}
	else
	{
		// AfxMessageBox(L"Could not Open Thermostat Shield Log File Open");
		add_message(L" Could not Open Thermostat Shield Log File " + now);
	}

	return;
}


unsigned long CminervaDlg::Write_To_File_Thermostat_Shield(double target, double sensor, double deltaT, double power, double speed)
{
	m_seconds_absolute = CTime::GetCurrentTime();
	long seconds = m_seconds_absolute.GetTime() - m_seconds_beginning_Dec_2013.GetTime();
	if (m_file_thermo_shield.m_hFile != CFile::hFileNull)
	{
		CString aux;
		aux.Format(L" %6d \t%7.5g \t%7.5g \t%7.5g \t%12.12g \t%12.12g \t%7.5g \t%7.5g \n", seconds, deltaT, speed, power, sensor, target, m_p_pid, m_d_PID);
		m_file_thermo_shield.WriteString(aux);
	}
	// plotta_termo(secondi, delta); // questo lo faccio con Stefano; 
	plot_thermostat(seconds, deltaT);
	return 0;
}


int CminervaDlg::create_thermo_graph()
{
	//return 0;
	if (m_grafico_termo)
	{
		//m_grafico_termo->puntatoreCDC->DeleteDC();
		delete m_grafico_termo;
	}
	m_grafico_termo = new grafico_ver2;
	m_grafico_termo->assegna(&m_graph_C);
	m_grafico_termo->back_ground_color[0] = 245;
	m_grafico_termo->back_ground_color[1] = 245;
	m_grafico_termo->back_ground_color[2] = 245;
	m_grafico_termo->riempi_tutto();
	m_grafico_termo->sposta_label_x_axis(5);
	m_grafico_termo->coordinate(0, 3600, -.001, +.001);
	m_grafico_termo->cambia_colore_frame(0, 50, 0, 1);
	m_grafico_termo->CambiaColore(200, 0, 0, 2);
	m_grafico_termo->plotta_frame();


	return 0;
}


int CminervaDlg::plot_thermostat(double time, double delta_t)
{
	double ymin = delta_t;
	double  ymax = delta_t;
	if (m_points_vector_thermo<DIM_VET_TERMO)
	{
		m_vector_thermo[m_points_vector_thermo][0] = time;
		m_vector_thermo[m_points_vector_thermo][1] = delta_t;
		m_points_vector_thermo++;

	}
	else
	{
		int ctr = 0;
		while (ctr<DIM_VET_TERMO - 1)
		{
			m_vector_thermo[ctr][0] = m_vector_thermo[ctr + 1][0];
			m_vector_thermo[ctr][1] = m_vector_thermo[ctr + 1][1];
			ctr++;
		}
		m_vector_thermo[ctr][0] = time;
		m_vector_thermo[ctr][1] = delta_t;
	}

	int scala = m_scale_plot_thermo;
	int delta;
	(delta_t>0) ? delta = (delta_t*scala + .5) : delta = (delta_t*scala - .5);
	double y_min = ((delta - 1) / double(scala));
	double y_max = ((delta + 1) / double(scala));
	if (delta_t<m_grafico_termo->m_ymax && delta_t>m_grafico_termo->m_ymin)
	{
		y_min = m_grafico_termo->m_ymin;
		y_max = m_grafico_termo->m_ymax;

	}
	m_grafico_termo->coordinate(time - 3589, time + 11, y_min, y_max);
	m_grafico_termo->x_tick_change(600);
	m_grafico_termo->y_tick_change((2. / scala) / 5.);
	m_grafico_termo->plotta_frame();
	if (m_grafico_termo->punto_plottabile(time - 3588, 0) && m_grafico_termo->punto_plottabile(time + 10, 0))
	{
		m_grafico_termo->CambiaColore(0, 100, 0, 1);
		m_grafico_termo->plot_single_point(time - 3588, 0, TRUE);
		m_grafico_termo->plot_single_point(time + 10, 0, FALSE);
		m_grafico_termo->CambiaColore(200, 0, 0, 2);
	}



	m_grafico_termo->plot_vettore(m_vector_thermo, 0, m_points_vector_thermo - 1);


	return 0;
}


void CminervaDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	int old_scale = m_scale_plot_thermo;
	if (pNMUpDown->iDelta == 1 && m_scale_plot_thermo>1)
	{
		m_scale_plot_thermo /= 10;
	}
	else if (pNMUpDown->iDelta == -1 && m_scale_plot_thermo<10000)
	{
		m_scale_plot_thermo *= 10;
	}
	if (m_points_vector_thermo>2)
	{
		double x_min = m_grafico_termo->m_xmin;
		double x_max = m_grafico_termo->m_xmax;

		double delta = m_vector_thermo[m_points_vector_thermo - 1][1];
		int delta_int = 0;
		(delta>0) ? delta_int = (delta*m_scale_plot_thermo + .5) : delta_int = (delta*m_scale_plot_thermo - .5);
		double y_min = ((delta_int - 1) / double(m_scale_plot_thermo));
		double y_max = ((delta_int + 1) / double(m_scale_plot_thermo));

		m_grafico_termo->coordinate(x_min, x_max, y_min, y_max);
		m_grafico_termo->x_tick_change(600);
		m_grafico_termo->y_tick_change((2. / m_scale_plot_thermo) / 5.);
		m_grafico_termo->plotta_frame();
		if (m_grafico_termo->punto_plottabile(x_min, 0) && m_grafico_termo->punto_plottabile(x_max, 0))
		{
			m_grafico_termo->CambiaColore(0, 100, 0, 1);
			m_grafico_termo->plot_single_point(x_min, 0, TRUE);
			m_grafico_termo->plot_single_point(x_max, 0, FALSE);
			m_grafico_termo->CambiaColore(200, 0, 0, 2);
		}
		m_grafico_termo->plot_vettore(m_vector_thermo, 0, m_points_vector_thermo - 1);
	}
	*pResult = 0;
}


BOOL CminervaDlg::create_file_core()
{
	CTime  time_now = CTime::GetCurrentTime();

	CString now = m_directory + time_now.Format(L"%Y_%m_%d_%H_%M_%S_core.dat");
	m_file_core.Abort();
	BOOL whatsup = m_file_core.Open(now, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (m_file_core.m_hFile != CFile::hFileNull)
	{
		//AfxMessageBox(L"Core Log File Open", MB_OK | MB_ICONINFORMATION);
		//m_file_name_C.SetWindowText(finestra_file.GetFileName());
		CString aux = L" Seconds\t Resistance(Ohm)\t Sigma \t Trend (K/min) \n";
		m_file_core.WriteString(aux);
	}
	else
	{
		AfxMessageBox(L"Could not Open Core Log File");
		add_message(L" Could not Open COre Log File " + now);
	}

	return TRUE
;
}


bool CminervaDlg::save_core(long seconds, double resistance, double sigma, double trend)
{
	
		if (m_file_core.m_hFile != CFile::hFileNull)
	{
		CString aux;
		aux.Format(L" %6d \t%9.9g \t%7.5g \t%9.9g \n", seconds, resistance, sigma, trend);
		m_file_core.WriteString(aux);
	}
	// plotta_termo(secondi, delta); // questo lo faccio con Stefano; 
	// plot_thermostat(seconds, deltaT);
		double delta_t = (m_set_point - resistance) / (m_set_point*.04);
		plot_core(seconds, delta_t);

	return false;
}


void CminervaDlg::OnBnClickedButtonStopShieldInject()
{
	// This function interrupts current injection toward the four shield heating thermistors
	// 14 Gennaio 2014 ore 18
	// ATTENZIONE: verificare che questa funzione interrompa l'erogazione di corrente ai shield thermistors
	k_2400_onoff(FALSE, m_adr_k2400); // stop injecting current in the four thermistors heating the shield
	// CAREFUL here because you need to ensure that power is injected by PID into the shield depending on the status of k2400
}


int CminervaDlg::create_core_graph()
{
	if (m_grafico_core)
	{
		//m_grafico_termo->puntatoreCDC->DeleteDC();
		delete m_grafico_core;
	}
	m_grafico_core = new grafico_ver2;
	m_grafico_core->assegna(&m_graph_core_C);
	m_grafico_core->back_ground_color[0] = 240;
	m_grafico_core->back_ground_color[1] = 255;
	m_grafico_core->back_ground_color[2] = 240;
	m_grafico_core->riempi_tutto();
	m_grafico_core->sposta_label_x_axis(5);
	m_grafico_core->coordinate(0, 3600, -.001, +.001);
	m_grafico_core->cambia_colore_frame(0, 50, 0, 1);
	m_grafico_core->CambiaColore(200, 0, 0, 2);
	m_grafico_core->plotta_frame();


	return 0;
	return 0;
}


void CminervaDlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	int old_scale = m_scale_plot_core;
	if (pNMUpDown->iDelta == 1 && m_scale_plot_core>1)
	{
		m_scale_plot_core /= 10;
	}
	else if (pNMUpDown->iDelta == -1 && m_scale_plot_core<10000)
	{
		m_scale_plot_core *= 10;
	}
	if (m_points_vector_core>2)
	{
		double x_min = m_grafico_core->m_xmin;
		double x_max = m_grafico_core->m_xmax;

		double delta = m_vector_core[m_points_vector_core - 1][1];
		int delta_int = 0;
		(delta>0) ? delta_int = (delta*m_scale_plot_core + .5) : delta_int = (delta*m_scale_plot_core - .5);
		double y_min = ((delta_int - 1) / double(m_scale_plot_core));
		double y_max = ((delta_int + 1) / double(m_scale_plot_core));

		m_grafico_core->coordinate(x_min, x_max, y_min, y_max);
		m_grafico_core->x_tick_change(600);
		m_grafico_core->y_tick_change((2. / m_scale_plot_core) / 5.);
		m_grafico_core->plotta_frame();
		if (m_grafico_core->punto_plottabile(x_min, 0) && m_grafico_core->punto_plottabile(x_max, 0))
		{
			m_grafico_core->CambiaColore(0, 100, 0, 1);
			m_grafico_core->plot_single_point(x_min, 0, TRUE);
			m_grafico_core->plot_single_point(x_max, 0, FALSE);
			m_grafico_core->CambiaColore(200, 0, 0, 2);
		}
		m_grafico_core->plot_vettore(m_vector_core, 0, m_points_vector_core - 1);
	}


	*pResult = 0;
}


int CminervaDlg::plot_core(double time, double delta_t)
{
	double ymin = delta_t;
	double  ymax = delta_t;
	if (m_points_vector_core<DIM_VET_CORE)
	{
		m_vector_core[m_points_vector_core][0] = time;
		m_vector_core[m_points_vector_core][1] = delta_t;
		m_points_vector_core++;

	}
	else
	{
		int ctr = 0;
		while (ctr<DIM_VET_CORE - 1)
		{
			m_vector_core[ctr][0] = m_vector_core[ctr + 1][0];
			m_vector_core[ctr][1] = m_vector_core[ctr + 1][1];
			ctr++;
		}
		m_vector_core[ctr][0] = time;
		m_vector_core[ctr][1] = delta_t;
	}

	int scala = m_scale_plot_core;
	int delta;
	(delta_t>0) ? delta = (delta_t*scala + .5) : delta = (delta_t*scala - .5);
	double y_min = ((delta - 1) / double(scala));
	double y_max = ((delta + 1) / double(scala));
	if (delta_t<m_grafico_core->m_ymax && delta_t>m_grafico_core->m_ymin)
	{
		y_min = m_grafico_core->m_ymin;
		y_max = m_grafico_core->m_ymax;

	}
	m_grafico_core->coordinate(time - 3589, time + 11, y_min, y_max);
	m_grafico_core->x_tick_change(600);
	m_grafico_core->y_tick_change((2. / scala) / 5.);
	m_grafico_core->plotta_frame();
	if (m_grafico_core->punto_plottabile(time - 3588, 0) && m_grafico_core->punto_plottabile(time + 10, 0))
	{
		m_grafico_core->CambiaColore(0, 100, 200, 1);
		m_grafico_core->plot_single_point(time - 3588, 0, TRUE);
		m_grafico_core->plot_single_point(time + 10, 0, FALSE);
		m_grafico_core->CambiaColore(0, 0,200, 2);
	}



	m_grafico_core->plot_vettore(m_vector_core, 0, m_points_vector_core - 1);
	return 1;
}
