
// 16978_Mihajlo_Sutanovac_LV02View.h : interface of the CMy16978MihajloSutanovacLV02View class
//

#pragma once


class CMy16978MihajloSutanovacLV02View : public CView
{
protected: // create from serialization only
	CMy16978MihajloSutanovacLV02View() noexcept;
	DECLARE_DYNCREATE(CMy16978MihajloSutanovacLV02View)

// Attributes
public:
	CMy16978MihajloSutanovacLV02Doc* GetDocument() const;
	bool grid;
	float angleFirst = 0;
	float angleSecond = 0;
	float pi = 3.14159265;

// Operations
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nReptCnt, UINT nFlags);
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
	virtual ~CMy16978MihajloSutanovacLV02View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 16978_Mihajlo_Sutanovac_LV02View.cpp
inline CMy16978MihajloSutanovacLV02Doc* CMy16978MihajloSutanovacLV02View::GetDocument() const
   { return reinterpret_cast<CMy16978MihajloSutanovacLV02Doc*>(m_pDocument); }
#endif

