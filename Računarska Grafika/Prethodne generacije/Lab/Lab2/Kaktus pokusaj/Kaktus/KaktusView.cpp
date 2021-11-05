
// KaktusView.cpp : implementation of the CKaktusView class
//

#include "pch.h"
#include "framework.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kaktus.h"
#endif

#include "KaktusDoc.h"
#include "KaktusView.h"
#define razmera 25

#define _USE_MATH_DEFINES
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKaktusView

IMPLEMENT_DYNCREATE(CKaktusView, CView)

BEGIN_MESSAGE_MAP(CKaktusView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKaktusView construction/destruction

CKaktusView::CKaktusView() 
{
	// TODO: add construction code here
	this->dark = GetEnhMetaFileW(CString("cactus_part.emf"));
	this->light = GetEnhMetaFileW(CString("cactus_part_light.emf"));

	this->ugao1 = 0;
	this->ugao2 = 0;
	this->ugao3 = 0;


}

CKaktusView::~CKaktusView()
{
	delete dark, light;
}

BOOL CKaktusView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKaktusView drawing

void CKaktusView::OnDraw(CDC* pDC)
{
	CKaktusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);



	//za transformacije deo
	XFORM transOld;
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->GetWorldTransform(&transOld);


	this->DrawKaktus(pDC, rect);

	pDC->SetWorldTransform(&transOld);
	pDC->SetGraphicsMode(prevMode);
	if (this->stanje == 1)
		DrawGrid(pDC, rect);

	DrawTekst(pDC);

	// TODO: add draw code for native data here
}

void CKaktusView::DrawBackground(CDC* pDC, CRect& rect)
{
	CPen pen(PS_SOLID, 5, RGB(221, 221, 221));
	pDC->SelectObject(pen);
	CBrush brush(RGB(135, 206, 235));
	pDC->SelectObject(brush);
	CPoint a = CPoint(250, 0);
	CPoint b = CPoint(750, 500);

	pDC->Rectangle(a.x, a.y, b.x, b.y);

	brush.DeleteObject();
}

void CKaktusView::DrawGrid(CDC* pDC, CRect& rect)
{
	CPen pen(PS_SOLID, 1, RGB(242, 242, 242));
	pDC->SelectObject(pen);

	CPoint a = CPoint(275, 0);
	CPoint b = CPoint(275, 500);

	CPoint c = CPoint(250, 25);
	CPoint d = CPoint(750, 25);

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

void Translate(CDC* pDC, float x, float y, bool rightMul)
{
	XFORM f;
	f.eM11 = 1;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = 1;
	f.eDx = x;
	f.eDy = y;

	if (rightMul)
		pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&f, MWT_LEFTMULTIPLY);

}

void Rotate(CDC* pDC, float angle, bool rightMul) {
	float pi = 3.14159;
	XFORM f;
	f.eM11 = cos(angle * pi / 180);   // angle*pi/180 -- radijane
	f.eM12 = sin(angle * pi / 180);
	f.eM21 = -sin(angle * pi / 180);
	f.eM22 = cos(angle * pi / 180);
	f.eDx = 0;
	f.eDy = 0;

	if (rightMul)
		pDC->ModifyWorldTransform(&f, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&f, MWT_LEFTMULTIPLY);
}


void Scale(CDC* pDC, float sX, float sY, bool rightMultiply) {

	XFORM transformacija;
	///*
	transformacija.eM11 = sX;
	transformacija.eM12 = 0;
	transformacija.eM21 = 0;
	transformacija.eM22 = sY;
	//*/
	transformacija.eDx = 0;
	transformacija.eDy = 0;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&transformacija, MWT_RIGHTMULTIPLY);
	else pDC->ModifyWorldTransform(&transformacija, MWT_LEFTMULTIPLY);
}

void NoTransform(CDC* pDC)
{
	XFORM f;
	f.eM11 = 1;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = 1;
	f.eDx = 0;
	f.eDy = 0;
	pDC->SetWorldTransform(&f);
}


void CKaktusView::DrawSvetli(CDC* pDC, CRect& rect)
{
	pDC->PlayMetaFile(this->light, CRect(-35, -35, 35, 35));

}

void CKaktusView::DrawTamni(CDC* pDC, CRect& rect)
{
	pDC->PlayMetaFile(this->dark, CRect(-35, -35, 35, 35));

}

void CKaktusView::DrawKvadrat(CDC* pDC, CRect& rect)
{

	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(pen);

	CBrush brush2(RGB(210, 155, 30));
	pDC->SelectObject(brush2);

	pDC->Rectangle(562, 430, 439, 450);

	brush2.DeleteObject();

}


void CKaktusView::DrawSaksiju(CDC* pDC, CRect& rect)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(pen);


	CBrush brush1(RGB(210, 155, 30));  //smedje
	pDC->SelectObject(brush1);

	CPoint a2 = CPoint(450, 450);
	CPoint b2 = CPoint(550, 450);
	CPoint c2 = CPoint(540, 500);
	CPoint d2 = CPoint(460, 500);



	CPoint niz[] = { a2,b2,c2,d2 };


	//unutar sestougao 

	pDC->Polygon(niz, 4);


	brush1.DeleteObject();

}

void CKaktusView::DrawLevuStranu(CDC* pDC, CRect& rect)
{

	XFORM old;
	pDC->GetWorldTransform(&old);

	Scale(pDC, 0.6, 1.07, true);
	Translate(pDC, -133, 47, true);
	Rotate(pDC, -45, true);
	Translate(pDC, 534, 198, true);
	Rotate(pDC, ugao2, true);
	DrawSvetli(pDC, rect);

	NoTransform(pDC);

	Scale(pDC, 0.86, 1.07, true);
	Translate(pDC, 80, 102, true);
	Rotate(pDC, -45, true);
	Translate(pDC, 290, 257, true);
	Rotate(pDC, ugao2, true);
	DrawTamni(pDC, rect);

	NoTransform(pDC);

	Translate(pDC, -53, 73, true);
	Rotate(pDC, -45, true);
	Translate(pDC, 417, 209, true);
	Rotate(pDC, ugao2, true);
	DrawKruzic2(pDC, rect);

	NoTransform(pDC);

	Scale(pDC, 0.6, 1.07, true);
	Translate(pDC, -133, 47, true);
	Rotate(pDC, 0, true);
	Translate(pDC, 525, 158, true);
	Rotate(pDC, ugao2, true);
	DrawTamni(pDC, rect);

	NoTransform(pDC);

	Scale(pDC, 0.6, 1.07, true);
	Translate(pDC, 133, 47, true);
	Rotate(pDC, -90, true);
	Translate(pDC, 310, 378, true);
	Rotate(pDC, ugao2, true);
	DrawTamni(pDC, rect);

	NoTransform(pDC);

	Translate(pDC, -53, -4, true);
	Rotate(pDC, -45, true);
	Translate(pDC, 417, 209, true);
	Rotate(pDC, ugao2, true);
	DrawKruzic2(pDC, rect);


	pDC->SetWorldTransform(&old);
	

}

void CKaktusView::DrawDesnuStranu(CDC* pDC, CRect& rect)
{

	XFORM old;
	pDC->GetWorldTransform(&old);

	Scale(pDC, 0.6, 1.07, true);
	Translate(pDC, -133, 47, true);
	Rotate(pDC, 0, true);
	Translate(pDC, 687, 212, true);
	Rotate(pDC, ugao1, true);
	DrawSvetli(pDC, rect);

	NoTransform(pDC);



	Scale(pDC, 0.86, 1.07, true);
	Translate(pDC, 80, 102, true);
	Rotate(pDC, 0, true);
	Translate(pDC, 473, 80, true);
	Rotate(pDC, ugao1, true);
	DrawTamni(pDC, rect);

	NoTransform(pDC);


	Translate(pDC, -53, -4, true);
	Rotate(pDC, 0, true);
	Translate(pDC, 595, 214, true);
	Rotate(pDC, ugao1, true);
	DrawKruzic2(pDC, rect);
	

	pDC->SetWorldTransform(&old);
}

void CKaktusView::DrawStaticniDeo(CDC* pDC, CRect& rect)
{

	XFORM old;
	pDC->GetWorldTransform(&old);

	pDC->PlayMetaFile(this->dark, CRect(470, 423, 530, 351));
	
	Translate(pDC, 180, 27, true);
	Translate(pDC, 309, 386, true);
	DrawKruzic2(pDC, rect);

	NoTransform(pDC);

	Scale(pDC, 0.6, 1.07, true);
	Translate(pDC, 80, 85, true);
	Rotate(pDC, 45, true);
	Translate(pDC, 530, 207, true);
	DrawTamni(pDC, rect);

	NoTransform(pDC);


	Translate(pDC, 180, 27, true);
	Rotate(pDC, 45, true);
	Translate(pDC, 393, 189, true);
	//Rotate(pDC, ugao2, false);
	DrawKruzic2(pDC, rect);

	NoTransform(pDC);


	Scale(pDC, 0.6, 1.07, true);
	Translate(pDC, 80, 85, true);
	Rotate(pDC, 90, true);
	Translate(pDC, 677, 217, true);
	DrawTamni(pDC, rect);

	NoTransform(pDC);

	Translate(pDC, 80, 27, true);
	Rotate(pDC, 45, true);
	Translate(pDC, 517, 206, true);
	DrawKruzic2(pDC, rect);

	NoTransform(pDC);

	Scale(pDC, 0.6, 1.07, true);
	Translate(pDC, 133, -45, true);
	Rotate(pDC, 45, true);
	Translate(pDC, 530, 207, true);
	DrawTamni(pDC, rect);

	NoTransform(pDC);

	Scale(pDC, 0.6, 1.07, true);
	Translate(pDC, 131, -43, true);
	Rotate(pDC, 135, true);
	Translate(pDC, 720, 200, true);
	DrawTamni(pDC, rect);

	NoTransform(pDC);

	Translate(pDC, 80, 27, true);
	Rotate(pDC, 45, true);
	Translate(pDC, 593, 206, true);
	DrawKruzic2(pDC, rect);

	pDC->SetWorldTransform(&old);
	

}



void CKaktusView::DrawKruzic2(CDC* pDC, CRect& rect)
{
	// za iscrtavanje kruga

	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(pen);

	CBrush brush(RGB(50, 205, 50));
	pDC->SelectObject(brush);

	pDC->Ellipse(0, 0, 22, 22);
	brush.DeleteObject();

}



void CKaktusView::DrawKaktus(CDC* pDC, CRect& rect) {
	this->DrawBackground(pDC, rect);
	
	this->DrawLevuStranu(pDC, rect);
	this->DrawDesnuStranu(pDC, rect);
	this->DrawStaticniDeo(pDC, rect);


	this->DrawKvadrat(pDC, rect);
	this->DrawSaksiju(pDC, rect);
}

void CKaktusView::DrawTekst(CDC* pDC)
{
	CFont font, * oldFont;
	font.CreateFontW(1.5 * razmera, 0, -900, -900, 600, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
	oldFont = pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOutW(29 * razmera + 7, 1 * razmera + 1, CString("16826 Dijana Prokic"));
	pDC->SetTextColor(RGB(255, 255, 0));
	pDC->TextOutW(29 * razmera + 5, 1 * razmera, CString("16826 Dijana Prokic"));
	pDC->SelectObject(oldFont);
	font.DeleteObject();
	pDC->SetBkMode(OPAQUE);
	pDC->SetTextColor(RGB(1, 1, 1));
}







// CKaktusView printing

BOOL CKaktusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKaktusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKaktusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKaktusView diagnostics

#ifdef _DEBUG
void CKaktusView::AssertValid() const
{
	CView::AssertValid();
}

void CKaktusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKaktusDoc* CKaktusView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKaktusDoc)));
	return (CKaktusDoc*)m_pDocument;
}
#endif //_DEBUG


// CKaktusView message handlers


void CKaktusView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar =='A')			//na slovo A se pali gasi GRID
	{
		if (stanje == 0)
			stanje = 1;
		else if (stanje == 1)
			stanje = 0;

		Invalidate();
	}

	if (nChar == '1')
	{
		ugao1 += -5;   //ugao pod kojim se pomera desni deo 
		Invalidate();
	}

	if (nChar == '2')
	{

		ugao1 += 5;
		Invalidate();
	}

	if (nChar == 'Z')
	{
		ugao2 -= 5;      //ugao pod kojim se pomera levi deo
		Invalidate();
	}

	if (nChar == 'X')
	{
		ugao2 += 5;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
