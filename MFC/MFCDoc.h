#pragma once

class CMFCDoc : public CDocument
{
protected:
    DECLARE_DYNCREATE(CMFCDoc)

public:
    CMFCDoc() noexcept;
    virtual ~CMFCDoc();

    // 重写
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent();
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif

    // 实现
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    // 生成的消息映射函数
protected:
    DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
    // 为搜索处理程序设置搜索内容的 Helper 函数
    void SetSearchContent(const CString& value);
#endif
};
