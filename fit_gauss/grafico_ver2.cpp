// grafico_ver2.cpp: implementation of the grafico_ver2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "grafico_ver2.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

grafico_ver2::grafico_ver2()
: m_p_CDC_Compatibile(NULL)
, m_polar_max_radius(0)
, m_polar_max_theta(0)
{
	red=0;
	green=255;
	blue=0;
	m_pen_thickness=1;
	penna_line.CreatePen(PS_SOLID,m_pen_thickness,RGB(red,green,blue));
	penna_frame.CreatePen(PS_SOLID,m_pen_thickness,RGB(red,green,blue));
	m_caption_bool = FALSE;
	m_origine_x=0;
	m_origine_y=0;
	m_xmin=0;
	m_xmax=100;
	m_ymin=0;
	m_ymax=100;
	back_ground_color[0] = 70;
	back_ground_color[1] = 70;
	back_ground_color[2] = 70;
	back_ground_color_out[0] = 70;
	back_ground_color_out[1] = 70;
	back_ground_color_out[2] = 70;
m_x_shift=0;
	m_y_shift=1;
	m_grid=TRUE;
	m_margine_inferiore = 5; //per cento!
    m_margine_inferiore_pixels=0;
	m_margine_superiore_pixels =0;
    m_margine_sinistra_pixels=0;
	m_margine_destra_pixels =0;
	m_p_CDC_Compatibile = NULL;
	m_p_Bitmap = NULL;
	m_p_swap_CDC = NULL;
}

grafico_ver2::~grafico_ver2()
{
penna_line.DeleteObject();
penna_frame.DeleteObject();
carattere.DeleteObject();
if (m_p_CDC_Compatibile)
{
	delete	m_p_CDC_Compatibile;
	delete m_p_Bitmap;
}

}

BOOL grafico_ver2::assegna(CWnd *p)
{
puntatoreCDC = p->GetDC();
BOOL esito= (puntatoreCDC!=NULL);
dimensioni_area_di_stampa();
return (esito);

}

BOOL grafico_ver2::assegna(CDC *puntatore)
{
puntatoreCDC = puntatore;
BOOL esito= (puntatoreCDC!=NULL);
dimensioni_area_di_stampa();
return (esito);

}

VOID grafico_ver2::test(int x, int y)
{


}

BOOL grafico_ver2::CambiaColore(int r, int g, int b, int t)
{
red=r;
green=g;
blue=b;
m_pen_thickness = t;
penna_line.DeleteObject();
return(	penna_line.CreatePen(PS_SOLID,m_pen_thickness,RGB(red,green,blue)));

}
BOOL grafico_ver2::cambia_colore_frame(int r, int g, int b, int t)
{
red=r;
green=g;
blue=b;
m_pen_thickness = t;
penna_frame.DeleteObject();
return(	penna_frame.CreatePen(PS_SOLID,m_pen_thickness,RGB(red,green,blue)));

}

BOOL grafico_ver2::CambiaColore(COLORREF colore, int t)
{
red=GetRValue(colore);
green=GetGValue(colore);
blue=GetBValue(colore);

m_pen_thickness = t;
penna_line.DeleteObject();
return(	penna_line.CreatePen(PS_SOLID,m_pen_thickness,colore));

}
CSize grafico_ver2::dimensioni_area_di_stampa()
{
 CWnd *finestra;
  
 finestra = puntatoreCDC->GetWindow();
	m_origine_x=0;
	m_origine_y=0;

    if (finestra)
	{
		finestra->GetClientRect(&m_Polar_rect);
       
		m_larghezza = m_Polar_rect.Width();
		m_altezza = m_Polar_rect.Height();
	}
	else
	{
		m_larghezza = puntatoreCDC->GetDeviceCaps(HORZRES);
		m_altezza = puntatoreCDC->GetDeviceCaps(VERTRES);
	}
	m_size_area_stampa.cx=m_larghezza;
	m_size_area_stampa.cy=m_altezza;
	CRgn regione;
	regione.CreateRectRgn(m_origine_x,m_origine_y,m_larghezza,m_altezza);
     puntatoreCDC->SelectClipRgn(&regione);
	carattere.DeleteObject();
	carattere.CreatePointFont(80,"Times New Roman\0",puntatoreCDC);
//    m_margine_inferiore_pixels = m_altezza*m_margine_inferiore/100.;
//	m_altezza -= m_margine_inferiore_pixels;
	m_altezza_originale = m_altezza;
	m_larghezza_originale = m_larghezza;
	return(m_size_area_stampa);


}

CPoint grafico_ver2::caption(CString testo, long x, long y, BOOL caption_bool)
{
m_caption = testo;
m_coordinate_caption.x = m_origine_x + (m_larghezza*x)/100;
m_coordinate_caption.y = m_origine_y + (m_altezza - (m_altezza*y)/100);
m_caption_bool = caption_bool;
return(m_coordinate_caption);


}

int grafico_ver2::coordinate(double x1, double x2, double y1, double y2)
{
	m_xmin=x1;
	m_xmax=x2;
	m_ymin=y1;
	m_ymax=y2;
	int esponente=0;

	m_fattore_y = (m_altezza-1)/(m_ymax-m_ymin);
	m_fattore_x = (m_larghezza-1)/(m_xmax-m_xmin);
	m_tick_x = log10(fabs(m_xmax-m_xmin));
	if (m_tick_x>0) 
	{
		esponente = (int)m_tick_x;
	}
	else
	{
		esponente = (int)m_tick_x-1;
	}
	m_tick_x = (int) (((m_xmax-m_xmin)/5.)/pow(10.,esponente-1));
	m_tick_x *=pow(10.,esponente-1);

	m_tick_y = log10(fabs(m_ymax-m_ymin));
	if (m_tick_y>0) 
	{
		esponente = (int)m_tick_y;
	}
	else
	{
		esponente = (int)m_tick_y-1;
	}
	m_tick_y = (int) (((m_ymax-m_ymin)/5.)/pow(10.,esponente-1));
	m_tick_y *=pow(10.,esponente-1);
    m_tick_x_start = m_xmin;
    m_tick_y_start = m_ymin;


	return(1);






}

VOID grafico_ver2::plot_single_point(double x, double y, BOOL primo_punto)
{
	 puntatoreCDC->SelectObject(&penna_line);

	
    CPoint punto = converti_xy_in_punto(x,y);

	if (primo_punto)
	{
		m_last_point =   punto;
		if (m_caption_bool)
		{
			 CFont *pippo =   puntatoreCDC->SelectObject(&carattere);

			puntatoreCDC->SetTextColor(RGB(red,green,blue));
			puntatoreCDC->SetBkMode(OPAQUE);
BOOL esito=			puntatoreCDC->TextOut(m_coordinate_caption.x,
				m_coordinate_caption.y,m_caption);
             int p=0;
		}
	}
	if(punto_plottabile(x,y))
	{
	puntatoreCDC->MoveTo(punto);

	puntatoreCDC->LineTo(m_last_point);
	}
		m_last_point =   punto;
	 


		
}

VOID grafico_ver2::ridimensiona(int sinistra, int destra, int alto, int basso)
{
	m_origine_x += m_larghezza*(sinistra)/100.;
	long bordo = m_larghezza*( destra)/100.;
	m_larghezza = m_larghezza-m_origine_x-bordo;

	m_origine_y += m_altezza*(alto)/100.;
	bordo = m_altezza*( basso)/100.;
	m_altezza=m_altezza-m_origine_y-bordo;




}

BOOL grafico_ver2::cambia_font(LOGFONT *puntatore_font)
{
	carattere.DeleteObject();
	puntatore_font->lfHeight*=10;
BOOL esito =	carattere.CreatePointFontIndirect(puntatore_font,NULL);
	 return(esito);

}

VOID grafico_ver2::riempi_sfondo()
{

	puntatoreCDC->FillSolidRect(m_origine_x-m_margine_sinistra_pixels,m_origine_y-m_margine_superiore_pixels,
		m_larghezza+m_margine_sinistra_pixels+m_margine_destra_pixels,m_altezza+m_margine_inferiore_pixels+m_margine_superiore_pixels,
		RGB(back_ground_color[0],back_ground_color[1],back_ground_color[2]));

}


VOID grafico_ver2::plotta_frame()
{

 riempi_sfondo();
 	 puntatoreCDC->SelectObject(&penna_frame);
	 puntatoreCDC->SelectObject(&carattere);
	 puntatoreCDC->SetBkMode(TRANSPARENT);
	 LOGPEN struttura_penna;
	 penna_frame.GetLogPen(&struttura_penna);

	 puntatoreCDC->SetTextColor(struttura_penna.lopnColor);

	 puntatoreCDC->MoveTo(m_origine_x,m_origine_y);
	 puntatoreCDC->LineTo(m_origine_x,m_altezza-1+m_origine_y);
	 puntatoreCDC->LineTo(m_larghezza-1+m_origine_x,m_altezza-1+m_origine_y);
	 puntatoreCDC->LineTo(m_larghezza-1+m_origine_x,m_origine_y);
	 puntatoreCDC->LineTo(m_origine_x,m_origine_y);

	 double x=m_tick_x_start,y=m_tick_y_start;
	 long  posizione_x,posizione_y;
	 long shift_x= m_altezza*m_x_shift/100;
	 long shift_y = m_larghezza*m_y_shift/100;
	 CString label;
     CPen penna_grid;
	 struttura_penna.lopnStyle =PS_DOT;
	 penna_grid.CreatePenIndirect(&struttura_penna);
	 puntatoreCDC->SelectObject(&penna_grid);

	 while (x <= m_xmax)
	 {
		 label.Format("%G",x);
		 posizione_x =  ((x-m_xmin)*m_fattore_x)+m_origine_x;
		 posizione_y = m_origine_y +m_altezza-1- ((y-m_ymin)*m_fattore_y);
		 puntatoreCDC->TextOut(posizione_x+3,posizione_y-shift_x,label);
		 puntatoreCDC->MoveTo(posizione_x,posizione_y);
		 posizione_y -=5;
       if (m_grid)
	   {
		 posizione_y = m_origine_y ;
		  } 
	   puntatoreCDC->LineTo(posizione_x,posizione_y);
			
	 
		 x+=m_tick_x;

	 }
    
	 while (y <= m_ymax)
	 {
		 label.Format("%G",y);
		 posizione_x = m_origine_x ;
		 posizione_y = m_origine_y +m_altezza - 1 -((y-m_ymin)*m_fattore_y);
		 puntatoreCDC->TextOut(posizione_x+shift_y,posizione_y,label);
 		 puntatoreCDC->MoveTo(posizione_x,posizione_y);
		 posizione_x +=5;
      if (m_grid)
	   {
		 posizione_x = m_origine_x+m_larghezza ;
	   }
		 puntatoreCDC->LineTo(posizione_x,posizione_y);
			
		 y+=m_tick_y;

	 }


  


}

VOID grafico_ver2::grid_on(BOOL griglia)
{
 m_grid=griglia;
}

double grafico_ver2::x_axis_start_label(double x)
{

	double buffer =m_tick_x_start ;
	m_tick_x_start=x ;
	return(buffer);
}

double grafico_ver2::y_axis_start_label(double y)
{
	double buffer =m_tick_y_start ;
	m_tick_y_start=y ;
	return(buffer);
}

double grafico_ver2::x_tick_change(double x)
{
	double buffer =m_tick_x ;
	m_tick_x=x ;
	return(buffer);
}

double grafico_ver2::y_tick_change(double y)
{
	double buffer =m_tick_y ;
	m_tick_y=y ;
	return(buffer);
}

VOID grafico_ver2::plotta_cursore(double x, double y)
{
	 puntatoreCDC->SelectObject(&penna_line);
	 CPoint pivot = converti_xy_in_punto(x,y);

	 pivot.Offset(-1,0);
     puntatoreCDC->MoveTo(pivot);
	 pivot.Offset(-6,0);
	 puntatoreCDC->LineTo(pivot);
	 pivot.Offset(+7,0);

	 pivot.Offset(+1,0);
     puntatoreCDC->MoveTo(pivot);
	 pivot.Offset(+6,0);
	 puntatoreCDC->LineTo(pivot);
	 pivot.Offset(-7,0);
 
	 pivot.Offset(0,-1);
     puntatoreCDC->MoveTo(pivot);
	 pivot.Offset(0,-6);
	 puntatoreCDC->LineTo(pivot);
	 pivot.Offset(0,+7);

	 pivot.Offset(0,+1);
     puntatoreCDC->MoveTo(pivot);
	 pivot.Offset(0,+6);
	 puntatoreCDC->LineTo(pivot);
	 pivot.Offset(0,-7);
 




}

CPoint grafico_ver2::converti_xy_in_punto(double x, double y)
{
	long punto_x = (0.5+(x-m_xmin)*m_fattore_x)+m_origine_x;
	long punto_y = m_origine_y +m_altezza- (0.5+(y-m_ymin)*m_fattore_y)-1;
    CPoint punto(punto_x,punto_y);
	return(punto);



}

VOID grafico_ver2::freccia(double x, double y, BOOL verso_alto)
{
	 CPoint pivot = converti_xy_in_punto(x,y);
	 puntatoreCDC->SelectObject(&penna_line);

	 double verso;
	 if (verso_alto)
	 {
		 verso = 1.0;
	 }
	 else
	 {
		 verso = -1.0;
	 }

	 puntatoreCDC->MoveTo(pivot);
	 pivot.Offset(0,verso*9);
	 puntatoreCDC->LineTo(pivot);
	 pivot.Offset(0,verso*(-9));

	 puntatoreCDC->MoveTo(pivot);
     pivot.Offset(3,verso*3);
	 puntatoreCDC->LineTo(pivot);
	 pivot.Offset(-3,verso*(-3));

	 puntatoreCDC->MoveTo(pivot);
     pivot.Offset(-3,verso*3);
	 puntatoreCDC->LineTo(pivot);
	 pivot.Offset( 3,verso*(-3));





}

BOOL grafico_ver2::punto_plottabile(double x, double y)
{

	BOOL esito=TRUE;
	if (x<m_xmin | x>m_xmax | y<m_ymin | y > m_ymax) esito = FALSE;
	return (esito);
}

VOID grafico_ver2::plot_vettore(double  vettore[][2], int punto_iniziale, int punto_finale)
{
 int  dimensione = punto_finale-punto_iniziale+1;
	if (dimensione<2) return;
CPoint *poliline;
poliline = new CPoint[dimensione];


int ctr=0,ctr1=punto_iniziale;
	 puntatoreCDC->SelectObject(&penna_line);
while (ctr1<=punto_finale)
{
	if (punto_plottabile(vettore[ctr1][0], vettore[ctr1][1]))
		{
		*(poliline+ctr) = converti_xy_in_punto(vettore[ctr1][0], vettore[ctr1][1]);
           ctr++;
		   
		}
	else
	{
		 puntatoreCDC->Polyline(poliline,ctr);
		 ctr=0;
	}


ctr1++;
}

  puntatoreCDC->Polyline(poliline,ctr);

		if (m_caption_bool)
		{
			 CFont *pippo =   puntatoreCDC->SelectObject(&carattere);

			puntatoreCDC->SetTextColor(RGB(red,green,blue));
			puntatoreCDC->SetBkMode(TRANSPARENT);
BOOL esito=	puntatoreCDC->TextOut(m_coordinate_caption.x,
				m_coordinate_caption.y,m_caption);
             
		}
		delete [] poliline;

}

BOOL grafico_ver2::converti_punto_in_xy(CPoint punto, double *x, double *y)
{
BOOL esito =FALSE;


	double x1= ((punto.x -m_origine_x)/m_fattore_x) + m_xmin;
	double y1= ((-punto.y +m_origine_y+m_altezza-1)/m_fattore_y) + m_ymin;
    esito = punto_plottabile(x1,y1);
	*x = x1;
	*y = y1;
	return(esito);



}

VOID grafico_ver2::sposta_label_y_axis(double y_percento)
{
 m_y_shift = y_percento;

}
VOID grafico_ver2::sposta_label_x_axis(double x_percento)
{
 m_x_shift = x_percento;

}

VOID grafico_ver2::sposta_asse_x(double percento_basso,double percento_alto)
{
m_margine_inferiore = percento_basso;
m_margine_inferiore_pixels = m_altezza*m_margine_inferiore/100;
m_margine_superiore_pixels  =  m_altezza*percento_alto/100;
m_altezza -= m_margine_inferiore_pixels;
m_altezza -= m_margine_superiore_pixels;
m_origine_y +=m_margine_superiore_pixels;


}

VOID grafico_ver2::sposta_asse_y(double percento_sinistra,double percento_destra)
{
m_margine_sinistra_pixels = m_larghezza*percento_sinistra/100;
m_margine_destra_pixels  =  m_larghezza*percento_destra/100;
m_larghezza -= m_margine_sinistra_pixels;
m_larghezza -= m_margine_destra_pixels;
m_origine_x +=m_margine_sinistra_pixels;


}

int grafico_ver2::riempi_tutto(void)
{
	 CWnd *finestra;
 CRect rettangolo;
 finestra = puntatoreCDC->GetWindow();
	int origine_x=0;
	int origine_y=0;
    int larghezza =0;
	int altezza=0;
    if (finestra)
	{
		finestra->GetClientRect(&rettangolo);
       
		 larghezza = rettangolo.Width();
		 altezza = rettangolo.Height();
	}
	else
	{
		 larghezza = puntatoreCDC->GetDeviceCaps(HORZRES);
		 altezza = puntatoreCDC->GetDeviceCaps(VERTRES);
	}
puntatoreCDC->FillSolidRect(origine_x,origine_y,
		larghezza,altezza,
		RGB(back_ground_color_out[0],back_ground_color_out[1],back_ground_color_out[2]));

	return 0;
}

int grafico_ver2::draw_y_label(void)
{
 	 puntatoreCDC->SelectObject(&carattere);
	 puntatoreCDC->SetBkMode(TRANSPARENT);
	 LOGPEN struttura_penna;
	 penna_frame.GetLogPen(&struttura_penna);
	 puntatoreCDC->SetTextColor(struttura_penna.lopnColor);


	 double x=m_tick_x_start,y=m_tick_y_start;
	 long  posizione_x,posizione_y;
	 long shift_x= m_altezza*m_x_shift/100;
	 long shift_y = m_larghezza*m_y_shift/100;
	 CString label;
 
    
	 while (y <= m_ymax)
	 {
		 label.Format("%G",y);
		 posizione_x = m_origine_x ;
		 posizione_y = m_origine_y +m_altezza - 1 -((y-m_ymin)*m_fattore_y);
		 puntatoreCDC->TextOut(posizione_x+shift_y,posizione_y,label);
 		 puntatoreCDC->MoveTo(posizione_x,posizione_y);
		 posizione_x +=5;
     
			
		 y+=m_tick_y;

	 }

 return(0);
}

int grafico_ver2::plotta_punto(double x, double y, int size)
{
	if(!punto_plottabile(x,y)) return 0;
	 CPoint pivot = converti_xy_in_punto(x,y);
	if (size)
	{
	    CBrush pennello(COLORREF(RGB(red,green,blue)));
        puntatoreCDC->SelectObject(&pennello);
        puntatoreCDC->SelectObject(&penna_line);
		puntatoreCDC->Ellipse(pivot.x-size,pivot.y-size,pivot.x+size+1,pivot.y+size+1);
	}
	else
	{
	 puntatoreCDC->SelectObject(&penna_line);
     puntatoreCDC->MoveTo(pivot);
	 puntatoreCDC->LineTo(pivot.x+1,pivot.y);
	}
		return 0;
}


CDC * grafico_ver2::crea_CDC_compatibile()
{
	m_p_CDC_Compatibile = new CDC;
	m_p_Bitmap = new CBitmap;
	BOOL esito = m_p_CDC_Compatibile->CreateCompatibleDC(puntatoreCDC);
	
	

	esito = m_p_Bitmap->CreateCompatibleBitmap(puntatoreCDC, m_larghezza_originale, m_altezza_originale);
	  m_p_CDC_Compatibile->SelectObject(m_p_Bitmap);

	return m_p_CDC_Compatibile;
}


int grafico_ver2::swap_CDC()
{
	crea_CDC_compatibile();
	if (puntatoreCDC && m_p_CDC_Compatibile)
	{
		m_p_swap_CDC = puntatoreCDC;
	  puntatoreCDC = m_p_CDC_Compatibile;
	}
	

	return 0;
}


int grafico_ver2::show_compatible_CDC()
{
	if (m_p_swap_CDC && m_p_CDC_Compatibile)
		m_p_swap_CDC->StretchBlt(0, 0, m_larghezza_originale, m_altezza_originale, m_p_CDC_Compatibile, 0, 0, m_larghezza_originale, m_altezza_originale, SRCCOPY);

	return 0;
}


int grafico_ver2::crea_polar_plot()
{
	
	 
	 
	int h = m_Polar_rect.Height();
	int w = m_Polar_rect.Width();
	int deflate = (w - h) / 2;
	m_Polar_rect.InflateRect(0, deflate);
	CPoint p1 = m_Polar_rect.BottomRight(), p2 = m_Polar_rect.TopLeft();
	CPen penBlue;
	CPen interm(PS_DOT, 1, RGB(255, 0, 100));
	penBlue.CreatePen(PS_SOLID | PS_COSMETIC, 1, RGB(0, 0, 255));
	 puntatoreCDC->SelectObject(&penBlue);
	 puntatoreCDC->Arc(m_Polar_rect, p1, p2);
	 puntatoreCDC->Arc(m_Polar_rect, p2, p1);
	 CBrush pennello(COLORREF(RGB(255, 255, 0)));
	 puntatoreCDC->SelectObject(&pennello);
	puntatoreCDC->FloodFill(100, 100, RGB(0, 0, 255));
	int ctr = 0;
	int centro_top = (m_Polar_rect.right + m_Polar_rect.left) / 2;
	int centro_right = (m_Polar_rect.top + m_Polar_rect.bottom) / 2;
	puntatoreCDC->MoveTo(centro_top, m_Polar_rect.top);
	puntatoreCDC->LineTo(centro_top, m_Polar_rect.bottom);
	puntatoreCDC->MoveTo(m_Polar_rect.left, centro_right);
	puntatoreCDC->LineTo(m_Polar_rect.right, centro_right);
	int step = m_Polar_rect.Height() / 8;
 puntatoreCDC->SelectObject(&interm);
 CRect rettangolo = m_Polar_rect;
	while (ctr < 4)
	{
		rettangolo.DeflateRect(step, step);
		 puntatoreCDC->Arc(rettangolo, p1, p2);
		 puntatoreCDC->Arc(rettangolo, p2, p1);
		ctr++;

	}
	return 0;
}


int grafico_ver2::m_plot_polar(double theta, double radius, BOOL primo=FALSE, BOOL last=FALSE)
{
	puntatoreCDC->SelectObject(&penna_line);
	CPoint xy_min = m_Polar_rect.TopLeft();
	CPoint yx_max = m_Polar_rect.BottomRight();
	CPoint center = m_Polar_rect.CenterPoint();
	int Width = m_Polar_rect.Width();
	double duepigreco = 6.283185307179586476925286766559;
	double rotazionemeno90 = -1.5707963267948966192313216916398;
	double x = 0.5*Width*(radius / m_polar_max_radius)*cos(duepigreco*theta / m_polar_max_theta + rotazionemeno90);
	double y = 0.5*Width*(radius / m_polar_max_radius)*sin(duepigreco*theta / m_polar_max_theta + rotazionemeno90);
	CPoint punto(x, y);
	CPoint punto_finale = punto + center;
	if (primo)
	{
		puntatoreCDC->MoveTo(punto_finale);
	}
	puntatoreCDC->LineTo(punto_finale);
 //	puntatoreCDC->LineTo(center);
	//puntatoreCDC->LineTo(100, 100);
	if (last)
	{
		int size = 2;
		if (size)
		{
			CBrush pennello(COLORREF(RGB(red, green, blue)));
			puntatoreCDC->SelectObject(&pennello);
			puntatoreCDC->SelectObject(&penna_line);
			puntatoreCDC->Ellipse(punto_finale.x - size, punto_finale.y - size, punto_finale.x + size + 1, punto_finale.y + size + 1);
		}
	}
	return 0;
}
