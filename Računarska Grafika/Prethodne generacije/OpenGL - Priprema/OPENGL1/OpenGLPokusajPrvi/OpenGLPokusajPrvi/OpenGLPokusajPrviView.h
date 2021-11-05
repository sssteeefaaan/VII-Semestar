#include "CGLRenderer.h"

#include <gl/GL.h>
#include <gl/GLU.h>
// OpenGLPokusajPrviView.h : interface of the COpenGLPokusajPrviView class
//

#pragma once


class COpenGLPokusajPrviView : public CView
{
protected: // create from serialization only
	COpenGLPokusajPrviView();
	DECLARE_DYNCREATE(COpenGLPokusajPrviView)
	CGLRenderer m_glRenderer;

// Attributes
public:
	COpenGLPokusajPrviDoc* GetDocument() const;
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
	virtual ~COpenGLPokusajPrviView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in OpenGLPokusajPrviView.cpp
inline COpenGLPokusajPrviDoc* COpenGLPokusajPrviView::GetDocument() const
   { return reinterpret_cast<COpenGLPokusajPrviDoc*>(m_pDocument); }
#endif

