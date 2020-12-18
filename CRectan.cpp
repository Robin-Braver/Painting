#include "pch.h"
#include "CRectan.h"

CRectan::CRectan():m_rect(MAXLONG,MAXLONG, MAXLONG, MAXLONG)
{
}

CRectan::~CRectan()
{
}

void CRectan::OnDraw(CDC* pDC)
{
	CPen pen(PS_SOLID, 1, m_front);
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush br(m_back);
	CBrush* pOldBrush = pDC->SelectObject(&br);
	pDC->Rectangle(m_rect);
	pDC->SelectObject(&pOldPen);
	pDC->SelectObject(&pOldBrush);
	if (m_eType == T_SELECTED)//如果是选中状态,就在两个角画点点
	{
		CPoint& p1 = m_rect.TopLeft();
		pDC->FillSolidRect(p1.x - 3, p1.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
		CPoint& p2 = m_rect.BottomRight();
		pDC->FillSolidRect(p2.x - 3, p2.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
		CPoint p3(m_rect.right,m_rect.top);
		pDC->FillSolidRect(p3.x - 3, p3.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
		CPoint p4(m_rect.left, m_rect.bottom);
		pDC->FillSolidRect(p4.x - 3, p4.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));	
	}
}

void CRectan::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_rect.TopLeft() = point;
}

void CRectan::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_rect.BottomRight() = point;
	m_rect.NormalizeRect();//规范化
	m_eType = T_NORMAL;//弹起变为普通状态
}

void CRectan::OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
{
	if (nFlags && MK_LBUTTON)//判断是否拖着
	{
		
		HBRUSH hbr = HBRUSH(GetStockObject(NULL_BRUSH));//获取准备好的颜色
		pDC->SelectObject(hbr);
		pDC->SetROP2(R2_NOT);//反射画
		if (m_rect.right != MAXLONG)//区别初始化状态
		{
			pDC->Rectangle(m_rect);
		}
		m_rect.BottomRight() = point;
		pDC->Rectangle(m_rect);
	}
}

void CRectan::SelectLayer(UINT nFlags, CPoint point)
{
	if (m_rect.PtInRect(point))
		m_eType = T_SELECTED;//变为选中状态
	else
		m_eType = T_NORMAL;
	m_ptSel = point;//记录下被点击的点
	return;
	
}

void CRectan::Offset(CPoint ptOffset)
{
	m_rect.OffsetRect(ptOffset);
}





