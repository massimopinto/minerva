// DialogRunAnalyze.cpp : implementation file
//

#include "stdafx.h"
#include "minervaRx.h"
#include "DialogRunAnalyze.h"
#include "afxdialogex.h"


// CDialogRunAnalyze dialog

IMPLEMENT_DYNAMIC(CDialogRunAnalyze, CDialogEx)

CDialogRunAnalyze::CDialogRunAnalyze(CWnd* pParent /*=NULL*/, BOOL irradiation, long id_run)
	: CDialogEx(CDialogRunAnalyze::IDD, pParent)
{
	CRecRunMeas = new Crun_measurements();
	CRecRunId = new Crun_id();
	CString idStr;
	idStr.Format(L"%d", id_run);
	CRecRunId->Open(CRecordset::snapshot, _T("select * from run_id where ID =" + idStr));
	CRecRunMeas->Open(CRecordset::snapshot, _T("select * from run_measurements where ID_RUN =" + idStr));

	m_grafico_run = NULL;
	m_p_CDC_RUN = NULL;

	j = 0;
	while (!CRecRunMeas->IsEOF())
	{
		j++;
		CRecRunMeas->MoveNext();
	}
	CRecRunMeas->MoveFirst();

	m_vector_run = new (double[j][2]);
	
	for (int i = 0; i < j; i++) // popolo il vettore da graficare
	{
		m_vector_run[i][0] = CRecRunMeas->m_time;
		m_vector_run[i][1] = CRecRunMeas->m_resistance;
		if (CRecRunMeas->m_time == CRecRunId->m_t_core_begin) // run begin time, as stored in the core_vector
			x2 = i; 
		if (CRecRunMeas->m_time == CRecRunId->m_t_core_end) // run end time, as stored in the core_vector
			x3 = i;
		CRecRunMeas->MoveNext();
	}

	/*CString tmp1, tmp2;
	tmp1.Format(L"%d", x2);
	tmp2.Format(L"%d", x3);
	MessageBox(L"index x2: " + tmp1 + L", index x3: " + tmp2, L"identified x2 and x3", MB_YESNO);
	*/

	// Identification of the linear fitting regions
	double delta_T = m_vector_run[x3][0] - m_vector_run[x2][0]; // run duration
	int x1, x4 = 0; // indices of the beginning of the region for the preDrift regression and the end of the region for the postDrift regression
	double t1 = CRecRunId->m_t_core_begin - 120.; 
	double t4 = CRecRunId->m_t_core_end + 120.;

	for (int i = 0; i < x2; ++i)
	{
		if (m_vector_run[i][0] > t1)
		{
			x1 = i - 1;
			break;
		}
	}

	for (int i = x3; i < j; ++i)
	{
		x4 = x3;
		if (m_vector_run[i][0] > t4)
		{
			x4 = i - 1;
			break;
		}
	}

	/*
	tmp1.Format(L"%d", x1);
	tmp2.Format(L"%d", x4);
	MessageBox(L"index x1: " + tmp1 + L", index x4: " + tmp2, L"identified x1 and x4", MB_YESNO);
	*/
	
	// linear regressions, preDrift and postDrift

	preDriftRegression.calcola_regressione(m_vector_run, x1, x2);
	postDriftRegression.calcola_regressione(m_vector_run, x3, x4);

	double slope_preDrift = preDriftRegression.m_coefficiente_angolare;
	double intercept_preDrift = preDriftRegression.m_intercetta;
	double slope_postDrift = postDriftRegression.m_coefficiente_angolare;
	double intercept_postDrift = postDriftRegression.m_intercetta;

	// population of the linear fit vectors with the best fit lines data

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDialogRunAnalyze::~CDialogRunAnalyze()
{
}

void CDialogRunAnalyze::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC_RUN_GRAPH, m_graph_run_C);
	DDX_Control(pDX, IDC_STATIC_RUN_GRAPH, m_graph_run_C);
}


BEGIN_MESSAGE_MAP(CDialogRunAnalyze, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CDialogRunAnalyze message handlers


void CDialogRunAnalyze::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	delete this;
}


BOOL CDialogRunAnalyze::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	/*UpdateData(TRUE);
	m_grafico_run = new grafico_ver2;
	//m_p_CDC_RUN = m_graph_run_C.GetDC();

	
	m_grafico_run->assegna(&m_graph_run_C);
	//m_grafico_run->assegna(m_p_CDC_RUN);
	m_grafico_run->back_ground_color[0] = 240;
	m_grafico_run->back_ground_color[1] = 255;
	m_grafico_run->back_ground_color[2] = 240;
	m_grafico_run->riempi_tutto();
	m_grafico_run->sposta_label_x_axis(5);
	CRecRunMeas->MoveFirst();
	double y_min = 1000000;
	double y_max = 0.0;
	double t_min = CRecRunMeas->m_time;
	while (!CRecRunMeas->IsEOF())
	{
		if (CRecRunMeas->m_resistance > y_max)
			y_max = CRecRunMeas->m_resistance;
		if (CRecRunMeas->m_resistance < y_min);
		y_min = CRecRunMeas->m_resistance;
		CRecRunMeas->MoveNext();
	}
	CRecRunMeas->MoveLast();
	m_grafico_run->coordinate(t_min, CRecRunMeas->m_time, y_min, y_max);
	m_grafico_run->cambia_colore_frame(0, 50, 0, 1);
	m_grafico_run->CambiaColore(200, 0, 0, 2);
	m_grafico_run->x_tick_change(100);
	m_grafico_run->y_tick_change((y_max - y_min) / 5.);
	m_grafico_run->plotta_frame();


	//m_grafico_core->coordinate((long)floor(time - 3589), (long)floor(time + 11), y_min, y_max);
	//m_grafico_core->x_tick_change(600);
	
	//m_grafico_core->y_tick_change((y_max - y_min) / 5.); // Divides the vertical space in 5 blocks (plots four grid lines) 
	//m_grafico_run->plotta_frame();
	m_grafico_run->plot_vettore(m_vector_run, 0, j-1); /* re-plot the entire vector */

	//m_grafico_run->plot_vettore(m_vector_run, 100, 1000);*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogRunAnalyze::OnPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

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
		m_grafico_run = new grafico_ver2;
		m_grafico_run->assegna(&m_graph_run_C);
		m_grafico_run->back_ground_color[0] = 240;
		m_grafico_run->back_ground_color[1] = 255;
		m_grafico_run->back_ground_color[2] = 240;
		m_grafico_run->riempi_tutto();
		m_grafico_run->sposta_label_x_axis(5);
		CRecRunMeas->MoveFirst();
		double y_min = 1000000;
		double y_max = -1.0;
		double t_min = CRecRunMeas->m_time;
		while (!CRecRunMeas->IsEOF())
		{
			if (CRecRunMeas->m_resistance > y_max)
				y_max = CRecRunMeas->m_resistance;
			if (CRecRunMeas->m_resistance < y_min);
				y_min = CRecRunMeas->m_resistance;
			CRecRunMeas->MoveNext();
		}
		/*
		CString t, t2;
		t.Format(L"%.3f", y_min);
		t2.Format(L"%.3f", y_max);
		MessageBox(L"Min = " + t + L" Max = " + t2);
		*/
		CRecRunMeas->MoveLast();
		double t_max = CRecRunMeas->m_time;
		m_grafico_run->coordinate(t_min, t_max, y_min - (y_max - y_min)*0.10, y_max + (y_max - y_min)*0.10); // Center the plot leaving a little space above and below.
		m_grafico_run->cambia_colore_frame(0, 50, 0, 1);
		m_grafico_run->CambiaColore(200, 0, 0, 2);
		m_grafico_run->x_tick_change((t_max - t_min) / 5.);
		m_grafico_run->y_tick_change((y_max - y_min) / 5.);
		m_grafico_run->plotta_frame();
		//m_grafico_core->coordinate((long)floor(time - 3589), (long)floor(time + 11), y_min, y_max);
		//m_grafico_core->x_tick_change(600);

		//m_grafico_core->y_tick_change((y_max - y_min) / 5.); // Divides the vertical space in 5 blocks (plots four grid lines) 
		//m_grafico_run->plotta_frame();
		m_grafico_run->plot_vettore(m_vector_run, 0, j - 1); /* re-plot the entire vector */
		CDialogEx::OnPaint();
	}
}


HCURSOR CDialogRunAnalyze::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return CDialogEx::OnQueryDragIcon();
}
