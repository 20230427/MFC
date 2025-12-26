#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "MFC.h"
#endif

#include "MFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCDoc, CDocument)
END_MESSAGE_MAP()

CMFCDoc::CMFCDoc() noexcept
{
}

CMFCDoc::~CMFCDoc()
{
}

BOOL CMFCDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    return TRUE;
}

void CMFCDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: 在此添加存储代码
    }
    else
    {
        // TODO: 在此添加加载代码
    }
}

#ifdef SHARED_HANDLERS

void CMFCDoc::InitializeSearchContent()
{
    CString strSearchContent;
    SetSearchContent(strSearchContent);
}

void CMFCDoc::SetSearchContent(const CString& value)
{
    if (value.IsEmpty())
    {
        RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
    }
    else
    {
        CMFCFilterChunkValueImpl* pChunk = nullptr;
        ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
        if (pChunk != nullptr)
        {
            pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
            SetChunkValue(pChunk);
        }
    }
}

#endif

#ifdef _DEBUG
void CMFCDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CMFCDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif
