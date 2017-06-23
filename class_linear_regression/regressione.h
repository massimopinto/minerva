#pragma once
#include <math.h>


// regressione

class regressione : public CWnd
{
	DECLARE_DYNAMIC(regressione)

public:
	regressione();
	virtual ~regressione();

protected:
	DECLARE_MESSAGE_MAP()
public:
	double m_coefficiente_angolare;
	double m_intercetta;
	double m_covarianza;
	double m_varianza;
	double m_R_square;
	double m_SSE;
	int calcola_regressione(double x[], double y[], int punto_start, int punto_stop);
		int calcola_regressione(double punti[][2], int punto_start, int punto_stop);

		double (*m_valori)[2];
		long m_numero_punti;
private:
	int avvia_calcolo(void);
	int varianza(void);
public:
	int xy_medio(void);
	double m_x_medio;
	double m_y_medio;
	int covarianza(void);
	int calcolo_R(void);
	int calcolo_incertezze(void);
	double m_standard_dev;
	double *t_student_005;
	double t_student(int campioni);
};


