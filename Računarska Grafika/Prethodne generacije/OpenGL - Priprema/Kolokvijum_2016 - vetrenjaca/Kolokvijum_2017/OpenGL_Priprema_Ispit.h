
// OpenGL_Priprema_Ispit.h : main header file for the OpenGL_Priprema_Ispit application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COpenGLPripremaIspitApp:
// See OpenGL_Priprema_Ispit.cpp for the implementation of this class
//

class COpenGLPripremaIspitApp : public CWinApp
{
public:
	COpenGLPripremaIspitApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLPripremaIspitApp theApp;
