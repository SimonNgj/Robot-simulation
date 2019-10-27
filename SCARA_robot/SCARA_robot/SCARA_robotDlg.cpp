
// SCARA_robotDlg.cpp : implementation file
//
#include "stdafx.h"
#include "SCARA_robot.h"
#include "SCARA_robotDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSCARA_robotDlg dialog


CSCARA_robotDlg::CSCARA_robotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCARA_ROBOT_DIALOG, pParent)
	, m_theta1(_T(""))
	, m_theta2(_T(""))
	, m_d3(_T(""))
	, m_tocdo(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CSCARA_robotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_RADIO_LRB, m_radio_load);
	DDX_Check(pDX, IDC_RADIO_DT, m_radio_dt);
	DDX_Check(pDX, IDC_RADIO_XR, m_radio_xr);
	DDX_Check(pDX, IDC_RADIO_BH, m_radio_bh);
	DDX_Check(pDX, IDC_RADIO_GK, m_radio_gk);
	DDX_Check(pDX, IDC_RADIO_HT, m_radio_ht);
	DDX_Check(pDX, IDC_RADIO_EL, m_radio_el);

	DDX_Control(pDX, IDC_SLIDER1, sl_theta1);
	DDX_Control(pDX, IDC_SLIDER2, sl_theta2);
	DDX_Control(pDX, IDC_SLIDER3, sl_d3);
	DDX_Control(pDX, IDC_SLIDER4, sl_tocdo);
	DDX_Text(pDX, IDC_THETA1, m_theta1);
	DDX_Text(pDX, IDC_THETA2, m_theta2);
	DDX_Text(pDX, IDC_THETA3, m_d3);
	DDX_Text(pDX, IDC_TOC_DO, m_tocdo);
}


BEGIN_MESSAGE_MAP(CSCARA_robotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSCARA_robotDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_VIEW, &CSCARA_robotDlg::OnBnClickedBtnView)
	ON_BN_CLICKED(IDC_BTN_LIGHTING, &CSCARA_robotDlg::OnBnClickedBtnLighting)
	ON_BN_CLICKED(IDC_BTN_DIS, &CSCARA_robotDlg::OnBnClickedBtnDis)
END_MESSAGE_MAP()


// CSCARA_robotDlg message handlers

BOOL CSCARA_robotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	GetDlgItem(IDC_WINDOW)->GetWindowRect(rect);
	ScreenToClient(rect);
	_openGLControl.oglCreate(rect, this);
	_openGLControl._Timer = _openGLControl.SetTimer(1, 1, 0);

	////khoi tao status radio button
	m_radio_load = 1;
	m_radio_dt = 0;
	m_radio_xr = 0;
	m_radio_bh = 0;
	m_radio_gk = 0;
	dem = 0;

	//khoi tao mien gia tri cho slider
	sl_tocdo.SetRange(0, 100, TRUE);
	sl_theta1.SetRange(-360, 360, TRUE);
	sl_theta2.SetRange(-360, 360, TRUE);
	sl_d3.SetRange(0, 100, TRUE);

	sl_tocdo.SetPos(0);
	sl_theta1.SetPos(0);
	sl_theta2.SetPos(0);
	sl_d3.SetPos(0);

	m_tocdo.Format(_T("%d"), 0);
	m_theta1.Format(_T("%d"), 0);
	m_theta2.Format(_T("%d"), 0);
	m_d3.Format(_T("%d"), 0);
	//timer
	SetTimer(0, 0.1, NULL);
	time = 0;
	tang = 0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CSCARA_robotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CSCARA_robotDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSCARA_robotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSCARA_robotDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	_openGLControl.drawStuff.m_count = 0;
	_openGLControl.drawStuff.m_time = 0;
	_openGLControl.drawStuff.m_time1 = 0;

	UpdateData(TRUE);

	if (m_radio_load == 1)
	{
		_openGLControl._fZoom = 1000;
		_openGLControl.stuff = LOAD_FILE_STL;
	}

	if (m_radio_gk == 1)
	{
		_openGLControl.stuff = COMPOUND;
	}

	UpdateData(FALSE);
}


void CSCARA_robotDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);
	UpdateData(TRUE);
	tang = sl_tocdo.GetPos();

	if (m_radio_dt == 1)
	{
		_openGLControl.stuff = DUONG_TRON;
		time += tang;

		float t = time*pi / 180;;
		float c1, s1, c2, s2;
		double q1, q2, q21, q3;
		float d1 = 125, a1 = 150, a2 = 150, d3 = 125;

		float x = 200 * cos(t);
		float y = 200 * sin(t);
		float z = 5;

		q3 = z - d1 + d3;
		c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
		s2 = sqrt(1 - (c2*c2));
		q2 = (acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2))));
		q21 = q2*(180 / pi);
		c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
		s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
		q1 = (atan2(s1, c1))*(180 / pi);

		_openGLControl.dem = time;
		m_theta1.Format(_T("%f"), q1);
		m_theta2.Format(_T("%f"), q21);
		m_d3.Format(_T("%f"), q3);

		sl_theta1.SetPos((int)q1);
		sl_theta2.SetPos((int)q21);
		sl_d3.SetPos((int)q3);

		if (time >= 360)	time = 0;
	}

	else if (m_radio_xr == 1)
	{
		_openGLControl.stuff = XOAN_REN;
		time += tang;

		float t1 = time*pi / 180;;
		float c1, s1, c2, s2;
		float q1, q2, q21, q3;
		float d1 = 125, a1 = 150, a2 = 150, d3 = 125;
		float a = 15, b = 43, c = 130;

		float x = 20 + a*(cos(t1) + t1*sin(t1));
		float y = 10 + a*(sin(t1) - t1*cos(t1));
		float z = 20 + 3 * t1;

		q3 = z - d1 + d3;
		c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
		s2 = sqrt(1 - (c2*c2));
		q2 = acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2)));
		q21 = q2*(180 / pi);
		c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
		s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
		q1 = (atan2(s1, c1))*(180 / pi);

		_openGLControl.dem = time;
		m_theta1.Format(_T("%f"), q1);
		m_theta2.Format(_T("%f"), q21);
		m_d3.Format(_T("%f"), q3);

		sl_theta1.SetPos((int)q1);
		sl_theta2.SetPos((int)q21);
		sl_d3.SetPos((int)q3);

		if (time >= 720)	time = 0;
	}

	else if (m_radio_bh == 1)
	{
		_openGLControl.stuff = TRAI_TIM;
		time += tang;

		float t2 = time*pi / 180;
		float c1, s1, c2, s2;
		float q1, q2, q21, q3;
		float d1 = 125, a1 = 150, a2 = 150, d3 = 125;
		float a = 50 * pi, b = 50, c = 130;
		
		float x = (a - b)*cos(t2) + b*cos(((a / b) - 1)*t2);
		float y = (a - b)*sin(t2) - b*sin(((a / b) - 1)*t2);
		float z = 50;

		q3 = z - d1 + d3;
		c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
		s2 = sqrt(1 - (c2*c2));
		q2 = acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2)));
		q21 = q2*(180 / pi);
		c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
		s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
		q1 = (atan2(s1, c1))*(180 / pi);

		_openGLControl.dem = time;
		m_theta1.Format(_T("%f"), q1);
		m_theta2.Format(_T("%f"), q21);
		m_d3.Format(_T("%f"), q3);

		sl_theta1.SetPos((int)q1);
		sl_theta2.SetPos((int)q21);
		sl_d3.SetPos((int)q3);

		if (time >= 12000)	time = 0;
	}

	else if (m_radio_ht == 1)
	{
		_openGLControl.stuff = HEART;
		time += tang;

		float t2 = time*pi / 180;
		float c1, s1, c2, s2;
		float q1, q2, q21, q3;
		float d1 = 125, a1 = 150, a2 = 150, d3 = 125;
		float a = 50 * pi, b = 50, c = 130;

		float x = 15 * 16 * sin(t2)*sin(t2)*sin(t2);
		float y = 15 * (13 * cos(t2) - 5 * cos(2 * t2) - 2 * cos(3 * t2) - cos(4 * t2));
		float z = 50;

		q3 = z - d1 + d3;
		c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
		s2 = sqrt(1 - (c2*c2));
		q2 = acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2)));
		q21 = q2*(180 / pi);
		c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
		s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
		q1 = (atan2(s1, c1))*(180 / pi);

		_openGLControl.dem = time;
		m_theta1.Format(_T("%f"), q1);
		m_theta2.Format(_T("%f"), q21);
		m_d3.Format(_T("%f"), q3);

		sl_theta1.SetPos((int)q1);
		sl_theta2.SetPos((int)q21);
		sl_d3.SetPos((int)q3);

		if (time >= 360)	time = 0;
	}

	else if (m_radio_el == 1)
	{
		_openGLControl.stuff = ELLIPSE;
		time += tang;

		float t2 = time*pi / 180;
		float c1, s1, c2, s2;
		float q1, q2, q21, q3;
		float d1 = 125, a1 = 150, a2 = 150, d3 = 125;
		float a = 50 * pi, b = 50, c = 130;

		float x = 196 * cos(t2);
		float y = 121 * sin(t2);
		float z = 50;

		q3 = z - d1 + d3;
		c2 = (((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2));
		s2 = sqrt(1 - (c2*c2));
		q2 = acos((((x*x + y*y) - (a1*a1 + a2*a2)) / (2 * a1*a2)));
		q21 = q2*(180 / pi);
		c1 = (a1*x + a2*(x*cos(q2) + y*sin(q2))) / (x*x + y*y);
		s1 = (a1*y + a2*(y*cos(q2) - x*sin(q2))) / (x*x + y*y);
		q1 = (atan2(s1, c1))*(180 / pi);

		_openGLControl.dem = time;
		m_theta1.Format(_T("%f"), q1);
		m_theta2.Format(_T("%f"), q21);
		m_d3.Format(_T("%f"), q3);

		sl_theta1.SetPos((int)q1);
		sl_theta2.SetPos((int)q21);
		sl_d3.SetPos((int)q3);

		if (time >= 350)	time = 0;
	}

	UpdateData(FALSE);
}


void CSCARA_robotDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//dieu khien toc do
	if (pScrollBar == (CScrollBar *)&sl_tocdo)
	{
		int tocdo = sl_tocdo.GetPos();
		m_tocdo.Format(_T("%d"), tocdo);
		UpdateData(FALSE);
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	//Góc khớp khâu 1
	if (pScrollBar == (CScrollBar *)&sl_theta1)
	{
		int value1 = sl_theta1.GetPos();
		m_theta1.Format(_T("%d"), value1);
		UpdateData(FALSE);
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	//Góc khớp khâu 2
	if (pScrollBar == (CScrollBar*)&sl_theta2)
	{
		int value2 = sl_theta2.GetPos();
		m_theta2.Format(_T("%d"), value2);
		UpdateData(FALSE);
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	//Góc khớp khâu 3
	if (pScrollBar == (CScrollBar*)&sl_d3)
	{
		int d3 = sl_d3.GetPos();
		m_d3.Format(_T("%d"), d3);
		UpdateData(FALSE);
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
	_openGLControl.q1 = sl_theta1.GetPos();
	_openGLControl.q2 = sl_theta2.GetPos();
	_openGLControl.q3 = sl_d3.GetPos();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSCARA_robotDlg::OnBnClickedBtnView()
{
	dem++;
	switch (dem)
	{
	case 1:
		gluLookAt(1, 0, 0, 0, 0, 0, 0, 0, 1);//camera
		break;
	case 2:
		gluLookAt(0, 1, 0, 0, 0, 0, 0, 0, 1);//camera
		break;
	case 3:
		gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);//camera
		break;
	default:
		break;
	}
	dem = dem;
	if (dem == 4)
	{
		dem = 0;
		gluLookAt(1, 1, 0, 0, 0, 0, 0, 1, 0);//camera
	}
}


void CSCARA_robotDlg::OnBnClickedBtnLighting()
{
	//gluLookAt(1, 0, 0, 0, 0, 0, 0, 0, 1);//camera
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 10);
	//hinh chieu phoi canh
	//nguon sang
	//
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light_pos[] = { 1.0, 0.0, 0.0, 0.0 };//huong chieu sang
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	GLfloat ambien[] = { 1, 1, 0, 1.0 };//mau do
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambien);

	GLfloat diff_use[] = { 1, 0.5, 0.5, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diff_use);

	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, specular);

	GLfloat shininess = 100.0f;
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
}


void CSCARA_robotDlg::OnBnClickedBtnDis()
{
	glDisable(GL_LIGHTING);
}
