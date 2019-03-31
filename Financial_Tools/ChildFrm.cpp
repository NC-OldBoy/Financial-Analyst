// ChildFrm.cpp : CChildFrame 类的实现
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


// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CChildFrame 诊断

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


// CChildFrame 消息处理程序


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
	// TODO: 在此添加命令处理程序代码
	ShowDlg_FPDll();
}


void CChildFrame::OnEffectivereturn()
{
	// TODO: 在此添加命令处理程序代码
	ShowDlg_Effective_Return();
}

void CChildFrame::OnFpa()
{
	// TODO: 在此添加命令处理程序代码
	ShowDlg_FPA();
}

void CChildFrame::OnNpv()
{
	// TODO: 在此添加命令处理程序代码
	CFinancial_ToolsDoc * pCurrentDoc = (CFinancial_ToolsDoc *)this->GetActiveDocument();
	ObjectCashFlow_Sheet* tmp=pCurrentDoc->GetDocData();
	Create_DiscountedCashFlow_DCF();
	ShowDlg_DiscountedCashFlow_DCF(*tmp);
}


void CChildFrame::OnTwrr()
{
	// TODO: 在此添加命令处理程序代码
	CFinancial_ToolsDoc * pCurrentDoc = (CFinancial_ToolsDoc *)this->GetActiveDocument();
	ObjectCashFlow_Sheet* tmp=pCurrentDoc->GetDocData();
	Create_DiscountedCashFlow_TWRR();
	ShowDlg_DiscountedCashFlow_TWRR(*tmp);
}
