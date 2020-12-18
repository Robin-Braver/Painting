
// PaintingDoc.h: CPaintingDoc 类的接口
//


#pragma once

#pragma once
#include "CLayer.h"
class CPaintingDoc : public CDocument
{
protected: // 仅从序列化创建
	CPaintingDoc() noexcept;
	DECLARE_DYNCREATE(CPaintingDoc)

// 特性
public:
	int m_nDrawIndex;//记录选中菜单
	CArray<CLayer*>m_arr;//存储画的物品
// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CPaintingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
	virtual void SetTitle(LPCTSTR lpszTitle);
};
