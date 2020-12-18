
// PaintingDoc.cpp: CPaintingDoc 类的实现
//
#pragma once
#include "pch.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Painting.h"
#endif

#include "PaintingDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MainFrm.h"
#include "PaintingView.h"

// CPaintingDoc

IMPLEMENT_DYNCREATE(CPaintingDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaintingDoc, CDocument)
END_MESSAGE_MAP()


// CPaintingDoc 构造/析构

CPaintingDoc::CPaintingDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	m_nDrawIndex = ID_DRAW_ARROW;

}

CPaintingDoc::~CPaintingDoc()
{
	int i = 0, nSize = m_arr.GetSize();
	while (i < nSize)
		delete m_arr[i++];
}

BOOL CPaintingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPaintingDoc 序列化



#ifdef SHARED_HANDLERS

// 缩略图的支持
void CPaintingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CPaintingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CPaintingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPaintingDoc 诊断

#ifdef _DEBUG
void CPaintingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaintingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPaintingDoc 命令


void CPaintingDoc::DeleteContents()
{
	// TODO: 在此添加专用代码和/或调用基类
	//memset(&m_pt)
	/*for (size_t i = 0; i < m_arr.GetSize(); i++)
	{
		m_arr[i] = NULL;
	}*/
	//memset(&m_arr, NULL, sizeof(m_arr));

	CDocument::DeleteContents();
}


void CPaintingDoc::SetTitle(LPCTSTR lpszTitle)
{
	
	CDocument::SetTitle(L"Wolson");
}
