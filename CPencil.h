#pragma once
#include "CLayer.h"
class CPencil :public CLayer
{
public:
	CPencil();
	~CPencil();
	void OnDraw(CDC* pDC);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC);
	void SelectLayer(UINT nFlags, CPoint point);
	void Offset(CPoint ptOffset);
	
private:
	CArray<CPoint>m_ps;//记录移动过程中的点
};

