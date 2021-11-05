
// MFC3.h : main header file for the MFC3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFC3App:
// See MFC3.cpp for the implementation of this class
//

class CMFC3App : public CWinApp
{
public:
	CMFC3App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC3App theApp;
