// fit_gauss_mario.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// Cfit_gauss_marioApp:
// See fit_gauss_mario.cpp for the implementation of this class
//

class Cfit_gauss_marioApp : public CWinApp
{
public:
	Cfit_gauss_marioApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cfit_gauss_marioApp theApp;