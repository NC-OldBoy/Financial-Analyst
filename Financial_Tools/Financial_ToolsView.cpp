// Financial_ToolsView.cpp : CFinancial_ToolsView 类的实现
//

#include "stdafx.h"
#include "Financial_Tools.h"

#include "Financial_ToolsDoc.h"
#include "Financial_ToolsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFinancial_ToolsView

IMPLEMENT_DYNCREATE(CFinancial_ToolsView, CView)

BEGIN_MESSAGE_MAP(CFinancial_ToolsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CFinancial_ToolsView 构造/析构

CFinancial_ToolsView::CFinancial_ToolsView()
{
	// TODO: 在此处添加构造代码

}

CFinancial_ToolsView::~CFinancial_ToolsView()
{
}

BOOL CFinancial_ToolsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFinancial_ToolsView 绘制

void CFinancial_ToolsView::OnDraw(CDC* /*pDC*/)
{
	CFinancial_ToolsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CFinancial_ToolsView 打印

BOOL CFinancial_ToolsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFinancial_ToolsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CFinancial_ToolsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CFinancial_ToolsView 诊断

#ifdef _DEBUG
void CFinancial_ToolsView::AssertValid() const
{
	CView::AssertValid();
}

void CFinancial_ToolsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFinancial_ToolsDoc* CFinancial_ToolsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFinancial_ToolsDoc)));
	return (CFinancial_ToolsDoc*)m_pDocument;
}
#endif //_DEBUG


