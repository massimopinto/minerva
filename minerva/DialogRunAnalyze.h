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
	//CArray<double, double> preDrift;
	//CArray<double, double> postDrift;
	regressione preDriftRegression, postDriftRegression;
	int x2; // index of the time value corresponding to the beginning of the heating run, defining the _end_ of the preDrift linear regression
	int x3; // index of the time value corresponding to the end of the heating run, defining the _beginning_ of the postDrift linear regression
	int j; // Size of the vector that will contain the run data, as read from the DBase;
	double(*m_vector_run)[2];
	/*double(*m_vector_prefit)[2];
	double(*m_vector_postfit)[2];*/
	Crun_measurements* CRecRunMeas;
	Crun_id* CRecRunId;
	CDC *m_p_CDC_RUN;
	grafico_ver2 *m_grafico_run; /* graph where the run trend will be displayed. Instantiated from Stefano's grafico_ver2 Class*/
	CDialogRunAnalyze(CWnd* pParent = NULL, BOOL irradiation = FALSE, long id_run = 0);   // standard constructor
	virtual ~CDialogRunAnalyze();

// Dialog Data
	enum { IDD = IDD_DIALOG_ANALYZE_RUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
//	CStatic m_graph_run_C;
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CStatic m_graph_run_C;
};
