
// SCARA_robot.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSCARA_robotApp:
// See SCARA_robot.cpp for the implementation of this class
//

class CSCARA_robotApp : public CWinApp
{
public:
	CSCARA_robotApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSCARA_robotApp theApp;