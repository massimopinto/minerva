// grafico_ver2.h: interface for the grafico_ver2 class.
//
//////////////////////////////////////////////////////////////////////

#include "atltypes.h"
#if !defined(AFX_GRAFICO_VER2_H__06B295E0_DB7D_4730_881E_9F2956669CBC__INCLUDED_)
#define AFX_GRAFICO_VER2_H__06B295E0_DB7D_4730_881E_9F2956669CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class grafico_ver2  
{
public:
	int m_margine_sinistra_pixels;
	int m_margine_destra_pixels;
	int m_margine_superiore_pixels;
	VOID sposta_asse_x(double percento_basso,double percento_alto=0.);
	VOID sposta_asse_y(double percento_sinistra,double percento_destra=0.);
	VOID sposta_label_y_axis(double y_percento);
	VOID sposta_label_x_axis(double x_percento);
	BOOL converti_punto_in_xy(CPoint punto,double *x,double *y);
	VOID plot_vettore(double  vettore[][2],int punto_iniziale, int punto_finale);
	BOOL punto_plottabile(double x,double y);
	VOID freccia(double x,double y,BOOL verso_alto = TRUE);
	CPoint converti_xy_in_punto(double x,double y);
	VOID plotta_cursore(double x,double y);
	double y_tick_change(double y);
	double x_tick_change(double x);
	double y_axis_start_label(double y);
	double x_axis_start_label(double x);
	double m_tick_x_start;
	double m_tick_y_start;
	long m_margine_inferiore_pixels;
	long m_margine_inferiore;
	float m_y_shift;
	VOID grid_on(BOOL griglia=TRUE);
	BOOL m_grid;
	float m_x_shift;
	VOID plotta_frame();
	VOID riempi_sfondo();
	long back_ground_color[3];
	long back_ground_color_out[3];
	BOOL cambia_font(LOGFONT *puntatore_font);
	VOID ridimensiona(int sinistra,int destra,int alto,int basso);
	double m_tick_y;
	CPoint m_last_point;
	CFont carattere;
	VOID plot_single_point(double x,double y,BOOL primo_punto=FALSE);
	double m_tick_x;
	double m_fattore_x;
	double m_fattore_y;
	double m_xmin;
	double m_xmax;
	double m_ymin;
	double m_ymax;
	int coordinate(double x1,double x2,double y1,double y2);
	CPoint m_coordinate_caption;
	long m_origine_y;
	long m_origine_x;
	CPoint caption(CString testo,long x,long y,BOOL caption_bool=TRUE);
	CString m_caption;
	BOOL m_caption_bool;
	CSize m_size_area_stampa;
	long m_altezza;
	long m_larghezza;
	long m_altezza_originale;
	long m_larghezza_originale;
	CSize dimensioni_area_di_stampa();
	BOOL CambiaColore(int r,int g,int b, int t=1);
	BOOL CambiaColore(COLORREF colore, int t=1);
	BOOL cambia_colore_frame(int r,int g,int b, int t=1);
	int m_pen_thickness;
	int red;
	int green;
	int blue;
	CPen penna_frame;
	CPen penna_line;
	VOID test(int x,int y);
	CDC * puntatoreCDC;
	BOOL assegna(CDC *puntatore);
	BOOL assegna(CWnd * p);
	grafico_ver2();
	virtual ~grafico_ver2();

	int riempi_tutto(void);
	int draw_y_label(void);
	int plotta_punto(double x, double y, int size);

protected:
	CDC * crea_CDC_compatibile();
public:
	CDC * m_p_CDC_Compatibile;
	CBitmap *m_p_Bitmap;
	CDC *m_p_swap_CDC;
	int swap_CDC();
	int show_compatible_CDC();
	int crea_polar_plot();
	CRect m_Polar_rect;
	double m_polar_max_theta;
	double m_polar_max_radius;
	int m_plot_polar(double theta, double radius, BOOL primo, BOOL last);
};

#endif // !defined(AFX_GRAFICO_VER2_H__06B295E0_DB7D_4730_881E_9F2956669CBC__INCLUDED_)
