
// PaintingView.h: CPaintingView 类的接口
//

#pragma once
#include "CLayer.h"
#include"CLine.h"
#include"CRectan.h"
#include"CPencil.h"
#include"CEllipse.h"


class CPaintingView : public CView
{
public:
	
protected: // 仅从序列化创建
	CPaintingView() noexcept;
	DECLARE_DYNCREATE(CPaintingView)

// 特性
public:
	CPaintingDoc* GetDocument() const;
	void SelectLayer(UINT nFlags, CPoint point);
	void SelectEnd(UINT nFlags, CPoint point);
// 操作
public:
	
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPaintingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawArrow();
	afx_msg void OnDrawEllipse();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawPencil();
	afx_msg void OnDrawRect();
	afx_msg void OnUpdateDrawArrow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawPencil(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawBack();
	afx_msg void OnDrawFront();
	afx_msg void OnFileNew();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnWritefile();
//	afx_msg void OnUpdateWritefile(CCmdUI* pCmdUI);
//	afx_msg void OnFileOpen();
//	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
private:
};

#ifndef _DEBUG  // PaintingView.cpp 中的调试版本
inline CPaintingDoc* CPaintingView::GetDocument() const
   { return reinterpret_cast<CPaintingDoc*>(m_pDocument); }
#endif

