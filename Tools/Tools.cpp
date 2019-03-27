// Tools.cpp : ���� DLL �ĳ�ʼ�����̡�
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
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CToolsApp

BEGIN_MESSAGE_MAP(CToolsApp, CWinApp)
END_MESSAGE_MAP()


// CToolsApp ����
DiscountCashFlow DCF_Dialog;
CToolsApp::CToolsApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CToolsApp ����

CToolsApp theApp;


// CToolsApp ��ʼ��

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
	if(&DCF_Dialog.m_hWnd!=NULL)
		DCF_Dialog.DestroyWindow();
	DCF_Dialog.Create(IDD_DIALOG_DiscountedCashFlow,0);
	DCF_Dialog.ShowWindow(SW_SHOW);
}

void Refresh_DiscountedCashFlow(ObjectCashFlow_Sheet Data)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!DCF_Dialog.Project_Sheet_receive.isempty())
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
	// TODO: �ڴ����ר�ô����/����û���
	return CWinApp::ExitInstance();
}
