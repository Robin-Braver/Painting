
// PaintingView.cpp: CPaintingView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Painting.h"
#endif

#include "PaintingDoc.h"
#include "PaintingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CPaintingView

IMPLEMENT_DYNCREATE(CPaintingView, CView)

BEGIN_MESSAGE_MAP(CPaintingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DRAW_ARROW, &CPaintingView::OnDrawArrow)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CPaintingView::OnDrawEllipse)
	ON_COMMAND(ID_DRAW_LINE, &CPaintingView::OnDrawLine)
	ON_COMMAND(ID_DRAW_PENCIL, &CPaintingView::OnDrawPencil)
	ON_COMMAND(ID_DRAW_RECT, &CPaintingView::OnDrawRect)
//	ON_COMMAND(ID_DRAW_SEL, &CPaintingView::OnDrawSel)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ARROW, &CPaintingView::OnUpdateDrawArrow)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &CPaintingView::OnUpdateDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CPaintingView::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PENCIL, &CPaintingView::OnUpdateDrawPencil)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &CPaintingView::OnUpdateDrawRect)
//	ON_UPDATE_COMMAND_UI(ID_DRAW_SEL, &CPaintingView::OnUpdateDrawSel)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_BACK, &CPaintingView::OnDrawBack)
	ON_COMMAND(ID_DRAW_FRONT, &CPaintingView::OnDrawFront)
	ON_COMMAND(ID_FILE_NEW, &CPaintingView::OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CPaintingView::OnUpdateFileNew)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(IDM_WRITEFILE, &CPaintingView::OnWritefile)
//	ON_UPDATE_COMMAND_UI(IDM_WRITEFILE, &CPaintingView::OnUpdateWritefile)
//	ON_COMMAND(ID_FILE_OPEN, &CPaintingView::OnFileOpen)
//	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CPaintingView::OnUpdateFileOpen)
END_MESSAGE_MAP()

// CPaintingView 构造/析构

CPaintingView::CPaintingView() noexcept
{
	
}

void CPaintingView::SelectLayer(UINT nFlags, CPoint point)
{	
	CPaintingDoc* pDoc = GetDocument();
	int i = 0; INT_PTR nSize = pDoc->m_arr.GetSize();
	while (i < nSize)
		pDoc->m_arr[i++]->SelectLayer(nFlags, point);
	Invalidate(TRUE);
}

void CPaintingView::SelectEnd(UINT nFlags, CPoint point)
{
	CLayer* pLayer = NULL;
	CPaintingDoc* pDoc = GetDocument();
	int i = 0; INT_PTR nSize = pDoc->m_arr.GetSize();
	while (i < nSize)//遍历每一个，找到选中
	{
		pLayer = pDoc->m_arr[i++];
		if (pLayer->m_eType==T_SELECTED)
		{
			pLayer->Offset(point-pLayer->m_ptSel);
		}
	}
	Invalidate(TRUE);
}



CPaintingView::~CPaintingView()
{
	
}

BOOL CPaintingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPaintingView 绘图

void CPaintingView::OnDraw(CDC* pDC)
{
	CPaintingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int i = 0; INT_PTR nSize = pDoc->m_arr.GetSize();
	while (i<nSize)
	{
		pDoc->m_arr[i]->OnDraw(pDC);
		++i;
	}
}


// CPaintingView 打印

BOOL CPaintingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPaintingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPaintingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPaintingView 诊断

#ifdef _DEBUG
void CPaintingView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintingDoc* CPaintingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintingDoc)));
	return (CPaintingDoc*)m_pDocument;
}
#endif //_DEBUG


// CPaintingView 消息处理程序


void CPaintingView::OnDrawArrow()
{
	CPaintingDoc* pDoc = GetDocument();
	pDoc->m_nDrawIndex = ID_DRAW_ARROW;
}


void CPaintingView::OnDrawEllipse()
{
	CPaintingDoc* pDoc = GetDocument();
	pDoc->m_nDrawIndex = ID_DRAW_ELLIPSE;
}


void CPaintingView::OnDrawLine()
{
	CPaintingDoc* pDoc = GetDocument();
	pDoc->m_nDrawIndex = ID_DRAW_LINE;
}


void CPaintingView::OnDrawPencil()
{
	CPaintingDoc* pDoc = GetDocument();
	pDoc->m_nDrawIndex = ID_DRAW_PENCIL;
}


void CPaintingView::OnDrawRect()
{
	CPaintingDoc* pDoc = GetDocument();
	pDoc->m_nDrawIndex = ID_DRAW_RECT;
}

void CPaintingView::OnFileNew()
{
	CPaintingDoc* pDoc = GetDocument();
	pDoc->m_nDrawIndex = ID_FILE_NEW;
}




void CPaintingView::OnUpdateDrawArrow(CCmdUI* pCmdUI)
{
	CPaintingDoc* pDoc = GetDocument();
	pCmdUI->SetRadio(pDoc->m_nDrawIndex==ID_DRAW_ARROW);
	
}

void CPaintingView::OnUpdateDrawEllipse(CCmdUI* pCmdUI)
{
	CPaintingDoc* pDoc = GetDocument();
	pCmdUI->SetRadio(pDoc->m_nDrawIndex == ID_DRAW_ELLIPSE);
}


void CPaintingView::OnUpdateDrawLine(CCmdUI* pCmdUI)
{
	CPaintingDoc* pDoc = GetDocument();
	pCmdUI->SetRadio(pDoc->m_nDrawIndex == ID_DRAW_LINE);
}


void CPaintingView::OnUpdateDrawPencil(CCmdUI* pCmdUI)
{
	CPaintingDoc* pDoc = GetDocument();
	pCmdUI->SetRadio(pDoc->m_nDrawIndex == ID_DRAW_PENCIL);
}


void CPaintingView::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	CPaintingDoc* pDoc = GetDocument();
	pCmdUI->SetRadio(pDoc->m_nDrawIndex == ID_DRAW_RECT);
}




void CPaintingView::OnUpdateFileNew(CCmdUI* pCmdUI)
{
	CPaintingDoc* pDoc = GetDocument();
	pCmdUI->SetRadio(pDoc->m_nDrawIndex == ID_FILE_NEW);
}



void CPaintingView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPaintingDoc* pDoc = GetDocument();
	SelectLayer(nFlags, point);
	for (int i = 0; i < pDoc->m_arr.GetSize(); )
	{
		if (pDoc->m_arr[i]->m_eType == T_SELECTED)//如果被选中状态
			pDoc->m_arr.RemoveAt(i);//删除了图像就不加下标，动态改变		
		else
			++i;
	}
	CView::OnRButtonDown(nFlags, point);
}




void CPaintingView::OnRButtonUp(UINT nFlags, CPoint point)
{	
	Invalidate(FALSE);//更新画面
	CView::OnRButtonUp(nFlags, point);
}


void CPaintingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPaintingDoc* pDoc = GetDocument();
	if (ID_DRAW_ARROW == pDoc->m_nDrawIndex)//选中的是鼠标状态
	{
		SelectLayer(nFlags, point);
		return;
	}
	if (ID_FILE_NEW == pDoc->m_nDrawIndex)//新建文件状态
	{
		pDoc->m_arr.RemoveAll();
	
		return;
	}

	CLayer* pLayer = NULL;
	switch (pDoc->m_nDrawIndex)
	{
	case ID_DRAW_LINE:
		pLayer = new CLine;
		break;
	case ID_DRAW_RECT:
		pLayer = new CRectan;
		break;
	case ID_DRAW_PENCIL:
		pLayer = new CPencil;
		break;
	case ID_DRAW_ELLIPSE:
		pLayer = new CEllipse;
		break;
	}
	if (pLayer)
	{
		pLayer->m_front = theApp.m_dFront;
		pLayer->m_back = theApp.m_dBack;
		pLayer->OnLButtonDown(nFlags, point);
		pDoc->m_arr.Add(pLayer);
	}

	CView::OnLButtonDown(nFlags, point);
}


void CPaintingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CPaintingDoc* pDoc = GetDocument();
	
	if (pDoc->m_nDrawIndex == ID_DRAW_ARROW)
	{
		SelectEnd(nFlags, point);
		return;
	}

	if (ID_FILE_NEW == pDoc->m_nDrawIndex)//新建文件状态
	{
		Invalidate();
		return;
	}

	INT_PTR nSize = pDoc->m_arr.GetSize();
	if (nSize <= 0)return;
	pDoc->m_arr[nSize-1]->OnLButtonUp(nFlags, point);
	Invalidate(FALSE);//更新画面
	CView::OnLButtonUp(nFlags, point);
}


void CPaintingView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPaintingDoc* pDoc = GetDocument();
	CView::OnMouseMove(nFlags, point);
	if (ID_DRAW_ARROW == pDoc->m_nDrawIndex)//选中的是鼠标状态
		return;
	INT_PTR nSize = pDoc->m_arr.GetSize();
	if (nSize <= 0)return;
	CClientDC dc(this);	
	pDoc->m_arr[nSize - 1]->OnMouseMove(nFlags, point,&dc);
}


void CPaintingView::OnDrawBack()
{
	
	CColorDialog dlg(theApp.m_dBack);
	if (dlg.DoModal() == IDCANCEL)
		return;
	theApp.m_dBack = dlg.GetColor();
}


void CPaintingView::OnDrawFront()
{
	
	//设置缺省，设置选中颜色
	CColorDialog dlg(theApp.m_dFront);
	if (dlg.DoModal() == IDCANCEL)
		return;
	theApp.m_dFront = dlg.GetColor();
}



