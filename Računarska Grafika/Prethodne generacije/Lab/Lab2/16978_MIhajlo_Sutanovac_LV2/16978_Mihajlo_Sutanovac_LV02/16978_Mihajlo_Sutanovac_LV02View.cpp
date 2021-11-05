
// 16978_Mihajlo_Sutanovac_LV02View.cpp : implementation of the CMy16978MihajloSutanovacLV02View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "16978_Mihajlo_Sutanovac_LV02.h"
#endif

#include "16978_Mihajlo_Sutanovac_LV02Doc.h"
#include "16978_Mihajlo_Sutanovac_LV02View.h"
#define kvadratic 25
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy16978MihajloSutanovacLV02View

IMPLEMENT_DYNCREATE(CMy16978MihajloSutanovacLV02View, CView)

BEGIN_MESSAGE_MAP(CMy16978MihajloSutanovacLV02View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy16978MihajloSutanovacLV02View construction/destruction

CMy16978MihajloSutanovacLV02View::CMy16978MihajloSutanovacLV02View() noexcept
{
	// TODO: add construction code here

}

CMy16978MihajloSutanovacLV02View::~CMy16978MihajloSutanovacLV02View()
{
}

BOOL CMy16978MihajloSutanovacLV02View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy16978MihajloSutanovacLV02View drawing

void drawCircle(CDC* pDC, int x, int y)
{
	CBrush brush;
	CBrush* oldBrush;
	brush.CreateSolidBrush(RGB(48, 191, 0));
	oldBrush = pDC->SelectObject(&brush);
	pDC->Ellipse(x - kvadratic / 2, y - kvadratic / 2, x + kvadratic / 2, y + kvadratic / 2);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
}

void drawSaksija(CDC* pDC)
{
	CBrush brush;
	CBrush* oldBrush;
	brush.CreateSolidBrush(RGB(204, 156, 0));
	oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(7 * kvadratic + 2 * kvadratic / 3, 17 * kvadratic + kvadratic / 5, 12 * kvadratic + kvadratic / 3, 18 * kvadratic+1);
	pDC->Polygon(new CPoint[4]{ CPoint(8 * kvadratic,18 * kvadratic),CPoint(12 * kvadratic,18 * kvadratic),CPoint(12 * kvadratic - kvadratic / 3,20 * kvadratic),CPoint(8 * kvadratic + kvadratic / 3,20 * kvadratic) }, 4);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
}

void drawKaktus(CDC* pDC, int x, int y,int size, bool tamni)
{
	HENHMETAFILE k;
	if (tamni)
		k = GetEnhMetaFile(L"res/cactus_part.emf");
	else
		k = GetEnhMetaFile(L"res/cactus_part_light.emf");
	pDC->PlayMetaFile(k,CRect(x-size,y,x+size,y+75));
	DeleteEnhMetaFile(k);
}

void Rotiraj(XFORM* xform, float angle, int x, int y)
{
	xform->eDx = x;
	xform->eDy = y;
	xform->eM11 = cos(angle);
	xform->eM12 = -sin(angle);
	xform->eM21 = sin(angle);
	xform->eM22 = cos(angle);
}

void drawGrid(CDC* pDC, int width, int height)
{
	CPen newPen(PS_SOLID, 1, RGB(229, 229, 229));

	pDC->SelectObject(newPen);

	POINT linija[2] = { 0,0,width,0 };
	for (int i = 0; i < height / kvadratic + 1; i++)
	{
		pDC->Polyline(linija, 2);
		linija[0].x = 0;
		linija[0].y = (i + 1) * kvadratic;
		linija[1].x = width;
		linija[1].y = linija[0].y;
	}
	linija[0].x = 0;
	linija[0].y = 0;
	linija[1].x = height;
	linija[1].y = 0;
	for (int i = 0; i < width / kvadratic + 1; i++)
	{
		pDC->Polyline(linija, 2);
		linija[0].x = (i + 1) * kvadratic;
		linija[0].y = 0;
		linija[1].x = (i + 1) * kvadratic;
		linija[1].y = height;
	}
}

void drawTekst(CDC* pDC)
{
	CFont font, *oldFont;
	font.CreateFontW(1.5*kvadratic, 0, -900, -900, 600, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
	oldFont = pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOutW(19 * kvadratic+2, 1 * kvadratic+1, CString("16978 Mihajlo Sutanovac"));
	pDC->SetTextColor(RGB(255, 255, 0));
	pDC->TextOutW(19 * kvadratic, 1 * kvadratic, CString("16978 Mihajlo Sutanovac"));
	pDC->SelectObject(oldFont);
	font.DeleteObject();
	pDC->SetBkMode(OPAQUE);
	pDC->SetTextColor(RGB(1, 1, 1));
}

void CMy16978MihajloSutanovacLV02View::OnDraw(CDC* pDC)
{
	CMy16978MihajloSutanovacLV02Doc* pDoc = GetDocument();
	int width = 500;
	int height = 500;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->SetGraphicsMode(GM_ADVANCED);
	CBrush brush;
	CBrush* oldBrush;

	//plava pozadina
	brush.CreateSolidBrush(RGB(131, 235, 231));
	oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(0, 0, 500, 500);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	drawKaktus(pDC, 10 * kvadratic, 14 * kvadratic,30, true);
	XFORM* xform = new XFORM();
	pDC->SetWorldTransform(xform);
	
	//leva grana
	Rotiraj(xform, pi / 4, 10 * kvadratic, 14 * kvadratic);
	pDC->ModifyWorldTransform(xform, MWT_LEFTMULTIPLY);
	drawKaktus(pDC, 0, -3*kvadratic,10, true);
	drawKaktus(pDC, 0, -6*kvadratic,30, true);
	drawKaktus(pDC, 0,-9*kvadratic,30, true);
	drawCircle(pDC, 0, -3 * kvadratic);
	drawCircle(pDC, 0, -6 * kvadratic);

	//sredisnja grana
	Rotiraj(xform, - pi / 4 + this->angleFirst, 0,0);
	pDC->ModifyWorldTransform(xform, MWT_LEFTMULTIPLY);
	drawKaktus(pDC, 0, -3 * kvadratic, 10, false);

	Rotiraj(xform, pi / 4 , 0, -3*kvadratic);
	pDC->ModifyWorldTransform(xform, MWT_LEFTMULTIPLY);
	drawKaktus(pDC, 0, -3 * kvadratic, 20, true);

	Rotiraj(xform, - pi / 2, 0, 0);
	pDC->ModifyWorldTransform(xform, MWT_LEFTMULTIPLY);
	drawKaktus(pDC, 0, -3 * kvadratic, 20, true);
	drawCircle(pDC, 0, 0);

	
	pDC->ModifyWorldTransform(xform, MWT_IDENTITY);

	Rotiraj(xform, -pi / 4, 10*kvadratic, 14 * kvadratic);
	pDC->ModifyWorldTransform(xform, MWT_LEFTMULTIPLY);

	drawKaktus(pDC, 0, -3 * kvadratic, 10, true);

	Rotiraj(xform, this->angleSecond, 0, -3 * kvadratic);
	pDC->ModifyWorldTransform(xform, MWT_LEFTMULTIPLY);

	drawKaktus(pDC, 0, -3 * kvadratic, 30, false);
	drawCircle(pDC, 0, 0);

	Rotiraj(xform, pi/4, 0, -3*kvadratic);
	pDC->ModifyWorldTransform(xform, MWT_LEFTMULTIPLY);
	drawKaktus(pDC, 0, -3 * kvadratic, 20, true);

	Rotiraj(xform, -pi / 2, 0, 0);
	pDC->ModifyWorldTransform(xform, MWT_LEFTMULTIPLY);
	drawKaktus(pDC, 0, -3 * kvadratic, 20, true);

	drawCircle(pDC, 0, 0);

	pDC->ModifyWorldTransform(xform, MWT_IDENTITY);
	drawCircle(pDC, 10 * kvadratic, 14 * kvadratic);
	drawCircle(pDC, 10 * kvadratic, 17 * kvadratic);
	drawSaksija(pDC);

	if (this->grid)
		drawGrid(pDC, width, height);

	drawTekst(pDC);
}

afx_msg void CMy16978MihajloSutanovacLV02View::OnKeyDown(UINT nChar, UINT nReptCnt, UINT nFlags)
{
	if (nChar == 'G')
	{
		this->grid = !this->grid;
	}
	if (nChar == 'A')
	{
		this->angleFirst += pi / 30;
	}
	if (nChar == 'S')
	{
		this->angleFirst -= pi / 30;
	}
	if (nChar == 'D')
	{
		this->angleSecond += pi / 30;
	}
	if (nChar == 'F')
	{
		this->angleSecond -= pi / 30;
	}
	this->Invalidate();
}

// CMy16978MihajloSutanovacLV02View printing

BOOL CMy16978MihajloSutanovacLV02View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy16978MihajloSutanovacLV02View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy16978MihajloSutanovacLV02View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy16978MihajloSutanovacLV02View diagnostics

#ifdef _DEBUG
void CMy16978MihajloSutanovacLV02View::AssertValid() const
{
	CView::AssertValid();
}

void CMy16978MihajloSutanovacLV02View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy16978MihajloSutanovacLV02Doc* CMy16978MihajloSutanovacLV02View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy16978MihajloSutanovacLV02Doc)));
	return (CMy16978MihajloSutanovacLV02Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy16978MihajloSutanovacLV02View message handlers
