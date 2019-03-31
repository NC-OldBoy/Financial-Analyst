// ChildFrm.cpp : CChildFrame ���ʵ��
//
#include "stdafx.h"
#include "Financial_Tools.h"
#include "ChildFrm.h"
#include "Financial_ToolsDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame
#pragma comment(lib,"../Debug/Tools.lib")
IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_COMMAND(ID_FutureAndPresent, &CChildFrame::OnFutureandpresent)
	ON_COMMAND(ID_Effective_return, &CChildFrame::OnEffectivereturn)
	ON_COMMAND(ID_FPA, &CChildFrame::OnFpa)
	ON_COMMAND(ID_NPV, &CChildFrame::OnNpv)
	ON_COMMAND(ID_TWRR, &CChildFrame::OnTwrr)
END_MESSAGE_MAP()


// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame ��Ϣ�������


extern void _declspec(dllimport) ShowDlg_FPDll(void);
extern void _declspec(dllimport) ShowDlg_Effective_Return(void);
extern void _declspec(dllimport) ShowDlg_FPA(void);
extern void _declspec(dllimport) ShowDlg_DiscountedCashFlow_DCF(ObjectCashFlow_Sheet Data);
extern void _declspec(dllimport) Create_DiscountedCashFlow_DCF();
extern void _declspec(dllimport) Refresh_DiscountedCashFlow_DCF(ObjectCashFlow_Sheet Data);
extern void _declspec(dllimport) ShowDlg_DiscountedCashFlow_TWRR(ObjectCashFlow_Sheet Data);
extern void _declspec(dllimport) Create_DiscountedCashFlow_TWRR();
extern void _declspec(dllimport) Refresh_DiscountedCashFlow_TWRR(ObjectCashFlow_Sheet Data);
void CChildFrame::OnFutureandpresent()
{
	// TODO: �ڴ���������������
	ShowDlg_FPDll();
}


void CChildFrame::OnEffectivereturn()
{
	// TODO: �ڴ���������������
	ShowDlg_Effective_Return();
}

void CChildFrame::OnFpa()
{
	// TODO: �ڴ���������������
	ShowDlg_FPA();
}

void CChildFrame::OnNpv()
{
	// TODO: �ڴ���������������
	CFinancial_ToolsDoc * pCurrentDoc = (CFinancial_ToolsDoc *)this->GetActiveDocument();
	ObjectCashFlow_Sheet* tmp=pCurrentDoc->GetDocData();
	Create_DiscountedCashFlow_DCF();
	ShowDlg_DiscountedCashFlow_DCF(*tmp);
}


void CChildFrame::OnTwrr()
{
	// TODO: �ڴ���������������
	CFinancial_ToolsDoc * pCurrentDoc = (CFinancial_ToolsDoc *)this->GetActiveDocument();
	ObjectCashFlow_Sheet* tmp=pCurrentDoc->GetDocData();
	Create_DiscountedCashFlow_TWRR();
	ShowDlg_DiscountedCashFlow_TWRR(*tmp);
}
