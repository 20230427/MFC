#include "pch.h"
#include "LanguageManager.h"
#include "Resource.h"

CLanguageManager& CLanguageManager::GetInstance()
{
    static CLanguageManager instance;
    return instance;
}

CLanguageManager::CLanguageManager()
    : m_currentLanguage(Language::Chinese)
{
    InitializeStrings();
}

void CLanguageManager::SetLanguage(Language lang)
{
    m_currentLanguage = lang;
}

CString CLanguageManager::GetString(UINT nID) const
{
    auto langIt = m_strings.find(m_currentLanguage);
    if (langIt != m_strings.end())
    {
        auto strIt = langIt->second.find(nID);
        if (strIt != langIt->second.end())
        {
            return strIt->second;
        }
    }

    // 如果当前语言没有找到，尝试使用中文作为默认
    if (m_currentLanguage != Language::Chinese)
    {
        auto chineseIt = m_strings.find(Language::Chinese);
        if (chineseIt != m_strings.end())
        {
            auto strIt = chineseIt->second.find(nID);
            if (strIt != chineseIt->second.end())
            {
                return strIt->second;
            }
        }
    }

    return _T("");
}

void CLanguageManager::InitializeStrings()
{
    // 中文字符串
    m_strings[Language::Chinese][IDS_MENU_FILE] = _T("文件(&F)");
    m_strings[Language::Chinese][IDS_MENU_EDIT] = _T("编辑(&E)");
    m_strings[Language::Chinese][IDS_MENU_TOOL] = _T("绘图工具(&T)");
    m_strings[Language::Chinese][IDS_MENU_COLOR] = _T("颜色(&C)");
    m_strings[Language::Chinese][IDS_MENU_LINEWIDTH] = _T("线宽(&W)");
    m_strings[Language::Chinese][IDS_MENU_LANGUAGE] = _T("语言(&L)");
    m_strings[Language::Chinese][IDS_MENU_HELP] = _T("帮助(&H)");
    m_strings[Language::Chinese][IDS_FILE_NEW] = _T("新建(&N)\tCtrl+N");
    m_strings[Language::Chinese][IDS_FILE_OPEN] = _T("打开(&O)...\tCtrl+O");
    m_strings[Language::Chinese][IDS_FILE_SAVE] = _T("保存(&S)\tCtrl+S");
    m_strings[Language::Chinese][IDS_FILE_SAVE_AS] = _T("另存为(&A)...");
    m_strings[Language::Chinese][IDS_FILE_EXIT] = _T("退出(&X)");
    m_strings[Language::Chinese][IDS_EDIT_UNDO] = _T("撤销(&U)\tCtrl+Z");
    m_strings[Language::Chinese][IDS_EDIT_REDO] = _T("重做(&R)\tCtrl+Y");
    m_strings[Language::Chinese][IDS_EDIT_CLEAR_ALL] = _T("清空画布(&C)");
    m_strings[Language::Chinese][IDS_TOOL_LINE] = _T("直线(&L)");
    m_strings[Language::Chinese][IDS_TOOL_RECTANGLE] = _T("矩形(&R)");
    m_strings[Language::Chinese][IDS_TOOL_ELLIPSE] = _T("椭圆(&E)");
    m_strings[Language::Chinese][IDS_TOOL_FREEHAND] = _T("自由绘制(&F)");
    m_strings[Language::Chinese][IDS_COLOR_BLACK] = _T("黑色(&B)");
    m_strings[Language::Chinese][IDS_COLOR_RED] = _T("红色(&R)");
    m_strings[Language::Chinese][IDS_COLOR_GREEN] = _T("绿色(&G)");
    m_strings[Language::Chinese][IDS_COLOR_BLUE] = _T("蓝色(&L)");
    m_strings[Language::Chinese][IDS_COLOR_YELLOW] = _T("黄色(&Y)");
    m_strings[Language::Chinese][IDS_COLOR_CYAN] = _T("青色(&C)");
    m_strings[Language::Chinese][IDS_COLOR_MAGENTA] = _T("洋红色(&M)");
    m_strings[Language::Chinese][IDS_COLOR_CUSTOM] = _T("自定义颜色(&U)...");
    m_strings[Language::Chinese][IDS_LINEWIDTH_1] = _T("1 像素");
    m_strings[Language::Chinese][IDS_LINEWIDTH_2] = _T("2 像素");
    m_strings[Language::Chinese][IDS_LINEWIDTH_3] = _T("3 像素");
    m_strings[Language::Chinese][IDS_LINEWIDTH_5] = _T("5 像素");
    m_strings[Language::Chinese][IDS_LINEWIDTH_8] = _T("8 像素");
    m_strings[Language::Chinese][IDS_LANGUAGE_CHINESE] = _T("中文(&C)");
    m_strings[Language::Chinese][IDS_LANGUAGE_ENGLISH] = _T("English(&E)");
    m_strings[Language::Chinese][IDS_LANGUAGE_JAPANESE] = _T("日本語(&J)");
    m_strings[Language::Chinese][IDS_HELP_ABOUT] = _T("关于 MFC绘图板(&A)...");
    m_strings[Language::Chinese][IDS_CLEAR_CONFIRM] = _T("确定要清空画布吗？");
    m_strings[Language::Chinese][IDS_APP_TITLE] = _T("MFC绘图板");
    m_strings[Language::Chinese][IDS_FILE_PAGE_SETUP] = _T("页面设置(&U)...");
    m_strings[Language::Chinese][IDS_FILE_PRINT_PREVIEW] = _T("打印预览(&V)");
    m_strings[Language::Chinese][IDS_FILE_PRINT] = _T("打印(&P)...\tCtrl+P");
    m_strings[Language::Chinese][IDS_FILE_PRINT_BITMAP] = _T("打印位图(&B)...");

    // 英文字符串
    m_strings[Language::English][IDS_MENU_FILE] = _T("&File");
    m_strings[Language::English][IDS_MENU_EDIT] = _T("&Edit");
    m_strings[Language::English][IDS_MENU_TOOL] = _T("&Tools");
    m_strings[Language::English][IDS_MENU_COLOR] = _T("&Color");
    m_strings[Language::English][IDS_MENU_LINEWIDTH] = _T("Line &Width");
    m_strings[Language::English][IDS_MENU_LANGUAGE] = _T("&Language");
    m_strings[Language::English][IDS_MENU_HELP] = _T("&Help");
    m_strings[Language::English][IDS_FILE_NEW] = _T("&New\tCtrl+N");
    m_strings[Language::English][IDS_FILE_OPEN] = _T("&Open...\tCtrl+O");
    m_strings[Language::English][IDS_FILE_SAVE] = _T("&Save\tCtrl+S");
    m_strings[Language::English][IDS_FILE_SAVE_AS] = _T("Save &As...");
    m_strings[Language::English][IDS_FILE_EXIT] = _T("E&xit");
    m_strings[Language::English][IDS_EDIT_UNDO] = _T("&Undo\tCtrl+Z");
    m_strings[Language::English][IDS_EDIT_REDO] = _T("&Redo\tCtrl+Y");
    m_strings[Language::English][IDS_EDIT_CLEAR_ALL] = _T("&Clear All");
    m_strings[Language::English][IDS_TOOL_LINE] = _T("&Line");
    m_strings[Language::English][IDS_TOOL_RECTANGLE] = _T("&Rectangle");
    m_strings[Language::English][IDS_TOOL_ELLIPSE] = _T("&Ellipse");
    m_strings[Language::English][IDS_TOOL_FREEHAND] = _T("&Freehand");
    m_strings[Language::English][IDS_COLOR_BLACK] = _T("&Black");
    m_strings[Language::English][IDS_COLOR_RED] = _T("&Red");
    m_strings[Language::English][IDS_COLOR_GREEN] = _T("&Green");
    m_strings[Language::English][IDS_COLOR_BLUE] = _T("B&lue");
    m_strings[Language::English][IDS_COLOR_YELLOW] = _T("&Yellow");
    m_strings[Language::English][IDS_COLOR_CYAN] = _T("&Cyan");
    m_strings[Language::English][IDS_COLOR_MAGENTA] = _T("&Magenta");
    m_strings[Language::English][IDS_COLOR_CUSTOM] = _T("C&ustom Color...");
    m_strings[Language::English][IDS_LINEWIDTH_1] = _T("1 pixel");
    m_strings[Language::English][IDS_LINEWIDTH_2] = _T("2 pixels");
    m_strings[Language::English][IDS_LINEWIDTH_3] = _T("3 pixels");
    m_strings[Language::English][IDS_LINEWIDTH_5] = _T("5 pixels");
    m_strings[Language::English][IDS_LINEWIDTH_8] = _T("8 pixels");
    m_strings[Language::English][IDS_LANGUAGE_CHINESE] = _T("&Chinese");
    m_strings[Language::English][IDS_LANGUAGE_ENGLISH] = _T("&English");
    m_strings[Language::English][IDS_LANGUAGE_JAPANESE] = _T("&Japanese");
    m_strings[Language::English][IDS_HELP_ABOUT] = _T("&About MFC Paint...");
    m_strings[Language::English][IDS_CLEAR_CONFIRM] = _T("Are you sure you want to clear the canvas?");
    m_strings[Language::English][IDS_APP_TITLE] = _T("MFC Paint");
    m_strings[Language::English][IDS_FILE_PAGE_SETUP] = _T("Page Set&up...");
    m_strings[Language::English][IDS_FILE_PRINT_PREVIEW] = _T("Print Pre&view");
    m_strings[Language::English][IDS_FILE_PRINT] = _T("&Print...\tCtrl+P");
    m_strings[Language::English][IDS_FILE_PRINT_BITMAP] = _T("Print &Bitmap...");


    // 日文字符串
    m_strings[Language::Japanese][IDS_MENU_FILE] = _T("ファイル(&F)");
    m_strings[Language::Japanese][IDS_MENU_EDIT] = _T("編集(&E)");
    m_strings[Language::Japanese][IDS_MENU_TOOL] = _T("ツール(&T)");
    m_strings[Language::Japanese][IDS_MENU_COLOR] = _T("色(&C)");
    m_strings[Language::Japanese][IDS_MENU_LINEWIDTH] = _T("線の太さ(&W)");
    m_strings[Language::Japanese][IDS_MENU_LANGUAGE] = _T("言語(&L)");
    m_strings[Language::Japanese][IDS_MENU_HELP] = _T("ヘルプ(&H)");
    m_strings[Language::Japanese][IDS_FILE_NEW] = _T("新規作成(&N)\tCtrl+N");
    m_strings[Language::Japanese][IDS_FILE_OPEN] = _T("開く(&O)...\tCtrl+O");
    m_strings[Language::Japanese][IDS_FILE_SAVE] = _T("保存(&S)\tCtrl+S");
    m_strings[Language::Japanese][IDS_FILE_SAVE_AS] = _T("名前を付けて保存(&A)...");
    m_strings[Language::Japanese][IDS_FILE_EXIT] = _T("終了(&X)");
    m_strings[Language::Japanese][IDS_EDIT_UNDO] = _T("元に戻す(&U)\tCtrl+Z");
    m_strings[Language::Japanese][IDS_EDIT_REDO] = _T("やり直し(&R)\tCtrl+Y");
    m_strings[Language::Japanese][IDS_EDIT_CLEAR_ALL] = _T("すべてクリア(&C)");
    m_strings[Language::Japanese][IDS_TOOL_LINE] = _T("直線(&L)");
    m_strings[Language::Japanese][IDS_TOOL_RECTANGLE] = _T("四角形(&R)");
    m_strings[Language::Japanese][IDS_TOOL_ELLIPSE] = _T("楕円(&E)");
    m_strings[Language::Japanese][IDS_TOOL_FREEHAND] = _T("フリーハンド(&F)");
    m_strings[Language::Japanese][IDS_COLOR_BLACK] = _T("黒(&B)");
    m_strings[Language::Japanese][IDS_COLOR_RED] = _T("赤(&R)");
    m_strings[Language::Japanese][IDS_COLOR_GREEN] = _T("緑(&G)");
    m_strings[Language::Japanese][IDS_COLOR_BLUE] = _T("青(&L)");
    m_strings[Language::Japanese][IDS_COLOR_YELLOW] = _T("黄色(&Y)");
    m_strings[Language::Japanese][IDS_COLOR_CYAN] = _T("シアン(&C)");
    m_strings[Language::Japanese][IDS_COLOR_MAGENTA] = _T("マゼンタ(&M)");
    m_strings[Language::Japanese][IDS_COLOR_CUSTOM] = _T("カスタム色(&U)...");
    m_strings[Language::Japanese][IDS_LINEWIDTH_1] = _T("1 ピクセル");
    m_strings[Language::Japanese][IDS_LINEWIDTH_2] = _T("2 ピクセル");
    m_strings[Language::Japanese][IDS_LINEWIDTH_3] = _T("3 ピクセル");
    m_strings[Language::Japanese][IDS_LINEWIDTH_5] = _T("5 ピクセル");
    m_strings[Language::Japanese][IDS_LINEWIDTH_8] = _T("8 ピクセル");
    m_strings[Language::Japanese][IDS_LANGUAGE_CHINESE] = _T("中国語(&C)");
    m_strings[Language::Japanese][IDS_LANGUAGE_ENGLISH] = _T("英語(&E)");
    m_strings[Language::Japanese][IDS_LANGUAGE_JAPANESE] = _T("日本語(&J)");
    m_strings[Language::Japanese][IDS_HELP_ABOUT] = _T("MFCペイントについて(&A)...");
    m_strings[Language::Japanese][IDS_CLEAR_CONFIRM] = _T("キャンバスをクリアしてもよろしいですか？");
    m_strings[Language::Japanese][IDS_APP_TITLE] = _T("MFCペイント");
    m_strings[Language::Japanese][IDS_FILE_PAGE_SETUP] = _T("ページ設定(&U)...");
    m_strings[Language::Japanese][IDS_FILE_PRINT_PREVIEW] = _T("印刷プレビュー(&V)");
    m_strings[Language::Japanese][IDS_FILE_PRINT] = _T("印刷(&P)...\tCtrl+P");
    m_strings[Language::Japanese][IDS_FILE_PRINT_BITMAP] = _T("ビットマップ印刷(&B)...");
}

void CLanguageManager::UpdateMenuText(CMenu* pMenu)
{
    if (!pMenu) return;

    // 更新主菜单项
    struct MenuInfo {
        int position;
        UINT stringId;
    };

    MenuInfo mainMenus[] = {
        {0, IDS_MENU_FILE},
        {1, IDS_MENU_EDIT},
        {2, IDS_MENU_TOOL},
        {3, IDS_MENU_COLOR},
        {4, IDS_MENU_LINEWIDTH},
        {5, IDS_MENU_LANGUAGE},
        {6, IDS_MENU_HELP}
    };

    for (const auto& menu : mainMenus)
    {
        CString text = GetString(menu.stringId);
        if (!text.IsEmpty())
        {
            pMenu->ModifyMenu(menu.position, MF_BYPOSITION | MF_STRING,
                pMenu->GetMenuItemID(menu.position), text);
        }
    }

    // 更新子菜单项
    struct SubMenuInfo {
        UINT commandId;
        UINT stringId;
    };

    SubMenuInfo subMenus[] = {
        {ID_FILE_NEW, IDS_FILE_NEW},
        {ID_FILE_OPEN, IDS_FILE_OPEN},
        {ID_FILE_SAVE, IDS_FILE_SAVE},
        {ID_FILE_SAVE_AS, IDS_FILE_SAVE_AS},
        {ID_APP_EXIT, IDS_FILE_EXIT},
        {ID_EDIT_UNDO, IDS_EDIT_UNDO},
        {ID_EDIT_REDO, IDS_EDIT_REDO},
        {ID_EDIT_CLEAR_ALL, IDS_EDIT_CLEAR_ALL},
        {ID_TOOL_LINE, IDS_TOOL_LINE},
        {ID_TOOL_RECTANGLE, IDS_TOOL_RECTANGLE},
        {ID_TOOL_ELLIPSE, IDS_TOOL_ELLIPSE},
        {ID_TOOL_FREEHAND, IDS_TOOL_FREEHAND},
        {ID_COLOR_BLACK, IDS_COLOR_BLACK},
        {ID_COLOR_RED, IDS_COLOR_RED},
        {ID_COLOR_GREEN, IDS_COLOR_GREEN},
        {ID_COLOR_BLUE, IDS_COLOR_BLUE},
        {ID_COLOR_YELLOW, IDS_COLOR_YELLOW},
        {ID_COLOR_CYAN, IDS_COLOR_CYAN},
        {ID_COLOR_MAGENTA, IDS_COLOR_MAGENTA},
        {ID_COLOR_CUSTOM, IDS_COLOR_CUSTOM},
        {ID_LINE_WIDTH_1, IDS_LINEWIDTH_1},
        {ID_LINE_WIDTH_2, IDS_LINEWIDTH_2},
        {ID_LINE_WIDTH_3, IDS_LINEWIDTH_3},
        {ID_LINE_WIDTH_5, IDS_LINEWIDTH_5},
        {ID_LINE_WIDTH_8, IDS_LINEWIDTH_8},
        {ID_LANGUAGE_CHINESE, IDS_LANGUAGE_CHINESE},
        {ID_LANGUAGE_ENGLISH, IDS_LANGUAGE_ENGLISH},
        {ID_LANGUAGE_JAPANESE, IDS_LANGUAGE_JAPANESE},
        {ID_APP_ABOUT, IDS_HELP_ABOUT},
        { ID_FILE_PAGE_SETUP, IDS_FILE_PAGE_SETUP },
        {ID_FILE_PRINT_PREVIEW, IDS_FILE_PRINT_PREVIEW},
        {ID_FILE_PRINT, IDS_FILE_PRINT},
        {ID_FILE_PRINT_BITMAP, IDS_FILE_PRINT_BITMAP},
    };

    for (const auto& subMenu : subMenus)
    {
        CString text = GetString(subMenu.stringId);
        if (!text.IsEmpty())
        {
            pMenu->ModifyMenu(subMenu.commandId, MF_BYCOMMAND | MF_STRING,
                subMenu.commandId, text);
        }
    }
}
