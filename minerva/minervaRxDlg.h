
// minervaDlg.h : header file
//

#pragma once
#include "NIDAQmx.h"
#include "ni4882.h"
#include "afxwin.h"
#include "afx.h"
#include <afxdb.h>
#include "C:\Users\CalRx\Documents\Visual Studio 2013\Projects\minerva\class_linear_regression\regressione.h"
/* versione che veniva usata fino al 20 Aprile 2017.*/
//#include "C:\Users\CalRx\Documents\Visual Studio 2013\Projects\minerva\class_grafico_v2\grafico_ver2.h"
#include "C:\Users\CalRx\Documents\Visual Studio 2013\Projects\minerva\fit_gauss\grafico_ver2.h"
/*Ricevuta da Stefano L. via email il 6 Aprile 2017. Caricata nel progetto 20/04/2017 sembra non introdurre nuovi errori.*/
#include "atltime.h"
#include "run.h"
#include "dialogrunanalyze.h"
#include "run_id.h"
#include "run_measurements.h"

#define BDINDEX               0     // Board Index
#define PRIMARY_ADDR_OF_DMM   3     // Primary address of device
#define NO_SECONDARY_ADDR     0     // Secondary address of device
#define TIMEOUT               T3s  // Timeout value = 10 seconds
#define EOTMODE               1     // Enable the END message
#define EOSMODE               1     // Disable the EOS mode



#define TIMER_CORE 500 /* a measurement every 0.5 seconds! 1000 */
#define TIMER_THERMOSTAT 5000   // Every 5 seconds (holding time)
#define TIMER_AUX 10000	// Auxiliary thermistors timer interval
#define RESISTANCE_THERMOSTAT 40000
#define DERIVATIVE_POWER 10000 // microwatt

#define GPIB0        0        
#define TIMEOUT_POOL        10 // 10 secondi        
#define PERIODO_LETTURA_MEDIUM 20000  //millisecondi
#define POTENZA_DERIVATIVA 350000 // corrente derivativa iniziale = microWatt
#define RESISTENZA_TERMOSTATO 35 // Resistenza Termostato Medium ??? 
#define RESISTENZA_PONTE_WHEATSTONE 10000 // Resistenza Ponte Wheatstone
#define SECONDI_SCARTO 20 // Secondi da scartare nella regressione lineare testa-coda ???
#define DIM_VET_TERMO 1000 // Dimensione vettore dati thermostato
#define DIM_VET_CORE 4000 // Vector data size. Since TIMER_CORE is set to 500, for the graph to show the entire past one hour you should set this size to at least (3600" / 0.57"), that is 6315 positions.
#define DIM_VET_AUX 4000 // Dimensione vettore dati AUX
#define P_IN 1.00088197 // Parameters for the calculation of the monitor chambers' kSat (Pin, Pvol)
#define P_VOL 9854.7
#define POST_RUN_DRIFT_TIME 180 // 180 seconds to elapse after a single radiation or electrical calibration before another run can be executed
//#define DIM_VECT_BUFFER (int) ceil((1/0.57)*(RUN_TIME + 2* DRIFT_TIME))  // the dimesion of the buffer vector that will contain 480" of data (0.57" between two consecutive measurements)

// CminervaRxDlg dialog
class CminervaRxDlg : public CDialogEx
{
	friend bool run::create_run_file();
// Construction
public:
	CminervaRxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MINERVA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// VARIABILI GESTIONE OTTURATORE STANZA 10 RX ME
	TaskHandle taskHandleAPRI;			/* ID del task che verrà assegnato da DAQmxCreateTask */
	TaskHandle taskHandleCHIUDI;			/* ID del task che verrà assegnato da DAQmxCreateTask */
	char* outputAPRI;			/* L'output analogico usato per il tasto APRI è AO0*/
	char* outputCHIUDI;		/* L'output analogico usato per il tasto CHIUDI è AO1*/
	char* nomeTaskAPRI;			/* Nome del task */
	char* nomeTaskCHIUDI;		/* Nome del task */
	float64 minVal;
	float64 maxVal;				/* L'output è condizionato al range 0..5V */
	int32 configInput;		/* L'uscita è configurata come  come single-ended */
	int32 totale;
	// FINE VARIABILI GESTIONE OTTURATORE STANZA 10 RX ME
	afx_msg void OnBnClickedButtonTest();
	BOOL inizializza_GPIB();
	bool assign_GPIBaddress();
	int m_adr_k2400;
	int m_adr_k2400_core;
	int m_adr_k2400_jacket;

	int assign_device(int GPIB_address);
	CListBox m_message_box_C;
	int add_message(CString text);
	int IBSTA();
	CStatic m_ERR_C;
	CStatic m_TIMO;
	CStatic m_END_C;
	CStatic m_CMPL_C;
	int poll(int address);
	int check_instruments();
	BOOL write_GPIB(int address, CString command);
	BOOL K2400_configuration(int address);
	char *m_string;
	int conv_CS_CH(CString text);
	bool current_inject_k2400(int microampere, long address);
	bool current_inject_k2400(double ampere, long address);
	bool k_2400_onoff(bool on, long address);
	afx_msg void OnDestroy();
	int instruments_configuration();
	BOOL read_GPIB(int address, CString * p_text);
	int m_adr_k2182_core;
	int m_adr_k2182_multi;
	int K2182_configuration(int address);
	int K2182_configuration(int address, int DeltaMode); /*polymorphic configuration*/
	double read_k2182(int address, BOOL send_request=TRUE);
	CStatic m_test_C;
	int m_adr_k6220_core;
	void K6220_configuration(int address);
	int m_adr_k6220_multi;
	int m_adr_k7001_switch;
	
	// catena di misura stanza 10, ed. T-5 (elett+par. ambientali) /* 02/05/2018*/
	int m_adr_k617_monitor;
	int m_adr_druck;
	int m_adr_thermo_HP;
	int m_adr_k199;
	// catena di misura stanza 10, ed. T-5 (elett+par. ambientali)

	int m_micro_ampere_core;
	int m_secondi_core;
	CEdit m_microwatt_core_C;
	CEdit m_joule_core_C;
	CEdit m_seconds_core_C;
	CEdit m_volt_core_C;
	afx_msg void OnBnClickedStartCoreInjection();
	BOOL m_flag_core;
	BOOL m_flag_jacket;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int core_power();
	int m_timer_core;
	double m_joule_core;
	double k_2400_read_volt(int address);
	double microwatt(double current, double volt, CWnd * window);
	double microjoule(double watt, long live_time, long old_time, double *joule, CWnd * window);
	afx_msg void OnBnClickedButtonstartjacket();
	bool create_cycle_file();
	CString m_directory;
	CStdioFile m_file_cycle;
	double write_file_cycle(long cronometer, double joule_core, double current_core, double volt, double joule_jacket, double current_jacket, double volt_jacket);
	int m_number_of_cycles;
	long m_pause_cycle;
	afx_msg void OnBnClickedButtonRunCycle();
	afx_msg void OnBnClickedButtonStopCycle();
	CButton m_button_start_cycles_C;
	CButton m_button_stop_cycle_C;
	void cycle_core_power();
	int m_flag_cycle_power_core;
	int m_done_cycles;
	CEdit m_done_C;
	CEdit m_pause_C;
	CString m_aux_text;
	long m_pause_start;
	// checks whether pasue time has been reached before a new cycle is launched
	BOOL control_pause();
	double m_set_point;
	double m_p_pid;
	double m_d_PID;
	CEdit m_shield_ohm_C;
	CEdit m_delta_k_C;
	CEdit m_microW_shield_C;
	CEdit m_speed_shield_C;
	CEdit m_ETA_C;
	afx_msg void OnBnClickedButtonSetPoint();
	double read_core();
	double m_core_current;
	afx_msg void OnBnClickedButtonProbeCurrSet();
	double m_core_probe_curr;
	CEdit m_core_resistance_C;
	CEdit m_core_resistance_mean_C;
	CEdit m_core_resistance_STD_C;
	CEdit m_core_resistance_trend_C;
	CStatic m_core_color_C;
	int load_elements_media();
	CComboBox m_select_media_core_C;
	afx_msg void OnBnClickedButtonStartCoreMeasurement();
	int k6220_set_current(double microamp, long address);
	BOOL k6220_onoff(bool on, long address);
	afx_msg void OnBnClickedButtonStopCoreMeasurement2();
	double  (* m_media_core)[2];
	double  (* m_deltaR_thermostat)[2];
	int manage_core_measure();
	int m_flag_measure_core;
	double manage_core_media(double resistance);
	int m_elements_into_mean_core;
	
	/* Time declarations */
	double m_seconds_absolute;
	CTime m_seconds_beginning_Dec_2013; 
	/* long m_seconds_continuous; Questo era un long, Massimo lo cambia in double al 29/03/2018*/ 
	double m_seconds_continuous;
	BOOL request_data_core();
	double read_resistance(int address, BOOL core=TRUE);
	double manage_data_core(double resistance);
	int m_anti_block_core;
	regressione m_linear_regression;
	CComboBox m_select_mean_jacket_C;
//	CEdit m_jacket_probe_curr;
	afx_msg void OnBnClickedButtonProbeCurrSet2();
	double m_jacket_probe_current;
	CStatic m_antiloop_C;
	afx_msg void OnBnClickedButtonStartThermo();
	BOOL manage_thermostat();
	double read_thermostat();
	int m_skip_points_thermostat;
	CComboBox m_elements_mean_therrmo_C;
	int m_mean_thermostat;
	afx_msg void OnCbnSelchangeComboCoreThermElements3();
	int m_anti_block_general;
	double read_resistance_multi(int address, BOOL send_request = TRUE);
	double m_multi_probe_current;
	CStatic m_ledred_termo_medium_C;
	enum list_status_thermo { INIT, START, REQUEST, WAITING, DONE };
	list_status_thermo m_status_thermostat;
	list_status_thermo m_status_aux;
	
	BOOL request_data_multi();
	double read_multi();
	int m_anti_block_multi; // contatore dei loop di interrogazione
	int m_anti_block_aux; // contatore dei loop di interrogazione specifico per i termistori aux;
	afx_msg void OnBnClickedButtonStopThermo();
	BOOL manage_mean_thermostat(double resistance);
	int PID(double resistance);
	double m_old_thermo_temperature;
	int thermo(double speed, CDC * pCDC); // Color-coding of the resistance variation over time
	CDC *m_p_CDC;
	CStatic m_therm_color_C;
	int m_derivative_power;
	CStatic m_thermo_message_C;
	CStdioFile m_file_thermo_shield;
	CStdioFile m_file_core;
	CStdioFile m_file_aux;
	void Save_Measurements_Data(void);
	grafico_ver2 *m_grafico_termo; /* Graph where the thermostat trend will be displayed. Instantiated from Stefano's grafico_ver2 Class*/
	grafico_ver2 *m_grafico_core; /* Graph where the thermostat trend will be displayed. Instantiated from Stefano's grafico_ver2 Class*/
	grafico_ver2 *m_grafico_aux; /* Graph where the thermostat trend will be displayed. Instantiated from Stefano's grafico_ver2 Class*/
	void Create_Thermostat_Shield_File();
	unsigned long Write_To_File_Thermostat_Shield(double target, double sensor, double deltaR, double power, double speed);
	CEdit m_PID_D_C;
	CStatic m_graph_C;
	int create_thermo_graph();
	int plot_thermostat(double time, double delta_R);
	double(*m_vector_thermo)[2];
	double(*m_vector_core)[2];
	double(*m_vector_aux)[2];
	double(*buffer_vect)[2]; // The buffer vector that will hold the part of the stream of core resistance and time data that will be receive from the run-selected file.
	int m_points_vector_thermo;
	int m_points_vector_core;
	int m_points_vector_aux;
	float m_scale_plot_thermo;
	float m_scale_plot_core;
	float m_scale_plot_aux;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL create_file_core();
	bool save_core(double seconds, double resistance, double sigma, double trend);
	// afx_msg void OnBnClickedStaticGraph();
	afx_msg void OnBnClickedButtonStopShieldInject();
	CStatic m_graph_core_C;
	int create_core_graph();
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	int plot_core(double time, double resistance);
	// int plot_R(double time, double R, double &(*graph_vector)[2], int dim, grafico_ver2 *graph);
	int plot_R(double time, double R);
	CDC *m_p_CDC_CORE; 
	CDC *m_p_CDC_AUX;
	double m_I_PID;
	int m_do_noting;
	double m_ETA_target;
	int m_jacket_current_calibration;
	int m_jacket_calibration_seconds;
	CEdit m_volt_jacket_C;
	CEdit m_microwatt_jacket_C;
	CEdit m_joule_jacket_C;
	CEdit m_seconds_jacket_C;
	afx_msg void OnEnChangeEdit1();
	int jacket_power();
	long m_timer_jacket;
	double m_joule_jacket;
	afx_msg void OnBnClickedButtonStopJacketcalibration2();
	BOOL m_synchronize;
	int m_thermostat_reading_interval;
	int poll_7001();
	CButton m_CH1_C;
	CButton m_CH2_C;
	CButton m_CH3_C;
	CButton m_CH4_C;
	CButton m_CH5_C;
	CButton m_CH7_C;
	afx_msg void OnBnClickedCheck2();
	int openclose_switch(int channel,BOOL status);
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	CButton m_CH6_C;
	int Status_7001();
	int Check_mask(CString Mask);
	CButton *m_p_status_switch[9];
	CButton m_enable_C;
	afx_msg void OnBnClickedCheck10();
	int enable_switch(bool enable);
	int switch_open_all();
	afx_msg void OnBnClickedStaticCoreGraph2();
	int m_thermistor_ID;
	// BOOL m_radio_therm;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	CButton m_jacket_1c_C;
	BOOL m_radio_thermo;
	CStatic m_graph_radio_C;
	CButton m_radio1_C;
	afx_msg void OnBnClickedButtonStartAuxMeasurement();
	CComboBox m_combo_thermo_aux_C;
	afx_msg void OnCbnSelchangeCombo1();
	int m_thermo_CH_aux; // integer to drive the 7001 switch
	afx_msg void OnBnClickedButtonStopAuxMeasurement();
	int crea_aux_graph();
	CStatic m_aux_color_C;
	afx_msg void OnDeltaposSpinAux(NMHDR *pNMHDR, LRESULT *pResult);
	bool save_aux(long seconds, double resistance, double sigma, double trend);
	BOOL create_file_aux();
	int plot_aux(double time, double delta_R);
	// Drives the reading of one auxiliary thermistor via the 7001 switch
	BOOL manage_aux();
	// Control variable to alter the color of the auxiliary LED status
	CStatic m_ledred_therm_aux_C;
	CStatic m_antiloop_aux_C;
	// this function returns the resistance value read on the auxiliary thermistor
	double read_aux();
	// manages the mean of the resistance values read on the auxiliary thermistor
	BOOL manage_mean_aux(double resistance);
	// number of elements concurring in the calculation of the mean resistance of the auxiliary thermistor	
	int m_mean_aux;
	CEdit m_aux_ohm_C;
	int m_skip_points_aux;
	afx_msg void OnBnClickedButtonSetValuesAux();
	int m_aux_reading_interval;
	// Sistema semaforico con precedenza sul termostato
	BOOL m_red_light_thermostat;
	afx_msg void OnCbnSelchangeComboCoreThermElements2();
	double m_mean_resistance_aux;
	CEdit m_aux_speed_C;
	// checks whether any channel on 7001 is busy
	int check_7001_busy(CString Mask);
	// Holds status of 7001 switch
	CString busy_7001;
	// polimorfismo per verificare solo se lo swtich è occupato 
	int Status_7001(CString busy);
	CStatic m_ledred_switch_C;
	BOOL check_7001_busy();
	CStatic m_antiloop_core_C;
	// To show the number of measurements that were already completed
	CStatic m_thermostat_completed_C;
	// Displays progress in single measurements with respect to the elements in mean
	// CStatic m_core_completed_C;
	// Shows progress in the number of consecutive measurements due
	//CStatic m_aux_completed_C;
	CStatic m_aux_show_completed_C;
	// you can freeze the PID status during irradiaitons
	BOOL m_thermo_freeze;
	afx_msg void OnCheckboxClickedFreezePID();
	afx_msg void OnBnClickedSaveThermoSettings();
	afx_msg void OnBnClickedButtonReadThermo();
	// funzione creata da Massimo per esoserare PID(resistance) da compiti che non dovrebbe assolvere
	BOOL Manage_Thermostat_Mean(double resistance);
	// the power to be inhected in the thermostat
	double m_power_thermostat;
	// polymorphic PID function
	int PID(double resistance, double delta_T, double speed);
	// global value of old time with respect to which you can calculate speed
	long m_old_time;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	// The zero time that gets set upon starting any reading (Core, Jacket, or medium-shield)
	double m_seconds_t_zero;
	// differental power, in micro Watt, as calculated in derivative mode (derivative delta, only)
	CEdit m_delta_uW_shield_C;
	// Display mA really injected in the shield as a result of all PID calculations
	CEdit m_mA_injected_shield;
	// Displays the value of the average speed ot the thermostat (detla_T/time) as averaged over N points
	CEdit m_average_speed_shield_C;
	// Select the number of elements to be used to calculate the average speed of the thermostat, as delta_T / time
	CComboBox m_elements_average_speed_thermo_C;
	// Number of elements that make up for the average speed of the thermostat
	int m_elements_into_average_thermospeed;
	afx_msg void OnCbnSelchangeComboCoreThermElements();
	afx_msg void OnCbnSelchangeComboThermospeedElements();
	// Creates an empty vector of finite size where values will be stored to calculate the mean core resistance
	void create_empty_core_mean_vector();
	// A vector to keep track of delta_T Vs time, useful to calculate average thermostat speed and integral qauntities
	void create_empty_deltaR_thermostat_vector();
	// Copies arguments into matrix of thermostat's deltaT and time
	void manage_thermo_deltaR_vector(double delta_R, long seconds);
	// Continous time to be used within thermostat routines
	long m_seconds_continuous_thermostat;
	// The average value of thermostat's speed toward the setpoint
	double m_average_thermospeed;
	CButton m_aux_start_button_C;
	CButton m_aux_stop_button_C;
	CButton m_core_start_button_C;
	CButton m_core_stop_button_C;
	CButton m_thermo_start_button_C;
	CButton m_thermo_stop_button_C;
	CButton m_Okay_button_C;
	double m_old_thermo_resistance;
	double old_error; // utile per implementazione del PID
	double older_error; // utile per implementazione del PID, in particolare per implementare la parte derivativa
	BOOL saturazione; //  utile per implementazione del PID, per evitare la parte integrazione del PID (integrazione dell'errore) quando dai conti vien fuori una corrente oltre 1.5 mA o negativa (saturazione del PID)
	void PID_2017(double resistance, double error, double speed);
//	double m_Pp;
//	double m_Pi;
//	double m_Pd;
	CEdit m_Pp;
	CEdit m_Pi;
	CEdit m_Pd;
	// Polymorphic plot_thermostat function, centers the graph on the x-axis if center is set to TRUE
	int plot_thermostat(double time, double delta_R, bool center);
	int m_CoreHeatingMode; // 0 for Eletrical Calibration, 1 for manual heating, in an electrical calibration.
	
	// Combo box to swtich DeltaMode function on and off
	CComboBox m_Combo_CoreHeatingMode;
	afx_msg void OnCbnSelchangeComboHeatingMode();
	// polymorphic K6220 configuration function with DeltaMode on or off
	void K6220_configuration(int address, int DeltaMode);
	// void K6220_Sweep_Configuration(int address, double microampere);
	// Configures Delta Mode on the 6220
	void K6220_Delta_Configuration(int address, double microampere, bool action);
	run* my_run;
	
	CComboBox m_Combo_Electrical_Calibration_Time; // sets the duration of an electrical calibration cycle
	int m_electrical_calibration_duration_option; // Holds the current selection of calibration time (corresponding to 60", 90" or 120")
	// controls seconds set for current injection
	CEdit m_core_set_seconds_C;
	CButton m_Stop_Core_current_injection_C;
	CButton m_Stop_Jacket_current_injection_C;
	BOOL K617_configuration(int address, int range = 2);
	BOOL HP_thermometer_configuration(int address);
	BOOL K199_configuration(int address);
	CComboBox capacitor_number;
	CEdit capacitor_value_text;
	double capacitor_value_numeric;
	void populate_capacitor_list();
	afx_msg void OnCbnSelchangeComboCapacitor();
	afx_msg void OnBnClickedButtonIrradiate();
	CComboBox m_Combo_Irradiation_Time;
	afx_msg void OnCbnSelchangeComboIrradiationTime();
	CButton m_button_irradiate;
	long m_run_countdown;
	
	double irradiation_begins_now; // when the shutter opens or when the heating starts
	double irradiation_ends_now; // when the shutter closes or when the heating stops
	double irradiation_begins_now_core_vector_time; // last time value stored in the m_core_vector when the shutter opens (irradiation starts) or when injection starts
	double irradiation_ends_now_core_vector_time; // last time value stored in the m_core_vector when the shutter closes (irradiation ends) or when injection stops
	int m_ShutterWait;
	BOOL m_partial_GPIB_configuration;
	bool extend_GPIBNetwork();
	int extended_check_instruments();
	int extended_instruments_configuration();
	
	// // CHECK control to extend the GPIB configuration to include the monitor chamber electrometer etc.
	CButton m_enable_extended_GPIB_C;
	afx_msg void OnBnClickedCheckEnableExtendedGPIB();
	double VMbegin;
	double VMend;
	double TMbegin;
	double TMend;
	double PMbegin;
	double PMend;
	double HMbegin;
	double HMend;
	CString CoreVectorRunStarts, CoreVectorRunEnds;
	void AcquireTmon(int index);
	void AcquirePmon(int index);
	void AcquireHmon(int index);
	CComboBox m_combo_radiation_quality;
	afx_msg void OnCbnSelchangeComboRadiationQuality();
	double attenuation_coeff;
	void ElaborateMonitorData();
	double QMON;
	double IMON;
	double Ktpm, Katt;
	CEdit m_jacket_calibration_seconds_C;
	CButton m_start_core_injection_C;
	afx_msg void OnBnClickedChecksynchronize();
	CButton m_start_jacket_injection_C;
	CEdit m_jacket_current_calibration_C;
	afx_msg void OnSelchangeComboCalibrationTime();
	CStatic m_Countdown_show_phase;
	CComboBox m_combo_range_k617;
	afx_msg void OnCbnSelchangeComboRangeK617();
	afx_msg void OnBnClickedButtonAnalyzeRun();
	
	// global variable stating the run condition. 0: idle; 1: electric calibration, 2: irradiation
	int m_run_type;

	CDatabase db;
	Crun_id* CRecRunId;
	Crun_measurements* CRecRunMeas;
	afx_msg void OnBnClickedButtonStopCoreCurrentInjection();
};
