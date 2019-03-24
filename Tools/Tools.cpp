// Tools.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Tools.h"
#include "FPDll.h"
#include "Effective_Ruturn.h"
#include "FPA.h"
#include "DiscountCashFlow.h"
#include <cmath>
#include <windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CToolsApp

BEGIN_MESSAGE_MAP(CToolsApp, CWinApp)
END_MESSAGE_MAP()


// CToolsApp 构造
DiscountCashFlow DCF_Dialog;
CToolsApp::CToolsApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CToolsApp 对象

CToolsApp theApp;


// CToolsApp 初始化

BOOL CToolsApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

BOOL FutureAndPresentValue(long double *FV,long double *PV,long double *r,double *N)
{
	if(*FV==WANT_GET)
	{
		*FV=*PV*powl(1+*r,*N);
		return 1;
	}
	else if(*PV==WANT_GET)
	{
		*PV=*FV*(1/powl(1+*r, *N));
		return 1;
	}
	else if(*r==WANT_GET)
	{
		*r=powl(*FV/(*PV),1/(*N))-1;
		return 1;
	}
	else
	{
		*N=logl(*FV/(*PV))/log(1+*r);
		return 1;
	}
	return 0;
}

BOOL FutureAndPresentValue_NoAnnual(long double *FV,long double *PV,long double *r,double *N,int *M)
{
	if(*FV==WANT_GET)
	{
		*FV=*PV*powl(1+*r/(*M),*N*(*M));
		return 1;
	}
	else if(*PV==WANT_GET)
	{
		*PV=*FV*(1/powl(1+*r/(*M),*N*(*M)));
		return 1;
	}
	else if(*r==WANT_GET)
	{
		*r=(powl(*FV/(*PV),1/(*N*(*M)))-1)*(*M);
		return 1;
	}
	else
	{
		*N=(logl(*FV/(*PV))/log(1+*r))/(*M);
		return 1;
	}
	return 0;
}

BOOL FutureAndPresentValue_Continuous(long double *FV,long double *PV,long double *r,double *N)
{
	if(*FV==WANT_GET)
	{
		*FV=*PV*expl(*r*(*N));
		return 1;
	}
	else if(*PV==WANT_GET)
	{
		*PV=*FV/expl(*r*(*N));
		return 1;
	}
	else if(*r==WANT_GET)
	{
		*r=logl(*FV/(*PV))/(*N);
		return 1;
	}
	else
	{
		*N=logl(*FV/(*PV))/(*r);
		return 1;
	}
	return 0;
}

BOOL EffectiveAnnualRate(long double *EAR,long double *PeriodicRate,int *m)
{
	*EAR=powl(1+*PeriodicRate,*m)-1;
	return TRUE;
}

BOOL FutureValueOfCashFlow(long double *FV,long double *A,long double *r,double *N)
{
	if(*FV==WANT_GET)
	{
		*FV=*A*((powl(1+(*r),*N)-1)/(*r));
		return 1;
	}
	else if(*A==WANT_GET)
	{
		*A=*FV/((powl(1+(*r),*N)-1)/(*r));
		return 1;
	}
	else if(*r==WANT_GET)
	{
		long double i;
		for(i=0.01;*FV-*A*((powl(1+i,*N)-1)/i)>=0;i=i+0.00001)
		{
		}
		*r=i;
		return 1;
	}
	else
	{
		*N=logl((*FV/(*A))*(*r)+1)/logl(1+*r);
		return 1;
	}
}

BOOL PresentValueOfCashFlow(long double *PV,long double *A,long double *r,double *N)
{
	if(*PV==WANT_GET)
	{
		*PV=*A*((1-1/powl(1+*r,*N))/(*r));
		return 1;
	}
	else if(*A==WANT_GET)
	{
		*A=*PV/((1-1/powl(1+*r,*N))/(*r));
		return 1;
	}
	else if(*r==WANT_GET)
	{
		long double i;
		for(i=0.01;*PV-(*A)*(1-powl(1+i,-(*N)))/i<=0;i=i+0.0001)
		{
		}
		*r=i;
		return 1;
	}
	else
	{
		*N=logl(1/(1-*PV*(*r)/(*A)))/logl(1+*r);
		return 1;
	}
	return 0;
}

BOOL PresentValueInfiniteEqualCashFlow(long double *PV,long double *A,long double *r)
{

	if(*PV==WANT_GET)
	{
		*PV=*A/(*r);
		return 1;
	}
	else if(*A==WANT_GET)
	{
		*A=*PV*(*r);
		return 1;
	}
	else
	{
		*r=*A/(*PV);
		return 1;
	}
}

void ShowDlg_FPDll(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	FPDll FPDll_Dialog;
	FPDll_Dialog.DoModal();
}

void ShowDlg_Effective_Return(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	Effective_Ruturn Effective_Ruturn_Dialog;
	Effective_Ruturn_Dialog.DoModal();
}

void ShowDlg_FPA(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	FPA FPA_Dialog;
	FPA_Dialog.DoModal();
}

void ShowDlg_DiscountedCashFlow(ObjectCashFlow_Sheet Data)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(Data.Project_Num!=0&&Data.Years!=0)
	{
		DCF_Dialog.GetDataFromChild(&Data);
	    DCF_Dialog.SetInitialItem();
	}
}

void Create_DiscountedCashFlow()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	DCF_Dialog.Create(IDD_DIALOG_DiscountedCashFlow,0);
	DCF_Dialog.ShowWindow(SW_SHOW);
}

void Refresh_DiscountedCashFlow(ObjectCashFlow_Sheet Data)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(DCF_Dialog.Project_Sheet_receive!=NULL)
	{
		CListCtrl *ptr=(CListCtrl*)DCF_Dialog.GetDlgItem(IDC_LIST_CTRL);
		int count=ptr->GetHeaderCtrl()->GetItemCount();
		for(int i=0;i<count;++i)
			ptr->DeleteColumn(0);
		ptr->DeleteAllItems();
	}
	DCF_Dialog.GetDataFromChild(&Data);
	DCF_Dialog.SetInitialItem();
}

BOOL Is_Dialog_Empty()
{
	if(DCF_Dialog.m_hWnd==NULL)
		return TRUE;
	else
		return FALSE;
}


void Clear_Data(ObjectCashFlow_Sheet& Data)
{
	map<CString,ObjectCashFlow>::iterator iter=Data.Project_Sheet.begin();
	for(;iter!=Data.Project_Sheet.end();)
	{
		map<CString,long double>::iterator iter2=iter->second.Project.begin();
		for (;iter2!=iter->second.Project.end();)
		{
			iter->second.Project.erase(iter2++);
		}
		Data.Project_Sheet.erase(iter++);
	}
}

int CToolsApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	return CWinApp::ExitInstance();
}
