  
// minervaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "minervaRx.h"
#include "minervaRxDlg.h"
#include "afxdialogex.h"
#include <stdlib.h> 
#include <math.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CminervaRxDlg dialog


CminervaRxDlg::CminervaRxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CminervaRxDlg::IDD, pParent)
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
	, m_anti_block_aux(0)
	, m_old_thermo_temperature(0)
	, m_p_CDC(NULL)
	, m_derivative_power(0)
	, m_I_PID(0)
	, m_do_noting(0)
	, m_ETA_target(0)
	, m_jacket_current_calibration(0)
	, m_jacket_calibration_seconds(0)
	, m_timer_jacket(0)
	, m_joule_jacket(0)
	, m_synchronize(FALSE)
	, m_thermostat_reading_interval(0)
	, m_thermistor_ID(0)
	
	, m_radio_thermo(FALSE)
	, m_thermo_CH_aux(0)
//	, m_skip_points_aux(_T(""))
	, m_mean_aux(0)
	, m_skip_points_aux(0)
	, m_aux_reading_interval(0)
	, m_red_light_thermostat(FALSE)
	, m_mean_resistance_aux(0)
	, busy_7001(_T(""))
	, m_thermo_freeze(FALSE)
	, m_power_thermostat(0)
	, m_old_time(0)
	, m_seconds_t_zero(0)
	, m_elements_into_average_thermospeed(0)
	, m_seconds_continuous_thermostat(0)
	, m_average_thermospeed(0)
	, m_CoreHeatingMode(FALSE)

	, m_electrical_calibration_duration_option(0)
	, capacitor_value_numeric(0)
	, m_run_countdown(0)
	, m_partial_GPIB_configuration(TRUE)
	, VMbegin(0)
	, attenuation_coeff(0)
	, QMON(0)
	, IMON(0)
	, Ktpm(0)
	, Katt(0)
	, m_run_type(0)
{
		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CminervaRxDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Text(pDX, IDC_EDIT24, m_ETA_target);
	DDX_Text(pDX, IDC_EDIT25, m_jacket_current_calibration);
	DDX_Text(pDX, IDC_EDIT26, m_jacket_calibration_seconds);
	DDX_Control(pDX, IDC_EDIT30, m_volt_jacket_C);
	DDX_Control(pDX, IDC_EDIT27, m_microwatt_jacket_C);
	DDX_Control(pDX, IDC_EDIT28, m_joule_jacket_C);
	DDX_Control(pDX, IDC_EDIT29, m_seconds_jacket_C);
	DDX_Check(pDX, IDC_CHECK1, m_synchronize);
	DDX_Text(pDX, IDC_EDIT31, m_thermostat_reading_interval);
	DDX_Control(pDX, IDC_CHECK2, m_CH1_C);
	DDX_Control(pDX, IDC_CHECK3, m_CH2_C);
	DDX_Control(pDX, IDC_CHECK4, m_CH3_C);
	DDX_Control(pDX, IDC_CHECK5, m_CH4_C);
	DDX_Control(pDX, IDC_CHECK6, m_CH5_C);
	DDX_Control(pDX, IDC_CHECK7, m_CH7_C);
	DDX_Control(pDX, IDC_CHECK8, m_CH6_C);
	DDX_Control(pDX, IDC_CHECK10, m_enable_C);
	//DDX_Radio(pDX, IDC_RADIO1, m_radio_therm);
	DDX_Control(pDX, IDCANCEL, m_jacket_1c_C);

	DDX_Control(pDX, IDC_STATIC_CORE_GRAPH2, m_graph_radio_C);

	DDX_Control(pDX, IDC_COMBO1, m_combo_thermo_aux_C);
	DDX_Control(pDX, IDC_STATIC_core_color2, m_aux_color_C);
	DDX_Control(pDX, IDC_STATIC_LED_THERM_AUX, m_ledred_therm_aux_C);
	DDX_Control(pDX, IDC_STATIC_ANTILOOP_AUX, m_antiloop_aux_C);
	//	DDX_Control(pDX, IDC_COMBO_aux_elements_mean, m_elements_aux_mean_C);
	//	DDX_Text(pDX, IDC_EDIT_aux_skip_points, m_skip_points_aux);
	DDX_Control(pDX, IDC_Auxiliary_Resistance, m_aux_ohm_C);
	DDX_Text(pDX, IDC_EDIT_aux_skip_points, m_skip_points_aux);
	DDV_MinMaxInt(pDX, m_skip_points_aux, 0, 10);
	DDX_Text(pDX, IDC_EDIT32, m_aux_reading_interval);
	DDV_MinMaxInt(pDX, m_aux_reading_interval, 1, 60);
	DDX_Control(pDX, IDC_Auxiliary_Trend, m_aux_speed_C);
	DDX_Control(pDX, IDC_STATIC_LED_SWITCH, m_ledred_switch_C);
	DDX_Control(pDX, IDC_STATIC_ANTILOOP_CORE, m_antiloop_core_C);
	DDX_Control(pDX, IDC_STATIC_thermostat_completed, m_thermostat_completed_C);
	// DDX_Control(pDX, IDC_STATIC_aux_completed, m_aux_completed_C);
	DDX_Control(pDX, IDC_STATIC_core_completed, m_aux_show_completed_C);
	DDX_Check(pDX, IDC__PID_freeze_check, m_thermo_freeze);
	DDX_Control(pDX, IDC_EDIT19, m_delta_uW_shield_C);
	DDX_Control(pDX, IDC_EDIT20, m_mA_injected_shield);
	DDX_Control(pDX, IDC_EDIT_SET_POINT4, m_average_speed_shield_C);
	DDX_Control(pDX, IDC_COMBO_CORE_THERM_ELEMENTS4, m_elements_average_speed_thermo_C);
	DDX_Control(pDX, IDC_BUTTON_START_AUX_MEASUREMENT, m_aux_start_button_C);
	DDX_Control(pDX, IDC_BUTTON_STOP_AUX_MEASUREMENT, m_aux_stop_button_C);
	DDX_Control(pDX, IDC_BUTTON_START_CORE_MEASUREMENT, m_core_start_button_C);
	DDX_Control(pDX, IDC_BUTTON_STOP_CORE_MEASUREMENT2, m_core_stop_button_C);
	DDX_Control(pDX, IDC_BUTTON_START_THERMO, m_thermo_start_button_C);
	DDX_Control(pDX, IDC_BUTTON_STOP_THERMO, m_thermo_stop_button_C);
	DDX_Control(pDX, IDOK, m_Okay_button_C);
	//  DDX_Text(pDX, IDC_EDIT_PP, m_Pp);
	//  DDX_Text(pDX, IDC_EDIT_PI, m_Pi);
	//  DDX_Text(pDX, IDC_EDIT_PD, m_Pd);
	DDX_Control(pDX, IDC_EDIT_PP, m_Pp);
	DDX_Control(pDX, IDC_EDIT_PI, m_Pi);
	DDX_Control(pDX, IDC_EDIT_PD, m_Pd);
	DDX_Control(pDX, IDC_COMBO2, m_Combo_CoreHeatingMode);
	DDX_Control(pDX, IDC_COMBO_CALIBRATION_TIME, m_Combo_Electrical_Calibration_Time);
	DDX_Control(pDX, IDC_EDIT2, m_core_set_seconds_C);
	DDX_Control(pDX, IDC_BUTTON_STOP_Core_Current_Injection, m_Stop_Core_current_injection_C);
	DDX_Control(pDX, IDC_BUTTON_STOP_Jacket_calibration2, m_Stop_Jacket_current_injection_C);
	DDX_Control(pDX, IDC_COMBO_CAPACITOR, capacitor_number);
	DDX_Control(pDX, IDC_EDIT33, capacitor_value_text);
	DDX_Control(pDX, IDC_COMBO_IRRADIATION_TIME, m_Combo_Irradiation_Time);
	DDX_Control(pDX, IDC_BUTTON_IRRADIATE, m_button_irradiate);
	DDX_Text(pDX, IDC_EDIT_TIME_LEFT_IRRADIATION, m_run_countdown);
	DDX_Control(pDX, IDC__GPIB_EXTENSION, m_enable_extended_GPIB_C);
	DDX_Control(pDX, IDC_COMBO_RADIATION_QUALITY, m_combo_radiation_quality);
	DDX_Control(pDX, IDC_EDIT26, m_jacket_calibration_seconds_C);
	DDX_Control(pDX, IDC_BUTTON_Start_Core_Current_Injection, m_start_core_injection_C);
	DDX_Control(pDX, IDC_BUTTON_start_jacket, m_start_jacket_injection_C);
	DDX_Control(pDX, IDC_EDIT25, m_jacket_current_calibration_C);
	DDX_Control(pDX, IDC_STATIC_Countdown_phase, m_Countdown_show_phase);
	DDX_Control(pDX, IDC_COMBO_RANGE_K617, m_combo_range_k617);
}

BEGIN_MESSAGE_MAP(CminervaRxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CminervaRxDlg::OnBnClickedButtonTest)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_Start_Core_Current_Injection, &CminervaRxDlg::OnBnClickedStartCoreInjection)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_start_jacket, &CminervaRxDlg::OnBnClickedButtonstartjacket)
	ON_BN_CLICKED(IDC_BUTTON_RUN_CYCLE, &CminervaRxDlg::OnBnClickedButtonRunCycle)
	ON_BN_CLICKED(IDC_BUTTON_STOP_CYCLE, &CminervaRxDlg::OnBnClickedButtonStopCycle)
	ON_BN_CLICKED(IDC_BUTTON_SET_POINT, &CminervaRxDlg::OnBnClickedButtonSetPoint)
	ON_BN_CLICKED(IDC_BUTTON_PROBE_CURR_SET, &CminervaRxDlg::OnBnClickedButtonProbeCurrSet)
	ON_BN_CLICKED(IDC_BUTTON_START_CORE_MEASUREMENT, &CminervaRxDlg::OnBnClickedButtonStartCoreMeasurement)
	ON_BN_CLICKED(IDC_BUTTON_STOP_CORE_MEASUREMENT2, &CminervaRxDlg::OnBnClickedButtonStopCoreMeasurement2)
	ON_BN_CLICKED(IDC_BUTTON_PROBE_CURR_SET2, &CminervaRxDlg::OnBnClickedButtonProbeCurrSet2)
	ON_BN_CLICKED(IDC_BUTTON_START_THERMO, &CminervaRxDlg::OnBnClickedButtonStartThermo)
	ON_CBN_SELCHANGE(IDC_COMBO_CORE_THERM_ELEMENTS3, &CminervaRxDlg::OnCbnSelchangeComboCoreThermElements3)
	ON_BN_CLICKED(IDC_BUTTON_STOP_THERMO, &CminervaRxDlg::OnBnClickedButtonStopThermo)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CminervaRxDlg::OnDeltaposSpin1)
	// ON_BN_CLICKED(IDC_STATIC_GRAPH, &CminervaRxDlg::OnBnClickedStaticGraph)
	ON_BN_CLICKED(IDC_BUTTON_STOP_SHIELD_INJECT, &CminervaRxDlg::OnBnClickedButtonStopShieldInject)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CminervaRxDlg::OnDeltaposSpin2)
	ON_EN_CHANGE(IDC_EDIT1, &CminervaRxDlg::OnEnChangeEdit1)
	//ON_BN_CLICKED(IDC_BUTTON_STOP_Core_calibration, &CminervaRxDlg::OnBnClickedButtonStopCorecalibration)
	ON_BN_CLICKED(IDC_BUTTON_STOP_Jacket_calibration2, &CminervaRxDlg::OnBnClickedButtonStopJacketcalibration2)
	ON_BN_CLICKED(IDC_CHECK2, &CminervaRxDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CminervaRxDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CminervaRxDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CminervaRxDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CminervaRxDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CminervaRxDlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CminervaRxDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK10, &CminervaRxDlg::OnBnClickedCheck10)
	ON_BN_CLICKED(IDC_STATIC_CORE_GRAPH2, &CminervaRxDlg::OnBnClickedStaticCoreGraph2)
	ON_BN_CLICKED(IDC_BUTTON_START_AUX_MEASUREMENT, &CminervaRxDlg::OnBnClickedButtonStartAuxMeasurement)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CminervaRxDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_STOP_AUX_MEASUREMENT, &CminervaRxDlg::OnBnClickedButtonStopAuxMeasurement)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AUX, &CminervaRxDlg::OnDeltaposSpinAux)
	ON_BN_CLICKED(IDC_BUTTON_SET_VALUES_AUX, &CminervaRxDlg::OnBnClickedButtonSetValuesAux)
	ON_CBN_SELCHANGE(IDC_COMBO_CORE_THERM_ELEMENTS2, &CminervaRxDlg::OnCbnSelchangeComboCoreThermElements2)
	ON_BN_CLICKED(IDC__PID_freeze_check, &CminervaRxDlg::OnCheckboxClickedFreezePID)
	ON_BN_CLICKED(IDC_Save_Thermo_Settings, &CminervaRxDlg::OnBnClickedSaveThermoSettings)
	ON_BN_CLICKED(IDC_BUTTON_READ_THERMO, &CminervaRxDlg::OnBnClickedButtonReadThermo)
	ON_BN_CLICKED(IDCANCEL, &CminervaRxDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CminervaRxDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_CORE_THERM_ELEMENTS, &CminervaRxDlg::OnCbnSelchangeComboCoreThermElements)
	ON_CBN_SELCHANGE(IDC_COMBO_CORE_THERM_ELEMENTS4, &CminervaRxDlg::OnCbnSelchangeComboThermospeedElements)
	
	ON_CBN_SELCHANGE(IDC_COMBO2, &CminervaRxDlg::OnCbnSelchangeComboHeatingMode)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPACITOR, &CminervaRxDlg::OnCbnSelchangeComboCapacitor)
	ON_BN_CLICKED(IDC_BUTTON_IRRADIATE, &CminervaRxDlg::OnBnClickedButtonIrradiate)
	ON_CBN_SELCHANGE(IDC_COMBO_IRRADIATION_TIME, &CminervaRxDlg::OnCbnSelchangeComboIrradiationTime)
	ON_BN_CLICKED(IDC__GPIB_EXTENSION, &CminervaRxDlg::OnBnClickedCheckEnableExtendedGPIB)
	ON_CBN_SELCHANGE(IDC_COMBO_RADIATION_QUALITY, &CminervaRxDlg::OnCbnSelchangeComboRadiationQuality)
	ON_BN_CLICKED(IDC_CHECK_synchronize, &CminervaRxDlg::OnBnClickedChecksynchronize)
	ON_CBN_SELCHANGE(IDC_COMBO_CALIBRATION_TIME, &CminervaRxDlg::OnSelchangeComboCalibrationTime)
	ON_CBN_SELCHANGE(IDC_COMBO_RANGE_K617, &CminervaRxDlg::OnCbnSelchangeComboRangeK617)
	ON_BN_CLICKED(IDC_BUTTON_ANALYZE_RUN, &CminervaRxDlg::OnBnClickedButtonAnalyzeRun)
	ON_BN_CLICKED(IDC_BUTTON_STOP_Core_Current_Injection, &CminervaRxDlg::OnBnClickedButtonStopCoreCurrentInjection)
END_MESSAGE_MAP()


// CminervaRxDlg message handlers

BOOL CminervaRxDlg::OnInitDialog()
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
	
	int i = MessageBox(L"Do you want to extend the GPIB configuration for Rx Irradiation Mode?\nThis includes connecting to the monitor chamber electrometer, thermometer, barometer, hygrometer, and shutter.", L"GPIB configuration", MB_YESNO);
	if (i == IDNO) m_partial_GPIB_configuration = TRUE;
	else
	{
		m_partial_GPIB_configuration = FALSE;
		//UpdateData(FALSE);
	}
	m_string = new char[200];
	
	// Default configuration withOUT Monitor chamber electrometer etc.
	assign_GPIBaddress();
	check_instruments();
	instruments_configuration();
		
	if (!m_partial_GPIB_configuration)
	{
		extend_GPIBNetwork();
		extended_check_instruments();
		extended_instruments_configuration();
	}

	 m_directory = L"\\Users\\CalRx\\Documents\\Minerva_runs\\"; 
	 m_ETA_target = 15; // desired minutes to setpoint
	 m_set_point=10500; // Ohm
	 m_p_pid = 0.1;
	 m_d_PID = 0.06;
	 m_I_PID = 0.005;
	 m_mean_resistance_aux = 8000.; 
	 m_core_probe_curr = 15; // microAmpere
	 m_jacket_probe_current = 15; // microAmpere
	 load_elements_media();
	 m_media_core = NULL;
	 m_deltaR_thermostat = NULL;
	 m_grafico_termo = NULL;
	 m_grafico_core = NULL;
	 my_run = NULL;
	 busy_7001 = _T("This is a test");

	 m_seconds_beginning_Dec_2013 = CTime(2014, 07, 1, 0, 0, 0); // T_0 is July 1st, 2014, 00:00:00
	 // m_seconds_OnInit = CTime::GetCurrentTime();
		 
	 m_old_time = 0; 
	 old_error = 0;
	 older_error = 0;
	 saturazione = FALSE;
	  
	 m_p_CDC = NULL;
	 m_p_CDC_CORE = NULL;
	 m_p_CDC_AUX = NULL;
	 m_vector_thermo =  new (double[DIM_VET_TERMO +2][2]);
	 m_vector_core = new (double[DIM_VET_CORE + 2][2]);
	 m_vector_aux = new (double[DIM_VET_AUX + 2][2]);
	
	 for (int i = 0; i < DIM_VET_CORE+2; i++) // inizializzo a zero il vettore del core
	 {
		 m_vector_core[i][0] = 0.0;
		 m_vector_core[i][1] = 0.0;
	 }

	 for (int j = 0; j < DIM_VET_TERMO+2; j++) // inizializzo a zero il vettore del core
	 {
		 m_vector_thermo[j][0] = 0.0;
		 m_vector_thermo[j][1] = 0.0;
	 }

	 for (int k = 0; k < DIM_VET_AUX+2; k++) // inizializzo a zero il vettore del core
	 {
		 m_vector_aux[k][0] = 0.0;
		 m_vector_aux[k][1] = 0.0;
	 }
	 
	 
	 m_points_vector_thermo = 0;
	 m_points_vector_core = 0;
	 m_points_vector_aux = 0;
	 m_scale_plot_thermo = (float) 0.001;
	 m_scale_plot_core = 1;
	 m_scale_plot_aux = 1;
	 m_thermostat_reading_interval = (int) ceil(TIMER_THERMOSTAT / 1000.);
	 m_aux_reading_interval = (int) ceil(TIMER_AUX / 1000.); 
	 m_p_status_switch[1] = &m_CH1_C;
	 m_p_status_switch[2] = &m_CH2_C;
	 m_p_status_switch[3] = &m_CH3_C;
	 m_p_status_switch[4] = &m_CH4_C;
	 m_p_status_switch[5] = &m_CH5_C;
	 m_p_status_switch[6] = &m_CH6_C;
	 m_p_status_switch[7] = &m_CH7_C;

	 enable_switch(false);
	 switch_open_all();
	 Status_7001();
	
	 // Auxiliary Thermistor Plot Combo Box
	 m_combo_thermo_aux_C.AddString(L"none");
	 m_combo_thermo_aux_C.AddString(L"Core_2");
	 m_combo_thermo_aux_C.AddString(L"Jacket_2_base");
	 m_combo_thermo_aux_C.AddString(L"Jacket_1_cap");
	 m_combo_thermo_aux_C.AddString(L"Shield_2_cap");
	 m_combo_thermo_aux_C.AddString(L"T_water");
	 m_combo_thermo_aux_C.AddString(L"T_PMMA");
	
	 m_combo_thermo_aux_C.SetCurSel(2);
	 OnCbnSelchangeCombo1();

	 populate_capacitor_list();
	 
	 // Calibration mode OFF or ON
	 m_Combo_CoreHeatingMode.AddString(L"Calibration OFF");
	 m_Combo_CoreHeatingMode.AddString(L"Calibration ON");
	 m_Combo_CoreHeatingMode.SetCurSel(0);

	 // Electrical Calibration Time Combo Box
	 m_Combo_Electrical_Calibration_Time.AddString(L"120"); 
	 m_Combo_Electrical_Calibration_Time.AddString(L"90 ");
	 m_Combo_Electrical_Calibration_Time.AddString(L"60 ");
	 m_Combo_Electrical_Calibration_Time.SetCurSel(0);

	 // Selection of the range on the k617 electrometer connected to the monitor chamber
	 m_combo_range_k617.AddString(L"0.2");
	 m_combo_range_k617.AddString(L"2.0");
	 m_combo_range_k617.AddString(L"20");
	 m_combo_range_k617.SetCurSel(2);

	 // Radiation Time Combo Box
	 m_Combo_Irradiation_Time.AddString(L"120");
	 m_Combo_Irradiation_Time.AddString(L"90 ");
	 m_Combo_Irradiation_Time.AddString(L"60 ");
	 m_Combo_Irradiation_Time.AddString(L"5 ");
	 m_Combo_Irradiation_Time.SetCurSel(0);

	 // Radiation Quality Combo Box
	 attenuation_coeff = 0.259;
	 m_combo_radiation_quality.AddString(L"CCRI-100");
	 m_combo_radiation_quality.AddString(L"CCRI-135"); 
	 m_combo_radiation_quality.AddString(L"CCRI-180"); 
	 m_combo_radiation_quality.AddString(L"CCRI-280");
	 m_combo_radiation_quality.SetCurSel(0);

	 // Countdown and modality
	 m_run_countdown = 120;
	 m_Countdown_show_phase.ShowWindow(SW_HIDE); // Will be shown while heating takes place either due to irradiation or electrical heating
	 m_run_type = 0; // Defaults to 'idle' state which applies to non-calibrating heatings and core drifts

	 m_red_light_thermostat = 0; // no precedence to the thermostat thermistor
	 m_status_aux = DONE;
	 m_status_thermostat = DONE;
	 m_skip_points_aux = 1;
	 m_skip_points_thermostat = 1;
	 m_power_thermostat = 0. ;
	 m_average_thermospeed = 999;

	 m_aux_stop_button_C.EnableWindow(FALSE); // Disables the STOP buttons on Init Dialog
	 m_core_stop_button_C.EnableWindow(FALSE);
	 m_thermo_stop_button_C.EnableWindow(FALSE);
	 m_Okay_button_C.EnableWindow(FALSE);
	 m_Stop_Core_current_injection_C.EnableWindow(FALSE);
	 m_Stop_Jacket_current_injection_C.EnableWindow(FALSE);
	 m_Combo_CoreHeatingMode.EnableWindow(TRUE);
	 m_Combo_Electrical_Calibration_Time.EnableWindow(FALSE);

	 m_Pp.EnableWindow(FALSE);
	 m_Pi.EnableWindow(FALSE);
	 m_Pd.EnableWindow(FALSE);
	 m_Combo_CoreHeatingMode.EnableWindow(TRUE);

	 if (m_partial_GPIB_configuration) // GPIB network is limited
	 {
		 m_button_irradiate.EnableWindow(FALSE);
		 m_Combo_Irradiation_Time.EnableWindow(FALSE);
		 m_combo_radiation_quality.EnableWindow(FALSE);
		 m_combo_range_k617.EnableWindow(FALSE);
		 capacitor_number.EnableWindow(FALSE);
		 capacitor_value_text.EnableWindow(FALSE);
		 m_enable_extended_GPIB_C.EnableWindow(TRUE);
	 }
	 else // GPIB network is extended to the monitor chamber electrometer, thermometer, barometer...
	 {
		 m_enable_extended_GPIB_C.EnableWindow(FALSE);
		 m_enable_extended_GPIB_C.SetCheck(1);
	 }
		

	 populate_capacitor_list();

	 taskHandleAPRI = 0;			/* ID del task che verrà assegnato da DAQmxCreateTask */
	 taskHandleCHIUDI = 0;			/* ID del task che verrà assegnato da DAQmxCreateTask */
	 outputAPRI = "dev1/ao0";			/* L'output analogico usato per il tasto APRI è AO0*/
	 outputCHIUDI = "dev1/ao1";		/* L'output analogico usato per il tasto CHIUDI è AO1*/
	 nomeTaskAPRI = "TaskAO0";			/* Nome del task */
	 nomeTaskCHIUDI = "TaskAO1";		/* Nome del task */
	 minVal = 0, maxVal = 5;				/* L'output è condizionato al range 0..5V */
	 configInput = DAQmx_Val_RSE;		/* L'uscita è configurata come  come single-ended */
	 totale = 0;

	 /* CREAZIONE DEL TASK                        */
	 DAQmxCreateTask(nomeTaskAPRI, &taskHandleAPRI);
	 DAQmxCreateTask(nomeTaskCHIUDI, &taskHandleCHIUDI);

	 /* CONFIGURAZIONE DEL TASK                   */
	 DAQmxCreateAOVoltageChan(taskHandleAPRI, outputAPRI, "", minVal, maxVal, DAQmx_Val_Volts, NULL);
	 DAQmxCreateAOVoltageChan(taskHandleCHIUDI, outputCHIUDI, "", minVal, maxVal, DAQmx_Val_Volts, NULL);

	 /* AVVIO DEL TASK                            */
	 DAQmxStartTask(taskHandleAPRI);
	 DAQmxStartTask(taskHandleCHIUDI);

	 m_seconds_t_zero = ((double)clock() / (double)CLOCKS_PER_SEC);
	 
	 // create the recordset:
	 db.OpenEx(_T("DSN=192.168.120.102;UID=misuraUser; PWD=musy1981; DATABASE=calorimetroRX"), CDatabase::noOdbcDialog);
	 CRecRunId = new Crun_id(&db);
	 CRecRunMeas = new Crun_measurements(&db);

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CminervaRxDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CminervaRxDlg::OnPaint()
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
HCURSOR CminervaRxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CminervaRxDlg::OnBnClickedButtonTest()
{
	// Test functions go here
		
	
	my_run = new run(m_directory, DIM_VET_CORE+2, m_vector_core);
	my_run->save_to_file();
	return;
	

	//create_thermo_graph();

}


BOOL CminervaRxDlg::inizializza_GPIB()
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


bool CminervaRxDlg::assign_GPIBaddress()
{
	m_adr_k7001_switch = assign_device(19); // vecchio valore indirizzo GPIB 20
	m_adr_k2400 = assign_device(22);
	m_adr_k2400_core = assign_device(23);
	m_adr_k2400_jacket = assign_device(24);
	//m_adr_k2182_core = assign_device(7);
	m_adr_k2182_multi = assign_device(8);

	m_adr_k6220_core = assign_device(11);
	m_adr_k6220_multi = assign_device(12);



	return false;
}


int CminervaRxDlg::assign_device(int GPIB_address)
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


int CminervaRxDlg::add_message(CString text)
{
	CTime hour = CTime::GetCurrentTime();

	CString message;
	message.Format(L" %s: %s.", hour.Format(L"%x %X"), text);
	m_message_box_C.AddString(message);
	
	m_message_box_C.SetTopIndex(m_message_box_C.GetCount() - 4);
	return 1;
}

int CminervaRxDlg::IBSTA()
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


int CminervaRxDlg::poll(int address)
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


int CminervaRxDlg::check_instruments()
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

	/*if (!poll(m_adr_k2182_core))
	{
		testo = "Please Check K2182 Address 7";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}*/

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


BOOL CminervaRxDlg::write_GPIB(int address, CString command)
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


BOOL CminervaRxDlg::K2400_configuration(int address)
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


int CminervaRxDlg::conv_CS_CH(CString text)
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


bool CminervaRxDlg::current_inject_k2400(int microampere, long address)
{
	CString text;

	text.Format(L"SOUR:CURR:RANG  %g ", microampere / 1000000.);
	write_GPIB(address, text);
	
	text.Format(L"SOUR:CURR:LEV %g", microampere / 1000000.);
	write_GPIB(address, text);
	return 1;
	

	
}

bool CminervaRxDlg::current_inject_k2400(double ampere, long address)
{
	CString text;

	text.Format(L"SOUR:CURR:RANG  %12.8f ", ampere );
	write_GPIB(address, text);

	text.Format(L"SOUR:CURR:LEV  %12.8f", ampere );
	write_GPIB(address, text);
	return 1;



}


bool CminervaRxDlg::k_2400_onoff(bool on, long address)
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


void CminervaRxDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	k_2400_onoff(0, m_adr_k2400);
	k_2400_onoff(0, m_adr_k2400_core);
	k_2400_onoff(0, m_adr_k2400_jacket);
	K6220_Delta_Configuration(m_adr_k6220_core, m_core_probe_curr, FALSE); // Halts Trigger and exits from DeltaMode.
	// k_2400_onoff(0, m_adr_k6220_core);
	k_2400_onoff(0, m_adr_k6220_multi);

	delete[] m_string;
	if (m_media_core)
	{
		delete[] m_media_core;
	}
	if (m_deltaR_thermostat)
		delete[] m_deltaR_thermostat;
}


int CminervaRxDlg::instruments_configuration()
{
	K2400_configuration(m_adr_k2400);
	K2400_configuration(m_adr_k2400_core);
	K2400_configuration(m_adr_k2400_jacket);
	//K2182_configuration(m_adr_k2182_core);
	K2182_configuration(m_adr_k2182_multi);
	K6220_configuration(m_adr_k6220_core); // 22/06/2017 da oggi sviluppo della modalità di misura Delta Mode in cui si parla su GPIB solo col 6220 e il 2182 visto come una sua appendice
	K6220_configuration(m_adr_k6220_multi);
	return 0;
}


BOOL CminervaRxDlg::read_GPIB(int address, CString * p_text)
{
	int result = ibrd(address, m_string, 200);
	IBSTA();
	unsigned long ctr = 0;
	p_text->Delete(0,1000);
	while (ctr < ibcntl)
	{
		p_text->AppendChar( m_string[ctr]);
		ctr++;
	}
	
	return ibcntl;
}


int CminervaRxDlg::K2182_configuration(int address) 
/* Makes an initial configuration of a K2182A nanovoltmeter.
This has been largely conceived at the time of programming for the brachytherapy graphite calorimeter.
Later extended in 2015-2016 to the case of the Rx calorimeter. 
In June 2017, updated to include the use of DeltaMode via TriggerLink (Massimo).
Please also refer to the 6220 configuration as the current source becomes the master instrument in Delta mode,
i.e. the source meter sources current and reads voltage (which is presumably passed onto it by the 2182A).
*/ 
{
	CString text;

	text = L":syst:pres"; /* 2182 - System preset defaults */
	write_GPIB(address, text);

	text = L":SENS:VOLT:RANGE:AUTO ON";
	write_GPIB(address, text);

	text = L":SENS:VOLT:DC:NPLC 1"; /* Single measurement carried out over 5 power line cycles */
	write_GPIB(address, text);

	text = L":SENS:VOLT:LPAS OFF"; /* Analog filtration off */
	write_GPIB(address, text);
	
	//text = L":SENS:VOLT:CHAN1:DFIL:STAT OFF"; /*turning off digital filtration to check speed*/
	//write_GPIB(address, text);


	text = L":SENS:VOLT:DFIL:COUN 20"; /*Will COUNt 20 measurements in the stack prior to calculate an average and output a value*/
	write_GPIB(address, text);

	text = L":SENS:VOLT:DFIL:WIND 0.01"; /*was 0.01 until 20170802. This is 0.01% of the RANGE, which is currently automatic.*/
	write_GPIB(address, text);

	text = L":SENS:VOLT:DFIL:TCON REP"; /* The vector of COUN individual values is purged and REPeated at each new measurement.*/
	write_GPIB(address, text);
	
	text = L":SENS:VOLT:CHAN1:DFIL:STAT ON"; /* turn Digital filter STATus on*/
	write_GPIB(address, text);
/*	CString text;
	text = L":SENS:VOLT:RANGE:AUTO ON";
	write_GPIB(address, text);

	text = L":SENS:VOLT:NPLC 1";
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
*/
	return 0;
}

int CminervaRxDlg::K2182_configuration(int address, int DeltaMode)
/*Polymorphic configuration to turn DeltaMode on or off on the fly*/
{
	CString text;
	if (DeltaMode == 0) /*the traditional way at ENEA*/
		{
		text = L":syst:pres"; /* 2182 - System preset defaults */
		write_GPIB(address, text);
		
		text = L":SENS:VOLT:RANGE:AUTO ON";
		write_GPIB(address, text);

		text = L":SENS:VOLT:DC:NPLC 1";
		write_GPIB(address, text);

		text = L":SENS:VOLT:CHAN1:DFIL:STAT ON";
		write_GPIB(address, text);

		text = L":SENS:VOLT:DFIL:WIND 0.01";
		write_GPIB(address, text);

		text = L":SENS:VOLT:DFIL:TCON REP";
		write_GPIB(address, text);
		}
	else if (DeltaMode == 1) /*Pre-disposes the 2182 to triggered DeltaMode*/
		{
			text = L":syst:pres"; /* 2182 - System preset defaults */
			write_GPIB(address, text);

			text = L":SENS:VOLT:DC:NPLC 1"; /* Fast but not fastest measurement rate*/
			write_GPIB(address, text);

		//	text = L":trig:del 0.3"; /* 0.3 sec delay on the 2182A. */
		//	write_GPIB(address, text);

			text = L"sens:volt:delta on"; /* enables delta-mode on the 2182 */
			write_GPIB(address, text);

			text = L":syst:faz off"; /* disable front auto-zero for faster Delta Mode*/
			write_GPIB(address, text);

			text = L":trig:sour ext"; /* prepares for external triggering */
			write_GPIB(address, text);
		}
	return 0;
}

double CminervaRxDlg::read_k2182(int address,BOOL send_request)
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


void CminervaRxDlg::K6220_configuration(int address)
{
	CString text;
	
	text = L"*rst"; /* Resets to defaults on the 6220*/
	/*This still retains the current GPIB configuration*/
	write_GPIB(address, text);

	text = L"SOUR:CURR:RANG 10e-6"; /* Selects the XX.XXX range on the 6220. */
	write_GPIB(address, text);

	text.Format(L"CURR  %6.3g", 15. / 1000000.);
	write_GPIB(address, text);

	if (address == m_adr_k6220_core)
	{
	/* settaggi 2182 attraverso seriale (delta mode)*/

	//text = L"SYST:COMM:SER:SEND '*rst'"; /*Resets the 2182A to defaults */
	//write_GPIB(address, text);

	text = L"SYST:COMM:SER:SEND 'VOLT:RANG 0.01'";
	write_GPIB(address, text);
	
	text = L"SYST:COMM:SER:SEND 'VOLT:NPLC 5'";
	write_GPIB(address, text);

	text = L"SYST:COMM:SER:SEND ':SENS:VOLT:DELTA ON'"; /* enables delta-mode on the 2182 */
	write_GPIB(address, text);

	text = L"SYST:COMM:SER:SEND 'syst:faz off'"; /* disable front auto-zero for faster Delta Mode*/
	write_GPIB(address, text);

	text = L"SYST:COMM:SER:SEND 'trig:sour ext'"; /* prepares for external triggering */
	write_GPIB(address, text);

	/* fine settaggi 2182 attraverso seriale */

	/* ARM Layer Settings */

	text = L"ARM:SOUR IMM"; /* Set the ARM-In Event to IMMediate*/
	write_GPIB(address, text);

	text = L"ARM:OLIN 3"; /*Set ARM layer output signal line #3 (from the 2182A manual, p.5-11)*/
	write_GPIB(address, text);

	text = L"ARM:OUTP NONE"; /* Disables the ARM layer output trigger p.8-10)*/
	/* not sure whether this corresponds to ARM-OUT Events OFF as at p 5.11 */
	write_GPIB(address, text);

	/* Trigger layer settings */

	text = L"TRIG:SOUR TLIN"; /* SM - Select the trigger source to TLINk */
	write_GPIB(address, text);

	text = L"TRIG:ILIN 1"; /* SM - Select the trigger layer input signal line to 1 */
	write_GPIB(address, text);

	text = L"TRIG:OLIN 2"; /* SM - Select the trigger layer output signal line to 2 */
	write_GPIB(address, text);

	text = L"TRIG:OUTP SOUR"; /* SM - Output trigger after source.*/
	write_GPIB(address, text);

	//text = L":TRIG:COUN 2"; /* SM - Trig count 2: one positive (high) and one negative (low). */
	//write_GPIB(address, text);

	text = L"UNIT:VOLT V"; /* Specifies that Volts readings are sent from 2182 to 6220. */
	write_GPIB(address, text);

	/* text = L"SOUR:DELT:DEL 1.7e-3";
	write_GPIB(address, text); */

	text = L"CURR:FILT ON"; /*turns on source-meter filtering*/
	write_GPIB(address, text);

	text = L"TRIG:DIR SOUR"; /* SM - Enable source bypass */
	write_GPIB(address, text);
	}
	else if (address == m_adr_k6220_multi)
	{
		text = L"CURR:FILT ON"; /*turns on source-meter filtering*/
		write_GPIB(address, text);
	}

	return ;
}


void CminervaRxDlg::OnBnClickedStartCoreInjection()
{
	// Starts injection of current is the heating thermistors of the core
	// IF this is an electrical calibration, several things must be taken care of:
	// 1) The PID is blocked (freeze on)
	// 2) the beginning of the heating time is stored (seconds)
	// 3) At the end of the prescribed calibration time (defaults to 120") data output is handled via  
	UpdateData(TRUE);
	
	if (m_secondi_core <= 0 || m_micro_ampere_core <= 0 || m_micro_ampere_core >500 || m_secondi_core>15000)
	{
		AfxMessageBox(L"*** ERRORE NEI PARAMETRI IMPOSTATI", MB_OK | MB_ICONSTOP);
		return;
	}
	
	// Enabling and disbaling buttons linked to injection of current in the core
	m_Stop_Core_current_injection_C.EnableWindow(TRUE);
	m_start_core_injection_C.EnableWindow(FALSE);
	m_button_start_cycles_C.EnableWindow(FALSE);
	
	m_flag_core = 1;
	k_2400_onoff(0, m_adr_k2400_core);
	current_inject_k2400(m_micro_ampere_core, m_adr_k2400_core);
	
	if (m_CoreHeatingMode == 1) // Electrical calibration: connect to Dbase to create Crun_id and Crun_measurements records
	{
		m_run_type = 1;
		m_Combo_CoreHeatingMode.EnableWindow(FALSE);
		m_Combo_Electrical_Calibration_Time.EnableWindow(FALSE);
		CRecRunId->Open();
		CRecRunId->AddNew();
		CRecRunId->m_calibration_mode = 1;
		CString today = (CTime::GetCurrentTime()).Format(L"%Y%m%d");
		CRecRunId->m_hour = CTime::GetCurrentTime();
		CRecRunId->m_date = today;
		CRecRunId->Update();
		CRecRunId->Requery();
	}
	core_power();
	if (m_synchronize) OnBnClickedButtonstartjacket();
	return;
}


void CminervaRxDlg::OnTimer(UINT_PTR nIDEvent)
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
	else if (nIDEvent == 2001) // read core thermistor resistance
	{
		// read_core();
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
	else if (nIDEvent == 4001)
	{
		jacket_power();
	}
	else if (nIDEvent == 5000) // reads one auxiliary thermistor
	{
		manage_aux();
	}
	else if (nIDEvent == 6000) // Irradiation
	{
		if (m_run_countdown > 1)
		{
			--m_run_countdown;
			UpdateData(FALSE);
			m_Countdown_show_phase.SetWindowTextW(L"Irradiation");
			m_Countdown_show_phase.ShowWindow(SW_SHOW);
		}
		else
		{
			KillTimer(6000);
			
			// Shutter closure operations begin
			float64 value = 4;
			DAQmxWriteAnalogScalarF64(taskHandleCHIUDI, 0, DAQmx_Val_WaitInfinitely, value, NULL);
			DAQmxWriteAnalogScalarF64(taskHandleAPRI, 0, DAQmx_Val_WaitInfinitely, 0.0, NULL);

			// imposto timer di 0.1 s con passo da 0.01 s per finalizzazione apertura otturatore:
			m_ShutterWait = 11;
			SetTimer(6002, 10, NULL);
			// Shutter closure operations end

			OnCbnSelchangeComboIrradiationTime();
			m_button_irradiate.SetWindowTextW(L"Irradiate");
			m_Combo_Irradiation_Time.EnableWindow(TRUE);
			m_combo_radiation_quality.EnableWindow(TRUE);
			capacitor_number.EnableWindow(TRUE);
			m_Combo_CoreHeatingMode.EnableWindow(TRUE); // Enable electrical calibration option
			m_thermo_freeze = FALSE; // PID freeze
			UpdateData(FALSE);
		}
	}
	else if (nIDEvent == 6001) // Timer for handling the opening of the Rx tube Shutter
	{
		m_ShutterWait = m_ShutterWait - 1;

		if (m_ShutterWait <= 0)
		{
			KillTimer(6001);

			float64 value = 0.0;
			DAQmxWriteAnalogScalarF64(taskHandleAPRI, 0, DAQmx_Val_WaitInfinitely, value, NULL);

			SetTimer(6000, 1000, NULL);
		}
	}
	else if (nIDEvent == 6002) // Timer for handling the closure of the Rx tube Shutter
	{
		m_ShutterWait = m_ShutterWait - 1;

		if (m_ShutterWait <= 0)
		{
			KillTimer(6002);

			float64 value = 0.0;
			DAQmxWriteAnalogScalarF64(taskHandleCHIUDI, 0, DAQmx_Val_WaitInfinitely, value, NULL);

			CString text;
				
			irradiation_ends_now = ((double)clock() / (double)CLOCKS_PER_SEC); // Prendere il momento attuale come istante 0- dell'irraggiamento (OK)
			//  mettere in modalità misura OFF elettrometro monitor (dare il GET per la memorizzazione valore finale)
			//  Prendere il momento attuale come istante 0+ dell'irraggiamento e farne la _media_ con il precedente, sottraendogli poi il t_zero.
			//  Note: this is a strategy to estimate the moment in which the voltage measurement on the electrometer was actually made and stored. 
				
			text = L"G1X";
			write_GPIB(m_adr_k617_monitor, text); // comando di lettura misure senza prefisso

			CString rMString, timeStr, temp; 
			read_GPIB(m_adr_k617_monitor, &rMString);

			//  Prendere il momento attuale come istante 0+ dell'irraggiamento e farne la _media_ con il precedente, sottraendogli poi il t_zero.
			//  Note: this is a strategy to estimate the moment in which the voltage measurement on the electrometer was actually made and stored. 
			irradiation_ends_now = 0.5* (irradiation_ends_now + ((double)clock() / (double)CLOCKS_PER_SEC)) - m_seconds_t_zero;
			irradiation_ends_now_core_vector_time = m_vector_core[m_points_vector_core - 1][0];
			VMend = wcstod(rMString, NULL);
			
			AcquireTmon(1);
			AcquirePmon(1);
			AcquireHmon(1);

			timeStr.Format(L"%.3f", irradiation_ends_now);

			temp.Format(L"%.1f", (TMbegin + TMend) / 2.0);
			add_message(L"\nVM2=" + rMString + L", tend=" + timeStr + L" s, T="+temp +L" °C");

			CoreVectorRunEnds.Format(L"%.3f", irradiation_ends_now_core_vector_time);
			add_message(L"corresponding to a value stored in core vector: " + CoreVectorRunEnds + L" s");
			temp.Format(L"%.1f", (PMbegin + PMend) / 2.0);
			add_message(L" P=" + temp+L" hPa");
			temp.Format(L"%.1f", (HMbegin + HMend) / 2.0);
			add_message(L" Hr=" + temp + L" %");
			
			text = L"C1Z0X";
			write_GPIB(m_adr_k617_monitor, text); // zero check ON, correct OFF

			ElaborateMonitorData();
			temp.Format(L"%.5e", QMON);
			add_message(L"Qmonitor=" + temp + L" /pC");
			temp.Format(L"%.5e", IMON);
			add_message(L"Imonitor=" + temp + L" /pA");

			m_run_countdown = POST_RUN_DRIFT_TIME; // Post-run contdown before output to file.
			SetTimer(6003, 1000, NULL); 
		}
	}
	else if (nIDEvent == 6003) // Timer to handle the final 180 sec after a heating run (post-irradiation o post heating)
	{
		if (m_run_countdown > 1) // Countdown showing time left to creation of run 'dump' file, via the instantiation of a run-class object
		{
			--m_run_countdown; 
			UpdateData(FALSE);
			m_Countdown_show_phase.SetWindowTextW(L"Post-Run Drift");
			m_Countdown_show_phase.ShowWindow(SW_SHOW);
			if (m_run_countdown == 60) // Two minutes (180" - 120") after heating bring back a series of controls so that you can repeat a run
			{
				// re-enabling all buttons linked to irradiations, if the GPIB is extended
				if (!m_partial_GPIB_configuration)
				{
					m_button_irradiate.EnableWindow(TRUE);
					m_Combo_Irradiation_Time.EnableWindow(TRUE);
					m_combo_radiation_quality.EnableWindow(TRUE);
					m_combo_range_k617.EnableWindow(TRUE);
					capacitor_number.EnableWindow(TRUE);
					capacitor_value_text.EnableWindow(TRUE);
				}
				
				// re-enabling all controls for Calibrations (Mode and Time Combos, Start and Stop buttons )
				m_Combo_CoreHeatingMode.EnableWindow(TRUE);
				m_Combo_Electrical_Calibration_Time.EnableWindow(TRUE);
				m_Stop_Core_current_injection_C.EnableWindow(FALSE); 
				m_start_core_injection_C.EnableWindow(TRUE);
			}
		}
		else
		{
			KillTimer(6003);
			m_Countdown_show_phase.ShowWindow(SW_HIDE);
			OnCbnSelchangeComboIrradiationTime(); // shows the duration that the next run will have.
			run* runObject;
			BOOL electrical_calibration = FALSE;
			if (m_CoreHeatingMode == 1) // You are finishing up an electrical calibration. Not the best control. Find a better **global** one.
				electrical_calibration = TRUE;
			else if (m_CoreHeatingMode == 0) // You are completing an irradiation. NO. As it stands, this could just be a heating without a calibration.
				electrical_calibration = FALSE;

			CRecRunId->MoveLast();
			CRecRunId->Edit();
			CRecRunId->m_t_core_begin = irradiation_begins_now_core_vector_time;
			CRecRunId->m_t_core_end = irradiation_ends_now_core_vector_time;

			if (electrical_calibration)
			{
				CRecRunId->m_Injected_energy = m_joule_core;
				CRecRunId->m_injected_power = m_joule_core / (irradiation_ends_now - irradiation_begins_now);
				CRecRunId->m_t_mon_begin = irradiation_begins_now;
				CRecRunId->m_t_mon_end = irradiation_ends_now;
			}
			else if (!electrical_calibration) // Write to database all data related to the monitor chamber acquisition
			{
				CRecRunId->m_Delta_VMON = VMend - VMbegin;
				CRecRunId->m_QMON = QMON;
				CRecRunId->m_katt = Katt;
				CRecRunId->m_ktp = Ktpm;
				CRecRunId->m_P = 0.5 *(PMbegin + PMend);
				CRecRunId->m_T = 0.5 *(TMbegin + TMend);
				CRecRunId->m_H = 0.5 *(HMbegin + HMend);
			}
			CRecRunId->Update();
			CRecRunId->Requery();
			CRecRunId->MoveLast();
			
			int run_time = 0;
			if (electrical_calibration)
				run_time = m_secondi_core;
			else
				run_time = m_run_countdown;

			runObject = new run(m_directory, m_points_vector_core - 1, m_vector_core, electrical_calibration, run_time, CRecRunId->m_ID, CRecRunMeas);
			runObject->t1 = CoreVectorRunStarts;
			runObject->t2 = CoreVectorRunEnds;
			runObject->save_to_file();
			runObject->~run();

			// closing the recordsets related to the ID of the current RUN and associated set of time/resistance measures.
			if (CRecRunId->IsOpen()) CRecRunId->Close();
			if (CRecRunMeas->IsOpen()) CRecRunMeas->Close();
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


int CminervaRxDlg::core_power()
{
	static long old_time = 0;
	double volt;
	CString text;
	if (m_flag_core == 1)
	{
		SetTimer(1001, 100, NULL);
		m_timer_core = clock();
		k_2400_onoff(1, m_adr_k2400_core);
		m_joule_core = 0;
		m_flag_core = 2;
		old_time = 0;
		if (m_CoreHeatingMode == 1)
		{
			irradiation_begins_now = ((double)clock() / (double)CLOCKS_PER_SEC) - m_seconds_t_zero;
			irradiation_begins_now_core_vector_time = m_vector_core[m_points_vector_core - 1][0];
			create_cycle_file();
			m_button_irradiate.EnableWindow(FALSE);
			m_Combo_Irradiation_Time.EnableWindow(FALSE);
			m_combo_radiation_quality.EnableWindow(FALSE);
			m_combo_range_k617.EnableWindow(FALSE);
			capacitor_number.EnableWindow(FALSE);
			capacitor_value_text.EnableWindow(FALSE);
			m_thermo_freeze = TRUE;
			UpdateData(FALSE);
		}
			
	} // portion that is executed regardless of the value of m_flag_core
		 long cronometer = (clock() - m_timer_core);
		 double seconds = (double)(cronometer) / 1000.;
		 text.Format(L"%6.2f", seconds);
		 m_seconds_core_C.SetWindowTextW(text);
		 m_Countdown_show_phase.SetWindowTextW(L"Electric Injection");
		 m_Countdown_show_phase.ShowWindow(SW_SHOW);
		
		 volt = k_2400_read_volt(m_adr_k2400_core);
		 text.Format(L"%g", volt);
		 m_volt_core_C.SetWindowTextW(text);
  		 double micro_watt = microwatt(m_micro_ampere_core, volt, &m_microwatt_core_C);

 if (m_flag_core == 2)
		 {
			 microjoule(micro_watt, cronometer,old_time, &m_joule_core, &m_joule_core_C);
			 if (m_CoreHeatingMode == 1) write_file_cycle(cronometer, m_joule_core, m_micro_ampere_core, volt, 0, 0, 0);
			 old_time = cronometer;
		 } 

   if (seconds >= m_secondi_core)
		 {
			 k_2400_onoff(0, m_adr_k2400_core);
			 KillTimer(1001);
			 m_Countdown_show_phase.ShowWindow(SW_HIDE);
			 if (m_CoreHeatingMode == 1) // for electrical calibration, follow the run time with the 6003 timer event handling
			 {
				 
				 irradiation_ends_now = ((double)clock() / (double)CLOCKS_PER_SEC) - m_seconds_t_zero;
				 irradiation_ends_now_core_vector_time = m_vector_core[m_points_vector_core - 1][0];
				 
				 m_file_cycle.Close();

				 m_thermo_freeze = FALSE; // disable PID freeze
				 UpdateData(FALSE);

				 m_run_countdown = POST_RUN_DRIFT_TIME; // Set the countdown at 180 s
				 SetTimer(6003, 1000, NULL);
				 
				 /*
				 // re-enabling all buttons linked to irradiations
				 // To do: begins here -> 2018 05 18: Move all these re-habilitations to the 6003 timer and enable them after 120" (not 180").
				 m_button_irradiate.EnableWindow(TRUE);
				 m_Combo_Irradiation_Time.EnableWindow(TRUE);
				 m_combo_radiation_quality.EnableWindow(TRUE);
				 m_combo_range_k617.EnableWindow(TRUE);
				 capacitor_number.EnableWindow(TRUE);
				 capacitor_value_text.EnableWindow(TRUE);

				 // re-enabling all controls for Calibrations (Mode and Time)
				 m_Combo_CoreHeatingMode.EnableWindow(FALSE);
				 m_Combo_Electrical_Calibration_Time.EnableWindow(FALSE);
				 // To do: ends here -> 2018 05 18
				 */
			 }
			 else if (m_CoreHeatingMode == 0) // Heating without a calibration
			 {
				 m_Stop_Core_current_injection_C.EnableWindow(FALSE);
				 m_start_core_injection_C.EnableWindow(TRUE);
			 }
			 //m_Countdown_show_phase.ShowWindow(SW_HIDE);
			 
			 m_flag_core = 3;
			 m_button_start_cycles_C.EnableWindow(TRUE);
		 }
	return 0;
}



double CminervaRxDlg::k_2400_read_volt(int address)
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


double CminervaRxDlg::microwatt(double current, double volt,  CWnd * window)
{
	double microwatt;
	microwatt = current*volt;
	CString text;
	text.Format(L"%g", microwatt);
	window->SetWindowTextW(text);
	return microwatt;
}


double CminervaRxDlg::microjoule(double watt, long live_time,long old_time, double *joule, CWnd * window)
{
	
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
	
	CString text;
	text.Format(L"%g", *joule);
	window->SetWindowTextW(text);

	return microjoule;
}


void CminervaRxDlg::OnBnClickedButtonstartjacket()
{
	UpdateData(TRUE);
	if (m_synchronize)
	{
		CString current;
		m_jacket_current_calibration = m_micro_ampere_core; 
		m_core_set_seconds_C.GetWindowTextW(current); 
		m_jacket_calibration_seconds = (int) wcstod(current, NULL);
		UpdateData(FALSE);
	}
	else
	{
		m_start_jacket_injection_C.EnableWindow(FALSE);
		m_Stop_Jacket_current_injection_C.EnableWindow(TRUE);
	}
		// UpdateData(TRUE);
		
		if (m_jacket_calibration_seconds <= 0 || m_jacket_current_calibration <= 0 || m_jacket_current_calibration >500 || m_jacket_calibration_seconds >15000)
		{
			AfxMessageBox(L"*** ERRORE NEI PARAMETRI IMPOSTATI NEL JACKET", MB_OK | MB_ICONSTOP);
			return;
		}

		
		m_button_start_cycles_C.EnableWindow(FALSE);
		m_flag_jacket = 1;
		//crea_file_ciclo();

		//controllo_potenza_core();
		k_2400_onoff(0, m_adr_k2400_jacket);
		current_inject_k2400(m_jacket_current_calibration, m_adr_k2400_jacket);

		jacket_power();
		return;
}


bool CminervaRxDlg::create_cycle_file() // Creates a file name for output of power injection data during an electric heating run.
// Note: This could refer to an electrical calibration, or also a manual/piloted heating done to speed up the experiment towards thermal equilibrium.
{
	CTime time = CTime::GetCurrentTime();

	CString file_name = m_directory + time.Format("%Y_%m_%d_%H_%M_%S_heating_cycle.dat");
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


double CminervaRxDlg::write_file_cycle(long cronometer, double joule_core, double current_core, double volt, double joule_jacket, double current_jacket, double volt_jacket)
{
	CTime  absolute_seconds = CTime::GetCurrentTime();
	long seconds = absolute_seconds.GetTime();
	CString aux;
	aux.Format(L" %6.3f    %7.5g    %7.5g   %7.5g    %7.5g   %7.5g    %7.5g   \n", (double)cronometer/1000., joule_core, current_core, volt
		, joule_jacket, current_jacket, volt_jacket);
	m_file_cycle.WriteString(aux);

	return 0;
}


void CminervaRxDlg::OnBnClickedButtonRunCycle()
{
	
	UpdateData(TRUE);
	m_button_stop_cycle_C.EnableWindow(TRUE);
	m_button_start_cycles_C.EnableWindow(FALSE);
	SetTimer(1002, 1000, NULL);
	m_flag_cycle_power_core = 1;
	m_done_cycles = 0;
	cycle_core_power();
	
}


void CminervaRxDlg::OnBnClickedButtonStopCycle()
{
	
	m_button_stop_cycle_C.EnableWindow(FALSE);
	m_button_start_cycles_C.EnableWindow(TRUE);
	KillTimer(1002);
}


void CminervaRxDlg::cycle_core_power()
{
	if (m_flag_cycle_power_core == 1)
	{
		OnBnClickedStartCoreInjection();
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


// checks whether pause time has been reached before a new cycle is launched
BOOL CminervaRxDlg::control_pause()
{
	int seconds = (clock() - m_pause_start) / 1000;
	m_aux_text.Format(L"%d", m_pause_cycle - seconds);
	m_pause_C.SetWindowTextW(m_aux_text);
	return (m_pause_cycle>seconds);
}


void CminervaRxDlg::OnBnClickedButtonSetPoint()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

}


double CminervaRxDlg::read_core() 

{
	char spr;
	BOOL esito = ibrsp(m_adr_k6220_core, &spr);
	double resistance = 0;
	m_anti_block_core++;

	BOOL pronto = spr & 16;
	if (pronto)
	{
		resistance = read_resistance(m_adr_k6220_core);
		manage_data_core(resistance);
	}
	if (pronto || m_anti_block_core>100)
	{

		if (m_anti_block_core > 100)
		{
			m_anti_block_core = 0;
			CString text = L":ABORT";
			write_GPIB(m_adr_k6220_core, text);

		}
		KillTimer(2002);
		SetTimer(2001, TIMER_CORE, NULL); 
	}
	
	
	m_aux_text.Format(L"%d", m_anti_block_core);
	m_antiloop_core_C.SetWindowTextW(m_aux_text);
	
	return resistance;
}
	


void CminervaRxDlg::OnBnClickedButtonProbeCurrSet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	k6220_set_current(m_core_probe_curr, m_adr_k6220_core);
}


int CminervaRxDlg::load_elements_media()
{
	int ctr = 1;
	CString testo;

	while (ctr<=12)
	{
		testo.Format(L"%d", ctr);
		m_select_media_core_C.AddString(testo);
		m_select_mean_jacket_C.AddString(testo);
		m_elements_mean_therrmo_C.AddString(testo);
		m_elements_average_speed_thermo_C.AddString(testo);
		//m_select_mean_jacket_C.AddString(testo);
		ctr++;

	}
	m_select_media_core_C.SetCurSel(0);
	m_select_mean_jacket_C.SetCurSel(2);
	m_elements_mean_therrmo_C.SetCurSel(2);
	m_elements_average_speed_thermo_C.SetCurSel(4);

	m_mean_thermostat = m_elements_mean_therrmo_C.GetCurSel()+1;
	m_mean_aux = m_select_mean_jacket_C.GetCurSel() +1;
	m_elements_into_mean_core = m_select_media_core_C.GetCurSel() +1; // media core. Questa operazione viene anche effettuata alla partenza della misura sul Core.
	m_elements_into_average_thermospeed = m_elements_average_speed_thermo_C.GetCurSel() + 1;

	return 0;
}


void CminervaRxDlg::OnBnClickedButtonStartCoreMeasurement()
{
	
	UpdateData(TRUE);
	m_p_CDC_CORE = m_core_color_C.GetDC();
	CString text;
	
	//k6220_set_current(m_core_probe_curr, m_adr_k6220_core);
	//k6220_onoff(TRUE, m_adr_k6220_core);
		
	// configurazione del Delta
	K6220_Delta_Configuration(m_adr_k6220_core, m_core_probe_curr, TRUE);

	//avvio del triggering del Delta Mode
	
	/*Verifica che il 2182A sia in external trigger mode*/
	// text = L"SYST:COMM:SER:SEND 'trig:sour ext'"; /* prepares for external triggering */
	// write_GPIB(address, text);
	
	/* Verifica che il Delta Mode sia Armato sul 6220 */
	text = L"SOURce:DELTa:ARM?";
	write_GPIB(m_adr_k6220_core, text);

	BOOL delta_arm_status = read_GPIB(m_adr_k6220_core, &text);

	if (delta_arm_status)
	{
		text = L"INIT"; /*Starts trigger in Delta Mode*/
		write_GPIB(m_adr_k6220_core, text);
	}
	else AfxMessageBox(L"Delta Mode not ARMed on 6220");
	
	SetTimer(2001, 1000, NULL);
	m_flag_measure_core = 0;
	
	create_empty_core_mean_vector();
	create_file_core();
	manage_core_measure();
	create_core_graph();
	m_core_start_button_C.EnableWindow(FALSE);
	m_core_stop_button_C.EnableWindow(TRUE);
	m_Okay_button_C.EnableWindow(FALSE);
}


int CminervaRxDlg::k6220_set_current(double microamp, long address)
{
	CString text, text2;

	text.Format(L"CURR  %6.3g", microamp / 1000000.);
	write_GPIB(address, text);

	return 0;
}


BOOL CminervaRxDlg::k6220_onoff(bool on, long address)
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


void CminervaRxDlg::OnBnClickedButtonStopCoreMeasurement2()
{
	// TODO: Add your control notification handler code here
	// k6220_onoff(FALSE, m_adr_k6220_core);
	
	CString text = L"ABORt";
	write_GPIB(m_adr_k6220_core, text);

	text = L"SOURce:DELTa:ARM?";
	write_GPIB(m_adr_k6220_core, text);

	BOOL delta_arm_status = read_GPIB(m_adr_k6220_core, &text);
	if (!delta_arm_status)
		{
		AfxMessageBox(L"Delta Mode disARMed on Core 6220");
		}
	
	// K6220_Delta_Configuration(m_adr_k6220_core, m_core_probe_curr, FALSE);
	KillTimer(2001);
	KillTimer(2002);
	m_file_core.Close();

	for (int i = 0; i < DIM_VET_CORE; i++) // Ripulisco il vettore del core così che al prossimo riavvio dell'acquisizione dati sul core i grafici non si sovrappongano
	{
		m_vector_core[i][0] = 0;
		m_vector_core[i][1] = 0;
	}

	m_core_start_button_C.EnableWindow(TRUE);
	m_core_stop_button_C.EnableWindow(FALSE);
}


int CminervaRxDlg::manage_core_measure() /* Manages how the core measurements are handled, instantaneously and averaged out */
									 
{
	KillTimer(2001); /* sends control to timer 2002*/
	m_anti_block_core = 0;
	if (!request_data_core())
	{
		SetTimer(2001, TIMER_CORE, NULL); 
		return 0; 
	}
	
	SetTimer(2002, TIMER_CORE / 10, NULL); /* set the faster timer for check whether a new measurement is ready to be retrieved */

    //read_core();
	return 0;
}


double CminervaRxDlg::manage_core_media(double resistance) // this is a smooth average in which a vector of individual measurements
// is retained, but for one new element, for the calculation of the mean. First measurement in is also first measurement out,
// m_elements_into_mean_core measurements later

{
	if (m_elements_into_mean_core<1) return 0;
	
	CString text;

	// shifts the positions of the vector's content, by one step at each call
	int ctr = 0;
	while (ctr<m_elements_into_mean_core - 1)
	{
		m_media_core[ctr][0] = m_media_core[ctr + 1][0]; // time
		m_media_core[ctr][1] = m_media_core[ctr + 1][1]; // resistance
		ctr++;
	}
	double mean = resistance, sigma = 999, trend = 999.;
	// Calculates speed based on the current resistance (and time) relative to the previous resistance value stored in the m_media_core vector.
	trend = 60 * (resistance - m_media_core[m_elements_into_mean_core - 1][1]) / (m_seconds_continuous - m_media_core[m_elements_into_mean_core - 1][0]); /* speed, in Ohm min**-1 */
	// trend = 60*(-(resistance - m_media_core[m_elements_into_mean_core - 1][1]) / (0.04*resistance)) / (m_seconds_continuous - m_media_core[m_elements_into_mean_core - 1][0]);
	m_media_core[m_elements_into_mean_core - 1][1] = resistance; /*occhio che qui c'è stata una conversione di data type*/
	m_media_core[m_elements_into_mean_core - 1][0] = m_seconds_continuous; /* Time when resistance value was fetched by K2182A*/ 
	
	// Calculations of mean, stdev, and trend

	double accumulator = 0; // No loner used, consider deletion.

	if (m_elements_into_mean_core == 1)
	{
		m_aux_text.Format(L"%9.9f", mean);
		m_core_resistance_mean_C.SetWindowTextW(m_aux_text);
		m_aux_text.Format(L"%6.5g", sigma);
		m_core_resistance_STD_C.SetWindowTextW(m_aux_text);
	}
	else if (m_elements_into_mean_core > 1)
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
		trend = 60 * m_linear_regression.m_coefficiente_angolare /* / (.04*mean) */;
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
	m_aux_text.Format(L"%6.5g", trend);
	m_core_resistance_trend_C.SetWindowTextW(m_aux_text);

	thermo(-trend, m_p_CDC_CORE);

	save_core(m_seconds_continuous, mean, sigma, trend);


	//*p_trend_finestre[m_sensore_in_misura] = -60 *m_regressione_lineare.m_coefficiente_angolare/(.04*media);
	// UpdateData(FALSE);
	return 0;

}




BOOL CminervaRxDlg::request_data_core()
{
	CString text = L":sens:data:fres?"; /* latest pre-Math reading, when MATH is enabled. */
	//CString text = L":calc1:data:fresh?"; /* CALC1:DATA? command can be sent to read the latest (last) postmath reading processed by the Model 6220*/
	//return write_GPIB(m_adr_k2182_core, text);
	return write_GPIB(m_adr_k6220_core, text);
}


double CminervaRxDlg::read_resistance(int address,BOOL core)
{
	CString text;
	BOOL status = read_GPIB(address, &text);
	double volt = 0;
	
	if (status)
	{
		volt = wcstod(text, NULL);
	}
	
	double current = 0;
	core ? current = m_core_probe_curr : current = m_jacket_probe_current;
	double R = RESISTENZA_PONTE_WHEATSTONE;
	double i = current / 1000000.;
	double V = volt;
	double resistance = R *(i*R - 3 * V) / (V + i*R);

	return resistance;
}


double CminervaRxDlg::manage_data_core(double resistance)
{
	CString text;

	// CTime today = CTime::GetCurrentTime(); /* potrebbe non esser necessario */
	/* m_seconds_beginning_2013 = CTime(today.GetYear, today.GetMonth, today.GetDay, 0, 0, 0); */
	/* m_secondi_assoluti = CTime::GetCurrentTime(); */
	m_seconds_absolute = ((double)clock() / (double)CLOCKS_PER_SEC);

	if (m_seconds_t_zero != 0.)
	{
		// m_seconds_continuous = double(m_seconds_absolute.GetTime()) - double(m_seconds_t_zero.GetTime());
		m_seconds_continuous = m_seconds_absolute - m_seconds_t_zero;/* borrowed from Gianluca's Misura. clock() returns an integer, in milliseconds*/
	}
	else
	{
		m_seconds_t_zero = m_seconds_absolute;
		// m_seconds_continuous = m_seconds_absolute.GetTime() - m_seconds_beginning_Dec_2013.GetTime();
		// m_seconds_continuous = double(m_seconds_absolute.GetTime()) - double(m_seconds_t_zero.GetTime());
		m_seconds_continuous = m_seconds_t_zero;
	}

	manage_core_media(resistance);

	text.Format(L"%9.9f", resistance);
	m_core_resistance_C.SetWindowTextW(text);

	return resistance;
}


void CminervaRxDlg::OnBnClickedButtonProbeCurrSet2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	k6220_set_current(m_jacket_probe_current, m_adr_k6220_multi);
}


void CminervaRxDlg::OnBnClickedButtonStartThermo()
{
	
	UpdateData(TRUE);
	m_do_noting = -3;
	m_p_CDC = m_therm_color_C.GetDC();

	k6220_onoff(1, m_adr_k6220_multi);
	m_status_thermostat = INIT;
	m_old_thermo_temperature = 0;

	k_2400_onoff(TRUE, m_adr_k2400);

	if (m_seconds_t_zero == 0) // If no other graph is live
	{
		m_seconds_t_zero = ((double)clock() / (double)CLOCKS_PER_SEC);
	}
	create_empty_deltaR_thermostat_vector();
	create_thermo_graph(); 
	
	Create_Thermostat_Shield_File();
	manage_thermostat();// start reading 

	m_thermo_start_button_C.EnableWindow(FALSE);
	m_thermo_stop_button_C.EnableWindow(TRUE);
}


BOOL CminervaRxDlg::manage_thermostat() // Drives the reading of the Thermostat sensing thermistor (on channel 4)
{
	CString status;
	//switch (m_status_thermostat) // INIT, START, REQUEST, WAITING, DONE
	//	{
	//	case DONE: status = L"DONE";
	//		break;
	//	case START: status = L"START";
	//		break;
	//	case INIT: status = L"INIT";
	//		break;
	//	case WAITING: status = L"WAITING";
	//		break;
	//	case REQUEST: status = L"REQUEST";
	//		break;
	//	}
	
	//CString text;
	//text.Format(L"%s", status);
	// m_thermo_message_C.SetWindowTextW(status);

	if (m_status_thermostat == INIT)
	{	
		m_ledred_termo_medium_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		m_ledred_termo_medium_C.ShowWindow(SW_SHOW);
		m_ledred_termo_medium_C.RedrawWindow();
		m_derivative_power = DERIVATIVE_POWER;
		m_status_thermostat = START;
			
		CString text = L":ABORT";
		write_GPIB(m_adr_k2182_multi, text);
	}

	if (m_status_thermostat == START)
	{
		if (check_7001_busy())
		{
			m_ledred_termo_medium_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
			m_ledred_termo_medium_C.RedrawWindow();
			SetTimer(3000, 500, NULL);
			m_ledred_termo_medium_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON3));
			return 1;

		}

		openclose_switch(4, TRUE);
		Status_7001();
		KillTimer(3000);
		BOOL esito = request_data_multi();
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
		if (resistance!=0)
		{
			m_anti_block_multi = 0;
			m_ledred_termo_medium_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
			m_ledred_termo_medium_C.ShowWindow(SW_SHOW);
			m_ledred_termo_medium_C.RedrawWindow();

			// if (manage_mean_thermostat(resistance)) // The one that Stefano defined
			if (Manage_Thermostat_Mean(resistance)) // Defined by Massimo
			{			
				KillTimer(3000);
				m_status_thermostat = START;
				switch_open_all();
				Status_7001();
				SetTimer(3000, m_thermostat_reading_interval*1000, NULL);
			}
			else
			{
				BOOL esito = request_data_multi();
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
				request_data_multi();

				m_anti_block_multi = 0;
				SetTimer(3000, 100, NULL);

			}

		}

	}
	return 0;
}


double CminervaRxDlg::read_thermostat() /* handles repeated readings of the thermostat resistance without 
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


void CminervaRxDlg::OnCbnSelchangeComboCoreThermElements3()
{
	m_mean_thermostat = m_elements_mean_therrmo_C.GetCurSel()+1;
	return;
}


double CminervaRxDlg::read_resistance_multi(int address, BOOL send_request)
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


BOOL CminervaRxDlg::request_data_multi()
{
	CString text = L":sens:data:fres?";
	return write_GPIB(m_adr_k2182_multi, text);
}


double CminervaRxDlg::read_multi()
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


void CminervaRxDlg::OnBnClickedButtonStopThermo()
{
	int i = MessageBox(L"Are you sure that you want to \n stop aquisition on all calorimeter bodies? \n If yes, all data files will be saved and closed.", L"Calorimeter measures stop alert", MB_YESNO);
	if (i == IDYES)
	{
		m_status_thermostat = DONE;
		/*if (m_status_aux == DONE)
				 k6220_onoff(0, m_adr_k6220_multi);*/

		openclose_switch(4, FALSE);
		KillTimer(3000);
		m_file_thermo_shield.Close();

		OnBnClickedButtonStopCoreMeasurement2();
		OnBnClickedButtonStopAuxMeasurement();

		m_thermo_start_button_C.EnableWindow(TRUE);
		m_thermo_stop_button_C.EnableWindow(FALSE);

		for (int i = 0; i < DIM_VET_TERMO; i++)
		{ 
			m_vector_thermo[i][0] = 0;
			m_vector_thermo[i][1] = 0;
		}
		// ri-mettiamo anche la potenza da erogare per la termostatazione a zero
		m_power_thermostat = 0;
		UpdateData(FALSE);
	}
}


BOOL CminervaRxDlg::manage_mean_thermostat(double resistance)
{
	static int ctr = 0, discharge = 0;
	static double  integrator = 0;
	static double mean_resistance = 0;
	CString aux_text;
	aux_text.Format(L"%d / %d", ctr, m_mean_thermostat);
	m_thermostat_completed_C.SetWindowTextW(aux_text);

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
	if (resistance>0)
	{

		ctr++;
		integrator += resistance;
		mean_resistance = integrator / ctr;
		m_aux_text.Format(L"%9.9f", mean_resistance);
		m_shield_ohm_C.SetWindowTextW(m_aux_text);
		aux_text.Format(L"%d / %d", ctr, m_mean_thermostat);
		m_thermostat_completed_C.SetWindowTextW(aux_text);

		if (ctr >= m_mean_thermostat)
		{
			if (!m_thermo_freeze) // Do this unless you have frozen the PID with the proper checkbox on the thermostat settings
			{
				PID(mean_resistance); // Modify power injection or leave it as it is (while you continue reading the thermostat thermistor res. value.
			}

			discharge = 0;
			ctr = 0;
			integrator = 0;
			return 1;

		}

	}
	return 0;
}


// Per Stefano:
// In Calorimetro questa era un funzione che serviva solo a calcolare la corrente da erogare per la termostatazione. 
// Qui invece PID() vuole fare anche il lavoro di CcalorimetroDlg::gestisci_termostato(void) ? 
// NB in Calorimetro era CcalorimetroDlg::PID_medium(double delta_T,double velocita)

int CminervaRxDlg::PID(double resistance)
{
	// Stefano changed 11/2/2014
	int pippo = 0; //Comando inserito da Marco il 12/2/2014 su suggerimento di Stefano
	//// PARAMETERS FOR PID DERIVATIVE
	////
	double spec_heat = .72; /// specific heat this should be a PARAMETER (J/K g-1)
	double weight = 15.0; /// this could be a input variable (g)
	double ETA_target = m_ETA_target;  /// this should be a input vatiable (min)
    ////// END PARAMETER
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
	double milliampere = 0.;
	double power = 0.;
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

		else if (delta_T<-0.05 && /*(speed > 0. && speed < 2.) )*/ (fabs(speed)<2) && eta>0 || TRUE )  /*questa era quella di Stefano */  // Constant DERIVATIVE Mode: Slower than 2 K/min and farther away than -100 mK from target.         
		// Adds or removes power in order to maintain a constant speed, measured as temperature/time, of 0.1 K/min. 
		// 20 Genn 2014: il controllo sul segno della velocità non ha funzionato: ha ripristinato il dente di sega derivativo. Occorre tornare al fabs(speed)<2 e risolvere separatamente 
		// il problema della caduta libera da cui non si esce più.
		// NB: Aggiunto un || TRUe alla fine della condizione dell'If (suggerimento di Stefano via email del 14/2/2014) per bypassare gli altri else a valle.

		{
		// Stefano changed 11/2/2014
		////  double eta_desiderato = 20.;
		/// INIT PID DERIVATIVE
		double delta_mW = (1000000./60.)*(weight*spec_heat *delta_T)*(1./ETA_target - 1/eta);
		m_d_PID -= delta_mW; // Stefano changed 11/2/2014 
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
			double ETA_target_slow=10.;  // Stefano changed 11/2/2014
			double delta_mW = (1000000./60.)*(weight*spec_heat *delta_T)*(1./ETA_target_slow - 1/eta);

			m_d_PID -= delta_mW;  // Stefano changed 11/2/2014 

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


	// return 0;
}



int CminervaRxDlg::thermo(double speed, CDC * pCDC) // Color coding of the thermostat status
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


void CminervaRxDlg::Save_Measurements_Data(void) // Saves all measurement setup data to a SetUp file;
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
// e quella fatta in CcalorimetroDlg dove PID_medium(double delta_R,double velocita)
// e termo_medium() non sono uguali a PID(double resistance) di qui
// =================================================================================

void CminervaRxDlg::Create_Thermostat_Shield_File(void)
{
	CTime  time_now = CTime::GetCurrentTime();

	CString now = m_directory + time_now.Format(L"%Y_%m_%d_%H_%M_%S_thermostat_shield.dat");
	m_file_thermo_shield.Abort(); 
	BOOL whatsup = m_file_thermo_shield.Open(now, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (m_file_thermo_shield.m_hFile != CFile::hFileNull)
	{
		// AfxMessageBox(L"Thermostat Shield Log File Open", MB_OK | MB_ICONINFORMATION);
		add_message(L" Thermostat Shield Log File Open" + now);
		//m_file_name_C.SetWindowText(finestra_file.GetFileName());
		CString aux = L" Seconds \t deltaR \t speed (K/min) \t Power(mW) \t Sensor(ohm) \t Target(ohm) \t PID_propor \t PID_dissip\n";
		m_file_thermo_shield.WriteString(aux);
	}
	else
	{
		// AfxMessageBox(L"Could not Open Thermostat Shield Log File Open");
		add_message(L" Could not Open Thermostat Shield Log File " + now);
	}

	return;
}


unsigned long CminervaRxDlg::Write_To_File_Thermostat_Shield(double target, double sensor, double deltaR, double power, double speed)
{
	m_seconds_absolute = ((double)clock() / (double)CLOCKS_PER_SEC);
	
	 // = m_seconds_absolute.GetTime() - m_seconds_beginning_Dec_2013.GetTime();
	if (m_seconds_t_zero != 0)
	{
			m_seconds_continuous_thermostat = m_seconds_absolute - m_seconds_t_zero;
	}
	else
	{
		m_seconds_t_zero = ((double)clock() / (double)CLOCKS_PER_SEC);
		m_seconds_continuous_thermostat = m_seconds_absolute - m_seconds_t_zero;
	}
	
	if (m_file_thermo_shield.m_hFile != CFile::hFileNull)
	{
		CString aux;
		aux.Format(L" %6d \t%7.5g \t%7.5g \t%7.5g \t%12.12g \t%12.12g \t%7.5g \t%7.5g \n", m_seconds_continuous_thermostat, deltaR, speed, power, sensor, target, m_p_pid, m_d_PID);
		m_file_thermo_shield.WriteString(aux);
	}
	
	return 0;
}


int CminervaRxDlg::create_thermo_graph()
{
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
	m_grafico_termo->coordinate(0, 3600, -.001, +.001); // x-scale spanning one hour (3600 seconds). What are the +.001 and -0.001 ? 
	m_grafico_termo->cambia_colore_frame(0, 50, 0, 1);
	m_grafico_termo->CambiaColore(200, 0, 0, 2);

	m_grafico_termo->plotta_frame();

	return 0;
}

int CminervaRxDlg::plot_thermostat(double time, double delta_R)
{
	double ymin = delta_R;
	double ymax = delta_R;

	/* 1. Preparation of the vector to be plotted */

	if (m_points_vector_thermo<DIM_VET_TERMO)
	{ // If the vector is not filled yet, append the last couple of values
		m_vector_thermo[m_points_vector_thermo][0] = time;
		m_vector_thermo[m_points_vector_thermo][1] = delta_R;
		m_points_vector_thermo++;
	}
	else
	{ // if the vector has been filled, move backwards to create an empty slot for the fresh couple of values
		int ctr = 0;
		while (ctr<DIM_VET_TERMO - 1)
		{
			m_vector_thermo[ctr][0] = m_vector_thermo[ctr + 1][0];
			m_vector_thermo[ctr][1] = m_vector_thermo[ctr + 1][1];
			ctr++;
		} // append the last couple of values
		m_vector_thermo[ctr][0] = time;
		m_vector_thermo[ctr][1] = delta_R;
	}

	/* 2. Checking the axes scales, to make the plot visible 
	Might need to reverse the logic for the thermostat by fixing the x axis at the center
	of the plot and adjust the m_scale_plot_thermo */

	float scala = m_scale_plot_thermo;
	float delta;
	
	/* These conditions ensure that the current delta_R value is right at the middle of the y axis.*/
	(delta_R>0) ? delta = (delta_R*scala + 0.5) : delta = (delta_R*scala - 0.5); 
	double y_min = ((delta - 1) / double(scala));
	double y_max = ((delta + 1) / double(scala));
	/* however if the delta_R is plotted within the current limits of the thermostat plot, 
	over-ride the values just writtem and redefine y_min and y_max so that the graph does not change. */
	if (delta_R < m_grafico_termo->m_ymax && delta_R > m_grafico_termo->m_ymin)
	{ /* If the fresh value is within the maximum and the minimum value allowed in this plot (creates with min=0, max=100) 
	  make a local copy of the current plot y-scale limits */
		y_min = m_grafico_termo->m_ymin;
		y_max = m_grafico_termo->m_ymax;
	}
	m_grafico_termo->coordinate(time - 3589, time + 11, y_min, y_max);
	m_grafico_termo->x_tick_change(600);
	m_grafico_termo->y_tick_change((2. / scala) / 5.);
	m_grafico_termo->plotta_frame();
	if (m_grafico_termo->punto_plottabile(time - 3588, 0) && m_grafico_termo->punto_plottabile(time + 10, 0))
	{ /* Draw an horizontal line at the center of the graph, vertically (the set point) */
		m_grafico_termo->CambiaColore(0, 100, 0, 1);
		m_grafico_termo->plot_single_point(time - 3588, 0, TRUE);
		m_grafico_termo->plot_single_point(time + 10, 0, FALSE);
		m_grafico_termo->CambiaColore(200, 0, 0, 2);
	}
	m_grafico_termo->plot_vettore(m_vector_thermo, 0, m_points_vector_thermo - 1);
	return 0;
}

/*
	2017.04.13	
	Polymorphic plot_thermostat function, centers the graph on the x-axis if *center* is set to TRUE
	Massimo adds this function to make the plot centered on the set point right from the beginning 

*/
int CminervaRxDlg::plot_thermostat(double time, double delta_R, bool center)
{

	/* 1. Preparation of the vector to be plotted */

	if (m_points_vector_thermo<DIM_VET_TERMO)
	{ // If the vector is not filled yet, append the last couple of values
		m_vector_thermo[m_points_vector_thermo][0] = time;
		m_vector_thermo[m_points_vector_thermo][1] = delta_R;
		m_points_vector_thermo++;
	}
	else
	{ // if the vector has been filled, move backwards to create an empty slot for the fresh couple of values
		int ctr = 0;
		while (ctr<DIM_VET_TERMO - 1)
		{
			m_vector_thermo[ctr][0] = m_vector_thermo[ctr + 1][0];
			m_vector_thermo[ctr][1] = m_vector_thermo[ctr + 1][1];
			ctr++;
		} // append the last couple of values
		m_vector_thermo[ctr][0] = time;
		m_vector_thermo[ctr][1] = delta_R;
	}

	/* 2. Checking the axes scales, to make the plot visible */

	float axis_scale = m_scale_plot_thermo;
	float delta;
	(delta_R>0) ? delta = (delta_R*axis_scale + 0.5) : delta = (delta_R*axis_scale - 0.5);
	double y_min = ((delta - 1) / axis_scale);
	double y_max = ((delta + 1) / axis_scale);

	/* If _center_ is passed as TRUE, fixes the x axis at the center of the plot and adjust the m_scale_plot_thermo*/
	if (center)
		{
		y_min = -abs(long(delta_R*1.1));
		y_max = abs(long(delta_R*1.1));
		}
	/* however if the delta_R is plotted within the current limits of the thermostat plot,
	over-ride the values just writtem and redefine y_min and y_max so that the graph does not change. */
	if (delta_R < m_grafico_termo->m_ymax && delta_R > m_grafico_termo->m_ymin)
	{ 
		y_min = m_grafico_termo->m_ymin;
		y_max = m_grafico_termo->m_ymax;
	}

	m_grafico_termo->coordinate(time - 3589, time + 11, y_min, y_max);
	m_grafico_termo->x_tick_change(600);
	m_grafico_termo->y_tick_change((2. / axis_scale) / 5.);
	m_grafico_termo->plotta_frame();
	if (m_grafico_termo->punto_plottabile(time - 3588, 0) && m_grafico_termo->punto_plottabile(time + 10, 0))
	{ /* Draw an horizontal line at the center of the graph, vertically (the set point) */
		m_grafico_termo->CambiaColore(0, 100, 0, 1);
		m_grafico_termo->plot_single_point(time - 3588, 0, TRUE);
		m_grafico_termo->plot_single_point(time + 10, 0, FALSE);
		m_grafico_termo->CambiaColore(200, 0, 0, 2);
	}
	m_grafico_termo->plot_vettore(m_vector_thermo, 0, m_points_vector_thermo - 1);
	
	return 0;
}

void CminervaRxDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult) // Adjusts the scale of the shield thermistor plot. 
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	float old_scale = m_scale_plot_thermo;
	if (pNMUpDown->iDelta == 1 && m_scale_plot_thermo > 0.01)
	{
		m_scale_plot_thermo /= 10;
	}
	else if (pNMUpDown-> iDelta == -1 && m_scale_plot_thermo < 10000)
	{
		m_scale_plot_thermo *= 10;
	}
	/*CString tmp;
	tmp.Format(_T("m_scale_plot_thermo = %.5f"), m_scale_plot_thermo);
	MessageBox(tmp);*/
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


BOOL CminervaRxDlg::create_file_core()
{
	CTime  time_now = CTime::GetCurrentTime();

	CString now = m_directory + time_now.Format(L"%Y_%m_%d_%H_%M_%S_core.dat");
	m_file_core.Abort();
	BOOL whatsup = m_file_core.Open(now, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (m_file_core.m_hFile != CFile::hFileNull)
	{
		//AfxMessageBox(L"Core Log File Open", MB_OK | MB_ICONINFORMATION);
		//m_file_name_C.SetWindowText(finestra_file.GetFileName());
		CString aux = L" Seconds \tResist. (Ohm) \tSigma \tTrend (Ohm/min) \tPID freeze \n";
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


bool CminervaRxDlg::save_core(double seconds, double resistance, double sigma, double trend)
{
	
		if (m_file_core.m_hFile != CFile::hFileNull)
	{
		CString aux;
		aux.Format(L" %.3f \t%9.9g \t%7.5g \t%9.9g \t%2d \n", seconds, resistance, sigma, trend, m_thermo_freeze);
		m_file_core.WriteString(aux);
	}

		// double delta_t = (10025. - resistance) / (10025. *.04);
		// plot_core(seconds, resistance);
		plot_R(seconds, resistance);

	return false;
}


void CminervaRxDlg::OnBnClickedButtonStopShieldInject()
{
	// This function interrupts current injection toward the four shield heating thermistors
	// 14 Gennaio 2014 ore 18
	// ATTENZIONE: verificare che questa funzione interrompa l'erogazione di corrente ai shield thermistors
	k_2400_onoff(FALSE, m_adr_k2400); // stop injecting current in the four thermistors heating the shield
	// CAREFUL here because you need to ensure that power is injected by PID into the shield depending on the status of k2400
}


int CminervaRxDlg::create_core_graph()
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
}


void CminervaRxDlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
	/* This function was updated in 2017 to make the Core plot in terms of resistance Vs time. 
	Scaling is supplied by decades, on the y-axis. 
	*/
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// Adjusts the y-axis scale on the core plot
	float previous_scale = m_scale_plot_core; /* May be I need this, may be not */
	
	/* CString text;
	text.Format(L" Current core plot scale=%.5f ", m_scale_plot_core);
	add_message(text);*/

	double R = m_vector_core[m_points_vector_core - 1][1];
	double time = m_vector_core[m_points_vector_core - 1][0];

	double y_min = m_grafico_core->m_ymin;
	double y_max = m_grafico_core->m_ymax;

	double delta_y = y_max - y_min;

	if (pNMUpDown->iDelta == 1 && m_scale_plot_core > 0.001) /* Button Down pressed: zoom into the plot */
		{
		m_scale_plot_core /= 10.0;
		y_max -= 0.45 * delta_y;
		y_min += 0.45 * delta_y;
		}
		
	else if (pNMUpDown->iDelta == -1 && m_scale_plot_core < 100.) /* Button Up pressed: zoom out of the plot and increased y-scale */
		{
		m_scale_plot_core *= 10.0;
		y_max += 4.5 * delta_y; /* Magnifies the canvas by a factor of 10 on the y_scale */
		y_min -= 4.5 * delta_y;
		}
	else return; /* don't do anything if conditions were not met.*/
	 
	double upper_limit = y_min + 0.95*(y_max - y_min); /* Close to the limits of the frame as this was before the button pressed */
	double lower_limit = y_min + 0.05*(y_max - y_min);

	if (m_points_vector_core > 2)
		{
		if ( (R + 2.5 * m_scale_plot_core >= upper_limit) || (R - 2.5 * m_scale_plot_core <= lower_limit) ) /* Test condition is with the NEW m_scale_plot_core value */
			{
				y_min = R - 2.5 * m_scale_plot_core;
				y_max = R + 2.5 * m_scale_plot_core;
			}

		m_grafico_core->coordinate(time - 3589, time + 11, y_min, y_max);
		m_grafico_core->x_tick_change(600);
		// m_grafico_core->y_tick_change( (y_max - y_min) / 5. /* * m_scale_plot_core*/ ); // nuova larghezza dell'unità sulle ordinate del grafico
		m_grafico_core->y_tick_change( (y_max - y_min) / 5.); // nuova larghezza dell'unità sulle ordinate del grafico
		m_grafico_core->plotta_frame();
		}

	if (m_grafico_core->punto_plottabile(time - 3588, 0) && m_grafico_core->punto_plottabile(time + 10, 0))
	{
		m_grafico_core->CambiaColore(0, 100, 200, 1);
		m_grafico_core->plot_single_point(time - 3588, 0, TRUE);
		m_grafico_core->plot_single_point(time + 10, 0, FALSE);
		m_grafico_core->CambiaColore(0, 100, 0, 2);
	}
	m_grafico_core->plot_vettore(m_vector_aux, 0, m_points_vector_aux - 1); /* re-freshes the entire vector */
	*pResult = 0;
}

//int CminervaRxDlg::plot_R(double time, double R, double &(*graph_vector)[2], int dim, grafico_ver2 *graph)
//	{	
//	if (dim < DIM_VET_CORE)
//		{
//		graph_vector[dim][0] = time;
//		graph_vector[dim][1] = R;
//		}
//	else 
//		{
//		int ctr = 0;
//		while (ctr<DIM_VET_CORE - 1)
//		{
//			graph_vector[ctr][0] = graph_vector[ctr + 1][0];
//			graph_vector[ctr][1] = graph_vector[ctr + 1][1];
//			ctr++;
//		}

//		return 0;
//	}

int CminervaRxDlg::plot_R(double time, double R)
{
	if (m_points_vector_core<DIM_VET_CORE)
	{
		m_vector_core[m_points_vector_core][0] = time;
		m_vector_core[m_points_vector_core][1] = R;
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
		m_vector_core[ctr][1] = R;
	}

	double y_min = m_grafico_core->m_ymin;
	double y_max = m_grafico_core->m_ymax;

	double upper_limit = y_min + 0.95*(y_max - y_min); /* Close to the limits of the frame */
	double lower_limit = y_min + 0.05*(y_max - y_min);

	if (R >= upper_limit || R <= lower_limit) /* When the point being plotted is about to reach the upper or the lower limit of the frame */
		{
			y_min = R - 2.5 * m_scale_plot_core;
			y_max = R + 2.5 * m_scale_plot_core;
		}

	m_grafico_core->coordinate((long) floor(time - 3589), (long) floor(time + 11), y_min, y_max);
	m_grafico_core->x_tick_change(600);
	m_grafico_core->y_tick_change((y_max - y_min) / 5.); // Divides the vertical space in 5 blocks (plots four grid lines) 
	m_grafico_core->plotta_frame();

	if (m_grafico_core->punto_plottabile(time - 3588, 0) && m_grafico_core->punto_plottabile(time + 10, 0))
	{
		m_grafico_core->CambiaColore(0, 100, 200, 1);
		m_grafico_core->plot_single_point(time - 3588, 0, TRUE);
		m_grafico_core->plot_single_point(time + 10, 0, FALSE);
		m_grafico_core->CambiaColore(0, 0, 200, 2);
	}

	m_grafico_core->plot_vettore(m_vector_core, 0, m_points_vector_core - 1); /* re-plot the entire vector */
	
	return 1;
}




void CminervaRxDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


int CminervaRxDlg::jacket_power()
{
	static long old_time = 0;
		double volt;
		CString text;
		if (m_flag_jacket == 1)
		{
			SetTimer(4001, 100, NULL);
			m_timer_jacket = clock();
			k_2400_onoff(1, m_adr_k2400_jacket);
			m_joule_jacket = 0;
			m_flag_jacket = 2;
			old_time = 0;
		//	create_cycle_file();
		}


		long cronometer = (clock() - m_timer_jacket);
		double seconds = (double)(cronometer) / 1000.;
		text.Format(L"%6.2f", seconds);
		m_seconds_jacket_C.SetWindowTextW(text);


		volt = k_2400_read_volt(m_adr_k2400_jacket);
		text.Format(L"%g", volt);
		m_volt_jacket_C.SetWindowTextW(text);
		double micro_watt = microwatt(m_jacket_current_calibration, volt, &m_microwatt_jacket_C);
		if (m_flag_jacket == 2)
		{

			microjoule(micro_watt, cronometer,old_time,  &m_joule_jacket, &m_joule_jacket_C);
			old_time = cronometer;

			// write_file_cycle(cronometer, m_joule_core, m_micro_ampere_core, volt, 0, 0, 0);
		}

		if (seconds >= m_jacket_calibration_seconds)
		{
			k_2400_onoff(0, m_adr_k2400_jacket);
			KillTimer(4001);
			m_flag_jacket = 3;
			// m_file_cycle.Close();
			m_button_start_cycles_C.EnableWindow(TRUE);
			m_start_jacket_injection_C.EnableWindow(TRUE);
			m_Stop_Jacket_current_injection_C.EnableWindow(FALSE);
		}
	return 0;
}


void CminervaRxDlg::OnBnClickedButtonStopJacketcalibration2()
{
	k_2400_onoff(0, m_adr_k2400_jacket);
	KillTimer(4001);
	m_start_jacket_injection_C.EnableWindow(TRUE);
	m_Stop_Jacket_current_injection_C.EnableWindow(FALSE);
}


int CminervaRxDlg::poll_7001()
{
	char spr;
	BOOL esito = ibrsp(m_adr_k7001_switch, &spr);
	//m_poll = spr;
	if (ibsta & ERR)
	{

		add_message(L" Error in polling for K_7001 r ");
		return 0;
	}
	return esito;

}


void CminervaRxDlg::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here
	UINT status = BST_CHECKED&		m_CH1_C.GetState();
	openclose_switch(1,status);

}


int CminervaRxDlg::openclose_switch(int channel,BOOL status)
{
	CString text;
	if (status)
	{
		text.Format(L"CLOSE (@ 1!%d)", channel);		
	}
	else
	{
		text.Format(L"OPEN (@ 1!%d)", channel);
	}
	write_GPIB(m_adr_k7001_switch, text);
	return 0;
}


void CminervaRxDlg::OnBnClickedCheck3()
{
	// TODO: Add your control notification handler code here
	UINT status = BST_CHECKED&		m_CH2_C.GetState();
	openclose_switch(2, status);
}


void CminervaRxDlg::OnBnClickedCheck4()
{
	// TODO: Add your control notification handler code here
	UINT status = BST_CHECKED&		m_CH3_C.GetState();
	openclose_switch(3, status);
}


void CminervaRxDlg::OnBnClickedCheck5()
{
	// TODO: Add your control notification handler code here
	UINT status = BST_CHECKED&		m_CH4_C.GetState();
	openclose_switch(4, status);
}


void CminervaRxDlg::OnBnClickedCheck6()
{
	// TODO: Add your control notification handler code here
	UINT status = BST_CHECKED&		m_CH5_C.GetState();
	openclose_switch(5, status);
}


void CminervaRxDlg::OnBnClickedCheck7()
{
	// TODO: Add your control notification handler code here
	UINT status = BST_CHECKED&		m_CH7_C.GetState();
	openclose_switch(7, status);
}


void CminervaRxDlg::OnBnClickedCheck8()
{
	// TODO: Add your control notification handler code here
	UINT status = BST_CHECKED&		m_CH6_C.GetState();
	openclose_switch(6, status);
}


int CminervaRxDlg::Status_7001()
{
	write_GPIB(m_adr_k7001_switch, L":CLOS? (@ 1!1:1!8)");
	CString testo;
	read_GPIB(m_adr_k7001_switch, &testo);
	if (testo.Find(L"1") < 0)
	{
		m_ledred_switch_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
	}
	else 	m_ledred_switch_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));

	Check_mask(testo);

	return 0;
}


int CminervaRxDlg::Check_mask(CString Mask) // extracts numbers from the 7001 Status string and ticks the checkboxes
{
	LPWSTR p = Mask.GetBuffer(), p1 = NULL;
	//int *stato = new int[100];
	int length = Mask.GetLength();
	int ctr = 0;
	int k7001_status[8];
	while (ctr<8)
	{
		k7001_status[ctr] = wcstol(p, &p1, 10);
		if (m_p_status_switch[ctr+1])
			m_p_status_switch[ctr+1]->SetCheck(k7001_status[ctr]);
		if (p1>Mask.GetBuffer() + length) break;

		ctr++;
		p = p1 + 1;
	}
	return 0;
}


void CminervaRxDlg::OnBnClickedCheck10()
{
	int status = BST_CHECKED& m_enable_C.GetState();
	enable_switch(status);
}


int CminervaRxDlg::enable_switch(bool enable)
{
	int ctr = 1;
	while (ctr < 8)
	{ 
		m_p_status_switch[ctr]->EnableWindow(enable);
		ctr++;
	}
	return 0;
}


int CminervaRxDlg::switch_open_all()
{
	write_GPIB(m_adr_k7001_switch, L"OPEN ALL");
	return 0;
}


void CminervaRxDlg::OnBnClickedStaticCoreGraph2()
{
	// TODO: Add your control notification handler code here
}

///////////////////////////////////////////////////////////////////////////////////
// TUTTI REFUSI QUESTI RADIO BUTTONS? Abbiamo poi fatto ricorso al COMBOBOX invece
///////////////////////////////////////////////////////////////////////////////////

void CminervaRxDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}


void CminervaRxDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
}


void CminervaRxDlg::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code hereint 
	UpdateData(TRUE);
	m_graph_radio_C.SetWindowTextW(L"Jacket 1c");
	 
}


void CminervaRxDlg::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
}


void CminervaRxDlg::OnBnClickedRadio5()
{
	// TODO: Add your control notification handler code here
}


void CminervaRxDlg::OnBnClickedRadio6()
{
	// TODO: Add your control notification handler code here
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

void CminervaRxDlg::OnBnClickedButtonStartAuxMeasurement()
{
	UpdateData(TRUE);
	k6220_onoff(TRUE, m_adr_k6220_multi);
	m_combo_thermo_aux_C.EnableWindow(FALSE);
	m_aux_start_button_C.EnableWindow(FALSE); // Disables the button to prevent pressing again
	m_aux_stop_button_C.EnableWindow(TRUE); // Enables the STOP button
	m_Okay_button_C.EnableWindow(FALSE);
	
	// openclose_switch(m_thermo_CH_aux,TRUE);
	m_p_CDC_AUX = m_aux_color_C.GetDC();
	m_status_aux = INIT;
	manage_aux(); // Manages the measurement of the auxiliary thermistor, as defined by m_thermo_CH_aux
	create_file_aux(); // this creates the auxiliary output file where time, resistance, STD, and trend are stored.
	crea_aux_graph();
}


void CminervaRxDlg::OnCbnSelchangeCombo1()
{
	CString text;
	int pos= m_combo_thermo_aux_C.GetCurSel();
	m_combo_thermo_aux_C.GetLBText(pos, text);
	m_graph_radio_C.SetWindowTextW(text);
	if (pos < 4)
	{
		m_thermo_CH_aux = pos;
	}
	else if (pos >= 4)
	{
		m_thermo_CH_aux = pos + 1;
	}
}


void CminervaRxDlg::OnBnClickedButtonStopAuxMeasurement()
{
	for (int i = 0; i < DIM_VET_AUX; i++) // Ripulisco il vettore del termistore AUX così che al prossimo riavvio dell'acquisizione dati sul core i grafici non si sovrappongano
	{
		m_vector_aux[i][0] = 0;
		m_vector_aux[i][1] = 0;
	}

	
	openclose_switch(m_thermo_CH_aux, FALSE);
	m_combo_thermo_aux_C.EnableWindow(TRUE);
	m_aux_start_button_C.EnableWindow(TRUE); // Re-enables the start button 
	m_aux_stop_button_C.EnableWindow(FALSE); // Disables the STOP button to prevent double pressing

	m_status_aux = DONE;
	if (m_status_thermostat == DONE) // If the thermostat is also DONE, then switch off
		k6220_onoff(FALSE, m_adr_k6220_multi);
		KillTimer(5000); 
		m_file_aux.Close();

	// Se il LED del busy è rosso, resta rosso anche dopo l'arresto della misura. Questa cosa accade anche sul termostato, va 
	// corretta.
}


int CminervaRxDlg::crea_aux_graph()
{
	if (m_grafico_aux)
	{
		//m_grafico_termo->puntatoreCDC->DeleteDC();
		delete m_grafico_aux;
	}
	m_grafico_aux = new grafico_ver2;
	m_grafico_aux->assegna(&m_graph_radio_C);
	m_grafico_aux->back_ground_color[0] = 255;
	m_grafico_aux->back_ground_color[1] = 240;
	m_grafico_aux->back_ground_color[2] = 255;
	m_grafico_aux->riempi_tutto();
	m_grafico_aux->sposta_label_x_axis(5);
	m_grafico_aux->coordinate(0, 3600, -.001, +.001);
	m_grafico_aux->cambia_colore_frame(0, 50, 0, 1);
	m_grafico_aux->CambiaColore(0, 100, 0, 2);
	m_grafico_aux->plotta_frame();
	return 0;
}


void CminervaRxDlg::OnDeltaposSpinAux(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	int old_scale = m_scale_plot_aux;
	if (pNMUpDown->iDelta == 1 && m_scale_plot_aux>1)
	{
		m_scale_plot_aux /= 10;
	}
	else if (pNMUpDown->iDelta == -1 && m_scale_plot_aux<10000)
	{
		m_scale_plot_aux *= 10;
	}
	if (m_points_vector_aux>2)
	{
		double x_min = m_grafico_aux->m_xmin;
		double x_max = m_grafico_aux->m_xmax;

		double delta = m_vector_aux[m_points_vector_aux - 1][1];
		int delta_int = 0;
		(delta>0) ? delta_int = (delta*m_scale_plot_aux + .5) : delta_int = (delta*m_scale_plot_aux - .5);
		double y_min = ((delta_int - 1) / double(m_scale_plot_aux));
		double y_max = ((delta_int + 1) / double(m_scale_plot_aux));

		m_grafico_aux->coordinate(x_min, x_max, y_min, y_max);
		m_grafico_aux->x_tick_change(600);
		m_grafico_aux->y_tick_change((2. / m_scale_plot_aux) / 5.);
		m_grafico_aux->plotta_frame();
		if (m_grafico_aux->punto_plottabile(x_min, 0) && m_grafico_aux->punto_plottabile(x_max, 0))
		{
			m_grafico_aux->CambiaColore(0, 100, 0, 1);
			m_grafico_aux->plot_single_point(x_min, 0, TRUE);
			m_grafico_aux->plot_single_point(x_max, 0, FALSE);
			m_grafico_aux->CambiaColore(0, 100, 0, 2);
		}
		m_grafico_aux->plot_vettore(m_vector_aux, 0, m_points_vector_aux - 1);
	}


	*pResult = 0;

}


bool CminervaRxDlg::save_aux(long seconds, double resistance, double sigma, double trend)
{
	// static double old_time = 0., old_delta_t = 0.;


	if (m_file_aux.m_hFile != CFile::hFileNull)
	{
		CString aux;
		aux.Format(L" %6d \t%9.9g \t%7.5g \t%9.9g \n", seconds, resistance, sigma, trend);
		m_file_aux.WriteString(aux);
	}

	return false;
}

BOOL CminervaRxDlg::create_file_aux()
{
	CTime  time_now = CTime::GetCurrentTime();
	CString thermistor_name;
	int pos = m_combo_thermo_aux_C.GetCurSel();
	m_combo_thermo_aux_C.GetLBText(pos, thermistor_name);

	CString now = m_directory + time_now.Format(L"%Y_%m_%d_%H_%M_%S_") + thermistor_name + L".dat";
	m_file_aux.Abort();
	BOOL whatsup = m_file_aux.Open(now, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (m_file_aux.m_hFile != CFile::hFileNull)
	{
		//AfxMessageBox(L"Core Log File Open", MB_OK | MB_ICONINFORMATION);
		//m_file_name_C.SetWindowText(finestra_file.GetFileName());
		CString aux = L" Seconds \tResistance(Ohm) \tSigma \tTrend (Ohm/min) \n";
		m_file_aux.WriteString(aux);
	}
	else
	{
		AfxMessageBox(L"Could not Open aux Log File");
		add_message(L" Could not Open aux Log File " + now);
	}

	return TRUE
		;
}

/* Plot aux based on delta_T, now moving to resistance readings as for the other plots.

int CminervaRxDlg::plot_aux(double time, double delta_t)
{
	double ymin = delta_t;
	double  ymax = delta_t;
	if (m_points_vector_aux<DIM_VET_AUX)
	{
		m_vector_aux[m_points_vector_aux][0] = time;
		m_vector_aux[m_points_vector_aux][1] = delta_t;
		m_points_vector_aux++;
	}
	else
	{
		int ctr = 0;
		while (ctr<DIM_VET_AUX - 1)
		{
			m_vector_aux[ctr][0] = m_vector_aux[ctr + 1][0];
			m_vector_aux[ctr][1] = m_vector_aux[ctr + 1][1];
			ctr++;
		}
		m_vector_aux[ctr][0] = time;
		m_vector_aux[ctr][1] = delta_t;
	}

	int scala = m_scale_plot_aux;
	int delta;
	(delta_t>0) ? delta = (delta_t*scala + .5) : delta = (delta_t*scala - .5);
	double y_min = ((delta - 1) / double(scala));
	double y_max = ((delta + 1) / double(scala));
	if (delta_t<m_grafico_aux->m_ymax && delta_t>m_grafico_aux->m_ymin)
	{
		y_min = m_grafico_aux->m_ymin;
		y_max = m_grafico_aux->m_ymax;

	}
	m_grafico_aux->coordinate(time - 3589, time + 11, y_min, y_max);
	m_grafico_aux->x_tick_change(600);
	m_grafico_aux->y_tick_change((2. / scala) / 5.);
	m_grafico_aux->plotta_frame();
	if (m_grafico_aux->punto_plottabile(time - 3588, 0) && m_grafico_aux->punto_plottabile(time + 10, 0))
	{
		m_grafico_aux->CambiaColore(0, 100, 200, 1);
		m_grafico_aux->plot_single_point(time - 3588, 0, TRUE);
		m_grafico_aux->plot_single_point(time + 10, 0, FALSE);
		m_grafico_aux->CambiaColore(0, 100, 0, 2);
	}
		
	m_grafico_aux->plot_vettore(m_vector_aux, 0, m_points_vector_aux - 1);
	return 1;
}
*/

int CminervaRxDlg::plot_aux(double time, double R)
{
	if (m_points_vector_aux < DIM_VET_AUX)
	{
		m_vector_aux[m_points_vector_aux][0] = time;
		m_vector_aux[m_points_vector_aux][1] = R;
		m_points_vector_aux++;
	}
	else
	{
		int ctr = 0;
		while (ctr<DIM_VET_AUX - 1)
		{
			m_vector_aux[ctr][0] = m_vector_aux[ctr + 1][0];
			m_vector_aux[ctr][1] = m_vector_aux[ctr + 1][1];
			ctr++;
		}
		m_vector_aux[ctr][0] = time;
		m_vector_aux[ctr][1] = R;
	}

	double y_min = m_grafico_aux->m_ymin;
	double y_max = m_grafico_aux->m_ymax;

	double upper_limit = y_min + 0.95*(y_max - y_min); /* Close to the limits of the frame */
	double lower_limit = y_min + 0.05*(y_max - y_min);

	if (R >= upper_limit || R <= lower_limit) /* When the point being plotted is about to reach the upper or the lower limit of the frame */
	{
		y_min = R - 2.5 * m_scale_plot_aux;
		y_max = R + 2.5 * m_scale_plot_aux;
	}

	m_grafico_aux->coordinate((long) floor(time - 3589), (long) floor(time + 11), y_min, y_max);
	m_grafico_aux->x_tick_change(600);
	m_grafico_aux->y_tick_change((y_max - y_min) / 5.); // Divides the vertical space in 5 blocks (plots four grid lines) 
	m_grafico_aux->plotta_frame();

	if (m_grafico_aux->punto_plottabile(time - 3588, 0) && m_grafico_aux->punto_plottabile(time + 10, 0))
	{
		m_grafico_aux->CambiaColore(0, 100, 200, 1);
		m_grafico_aux->plot_single_point(time - 3588, 0, TRUE);
		m_grafico_aux->plot_single_point(time + 10, 0, FALSE);
		m_grafico_aux->CambiaColore(0, 0, 200, 2);
	}

	m_grafico_aux->plot_vettore(m_vector_aux, 0, m_points_vector_aux - 1); /* re-plot the entire vector */

	return 1;
}

int CminervaRxDlg::plot_core(double time, double resistance)
{
	if (m_points_vector_core<DIM_VET_CORE)
	{
		m_vector_core[m_points_vector_core][0] = time;
		m_vector_core[m_points_vector_core][1] = resistance;
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
		m_vector_core[ctr][1] = resistance;
	}

	// portion commented, as tested on Calorimetro Co60 in May 2017
	// Questo era il vecchio modo di graficare i dati di deltaT, centrati intorno allo zero.
	/* int scala = m_scale_plot_core;
	int delta;
	(resistance>0) ? delta = (resistance*scala + .5) : delta = (resistance*scala - .5); */

	double y_min;
	double y_max;

	if (m_points_vector_core > 2)
	{

		if ((resistance + 2.5*m_scale_plot_core) < m_grafico_core->m_ymax && (resistance - 2.5*m_scale_plot_core) > m_grafico_core->m_ymin)
			// The current R values is plottable on the canvas given the current m_scale_plot_core value.
		{
			y_min = m_grafico_core->m_ymin; /*copies the current graph limits to the local variables y_min and y_max*/
			y_max = m_grafico_core->m_ymax;
		}
		else
		{
			// y_min = R*(1 - 0.25*m_scale_plot_core); /* Re-defines y_min and y_max around the center current value of R */
			// y_max = R*(1 + 0.25*m_scale_plot_core);
			y_min = resistance - 2.5 * m_scale_plot_core;
			y_max = resistance + 2.5 * m_scale_plot_core;
		}

		/*
		double y_min = ((delta - 1) / double(scala));
		double y_max = ((delta + 1) / double(scala));
		if (resistance<m_grafico_core->m_ymax && resistance>m_grafico_core->m_ymin)
		{
		y_min = m_grafico_core->m_ymin;
		y_max = m_grafico_core->m_ymax;

		}
		*/
		m_grafico_core->coordinate((long)floor(time - 3589), (long)floor(time + 11), y_min, y_max);
		m_grafico_core->x_tick_change(600);
		/* m_grafico_core->y_tick_change((2. / scala) / 5.); */
		m_grafico_core->y_tick_change(((y_max - y_min)) / 5.); // Divides the vertical space in 5 blocks (plots four grid lines) 
		m_grafico_core->plotta_frame();
		if (m_grafico_core->punto_plottabile(time - 3588, 0) && m_grafico_core->punto_plottabile(time + 10, 0))
		{
			m_grafico_core->CambiaColore(0, 100, 200, 1);
			m_grafico_core->plot_single_point(time - 3588, 0, TRUE);
			m_grafico_core->plot_single_point(time + 10, 0, FALSE);
			m_grafico_core->CambiaColore(0, 0, 200, 2);
		}

		m_grafico_core->plot_vettore(m_vector_core, 0, m_points_vector_core - 1);
	}
	return 1;
}


// Drives the reading of one auxiliary thermistor via the 7001 switch
BOOL CminervaRxDlg::manage_aux()
{
	if (m_status_aux == INIT)
	{
		m_ledred_therm_aux_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		m_ledred_therm_aux_C.ShowWindow(SW_SHOW);
		m_ledred_therm_aux_C.RedrawWindow();
		m_status_aux = START;
		
		// AlTRE INIZIALIZZAZIONI GRAFICO ECC ECC 
	}

	if (m_status_aux == START)
	{
		BOOL busy = check_7001_busy();
		if (busy)
		{
			m_ledred_therm_aux_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON3));
			SetTimer(5000, 500, NULL);
			return(1);
		}
		// prova per superare l'impasse di 10 secondi al lancio della funzione
		//CString text = L":ABORT";
		//write_GPIB(m_adr_k2182_multi, text);
		// fine prova: 13/06 la prova sembra riuscita perché non occorre attendere 10 secondi perché si verifichi m_anti_block_aux > 100  

		openclose_switch(m_thermo_CH_aux, TRUE);
		Status_7001();
		KillTimer(5000);
		request_data_multi();
		m_ledred_therm_aux_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		m_ledred_therm_aux_C.ShowWindow(SW_SHOW);
		m_ledred_therm_aux_C.RedrawWindow();
		m_status_aux = WAITING;
		SetTimer(5000, 100, NULL);
		m_anti_block_aux = 0;

	}
	else if (m_status_aux == WAITING)
	{
		double resistance = read_aux();
		if (resistance!=0)
		{
			m_anti_block_aux = 0;
			m_ledred_therm_aux_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
			m_ledred_therm_aux_C.ShowWindow(SW_SHOW);
			m_ledred_therm_aux_C.RedrawWindow();

			if (manage_mean_aux(resistance)) // Se la media è stata correttamente effettuata con il numero di punti desiderato
			{ // uscita dal timer "breve" e apertura di tutti i canali dello switch. Ritorno al timer "lungo". 
				KillTimer(5000);
				m_seconds_absolute = ((double) clock() / (double) CLOCKS_PER_SEC);
				
				double seconds; // = m_seconds_absolute.GetTime() - m_seconds_beginning_Dec_2013.GetTime(); // Quessta era la struttura in brachiterapia.
				if (m_seconds_t_zero != 0) // Check whether m_seconds_t_zero was initiated by another process in another body of the calorimeter
				{
					seconds = m_seconds_absolute - m_seconds_t_zero;
				}
				else
				{
					m_seconds_t_zero = ((double) clock() / (double) CLOCKS_PER_SEC);
					seconds = m_seconds_absolute - m_seconds_t_zero;
				}

				/* metti qui la definizione del trend ed il thermo_plot */

				// static double old_time = 0. , old_delta_t = 0.;
				double speed = 0.;
								
				speed = 60 * (resistance - m_vector_aux[m_points_vector_aux - 1][1]) / (seconds - m_vector_aux[m_points_vector_aux - 1][0]);
				// speed = 60 * (resistance - m_media_core[m_elements_into_mean_core - 1][1]) / (m_seconds_continuous - m_media_core[m_elements_into_mean_core - 1][0]); /* speed, in Ohm min**-1 */
				// double delta_t = (9735.5 - /*resistance*/ m_mean_resistance_aux) / (9735.5 * .04);
				m_aux_text.Format(L"%6.3g ", speed);
				plot_aux(seconds, m_mean_resistance_aux);
				m_aux_speed_C.SetWindowText(m_aux_text);
				thermo(- speed, m_p_CDC_AUX); 

				//if (old_time > 0)
				//{
				//	speed = 60/*000*/ * (delta_t - old_delta_t) / (seconds - old_time); // 60000: convertion factor from milliseconds to minutes. Speed is given in Kelvin / minute
				//	m_aux_text.Format(L"%6.3g ", speed);
					//termo(speed, p_termo);
				//	m_aux_speed_C.SetWindowText(m_aux_text);
				//	thermo(speed, m_p_CDC_AUX);
				// }
				m_aux_text.Format(L"%9.9f", m_mean_resistance_aux);
				m_aux_ohm_C.SetWindowTextW(m_aux_text);
				//old_time = seconds;
				// old_delta_t = delta_t;

				save_aux(seconds, m_mean_resistance_aux, 0, speed); 
								
				m_status_aux = START;
				switch_open_all();
				Status_7001();
				SetTimer(5000, m_aux_reading_interval * 1000, NULL); 
			}
			else
			{
				request_data_multi();
				m_ledred_therm_aux_C.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
				m_ledred_therm_aux_C.ShowWindow(SW_SHOW);
				m_ledred_therm_aux_C.RedrawWindow();
			}

		}
		else
		{
			if (m_anti_block_aux > 100) // 13/06/2014 all'avvio della misura sul termistore  aux sembra che si passi sempre prima per di qui. 
				// questo significherebbe che per i primi 10 secondi (0.1 s * 100) non c'è nessuna misura pronta.  VEDI if (m_status_aux == INIT) sopra.
			{
				KillTimer(5000);
				CString text = L":ABORT";
				write_GPIB(m_adr_k2182_multi, text);
				m_status_aux = WAITING;
				request_data_multi();

				m_anti_block_aux = 0;
				SetTimer(5000, 100, NULL);

			}

		}

	}
	return 0;
}


// this function returns the resistance value read on the auxiliary thermistor
double CminervaRxDlg::read_aux()
{
	char spr;
	BOOL esito = ibrsp(m_adr_k2182_multi, &spr);
	double resistance = 0;
	m_anti_block_aux++;

	BOOL pronto = spr & 16;
	if (pronto)
	{
		resistance = read_resistance(m_adr_k2182_multi, FALSE);
		m_anti_block_aux = 0;
	}

	m_aux_text.Format(L"%d", m_anti_block_aux);
	m_antiloop_aux_C.SetWindowTextW(m_aux_text); // shows on screen

	return resistance;
}


// manages the mean of the resistance values read on the auxiliary thermistor
BOOL CminervaRxDlg::manage_mean_aux(double resistance)
{
	static int ctr = 0, discharge = 0;
	static double  integrator = 0.;
	static double mean_resistance = 0.;
	CString aux_text;
	if (m_status_aux == INIT)
	{
		ctr = 0;
		integrator = 0;
		discharge = 0;
		return 0;
	}

	if (discharge < m_skip_points_aux)
	{
		discharge++; // una volta che discharge ha raggiunto il valore di m_skip_points_aux che cosa me ne faccio? Apparentemente nulla. Rivedi.
		return 0;
	}

	if (resistance>0)
	{
		ctr++;
		integrator += resistance;
		m_mean_resistance_aux = integrator / ctr;
		aux_text.Format(L"%d / %d", ctr, m_mean_aux);
		m_aux_show_completed_C.SetWindowTextW(aux_text);
		// mean_resistance = integrator / ctr;
		// m_mean_resistance_aux = mean_resistance;
		// m_aux_text.Format(L"%9.9f", mean_resistance);
		

		if (ctr >= m_mean_aux)
		{
			discharge = 0;
			ctr = 0;
			integrator = 0;
			return 1;
		}
	}
	return 0;
}


void CminervaRxDlg::OnBnClickedButtonSetValuesAux()
{
	UpdateData(TRUE);
}


void CminervaRxDlg::OnCbnSelchangeComboCoreThermElements2()
{
	m_mean_aux = m_select_mean_jacket_C.GetCurSel() + 1;
	return;
}


// checks whether any channel on 7001 is busy
int CminervaRxDlg::check_7001_busy(CString Mask)
{
	LPWSTR p = Mask.GetBuffer(), p1 = NULL;
	//int *stato = new int[100];
	int length = Mask.GetLength();
	int ctr = 0;
	int k7001_status[8];
	while (ctr<8)
	{
		k7001_status[ctr] = wcstol(p, &p1, 10);
		/*if (m_p_status_switch[ctr + 1])
			m_p_status_switch[ctr + 1]->SetCheck(k7001_status[ctr]);*/
		if (k7001_status[ctr] == 1) return 1;

		if (p1>Mask.GetBuffer() + length) break;

		ctr++;
		p = p1 + 1;
		
	}
	return 0;
}


// polimorfismo per verificare solo se lo swtich è occupato 
int CminervaRxDlg::Status_7001(CString busy)
{
	write_GPIB(m_adr_k7001_switch, L":CLOS? (@ 1!1:1!8)");
	//CString testo;
	read_GPIB(m_adr_k7001_switch, &busy);
		return check_7001_busy(busy);
}


BOOL CminervaRxDlg::check_7001_busy()
{
	CString busy;
	write_GPIB(m_adr_k7001_switch, L":CLOS? (@ 1!1:1!8)");
	//CString testo;
	read_GPIB(m_adr_k7001_switch, &busy);
	int esito=busy.Find(L"1");
	return (esito>=0);
}


void CminervaRxDlg::OnCheckboxClickedFreezePID()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}


void CminervaRxDlg::OnBnClickedSaveThermoSettings()
{
	// Save Settings to a user specified file.
	// these were all written in a version of Minerva that caused a crash. 
	// Writes thermostat settings to a *.thermodat file.
	UpdateData(TRUE);
	const int bufferSize = 1024;
	CTime time = CTime::GetCurrentTime();
	CString ThermoSettingsfileName = m_directory + time.Format("%Y_%m_%d_%H_%M_%S_thermosettings.thermodat");
	wchar_t* p = ThermoSettingsfileName.GetBuffer(bufferSize);

	CString sDummy(L"Specify Thermostat Settings File");
	CFileDialog dlgFile(FALSE, NULL, sDummy, OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST, NULL, this);

	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrFile = p; // Attaches the full path plus the file name, to the CString ThermoSettingsfileName, via the pointer p.
	ofn.lpstrInitialDir = m_directory; // Starts searching in the Minerva_runs directory 
	CString Text;

	if (dlgFile.DoModal() == IDOK) // This launches the actual Save As File Dialog 
	{
		CStdioFile SetUpFile;
		//	CFileException fileException; // Stores any error messages
		// SetUpFile.Abort();
		BOOL whatsup = SetUpFile.Open(ThermoSettingsfileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone, NULL);
		if (!whatsup)
		{
			Text.Format(L" Cannot Create File %s", ThermoSettingsfileName);
			//Text.Format(L" Cannot Create File %s, error: %u", ThermoSettingsfileName, fileException.m_cause);
			AfxMessageBox(Text);
		}
		else
		{
			Text.Format(L"%g, %g, %g, %g, %g, %i, %i, %i, %g,\n", m_set_point, m_p_pid, m_I_PID, m_d_PID, m_ETA_target
				, m_thermostat_reading_interval, m_skip_points_thermostat, m_mean_thermostat, m_jacket_probe_current);
			SetUpFile.WriteString(Text);
			SetUpFile.Close();
		}
		/* ThermoSettingsfileName.ReleaseBuffer();
		Text.ReleaseBuffer(); */
	}

}


void CminervaRxDlg::OnBnClickedButtonReadThermo()
{
	const int bufferSize = 1024;
	CString ThermoSettingsfileName = L"DummyThermoFile.dat";
	wchar_t* p = ThermoSettingsfileName.GetBuffer(bufferSize);

	CString sDummy(L"Specify Thermostat Settings File");
	
	/* Defines the types of files to be displayed in the directory, defaults to ".thermodat" 
	See https://docs.microsoft.com/en-us/cpp/mfc/reference/cfiledialog-class */
	TCHAR szFilters[] = _T("Thermosettings (*.thermodat)|*.thermodat|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("Thermosettings"), _T("*.thermodat"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrFile = p; // Attaches the full path plus the file name, to the CString ThermoSettingsfileName, via the pointer p.
	ofn.lpstrInitialDir = m_directory; // Starts searching in the Minerva_runs directory 

	
	CString Text;

	if (dlgFile.DoModal() == IDOK) // This launches the actual Open File Dialog 
	{
		CStdioFile SetUpFile;
		CFileException fileException; // Stores any error messages
		CString strBuff; // Where the file content will be streamed into, once opened; 

		SetUpFile.Abort();
		BOOL whatsup = SetUpFile.Open(ThermoSettingsfileName, CFile::modeRead, &fileException);
		if (!whatsup)
		{
			Text.Format(L" Cannot Read %s, error: %u", ThermoSettingsfileName, fileException.m_cause);
			AfxMessageBox(Text);
		}
		else
		{ // Extracts all settings from file and updates the control variables. 
			SetUpFile.ReadString(strBuff);
			SetUpFile.Close();
			// Extracting Set Point, P, I, D, Target ETA, Time Interval, Skip points, Elements in Mean, Ss1b probe current, 
			int virgola = 0;
			CString SetPoint, PID_P, PID_I, PID_D, Target_ETA, Time_interval, Skip_points, Elements_in_mean, Ss1b_probe_current;

			virgola = strBuff.Find(',', 0);
			SetPoint = strBuff.Left(virgola);
			m_set_point = wcstod(SetPoint, NULL);

			strBuff = strBuff.Right(strBuff.GetLength() - virgola - 1); // now moves to the right
			virgola = strBuff.Find(',', 0);
			PID_P = strBuff.Left(virgola);
			m_p_pid = wcstod(PID_P, NULL);

			strBuff = strBuff.Right(strBuff.GetLength() - virgola - 1);
			virgola = strBuff.Find(',', 0);
			PID_I = strBuff.Left(virgola);
			m_I_PID = wcstod(PID_I, NULL);

			strBuff = strBuff.Right(strBuff.GetLength() - virgola - 1);
			virgola = strBuff.Find(',', 0);
			PID_D = strBuff.Left(virgola);
			m_d_PID = wcstod(PID_D, NULL);

			strBuff = strBuff.Right(strBuff.GetLength() - virgola - 1);
			virgola = strBuff.Find(',', 0);
			Target_ETA = strBuff.Left(virgola);
			m_ETA_target = wcstod(Target_ETA, NULL);

			strBuff = strBuff.Right(strBuff.GetLength() - virgola - 1);
			virgola = strBuff.Find(',', 0);
			Time_interval = strBuff.Left(virgola);
			m_thermostat_reading_interval = wcstoul(Time_interval, NULL, NULL);

			strBuff = strBuff.Right(strBuff.GetLength() - virgola - 1);
			virgola = strBuff.Find(',', 0);
			Skip_points = strBuff.Left(virgola);
			m_skip_points_thermostat = wcstoul(Skip_points, NULL, NULL);

			strBuff = strBuff.Right(strBuff.GetLength() - virgola - 1);
			virgola = strBuff.Find(',', 0);
			Elements_in_mean = strBuff.Left(virgola);
			m_elements_mean_therrmo_C.SetCurSel(wcstoul(Elements_in_mean, NULL, NULL) - 1);
			m_mean_thermostat = m_elements_mean_therrmo_C.GetCurSel() + 1;

			strBuff = strBuff.Right(strBuff.GetLength() - virgola - 1);
			virgola = strBuff.Find(',', 0);
			Ss1b_probe_current = strBuff.Left(virgola);
			m_jacket_probe_current = wcstod(Ss1b_probe_current, NULL);

			// Final operations: data updating.
			UpdateData(FALSE); // flushes to screen all values in memory
			k6220_set_current(m_jacket_probe_current, m_adr_k6220_multi); // sets current value to K6220, but without turning any current on.

		}

		// Commento queste robe qui sotto che tanto non servono: all'uscita da questa funzione tutto questo verrà comunque distrutto
		/* ThermoSettingsfileName.ReleaseBuffer();
		Text.ReleaseBuffer();*/
	}
}


// funzione creata da Massimo per esonerare PID(resistance) da compiti che non dovrebbe assolvere
BOOL CminervaRxDlg::Manage_Thermostat_Mean(double resistance)
{
	static int ctr = 0, discharge = 0;
	static double  integrator = 0.;
	static double mean_resistance = 0;
	CString aux_text;
	if (m_status_thermostat == INIT)
	{
		ctr = 0;
		aux_text.Format(L"%d / %d", ctr, m_mean_thermostat);
		m_thermostat_completed_C.SetWindowTextW(aux_text);
		integrator = 0;
		discharge = 0;
		return 0;
	}

	if (discharge < m_skip_points_thermostat)
	{
		discharge++;
		return 0;
	}
	if (resistance>0)
	{
		ctr++;
		integrator += resistance;
		mean_resistance = integrator / ctr;
		m_aux_text.Format(L"%9.9f", mean_resistance);
		m_shield_ohm_C.SetWindowTextW(m_aux_text);
		aux_text.Format(L"%d / %d", ctr, m_mean_thermostat);
		m_thermostat_completed_C.SetWindowTextW(aux_text);

		if (ctr >= m_mean_thermostat) // If the number of prescribed measurements is complete, go ahead with plotting and saving. 
			// if requested, re-calculate the current injection via PID(resistance, deltaT, speed).
		{
			// definition of local variables for output to thermostat file and to graph, and call to PID() unless 'frozen'; 
			static long old_time = 0;
			static double thermospeed = .1;
			long time = clock();
			// double error = m_set_point - resistance;
			// double delta_T = (((m_set_point - resistance) / fabs(m_set_point)) / 0.04);
			double delta_R = m_set_point - mean_resistance /*resistance*/;
			m_aux_text.Format(L"%g", delta_R);
			m_delta_k_C.SetWindowText(m_aux_text);
			if (m_old_thermo_resistance) // Calcolo della velocità istantanea (ultime due misure)
			{ 
				// thermospeed = 60000 * (delta_T - m_old_thermo_temperature) / (time - old_time); // 60000: convertion factor from milliseconds to minutes. Speed is given in Kelvin / minute
				thermospeed = 60000 * (delta_R - m_old_thermo_resistance) / (time - old_time); /* thermostat speed in delta_R /min */
				m_aux_text.Format(L"%6.3g ", thermospeed);
				//termo(speed, p_termo);
				m_speed_shield_C.SetWindowText(m_aux_text);
				thermo(thermospeed, m_p_CDC);
			}
			m_old_thermo_resistance = /*delta_T*/ delta_R; 
	
			m_aux_text.Format(L"%6.5g", m_power_thermostat); // occhio che power deve essere aggiornato anche da PID, se questo viene chiamato;
			m_microW_shield_C.SetWindowTextW(m_aux_text);

			// August 6, 2014
			// Massimo is making changes here: first one updates the vector with the delta_T and times, then calculates integral and derived quantities to be passed over to PID();

			Write_To_File_Thermostat_Shield(m_set_point, resistance, delta_R, m_power_thermostat, thermospeed); // Handles the thermostat log file
			plot_thermostat(m_seconds_continuous_thermostat, delta_R); // Handles the thermostat plot, adding the current point to the graph.
			// plot_thermostat(m_seconds_continuous_thermostat, error, true); // Handles the thermostat plot, adding the current point to the graph.
			manage_thermo_deltaR_vector(delta_R, m_seconds_continuous_thermostat);  // Copies current delta_R and time inside the deltaR_vector;
				// This is useful also to calculate the average speed of the last N points, for the derivative term of PID
				// it is also useful if you need to make an integration of delta_R, for the implementation of the integral part of PID().

			if (m_deltaR_thermostat[0][0] != 0) // If all delta_R vector's positions have been filled, the vector is ready for averageing its contents.
			{
				m_linear_regression.calcola_regressione(m_deltaR_thermostat, 0, m_elements_into_average_thermospeed - 1);
				m_average_thermospeed = 60 * m_linear_regression.m_coefficiente_angolare; /* pendenza del fit lineare, dato in Ohm / minuto*/
				m_aux_text.Format(L"%6.5g", m_average_thermospeed);
				m_average_speed_shield_C.SetWindowTextW(m_aux_text);
			}
			
			if (!m_thermo_freeze) // Do this unless you have frozen the PID with the proper checkbox on the thermostat settings
			{
				// PID(mean_resistance); // this was the call to the old PID function (until July 2014); 

				if (m_average_thermospeed == 999) // If the average speed has not been calculated yet
					//PID(mean_resistance, delta_T, thermospeed);  
					PID_2017(mean_resistance, delta_R, thermospeed); // call PID() with instantaneous speed
				else PID_2017(mean_resistance, delta_R, m_average_thermospeed); // otherwise call PID() with average thermostat speed.
			}
			old_time = time;
			discharge = 0;
			ctr = 0;
			integrator = 0;
			return 1;
		}
	}
	return 0;
}


// polymorphic PID function, created by Massimo to isolate some features of PID(resistance) that are now managed by Manage_Thermostat_Mean(resistance)
int CminervaRxDlg::PID(double resistance, double delta_T, double speed)
{
	
	//// PARAMETERS FOR PID DERIVATIVE
	double spec_heat = .72; /// specific heat this should be a PARAMETER (J/K g-1)
	double weight = 15.0; /// this could be a input variable (g)
	double ETA_target = m_ETA_target;  /// this should be a input vatiable (min)
	////// END PARAMETER

	long old_time = m_old_time;
	m_old_thermo_temperature = delta_T;
	double thermostat_resistance = RESISTANCE_THERMOSTAT;
	double milliampere = 0.;
	double power = m_power_thermostat;
	double eta = -delta_T / speed;
	if (m_do_noting < 0) // m_do_nothing is initialized to -3 when the thersmotat is started
	{
		m_do_noting++;
		m_aux_text.Format(L"Do Nothing, %g min", int(eta));
		m_ETA_C.SetWindowText(m_aux_text);
		m_ETA_C.UpdateWindow();
		if (m_do_noting < -1)
		{
			power = m_d_PID;
		}
		else
		{
			power = m_d_PID - 10. * m_p_pid*delta_T; // Last shot under this condition, with a hint of proportionality that now kicks int.
		}
	}	
	else if (delta_T < -0.05 && /*(speed > 0. && speed < 2.) )*/ (fabs(speed)<2) && eta > 0 || TRUE)  /*questa era quella di Stefano */  // Constant DERIVATIVE Mode: Slower than 2 K/min and farther away than -100 mK from target.         
		// Adds or removes power in order to maintain a constant speed, measured as temperature/time, of 0.1 K/min. 
		// 20 Genn 2014: il controllo sul segno della velocità non ha funzionato: ha ripristinato il dente di sega derivativo. Occorre tornare al fabs(speed)<2 e risolvere separatamente 
		// il problema della caduta libera da cui non si esce più.
		// NB: Aggiunto un || TRUe alla fine della condizione dell'If (suggerimento di Stefano via email del 14/2/2014) per bypassare gli altri else a valle.
		// Il true è stato tolto da Massimo il primo di Agosto 2014 per cercare di rendere il PID meno nervoso alla fine di ciascun run di irraggiamento.

		{
		
		/// INIT PID DERIVATIVE
		double K_d = 0.5; // August 4, 2014. Derivative term coefficient, for manual tuning. 
		double delta_mW = K_d * (1000000. / 60.)*(weight*spec_heat *delta_T)*(1. / ETA_target - 1 / eta); // 60 converts minutes to seconds, 1000 converts from W to mW.
		m_d_PID -= delta_mW; // Stefano changed 11/2/2014 
		// if (fabs(delta_T) <= 1e-4) power = m_d_PID - 1. * m_p_pid*delta_T; // smaller proportional changes when temp within 100 uK
		/*else*/ 
		power = m_d_PID - 10 * m_p_pid*delta_T;
		
		//power = m_d_PID;
		m_aux_text.Format(L" Derivative, %g min", eta); // Qui si commenta così ma in realtà sta variando contemporaneamente il termine derivativo 
		// e quello proporzionale. Il senso è che il proporzionale non va mai via, ma qui viene cambiato anche il derivativo.
		m_ETA_C.SetWindowTextW(m_aux_text);
		m_ETA_C.UpdateWindow();
		
		m_aux_text.Format(L"%g", -delta_mW); // Displays power, in mW, subtracted from the derivative PID term.
		m_delta_uW_shield_C.SetWindowTextW(m_aux_text);
		m_delta_uW_shield_C.UpdateWindow();
		UpdateData(FALSE);
		// Potremmo dover metter qui un controllo che faccia uscire il software dalla caduta libera, in PID Derivative mode. 
		}
	else if (delta_T <- 0.1 && speed >= 2. /*fabs(speed)>=2.*/) // It positive speed too high then power off
		{
		power = 0;
		m_ETA_C.SetWindowTextW(L" Going up too fast, power off "); // Trying to identify what switches off power. Wasn't this though.
		m_ETA_C.UpdateWindow();
		}
	else
		{
		if (((delta_T>0 && speed>0) || fabs(speed) < 0.00001 || eta < -30. || (delta_T < 0 && speed < 0)) && (fabs(delta_T) < 0.01) /* Massimo, August 1, 2014*/) 
			{
			// CONDITIONS that access the DISSIPATIVE routine. Temperature within 10 mK from target AND ANY of the following
			// 1) Temperature greater than set point and still rising
			// 2) Speed below 10 microK / min which means that you have reached a steady state (too low may be??)
			// 3) Temperature below set point, positive speed and time of arrival greater than 30 min
			// 4) Temperature below set point and negative temperature speed (falling temperature away from set point)

			double fattore = 1;  // fattore  // Stefano changed 5 to 1 for smoothing 
			if (fabs(delta_T) < .001) fattore = .5; // scaling factor becomes 10x smaller if temperature within 1 mK from target (higher or lower) // Stefano changed .5 to .1 for smoothing 
			if (fabs(delta_T) < .0001) fattore = .1; 
			//		if (delta_T/velocita<-5) fattore*=-1;
			double delta_mW = fattore*m_I_PID*delta_T*(clock() - old_time) / 60000.; // INTEGRAL MODE;  dimensions: [fattore] * [m_I_PID] * K * min  
			m_d_PID -= delta_mW; // integral correction

			//		int pippo = m_tempo_termostato;
			m_aux_text.Format(L"%g", m_d_PID);
			m_PID_D_C.SetWindowText(m_aux_text);
			m_aux_text.Format(L" Dissipative, %g min", eta);
			m_ETA_C.SetWindowText(m_aux_text);
			m_ETA_C.UpdateWindow();

			}
		else if (eta < 10. && FALSE) // If ETA is within 10 minutes? May need to re-write this to consider what happens when either DeltaT>0 or speed<0
			// cambiato da -10 a -20: la procedura di slowing avviene per tempi più lunghi.
			{
			// m_d_PID += .1*m_I_PID*delta_T*(clock() - old_time) / 60000; /* il coefficiente moltiplicativo era .5 fino al 21 Genn 2014*/
			double ETA_target_slow = 10.;  // Stefano changed 11/2/2014
			double delta_mW = (1000000. / 60.)*(weight*spec_heat *delta_T)*(1. / ETA_target_slow - 1. / eta);

			m_d_PID -= delta_mW;  // Stefano changed 11/2/2014 

			// if (delta_T > 0) m_d_PID *= -1.; // Massimo e Marco: 16/01/2014 proviamo a vedere se, superato il set point, in questo modo ci scendiamo di nuovo.
			m_aux_text.Format(L"%g", m_d_PID);
			m_PID_D_C.SetWindowText(m_aux_text);

			m_aux_text.Format(L"Slowing, %g min", eta);
			m_ETA_C.SetWindowText(m_aux_text);
			m_ETA_C.UpdateWindow();
			}
		else
			{
			m_aux_text.Format(L" Prop., %g min", eta); // this is proportional because only the instruction below will be changed. 
			m_ETA_C.SetWindowText(m_aux_text);
			m_ETA_C.UpdateWindow();
			}

		power = m_d_PID - 10 * m_p_pid * delta_T; // Derivative and proportional term; This is always executed within this last "major" else scope.
	}


	if (power>0)
	{
		milliampere = sqrt(power / thermostat_resistance);
		m_power_thermostat = power; // power goes global
	}
	else milliampere = 0;

	milliampere = min(milliampere, 1.5); // Massimo e Marco: Setting maximum injection current to 1.5 mA
	m_aux_text.Format(L"%6.5g", power);
	m_microW_shield_C.SetWindowTextW(m_aux_text);
	m_aux_text.Format(L"%6.5g", milliampere); // the value of mA that was finally injected in the thermostat.
	m_mA_injected_shield.SetWindowTextW(m_aux_text);

	current_inject_k2400(milliampere / 1000., m_adr_k2400);
	k_2400_read_volt(m_adr_k2400);

	// Write_To_File_Thermostat_Shield(m_set_point, resistance, delta_T, power, speed);
	// old_time = time;
	return 0;
}


void CminervaRxDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CminervaRxDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CminervaRxDlg::OnCbnSelchangeComboCoreThermElements()
{
	m_elements_into_mean_core = m_select_media_core_C.GetCurSel() + 1;
	create_empty_core_mean_vector();
	return;
}


void CminervaRxDlg::OnCbnSelchangeComboThermospeedElements()
{
	m_elements_into_average_thermospeed = m_elements_average_speed_thermo_C.GetCurSel() + 1;
	create_empty_deltaR_thermostat_vector();
	m_average_thermospeed = 999;
	m_aux_text.Format(L"%6.5g", m_average_thermospeed);
	m_average_speed_shield_C.SetWindowTextW(m_aux_text);
	UpdateData(TRUE);
}


// Creates an empty vector of finite size where values will be stored to calculate the mean core resistance
void CminervaRxDlg::create_empty_core_mean_vector()
{
	if (m_media_core)
	{
		delete[] m_media_core;
	}
	m_elements_into_mean_core = m_select_media_core_C.GetCurSel() + 1;
	if (m_elements_into_mean_core>0)
	{
		m_media_core = new  (double[m_elements_into_mean_core + 2][2]);
		int ctr = 0;
		while (ctr < m_elements_into_mean_core)
		{ /* cleans all mean elements and their acquisition times */
			m_media_core[ctr][0] = 0;
			m_media_core[ctr][1] = 0;
			ctr++;
		}
	}
}


// A vector to keep track of delta_T Vs time, useful to calculate average thermostat speed and integral qauntities
void CminervaRxDlg::create_empty_deltaR_thermostat_vector()
{
	if (m_deltaR_thermostat)
		delete[] m_deltaR_thermostat;
	m_elements_into_average_thermospeed = m_elements_average_speed_thermo_C.GetCurSel() + 1;
	if (m_elements_into_average_thermospeed > 0)
	{
		m_deltaR_thermostat = new  (double[m_elements_into_average_thermospeed][2]);
		int ctr = 0;
		while (ctr < m_elements_into_average_thermospeed)
		{ /* cleans all mean elements and their acquisition times */
			m_deltaR_thermostat[ctr][0] = 0;
			m_deltaR_thermostat[ctr][1] = 0;
			ctr++;
		}
	}

}


// Copies arguments into matrix of thermostat's deltaR and time
void CminervaRxDlg::manage_thermo_deltaR_vector(double delta_R, long seconds)
{
	// shifts the positions of the vector's content, by one step at each call
	int ctr = 0;
	while (ctr < m_elements_into_average_thermospeed - 1) // The dimension with which the vector was created with null values throughout.
	{
		m_deltaR_thermostat[ctr][0] = m_deltaR_thermostat[ctr + 1][0]; // seconds
		m_deltaR_thermostat[ctr][1] = m_deltaR_thermostat[ctr + 1][1]; // delta_T
		ctr++;
	}
	m_deltaR_thermostat[m_elements_into_average_thermospeed - 1][0] = seconds;
	m_deltaR_thermostat[m_elements_into_average_thermospeed - 1][1] = delta_R;
}


void CminervaRxDlg::PID_2017(double resistance, double error, double speed)
{
	UpdateData(TRUE);

	//// PARAMETERS FOR PID DERIVATIVE
	double spec_heat = .72; /// specific heat this should be a PARAMETER (J/K g-1)
	double weight = 15.0; /// this could be a input variable (g)
	double ETA_target = m_ETA_target;  /// this should be a input vatiable (min)
	////// END PARAMETER

	long old_time = m_old_time;
	long current_time = clock();
	m_old_thermo_resistance = error;
	double thermostat_resistance = RESISTANCE_THERMOSTAT;
	double milliampere = 0.;
	double power = m_power_thermostat;
	double eta = - error / speed;

	m_do_noting++;
	CString tmp;
	tmp.Format(L"%d", m_do_noting);
	//m_contatore_PID.SetWindowTextW(tmp);
	if (m_do_noting < 0) // m_do_nothing is initialized to -3 when the thersmotat is started-
	{

		m_aux_text.Format(L"Do Nothing, %g min", int(eta));
		m_ETA_C.SetWindowText(m_aux_text);
		m_ETA_C.UpdateWindow();
		if (m_do_noting < -1)
		{
			power = 0;
			milliampere = 0;
		}
		else
		{
			if (!saturazione)
			{
				power += -m_p_pid*(error - old_error) - (m_I_PID * error * (double)m_thermostat_reading_interval) - (m_d_PID / pow((double)m_thermostat_reading_interval, 2)) * (error - 2 * old_error + older_error);
				
				m_aux_text.Format(L"%.5f", -m_d_PID*(error - old_error) / m_thermostat_reading_interval);
				m_Pd.SetWindowTextW(m_aux_text);
				
				m_aux_text.Format(L"%.5f", power + (m_d_PID*(error - old_error) / m_thermostat_reading_interval) + m_p_pid*error);
				m_Pi.SetWindowTextW(m_aux_text);
			}
			else
			{
				power = -m_p_pid*error - m_d_PID*(error - old_error) / m_thermostat_reading_interval;
				
				m_aux_text.Format(L"%.5f", 0);
				m_Pi.SetWindowTextW(m_aux_text);
				
				m_aux_text.Format(L"%.5f", -m_d_PID*(error - old_error) / m_thermostat_reading_interval);
				m_Pd.SetWindowTextW(m_aux_text);
			}
			
			m_aux_text.Format(L"%.5f", -m_p_pid*error);
			m_Pp.SetWindowTextW(m_aux_text);
			
			if (power >= 0)
				milliampere = (sqrt(power / thermostat_resistance))*1000.0;
			else
				milliampere = 0;
		}
	}
	else
	{
		if (!saturazione)
		{
			power += -m_p_pid*(error - old_error) - (m_I_PID * error * (double)m_thermostat_reading_interval) - (m_d_PID / pow((double)m_thermostat_reading_interval, 2)) * (error - 2 * old_error + older_error);
			
			m_aux_text.Format(L"%.5f", -m_d_PID*(error - old_error) / m_thermostat_reading_interval);
			m_Pd.SetWindowTextW(m_aux_text);

			m_aux_text.Format(L"%.5f", power + (m_d_PID*(error - old_error) / m_thermostat_reading_interval) + m_p_pid*error);
			m_Pi.SetWindowTextW(m_aux_text);
		}
		else
		{
			power = -m_p_pid*error - m_d_PID*(error - old_error) / m_thermostat_reading_interval;
			
			m_aux_text.Format(L"%.5f", 0);
			m_Pi.SetWindowTextW(m_aux_text);

			m_aux_text.Format(L"%.5f", -m_d_PID*(error - old_error) / m_thermostat_reading_interval);
			m_Pd.SetWindowTextW(m_aux_text);
		}

		m_aux_text.Format(L"%.5f", -m_p_pid*error);
		m_Pp.SetWindowTextW(m_aux_text);

		if (power >= 0)
			milliampere = (sqrt(power / thermostat_resistance))*1000.0;
		else
			milliampere = 0;
	}

	if (power <= 0 || milliampere >= 1.5)
	{
		saturazione = TRUE;
		if (milliampere >= 1.5)
			milliampere = 1.5;
		else
			milliampere = 0;
	}
	else
	{
		saturazione = FALSE;
	}
	m_power_thermostat = power; // power goes global


	//milliampere = min(milliampere, 1.5); // setting maximum injection current to 1.5 mA // cambiato il 30/03/2017
	m_aux_text.Format(L"%.5f", power);
	m_microW_shield_C.SetWindowTextW(m_aux_text); // nonostante il nome, la variabile mostra i Watt!
	m_aux_text.Format(L"%6.5g", milliampere); // the value of mA that was finally injected in the thermostat.
	m_mA_injected_shield.SetWindowTextW(m_aux_text);

	current_inject_k2400(milliampere / 1000.0, m_adr_k2400);
	k_2400_read_volt(m_adr_k2400);

	// Write_To_File_Thermostat(m_set_point, resistance, error, power, speed);
	// old_time = time;
	UpdateData(FALSE);
}


void CminervaRxDlg::OnCbnSelchangeComboHeatingMode() /* Selects Electrical Calibration OFF or ON and handles all corresponding events */
{
	CString text;
	int pos = m_Combo_CoreHeatingMode.GetCurSel();
	m_Combo_CoreHeatingMode.GetLBText(pos, text);
	if (pos < 2)
	{
		m_CoreHeatingMode = pos;
	}
	if (m_CoreHeatingMode == 0) // Electrical Calibration OFF: no output file creation, PID operation normal.
	{
		m_synchronize = FALSE;
		m_thermo_freeze = FALSE;
		m_core_set_seconds_C.EnableWindow(TRUE);
		m_Combo_Electrical_Calibration_Time.EnableWindow(FALSE);
		UpdateData(FALSE);
		OnBnClickedChecksynchronize();
	}
	else if (m_CoreHeatingMode == 1) // Electrical Calibration ON. Calibration run outputed to a file, Timer set for the entire run and for the following 180" to follow the post-run drift. 
	{
		m_synchronize = TRUE;
		UpdateData(FALSE);
		OnBnClickedChecksynchronize();
			
		// disable unwanted portions of the controls.
		
		m_Combo_Electrical_Calibration_Time.EnableWindow(TRUE);
		CString cal_time;
		int pos_duration = m_Combo_Electrical_Calibration_Time.GetCurSel();
		m_Combo_Electrical_Calibration_Time.GetLBText(pos_duration, cal_time);
		/*int cal_time = 0;
		if (pos_duration == 0) cal_time = 120;
		else if (pos_duration == 1) cal_time = 90;
		else if (pos_duration == 2) cal_time = 60;
		else cal_time = 0;
		*/
		// m_secondi_core = cal_time;
		// text.Format(L"%6.2f", cal_time);
		m_core_set_seconds_C.SetWindowTextW(cal_time);
		m_core_set_seconds_C.EnableWindow(FALSE);
		m_jacket_calibration_seconds_C.SetWindowTextW(cal_time);
		m_jacket_calibration_seconds_C.EnableWindow(FALSE);
	}
	// UpdateData(FALSE);
}


// polymorphic K6220 configuration function with DeltaMode on or off
void CminervaRxDlg::K6220_configuration(int address, int DeltaMode)
{
	CString text;
	if (DeltaMode == 0) /*Delta Mode Off */
	{
		text = L"*rst"; /* Resets to defaults on the 6220*/
		/*This still retains the current GPIB configuration*/
		write_GPIB(address, text);
		
		text = L"DISPlay:ENABle ON"; /* turns the display ON while no longer in Delta. */
		write_GPIB(address, text);
		
		text.Format(L"CURR  %6.3g", 15. / 1000000.);
		write_GPIB(address, text);

		text = L"CURR:FILT ON";
		write_GPIB(address, text);

		text = L"SOUR:CURR:RANG 10e-6"; /* Selects the XX.XXX range on the 6220. */
		write_GPIB(address, text);

		k6220_set_current(m_core_probe_curr, m_adr_k6220_core);
	}
	else if (DeltaMode == 1) /*Delta Mode On */
	{
		text = L"*rst"; /* Resets to defaults on the 6220*/
		/*This still retains the current GPIB configuration*/
		write_GPIB(address, text);

	/*  text = L"OUTPUT:ISHield GUARD";
		write_GPIB(address, text);  */

	/*	text = L"OUTPUT:LTEarth ON";
		write_GPIB(address, text);   */

		//text = L":FORM:ELEM READ,RNUM,TST,SOUR,COMP,AVOL,UNIT"; /*this is for the info to be retrieved from the buffer.*/
		//write_GPIB(address, text);

		/* ARM Layer settings */

		text = L"ARM:SOUR IMM"; /* Set the ARM-In Event to IMMediate*/
		write_GPIB(address, text);

		text = L"ARM:OLIN 3"; /*Set ARM layer output signal line #3 (from the 2182A manual, p.5-11)*/
		write_GPIB(address, text);

		text = L"ARM:OUTP NONE"; /* Disables the ARM layer output trigger p.8-10)*/
		/* not sure whether this corresponds to ARM-OUT Events OFF as at p 5.11 */
		write_GPIB(address, text);
		
		/* Trigger layer settings */

		text = L"TRIG:SOUR TLIN"; /* SM - Select the trigger source to TLINk */
		write_GPIB(address, text);

		text = L"TRIG:ILIN 1"; /* SM - Select the trigger layer input signal line to 1 */
		write_GPIB(address, text);

		text = L"TRIG:OLIN 2"; /* SM - Select the trigger layer output signal line to 2 */
		write_GPIB(address, text);

		text = L"TRIG:OUTP SOUR"; /* SM - Output trigger after source.*/
		write_GPIB(address, text);

		//text = L":TRIG:COUN 2"; /* SM - Trig count 2: one positive (high) and one negative (low). */
		//write_GPIB(address, text);

		text = L"SOUR:CURR:RANG 10e-6"; /* Selects the XX.XXX range on the 6220. */
		write_GPIB(address, text); 

		text = L"UNIT V"; /* Specifies that Volts readings are sent from 2182 to 6220. */
		write_GPIB(address, text);

		/* text = L"SOUR:DELT:DEL 1.7e-3";
		write_GPIB(address, text); */ 

		text = L"CURR:FILT ON"; /*turns on source-meter filtering*/
		write_GPIB(address, text);

		text = L"TRIG:DIR SOUR"; /* SM - Enable source bypass */
		write_GPIB(address, text);

		/*text = L"sour:func curr";
		write_GPIB(address, text); */

		/*text = L"func \'volt\'";
		write_GPIB(address, text);*/

		/*text = L"volt:nplc 1";
		write_GPIB(address, text);*/

		text = L"SOUR:DELT:HIGH  15e-6"; /* the high value is a positive 15 muA */
		write_GPIB(address, text);

		text = L"SOUR:DELT:LOW  -15e-6"; /* the low value is a negative 15 muA */
		write_GPIB(address, text);
		
		text = L"SOUR:DELT:ARM"; /*Arms Delta*/
		write_GPIB(address, text);

		//text = L"INIT:IMM"; /* Starts Delta measurements.*/
		//write_GPIB(address, text);

//		text = L"DISPlay:ENABle OFF"; /* turns the display off to prevent jitter while in Delta. */
//		write_GPIB(address, text);
	} 
	return;
}

// Configures Delta Mode on the 6220 (Obsolete, consider deletion) 
void CminervaRxDlg::K6220_Delta_Configuration(int address, double microampere, bool action)
{
	UpdateData(TRUE);

	CString text, text1;
	if (action == TRUE)
		{
		text1.Format(L"%.1g", microampere / 1000000);
		text = L"SOURce:DELTa:HIGH ";
		text += text1;
		write_GPIB(address, text);

		text = L"SOURce:DELTa:CABort OFF";
		write_GPIB(address, text);
		text = L"SOUR:DELTA:ARM"; /* Arms DELTA and waits for trigger */
		write_GPIB(address, text);
		}
	else if (action == FALSE)
		{
		text = L"ABORt";
		write_GPIB(address, text);
		text = L"SOURce:SWEep:ABORt"; /*unArms DELTA*/
		write_GPIB(address, text);
		}
}


BOOL CminervaRxDlg::K617_configuration(int address, int range) // sets the voltage scale of the electrometer 
{
	CString text;
	switch (range)
	{
	case 0: text = L"C1Z0XF4R1XQ0X"; break;
	case 1: text = L"C1Z0XF4R2XQ0X"; break;
	case 2: text = L"C1Z0XF4R3XQ0X"; break;
	}
	write_GPIB(address, text); // zero check ON, correct OFF, modalità controreazione, buffer ON e range fisso a 0.2 V (valutare se è il caso di cambiare range o addirittura parametrizzarlo per una scelta a video)

	//text = L"M1T3X"; // abilito SRQ per la condizione di overflow e one-shot trigger by GET	
	text = L"M1X"; // abilito SRQ per la condizione di overflow e one-shot trigger by GET	
	write_GPIB(address, text);

	return 1;
}


BOOL CminervaRxDlg::HP_thermometer_configuration(int address)
{
	CString text;
	text = L"R1X";
	write_GPIB(address, text); // Range 1 (?...)
	text = L"T2X";
	write_GPIB(address, text); // Termistore n. 2 sul monitor (?...)
	return 1;
}


BOOL CminervaRxDlg::K199_configuration(int address)
{
	CString text;
	text = L"F0R0S1P0X";
	write_GPIB(address, text); 

	text = L"O0Q0W0N1X";
	write_GPIB(address, text);

	return 1;
}


void CminervaRxDlg::populate_capacitor_list()
{
	capacitor_number.ResetContent();
	CString tmp;
	for (int i = 1; i <= 26; i++)
	{
		tmp.Format(L"%d", i);
		capacitor_number.AddString(tmp);
	}

	for (int i = 101; i <= 107; i++)
	{
		tmp.Format(L"%d", i);
		capacitor_number.AddString(tmp);
	}

	for (int i = 201; i <= 207; i++)
	{
		tmp.Format(L"%d", i);
		capacitor_number.AddString(tmp);
	}


	capacitor_number.SetCurSel(0);
	OnCbnSelchangeComboCapacitor();
}


void CminervaRxDlg::OnCbnSelchangeComboCapacitor()
{
	/* 
	Per iniziare, abbiamo scelto di non avvalerci della connessione al DBase Misura, già di riferimento per il software di gestione misure ionometriche.
	Non è però escluso che si faccia uso dei dBase in futuro anche per organizzare le misure di calorimetria.
	 */ 
	int i = capacitor_number.GetCurSel();
	switch (i)
	{
	case 0:  this->capacitor_value_text.SetWindowTextW(L"999.4"); break;
	case 1:  this->capacitor_value_text.SetWindowTextW(L"996.85"); break;
	case 2:  this->capacitor_value_text.SetWindowTextW(L"1012.2"); break;
	case 3:  this->capacitor_value_text.SetWindowTextW(L"1000.5"); break;
	case 4:  this->capacitor_value_text.SetWindowTextW(L"5013.5"); break;
	case 5:  this->capacitor_value_text.SetWindowTextW(L"5022.7"); break;
	case 6:  this->capacitor_value_text.SetWindowTextW(L"100.22"); break;
	case 7:  this->capacitor_value_text.SetWindowTextW(L"100.19"); break;
	case 8:  this->capacitor_value_text.SetWindowTextW(L"10030"); break;
	case 9:  this->capacitor_value_text.SetWindowTextW(L"29918"); break;
	case 10:  this->capacitor_value_text.SetWindowTextW(L"100510"); break;
	case 11:  this->capacitor_value_text.SetWindowTextW(L"100058"); break;
	case 12:  this->capacitor_value_text.SetWindowTextW(L"100604"); break;
	case 13:  this->capacitor_value_text.SetWindowTextW(L"59644"); break;
	case 14:  this->capacitor_value_text.SetWindowTextW(L"40015.8"); break;
	case 15:  this->capacitor_value_text.SetWindowTextW(L"29997"); break;
	case 16:  this->capacitor_value_text.SetWindowTextW(L"9976.8"); break;
	case 17:  this->capacitor_value_text.SetWindowTextW(L"10045.2"); break;
	case 18:  this->capacitor_value_text.SetWindowTextW(L"5009.91"); break;
	case 19:  this->capacitor_value_text.SetWindowTextW(L"5016.86"); break;
	case 20:  this->capacitor_value_text.SetWindowTextW(L"1002.22"); break;
	case 21:  this->capacitor_value_text.SetWindowTextW(L"1000.78"); break;
	case 22:  this->capacitor_value_text.SetWindowTextW(L"503.755"); break;
	case 23:  this->capacitor_value_text.SetWindowTextW(L"504.156"); break;
	case 24:  this->capacitor_value_text.SetWindowTextW(L"182490"); break;
	case 25:  this->capacitor_value_text.SetWindowTextW(L"364220"); break;
	case 26:  this->capacitor_value_text.SetWindowTextW(L"100.356"); break;
	case 27:  this->capacitor_value_text.SetWindowTextW(L"1002.23"); break;
	case 28:  this->capacitor_value_text.SetWindowTextW(L"5007"); break;
	case 29:  this->capacitor_value_text.SetWindowTextW(L"10017"); break;
	case 30:  this->capacitor_value_text.SetWindowTextW(L"30082"); break;
	case 31:  this->capacitor_value_text.SetWindowTextW(L"59756"); break;
	case 32:  this->capacitor_value_text.SetWindowTextW(L"99704"); break;
	case 33:  this->capacitor_value_text.SetWindowTextW(L"100.047"); break;
	case 34:  this->capacitor_value_text.SetWindowTextW(L"1001.39"); break;
	case 35:  this->capacitor_value_text.SetWindowTextW(L"5025"); break;
	case 36:  this->capacitor_value_text.SetWindowTextW(L"10065"); break;
	case 37:  this->capacitor_value_text.SetWindowTextW(L"30046"); break;
	case 38:  this->capacitor_value_text.SetWindowTextW(L"59949"); break;
	case 39:  this->capacitor_value_text.SetWindowTextW(L"100440"); break;
	}
}

void CminervaRxDlg::OnBnClickedButtonIrradiate()
{
	// Sequence of events that characterize a radiation run
	CString txt;
	m_button_irradiate.GetWindowTextW(txt);
	if (txt == L"Irradiate")
	{
		UpdateData(TRUE);
		CString tmp, tmp2;
		tmp = L"Are you sure your rx tube is on and stable? And are you sure your choices are: \nirradiation time = ";
		m_Combo_Irradiation_Time.GetLBText(m_Combo_Irradiation_Time.GetCurSel(), tmp2);
		tmp += tmp2 + L" /s";
		tmp += L"\ncapacitor = ";
		capacitor_value_text.GetWindowTextW(tmp2);
		tmp += tmp2 + L" /pF ?\n";
		
		int i = MessageBox(tmp, L"Irradiation...", MB_YESNO | MB_ICONEXCLAMATION);
		
		if (i == IDYES)
		{
			CRecRunId->Open();
			
			m_run_type = 2; // Irradiation mode. Will commute back to 0 at the end of writing a run to the file.
			m_CoreHeatingMode = 0; // set Calibration mode off and disable Combo until radiation ends.
			m_Combo_CoreHeatingMode.SetCurSel(0); 
			m_Combo_CoreHeatingMode.EnableWindow(FALSE);
			txt = L"Abort Irradiation";
			m_button_irradiate.SetWindowTextW(txt);

			CRecRunId->AddNew();
			CRecRunId->m_calibration_mode = 0;
			CRecRunId->m_Capacitance = capacitor_value_numeric;
			m_combo_radiation_quality.GetWindowTextW((CString)CRecRunId->m_RX_Qual);
			CRecRunId->m_calibration_mode = 0;
			CString today = (CTime::GetCurrentTime()).Format(L"%Y%m%d");
			CRecRunId->m_hour = CTime::GetCurrentTime();
			CRecRunId->m_date = today;
			CRecRunId->Update();
			CRecRunId->Requery();

			m_thermo_freeze = TRUE; // PID freeze
			UpdateData(FALSE);
			m_Combo_Irradiation_Time.EnableWindow(FALSE);
			m_combo_radiation_quality.EnableWindow(FALSE);
			capacitor_number.EnableWindow(FALSE);

			CString text;
			text = L"Z1C0X";  // zero correct ON and zero check OFF (electrometer measurement)
			write_GPIB(m_adr_k617_monitor, text); 
			
			text = L"G1X";
			write_GPIB(m_adr_k617_monitor, text); // comando di lettura misura singola senza prefisso

			CString rMString, timeStr;

			irradiation_begins_now = ((double)clock() / (double)CLOCKS_PER_SEC); // Prendere il momento attuale come istante 0- dell'irraggiamento (OK)

			read_GPIB(m_adr_k617_monitor, &rMString);
			//  mettere in modalità misura elettrometro monitor (dare il GET per la memorizzazione valore iniziale)
			//  Prendere il momento attuale come istante 0+ dell'irraggiamento e farne la _media_ con il precedente, sottraendogli poi il t_zero.
			//  Note: this is a strategy to estimate the moment in which the voltage measurement on the electrometer was actually made and stored. 
			irradiation_begins_now = 0.5* (irradiation_begins_now + ((double)clock() / (double)CLOCKS_PER_SEC)) - m_seconds_t_zero;
			irradiation_begins_now_core_vector_time = m_vector_core[m_points_vector_core - 1][0];
			timeStr.Format(L"%.2f", irradiation_begins_now);
			add_message(L"\nVM1 =" + rMString + L", tbegin=" + timeStr + L" s");
			VMbegin = wcstod(rMString, NULL);
			CoreVectorRunStarts.Format(L"%.3f", irradiation_begins_now_core_vector_time);
			add_message(L"corresponding to a value stored in core vector: " + CoreVectorRunStarts + L" s");
			AcquireTmon(0);
			AcquirePmon(0);
			AcquireHmon(0);

			float64 value = 4;
			DAQmxWriteAnalogScalarF64(taskHandleAPRI, 0, DAQmx_Val_WaitInfinitely, value, NULL);
			DAQmxWriteAnalogScalarF64(taskHandleCHIUDI, 0, DAQmx_Val_WaitInfinitely, 0.0, NULL);

			// imposto timer di 0.1 s con passo da 0.01 s per finalizzazione apertura otturatore:
			m_ShutterWait = 11;
			SetTimer(6001, 10, NULL);

			/*
			- aprire lo shutter (il tubo deve già essere stato acceso e scelta la capacità usata per la misura ionometrica col monitor)
			- partire con un timer di misura da 120 s con passo 120000 ms, allo scadere del quale:
			- chiudere lo shutter ed ordinare il GET per la memorizzazione finale del valore misurato col monitor
			- rimettere a OFF il PID freez settando come nuovo valore di setpoint l'ultimo valore di resistence sullo shield a fine irraggiamento
			- partire con un timer da 180 sec con passo 180000 ms (al termine del quale istanziare oggetto della classe Run, che gestirà la scrittura dei dati in un file dedicato)
			*/
		}
	}
	else // Abort Irradiation Instructions 
	{
		// case of abort of irradiation: to delete the partial recordset previously populated
		if (CRecRunId != NULL)
		{
			if (CRecRunId->IsOpen())
			{	
				CRecRunId->MoveLast();
				CString idStr;
				idStr.Format(L"%d", CRecRunId->m_ID);
				CRecRunId->Delete();
				CRecRunId->Close();
				if (CRecRunMeas->IsOpen()) CRecRunMeas->Close();
				CRecRunMeas->Open(CRecordset::snapshot, _T("select * from run_measurements where ID_RUN =" + idStr));
				while (!CRecRunMeas->IsEOF())
				{
					CRecRunMeas->Delete();
					CRecRunMeas->MoveNext();
				}
				CRecRunMeas->Close();
			}	
		}
			
		
		txt = L"Irradiate";
		m_button_irradiate.SetWindowTextW(txt);

		m_thermo_freeze = FALSE; // PID freeze
		UpdateData(FALSE);

		m_Combo_Irradiation_Time.EnableWindow(TRUE);
		m_combo_radiation_quality.EnableWindow(TRUE);
		KillTimer(6000);
		m_Combo_CoreHeatingMode.EnableWindow(TRUE);
		OnCbnSelchangeComboIrradiationTime();

		float64 value = 4;
		DAQmxWriteAnalogScalarF64(taskHandleCHIUDI, 0, DAQmx_Val_WaitInfinitely, value, NULL);
		DAQmxWriteAnalogScalarF64(taskHandleAPRI, 0, DAQmx_Val_WaitInfinitely, 0.0, NULL);

		// imposto timer di 0.1 s con passo da 0.01 s per finalizzazione apertura otturatore:
		m_ShutterWait = 11;
		SetTimer(6002, 10, NULL);

		CString text;
		text = L"C1Z0X";
		write_GPIB(m_adr_k617_monitor, text); // zero check ON, correct OFF
	}
}


void CminervaRxDlg::OnCbnSelchangeComboIrradiationTime()
{
	// Selection of the Irradiation Time through its Combo Box and update of the radiation time CountDown display.
	CString txt;
	m_Combo_Irradiation_Time.GetLBText(m_Combo_Irradiation_Time.GetCurSel(), txt);
	m_run_countdown = (long)wcstod(txt, NULL);
	UpdateData(FALSE);
}


bool CminervaRxDlg::extend_GPIBNetwork()
{
	// catena di misura stanza 10, ed. T-5 (elett+par. ambientali)
	m_adr_k617_monitor = assign_device(27);
	m_adr_druck = assign_device(20);
	m_adr_thermo_HP = assign_device(13);
	m_adr_k199 = assign_device(26);
	// catena di misura stanza 10, ed. T-5 (elett+par. ambientali)
	return false;
}


int CminervaRxDlg::extended_check_instruments()
{
	CString testo;
	// catena di misura st.za 10
	if (!poll(m_adr_k199))
	{
		testo = "Please Check K199 Address 26";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}

	if (!poll(this->m_adr_druck))
	{
		testo = "Please Check Druck DPI-141 Barometer Address 20";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}

	if (!poll(this->m_adr_k617_monitor))
	{
		testo = "Please Check Keithkley 617 Address 27";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}

	if (!poll(this->m_adr_thermo_HP))
	{
		testo = "Please Check HP Thermometer Address 13";
		add_message(testo);
		AfxMessageBox(testo, MB_ICONEXCLAMATION | MB_OK);
	}
	return 0;
}


int CminervaRxDlg::extended_instruments_configuration()
{
	K617_configuration(m_adr_k617_monitor);
	HP_thermometer_configuration(m_adr_thermo_HP);
	K199_configuration(m_adr_k199);
	return 0;
}


void CminervaRxDlg::OnBnClickedCheckEnableExtendedGPIB()
{
	// TODO: Add your control notification handler code here

	m_enable_extended_GPIB_C.EnableWindow(FALSE);
	m_partial_GPIB_configuration = FALSE;
	m_button_irradiate.EnableWindow(TRUE);
	m_Combo_Irradiation_Time.EnableWindow(TRUE);
	m_combo_radiation_quality.EnableWindow(TRUE);
	m_combo_range_k617.EnableWindow(TRUE);
	capacitor_number.EnableWindow(TRUE);
	capacitor_value_text.EnableWindow(TRUE);
	extend_GPIBNetwork();
	extended_check_instruments();
	extended_instruments_configuration();
}


void CminervaRxDlg::AcquireTmon(int index)
{
	CString TStr;
	write_GPIB(m_adr_thermo_HP, L"T2X");
	read_GPIB(m_adr_thermo_HP, &TStr);
	
	double T2val = wcstod(TStr, NULL);
	if (index == 0)
		TMbegin = T2val;
	else
		TMend = T2val;
}


void CminervaRxDlg::AcquirePmon(int index)
{
	CString P1CStr;
	read_GPIB(m_adr_druck, &P1CStr);
	double P1val = wcstod(P1CStr, NULL);
	if (index == 0)
		PMbegin = P1val;
	else if (index == 1)
		PMend = P1val;
}




void CminervaRxDlg::AcquireHmon(int index)
{
	CString k199CStr, k199Str2;
	double k199d;

	CString sec;
	(double)(clock() / (double)CLOCKS_PER_SEC);
	sec.Format(L"%.1f", (double)(clock() / (double)CLOCKS_PER_SEC));

	CString sec5;
	(double)(clock() / (double)CLOCKS_PER_SEC);

	write_GPIB(m_adr_k199, L"F0R0S1P0X");
	write_GPIB(m_adr_k199, L"O0Q0W0N1X");
	
	
	(double)(clock() / (double)CLOCKS_PER_SEC);

	read_GPIB(m_adr_k199, &k199CStr);

	k199CStr = k199CStr.Right(12);
	k199d = wcstod(k199CStr, NULL);
	k199Str2.Format(L"%4.3f", k199d);
	double Uval = wcstod(k199Str2, NULL);

	if (index == 0)
	{
		Uval = Uval * 100;
		HMbegin = Uval;
	}
	else if (index == 1)
	{
		Uval = Uval * 100;
		HMend = Uval;
	}
}


void CminervaRxDlg::OnCbnSelchangeComboRadiationQuality()
{
	// TODO: Add your control notification handler code here
	int i = m_combo_radiation_quality.GetCurSel();
	switch (i)
	{
	case 0: attenuation_coeff = 0.259; break;
	case 1: attenuation_coeff = 0.183; break;
	case 2: attenuation_coeff = 0.162; break;
	case 3: attenuation_coeff = 0.14; break;
	}
}


void CminervaRxDlg::ElaborateMonitorData() // handles calculation of QMon, Imon, and their corrections
{
	double temp; // Tutte variabili che potrebbero esser rese globali per poterle riutilizzare
	CString tempStr;
	capacitor_value_text.GetWindowTextW(tempStr);
	capacitor_value_numeric = wcstod(tempStr, NULL);
	QMON = capacitor_value_numeric*(VMend - VMbegin);
	IMON = QMON / (irradiation_ends_now - irradiation_begins_now);

	// correzione per ricombinazione ionica:
	IMON = P_IN + IMON*P_VOL;
	QMON = IMON*(irradiation_ends_now - irradiation_begins_now);

	// correzione per TP:
	Ktpm = ((273.15 + ((TMbegin + TMend) / 2.0)) * 1013.25) / (293.15 * ((PMbegin + PMend) / 2.0));
	IMON = IMON*Ktpm;
	QMON = QMON*Ktpm;

	// correzione per Hr%:
	double temp2 = (HMbegin + HMend) / 2.0;
	if (temp2 <= 10)
		temp = 0.9993;
	else if (temp2 > 10 && temp2 <= 15)
		temp = 0.9993 + (0.9991 - 0.9993) * (temp2 - 10) / 5.0;
	else if (temp2 > 15 && temp2 <= 20)
		temp = 0.9991;
	else if (temp2 > 20 && temp2 <= 25)
		temp = 0.9991;
	else if (temp2 > 25 && temp2 <= 30)
		temp = 0.9991 + (0.9993 - 0.9991) * (temp2 - 25) / 5.0;
	else if (temp2 > 30 && temp2 <= 35)
		temp = 0.9993 + (0.9994 - 0.9993) * (temp2 - 30) / 5.0;
	else if (temp2 > 35 && temp2 <= 40)
		temp = 0.9994 + (0.9996 - 0.9994) * (temp2 - 35) / 5.0;
	else if (temp2 > 40 && temp2 <= 45)
		temp = 0.9996 + (0.9998 - 0.9996) * (temp2 - 40) / 5.0;
	else if (temp2 > 45 && temp2 <= 50)
		temp = 0.9998 + (1 - 0.9998) * (temp2 - 45) / 5.0;
	else if (temp2 > 50 && temp2 <= 55)
		temp = 1 + (1.0003 - 1) * (temp2 - 50) / 5.0;
	else if (temp2 > 55 && temp2 <= 60)
		temp = 1.0003 + (1.0005 - 1.0003) * (temp2 - 55) / 5.0;
	else if (temp2 > 60 && temp2 <= 65)
		temp = 1.0005 + (1.0007 - 1.0005) * (temp2 - 60) / 5.0;
	else if (temp2 > 65 && temp2 <= 70)
		temp = 1.0007 + (1.0009 - 1.0007) * (temp2 - 65) / 5.0;
	else if (temp2 > 70)
		temp = 1;
	IMON = IMON*temp;
	QMON = QMON*temp;

	// correzione per Katt:
	double dm, LattMTP;
	dm = 39.95; // distanza del monitor dal fuoco (al Maggio 2018)
	LattMTP = (dm / Ktpm) - dm;
	Katt = exp(attenuation_coeff * 0.0012045 * LattMTP); //densità dell'aria a T=293.15 e P=1013.25 = 0.0012045 g/cm3
	IMON = IMON*Katt;
	QMON = QMON*Katt;
}


void CminervaRxDlg::OnBnClickedChecksynchronize() 
{ // On clicking the synchronize injection check button, limit the user's control to the core buttons and disable the Jacket buttons altogether.
	UpdateData(TRUE);
	CString txt;
	if (m_synchronize)
	{
		txt = L"START Core and Jacket Current Injection";
		m_start_core_injection_C.SetWindowTextW(txt);
		txt = L"STOP Core and Jacket Current Injection";
		m_Stop_Core_current_injection_C.SetWindowTextW(txt);
		m_start_jacket_injection_C.EnableWindow(FALSE);
		m_jacket_calibration_seconds_C.EnableWindow(FALSE);
		m_jacket_current_calibration_C.EnableWindow(FALSE);
	}
	else
	{
		txt = L"START Core Current Injection";
		m_start_core_injection_C.SetWindowTextW(txt);
		txt = L"STOP Core Current Injection";
		m_Stop_Core_current_injection_C.SetWindowTextW(txt);
		m_start_jacket_injection_C.EnableWindow(TRUE);
		m_jacket_calibration_seconds_C.EnableWindow(TRUE);
		m_jacket_current_calibration_C.EnableWindow(TRUE);
	}

}


void CminervaRxDlg::OnSelchangeComboCalibrationTime()
{
	// TODO: Add your control notification handler code here
	CString cal_time;
	int pos_duration = m_Combo_Electrical_Calibration_Time.GetCurSel();
	m_Combo_Electrical_Calibration_Time.GetLBText(pos_duration, cal_time);
	
	m_core_set_seconds_C.SetWindowTextW(cal_time);
	// m_core_set_seconds_C.EnableWindow(FALSE);
	m_jacket_calibration_seconds_C.SetWindowTextW(cal_time);
	// m_jacket_calibration_seconds_C.EnableWindow(FALSE);
	// UpdateData(TRUE);
	// UpdateData(FALSE);
}


void CminervaRxDlg::OnCbnSelchangeComboRangeK617()
{
	CString txt, range;
	int i = m_combo_range_k617.GetCurSel();
	switch (i)
	{
	case 0: K617_configuration(m_adr_k617_monitor, 0); break;
	case 1: K617_configuration(m_adr_k617_monitor, 1); break;
	case 2: K617_configuration(m_adr_k617_monitor, 2); break;
	}
	
	// m_combo_range_k617.GetLBText(m_combo_range_k617.GetCurSel(), txt);
	// m_run_countdown = (long)wcstod(txt, NULL);
	// UpdateData(FALSE);
}


void CminervaRxDlg::OnBnClickedButtonAnalyzeRun()
{
	// TODO: Add your control notification handler code here
	const int bufferSize = 1024;
	CString RunfileName = L"DummyRunFile.dat";
	wchar_t* p = RunfileName.GetBuffer(bufferSize);

	CString sDummy(L"Specify Run File to open...");

	/* Defines the types of files to be displayed in the directory, defaults to ".dat"
	See https://docs.microsoft.com/en-us/cpp/mfc/reference/cfiledialog-class */
	TCHAR szFilters[] = _T("radiation runs (*radiation.dat)|*radiation.dat|electric runs (*electric.dat)|*electric.dat|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("Runs"), _T("*.dat"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.lpstrFile = p; // Attaches the full path plus the file name, to the CString ThermoSettingsfileName, via the pointer p.
	ofn.lpstrInitialDir = m_directory; // Starts searching in the Minerva_runs directory 

	CString Text;

	if (dlgFile.DoModal() == IDOK) // This launches the actual Open File Dialog 
	{
		CStdioFile RunFile;
		CFileException fileException; // Stores any error messages
		CString strBuff; // Where the single line file content will be streamed into, once opened; 

		//RunFile.Abort();
		BOOL whatsup = RunFile.Open(RunfileName, CFile::modeRead, &fileException);
		if (!whatsup)
		{
			Text.Format(L" Cannot Read %s, error: %u", RunfileName, fileException.m_cause);
			AfxMessageBox(Text);
		}
		else
		{
			// read the first head line (ID_RUN int, used to select the recordset of measurements data to show)
			RunFile.ReadString(strBuff);
			
			long id = (long) wcstod(strBuff, NULL);

			// scanning the table:
			/*for (int i = 1; i <= DIM_VECT_BUFFER; i++)
			{
				tab = tempStr.Find('\t');
				timeStr = tempStr.Left(tab);
				newline = tempStr.Find('\n');
				resistanceStr = tempStr.Mid(tab,newline-tab);
				//buffer_vect[i - 1][0] = wcstod(timeStr, NULL);
				//buffer_vect[i - 1][1] = wcstod(resistanceStr, NULL);
				if (i == 1)
				{
					MessageBox(L"time= " + timeStr + L" resist = " + resistanceStr);
				}

				tempStr = tempStr.Mid(newline + 1, tempStr.GetLength() - (newline+1));
			}*/
			
			BOOL IRR = FALSE;
			if (RunfileName.Right(12) != L"electric.dat")
				IRR = TRUE;
			CDialogRunAnalyze* dialogRunAnalyze = new CDialogRunAnalyze(this, IRR, id);
			if (dialogRunAnalyze->Create(IDD_DIALOG_ANALYZE_RUN, this))
				dialogRunAnalyze->ShowWindow(SW_SHOWNORMAL);
			else
				delete dialogRunAnalyze;
			// dialogRunAnalyze->
		}

		RunFile.Close();
	}
}


void CminervaRxDlg::OnBnClickedButtonStopCoreCurrentInjection()
{
	// TODO: Add your control notification handler code here
	// If case of stop the current injection to abort electrical calibration, we must delete the created run_id record and measurements records alredy stored:
	k_2400_onoff(0, m_adr_k2400_core);
	KillTimer(1001);
	m_start_core_injection_C.EnableWindow(TRUE);
	m_Stop_Core_current_injection_C.EnableWindow(FALSE);
	if (m_synchronize) OnBnClickedButtonStopJacketcalibration2();
	
	
	if (m_CoreHeatingMode == 1) // case of electrical calibration
	{
		MessageBox(L"stop");
		if (CRecRunId->IsOpen())
		{
			CRecRunId->MoveLast();
			CString idStr;
			idStr.Format(L"%d", CRecRunId->m_ID);
			CRecRunId->Delete();
			CRecRunId->Close();
			
			if (CRecRunMeas->IsOpen()) CRecRunMeas->Close();
			CRecRunMeas->Open(CRecordset::snapshot, _T("select * from run_measurements where ID_RUN =" + idStr));
			while (!CRecRunMeas->IsEOF())
			{
				CRecRunMeas->Delete();
				CRecRunMeas->MoveNext();
			}
			CRecRunMeas->Close();
		}
	}
}
