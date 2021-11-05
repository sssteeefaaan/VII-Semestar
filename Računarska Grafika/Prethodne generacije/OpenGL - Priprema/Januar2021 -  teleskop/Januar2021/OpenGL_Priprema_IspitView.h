
// OpenGL_Priprema_IspitView.h : interface of the COpenGLPripremaIspitView class
//

#pragma once
#include "GLRenderer.h"

class COpenGLPripremaIspitView : public CView
{
protected: // create from serialization only
	COpenGLPripremaIspitView() noexcept;
	DECLARE_DYNCREATE(COpenGLPripremaIspitView)

// Attributes
public:
	COpenGLPripremaIspitDoc* GetDocument() const;

protected:
	GLRenderer m_glRenderer;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~COpenGLPripremaIspitView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in OpenGL_Priprema_IspitView.cpp
inline COpenGLPripremaIspitDoc* COpenGLPripremaIspitView::GetDocument() const
   { return reinterpret_cast<COpenGLPripremaIspitDoc*>(m_pDocument); }
#endif

