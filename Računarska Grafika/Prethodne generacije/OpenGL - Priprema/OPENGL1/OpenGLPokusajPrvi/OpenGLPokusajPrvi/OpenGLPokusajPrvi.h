
// OpenGLPokusajPrvi.h : main header file for the OpenGLPokusajPrvi application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COpenGLPokusajPrviApp:
// See OpenGLPokusajPrvi.cpp for the implementation of this class
//

class COpenGLPokusajPrviApp : public CWinAppEx
{
public:
	COpenGLPokusajPrviApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLPokusajPrviApp theApp;
