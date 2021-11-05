
// OpenGL_Priprema_IspitView.cpp : implementation of the COpenGLPripremaIspitView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL_Priprema_Ispit.h"
#endif

#include "OpenGL_Priprema_IspitDoc.h"
#include "OpenGL_Priprema_IspitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLPripremaIspitView

IMPLEMENT_DYNCREATE(COpenGLPripremaIspitView, CView)

BEGIN_MESSAGE_MAP(COpenGLPripremaIspitView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COpenGLPripremaIspitView construction/destruction

COpenGLPripremaIspitView::COpenGLPripremaIspitView() noexcept
{
	// TODO: add construction code here

}

COpenGLPripremaIspitView::~COpenGLPripremaIspitView()
{
}

BOOL COpenGLPripremaIspitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenGLPripremaIspitView drawing

void COpenGLPripremaIspitView::OnDraw(CDC* pDC)
{
	COpenGLPripremaIspitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);
}


// COpenGLPripremaIspitView printing

BOOL COpenGLPripremaIspitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLPripremaIspitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLPripremaIspitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COpenGLPripremaIspitView diagnostics

#ifdef _DEBUG
void COpenGLPripremaIspitView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLPripremaIspitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLPripremaIspitDoc* COpenGLPripremaIspitView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLPripremaIspitDoc)));
	return (COpenGLPripremaIspitDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLPripremaIspitView message handlers


BOOL COpenGLPripremaIspitView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


int COpenGLPripremaIspitView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void COpenGLPripremaIspitView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void COpenGLPripremaIspitView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


void COpenGLPripremaIspitView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


BOOL COpenGLPripremaIspitView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void COpenGLPripremaIspitView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT)
		m_glRenderer.RotateView(0, -3);
	else if (nChar == VK_LEFT)
		m_glRenderer.RotateView(0, 3);
	else if (nChar == VK_UP)
		m_glRenderer.RotateView(3, 0);
	else if (nChar == VK_DOWN)
		m_glRenderer.RotateView(-3, 0);

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
