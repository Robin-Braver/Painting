#pragma once
#include <afxwin.h>
//弹起是普通状态
enum EType { T_NORMAL, T_DRAWING, T_SELECTED };//记录绘画和选中状态,以及普通状态
class CLayer:public CObject
{
public:
	EType m_eType;//记录状态
	CPoint m_ptSel;//记录选中的点
	COLORREF m_back, m_front;//涂鸦色，铅笔色
	virtual void OnDraw(CDC* pDC) = 0;//虚函数自动切换到派生类
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) =0;
	virtual void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC = NULL) = 0;
	virtual void SelectLayer(UINT nFlags, CPoint point) = 0;
	virtual void Offset(CPoint ptOffset)=0;

	CLayer();
	virtual ~CLayer();//清理内存时，清理派生类内存
};

