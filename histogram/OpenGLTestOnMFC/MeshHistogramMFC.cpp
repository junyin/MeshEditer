
// CMeshHistogramMFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MeshHistogramMFC.h"
#include "MeshHistogramMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMeshHistogramMFCApp

BEGIN_MESSAGE_MAP(CMeshHistogramMFCApp, CWinAppEx)
	ON_COMMAND(ID_HELP, CWinAppEx::OnContextHelp)
END_MESSAGE_MAP()

// CMeshHistogramMFCApp construction

CMeshHistogramMFCApp::CMeshHistogramMFCApp()
{
	
	// Place all significant initialization in InitInstance
}


// The one and only CMeshHistogramMFCApp object

CMeshHistogramMFCApp theApp;


// CMeshHistogramMFCApp initialization

BOOL CMeshHistogramMFCApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);


	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CMeshHistogramMFCDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
