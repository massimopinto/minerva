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
	m_grafico_run = new grafico_ver2;
	
	CString idStr;
	idStr.Format(L"%d", id_run);
	CRecRunId->Open(CRecordset::snapshot, _T("select * from run_id where ID =" + idStr));
	CRecRunMeas->Open(CRecordset::snapshot, _T("select * from run_measurements where ID_RUN =" + idStr));

	vector_size = 0;
	while (!CRecRunMeas->IsEOF())
	{
		vector_size++;
		CRecRunMeas->MoveNext();
	}
	CRecRunMeas->MoveFirst();

	m_vector_run = new (double[vector_size][2]);
	
	for (int i = 0; i < vector_size; i++) // popolo il vettore da graficare
	{
		m_vector_run[i][0] = CRecRunMeas->m_time;
		m_vector_run[i][1] = CRecRunMeas->m_resistance;
		if (CRecRunMeas->m_time == CRecRunId->m_t_core_begin) // run begin time, as stored in the core_vector
			x2 = i; 
		if (CRecRunMeas->m_time == CRecRunId->m_t_core_end) // run and time, as stored in the core_vector
			x3 = i;
		CRecRunMeas->MoveNext();
	}

	/*CString tmp1, tmp2;
	tmp1.Format(L"%d", x2);
	tmp2.Format(L"%d", x3);
	MessageBox(L"index x2: " + tmp1 + L", index x3: " + tmp2, L"identified x2 and x3", MB_YESNO);
	*/

	// Identification of the linear fitting regions
	delta_T = m_vector_run[x3][0] - m_vector_run[x2][0]; // run duration (in seconds)
	mid_T = 0.5*(m_vector_run[x2][0] + m_vector_run[x3][0]); // mid point of the heating run
	int x1, x4 = 0; // indices of the beginning of the region for the preDrift regression and the end of the region for the postDrift regression
	double t1 = CRecRunId->m_t_core_begin - 120.; 
	double t4 = CRecRunId->m_t_core_end + 120.;

	for (int i = 0; i < x2; i++)
	{
		if (m_vector_run[i][0] > t1)
		{
			x1 = i - 1;
			break;
		}
	}

	for (int i = x3; i < vector_size; i++)
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

	slope_preDrift = preDriftRegression.m_coefficiente_angolare;
	intercept_preDrift = preDriftRegression.m_intercetta;
	slope_postDrift = postDriftRegression.m_coefficiente_angolare;
	intercept_postDrift = postDriftRegression.m_intercetta;

	// population of the linear fit vectors with the best fit lines data
	fit_vector_sizes = 120 + (int) (delta_T / 2.0);
	
	m_vector_preDriftRegression = new (double[fit_vector_sizes][2]);
	m_vector_preDriftRegression[0][0] = m_vector_run[x1][0]; // Best fit line starts from x1
	m_vector_preDriftRegression[0][1] = m_vector_preDriftRegression[0][0] * slope_preDrift + intercept_preDrift; // y[0] = a + bx[0]
	for (int i = 1; i < fit_vector_sizes; ++i) 
	{
		m_vector_preDriftRegression[i][0] = m_vector_preDriftRegression[0][0] + i;
		m_vector_preDriftRegression[i][1] = m_vector_preDriftRegression[i][0] * slope_preDrift + intercept_preDrift; // y[i] = a + bx[i]
	}

	m_vector_postDriftRegression = new (double[fit_vector_sizes][2]);
	m_vector_postDriftRegression[0][0] = mid_T; // Best fit line starts from the run midpoint
	m_vector_postDriftRegression[0][1] = m_vector_postDriftRegression[0][0] * slope_postDrift + intercept_postDrift; // y[0] = a + bx[0]
	for (int i = 1; i < fit_vector_sizes; ++i)
	{
		m_vector_postDriftRegression[i][0] = m_vector_postDriftRegression[0][0] + i;
		m_vector_postDriftRegression[i][1] = m_vector_postDriftRegression[i][0] * slope_postDrift + intercept_postDrift; // y[i] = a + bx[i]
	}

	// Calculating run results
	double R1, R2;
	R1 = mid_T *slope_preDrift + intercept_preDrift;
	R2 = mid_T *slope_postDrift + intercept_postDrift;
	delta_R = R1-R2;
	mid_R = 0.5*(R1 + R2);

	CRecRunId->m_delta_R = delta_R;
	CRecRunId->m_mid_R = mid_R;
	CRecRunId->m_deltaR_over_R = (delta_R / mid_R);
	CRecRunId->m_preDrift_slope = slope_preDrift;
	CRecRunId->m_postDrift_slope = slope_postDrift;
	
	// CRecRunId->Update();
	CRecRunId->Requery();
}

CDialogRunAnalyze::~CDialogRunAnalyze()
{
}

void CDialogRunAnalyze::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_RUN_GRAPH, m_graph_run_C);
	DDX_Control(pDX, IDC_STATIC_run_duration, m_run_duration);
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
	
	// Prepare text to be displayed below the plot, summaring run information and results
	
	CString tmp, tmp1, tmp2, tmp3, tmp4, tmp5;
	tmp.Format(L"%.1f", delta_T);
	tmp1.Format(L"%.3f", 1000*delta_R);
	tmp2.Format(L"%.3f", mid_R);
	tmp3.Format(L"%.3f", (1000*delta_R) / mid_R);
	tmp4.Format(L"%.3f", 1000*slope_preDrift);
	tmp5.Format(L"%.3f", 1000*slope_postDrift);
	m_run_duration.SetWindowTextW(L"run duration:" +tmp+ L" /s\ndelta_R: " +tmp1+ L" mOhm\nmid_R: " +tmp2+ L" Ohm\ndelta_R/R: " +tmp3+ L" mOhm/Ohm\n\nslope_pre: " +tmp4+ L" mOhm/s\nslope_post: " +tmp5+ L" mOhm/s");
	m_run_duration.ShowWindow(SW_SHOW);
	

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
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
		//m_grafico_run = new grafico_ver2;
		m_grafico_run->assegna(&m_graph_run_C);
		m_grafico_run->back_ground_color[0] = 240;
		m_grafico_run->back_ground_color[1] = 255;
		m_grafico_run->back_ground_color[2] = 240;
		m_grafico_run->riempi_tutto();
		m_grafico_run->sposta_label_x_axis(5);
		CRecRunMeas->MoveFirst();
		double t_min = CRecRunMeas->m_time;
		CRecRunMeas->MoveLast();
		double t_max = CRecRunMeas->m_time;
		double* temp;
		temp = new (double[vector_size]);
		for (int i = 0; i < vector_size; i++)
		{
			temp [i]= m_vector_run[i][1];
		}
		
		double y_min = minimum(temp, vector_size);
		double y_max = maximum(temp, vector_size);
		m_grafico_run->coordinate(t_min, t_max, y_min - (y_max - y_min)*0.10, y_max + (y_max - y_min)*0.10); // Center the plot leaving a little space above and below.
		m_grafico_run->cambia_colore_frame(0, 50, 0, 1);
		m_grafico_run->CambiaColore(200, 0, 0, 2);
		m_grafico_run->x_tick_change((t_max - t_min) / 5.);
		m_grafico_run->y_tick_change((y_max - y_min) / 5.);
		m_grafico_run->plotta_frame(); 
		//m_grafico_run->coordinate(t_min, t_max, y_min, y_max);
		//m_grafico_core->x_tick_change(600);

		//m_grafico_core->y_tick_change((y_max - y_min) / 5.); // Divides the vertical space in 5 blocks (plots four grid lines) 
		m_grafico_run->plotta_frame();
		m_grafico_run->plot_vettore(m_vector_run, 0, vector_size - 1); /* re-plot the entire run vector */
				
		// int run_duration = (int)delta_T / 2.0; //(int)(CRecRunId->m_t_mon_end - CRecRunId->m_t_mon_begin);
		
		m_grafico_run->CambiaColore(0, 0, 200, 4);
		m_grafico_run->plot_vettore(m_vector_preDriftRegression, 0, fit_vector_sizes);
		m_grafico_run->plot_vettore(m_vector_postDriftRegression, 0, fit_vector_sizes);
	
		CDialogEx::OnPaint();
	}
}


HCURSOR CDialogRunAnalyze::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return CDialogEx::OnQueryDragIcon();
}



double CDialogRunAnalyze::maxi(double*vector)
{
	double max = 0.0;
	double(*Y);
	Y = new (double[vector_size]);
	for (int i = 0; i < vector_size; i++)
	{
		Y[i] = vector[i];
	}

	//ordino il vettore Y:
	MergeSort(Y, 0, vector_size - 1);
	max = Y[vector_size - 1];
	return max;
}



double CDialogRunAnalyze::mini(double*vector)
{
	double min = 0;
	double(*Y);
	Y = new (double[vector_size]);
	for (int i = 0; i < vector_size; i++)
	{
			Y[i] = vector[i];
	}

	//ordino il vettore Y:
	MergeSort(Y, 0, vector_size - 1);

	// il max + l'ultima componente del vettore:
	min = Y[0];
	
	return min;
}

void  CDialogRunAnalyze::MergeSort(double*vector, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		MergeSort(vector, 0, center);
		MergeSort(vector, center + 1, right);
		Merge(vector, 0, center, right);
	}
	return;
}

void  CDialogRunAnalyze::Merge(double*vector, int left, int center, int right)
{
	double* B;
	B = new (double[right-left]);

	int i, j;
	for (i = center + 1; i > left; i--)
	{
		B[i - 1] = vector[i - 1];
	}

	for (j = center; j < right; j++)
	{
		B[right + center - j] = vector[j + 1];
	}

	for (int k = left; k <= right; k++)
	{
		if (B[j] < B[i]) vector[k] = B[j--];
		else vector[k] = B[i++];
	}

	return;
}

/*
void StatisticaBase::MergeD(CArray<double, double>* X, int left, int center, int right)
{
	CArray<double, double> B;
	B.SetSize(X->GetSize());

	int i, j;
	for (i = center + 1; i > left; i--)
	{
		B[i - 1] = (*X)[i - 1];
	}

	for (j = center; j < right; j++)
	{
		B[right + center - j] = (*X)[j + 1];
	}

	for (int k = left; k <= right; k++)
	{
		if (B[j] < B[i]) (*X)[k] = B[j--];
		else (*X)[k] = B[i++];
	}

	return;

}*/


double CDialogRunAnalyze::maximum(double*vector, int size)
{
	double max = NULL;
	int i;
	for (i = 0; i<size; i++) {
		if (max<vector[i])
		{
			max = vector[i];
		}
	}

	return max;
}

double CDialogRunAnalyze::minimum(double*vector, int size)
{
	int i;
	double min = 100000.0;
	for (i = 0; i<size; i++) {
		if (min>vector[i])
		{
			min = vector[i];
		}
	}
	return min;
}