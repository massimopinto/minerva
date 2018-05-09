#include "stdafx.h"
#include "run.h"

run::run(CString directory, int last_index, double(* vector)[2], BOOL electric) // The constructor will be invoked with the name of the directory where output shall be written to.
{
	path = directory;
	
	filetype = electric;
	//create_electric_run_file();
	//else create_radiation_run_file();
	buffer_vect = new (double[DIM_VECT_BUFFER][2]); 
	for (int ctr = 0; ctr < DIM_VECT_BUFFER; ctr++) // Copies the last DIM_VECT_BUFFER values of vector in the protected buffer_vect
	{
		buffer_vect[ctr][0] = 0.0;
		buffer_vect[ctr][1] = 0.0;
	}
	
	for (int ctr = 0; ctr < DIM_VECT_BUFFER; ctr++) // Copies the last DIM_VECT_BUFFER values of vector in the protected buffer_vect
	{
		if (last_index - ctr >= 0)
		{
			buffer_vect[DIM_VECT_BUFFER - 1 - ctr][0] = vector[last_index - ctr][0]; // with m_core_vector in mind, this was created with size 'DIM_VET_CORE + 2'
			buffer_vect[DIM_VECT_BUFFER - 1 - ctr][1] = vector[last_index - ctr][1];
		}
		else
			break;
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
bool run::create_run_file()
{
	CTime  time_now = CTime::GetCurrentTime();
	CString suffix;
	if (filetype == TRUE) suffix = L"_radiation.dat";
	else suffix = L"_electric.dat";
	CString now = path + time_now.Format(L"%Y_%m_%d_%H_%M__") + t1 + L"_" + t2 + suffix;
	run_file.Abort();
	BOOL whatsup = run_file.Open(now, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);
	if (run_file.m_hFile != CFile::hFileNull)
	{
		CString aux = L" Seconds \tResistance(Ohm)\n";
		run_file.WriteString(aux);
	}
	else
		AfxMessageBox(L"Could not open radiation run log file");

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
	// run::~run();
	return;
}