
// Lab_5_vaza_3DView.cpp : implementation of the CLab5vaza3DView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab_5_vaza_3D.h"
#endif

#include "Lab_5_vaza_3DDoc.h"
#include "Lab_5_vaza_3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab5vaza3DView

IMPLEMENT_DYNCREATE(CLab5vaza3DView, CView)

BEGIN_MESSAGE_MAP(CLab5vaza3DView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CLab5vaza3DView construction/destruction

CLab5vaza3DView::CLab5vaza3DView() noexcept
{
	// TODO: add construction code here
	m_isDragged = false;
}

CLab5vaza3DView::~CLab5vaza3DView()
{
}

BOOL CLab5vaza3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab5vaza3DView drawing

void CLab5vaza3DView::OnDraw(CDC* pDC)
{
	CLab5vaza3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);
	// TODO: add draw code for native data here
}


// CLab5vaza3DView printing

BOOL CLab5vaza3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab5vaza3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab5vaza3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLab5vaza3DView diagnostics

#ifdef _DEBUG
void CLab5vaza3DView::AssertValid() const
{
	CView::AssertValid();
}

void CLab5vaza3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab5vaza3DDoc* CLab5vaza3DView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab5vaza3DDoc)));
	return (CLab5vaza3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CLab5vaza3DView message handlers


int CLab5vaza3DView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void CLab5vaza3DView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);

	// TODO: Add your message handler code here
}


void CLab5vaza3DView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);

	// TODO: Add your message handler code here
}


void CLab5vaza3DView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);

	// TODO: Add your specialized code here and/or call the base class
}


BOOL CLab5vaza3DView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CLab5vaza3DView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_isDragged = true;
	m_glRenderer.SetCurrentPt(&point);
	CView::OnLButtonDown(nFlags, point);
}


void CLab5vaza3DView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_isDragged = false;
	m_glRenderer.SetMemAngles();
	CView::OnLButtonUp(nFlags, point);
}


void CLab5vaza3DView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_isDragged)
	{
		m_glRenderer.RotateView(&point);
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}


void CLab5vaza3DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	if (nChar == 'r' || nChar == 'R')
	{ 
		m_glRenderer.ToggleRed();
		Invalidate();
	}

	else if (nChar == 'g' || nChar == 'G')
	{ 
		m_glRenderer.ToggleGreen();
		Invalidate();
	}

	else if (nChar == 'b' || nChar == 'B')
	{
		m_glRenderer.ToggleBlue();
		Invalidate();
	}

	else if (nChar == 'n' || nChar == 'N')
	{
		m_glRenderer.ToggleNormals();
		Invalidate();
	}
	
}
