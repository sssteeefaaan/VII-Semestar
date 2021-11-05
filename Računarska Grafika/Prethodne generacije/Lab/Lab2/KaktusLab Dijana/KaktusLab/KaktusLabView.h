
// KaktusLabView.h : interface of the CKaktusLabView class
//

#pragma once


class CKaktusLabView : public CView
{
protected: // create from serialization only
	CKaktusLabView();
	DECLARE_DYNCREATE(CKaktusLabView)

	// Attributes
public:
	CKaktusLabDoc* GetDocument() const;


protected:
	int stanje;
	float ugao1;
	float ugao2;

	// Operations
public:
public:

	HENHMETAFILE svetliKaktus;
	HENHMETAFILE tamniKaktus;

	void DrawBaseKaktus(CDC* pDC, CRect& rect);  

	void DrawLeviDeo(CDC* pDC, CRect& rect);
	void DrawDesniDeo(CDC* pDC, CRect& rect);

	void DrawGreenCircle(CDC* pDC, CRect& rect);   
	void DrawSvetliKaktus(CDC* pDC, CRect& rect);	
	void DrawTamniKaktus(CDC* pDC, CRect& rect);	

	void DrawStaticniDeo(CDC* pDC, CRect& rect, float angle);		


	void DrawSaksija(CDC* pDC, CRect& rect);
	void DrawBackground(CDC* pDC, CRect& rect);
	void DrawGrid(CDC* pDC, CRect& rect);


	//transformacije
	void Translate(CDC* pDC, float x, float y, bool rightMul);
	void Rotate(CDC* pDC, float angle, bool rightMul);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void NoTranform(CDC* pDC);
	



	//void drawText(CDC* pDC, int size);

	void Tekst(CDC* pDC, int size);



	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	//CKaktusLabView();
	virtual ~CKaktusLabView();
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in KaktusLabView.cpp
inline CKaktusLabDoc* CKaktusLabView::GetDocument() const
{
	return reinterpret_cast<CKaktusLabDoc*>(m_pDocument);
}
#endif

