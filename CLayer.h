#pragma once
#include <afxwin.h>
//��������ͨ״̬
enum EType { T_NORMAL, T_DRAWING, T_SELECTED };//��¼�滭��ѡ��״̬,�Լ���ͨ״̬
class CLayer:public CObject
{
public:
	EType m_eType;//��¼״̬
	CPoint m_ptSel;//��¼ѡ�еĵ�
	COLORREF m_back, m_front;//Ϳѻɫ��Ǧ��ɫ
	virtual void OnDraw(CDC* pDC) = 0;//�麯���Զ��л���������
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) =0;
	virtual void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC = NULL) = 0;
	virtual void SelectLayer(UINT nFlags, CPoint point) = 0;
	virtual void Offset(CPoint ptOffset)=0;

	CLayer();
	virtual ~CLayer();//�����ڴ�ʱ�������������ڴ�
};

