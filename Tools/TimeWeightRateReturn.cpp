// TimeWeightRateReturn.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "TimeWeightRateReturn.h"
#include <comdef.h>
#import "C:\Users\tgw\Documents\Visual Studio 2008\Projects\Financial-Analyst-master\DCF_COM\Debug\DCF_COM.dll" no_namespace 

// TimeWeightRateReturn 对话框

IMPLEMENT_DYNAMIC(TimeWeightRateReturn, CDialog)

TimeWeightRateReturn::TimeWeightRateReturn(CWnd* pParent /*=NULL*/)
	: CDialog(TimeWeightRateReturn::IDD, pParent)
{

}

TimeWeightRateReturn::~TimeWeightRateReturn()
{
}

void TimeWeightRateReturn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TimeWeightRateReturn, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &TimeWeightRateReturn::OnBnClickedButton1)
END_MESSAGE_MAP()


// TimeWeightRateReturn 消息处理程序

void TimeWeightRateReturn::GetDataFromChild(ObjectCashFlow_Sheet* Data)
{
	Project_Sheet_receive=*Data;
}

void TimeWeightRateReturn::SetInitialItem_TWRR(void)
{
	CListCtrl* ptrlistctrl=(CListCtrl*)this->GetDlgItem(IDC_LIST_TWRR);
	CRect tmp_rect;
	this->GetDlgItem(IDC_LIST_TWRR)->GetWindowRect(&tmp_rect);
	ptrlistctrl->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
	int width=(tmp_rect.right-tmp_rect.left)/(Project_Sheet_receive.Years+3);
	for(int i=0;i<Project_Sheet_receive.Years+3;++i)
	{
		if(i==0)
			ptrlistctrl->InsertColumn(i,L"Project",0,width,10);
		else if(i==Project_Sheet_receive.Years+1)
			ptrlistctrl->InsertColumn(i,L"Time Weight Rate Of Return",0,width,10);
		else
		{
			map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
			map<CString,long double>::iterator iter2=iter->second.Project.begin();
			for(int j=0;j!=i-1&&j<Project_Sheet_receive.Years;++j)
				++iter2;
			ptrlistctrl->InsertColumn(i,iter2->first,0,width,10);
		}
	}
	for(int i=0;i<Project_Sheet_receive.Project_Num*2;++i)//因为每个项目有两个现金流所以要在这里乘以2
	{
		ptrlistctrl->InsertItem(i,NULL);
		for(int j=0;j<Project_Sheet_receive.Years+1;++j)
		{
			map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
			for(int index=0;index<i;++index)
				++iter;
			if(j==0)
			{
				if(i%2==0)
					ptrlistctrl->SetItemText(i,j,iter->first+L" Out Flows");
				else
					ptrlistctrl->SetItemText(i,j,iter->first+L" In Flows");
			}
			else
			{
				if(i%2==0)
				{
					map<CString,long double>::iterator iter2=iter->second.Project_OutFlow.begin();
					for(int index=1;index<j;++index)
						++iter2;
					CString str;
					str.Format(_T("%.2f"),iter2->second);
					ptrlistctrl->SetItemText(i,j,str);
				}
				else
				{
					map<CString,long double>::iterator iter2=iter->second.Project_InFlow.begin();
					for(int index=1;index<j;++index)
						++iter2;
					CString str;
					str.Format(_T("%.2f"),iter2->second);
					ptrlistctrl->SetItemText(i,j,str);
				}
			}
		}
	}

}

BOOL TimeWeightRateReturn::Get_Project_Sheet_receive(CString project_name, SAFEARRAY* ptr)
{
	map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
	for(;iter!=Project_Sheet_receive.Project_Sheet.end();++iter)
	{
		if(iter->first==project_name)
			break;
	}
	if (iter==Project_Sheet_receive.Project_Sheet.end())
	{
		MessageBox(_T("没有对应的项目"));
		return FALSE;
	}
	map<CString,long double>::iterator iter2=iter->second.Project_OutFlow.begin();
	map<CString,long double>::iterator iter3=iter->second.Project_InFlow.begin();
	_variant_t vValue[256];
	int vValue_size=0;
	for(int i=0;iter2!=iter->second.Project.end();++iter2,++iter3,++i)
	{
		vValue[i]=double(iter2->second*(-1)+iter3->second);
		++vValue_size;
	}
	int j=0;
	for(long i=0;i<vValue_size;++i,++j)
	{
		::SafeArrayPutElement(ptr,&i,&(vValue[j].dblVal));
	}
	return 0;
}

void TimeWeightRateReturn::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index=0;//指示是第几行
	map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
	CoInitialize(NULL);
	CLSID clsid;
	CLSIDFromProgID(OLESTR("DCF_COM.TimeReturn"),&clsid);
	CComPtr<ITimeReturn> tools_twrr;
	tools_twrr.CoCreateInstance(clsid);
	for (;iter!=Project_Sheet_receive.Project_Sheet.end();++iter)
	{
		SAFEARRAYBOUND arrbound[1];//设置安全数组的维度
		VARIANT vsaValue;//设置variant数组
		int arrsize=Project_Sheet_receive.Years;
		arrbound[0].lLbound=0;
		arrbound[0].cElements=(long)arrsize;
		SAFEARRAY *psa=SafeArrayCreate(VT_R8,1,arrbound);
		if(psa==NULL)
		{
			MessageBox(_T("创建失败"));
		}
		Get_Project_Sheet_receive(iter->first,psa);
		vsaValue.vt= VT_ARRAY|VT_VARIANT;
		vsaValue.parray = psa;//封装safearray;
		double TWRR=0;
		TWRR=tools_twrr->TimeWeightRateRuturn(vsaValue,Project_Sheet_receive.Years);
		CListCtrl* ptrlistctrl=(CListCtrl*)this->GetDlgItem(IDC_LIST_TWRR);
		CString str;
		str.Format(_T("%.2f"),TWRR);
		ptrlistctrl->SetItemText(index,Project_Sheet_receive.Years+1,str);
		SafeArrayDestroy(psa);
		index=index+2;
	}
	tools_twrr.Release();
	CoUninitialize();
}
