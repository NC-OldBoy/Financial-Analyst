// Financial_ToolsView.cpp : CFinancial_ToolsView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CFinancial_ToolsView ����/����

CFinancial_ToolsView::CFinancial_ToolsView()
{
	// TODO: �ڴ˴���ӹ������

}

CFinancial_ToolsView::~CFinancial_ToolsView()
{
}

BOOL CFinancial_ToolsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFinancial_ToolsView ����

void CFinancial_ToolsView::OnDraw(CDC* /*pDC*/)
{
	CFinancial_ToolsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CFinancial_ToolsView ��ӡ

BOOL CFinancial_ToolsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFinancial_ToolsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFinancial_ToolsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CFinancial_ToolsView ���

#ifdef _DEBUG
void CFinancial_ToolsView::AssertValid() const
{
	CView::AssertValid();
}

void CFinancial_ToolsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFinancial_ToolsDoc* CFinancial_ToolsView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFinancial_ToolsDoc)));
	return (CFinancial_ToolsDoc*)m_pDocument;
}
#endif //_DEBUG


