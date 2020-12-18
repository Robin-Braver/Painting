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
	if (m_eType == T_SELECTED)//�����ѡ��״̬,���������ǻ����
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
	m_rect.NormalizeRect();//�淶��
	m_eType = T_NORMAL;//�����Ϊ��ͨ״̬
}

void CRectan::OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
{
	if (nFlags && MK_LBUTTON)//�ж��Ƿ�����
	{
		
		HBRUSH hbr = HBRUSH(GetStockObject(NULL_BRUSH));//��ȡ׼���õ���ɫ
		pDC->SelectObject(hbr);
		pDC->SetROP2(R2_NOT);//���仭
		if (m_rect.right != MAXLONG)//�����ʼ��״̬
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
		m_eType = T_SELECTED;//��Ϊѡ��״̬
	else
		m_eType = T_NORMAL;
	m_ptSel = point;//��¼�±�����ĵ�
	return;
	
}

void CRectan::Offset(CPoint ptOffset)
{
	m_rect.OffsetRect(ptOffset);
}





