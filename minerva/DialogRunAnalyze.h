#pragma once



#include <grafico_ver2.h>
#include "afxwin.h"
#include "run_measurements.h"
#include <regressione.h>

// CDialogRunAnalyze dialog

class CDialogRunAnalyze : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRunAnalyze)

public:
	int j;
	double(*m_vector_run)[2];
	Crun_measurements* CRecRunMeas;
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
