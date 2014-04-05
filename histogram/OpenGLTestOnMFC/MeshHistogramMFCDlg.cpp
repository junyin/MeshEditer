// MeshHistogramMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MeshHistogramMFC.h"
#include "MeshHistogramMFCDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMeshHistogramMFCDlg dialog




CMeshHistogramMFCDlg::CMeshHistogramMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMeshHistogramMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMeshHistogramMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMeshHistogramMFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(Load, &CMeshHistogramMFCDlg::OnBnClickedLoad)
	//ON_BN_CLICKED(Align, &CMeshHistogramMFCDlg::OnBnClickedAlign)
	ON_BN_CLICKED(Noise, &CMeshHistogramMFCDlg::OnBnClickedNoise)
	//ON_BN_CLICKED(RotateX, &CMeshHistogramMFCDlg::OnBnClickedRotatex)
	//ON_BN_CLICKED(RotateY, &CMeshHistogramMFCDlg::OnBnClickedRotatey)
	//ON_BN_CLICKED(RotateZ, &CMeshHistogramMFCDlg::OnBnClickedRotatez)
	ON_BN_CLICKED(Normalize, &CMeshHistogramMFCDlg::OnBnClickedNormalize)
	ON_BN_CLICKED(MeshHistogram, &CMeshHistogramMFCDlg::OnBnClickedMeshhistogram)
	ON_BN_CLICKED(VRMLExport, &CMeshHistogramMFCDlg::OnBnClickedVrmlexport)
	ON_BN_CLICKED(RemoveDV, &CMeshHistogramMFCDlg::OnBnClickedRemovedv)
END_MESSAGE_MAP()


// CMeshHistogramMFCDlg message handlers

BOOL CMeshHistogramMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CRect rect;

	// Get size and position of the template textfield we created before in the dialog editor
	GetDlgItem(IDC_PIC_OPENGL)->GetWindowRect(rect);

	// Convert screen coordinates to client coordinates
	ScreenToClient(rect);

	// Create OpenGL Control window
	m_oglWindow.oglCreate(rect, this);

	// Setup the OpenGL Window's timer to render
	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 1, 0);



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMeshHistogramMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMeshHistogramMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMeshHistogramMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMeshHistogramMFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	switch (nType)
	{
	case SIZE_RESTORED:
		{
			if (m_oglWindow.m_bIsMaximized)
			{
				m_oglWindow.OnSize(nType, cx, cy);
				m_oglWindow.m_bIsMaximized = false;
			}

			break;
		}

	case SIZE_MAXIMIZED:
		{
			m_oglWindow.OnSize(nType, cx, cy);
			m_oglWindow.m_bIsMaximized = true;

			break;
		}
	}



}

void CMeshHistogramMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default


	CDialog::OnTimer(nIDEvent);
}



void CMeshHistogramMFCDlg::OnBnClickedLoad()
{
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"all files(*.*)|*.*|model files(*.ply)|*.ply", NULL);
	if (dlg.DoModal()!= IDOK) return;

	MyMesh mesh;

	char fileName[256]={0};
	sprintf_s(fileName,"%s\0",dlg.GetPathName());

	try
	{
		if ( !OpenMesh::IO::read_mesh(mesh, fileName) )
		{
			std::cerr << "Cannot read mesh from the directory" << std::endl;
		}
	}
	catch( std::exception& x )
	{
		std::cerr << x.what() << std::endl;
	}
	meshQueue.reserve(10);
	meshQueue.push_back(mesh);

	//ALIGN_CONTROL = false;
	//ROTATE_CONTROL = 0;
}


void CMeshHistogramMFCDlg::OnBnClickedNoise()
{
	NOISE_CONTROL = true;
	//ALIGN_CONTROL = false;
	//ROTATE_CONTROL = 0;
}

void CMeshHistogramMFCDlg::OnBnClickedNormalize()
{
	NORMALIZE_CONTROL = true;
	//ALIGN_CONTROL = false;
}

void CMeshHistogramMFCDlg::OnBnClickedMeshhistogram()
{
	HISTOGRAM_CONTROL = true;
	//ALIGN_CONTROL = false;
}


void CMeshHistogramMFCDlg::OnBnClickedVrmlexport()
{
	unsigned int meshsize = meshQueue.size();
	VRMLTranslator(meshQueue.at(meshsize-1));
	//ALIGN_CONTROL = false;
}


void CMeshHistogramMFCDlg::OnBnClickedRemovedv()
{
	REMOVE_CONTROL=true;
}
