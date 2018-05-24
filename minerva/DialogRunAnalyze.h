#pragma once



#include <grafico_ver2.h>
#include "afxwin.h"
#include "run_measurements.h"
#include "run_id.h"
#include <regressione.h>
//#include <afxtempl.h>
// CDialogRunAnalyze dialog

class CDialogRunAnalyze : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRunAnalyze)

public:
	regressione preDriftRegression, postDriftRegression;
	int x2; // index of the time value corresponding to the beginning of the heating run, defining the _end_ of the preDrift linear regression
	int x3; // index of the time value corresponding to the end of the heating run, defining the _beginning_ of the postDrift linear regression
	int vector_size; // Size of the vector that will contain the run data, as read from the DBase;
	double(*m_vector_run)[2];
	double(*m_vector_preDriftRegression)[2];
	double(*m_vector_postDriftRegression)[2];
	 
	Crun_measurements* CRecRunMeas;
	Crun_id* CRecRunId;
	CDC *m_p_CDC_RUN;
	grafico_ver2 *m_grafico_run; /* graph where the run trend will be displayed. Instantiated from Stefano's grafico_ver2 Class*/
	CDialogRunAnalyze(CWnd* pParent = NULL, BOOL irradiation = FALSE, long id_run = 0);   // standard constructor
	virtual ~CDialogRunAnalyze();
	double delta_T; // run duration (in seconds)
	double mid_T; // mid point of the heating run
	

// Dialog Data
	enum { IDD = IDD_DIALOG_ANALYZE_RUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HICON m_hIcon;
	int fit_vector_sizes;
	double delta_R, mid_R; // deltaR and average resistance value at the mid point of the heating run
	double slope_preDrift;
	double intercept_preDrift;
	double slope_postDrift;
	double intercept_postDrift;
	long IDrun;
	CStringA date;
	CTime hour;
	bool is_calibration;
	double power, energy, calibration_coefficient;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
//	CStatic m_graph_run_C;
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CStatic m_graph_run_C;
	// Bubble vector sorting functions, from "Misura", not used here though. 
	double maxi(double*vector);
	double mini(double*vector);
	double maximum(double*vector, int size);
	double minimum(double*vector, int size);
	void MergeSort(double*vector, int left, int right);
	void Merge(double*vector, int left, int center, int right);
	CStatic m_run_duration;
	// assists in displaying general information on the run being visualized
	CStatic m_run_info;
};
