#include "stdafx.h"
#include "run.h"
// #include "minervaRxDlg.h"

run::run(CString directory, int dim, double vector[][2]) // The constructor will be invoked with the name of the directory where output shall be written to.
{
	path = directory;
	create_electric_run_file();
	buffer_vect = new (double[DIM_VECT_BUFFER][2]);; // Copies the last DIM_VECT_BUFFER of the core matrix data.
	for (int ctr = 0; ctr < DIM_VECT_BUFFER; ctr++) // Copies the last DIM_VECT_BUFFER values of vector in the protected buffer_vect
	{
		if (vector) 
		{
			buffer_vect[DIM_VECT_BUFFER -1 -ctr][0] = vector[dim -1 -ctr][0]; // with m_core_vector in mind, this was created with size 'DIM_VET_CORE + 2'
			buffer_vect[DIM_VECT_BUFFER -1 -ctr][1] = vector[dim -1 -ctr][1];
		}
	}
}

run::~run()
{
	if (run_file)
		{
		run_file.Close();
		save_to_file();
		}
	if (buffer_vect)
		delete[] buffer_vect;
}

bool run::create_electric_run_file()
{
	CTime time_now = CTime::GetCurrentTime();
	CString now = path + time_now.Format(L"%Y_%m_%d_%H_%M_%S_electric") + L".dat";
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

bool run::create_radiation_run_file()
{
	CTime  time_now = CTime::GetCurrentTime();
	CString now = path + time_now.Format(L"%Y_%m_%d_%H_%M_%S_electric") + L".dat";
	run_file.Abort();
	BOOL whatsup = run_file.Open(now, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (run_file.m_hFile != CFile::hFileNull)
	{
		CString aux = L" Seconds \tResistance(Ohm)\n";
		run_file.WriteString(aux);
	}
	else
	{
		AfxMessageBox(L"Could not open radiation run log file");
		// add_message(L"Could not open radiation run log file " + now);
	}

	return TRUE
		;
}

void run::save_to_file() // Outputs all current run data to file and closes.
{
	if (run_file.m_hFile != CFile::hFileNull)
	{
		CString aux;
		// double seconds, resistance;
		for (int ctr = 0; ctr < DIM_VECT_BUFFER; ctr++)
			{
			aux.Format(L" %.5f \t%9.9g \n", buffer_vect[ctr][0], buffer_vect[ctr][1]);
			run_file.WriteString(aux);
			}
		run_file.Close();
	}
	// run::~run();
	return;
}