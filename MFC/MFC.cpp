#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "MFC.h"
#include "MainFrm.h"
#include "MFCDoc.h"
#include "MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMFCApp, CWinApp)
    ON_COMMAND(ID_APP_ABOUT, &CMFCApp::OnAppAbout)
    ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CMFCApp::CMFCApp() noexcept
{
    // 移除 m_bHiColorIcons 设置，因为 CWinApp 没有这个成员
    SetAppID(_T("MFC.AppID.NoVersion"));
}

CMFCApp theApp;

BOOL CMFCApp::InitInstance()
{
    // 初始化 GDI+
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    AfxEnableControlContainer();

    SetRegistryKey(_T("本地应用程序向导生成的应用程序"));
    LoadStdProfileSettings(4);

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CMFCDoc),
        RUNTIME_CLASS(CMainFrame),
        RUNTIME_CLASS(CMFCView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}

int CMFCApp::ExitInstance()
{
    // 清理 GDI+
    GdiplusShutdown(m_gdiplusToken);
    return CWinApp::ExitInstance();
}

// 关于对话框类
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg() noexcept;

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CMFCApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}
