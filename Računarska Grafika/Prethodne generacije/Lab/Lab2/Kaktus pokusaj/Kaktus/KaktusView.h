
// KaktusView.h : interface of the CKaktusView class
//

#pragma once

class CKaktusView : public CView
{
protected: // create from serialization only
	CKaktusView();
	DECLARE_DYNCREATE(CKaktusView)

// Attributes
public:
	CKaktusDoc* GetDocument() const;
	float ugao1, ugao2, ugao3;

	HENHMETAFILE light;
	HENHMETAFILE dark;

// Operations
public:
	void DrawBackground(CDC* pDC, CRect& rect);
	void DrawGrid(CDC* pDC, CRect& rect);

	void DrawKvadrat(CDC* pDC, CRect& rect);
	void DrawSaksiju(CDC* pDC, CRect& rect);
	void DrawLevuStranu(CDC* pDC, CRect& rect);
	void DrawDesnuStranu(CDC* pDC, CRect& rect);
	void DrawStaticniDeo(CDC* pDC, CRect& rect);
	void DrawTekst(CDC* pDC);
	void DrawSvetli(CDC* pDC, CRect& rect);
	void DrawTamni(CDC* pDC, CRect& rect);
	void DrawKruzic2(CDC* pDC, CRect& rect);
	void DrawKaktus(CDC* pDC, CRect& rect);

	//void Translate(CDC* pDC, float dx, float dy, bool rightMultiply);
	//void Rotate(CDC* pDC, float ugao, bool rightMultiply);
	//void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);

		//transformacije
	//void Translate(CDC* pDC, float x, float y, bool rightMul);
	//void Rotate(CDC* pDC, float angle, bool rightMul);
	//void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	//void NoTranform(CDC* pDC);
	


protected:
	int stanje = 0;

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
	virtual ~CKaktusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in KaktusView.cpp
inline CKaktusDoc* CKaktusView::GetDocument() const
   { return reinterpret_cast<CKaktusDoc*>(m_pDocument); }
#endif

