
// 16978_Mihajlo_Sutanovac_LV02.h : main header file for the 16978_Mihajlo_Sutanovac_LV02 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy16978MihajloSutanovacLV02App:
// See 16978_Mihajlo_Sutanovac_LV02.cpp for the implementation of this class
//

class CMy16978MihajloSutanovacLV02App : public CWinApp
{
public:
	CMy16978MihajloSutanovacLV02App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy16978MihajloSutanovacLV02App theApp;
