// regressione.cpp : implementation file
//

#include "stdafx.h"
#include "regressione.h"


// regressione

IMPLEMENT_DYNAMIC(regressione, CWnd)
regressione::regressione()
: m_coefficiente_angolare(0)


, m_numero_punti(0)
, m_x_medio(0)
, m_standard_dev(0)

{
	m_valori=NULL;
	t_student_005 = new double[31];
    t_student_005[0]=636.6;
    t_student_005[1]=31.60;
    t_student_005[2]=12.92;
    t_student_005[3]=8.610;
    t_student_005[4]=6.869;
    t_student_005[5]=5.959;
    t_student_005[6]=5.408;
    t_student_005[7]=5.041;
    t_student_005[8]=4.781;
    t_student_005[9]=4.587;
    t_student_005[10]=4.437;
    t_student_005[11]=4.318;
    t_student_005[12]=4.221;
    t_student_005[13]=4.140;
    t_student_005[14]=4.073;
    t_student_005[15]=4.015;
    t_student_005[16]=3.965;
    t_student_005[17]=3.922;
    t_student_005[18]=3.883;
    t_student_005[19]=3.85;
    t_student_005[20]=3.819;
    t_student_005[21]=3.792;
    t_student_005[22]=3.767;
    t_student_005[23]=3.745;
    t_student_005[24]=3.725;
    t_student_005[25]=3.707;
    t_student_005[26]=3.69;
    t_student_005[27]=3.674;
    t_student_005[28]=3.659;
    t_student_005[29]=3.646;
    t_student_005[30]=3.291;


}

regressione::~regressione()
{
	delete [] m_valori;
	delete [] t_student_005;
}


BEGIN_MESSAGE_MAP(regressione, CWnd)
END_MESSAGE_MAP()



// regressione message handlers


int regressione::calcola_regressione(double x[], double y[], int punto_start, int punto_stop)
{
    m_numero_punti=punto_stop-punto_start+1;
	if (m_valori) delete [] m_valori;
	m_valori = new double[m_numero_punti][2];
	long ctr=0;
	while (ctr<m_numero_punti)
	{
		m_valori[ctr][0]=x[punto_start+ctr];
		m_valori[ctr][1]=y[punto_start+ctr];
		ctr++;
	}
	avvia_calcolo();
	return 0;
}

int regressione::calcola_regressione(double punti[][2], int punto_start, int punto_stop)
{
	   m_numero_punti=punto_stop-punto_start+1;
	if (m_valori) delete [] m_valori;
	m_valori = new double[m_numero_punti][2];
	long ctr=0;
	while (ctr<m_numero_punti)
	{
		m_valori[ctr][0]=punti[punto_start+ctr][0];
		m_valori[ctr][1]=punti[punto_start+ctr][1];
		ctr++;
	}
	avvia_calcolo();
	return 0;
}

int regressione::avvia_calcolo(void)
{
   varianza();
   covarianza();
   m_coefficiente_angolare = m_covarianza/m_varianza;
   m_intercetta = m_y_medio - m_coefficiente_angolare*m_x_medio;
   calcolo_R();
   calcolo_incertezze();
	return 0;
}



int regressione::xy_medio(void)
{
   m_x_medio=0;
   m_y_medio=0;
   int ctr=0;
   while(ctr<m_numero_punti)
   {
	   m_x_medio+=m_valori[ctr][0];
	    m_y_medio+=m_valori[ctr][1];
	   ctr++;
   }
	m_x_medio/=m_numero_punti;
	m_y_medio/=m_numero_punti;

	return 0;
}

int regressione::varianza(void)
{
    double accumulatore=0;
		xy_medio();
		int ctr=0;
   while(ctr<m_numero_punti)
   {
	   accumulatore+=pow((m_valori[ctr][0]-m_x_medio),2);
	   ctr++;
   }
   m_varianza = accumulatore/m_numero_punti;

	return 0;
}
int regressione::covarianza(void)
{
  double accumulatore=0;
		
		int ctr=0;
   while(ctr<m_numero_punti)
   {
	   accumulatore+=((m_valori[ctr][0]-m_x_medio)*(m_valori[ctr][1]-m_y_medio));
	   ctr++;
   }
   m_covarianza = accumulatore/m_numero_punti;
	return 0;
}

int regressione::calcolo_R(void)
{

	 double SST=0;
		m_SSE=0;
		int ctr=0;
   while(ctr<m_numero_punti)
   {
	   m_SSE+=pow((m_valori[ctr][1]-m_intercetta-m_coefficiente_angolare*m_valori[ctr][0]),2);
	    SST+=pow((m_valori[ctr][1]-m_y_medio),2);
   ctr++;
   }
   m_R_square = 1 - m_SSE/SST;
	return 0;
}

int regressione::calcolo_incertezze(void)
{
	double sum_y=0,sum_square_y=0,determinante=0;
	int ctr=0;

 while(ctr<m_numero_punti)
   {
	   sum_y+=m_valori[ctr][0];
	    sum_square_y+=pow(m_valori[ctr][0],2);
	ctr++;
   }
   sum_y=sum_y*sum_y;
determinante=m_numero_punti*sum_square_y -sum_y;

double e_coefficiente_angolare = (m_SSE/(m_numero_punti-2))*(m_numero_punti/determinante);
m_standard_dev=sqrt(e_coefficiente_angolare);
	return 0;
}

double regressione::t_student(int campioni)
{
	campioni-=2; 
	if (campioni<0) return 99999;
	if (campioni>31) campioni=30;
	return (t_student_005[campioni]);

	return 0;
}
