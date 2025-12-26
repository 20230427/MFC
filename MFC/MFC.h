#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号

class CMFCApp : public CWinApp
{
public:
    CMFCApp() noexcept;

    // 重写
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

    // 实现
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()

private:
    ULONG_PTR m_gdiplusToken;
};

extern CMFCApp theApp;
