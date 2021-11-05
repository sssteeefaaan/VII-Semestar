
// OpenGLPokusajPrviView.cpp : implementation of the COpenGLPokusajPrviView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGLPokusajPrvi.h"
#endif

#include "OpenGLPokusajPrviDoc.h"
#include "OpenGLPokusajPrviView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLPokusajPrviView

IMPLEMENT_DYNCREATE(COpenGLPokusajPrviView, CView)

BEGIN_MESSAGE_MAP(COpenGLPokusajPrviView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COpenGLPokusajPrviView construction/destruction

COpenGLPokusajPrviView::COpenGLPokusajPrviView()
{
	// TODO: add construction code here

}

COpenGLPokusajPrviView::~COpenGLPokusajPrviView()
{
}

BOOL COpenGLPokusajPrviView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenGLPokusajPrviView drawing

void COpenGLPokusajPrviView::OnDraw(CDC* pDC)
{
	COpenGLPokusajPrviDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.PrepareScene(pDC);
	m_glRenderer.DrawScene(pDC);
	// TODO: add draw code for native data here
}


// COpenGLPokusajPrviView printing

BOOL COpenGLPokusajPrviView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLPokusajPrviView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLPokusajPrviView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COpenGLPokusajPrviView diagnostics

#ifdef _DEBUG
void COpenGLPokusajPrviView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLPokusajPrviView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLPokusajPrviDoc* COpenGLPokusajPrviView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLPokusajPrviDoc)));
	return (COpenGLPokusajPrviDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLPokusajPrviView message handlers


int COpenGLPokusajPrviView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


BOOL COpenGLPokusajPrviView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;

	//return CView::OnEraseBkgnd(pDC);
}


void COpenGLPokusajPrviView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void COpenGLPokusajPrviView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


void COpenGLPokusajPrviView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


void COpenGLPokusajPrviView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == 'K'){
		m_glRenderer.rotacija += 10;
	
	}
	if (nChar == 'J'){
		m_glRenderer.rotacija -= 10;

	}

	if (nChar == 'L'){
		m_glRenderer.rotacija2 += 10;
	}
	if (nChar == 'R'){
		m_glRenderer.rotacija3 += 10;
	}

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
