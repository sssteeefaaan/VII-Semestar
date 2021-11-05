
// Lab5View.cpp : implementation of the CLab5View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab5.h"
#endif

#include "Lab5Doc.h"
#include "Lab5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab5View

IMPLEMENT_DYNCREATE(CLab5View, CView)

BEGIN_MESSAGE_MAP(CLab5View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KEYUP()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CLab5View construction/destruction

CLab5View::CLab5View() noexcept
{
	// TODO: add construction code here

}

CLab5View::~CLab5View()
{
}

BOOL CLab5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab5View drawing

void CLab5View::OnDraw(CDC* pDC)
{
	CLab5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);
}


// CLab5View printing

BOOL CLab5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLab5View diagnostics

#ifdef _DEBUG
void CLab5View::AssertValid() const
{
	CView::AssertValid();
}

void CLab5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab5Doc* CLab5View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab5Doc)));
	return (CLab5Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab5View message handlers


int CLab5View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void CLab5View::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


BOOL CLab5View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	// return CView::OnEraseBkgnd(pDC);
}


void CLab5View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == 'r' || nChar == 'R')
	{
		m_glRenderer.PromeniCrvenoSvetlo();
		Invalidate();
	}

	else if (nChar == 'g' || nChar == 'G')
	{
		m_glRenderer.PromeniZelenoSvetlo();
		Invalidate();
	}

	else if (nChar == 'b' || nChar == 'B')
	{
		m_glRenderer.PromeniPlavoSvetlo();
		Invalidate();
	}

	else if (nChar == 'n' || nChar == 'N')
	{
		m_glRenderer.PromeniNormale();
		Invalidate();
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CLab5View::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_glRenderer.StopMovingCamera();

	CView::OnLButtonUp(nFlags, point);
}


void CLab5View::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		m_glRenderer.MoveCamera(point);
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}


void CLab5View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void CLab5View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}
