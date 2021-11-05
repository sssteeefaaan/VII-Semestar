// LabMonaLizaView.cpp : implementation of the CLabMonaLizaView class
//

#include "pch.h"
#include "DImage.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LabMonaLiza.h"
#endif

#include "LabMonaLizaDoc.h"
#include "LabMonaLizaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#define RIGHT 3
#define LEFT 2
#define toRad 0.01745329251994329576923690768489
#endif

IMPLEMENT_DYNCREATE(CLabMonaLizaView, CView)

BEGIN_MESSAGE_MAP(CLabMonaLizaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLabMonaLizaView construction/destruction

CLabMonaLizaView::CLabMonaLizaView() noexcept
{
	// TODO: add construction code here

}

CLabMonaLizaView::~CLabMonaLizaView()
{
}

BOOL CLabMonaLizaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}




void CLabMonaLizaView::MonaLiza(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	if (this->stanje == 1)
		DrawGrid(pDC, rect);

	crtajDeo(pDC, -centerX + 3, centerY - 156, CString("1.dib"), 16);
	crtajDeo(pDC, -centerX - 5, centerY - 7, CString("8.dib"), 325);
	crtajDeo(pDC, -centerX - 2, centerY + 161, CString("7.dib"), 153);
	crtajDeo(pDC, -centerX - 156, centerY - 155, CString("3.dib"), 296);
	crtajDeo(pDC, -centerX - 150, centerY + 10, CString("4.dib"), 155);
	crtajDeo(pDC, -centerX - 150, centerY + 144, CString("9.dib"), -21);
	crtajDeo(pDC, -centerX + 142, centerY - 155, CString("5.dib"), 292);
	crtajDeo(pDC, -centerX + 141, centerY + 7, CString("2.dib"), 216);
	crtajDeo(pDC, -centerX + 156, centerY + 150, CString("6.dib"), 58);


}
void CLabMonaLizaView::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC* MemDC = new CDC();
	MemDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	MemDC->SelectObject(&bmp);
	CBrush brush(RGB(255, 255, 255));
	CBrush* pOldBrush = MemDC->SelectObject(&brush);
	MemDC->Rectangle(0, 0, rect.Width(), rect.Height());

	//pDC->SetMapMode(MM_ISOTROPIC);
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	MemDC->SetGraphicsMode(GM_ADVANCED);

	XFORM old;
	MemDC->GetWorldTransform(&old);
	this->MonaLiza(MemDC);
	this->AntiFlicker(MemDC);
	MemDC->SetWorldTransform(&old);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), MemDC, 0, 0, SRCCOPY);
	MemDC->DeleteDC();
	delete MemDC;



}


CPoint CLabMonaLizaView::crtajPart(int x, int y, CString nameOfFile, CDC* pDC) {
	DImage* slika = new DImage();
	slika->Load(nameOfFile);

	CBitmap* bmpSlika = slika->m_pBmp;
	CBitmap bmpMask;
	BITMAP bm;

	bmpSlika->GetBitmap(&bm);
	bmpMask.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	CDC* SrcDC = new CDC();
	SrcDC->CreateCompatibleDC(pDC);
	CDC* DstDC = new CDC();
	DstDC->CreateCompatibleDC(pDC);

	CBitmap* pOldSrcBmp = SrcDC->SelectObject(bmpSlika);
	CBitmap* pOldDstBmp = DstDC->SelectObject(&bmpMask);

	COLORREF clrTopLeft = SrcDC->GetPixel(0, 0);
	COLORREF clrSaveBk = SrcDC->SetBkColor(clrTopLeft);
	DstDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, SrcDC, 0, 0, SRCCOPY);

	COLORREF clrSaveDstText = SrcDC->SetTextColor(RGB(255, 255, 255));
	SrcDC->SetBkColor(RGB(0, 0, 0));
	SrcDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, DstDC, 0, 0, SRCAND);

	SivaSlika(bmpSlika, bm);

	pDC->BitBlt(-bm.bmWidth / 2, -bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, DstDC, 0, 0, SRCAND);
	pDC->BitBlt(-bm.bmWidth / 2, -bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, SrcDC, 0, 0, SRCPAINT);

	SrcDC->DeleteDC();
	delete SrcDC;
	DstDC->DeleteDC();
	delete DstDC;

	return{ bm.bmWidth, bm.bmHeight };
}
void CLabMonaLizaView::crtajDeo(CDC* pDC, int x, int y, CString fileName, double alpha) {
	this->Mirror(pDC, true);
	this->Translate(pDC, x, y, false);
	this->Rotate(pDC, alpha, false);
	CString nameOfFile1(fileName);
	CPoint imageWidthHeight1 = crtajPart(0, 0, nameOfFile1, pDC);

	XFORM Xform;
	ModifyWorldTransform(pDC->m_hDC, &Xform, MWT_IDENTITY);
}


void CLabMonaLizaView::Scale(CDC* pDC, float x, float y, bool isRightMultiply)
{
	XFORM xForm;
	xForm.eM11 = x;
	xForm.eM12 = 0;
	xForm.eM21 = 0;
	xForm.eM22 = y;
	xForm.eDx = 0;
	xForm.eDy = 0;
	ModifyWorldTransform(pDC->m_hDC, &xForm, isRightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CLabMonaLizaView::Mirror(CDC* pDC, bool isRightMultiply)
{
	XFORM xForm;
	xForm.eM11 = -1;
	xForm.eM12 = 0;
	xForm.eM21 = 0;
	xForm.eM22 = 1;
	xForm.eDx = 0;
	xForm.eDy = 0;
	ModifyWorldTransform(pDC->m_hDC, &xForm, isRightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);

}
void CLabMonaLizaView::Translate(CDC* pDC, float dx, float dy, bool isRightMultiply) {
	XFORM xForm;
	xForm.eM11 = 1;
	xForm.eM12 = 0;
	xForm.eM21 = 0;
	xForm.eM22 = 1;
	xForm.eDx = dx;
	xForm.eDy = dy;
	ModifyWorldTransform(pDC->m_hDC, &xForm, isRightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}


void CLabMonaLizaView::Rotate(CDC* pDC, float angle, bool isRightMultiply) {
	XFORM xForm;
	float ugao = angle * toRad;
	xForm.eM11 = cos(ugao);
	xForm.eM12 = sin(ugao);
	xForm.eM21 = -sin(ugao);
	xForm.eM22 = cos(ugao);
	xForm.eDx = 0;
	xForm.eDy = 0;
	ModifyWorldTransform(pDC->m_hDC, &xForm, isRightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CLabMonaLizaView::SivaSlika(CBitmap* bmpImage, BITMAP bm)
{

	long dwCount = bm.bmWidthBytes * bm.bmHeight;
	BYTE* lpBits = new BYTE[dwCount];
	ZeroMemory(lpBits, dwCount);
	bmpImage->GetBitmapBits(bm.bmWidthBytes * bm.bmHeight, lpBits);

	for (long i = 0; i < dwCount - 3; i += 3)
	{
		BYTE b = BYTE(lpBits[i]);
		BYTE g = BYTE(lpBits[i + 1]);
		BYTE r = BYTE(lpBits[i + 2]);
		BYTE gray = (b + g + r) / 3;
		lpBits[i] = gray;
		lpBits[i + 1] = gray;
		lpBits[i + 2] = gray;
	}

	bmpImage->SetBitmapBits(dwCount, lpBits);
	delete[] lpBits;
}
void CLabMonaLizaView::AntiFlicker(CDC* memDC)
{
	XFORM Matrica;
	Matrica.eM11 = 1;
	Matrica.eM12 = 0;
	Matrica.eM21 = 0;
	Matrica.eM22 = 1;
	Matrica.eDx = 0;
	Matrica.eDy = 0;
	memDC->SetWorldTransform(&Matrica);
}

void CLabMonaLizaView::DrawGrid(CDC* pDC, CRect& rect)
{

	CPen pen2(PS_SOLID, 1, RGB(235, 235, 235));
	pDC->SelectObject(pen2);
	pDC->Rectangle(0, 0, 500, 500);

	CPen pen(PS_SOLID, 1, RGB(235, 235, 235));
	pDC->SelectObject(pen);

	CPoint a = CPoint(25, 0);
	CPoint b = CPoint(25, 500);

	CPoint c = CPoint(0, 25);
	CPoint d = CPoint(500, 25);

	int m = 0;
	for (int i = 0; i < 19; i++)
	{
		pDC->MoveTo(a.x + m, a.y);
		pDC->LineTo(b.x + m, b.y);
		m = m + 25;
	}

	int n = 0;
	for (int i = 0; i < 19; i++)
	{
		pDC->MoveTo(c.x, c.y + n);
		pDC->LineTo(d.x, d.y + n);
		n = n + 25;
	}

}

// CLabMonaLizaView printing

BOOL CLabMonaLizaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLabMonaLizaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLabMonaLizaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLabMonaLizaView diagnostics

#ifdef _DEBUG
void CLabMonaLizaView::AssertValid() const
{
	CView::AssertValid();
}

void CLabMonaLizaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLabMonaLizaDoc* CLabMonaLizaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLabMonaLizaDoc)));
	return (CLabMonaLizaDoc*)m_pDocument;
}
#endif //_DEBUG


// CLabMonaLizaView message handlers
