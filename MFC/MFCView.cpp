#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "MFC.h"
#endif

#include "MFCDoc.h"
#include "MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMFCView, CView)

BEGIN_MESSAGE_MAP(CMFCView, CView)
    // 鼠标消息
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()

    // 工具选择
    ON_COMMAND(ID_TOOL_LINE, &CMFCView::OnToolLine)
    ON_COMMAND(ID_TOOL_RECTANGLE, &CMFCView::OnToolRectangle)
    ON_COMMAND(ID_TOOL_ELLIPSE, &CMFCView::OnToolEllipse)
    ON_COMMAND(ID_TOOL_FREEHAND, &CMFCView::OnToolFreehand)
    ON_UPDATE_COMMAND_UI(ID_TOOL_LINE, &CMFCView::OnUpdateToolLine)
    ON_UPDATE_COMMAND_UI(ID_TOOL_RECTANGLE, &CMFCView::OnUpdateToolRectangle)
    ON_UPDATE_COMMAND_UI(ID_TOOL_ELLIPSE, &CMFCView::OnUpdateToolEllipse)
    ON_UPDATE_COMMAND_UI(ID_TOOL_FREEHAND, &CMFCView::OnUpdateToolFreehand)

    // 颜色选择
    ON_COMMAND(ID_COLOR_BLACK, &CMFCView::OnColorBlack)
    ON_COMMAND(ID_COLOR_RED, &CMFCView::OnColorRed)
    ON_COMMAND(ID_COLOR_GREEN, &CMFCView::OnColorGreen)
    ON_COMMAND(ID_COLOR_BLUE, &CMFCView::OnColorBlue)
    ON_COMMAND(ID_COLOR_YELLOW, &CMFCView::OnColorYellow)
    ON_COMMAND(ID_COLOR_CYAN, &CMFCView::OnColorCyan)
    ON_COMMAND(ID_COLOR_MAGENTA, &CMFCView::OnColorMagenta)
    ON_COMMAND(ID_COLOR_CUSTOM, &CMFCView::OnColorCustom)
    ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CMFCView::OnUpdateColorBlack)
    ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CMFCView::OnUpdateColorRed)
    ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CMFCView::OnUpdateColorGreen)
    ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CMFCView::OnUpdateColorBlue)
    ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, &CMFCView::OnUpdateColorYellow)
    ON_UPDATE_COMMAND_UI(ID_COLOR_CYAN, &CMFCView::OnUpdateColorCyan)
    ON_UPDATE_COMMAND_UI(ID_COLOR_MAGENTA, &CMFCView::OnUpdateColorMagenta)

    // 线宽选择
    ON_COMMAND(ID_LINE_WIDTH_1, &CMFCView::OnLineWidth1)
    ON_COMMAND(ID_LINE_WIDTH_2, &CMFCView::OnLineWidth2)
    ON_COMMAND(ID_LINE_WIDTH_3, &CMFCView::OnLineWidth3)
    ON_COMMAND(ID_LINE_WIDTH_5, &CMFCView::OnLineWidth5)
    ON_COMMAND(ID_LINE_WIDTH_8, &CMFCView::OnLineWidth8)
    ON_UPDATE_COMMAND_UI(ID_LINE_WIDTH_1, &CMFCView::OnUpdateLineWidth1)
    ON_UPDATE_COMMAND_UI(ID_LINE_WIDTH_2, &CMFCView::OnUpdateLineWidth2)
    ON_UPDATE_COMMAND_UI(ID_LINE_WIDTH_3, &CMFCView::OnUpdateLineWidth3)
    ON_UPDATE_COMMAND_UI(ID_LINE_WIDTH_5, &CMFCView::OnUpdateLineWidth5)
    ON_UPDATE_COMMAND_UI(ID_LINE_WIDTH_8, &CMFCView::OnUpdateLineWidth8)

    // 编辑操作
    ON_COMMAND(ID_EDIT_UNDO, &CMFCView::OnEditUndo)
    ON_COMMAND(ID_EDIT_REDO, &CMFCView::OnEditRedo)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, &CMFCView::OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, &CMFCView::OnUpdateEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CMFCView::OnUpdateEditUndo)
    ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CMFCView::OnUpdateEditRedo)

    // 语言选择
    ON_COMMAND(ID_LANGUAGE_CHINESE, &CMFCView::OnLanguageChinese)
    ON_COMMAND(ID_LANGUAGE_ENGLISH, &CMFCView::OnLanguageEnglish)
    ON_COMMAND(ID_LANGUAGE_JAPANESE, &CMFCView::OnLanguageJapanese)
    ON_UPDATE_COMMAND_UI(ID_LANGUAGE_CHINESE, &CMFCView::OnUpdateLanguageChinese)
    ON_UPDATE_COMMAND_UI(ID_LANGUAGE_ENGLISH, &CMFCView::OnUpdateLanguageEnglish)
    ON_UPDATE_COMMAND_UI(ID_LANGUAGE_JAPANESE, &CMFCView::OnUpdateLanguageJapanese)

    // 打印相关
    ON_COMMAND(ID_FILE_PAGE_SETUP, &CMFCView::OnFilePageSetup)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCView::OnFilePrintPreview)
    //ON_COMMAND(ID_FILE_PRINT, &CMFCView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_BITMAP, &CMFCView::OnFilePrintBitmap)
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)

    // 标准打印命令
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

END_MESSAGE_MAP()

CMFCView::CMFCView() noexcept
    : m_currentTool(SHAPE_LINE)
    , m_currentColor(Color::Black)
    , m_currentLineWidth(1.0f)
    , m_bDrawing(FALSE)
    , m_pCurrentShape(nullptr)
    , m_canvasSize(0, 0)
{
}

CMFCView::~CMFCView()
{
}

BOOL CMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CView::PreCreateWindow(cs);
}

void CMFCView::InitializeBuffers()
{
    CRect rect;
    GetClientRect(&rect);

    if (rect.Width() > 0 && rect.Height() > 0)
    {
        m_canvasSize = CSize(rect.Width(), rect.Height());

        // 创建后台缓冲区
        m_pBackBuffer = std::make_unique<Bitmap>(rect.Width(), rect.Height());
        m_pBackGraphics = std::make_unique<Graphics>(m_pBackBuffer.get());
        m_pBackGraphics->SetSmoothingMode(SmoothingModeAntiAlias);
        m_pBackGraphics->SetTextRenderingHint(TextRenderingHintAntiAlias);
        m_pBackGraphics->Clear(Color::White);

        // 创建临时缓冲区
        m_pTempBuffer = std::make_unique<Bitmap>(rect.Width(), rect.Height());
        m_pTempGraphics = std::make_unique<Graphics>(m_pTempBuffer.get());
        m_pTempGraphics->SetSmoothingMode(SmoothingModeAntiAlias);
        m_pTempGraphics->SetTextRenderingHint(TextRenderingHintAntiAlias);

        // 重绘后台缓冲区
        RedrawBackBuffer();
    }
}

void CMFCView::OnDraw(CDC* pDC)
{
    CMFCDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (!m_pBackBuffer || !m_pTempBuffer)
    {
        InitializeBuffers();
        return;
    }

    Graphics graphics(pDC->GetSafeHdc());
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    if (m_bDrawing && m_pCurrentShape)
    {
        // 绘制时：先复制后台缓冲区到临时缓冲区，然后绘制当前形状
        m_pTempGraphics->Clear(Color::White);
        m_pTempGraphics->DrawImage(m_pBackBuffer.get(), 0, 0);
        m_pCurrentShape->Draw(m_pTempGraphics.get());

        // 将临时缓冲区绘制到屏幕
        graphics.DrawImage(m_pTempBuffer.get(), 0, 0);
    }
    else
    {
        // 非绘制时：直接绘制后台缓冲区
        graphics.DrawImage(m_pBackBuffer.get(), 0, 0);
    }
}

void CMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
    SetCapture();
    m_bDrawing = TRUE;

    PointF startPoint((REAL)point.x, (REAL)point.y);
    CreateShape(m_currentTool, startPoint);

    SaveState();

    CView::OnLButtonDown(nFlags, point);
}

void CMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bDrawing)
    {
        ReleaseCapture();
        m_bDrawing = FALSE;

        FinishCurrentShape();
        RedrawBackBuffer();
        InvalidateCanvas();
    }

    CView::OnLButtonUp(nFlags, point);
}

void CMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bDrawing && m_pCurrentShape)
    {
        PointF currentPoint((REAL)point.x, (REAL)point.y);
        UpdateCurrentShape(currentPoint);

        // 只刷新当前绘制区域，减少闪烁
        InvalidateCanvas();
    }

    CView::OnMouseMove(nFlags, point);
}

void CMFCView::CreateShape(ShapeType type, PointF startPoint)
{
    switch (type)
    {
    case SHAPE_LINE:
        m_pCurrentShape = std::make_shared<CLineShape>();
        break;
    case SHAPE_RECTANGLE:
        m_pCurrentShape = std::make_shared<CRectangleShape>();
        break;
    case SHAPE_ELLIPSE:
        m_pCurrentShape = std::make_shared<CEllipseShape>();
        break;
    case SHAPE_FREEHAND:
        m_pCurrentShape = std::make_shared<CFreehandShape>();
        break;
    }

    if (m_pCurrentShape)
    {
        m_pCurrentShape->m_color = m_currentColor;
        m_pCurrentShape->m_lineWidth = m_currentLineWidth;
        m_pCurrentShape->m_startPoint = startPoint;
        m_pCurrentShape->m_endPoint = startPoint;

        if (type == SHAPE_FREEHAND)
        {
            auto freehandShape = std::static_pointer_cast<CFreehandShape>(m_pCurrentShape);
            freehandShape->m_points.push_back(startPoint);
        }
    }
}

void CMFCView::UpdateCurrentShape(PointF endPoint)
{
    if (!m_pCurrentShape) return;

    if (m_pCurrentShape->m_type == SHAPE_FREEHAND)
    {
        auto freehandShape = std::static_pointer_cast<CFreehandShape>(m_pCurrentShape);
        freehandShape->m_points.push_back(endPoint);
    }
    else
    {
        m_pCurrentShape->m_endPoint = endPoint;
    }
}

void CMFCView::FinishCurrentShape()
{
    if (m_pCurrentShape)
    {
        bool isValid = false;

        if (m_pCurrentShape->m_type == SHAPE_FREEHAND)
        {
            auto freehandShape = std::static_pointer_cast<CFreehandShape>(m_pCurrentShape);
            isValid = freehandShape->m_points.size() > 1;
        }
        else
        {
            isValid = (abs(m_pCurrentShape->m_startPoint.X - m_pCurrentShape->m_endPoint.X) > 1 ||
                abs(m_pCurrentShape->m_startPoint.Y - m_pCurrentShape->m_endPoint.Y) > 1);
        }

        if (isValid)
        {
            m_shapes.push_back(m_pCurrentShape);

            // 将完成的形状绘制到后台缓冲区
            if (m_pBackGraphics)
            {
                m_pCurrentShape->Draw(m_pBackGraphics.get());
            }

            // 清空重做栈
            while (!m_redoStack.empty())
            {
                m_redoStack.pop();
            }
        }

        m_pCurrentShape = nullptr;
    }
}

void CMFCView::RedrawBackBuffer()
{
    if (!m_pBackGraphics) return;

    // 清空后台缓冲区
    m_pBackGraphics->Clear(Color::White);

    // 重绘所有形状到后台缓冲区
    for (const auto& shape : m_shapes)
    {
        if (shape)
        {
            shape->Draw(m_pBackGraphics.get());
        }
    }
}

void CMFCView::SaveState()
{
    std::vector<std::shared_ptr<CDrawShape>> currentState;
    for (const auto& shape : m_shapes)
    {
        if (shape)
        {
            currentState.push_back(shape->Clone());
        }
    }
    m_undoStack.push(currentState);

    // 限制撤销栈大小
    if (m_undoStack.size() > 50)
    {
        std::stack<std::vector<std::shared_ptr<CDrawShape>>> tempStack;
        for (int i = 0; i < 49; i++)
        {
            tempStack.push(m_undoStack.top());
            m_undoStack.pop();
        }

        while (!m_undoStack.empty())
        {
            m_undoStack.pop();
        }

        while (!tempStack.empty())
        {
            m_undoStack.push(tempStack.top());
            tempStack.pop();
        }
    }
}

void CMFCView::ClearCanvas()
{
    SaveState();
    m_shapes.clear();
    RedrawBackBuffer();
    InvalidateCanvas();
}

void CMFCView::InvalidateCanvas()
{
    // 使用无效化区域而不是整个窗口，减少重绘
    Invalidate(FALSE);  // FALSE表示不擦除背景
}

void CMFCView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    if (cx > 0 && cy > 0)
    {
        InitializeBuffers();
    }
}

BOOL CMFCView::OnEraseBkgnd(CDC* pDC)
{
    // 返回TRUE防止系统擦除背景，避免闪烁
    return TRUE;
}

// 工具选择消息处理函数
void CMFCView::OnToolLine()
{
    m_currentTool = SHAPE_LINE;
}

void CMFCView::OnToolRectangle()
{
    m_currentTool = SHAPE_RECTANGLE;
}

void CMFCView::OnToolEllipse()
{
    m_currentTool = SHAPE_ELLIPSE;
}

void CMFCView::OnToolFreehand()
{
    m_currentTool = SHAPE_FREEHAND;
}

// 工具选择更新UI
void CMFCView::OnUpdateToolLine(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentTool == SHAPE_LINE);
}

void CMFCView::OnUpdateToolRectangle(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentTool == SHAPE_RECTANGLE);
}

void CMFCView::OnUpdateToolEllipse(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentTool == SHAPE_ELLIPSE);
}

void CMFCView::OnUpdateToolFreehand(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentTool == SHAPE_FREEHAND);
}

// 颜色选择消息处理函数
void CMFCView::OnColorBlack()
{
    m_currentColor = Color::Black;
}

void CMFCView::OnColorRed()
{
    m_currentColor = Color::Red;
}

void CMFCView::OnColorGreen()
{
    m_currentColor = Color::Green;
}

void CMFCView::OnColorBlue()
{
    m_currentColor = Color::Blue;
}

void CMFCView::OnColorYellow()
{
    m_currentColor = Color::Yellow;
}

void CMFCView::OnColorCyan()
{
    m_currentColor = Color::Cyan;
}

void CMFCView::OnColorMagenta()
{
    m_currentColor = Color::Magenta;
}

void CMFCView::OnColorCustom()
{
    CColorDialog dlg;
    if (dlg.DoModal() == IDOK)
    {
        COLORREF color = dlg.GetColor();
        m_currentColor = Color(GetRValue(color), GetGValue(color), GetBValue(color));
    }
}

// 颜色选择更新UI
void CMFCView::OnUpdateColorBlack(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentColor.GetValue() == Color::Black);
}

void CMFCView::OnUpdateColorRed(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentColor.GetValue() == Color::Red);
}

void CMFCView::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentColor.GetValue() == Color::Green);
}

void CMFCView::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentColor.GetValue() == Color::Blue);
}

void CMFCView::OnUpdateColorYellow(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentColor.GetValue() == Color::Yellow);
}

void CMFCView::OnUpdateColorCyan(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentColor.GetValue() == Color::Cyan);
}

void CMFCView::OnUpdateColorMagenta(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentColor.GetValue() == Color::Magenta);
}

// 线宽选择消息处理函数
void CMFCView::OnLineWidth1()
{
    m_currentLineWidth = 1.0f;
}

void CMFCView::OnLineWidth2()
{
    m_currentLineWidth = 2.0f;
}

void CMFCView::OnLineWidth3()
{
    m_currentLineWidth = 3.0f;
}

void CMFCView::OnLineWidth5()
{
    m_currentLineWidth = 5.0f;
}

void CMFCView::OnLineWidth8()
{
    m_currentLineWidth = 8.0f;
}

// 线宽选择更新UI
void CMFCView::OnUpdateLineWidth1(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentLineWidth == 1.0f);
}

void CMFCView::OnUpdateLineWidth2(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentLineWidth == 2.0f);
}

void CMFCView::OnUpdateLineWidth3(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentLineWidth == 3.0f);
}

void CMFCView::OnUpdateLineWidth5(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentLineWidth == 5.0f);
}

void CMFCView::OnUpdateLineWidth8(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_currentLineWidth == 8.0f);
}

// 编辑操作消息处理函数
void CMFCView::OnEditUndo()
{
    if (!m_undoStack.empty())
    {
        // 保存当前状态到重做栈
        std::vector<std::shared_ptr<CDrawShape>> currentState;
        for (const auto& shape : m_shapes)
        {
            if (shape)
            {
                currentState.push_back(shape->Clone());
            }
        }
        m_redoStack.push(currentState);

        // 恢复上一个状态
        m_shapes = m_undoStack.top();
        m_undoStack.pop();

        RedrawBackBuffer();
        InvalidateCanvas();
    }
}

void CMFCView::OnEditRedo()
{
    if (!m_redoStack.empty())
    {
        // 保存当前状态到撤销栈
        std::vector<std::shared_ptr<CDrawShape>> currentState;
        for (const auto& shape : m_shapes)
        {
            if (shape)
            {
                currentState.push_back(shape->Clone());
            }
        }
        m_undoStack.push(currentState);

        // 恢复重做状态
        m_shapes = m_redoStack.top();
        m_redoStack.pop();

        RedrawBackBuffer();
        InvalidateCanvas();
    }
}


// 编辑操作更新UI
void CMFCView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_undoStack.empty());
}

void CMFCView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_redoStack.empty());
}

// 清空画布功能
void CMFCView::OnEditClearAll()
{
    CString confirmMsg = CLanguageManager::GetInstance().GetString(IDS_CLEAR_CONFIRM);
    if (confirmMsg.IsEmpty())
        confirmMsg = _T("确定要清空画布吗？");

    if (AfxMessageBox(confirmMsg, MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
        // 保存当前状态到撤销栈
        SaveState();

        // 清空所有形状
        m_shapes.clear();

        // 清空重做栈
        while (!m_redoStack.empty()) {
            m_redoStack.pop();
        }

        // 重绘
        RedrawBackBuffer();
        Invalidate();
        GetDocument()->SetModifiedFlag();
    }
}

void CMFCView::OnUpdateEditClearAll(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_shapes.empty());
}

//#ifdef _DEBUG

void CMFCView::AssertValid() const
{
    CView::AssertValid();
}

void CMFCView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CMFCDoc* CMFCView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDoc)));
    return (CMFCDoc*)m_pDocument;
}



// 在文件末尾添加语言选择的实现
void CMFCView::OnLanguageChinese()
{
    CLanguageManager::GetInstance().SetLanguage(Language::Chinese);

    // 更新菜单文本
    CFrameWnd* pFrame = GetParentFrame();
    if (pFrame)
    {
        CMenu* pMenu = pFrame->GetMenu();
        if (pMenu)
        {
            CLanguageManager::GetInstance().UpdateMenuText(pMenu);
            pFrame->DrawMenuBar();
        }
    }

    // 更新窗口标题
    CString title = CLanguageManager::GetInstance().GetString(IDS_APP_TITLE);
    if (!title.IsEmpty())
    {
        GetParentFrame()->SetWindowText(title);
    }
}

void CMFCView::OnLanguageEnglish()
{
    CLanguageManager::GetInstance().SetLanguage(Language::English);

    // 更新菜单文本
    CFrameWnd* pFrame = GetParentFrame();
    if (pFrame)
    {
        CMenu* pMenu = pFrame->GetMenu();
        if (pMenu)
        {
            CLanguageManager::GetInstance().UpdateMenuText(pMenu);
            pFrame->DrawMenuBar();
        }
    }

    // 更新窗口标题
    CString title = CLanguageManager::GetInstance().GetString(IDS_APP_TITLE);
    if (!title.IsEmpty())
    {
        GetParentFrame()->SetWindowText(title);
    }
}

void CMFCView::OnLanguageJapanese()
{
    CLanguageManager::GetInstance().SetLanguage(Language::Japanese);

    // 更新菜单文本
    CFrameWnd* pFrame = GetParentFrame();
    if (pFrame)
    {
        CMenu* pMenu = pFrame->GetMenu();
        if (pMenu)
        {
            CLanguageManager::GetInstance().UpdateMenuText(pMenu);
            pFrame->DrawMenuBar();
        }
    }

    // 更新窗口标题
    CString title = CLanguageManager::GetInstance().GetString(IDS_APP_TITLE);
    if (!title.IsEmpty())
    {
        GetParentFrame()->SetWindowText(title);
    }
}

void CMFCView::OnUpdateLanguageChinese(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(CLanguageManager::GetInstance().GetCurrentLanguage() == Language::Chinese);
}

void CMFCView::OnUpdateLanguageEnglish(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(CLanguageManager::GetInstance().GetCurrentLanguage() == Language::English);
}

void CMFCView::OnUpdateLanguageJapanese(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(CLanguageManager::GetInstance().GetCurrentLanguage() == Language::Japanese);
}
//#endif

// 在 MFCView.cpp 中添加实现函数：

void CMFCView::OnFilePageSetup()
{
    // 创建页面设置对话框
    CPageSetupDialog dlg(PSD_MARGINS | PSD_INHUNDREDTHSOFMILLIMETERS |
        PSD_ENABLEPAGEPAINTHOOK, this);

    // 设置默认页边距（单位：0.01毫米）
    dlg.m_psd.rtMargin.left = 2500;   // 25毫米
    dlg.m_psd.rtMargin.right = 2500;  // 25毫米
    dlg.m_psd.rtMargin.top = 2500;    // 25毫米
    dlg.m_psd.rtMargin.bottom = 2500; // 25毫米

    if (dlg.DoModal() == IDOK)
    {
        // 可以保存页面设置到文档或应用程序设置中
        // 这里只是示例，实际应用中可能需要保存设置
        AfxMessageBox(_T("页面设置已更新"), MB_OK | MB_ICONINFORMATION);
    }
}

void CMFCView::OnFilePrintPreview()
{
    // 使用 MFC 的标准打印预览
    CView::OnFilePrintPreview();
}


// 在类定义外部添加这些函数：重写标准打印函数

BOOL CMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // 默认打印设置
    pInfo->SetMaxPage(1); // 只有一页
    return DoPreparePrinting(pInfo);
}

void CMFCView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // 开始打印前的初始化
    CView::OnBeginPrinting(pDC, pInfo);
}

void CMFCView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // 打印当前视图内容
    CRect rect = pInfo->m_rectDraw;

    // 保存原始映射模式
    int nOldMapMode = pDC->SetMapMode(MM_ANISOTROPIC);

    // 计算缩放比例以适应页面
    CSize sizeDoc = m_canvasSize;
    CSize sizePage(rect.Width(), rect.Height());

    // 保持纵横比
    double scaleX = (double)sizePage.cx / sizeDoc.cx;
    double scaleY = (double)sizePage.cy / sizeDoc.cy;
    double scale = min(scaleX, scaleY) * 0.9; // 留10%边距

    // 设置映射
    pDC->SetWindowExt(sizeDoc);
    pDC->SetViewportExt((int)(sizeDoc.cx * scale), (int)(sizeDoc.cy * scale));

    // 居中显示
    int xOffset = (sizePage.cx - (int)(sizeDoc.cx * scale)) / 2;
    int yOffset = (sizePage.cy - (int)(sizeDoc.cy * scale)) / 2;
    pDC->SetViewportOrg(rect.left + xOffset, rect.top + yOffset);

    // 绘制内容
    OnDraw(pDC);

    // 恢复映射模式
    pDC->SetMapMode(nOldMapMode);

    // 添加页眉和页脚
    CString strHeader = _T("MFC绘图板 - 打印输出");
    CString strFooter;
    strFooter.Format(_T("第 %d 页"), pInfo->m_nCurPage);

    pDC->SetTextAlign(TA_CENTER);
    pDC->TextOut(rect.Width() / 2, rect.top - 50, strHeader);
    pDC->TextOut(rect.Width() / 2, rect.bottom + 30, strFooter);
}

void CMFCView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // 清理打印资源
    CView::OnEndPrinting(pDC, pInfo);
}

//实现打印位图功能
void CMFCView::OnFilePrintBitmap()
{
    if (!m_pBackBuffer)
    {
        AfxMessageBox(_T("没有可打印的内容"), MB_OK | MB_ICONWARNING);
        return;
    }

    // 创建打印对话框
    CPrintDialog dlg(FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES |
        PD_NOPAGENUMS | PD_HIDEPRINTTOFILE | PD_NOSELECTION);

    if (dlg.DoModal() == IDOK)
    {
        CDC dcPrint;
        dcPrint.Attach(dlg.GetPrinterDC());

        // 开始文档
        DOCINFO di;
        memset(&di, 0, sizeof(DOCINFO));
        di.cbSize = sizeof(DOCINFO);
        di.lpszDocName = _T("MFC绘图板位图打印");

        if (dcPrint.StartDoc(&di) > 0)
        {
            // 开始页面
            if (dcPrint.StartPage() > 0)
            {
                // 准备位图用于打印
                CBitmap bitmap;
                PrepareBitmapForPrinting(&dcPrint, bitmap, NULL);

                // 绘制位图到打印机
                DrawBitmapToPrinter(&dcPrint, bitmap, NULL);

                dcPrint.EndPage();
            }
            dcPrint.EndDoc();
        }

        dcPrint.DeleteDC();
    }
}

BOOL CMFCView::PrepareBitmapForPrinting(CDC* pDC, CBitmap& bitmap, CPrintInfo* pInfo)
{
    if (!m_pBackBuffer)
        return FALSE;

    // 获取位图信息
    BitmapData bmpData;
    Rect rect(0, 0, m_pBackBuffer->GetWidth(), m_pBackBuffer->GetHeight());

    // 锁定位图数据
    if (m_pBackBuffer->LockBits(&rect, ImageLockModeRead,
        PixelFormat32bppARGB, &bmpData) != Ok)
    {
        return FALSE;
    }

    // 创建兼容位图
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);

    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bmpData.Width;
    bmi.bmiHeader.biHeight = bmpData.Height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* pBits = NULL;
    HBITMAP hBitmap = CreateDIBSection(memDC.GetSafeHdc(), &bmi,
        DIB_RGB_COLORS, &pBits, NULL, 0);

    if (hBitmap)
    {
        // 复制像素数据
        BYTE* pSrc = (BYTE*)bmpData.Scan0;
        BYTE* pDst = (BYTE*)pBits;

        for (UINT y = 0; y < bmpData.Height; y++)
        {
            for (UINT x = 0; x < bmpData.Width; x++)
            {
                // 注意：GDI+ 是 BGRA，DIB 是 RGB
                pDst[2] = pSrc[0]; // R
                pDst[1] = pSrc[1]; // G
                pDst[0] = pSrc[2]; // B
                pDst += 3;
                pSrc += 4;
            }
            pDst += bmpData.Width % 4; // DWORD对齐
        }

        bitmap.Attach(hBitmap);
    }

    // 解锁位图
    m_pBackBuffer->UnlockBits(&bmpData);

    return (hBitmap != NULL);
}

void CMFCView::DrawBitmapToPrinter(CDC* pDC, CBitmap& bitmap, CPrintInfo* pInfo)
{
    if (bitmap.m_hObject == NULL)
        return;

    // 获取位图尺寸
    BITMAP bm;
    bitmap.GetBitmap(&bm);

    // 计算打印区域
    CRect rectPrint;
    if (pInfo)
    {
        rectPrint = pInfo->m_rectDraw;
    }
    else
    {
        // 如果没有打印信息，使用默认设置
        int nHorzRes = pDC->GetDeviceCaps(HORZRES);
        int nVertRes = pDC->GetDeviceCaps(VERTRES);
        rectPrint.SetRect(0, 0, nHorzRes, nVertRes);
    }

    // 保持纵横比
    double aspectRatio = (double)bm.bmWidth / bm.bmHeight;
    int destWidth = rectPrint.Width();
    int destHeight = (int)(destWidth / aspectRatio);

    if (destHeight > rectPrint.Height())
    {
        destHeight = rectPrint.Height();
        destWidth = (int)(destHeight * aspectRatio);
    }

    // 居中显示
    int x = rectPrint.left + (rectPrint.Width() - destWidth) / 2;
    int y = rectPrint.top + (rectPrint.Height() - destHeight) / 2;

    // 创建内存DC并选择位图
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

    // 使用 StretchBlt 进行高质量缩放
    pDC->SetStretchBltMode(HALFTONE);
    pDC->StretchBlt(x, y, destWidth, destHeight,
        &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    // 清理
    memDC.SelectObject(pOldBitmap);
}

