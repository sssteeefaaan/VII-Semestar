
// KaktusLab.h : main header file for the KaktusLab application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKaktusLabApp:
// See KaktusLab.cpp for the implementation of this class
//

class CKaktusLabApp : public CWinApp
{
public:
	CKaktusLabApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKaktusLabApp theApp;
