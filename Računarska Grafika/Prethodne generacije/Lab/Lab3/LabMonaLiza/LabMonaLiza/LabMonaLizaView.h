
// LabMonaLizaView.h : interface of the CLabMonaLizaView class
//

#pragma once


class CLabMonaLizaView : public CView
{
protected: // create from serialization only
	CLabMonaLizaView() noexcept;
	DECLARE_DYNCREATE(CLabMonaLizaView)

	// Attributes
public:
	double alpha = 0;
	int kvadrat = 25;
	int visina;
	int sirina;
	int kv = 0;
	int centerX = 250;
	int centerY = 250;
	int baseX = 0;
	int baseY = 0;
	bool stanje = 1;
	CLabMonaLizaDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	virtual void MonaLiza(CDC* pDC);
	CPoint crtajPart(int x, int y, CString nameOfFile, CDC* pDC);
	virtual void crtajDeo(CDC* pDC, int x, int y, CString fileName, double alpha);
	virtual void Rotate(CDC* pDC, float angle, bool isRightMultiply);
	virtual void Translate(CDC* pDC, float dx, float dy, bool isRightMultiply);
	virtual void Scale(CDC* pDC, float x, float y, bool isRightMultiply);
	virtual void Mirror(CDC* pDC, bool isRightMultiply);

	virtual void SivaSlika(CBitmap* bmpImage, BITMAP bm);
	virtual void AntiFlicker(CDC* pDC);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void DrawGrid(CDC* pDC, CRect& rect);



	// Implementation
public:
	virtual ~CLabMonaLizaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LabMonaLizaView.cpp
inline CLabMonaLizaDoc* CLabMonaLizaView::GetDocument() const
{
	return reinterpret_cast<CLabMonaLizaDoc*>(m_pDocument);
}
#endif

