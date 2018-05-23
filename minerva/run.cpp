#include "stdafx.h"
#include "run.h"

run::run(CString directory, int last_index, double(*vector)[2], BOOL electric, int run_duration, long RunID, Crun_measurements* recMeas) // The constructor will be invoked with the name of the directory where output shall be written to.
{
	path = directory;
	
	filetype = electric;
	//create_electric_run_file();
	//else create_radiation_run_file();

	RUNID = RunID;
	CRecRunMeas = recMeas;
	
	int vector_time_span = run_duration + 2 * DRIFT_TIME;
	/* TO DO 18/05/2018 Search for the vector's index corresponding to vector_time_span behind the last point (example: 180+180+120 = 480 seconds earlier)*/
	
	// Make this obsolete when the above is fixed.
	//DIM_VECT_BUFFER = (int)ceil((1 / 0.57)*(run_duration + 2 * DRIFT_TIME));
	double last_time = vector[last_index][0];
	double first_time = last_time - vector_time_span;
	if (first_time < 0) first_time = 0;
	int first_index = 0;
	int i = last_index;
	while (vector[i][0] > first_time)
	{
		i--;

	}
	first_index = i;

	DIM_VECT_BUFFER = last_index - first_index;
	
	buffer_vect = new (double[DIM_VECT_BUFFER][2]); 
	for (int ctr = 0; ctr < DIM_VECT_BUFFER; ctr++) // Copies the last DIM_VECT_BUFFER values of vector in the protected buffer_vect
	{
		buffer_vect[ctr][0] = 0.0;
		buffer_vect[ctr][1] = 0.0;
	}
	
	for (int ctr = 0; ctr < DIM_VECT_BUFFER; ctr++) // Copies the last DIM_VECT_BUFFER values of vector in the protected buffer_vect
	{
		buffer_vect[DIM_VECT_BUFFER - 1 - ctr][0] = vector[last_index - ctr][0]; // with m_core_vector in mind, this was created with size 'DIM_VET_CORE + 2'
		buffer_vect[DIM_VECT_BUFFER - 1 - ctr][1] = vector[last_index - ctr][1];
	}	
}

run::~run()
{
	if (run_file)
		{
		run_file.Close();
		//save_to_file();
		}
	if (buffer_vect)
		delete[] buffer_vect;
}

/* bool run::create_electric_run_file()
{
	CTime time_now = CTime::GetCurrentTime();
	CString now = path + time_now.Format(L"%Y_%m_%d_%H_%M__") + t1 + L"_" + t2 + L"_electric.dat";
	run_file.Abort();
	BOOL whatsup = run_file.Open(now, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (run_file.m_hFile != CFile::hFileNull)
	{
		CString aux = L" Seconds \tResistance(Ohm)\n";
		run_file.WriteString(aux);
	}
	else
	{
		AfxMessageBox(L"Could not open electric run log file");
		// add_message(L"Could not open electric run log file " + now);
	}

	return TRUE;
}
*/ 
bool run::create_run_file() // crea il file di run e apre tabella relativa del database
{
	CTime  time_now = CTime::GetCurrentTime();
	CString suffix;
	if (filetype == TRUE) suffix = L"_electric.dat";
	else suffix = L"_radiation.dat";
	CString now = path + time_now.Format(L"%Y_%m_%d_%H_%M__") + t1 + L"_" + t2 + suffix;
	run_file.Abort();
	BOOL whatsup = run_file.Open(now, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (run_file.m_hFile != CFile::hFileNull)
	{
		CString aux;
		aux.Format(L"%d\n", RUNID);
		run_file.WriteString(aux); // 14/05/2018: insert ID RUN at the head of electric/radiation .dat file (it will used then to show the measures graph)
		
		aux = L" Seconds \tResistance(Ohm)\n";
		run_file.WriteString(aux);
	}
	else
		AfxMessageBox(L"Could not open radiation run log file");
	
	CRecRunMeas->Open();
	return TRUE;
}

void run::save_to_file() // Outputs all current run data to file and closes.
{
	/*if (filetype == FALSE) run::create_electric_run_file();
	else if (filetype == TRUE) run::create_radiation_run_file();
	else return;*/
	create_run_file();
	if (run_file.m_hFile != CFile::hFileNull)
	{
		CString aux;
		// double seconds, resistance;
		for (int ctr = 0; ctr < DIM_VECT_BUFFER; ctr++)
		{
			aux.Format(L" %.3f \t%9.9g \n", buffer_vect[ctr][0], buffer_vect[ctr][1]);
			run_file.WriteString(aux);
		}
		run_file.Close();
	}

	// measures to insert:
	for (int ctr = 0; ctr < DIM_VECT_BUFFER; ctr++)
	{
			CRecRunMeas->AddNew();
			CRecRunMeas->m_ID_RUN = RUNID;
			CRecRunMeas->m_time = buffer_vect[ctr][0];
			CRecRunMeas->m_resistance = buffer_vect[ctr][1];
			CRecRunMeas->Update();
	}
	return;
}