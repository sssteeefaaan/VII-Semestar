
// Lab5.h : main header file for the Lab5 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLab5App:
// See Lab5.cpp for the implementation of this class
//

class CLab5App : public CWinApp
{
public:
	CLab5App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLab5App theApp;
