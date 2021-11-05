
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
	this->ugao1 = 0;   
	this->ugao2 = 0;    

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

	DrawLeviKrak(pDC, rect);
	DrawDesniKrak(pDC, rect);

	DrawKaktus3(pDC, rect, -45, 1);		
	DrawKaktus3(pDC, rect, 0, 0);       
	DrawKaktus3(pDC, rect, 45, 2);     

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

	DrawGreenCircle(pDC, rect);  

	Translate(pDC, 0, -40, true);

	DrawTamniKaktus(pDC, rect);  

	Translate(pDC, 0, -40, true);

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

	pDC->Ellipse(-15, -15, 15, 15);		

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

void CKaktusLabView::DrawKaktus3(CDC* pDC, CRect& rect, float angle, int krug)
{
	XFORM old;
	pDC->GetWorldTransform(&old);

	

	Scale(pDC, 0.3, 1, true);   
	Translate(pDC, 0, -40, true);
	Rotate(pDC, angle, true);
	Translate(pDC, 500, 245, true);
	DrawTamniKaktus(pDC, rect);

	NoTranform(pDC);		

	Translate(pDC, 0, -80, true);  
	Rotate(pDC, angle, true);
	Translate(pDC, 500, 245, true);
	if (krug == 1)
	{
		DrawGreenCircle(pDC, rect);
		NoTranform(pDC);
		Scale(pDC, 0.5, 1, true);  
		Rotate(pDC, 90, true);
		Translate(pDC, 405, 190, true);
		DrawTamniKaktus(pDC, rect);
	}

	else if (krug == 2)
	{
		DrawGreenCircle(pDC, rect);

		NoTranform(pDC);
		Scale(pDC, 0.3, 1, true);   
		Translate(pDC, 0, -120, true);
		Rotate(pDC, angle, true);
		Translate(pDC, 500, 245, true);
		DrawTamniKaktus(pDC, rect);

		NoTranform(pDC);
		Scale(pDC, 0.3, 1, true);  
		Translate(pDC, 0, -40, true);
		//Rotate(pDC, -45, true);
		Rotate(pDC, 0, true);
		Translate(pDC, 555, 190, true);
		DrawTamniKaktus(pDC, rect);
	}

	pDC->SetWorldTransform(&old);
}

void CKaktusLabView::DrawDesniKrak(CDC* pDC, CRect& rect)   
{
	XFORM old;
	pDC->GetWorldTransform(&old);


	Scale(pDC, 0.3, 1, true); 
	Rotate(pDC, 90, true);
	Translate(pDC, 40, 0, true);
	Rotate(pDC, ugao1, true);  

	Translate(pDC, 555, 190, true);
	DrawSvetliKaktus(pDC, rect);

	NoTranform(pDC);

	Translate(pDC, 80, 0, true);           
	Rotate(pDC, ugao1, true);           

	Translate(pDC, 555, 190, true);
	DrawGreenCircle(pDC, rect);

	NoTranform(pDC);

	Rotate(pDC, 90, true);         
	Translate(pDC, 120, 0, true);
	Rotate(pDC, ugao1, true);

	Translate(pDC, 555, 190, true);  
	DrawTamniKaktus(pDC, rect);

	pDC->SetWorldTransform(&old);
}

void CKaktusLabView::DrawLeviKrak(CDC* pDC, CRect& rect) 
{
	XFORM old;     
	pDC->GetWorldTransform(&old);


	Scale(pDC, 0.5, 1, true);  
	//Rotate(pDC, 90, true);
	Translate(pDC, 0, -40, true);
	Rotate(pDC, ugao2, true);

	Translate(pDC, 445, 190, true);
	DrawSvetliKaktus(pDC, rect);

	NoTranform(pDC);

	Translate(pDC, 0, -80, true);
	Rotate(pDC, ugao2, true);

	Translate(pDC, 445, 190, true); 
	DrawGreenCircle(pDC, rect);   
	NoTranform(pDC);

	Translate(pDC, 0, -120, true);
	Rotate(pDC, ugao2, true);

	Translate(pDC, 445, 190, true); 
	DrawTamniKaktus(pDC, rect);

	pDC->SetWorldTransform(&old);
}




void CKaktusLabView::DrawSaksija(CDC* pDC, CRect& rect)
{
	CPen pen(PS_SOLID, 1, RGB(25, 25, 25));
	pDC->SelectObject(pen);
	CBrush brush(RGB(222, 148, 0));
	pDC->SelectObject(brush);

	CPoint a = CPoint(460, 420);
	CPoint b = CPoint(540, 420);
	CPoint c = CPoint(550, 350);
	CPoint d = CPoint(560, 350);
	CPoint e = CPoint(560, 330);
	CPoint f = CPoint(440, 330);
	CPoint g = CPoint(440, 350);
	CPoint h = CPoint(450, 350);

	CPoint poligon[] = { a,b,c,d,e,f,g,h };

	pDC->Polygon(poligon, 8);



	brush.DeleteObject();
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
	pDC->SetBkMode(1);
	CFont font;
	font.CreateFont(size * 0.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Monotype Corsiva"));
	pDC->SelectObject(&font);

	XFORM old;
	pDC->GetWorldTransform(&old);

	Rotate(pDC, 90, true);					
	Translate(pDC, 730, 0, true);              
	pDC->TextOut(size, -20, CString("16915 Teodora Stefanovic"));

	pDC->SetWorldTransform(&old);
	font.DeleteObject();
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


	if (nChar == 71)			
	{
		if (stanje == 0)
			stanje = 1;
		else if (stanje == 1)
			stanje = 0;

		Invalidate();
	}

	if (nChar == VK_LEFT)
	{
		ugao1 += -5;   
		Invalidate();
	}
	else if (nChar == VK_RIGHT)
	{
		ugao1 += 5;
		Invalidate();
	}

	else if (nChar == 81)				// Q
	{
		ugao2 += -5;     
		Invalidate();
	}
	else if (nChar == 87)			// W
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
