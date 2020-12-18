#include "pch.h"
#include "CLine.h"

CLine::CLine():m_ps(0, 0),m_pe(MAXLONG, MAXLONG)
{
}

CLine::~CLine()
{
}

void CLine::OnDraw(CDC* pDC)
{
	CPen pen(PS_SOLID, 1, m_front);
	CPen*pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(m_ps);
	pDC->LineTo(m_pe);
	pDC->SelectObject(&pOldPen);//�ָ�
	if (this->m_eType == T_SELECTED)//ѡ��״̬
	{
		pDC->FillSolidRect(m_ps.x - 3, m_ps.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillSolidRect(m_pe.x - 3, m_pe.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
	}
}

void CLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ps = point;
}

void CLine::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_pe = point;
	m_eType = T_NORMAL;//�����Ϊ��ͨ״̬	
}

void CLine::OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
{
	if (nFlags && MK_LBUTTON)//�ж��Ƿ�����
	{
		pDC->SetROP2(R2_NOT);//���仭
		if (m_pe.x != MAXLONG)//�����ʼ��״̬
		{
			pDC->MoveTo(m_ps);
			pDC->LineTo(m_pe);	
		}
		m_pe = point;
		pDC->MoveTo(m_ps);
		pDC->LineTo(m_pe);
	}
}

void CLine::SelectLayer(UINT nFlags, CPoint point)
{
	int dis = GetDistance(point);
	if (dis<10)
		m_eType = T_SELECTED;//��Ϊѡ��״̬
	else
		m_eType = T_NORMAL;
	m_ptSel = point;//��¼�±�����ĵ�
	return;
}

void CLine::Offset(CPoint ptOffset)//����ƽ��
{
	m_pe.Offset(ptOffset);
	m_ps.Offset(ptOffset);
}

int CLine::GetDistance(CPoint point)
{
	int x0, x1, x2, y0, y1, y2;
	x1 = m_ps.x;
	x2 = m_pe.x;
	y1 = m_ps.y;
	y2 = m_pe.y;
	x0 = point.x;
	y0 = point.y;
	int m = (y1 - y2) * x0 - (x1 - x2) * y0 + y1 * (x1 - x2) - x1 * (y1 - y2);
	int n = (y1 - y2) * (y1 - y2)+(x1-x2)*(x1-x2);
	n = sqrt(n);

	return abs(m)/n;
}


