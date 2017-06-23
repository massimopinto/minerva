// fit_gauss_marioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fit_gauss_mario.h"
#include "fit_gauss_marioDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cfit_gauss_marioDlg dialog



Cfit_gauss_marioDlg::Cfit_gauss_marioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cfit_gauss_marioDlg::IDD, pParent)
	, m_nome_exp(_T(""))
	, m_x_min(0)
	, m_x_max(0)
	, m_y_min(0)
	, m_y_max(0)
	, m_a_gauss(0)
	, m_x0_gauss(0)
	, m_s_gauss(0)
	, m_dE_gauss(0)
	, m_varianza_min(0)
	, m_bkg_m(0)
	, m_bkg_c(0)
	, m_bkg_v(0)
	, m_bkg_tot(0)
	, m_ctr_start(0)
	, m_ctr_stop(0)
	, m_abort(FALSE)
	, m_testo(_T(""))
	, m_primo_file(false)
	, m_salvato(FALSE)
	, m_live_time(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cfit_gauss_marioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_nome_exp_C);
	DDX_Control(pDX, IDC_EDIT2, m_nome_MCNP_C);
	DDX_Control(pDX, IDC_STATIC_PLOT, m_area_grafico);
	DDX_Control(pDX, IDC_STATIC_COORD, m_static_messaggi_C);
	DDX_Text(pDX, IDC_EDIT3, m_x_min);
	DDX_Text(pDX, IDC_EDIT4, m_x_max);
	DDX_Text(pDX, IDC_EDIT5, m_y_min);
	DDX_Text(pDX, IDC_EDIT6, m_y_max);
	DDX_Text(pDX, IDC_EDIT7, m_a_gauss);
	DDX_Text(pDX, IDC_EDIT8, m_x0_gauss);
	DDX_Text(pDX, IDC_EDIT9, m_s_gauss);
	DDX_Control(pDX, IDC_LIST1, m_messaggi_C);
	DDX_Control(pDX, IDC_STATIC_VARIANZA, m_varianza_C);
	DDX_Control(pDX, IDC_EDIT7, m_finestra_a_C);
	DDX_Control(pDX, IDC_EDIT8, m_fimestra_x0_C);
	DDX_Control(pDX, IDC_EDIT9, m_fimestra_s_C);
	DDX_Control(pDX, IDC_CHECK1, m_a_check_C);
	DDX_Control(pDX, IDC_CHECK2, m_x0_check_C);
	DDX_Control(pDX, IDC_CHECK3, m_s_check_C);
	DDX_Control(pDX, IDC_EDIT10, m_de_finestra_C);
	DDX_Text(pDX, IDC_EDIT10, m_bkg_m);
	DDX_Control(pDX, IDC_CHECK4, m_dE_check_C);
	DDX_Control(pDX, IDC_STATIC_VARIANZA2, m_var_min_C);
	DDX_Control(pDX, IDC_CHECK5, m_check_convolution);
	DDX_Control(pDX, IDC_CHECK6, m_BLG_c_check_C);
	DDX_Control(pDX, IDC_EDIT11, m_bkg_c_C);
	DDX_Text(pDX, IDC_EDIT11, m_bkg_c);
	DDX_Text(pDX, IDC_EDIT12, m_bkg_tot);
	DDX_Control(pDX, IDC_EDIT12, m_bgk_tot_C);
	DDX_Control(pDX, IDC_STATIC_STEP, m_step_C);
	DDX_Control(pDX, IDC_EDIT13, m_int_tot_C);
	DDX_Control(pDX, IDC_EDIT14, m_delta_a_C);
	DDX_Control(pDX, IDC_EDIT15, m_delta_x0_C);
	DDX_Control(pDX, IDC_EDIT16, m_delta_s_C);
	DDX_Control(pDX, IDC_EDIT17, m_delta_c_C);
	DDX_Control(pDX, IDC_EDIT18, m_delta_bkgc_C);
}

BEGIN_MESSAGE_MAP(Cfit_gauss_marioDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN_EXP, OnBnClickedButtonOpenExp)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MCNP, OnBnClickedButtonOpenMcnp)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_REPLOT, OnBnClickedButtonReplot)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_GAUSS, OnBnClickedButtonShowGauss)
	ON_BN_CLICKED(IDC_BUTTON_GO, OnBnClickedButtonGo)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_CHECK5, OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM_ALL, OnBnClickedButtonZoomAll)
	ON_BN_CLICKED(IDC_BUTTON_ABORT, OnBnClickedButtonAbort)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_DATA, OnBnClickedButtonSaveData)
END_MESSAGE_MAP()


// Cfit_gauss_marioDlg message handlers

BOOL Cfit_gauss_marioDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
		m_plot.assegna(&m_area_grafico);
		m_plot.swap_CDC();
 m_salvato=TRUE;
	m_plot.cambia_colore_frame(0,150,0);
	m_plot.back_ground_color[0]=200;
	m_plot.back_ground_color[1]=200;
	m_plot.back_ground_color[2]=200;
	m_plot.sposta_asse_x(5);
	m_plot.riempi_tutto();
		   m_area_grafico.GetWindowPlacement(&m_grafico_place);
	m_grafico_rect=m_grafico_place.rcNormalPosition;
	m_vertice_grafico.x=m_grafico_place.rcNormalPosition.left;
	m_vertice_grafico.y=m_grafico_place.rcNormalPosition.top;
	//m_grafico_on=FALSE;
	m_init_drag=FALSE;
    m_grafico_on=FALSE;
	m_punti_compa=0;
	m_punti_exp=0;
	m_punti_MCNP=0;
    m_a_gauss=20000;
	m_x0_gauss=4500;
	m_bkg_m=0;
	m_bkg_c=0;
	m_s_gauss=50;
	m_gauss=NULL;
	m_conv=NULL;
	 m_a_check_C.SetCheck(1);
	 m_x0_check_C.SetCheck(1);
	 m_s_check_C.SetCheck(1);
	 m_dE_check_C.SetCheck(1);
	 m_BLG_c_check_C.SetCheck(1);
	 m_check_convolution.SetCheck(1);
	UpdateData(FALSE);
	m_primo_file=TRUE;
	m_file_out.Open("gauss_fit.txt",CFile::modeCreate
       | CFile::modeWrite | CFile::typeText );
	m_testo.Format("File \t area_exp \t Area_Gauss \t FWHM \t Center \t%BKG_Count/channel \t Varianza \n");
	m_file_out.WriteString(m_testo);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cfit_gauss_marioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cfit_gauss_marioDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cfit_gauss_marioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cfit_gauss_marioDlg::OnBnClickedButtonOpenExp()
{
	// TODO: Add your control notification handler code here
	m_varianza_min=-1;
	if (!m_salvato)
	{
		BOOL response = AfxMessageBox("Vuoi salvare il risultato?",MB_YESNO|MB_ICONQUESTION  );
		if (response==IDYES) OnBnClickedButtonSaveData();   
	}
	open_exp();
}

int Cfit_gauss_marioDlg::open_exp(void)
{
	m_salvato=FALSE;
	CFileDialog finestra_file(TRUE,"*.dat",NULL,NULL,"Data Files (*.dat)|*.dat|Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||"); 
	if (IDOK!=finestra_file.DoModal()) return 0;
	CString nome,path;
	m_nome_exp=finestra_file.GetFileName();
	path=finestra_file.GetPathName();
	
	m_nome_exp_C.SetWindowText(m_nome_exp);
	  m_file_dati.Abort();
	if (!m_file_dati.Open(path,CFile::modeRead))
	{
		AfxMessageBox(" Problemi Nell'apertura del File!",MB_ICONSTOP |MB_OK   )  ;
		return 0;
	}
 	load_exp();
		m_nome_exp.Format("%s  %g",m_nome_exp,m_live_time);
	
	m_nome_exp_C.SetWindowText(m_nome_exp);

 	return 0;
}

void Cfit_gauss_marioDlg::OnBnClickedButtonOpenMcnp()
{
	// TODO: Add your control notification handler code here
	open_MCNP();
}

int Cfit_gauss_marioDlg::open_MCNP(void)
{
	CFileDialog finestra_file(TRUE,"*.dat",NULL,NULL,"Data Files (*.dat)|*.dat|Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||"); 
	if (IDOK!=finestra_file.DoModal()) return 0;
	CString nome,path;
	m_nome_MCNP=finestra_file.GetFileName();
	path=finestra_file.GetPathName();
	m_nome_MCNP_C.SetWindowText(m_nome_MCNP);
	  m_file_MCNP.Abort();
	if (!m_file_MCNP
		.Open(path,CFile::modeRead))
	{
		AfxMessageBox(" Problemi Nell'apertura del File!",MB_ICONSTOP |MB_OK   )  ;
		return 0;
	}
	load_MCNP();
 	return 0;
	 
}

int Cfit_gauss_marioDlg::load_exp(void)
{
	m_punti_exp=0;
	char *puntatore=NULL,*puntatore2=NULL;

	CString text;
	while (m_file_dati.ReadString(text) && m_punti_exp<10000)
	{
		if (text.GetLength()>1)
		{
			int pos=text.Find("=");
		if (pos>0)
		{
			m_live_time = strtod(text.GetBuffer()+pos+1,&puntatore);
			
		}
		else 
		{
		m_exp[m_punti_exp][0]=strtod(text.GetBuffer(),&puntatore);
		m_exp[m_punti_exp][1]=strtod(puntatore,&puntatore2);
		if (m_punti_exp==0)
		{
			m_exp_min=m_exp[m_punti_exp][1];
			m_exp_max=m_exp[m_punti_exp][1];
		}
		else
		{
			m_exp_min=min(m_exp[m_punti_exp][1],m_exp_min);
			m_exp_max=max(m_exp[m_punti_exp][1],m_exp_max);

		}
		m_punti_exp++;
		}
		}
	}
	m_grafico_on=TRUE;
	 
 if (m_primo_file)
 {
	 m_x_min=m_exp[0][0];
	 m_x_max=m_exp[m_punti_exp-1][0];
	 m_y_min=m_exp_min;
	 m_y_max=m_exp_max;
	  
	 m_x_min_all=m_x_min;
	  m_x_max_all=m_x_max;
		 m_y_min_all=m_y_min;
		 m_y_max_all=m_y_max;
     UpdateData(FALSE);
 }
 m_primo_file=FALSE;
	 compa();
	replot();
	 
	
	return 0;
}

int Cfit_gauss_marioDlg::plotta_point(void)
{

	m_plot.plotta_frame();
	m_plot.CambiaColore(250,0,0);
	m_plot.caption(m_nome_exp,90,90,TRUE);
	m_plot.plot_vettore(m_exp,0,m_punti_exp-1);
	
int	 ctr=m_ctr_start;
if (m_gauss!=NULL)
{
	m_plot.CambiaColore(0,0,255);
	BOOL primo=TRUE;
		while (ctr<=m_ctr_stop)
		{
			m_plot.plot_single_point(m_exp[ctr][0], m_gauss[ctr] ,primo);
 		   primo=FALSE;
          ctr++;
		}
}
		if (m_punti_compa>2)
	{
		m_plot.CambiaColore(0,200,250);
           	m_plot.caption("Interpolation",90,75,TRUE);
		  ctr=0;
		while (ctr<m_punti_compa)
		{
		  m_plot.plotta_punto(m_compa[ctr][0],m_compa[ctr][1],2);
          ctr++;
		}
		m_plot.CambiaColore(0,180,0);
           	m_plot.caption("Interpolation",90,75,TRUE);
		
			 ctr=0;
			 m_plot.CambiaColore(0,0,255);
		while (ctr<m_punti_compa)
		{
 		  m_plot.plotta_punto(m_compa[ctr][0],m_conv[ctr],2);
          ctr++;
		}


	}
	plot_bkG();
	m_plot.show_compatible_CDC();
	return 0;
}

void Cfit_gauss_marioDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
   CString testo;
   m_cursore_on_grafico=m_grafico_rect.PtInRect(point);
   if (m_cursore_on_grafico&&m_grafico_on)
   {
	   m_point=point;
       calcola_coordinate(point);
	   CString testo;
	   testo.Format(" x=%10.8g y=%10.8g ",m_coordinate[0],m_coordinate[1]);
       m_static_messaggi_C.SetWindowText(testo);

   }
   if (m_init_drag&&m_cursore_on_grafico)
   {
	  selezione(point);
   }
	CDialog::OnMouseMove(nFlags, point);
}

int Cfit_gauss_marioDlg::calcola_coordinate(CPoint punto)
{
		punto-=m_vertice_grafico;
	//punto.x-=m_grafico_place.rcNormalPosition.left;
	//punto.y-=m_grafico_place.rcNormalPosition.top;
	 m_plot.converti_punto_in_xy(punto,m_coordinate,m_coordinate+1);
		 

	return 0;
}

void Cfit_gauss_marioDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
if (m_cursore_on_grafico&&m_grafico_on)
	{
		m_init_drag=TRUE;
		m_start_drag=TRUE;
		m_init_drag_p1=point-m_vertice_grafico;
	}
	CDialog::OnLButtonDown(nFlags, point);
}

int Cfit_gauss_marioDlg::selezione(CPoint punto)
{
	    punto-=m_vertice_grafico;
     CRect newRect(m_init_drag_p1,punto);
    static CRect old;
    CSize size(1,1);
	if (m_start_drag)
	{
		m_plot.puntatoreCDC->DrawDragRect(newRect,size,NULL,size);
       m_start_drag=FALSE;
	   m_track_drag=TRUE;
	}
	else if (!m_init_drag)
	{
			m_plot.puntatoreCDC->DrawDragRect(newRect,size,old,size);
	}
	else
	{
		m_plot.puntatoreCDC->DrawDragRect(newRect,size,old,size);

	}
	  old=newRect;
	return 0;
}

void Cfit_gauss_marioDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
     m_init_drag=FALSE;
	 if (m_track_drag)
	 {
		selezione( m_init_drag_p1+m_vertice_grafico);
		m_track_drag=FALSE;
		rescale(m_init_drag_p1+m_vertice_grafico,point);
	 }

	CDialog::OnLButtonUp(nFlags, point);
}

int Cfit_gauss_marioDlg::rescale(CPoint topleft, CPoint bottonright)
{
		if ((bottonright.x - topleft.x)<5 || (bottonright.y - topleft.y)<5) return 0;
    double top[2];
	calcola_coordinate(topleft);
	top[0]=m_coordinate[0];
	top[1]=m_coordinate[1];

	 double botton[2];
	 calcola_coordinate(bottonright);
	 botton[0]=m_coordinate[0];
	  botton[1]=m_coordinate[1];
	 m_x_min=top[0];
	 m_x_max=botton[0];
	 m_y_min=botton[1];
	 m_y_max=top[1];
  //   UpdateData(FALSE);
	 replot();
	return 0;
}

void Cfit_gauss_marioDlg::OnBnClickedButtonReplot()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	replot();
}

int Cfit_gauss_marioDlg::replot(void)
{
	UpdateData(FALSE);
		m_plot.coordinate(m_x_min, m_x_max,m_y_min,m_y_max);
 //   m_plot.coordinate(top[0],botton[0],botton[1],top[1]);
		m_ctr_start=-1;
		m_ctr_stop=-1;
	int ctr=0;
	while (ctr<m_punti_exp && m_exp[ctr][0]<=m_x_max)
	{
		if (m_ctr_start<0 && m_exp[ctr][0]>=m_x_min) m_ctr_start=ctr;
		if (m_ctr_stop<0 && m_exp[ctr][0]>=m_x_max) m_ctr_stop=ctr;
		ctr++;
	}


		 
   plotta_point();

	return 0;
}

int Cfit_gauss_marioDlg::load_MCNP(void)
{	m_punti_MCNP=0;
	char *puntatore=NULL,*puntatore2=NULL;
    double max=0;
	CString text;
	while (m_file_MCNP.ReadString(text) && m_punti_MCNP<2000)
	{
		if (text.GetLength()>0)
		{
		m_MCNP[m_punti_MCNP][0]=strtod(text.GetBuffer(),&puntatore);
		m_MCNP[m_punti_MCNP][1]=strtod(puntatore,&puntatore2);
		if (m_MCNP[m_punti_MCNP][1]>max)
		{
			max=m_MCNP[m_punti_MCNP][1];
            m_x0_gauss = m_MCNP[m_punti_MCNP][0];
		}
		m_punti_MCNP++;
		}
	}
	compa();
	if (m_grafico_on)
	{
		m_x_min=m_MCNP[0][0];
		m_x_max=m_MCNP[m_punti_MCNP-1][0];
		m_y_min=-max*.01;
		m_y_max=max*2;
		replot();
	}
	UpdateData(FALSE);
	 
	return 0;
}

int Cfit_gauss_marioDlg::compa(void)
{
	if (!(m_punti_exp && m_punti_MCNP)) return 0;
	double *MCNP_shifted  = new double[m_punti_MCNP];
	int ctr=1,ctr1=0;
	while (ctr1<m_punti_MCNP)
	{
     MCNP_shifted[ctr1]=m_MCNP[ctr1][0]-m_dE_gauss;
	 ctr1++;
     }
	  ctr1=0;
    while (ctr<m_punti_exp)
	{
		if (MCNP_shifted[0]<=(m_exp[ctr][0])) 
		{
			m_fit_start=ctr;
			break;

		}
		ctr++;
	}
  m_fit_end=m_punti_exp-1;
	while (ctr<m_punti_exp)
	{
		if (MCNP_shifted[m_punti_MCNP-1]<=(m_exp[ctr][0])) 
		{
			m_fit_end=ctr;
			break;

		}
		ctr++;
	}

	 m_punti_compa=0;
	 ctr=m_fit_start;
	 m_punti_compa=0;
	 while (ctr<=m_fit_end)
	 {
		 m_compa[m_punti_compa][0]=m_exp[ctr][0];
           m_compa[m_punti_compa][1]=interpola(ctr,!m_punti_compa,MCNP_shifted);
		   ctr++;
		   m_punti_compa++;
	 }
	 calcola_gauss();
	 calcola_conv();
	 calcola_varianza();
    
		  delete [] MCNP_shifted;
	return 0;
}

double Cfit_gauss_marioDlg::interpola(int ctr,BOOL inizializzo, double* MCNP_shifted )
{
	static ctr1;
	if (inizializzo) ctr1=0;
    while (ctr1<m_punti_MCNP-1)
	{
	if (MCNP_shifted[ctr1]>(m_exp[ctr][0])) 
		{
			
			break;

		}
		ctr1++;
	}
	

	double fit = m_MCNP[ctr1-1][1]+ (m_exp[ctr][0]-MCNP_shifted[ctr1-1])*(m_MCNP[ctr1][1]-m_MCNP[ctr1-1][1])/(MCNP_shifted[ctr1]-MCNP_shifted[ctr1-1]);
	return fit;
}

int Cfit_gauss_marioDlg::calcola_gauss(void)
{
	double bkg_tot=0;
	m_bkg_tot=0;
	if (m_gauss)
	{
		delete [] m_gauss;
	}
	m_gauss = new double[m_punti_exp];
	int ctr=m_ctr_start;
	 double costante=0.3989422804/m_s_gauss,bkg=0;
	while (ctr<=m_ctr_stop)
	{
	      bkg=m_bkg_m*(m_exp[ctr][0]-m_exp[m_ctr_start][0])+m_bkg_c;
		
		m_gauss[ctr]=bkg+ m_a_gauss*costante*exp(  -0.5*pow(((m_exp[ctr][0]-m_x0_gauss)/m_s_gauss),2));
		ctr++;
		bkg_tot+=bkg;
	}
	m_bkg_tot=bkg_tot;
	//UpdateData(TRUE);
	return 0;
}

void Cfit_gauss_marioDlg::OnBnClickedButtonShowGauss()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	compa();
	calcola_gauss();
	calcola_conv();
	calcola_varianza();
	replot();
}

int Cfit_gauss_marioDlg::calcola_conv(void)
{
if (m_conv)
	{
		delete [] m_conv;
	}
	m_conv = new double[m_punti_exp];
	int ctr=m_ctr_start;
	if (TRUE)
	{
		while (ctr<=m_ctr_stop)
			{
		m_conv[ctr]= m_gauss[ctr];
		ctr++;
			}
	}
	else
	{
	 

	}
	return 0;
	 
}

double Cfit_gauss_marioDlg::calcola_varianza(void)
{
	int ctr=m_ctr_start,ctr_validi=0;
	double varianza=0,y,differenza;
	m_fit_start=0;
	while (ctr<=m_ctr_stop)
	{
		if (m_exp[m_fit_start+ctr][0]>=m_plot.m_xmin 
			&& m_exp[m_fit_start+ctr][0]<=m_plot.m_xmax)
		{
		y = m_conv[ctr];
		differenza = (m_exp[m_fit_start+ctr][1]-y);
		varianza +=pow(differenza,2);
		ctr_validi++;
		}
		ctr++;
	}
	varianza = ((varianza)/(ctr_validi-3));
	CString testo;
	testo.Format("%8.6g",varianza);
	m_varianza_C.SetWindowText(testo);
	m_varianza_C.RedrawWindow();
	if ((varianza<m_varianza_min) || (m_varianza_min<=0))
	{
		testo.Format("%8.7g, %8.7g",varianza,(varianza-m_varianza_min)/m_varianza_min);
		m_varianza_min=varianza;
		m_var_min_C.SetWindowText(testo);

	}
	return (varianza);
	return 0;
}

void Cfit_gauss_marioDlg::OnBnClickedButtonGo()
{
	// TODO: Add your control notification handler code here
	OnBnClickedButtonShowGauss();
	UpdateData(TRUE);
	m_abort=FALSE;
			m_testo.Format("%8.7g", m_varianza_min);
		 
		m_var_min_C.SetWindowText(m_testo);
	start_fit();
}

int Cfit_gauss_marioDlg::start_fit(void)
{
	int cicli=0;
	double varianza_old=calcola_varianza(),varianza_new=0; 
		while(cicli<10 && varianza_old>varianza_new)
		{
            varianza_old=calcola_varianza();
			if (m_a_check_C.GetCheck()==BST_CHECKED) minimizza_a();
			if (m_x0_check_C.GetCheck()==BST_CHECKED) minimizza_x0();
			if (m_s_check_C.GetCheck()==BST_CHECKED) minimizza_s();
			if (m_dE_check_C.GetCheck()==BST_CHECKED) minimizza_dE();
			if (m_BLG_c_check_C.GetCheck()==BST_CHECKED) minimizza_c();

			cicli++;
			compa();
			replot();
            varianza_new=calcola_varianza();
             UpdateData(FALSE);
		}
	return 0;
}

int Cfit_gauss_marioDlg::minimizza_a(void)
{
	double errore=0,varianza_old;
	m_finestra_a_C.EnableWindow(FALSE);
	double m_a_gauss_old = m_a_gauss,m_gauss_start=m_a_gauss;
	int  iterazioni=0;
	 CString testo;
	double step = fabs(m_a_gauss*0.01)+0.0001, varianza_new=calcola_varianza();
	while (iterazioni<10 && step>fabs(m_a_gauss*0.0001))
	{

		testo.Format("%8.6g",m_a_gauss);
		m_finestra_a_C.SetWindowText(testo);
		m_finestra_a_C.RedrawWindow();
	
	do {	
		m_testo.Format("%8.6g", step);
		m_step_C.SetWindowText(m_testo);
		m_step_C.RedrawWindow();
		 varianza_old=varianza_new;
		m_a_gauss_old = m_a_gauss;
		m_a_gauss +=step;
		calcola_gauss();
		calcola_conv();
		replot();
		varianza_new= calcola_varianza();
		 step*=1.1;
		iterazioni++;
	}
	while (varianza_old>varianza_new);

		m_a_gauss = m_a_gauss_old;
		 varianza_new = varianza_old;

	do {
		 varianza_old=varianza_new;
		m_a_gauss_old = m_a_gauss;
	m_a_gauss -=step;
			calcola_gauss();
		calcola_conv();
          replot();
	varianza_new= calcola_varianza();
	iterazioni++;
			 step*=1.1; 

	}
	while (varianza_old>varianza_new);

		m_a_gauss = m_a_gauss_old;
		 varianza_new=varianza_old;
		if (iterazioni<10)
		{
			iterazioni=0;
			step/=10;
		}

	}
    m_finestra_a_C.EnableWindow(TRUE);
	m_finestra_a_C.RedrawWindow();
		testo.Format("%8.6g",m_a_gauss);
		m_finestra_a_C.SetWindowText(testo);
		m_finestra_a_C.RedrawWindow();
        testo.Format("%8.6g",m_a_gauss-m_gauss_start);
		m_delta_a_C.SetWindowText(testo);
		m_delta_a_C.RedrawWindow();
	return 0;
}

int Cfit_gauss_marioDlg::minimizza_x0(void)
{
	double errore=0,varianza_old;
	m_fimestra_x0_C.EnableWindow(FALSE);
	double m_x0_gauss_old = m_x0_gauss,m_x0_gauss_start=m_x0_gauss;
	int  iterazioni=0;
	 CString testo;
	double step = fabs(m_x0_gauss*0.01)+0.00001, varianza_new=calcola_varianza();
	while (iterazioni<10 && step>fabs(m_x0_gauss*0.0001))
	{
		testo.Format("%8.6g",m_x0_gauss);
		m_fimestra_x0_C.SetWindowText(testo);
		m_fimestra_x0_C.RedrawWindow();

	do {				m_testo.Format("%8.6g", step);
		m_step_C.SetWindowText(m_testo);
		m_step_C.RedrawWindow();
		 varianza_old=varianza_new;
		m_x0_gauss_old = m_x0_gauss;
		m_x0_gauss +=step;
				calcola_gauss();
		calcola_conv();
         replot();
		varianza_new= calcola_varianza();
		 step*=1.1;
		iterazioni++;
	}
	while (varianza_old>varianza_new);

		m_x0_gauss = m_x0_gauss_old;
		 varianza_new = varianza_old;

	do {
		 varianza_old=varianza_new;
		m_x0_gauss_old = m_x0_gauss;
	m_x0_gauss -=step;
			calcola_gauss();
		calcola_conv();
    replot();
	varianza_new= calcola_varianza();
	iterazioni++;
			 
 step*=1.1;
	}
	while (varianza_old>varianza_new);

		m_x0_gauss = m_x0_gauss_old;
		 varianza_new=varianza_old;
		if (iterazioni<10)
		{
			iterazioni=0;
			step/=10;
		}

	}
    m_fimestra_x0_C.EnableWindow(TRUE);
	m_fimestra_x0_C.RedrawWindow();
	testo.Format("%8.6g",m_x0_gauss);
		m_fimestra_x0_C.SetWindowText(testo);
		m_fimestra_x0_C.RedrawWindow();
		testo.Format("%8.6g",m_x0_gauss-m_x0_gauss_start);
		m_delta_x0_C.SetWindowText(testo);
        m_delta_x0_C.RedrawWindow();
	return 0;
}

int Cfit_gauss_marioDlg::minimizza_s(void)
{
		double errore=0,varianza_old;
	m_fimestra_s_C.EnableWindow(FALSE);
	double m_s_gauss_old = m_s_gauss,m_s_gauss_start=m_s_gauss;
	int  iterazioni=0;
	 CString testo;
	double step = fabs(m_s_gauss*0.01)+0.0001, varianza_new=calcola_varianza();
	while (iterazioni<10 && step>fabs(m_s_gauss*0.0001))
	{
		testo.Format("%8.6g",m_s_gauss);
		m_fimestra_s_C.SetWindowText(testo);
		m_fimestra_s_C.RedrawWindow();

	do {				m_testo.Format("%8.6g", step);
		m_step_C.SetWindowText(m_testo);
		m_step_C.RedrawWindow();
		 varianza_old=varianza_new;
		m_s_gauss_old = m_s_gauss;
		m_s_gauss +=step;
		calcola_gauss();
		calcola_conv();
		replot();
		varianza_new= calcola_varianza();
		 step*=1.1;
		iterazioni++;
	}
	while (varianza_old>varianza_new);

		m_s_gauss = m_s_gauss_old;
		 varianza_new = varianza_old;

	do {
		 varianza_old=varianza_new;
		m_s_gauss_old = m_s_gauss;
	m_s_gauss -=step;
		calcola_gauss();
		calcola_conv();
		replot();
	varianza_new= calcola_varianza();
	iterazioni++;
			  step*=1.1;

	}
	while (varianza_old>varianza_new);

		m_s_gauss = m_s_gauss_old;
		 varianza_new=varianza_old;
		if (iterazioni<10)
		{
			iterazioni=0;
			step/=10;
		}

	}
	testo.Format("%8.6g",m_s_gauss);
		m_fimestra_s_C.SetWindowText(testo);
		m_fimestra_s_C.RedrawWindow();
     m_fimestra_s_C.EnableWindow(TRUE);
	 m_fimestra_s_C.RedrawWindow();
	 testo.Format("%8.6g",m_s_gauss-m_s_gauss_start);
	 m_delta_s_C.SetWindowText(testo);
       m_delta_s_C.RedrawWindow();
	return 0;
}

int Cfit_gauss_marioDlg::minimizza_dE(void)
{
		double errore=0,varianza_old;
	m_de_finestra_C.EnableWindow(FALSE);
	double m_bkg_m_old = m_bkg_m,m_bkg_m_start=m_bkg_m;
	int  iterazioni=0;
	 CString testo;
	double step = fabs(m_bkg_m*0.1)+0.0001, varianza_new=calcola_varianza();
	while (iterazioni<10 && step>fabs(m_bkg_m*0.0001))
	{
		testo.Format("%8.6g",m_bkg_m);
		m_de_finestra_C.SetWindowText(testo);
		m_de_finestra_C.RedrawWindow();

	do {				m_testo.Format("%8.6g", step);
		m_step_C.SetWindowText(m_testo);
		m_step_C.RedrawWindow();
		 varianza_old=varianza_new;
		m_bkg_m_old = m_bkg_m;
		m_bkg_m +=step;
		calcola_gauss();
		calcola_conv();
		replot();
		varianza_new= calcola_varianza();
		 step*=1.1;
		iterazioni++;
	}
	while (varianza_old>varianza_new);

		  m_bkg_m = m_bkg_m_old ;
		 varianza_new = varianza_old;

	do {
		 varianza_old=varianza_new;
		m_bkg_m_old = m_bkg_m;
	m_bkg_m -=step;
		 calcola_gauss();
		calcola_conv();
		replot();
	varianza_new= calcola_varianza();
 step*=1.1;
	iterazioni++;
			 

	}
	while (varianza_old>varianza_new);

		m_bkg_m = m_bkg_m_old;
		 varianza_new=varianza_old;
		if (iterazioni<10)
		{
			iterazioni=0;
			step/=10;
		}

	}
    m_de_finestra_C.EnableWindow(TRUE);
		m_de_finestra_C.RedrawWindow();
		testo.Format("%8.6g",m_bkg_m);
		m_de_finestra_C.SetWindowText(testo);
		m_de_finestra_C.RedrawWindow();
		testo.Format("%8.6g",m_bkg_m-m_bkg_m_start);
		m_delta_bkgc_C.SetWindowText(testo);
        m_delta_bkgc_C.RedrawWindow();
	return 0;
}

void Cfit_gauss_marioDlg::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
CFileDialog finestra_file(FALSE,"*.dat",NULL,NULL,"Data Files (*.dat)|*.dat|Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||"); 
	if (IDOK!=finestra_file.DoModal()) return ;
	CString nome,path;
	nome=finestra_file.GetFileName();
	path=finestra_file.GetPathName();
	 
	    CStdioFile file;
		if (!file.Open(path,CFile::modeWrite|CFile::modeCreate))
	{
		AfxMessageBox(" Problemi Nell'apertura del File!",MB_ICONSTOP |MB_OK   )  ;
		return ;
	}
	int ctr=0;
	CString testo;
	testo.Format("dati fit dE=%g, X0=%g, a=%g, s=%g varianza=%g\n",m_dE_gauss,m_x0_gauss,m_a_gauss,m_s_gauss,calcola_varianza());
	file.WriteString(testo);
    testo.Format("Eneg.     exp     fit  MCNP(X) MCNP(Y)  gauss \n");
    file.WriteString(testo);

   while (ctr<m_punti_compa)
	{
		testo.Format(" %g   %g    %g    %g    %g   %g \n",m_exp[m_fit_start+ctr][0],m_exp[m_fit_start+ctr][1],m_conv[ctr],m_compa[ctr][0]+m_dE_gauss, m_compa[ctr][1], m_gauss[ctr]);
		file.WriteString(testo);
		ctr++;
 
	}

   file.Close();
}

double Cfit_gauss_marioDlg::conv_gauss(int punta)
{
         double gaussiana=0;
		 double costante=0.3989422804/m_s_gauss;
		 double integratore=0;
		 int ctr=1;
		 while (ctr<m_punti_compa)
		 {
        gaussiana= m_a_gauss*costante*exp(  -0.5*pow(((m_compa[ctr][0]-m_compa[punta][0])/m_s_gauss),2));
        integratore+=gaussiana*m_compa[ctr][1]*(m_compa[ctr][0]-m_compa[ctr-1][0]);
		ctr++;
		 }
		
		 

	return integratore;
}

void Cfit_gauss_marioDlg::OnBnClickedCheck5()
{
	// TODO: Add your control notification handler code here
	BOOL stato=m_check_convolution.GetCheck();
	if (stato)
	{
		m_fimestra_x0_C.ShowWindow(FALSE);
		m_x0_check_C.SetCheck(0);
		m_x0_check_C.ShowWindow(FALSE);
	}
	else
	{
		m_fimestra_x0_C.ShowWindow(TRUE);
		 
		m_x0_check_C.ShowWindow(TRUE);


	}
}

void Cfit_gauss_marioDlg::OnBnClickedButtonZoomAll()
{
	// TODO: Add your control notification handler code here
		 m_x_min=m_x_min_all;
	  m_x_max=m_x_max_all;
		 m_y_min=m_y_min_all;
		 m_y_max=m_y_max_all;
		 replot();
 
}

int Cfit_gauss_marioDlg::minimizza_c(void)
{
		double errore=0,varianza_old;
	m_bkg_c_C.EnableWindow(FALSE);
	double m_bkg_c_old = m_bkg_c,m_bkg_c_start=m_bkg_c;
	int  iterazioni=0;
	 CString testo;
	double step = fabs(m_bkg_c*0.1)+0.0001, varianza_new=calcola_varianza();
	while (iterazioni<10 && step>fabs(m_bkg_c*0.0001))
	{
		testo.Format("%8.6g",m_bkg_c);
		m_bkg_c_C.SetWindowText(testo);
		m_bkg_c_C.RedrawWindow();

	do {
		 varianza_old=varianza_new;
		 				m_testo.Format("%8.6g", step);
		m_step_C.SetWindowText(m_testo);
		m_step_C.RedrawWindow();
		m_bkg_c_old = m_bkg_c;
		m_bkg_c +=step;
		calcola_gauss();
		calcola_conv();
		replot();
		varianza_new= calcola_varianza();
		 step*=1.1;
		iterazioni++;
	}
	while (varianza_old>varianza_new);

		  m_bkg_c = m_bkg_c_old ;
		 varianza_new = varianza_old;

	do {
		 varianza_old=varianza_new;
		m_bkg_c_old = m_bkg_c;
	m_bkg_c -=step;
		 calcola_gauss();
		calcola_conv();
		replot();
	varianza_new= calcola_varianza();
       step*=1.1;
	iterazioni++;
	}
while (varianza_old>varianza_new);

		m_bkg_c = m_bkg_c_old;
		 varianza_new=varianza_old;
		if (iterazioni<10)
		{
			iterazioni=0;
			step/=10;
		}

	}
    m_bkg_c_C.EnableWindow(TRUE);
		m_bkg_c_C.RedrawWindow();
		testo.Format("%8.6g",m_bkg_c);
		m_bkg_c_C.SetWindowText(testo);
		m_bkg_c_C.RedrawWindow();
    testo.Format("%8.6g",m_bkg_c-m_bkg_c_start);
		m_delta_c_C.SetWindowText(testo);
		m_delta_c_C.RedrawWindow();
	return 0;
}

void Cfit_gauss_marioDlg::OnBnClickedButtonAbort()
{
	// TODO: Add your control notification handler code here
	m_abort=TRUE;
}

int Cfit_gauss_marioDlg::plot_bkG(void)
{
	int ctr=m_ctr_start,ctr2=0;
	double y=0,x=0;
	double  (*bkg)[2];
	  bkg =  new (double[m_ctr_stop-m_ctr_start+1][2]);
	   m_integrale_BKG=0;
	   m_integrale_exp=0;
	while (ctr<=m_ctr_stop)
	{
		bkg[ctr2][0]=m_exp[ctr][0];
		bkg[ctr2][1]=m_bkg_m*(m_exp[ctr][0]-m_exp[m_ctr_start][0])+m_bkg_c;
		ctr++;
       m_integrale_BKG+=bkg[ctr2][1];
       m_integrale_exp+=(m_exp[ctr][1]-bkg[ctr2][1]);
		ctr2++;
	}
	m_plot.CambiaColore(150,150,200,1);
	m_plot.plot_vettore(bkg,0,ctr2-1);
	CString m_testo;
	m_testo.Format("%6.5f",m_integrale_BKG);
	m_bgk_tot_C.SetWindowText(m_testo);
	m_bgk_tot_C.RedrawWindow();
		m_testo.Format("%6.5f",m_integrale_exp);
	m_int_tot_C.SetWindowText(m_testo);
	m_int_tot_C.RedrawWindow();
	return 0;
}

void Cfit_gauss_marioDlg::OnBnClickedButtonSaveData()
{
	// TODO: Add your control notification handler code here
  m_testo.Format("%s \t %7.5f \t %7.5f \t %7.5f \t%7.5f \t%7.5f \t%7.5f \n",m_nome_exp,m_integrale_exp,
	  m_a_gauss,2.3548*m_s_gauss,m_x0_gauss,m_integrale_BKG/(m_ctr_stop-m_ctr_start+1),m_varianza_min);
  m_file_out.WriteString(m_testo);
  m_salvato =TRUE;

}
