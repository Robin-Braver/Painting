#pragma once
#include "CLayer.h"
class CLine :public CLayer
{
public:
	CLine();
	~CLine();
	void OnDraw(CDC* pDC);
	void OnLButtonDown(UINT nFlags, CPoint point) ;
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC);
	void SelectLayer(UINT nFlags, CPoint point);
	void Offset(CPoint ptOffset);
	int GetDistance(CPoint point);//��ȡĳ�㵽����ֱ�ߵľ���
private:
	CPoint m_ps, m_pe;//��ʼ�յ�
};

