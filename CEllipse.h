#pragma once
#include "CLayer.h"
class CEllipse :public CLayer
{
public:
	CEllipse();
	~CEllipse();
	void OnDraw(CDC* pDC);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC);
	void SelectLayer(UINT nFlags, CPoint point);
	void Offset(CPoint ptOffset);
private:
	CRect m_rect;
};

