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
	CString idStr;
	idStr.Format(L"%d", id_run);
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
		CRecRunMeas->MoveNext();
	}

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
		m_grafico_run->coordinate(t_min, CRecRunMeas->m_time, y_min/*0.95*/, y_max/*1.05]*/);
		m_grafico_run->cambia_colore_frame(0, 50, 0, 1);
		m_grafico_run->CambiaColore(200, 0, 0, 2);
		m_grafico_run->x_tick_change(100);
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
