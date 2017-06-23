// fit_gauss_marioDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "grafico_ver2.h"
#include <math.h>


// Cfit_gauss_marioDlg dialog
class Cfit_gauss_marioDlg : public CDialog
{
// Construction
public:
	Cfit_gauss_marioDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FIT_GAUSS_MARIO_DIALOG };

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
	CEdit m_nome_exp_C;
	afx_msg void OnBnClickedButtonOpenExp();
	int open_exp(void);
	CString m_nome_exp;
		CString m_nome_MCNP;

		CStdioFile m_file_dati;
		CStdioFile m_file_MCNP;

		CEdit m_nome_MCNP_C;
		afx_msg void OnBnClickedButtonOpenMcnp();
		int open_MCNP(void);
		double m_exp[20000][2];
		int m_punti_exp;
				double m_MCNP[20000][2];
		int m_punti_MCNP;

		double m_exp_min;
		double m_exp_max;

		int load_exp(void);
		CStatic m_area_grafico;
		grafico_ver2 m_plot;
		int plotta_point(void);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		BOOL m_cursore_on_grafico;
		CRect  m_grafico_rect;
		WINDOWPLACEMENT m_grafico_place;
		CPoint m_point;
		BOOL m_start_drag;
		BOOL m_track_drag;
		CPoint m_init_drag_p1;
		CPoint m_vertice_grafico;
		BOOL m_init_drag;

		CStatic m_static_messaggi_C;
		int calcola_coordinate(CPoint punto);
		double m_coordinate[2];
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		BOOL m_grafico_on;
		int selezione(CPoint punto);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		int rescale(CPoint p1, CPoint p2);
		double m_x_min;
		double m_x_max;
		double m_y_min;
		double m_y_max;
		afx_msg void OnBnClickedButtonReplot();
		int replot(void);
		int load_MCNP(void);
		double m_compa[20000][2];
		int m_punti_compa;
		int m_fit_start;
        int m_fit_end;

		int compa(void);
		double interpola(int ctr,BOOL inizializzo,double* MCNP_shifted);
		double m_a_gauss;
		double m_x0_gauss;
		double m_s_gauss;
 		double *m_gauss ;
 		double *m_conv ;
		CListBox m_messaggi_C;
		int calcola_gauss(void);
		afx_msg void OnBnClickedButtonShowGauss();
		int calcola_conv(void);
		double calcola_varianza(void);
		CStatic m_varianza_C;
		afx_msg void OnBnClickedButtonGo();
		int start_fit(void);
		int minimizza_a(void);
		CEdit m_finestra_a_C;
		int minimizza_x0(void);
		CEdit m_fimestra_x0_C;
		int minimizza_s(void);
		CEdit m_fimestra_s_C;
		CButton m_a_check_C;
		CButton m_x0_check_C;
		CButton m_s_check_C;
		CEdit m_de_finestra_C;
		double m_dE_gauss;
		CButton m_dE_check_C;
		int minimizza_dE(void);
		afx_msg void OnBnClickedButtonSave();
		CStatic m_var_min_C;
		double m_varianza_min;
		double conv_gauss(int punta);
		CButton m_check_convolution;
		afx_msg void OnBnClickedCheck5();
		afx_msg void OnBnClickedButtonZoomAll();
		double m_x_min_all;
		double m_x_max_all;
		double m_y_min_all;
		double m_y_max_all;

		CButton m_BLG_c_check_C;
		CEdit m_bkg_c_C;
		double m_bkg_m;
		double m_bkg_c;
		double m_bkg_v;
		double m_bkg_tot;
		int minimizza_c(void);
		int m_ctr_start;
		int m_ctr_stop;
		afx_msg void OnBnClickedButtonAbort();
		BOOL m_abort;
		int plot_bkG(void);
		CEdit m_bgk_tot_C;
		CStatic m_step_C;
		CString m_testo;
		CEdit m_int_tot_C;
		afx_msg void OnBnClickedButtonSaveData();
		double m_integrale_exp;
		double m_integrale_BKG;
		CStdioFile m_file_out;
		bool m_primo_file;
		BOOL m_salvato;
		CEdit m_delta_a_C;
		CEdit m_delta_x0_C;
		CEdit m_delta_s_C;
		CEdit m_delta_c_C;
		CEdit m_delta_bkgc_C;
		double m_live_time;
};
