// fit_gauss_mario.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "fit_gauss_mario.h"
#include "fit_gauss_marioDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cfit_gauss_marioApp

BEGIN_MESSAGE_MAP(Cfit_gauss_marioApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cfit_gauss_marioApp construction

Cfit_gauss_marioApp::Cfit_gauss_marioApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Cfit_gauss_marioApp object

Cfit_gauss_marioApp theApp;


// Cfit_gauss_marioApp initialization

BOOL Cfit_gauss_marioApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	Cfit_gauss_marioDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
