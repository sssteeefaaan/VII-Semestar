
// Lab_5_vaza_3DView.h : interface of the CLab5vaza3DView class
//

#pragma once

#include "GLRenderer.h"

class CLab5vaza3DView : public CView
{
protected: // create from serialization only
	CLab5vaza3DView() noexcept;
	DECLARE_DYNCREATE(CLab5vaza3DView)

// Attributes
public:
	CLab5vaza3DDoc* GetDocument() const;

protected:
	GLRenderer m_glRenderer;
	bool m_isDragged;

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
	virtual ~CLab5vaza3DView();
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Lab_5_vaza_3DView.cpp
inline CLab5vaza3DDoc* CLab5vaza3DView::GetDocument() const
   { return reinterpret_cast<CLab5vaza3DDoc*>(m_pDocument); }
#endif

