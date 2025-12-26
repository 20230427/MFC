#pragma once

#include "DrawShape.h"
#include "LanguageManager.h"
#include <vector>
#include <memory>
#include <stack>

using namespace Gdiplus;

class CMFCView : public CView
{
protected:
	DECLARE_DYNCREATE(CMFCView)

public:
	CMFCView() noexcept;
	virtual ~CMFCView();

	CMFCDoc* GetDocument() const;

	// 重写
public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// 打印支持
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
//#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
//#endif




	// 绘图相关成员变量
private:
	std::vector<std::shared_ptr<CDrawShape>> m_shapes;
	std::shared_ptr<CDrawShape> m_pCurrentShape;

	// 撤销/重做栈 - 只保留一个定义
	std::stack<std::vector<std::shared_ptr<CDrawShape>>> m_undoStack;
	std::stack<std::vector<std::shared_ptr<CDrawShape>>> m_redoStack;

	// 当前绘图状态
	ShapeType m_currentTool;
	Color m_currentColor;
	REAL m_currentLineWidth;
	BOOL m_bDrawing;

	// 双缓冲相关
	std::unique_ptr<Bitmap> m_pBackBuffer; // 后台缓冲区
	std::unique_ptr<Graphics> m_pBackGraphics; // 后台绘图对象
	std::unique_ptr<Bitmap> m_pTempBuffer; // 临时缓冲区
	std::unique_ptr<Graphics> m_pTempGraphics; // 临时绘图对象
	CSize m_canvasSize; // 画布大小

	// 绘图相关方法
private:
	void InitializeBuffers();
	void CreateShape(ShapeType type, PointF startPoint);
	void UpdateCurrentShape(PointF endPoint);
	void FinishCurrentShape();
	void RedrawBackBuffer();
	void SaveState();
	void ClearCanvas();
	void InvalidateCanvas();

	// 打印辅助方法
private:
	BOOL PrepareBitmapForPrinting(CDC* pDC, CBitmap& bitmap, CPrintInfo* pInfo);
	void DrawBitmapToPrinter(CDC* pDC, CBitmap& bitmap, CPrintInfo* pInfo);

	// 消息处理函数
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	// 工具选择
	afx_msg void OnToolLine();
	afx_msg void OnToolRectangle();
	afx_msg void OnToolEllipse();
	afx_msg void OnToolFreehand();
	afx_msg void OnUpdateToolLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolFreehand(CCmdUI* pCmdUI);

	// 颜色选择
	afx_msg void OnColorBlack();
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnColorYellow();
	afx_msg void OnColorCyan();
	afx_msg void OnColorMagenta();
	afx_msg void OnColorCustom();
	afx_msg void OnUpdateColorBlack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorRed(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorYellow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorCyan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorMagenta(CCmdUI* pCmdUI);

	// 线宽选择
	afx_msg void OnLineWidth1();
	afx_msg void OnLineWidth2();
	afx_msg void OnLineWidth3();
	afx_msg void OnLineWidth5();
	afx_msg void OnLineWidth8();
	afx_msg void OnUpdateLineWidth1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineWidth2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineWidth3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineWidth5(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineWidth8(CCmdUI* pCmdUI);

	// 编辑操作
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnEditClearAll(); // 添加这个声明
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);

	// 语言选择
	afx_msg void OnLanguageChinese();
	afx_msg void OnLanguageEnglish();
	afx_msg void OnLanguageJapanese();
	afx_msg void OnUpdateLanguageChinese(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLanguageEnglish(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLanguageJapanese(CCmdUI* pCmdUI);

	// 打印相关
	afx_msg void OnFilePageSetup();
	afx_msg void OnFilePrintPreview();
	//afx_msg void OnFilePrint();
	afx_msg void OnFilePrintBitmap();



	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CMFCDoc* CMFCView::GetDocument() const
{
	return reinterpret_cast<CMFCDoc*>(m_pDocument);
}
#endif
