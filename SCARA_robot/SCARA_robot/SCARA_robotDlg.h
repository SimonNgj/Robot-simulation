
// SCARA_robotDlg.h : header file
//

#pragma once
#include "OpenGLControl.h"
#include "STL_File.h"
#include "DrawStuff.h"
#include "afxcmn.h"
#define pi 3.1414159265f

// CSCARA_robotDlg dialog
class CSCARA_robotDlg : public CDialogEx
{
// Construction
public:
	CSCARA_robotDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCARA_ROBOT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	int m_second;
	unsigned _sizeChange;
	OpenGLControl _openGLControl;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	int m_radio_load;
	int m_radio_dt;
	int m_radio_bh;
	int m_radio_xr;
	int m_radio_gk;
	int m_radio_ht;
	int m_radio_el;

	int time;
	int tang;
	int dem;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedBtnView();
	afx_msg void OnBnClickedBtnLighting();
	afx_msg void OnBnClickedBtnDis();

	CSliderCtrl sl_theta1;
	CSliderCtrl sl_theta2;
	CSliderCtrl sl_d3;
	CSliderCtrl sl_tocdo;
	
	CString m_theta1;
	CString m_theta2;
	CString m_d3;
	CString m_tocdo;
};
