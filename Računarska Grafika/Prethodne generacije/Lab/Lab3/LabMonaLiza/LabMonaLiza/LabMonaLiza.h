
// LabMonaLiza.h : main header file for the LabMonaLiza application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols



// See LabMonaLiza.cpp for the implementation of this class
//

class CLabMonaLizaApp : public CWinApp
{
public:
	CLabMonaLizaApp() noexcept;


	// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLabMonaLizaApp theApp;
