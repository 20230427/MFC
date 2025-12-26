#pragma once

class CMainFrame : public CFrameWnd
{
protected:
    DECLARE_DYNCREATE(CMainFrame)

public:
    CMainFrame() noexcept;

    // 属性
public:

    // 操作
public:

    // 重写
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    // 实现
public:
    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CStatusBar m_wndStatusBar;
    CToolBar m_wndToolBar;

    // 生成的消息映射函数
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()
};
