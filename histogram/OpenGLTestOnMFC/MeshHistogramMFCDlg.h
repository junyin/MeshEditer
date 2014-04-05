// MeshHistogramMFCDlg.h : header file
//

#pragma once

#include "OpenGLControl.h"
#include "MeshOperation.h"

// CMeshHistogramMFCDlg dialog
class CMeshHistogramMFCDlg : public CDialog
{
// Construction
public:
	CMeshHistogramMFCDlg(CWnd* pParent = NULL);	// standard constructor

	COpenGLControl m_oglWindow;

// Dialog Data
	enum { IDD = IDD_MeshHistogramMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//afx_msg void OnBnClickedAlignmesh();
	afx_msg void OnBnClickedLoad();
	//afx_msg void OnBnClickedAlign();
	afx_msg void OnBnClickedNoise();
	//afx_msg void OnBnClickedRotatex();
	//afx_msg void OnBnClickedRotatey();
	//afx_msg void OnBnClickedRotatez();
	afx_msg void OnBnClickedNormalize();
	afx_msg void OnBnClickedMeshhistogram();
	afx_msg void OnBnClickedVrmlexport();
	afx_msg void OnBnClickedRemovedv();
};
