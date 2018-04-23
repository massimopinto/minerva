#pragma once
// The run class offers tools for handling data output to a file when an electrical calibration is run, 
// or when heating is caused by radiation. A file is created for each run, in which time (seconds) and 
// resistance values are outputed during and around the calorimetric run. Around in this context means that
// data are provided so that linear regressions of pre-run and post-run regions can be made later.

#define DIM_VECT_BUFFER 1000 // Size of buffer vector which holds data in and around the calorimetric run.

class run // 
{
	
public:
	CStdioFile run_file;
	double(*buffer_vect)[2];
	bool create_electric_run_file();
	bool create_radiation_run_file();
	run(CString directory);
	
	~run();
protected:
	CString path;

};
