#pragma once
/* The run class offers tools for handling data output to a file when an electrical calibration is run, 
 or when heating is caused by radiation. A file is created for each run, in which time (seconds) and 
 resistance values are outputed during and around the calorimetric run. Around in this context means that
 data are provided so that linear regressions of pre-run and post-run regions can be made later. */

// An object of class run is created at the end of the run itself, and serves to handle the creation of a file containing data from the past about 480"

#define RUN_TIME 120 // Duration (in seconds) of a single heating run.
#define DRIFT_TIME 180 // Duration (in seconds) of either the pre-run or the post-run drift
#define DIM_VECT_BUFFER (int) ceil((1/0.57)*(RUN_TIME + 2* DRIFT_TIME))  // the dimesion of the buffer vector that will contain 480" of data (0.57" between two consecutive measurements)
#include "run_measurements.h"

class run // 
{
	
public:
	Crun_measurements* CRecRunMeas;
	long RUNID;
	CStdioFile run_file;
	// bool create_electric_run_file();
	bool create_run_file();
	void save_to_file();
	CString t1, t2;
	BOOL filetype;
	/* questo costruttore instanzia l'oggetto di tipo run specificando anzitutto la directory dove andrà a salvare il file testo
	   con i dati acquisiti (primo argomento), il vettore generale di grossa dimensione dove sono memorizzati i dati acquisiti del core
	   (quarto argomento), la dimensione di quest'ultimo vettore (secondo argomento), l'indice corrispondente all'istante di START del run del core (terzo argomento) */
	run(CString directory = L".", int last_index = 0, double(*vector)[2] = NULL, BOOL electric = FALSE, long RunID = 0, Crun_measurements* recMeas = NULL);
	~run();

protected:
	CString path;
	double(*buffer_vect)[2]; // The buffer vector that will hold the part of the stream of core resistance and time data that will be sent out to a run-dedicated file.

};
