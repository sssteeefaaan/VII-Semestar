
// Lab_5_vaza_3D.h : main header file for the Lab_5_vaza_3D application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLab5vaza3DApp:
// See Lab_5_vaza_3D.cpp for the implementation of this class
//

class CLab5vaza3DApp : public CWinApp
{
public:
	CLab5vaza3DApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLab5vaza3DApp theApp;
