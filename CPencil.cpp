#include "pch.h"
#include "CPencil.h"

CPencil::CPencil()
{
}

CPencil::~CPencil()
{
}

void CPencil::OnDraw(CDC* pDC)
{
	CPen pen(PS_SOLID, 1, m_front);
	CPen* pOldPen = pDC->SelectObject(&pen);
	int i = 0, nSize = m_ps.GetSize();
	if (nSize <= 0)return;//防止为空
	pDC->MoveTo(m_ps[i++]);
	while (i< nSize)
		pDC->LineTo(m_ps[i++]);
	pDC->SelectObject(&pOldPen);
	if (m_eType == T_SELECTED)//如果是选中状态,就在两端画两个点
	{
		CPoint& ps = m_ps[0];
		pDC->FillSolidRect(ps.x - 3, ps.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
		CPoint& pe = m_ps[nSize-1];
		pDC->FillSolidRect(pe.x - 3, pe.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
	}	
}

void CPencil::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ps.Add(point);//每次点一下记录下一个点
}

void CPencil::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_ps.Add(point);
	m_eType = T_NORMAL;//弹起变为普通状态
}

void CPencil::OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
{
	if (nFlags & MK_LBUTTON)
	{
		int nSize = m_ps.GetSize();
		if (nSize > 0)
			pDC->MoveTo(m_ps[nSize - 1]);
		m_ps.Add(point);
		pDC->LineTo(point);
	}
}

void CPencil::SelectLayer(UINT nFlags, CPoint point)
{
	int i = 0, nSize = m_ps.GetSize();
	while (i < nSize)//遍历每个点
	{
		CPoint pt = m_ps[i++];
		int cx = pt.x - point.x;
		int cy = pt.y - point.y;
		if (sqrt(cx * cx + cy * cy) < 10)//如果点在当前这条直线上
		{
			m_eType = T_SELECTED;//变为选中状态
			break;
		}
		else
			m_eType = T_NORMAL;
	}

	m_ptSel = point;//记录下被点击的点
	return;	
}

void CPencil::Offset(CPoint ptOffset)
{
	int i = 0, nSize = m_ps.GetSize();
	while (i < nSize)//遍历每个点,平移
		m_ps[i++].Offset(ptOffset);
}

