
// KaktusLabView.cpp : implementation of the CKaktusLabView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "KaktusLab.h"
#endif




#include "KaktusLabDoc.h"
#include "KaktusLabView.h"
#define razmera 25


#define _USE_MATH_DEFINES


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKaktusLabView

IMPLEMENT_DYNCREATE(CKaktusLabView, CView)

BEGIN_MESSAGE_MAP(CKaktusLabView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CKaktusLabView construction/destruction

CKaktusLabView::CKaktusLabView()
{
	this->stanje = 0;   
	this->ugao1 = -90;
	this->ugao2 = -45;    

	this->tamniKaktus = GetEnhMetaFileW(CString("cactus_part.emf"));
	this->svetliKaktus = GetEnhMetaFileW(CString("cactus_part_light.emf"));

}

CKaktusLabView::~CKaktusLabView()
{
	DeleteEnhMetaFile(svetliKaktus);
	DeleteEnhMetaFile(tamniKaktus);


}

BOOL CKaktusLabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKaktusLabView drawing



void CKaktusLabView::OnDraw(CDC* pDC)
{
	CKaktusLabDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(&rect);

	DrawBackground(pDC, rect);


	XFORM transOld;
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->GetWorldTransform(&transOld);

	Tekst(pDC, 50);

	DrawLeviDeo(pDC, rect);
    DrawDesniDeo(pDC, rect);

	DrawStaticniDeo(pDC, rect, 45);

	Translate(pDC, 500, 325, true);

	DrawBaseKaktus(pDC, rect);			
	pDC->SetWorldTransform(&transOld);
	pDC->SetGraphicsMode(prevMode);

	DrawSaksija(pDC, rect);
	if (this->stanje == 1)
		DrawGrid(pDC, rect);

}


void CKaktusLabView::DrawBaseKaktus(CDC* pDC, CRect& rect)
{
	XFORM old;
	pDC->GetWorldTransform(&old);

	Translate(pDC, 0, 100, true);
	DrawGreenCircle(pDC, rect);  

	
	Translate(pDC, 0, -37, true);
	DrawTamniKaktus(pDC, rect);  

	Translate(pDC, 0, -37, true);
	DrawGreenCircle(pDC, rect);  

	NoTranform(pDC);

	pDC->SetWorldTransform(&old);

}

void CKaktusLabView::DrawGreenCircle(CDC* pDC, CRect& rect)
{
	CPen pen(PS_SOLID, 1, RGB(25, 25, 25));
	pDC->SelectObject(pen);
	CBrush brush(RGB(0, 204, 0));
	pDC->SelectObject(brush);

	pDC->Ellipse(-11, -11, 11, 11);		

	brush.DeleteObject();
}

void CKaktusLabView::DrawSvetliKaktus(CDC* pDC, CRect& rect)
{
	pDC->PlayMetaFile(this->svetliKaktus, CRect(-35, -35, 35, 35));
	

}

void CKaktusLabView::DrawTamniKaktus(CDC* pDC, CRect& rect)
{
	pDC->PlayMetaFile(this->tamniKaktus, CRect(-35, -35, 35, 35));
}

void CKaktusLabView::DrawStaticniDeo(CDC* pDC, CRect& rect, float angle)
{
	XFORM old;
	pDC->GetWorldTransform(&old);


		Scale(pDC, 0.6, 1, true);
		Translate(pDC, 0, -38, true);
		Rotate(pDC, angle, true);
		Translate(pDC, 500, 350, true);
		DrawTamniKaktus(pDC, rect);
		NoTranform(pDC);
	

		
		Scale(pDC, 0.6, 1, true);   
		Translate(pDC, 0, -120, true);
		Rotate(pDC, 90, true);
		Translate(pDC, 472, 297, true);
		DrawTamniKaktus(pDC, rect);
		NoTranform(pDC);

		Scale(pDC, 0.6, 1, true);
		Translate(pDC, 0, -177, true);
		Rotate(pDC, 45, true);
		Translate(pDC, 530, 397, true);
		DrawTamniKaktus(pDC, rect);
		NoTranform(pDC);

		Scale(pDC, 0.6, 1, true);
		Translate(pDC, 0, -177, true);
		Rotate(pDC, 135, true);
		Translate(pDC, 530, 197, true);
		DrawTamniKaktus(pDC, rect);
		NoTranform(pDC);

		Translate(pDC, 0, -180, true);
		Rotate(pDC, angle, true);
		Translate(pDC, 501, 425, true);
		DrawGreenCircle(pDC, rect);
		NoTranform(pDC);


		Translate(pDC, 0, -78, true);
		Rotate(pDC, angle, true);
		Translate(pDC, 500, 355, true);
		//Rotate(pDC, ugao1, true);
		DrawGreenCircle(pDC, rect);

		NoTranform(pDC);
		
	
	

	pDC->SetWorldTransform(&old);
}

void CKaktusLabView::DrawDesniDeo(CDC* pDC, CRect& rect)
{
	XFORM old;
	pDC->GetWorldTransform(&old);

	Scale(pDC, 0.6, 1, true); 
	Rotate(pDC, 90, true);
	Translate(pDC, 40, 0, true);
	Rotate(pDC, ugao1, true);  
	Translate(pDC, 553, 303, true);
	DrawSvetliKaktus(pDC, rect);
	NoTranform(pDC);

	Scale(pDC, 0.86, 1.07, true);
	Rotate(pDC, 90, true);         
	Translate(pDC, 120, 0, true);
	Rotate(pDC, ugao1, true);
	Translate(pDC, 553, 305, true);  
	DrawTamniKaktus(pDC, rect);
	NoTranform(pDC);

	Translate(pDC, 80, 0, true);
	Rotate(pDC, ugao1, true);
	Translate(pDC, 553, 305, true);
	DrawGreenCircle(pDC, rect);


	pDC->SetWorldTransform(&old);
}

void CKaktusLabView::DrawLeviDeo(CDC* pDC, CRect& rect) 
{
	XFORM old;     
	pDC->GetWorldTransform(&old);


	Scale(pDC, 0.6, 1, true);  
	Translate(pDC, 0, -40, true);
	Rotate(pDC, ugao2, true);
	Translate(pDC, 504, 351, true);
	DrawSvetliKaktus(pDC, rect);
	NoTranform(pDC);

	Scale(pDC, 0.86, 1.07, true);
	Translate(pDC, 0, -120, true);
	Rotate(pDC, ugao2, true);
	Translate(pDC, 506, 353, true); 
	DrawTamniKaktus(pDC, rect);
	NoTranform(pDC);

	Translate(pDC, 0, -80, true);
	Rotate(pDC, ugao2, true);
	Translate(pDC, 506, 353, true);
	DrawGreenCircle(pDC, rect);
	NoTranform(pDC);

	Scale(pDC, 0.6, 1, true);
	Rotate(pDC, 45, true);
	Translate(pDC, 0, -200, true);
	Rotate(pDC, ugao2, true);
	Translate(pDC, 534, 345, true);
	DrawTamniKaktus(pDC, rect);
	NoTranform(pDC);

	Scale(pDC, 0.6, 1, true);
	Rotate(pDC, -45, true);
	Translate(pDC, 0, -200, true);
	Rotate(pDC, ugao2, true);
	Translate(pDC, 499, 379, true);
	DrawTamniKaktus(pDC, rect);
	NoTranform(pDC);


	Translate(pDC, 0, -160, true);
	Rotate(pDC, ugao2, true);
	Translate(pDC, 507, 354, true);
	DrawGreenCircle(pDC, rect);
	NoTranform(pDC);


	pDC->SetWorldTransform(&old);
}




void CKaktusLabView::DrawSaksija(CDC* pDC, CRect& rect)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(pen);

	CBrush brush2(RGB(210, 155, 30));
	pDC->SelectObject(brush2);

	pDC->Rectangle(562, 430, 439, 450);

	brush2.DeleteObject();
	CPen pen2(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(pen2);


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

void CKaktusLabView::DrawBackground(CDC* pDC, CRect& rect)
{
	CPen pen(PS_SOLID, 5, RGB(135, 206, 235));
	pDC->SelectObject(pen);
	CBrush brush(RGB(135, 206, 235));
	pDC->SelectObject(brush);
	CPoint a = CPoint(250, 0);  
	CPoint b = CPoint(750, 500);  

	pDC->Rectangle(a.x, a.y, b.x, b.y);

	brush.DeleteObject();
}

void CKaktusLabView::DrawGrid(CDC* pDC, CRect& rect)
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

void CKaktusLabView::Translate(CDC* pDC, float x, float y, bool rightMul)
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

void CKaktusLabView::Rotate(CDC* pDC, float angle, bool rightMul)
{
	float pi = 3.14159;
	XFORM f;
	f.eM11 = cos(angle * pi / 180);   
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

void CKaktusLabView::Scale(CDC* pDC, float sX, float sY, bool rightMultiply) {

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

void CKaktusLabView::NoTranform(CDC* pDC)
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







void CKaktusLabView::Tekst(CDC* pDC, int size)
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


// CKaktusLabView printing

BOOL CKaktusLabView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKaktusLabView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKaktusLabView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKaktusLabView diagnostics

#ifdef _DEBUG
void CKaktusLabView::AssertValid() const
{
	CView::AssertValid();
}

void CKaktusLabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKaktusLabDoc* CKaktusLabView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKaktusLabDoc)));
	return (CKaktusLabDoc*)m_pDocument;
}
#endif //_DEBUG


// CKaktusLabView message handlers


void CKaktusLabView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{


	if (nChar == 'A')			
	{
		if (stanje == 0)
			stanje = 1;
		else if (stanje == 1)
			stanje = 0;

		Invalidate();
	}

	if (nChar == 'S')  //desni deo
	{
		ugao1 += -5;   
		Invalidate();
	}
	else if (nChar == 'D') //desni deo
	{
		ugao1 += 5;
		Invalidate();
	}

	else if (nChar == 'Q')	//levi deo
	{
		ugao2 += -5;     
		Invalidate();
	}
	else if (nChar == 'W')		//levi deo
	{
		ugao2 += 5;
		Invalidate();
	}



	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	// TODO: Add your message handler code here and/or call default


}


BOOL CKaktusLabView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CView::OnEraseBkgnd(pDC);
}
