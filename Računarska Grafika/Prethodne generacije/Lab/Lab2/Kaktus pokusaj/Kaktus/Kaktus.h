
// Kaktus.h : main header file for the Kaktus application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKaktusApp:
// See Kaktus.cpp for the implementation of this class
//

class CKaktusApp : public CWinApp
{
public:
	CKaktusApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKaktusApp theApp;
