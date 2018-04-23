#include "stdafx.h"
#include "run.h"
// #include "minervaRxDlg.h"

run::run(CString directory) // The constructor will be invoked with the name of the directory where output shall be written to.
{
	path = directory;
}

run::~run()
{
	if (run_file)
		run_file.Close();
	if (buffer_vect)
		delete[] buffer_vect;
}

bool run::create_electric_run_file()
{
	CTime time_now = CTime::GetCurrentTime();
	// CString path;
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

	return TRUE
		;
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

