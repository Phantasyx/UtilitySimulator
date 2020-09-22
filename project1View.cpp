
// project1View.cpp : implementation of the Cproject1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "project1.h"
#endif

#include "project1Doc.h"
#include "project1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cproject1View

IMPLEMENT_DYNCREATE(Cproject1View, CView)

BEGIN_MESSAGE_MAP(Cproject1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cproject1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cproject1View construction/destruction

Cproject1View::Cproject1View()
{
	// TODO: add construction code here

}

Cproject1View::~Cproject1View()
{
}

BOOL Cproject1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cproject1View drawing

void Cproject1View::OnDraw(CDC* /*pDC*/)
{
	Cproject1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Cproject1View printing


void Cproject1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cproject1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cproject1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cproject1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cproject1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cproject1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cproject1View diagnostics

#ifdef _DEBUG
void Cproject1View::AssertValid() const
{
	CView::AssertValid();
}

void Cproject1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cproject1Doc* Cproject1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cproject1Doc)));
	return (Cproject1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cproject1View message handlers
