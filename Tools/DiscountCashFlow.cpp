// DiscountCashFlow.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "DiscountCashFlow.h"
#include "../DCF_COM/DCF_COM_i.h"
#include "../DCF_COM/DCF_COM_i.c"
#include <comdef.h>
//#import "C:\Users\tgw\Documents\Visual Studio 2008\Projects\Financial-Analyst-master\DCF_COM\Debug\DCF_COM.dll" no_namespace 
// DiscountCashFlow 对话框
#define MAX_SIZE 256
IMPLEMENT_DYNAMIC(DiscountCashFlow, CDialog)

DiscountCashFlow::DiscountCashFlow(CWnd* pParent /*=NULL*/)
	: CDialog(DiscountCashFlow::IDD, pParent)
	, m_edit_r(_T(""))
{
	
}

DiscountCashFlow::~DiscountCashFlow()
{
	
}

void DiscountCashFlow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_r);
}


BEGIN_MESSAGE_MAP(DiscountCashFlow, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DiscountCashFlow::OnBnClickedButtonCalcu)
END_MESSAGE_MAP()


// DiscountCashFlow 消息处理程序

void DiscountCashFlow::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialog::PostNcDestroy();
	//DCF_Dialog.m_hWnd=NULL;
}

void DiscountCashFlow::GetDataFromChild(ObjectCashFlow_Sheet* Data)
{
	Project_Sheet_receive=*Data;
}
BOOL DiscountCashFlow::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_edit_r=L"0.0";
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void DiscountCashFlow::SetInitialItem(void)
{
	CListCtrl* ptrlistctrl=(CListCtrl*)this->GetDlgItem(IDC_LIST_CTRL);
	CRect tmp_rect;
	this->GetDlgItem(IDC_LIST_CTRL)->GetWindowRect(&tmp_rect);
	ptrlistctrl->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
	int width=(tmp_rect.right-tmp_rect.left)/(Project_Sheet_receive.Years+3);
	for(int i=0;i<Project_Sheet_receive.Years+3;++i)
	{
		if(i==0)
			ptrlistctrl->InsertColumn(i,L"Project",0,width,10);
		else if(i==Project_Sheet_receive.Years+1)
			ptrlistctrl->InsertColumn(i,L"NPV",0,width,10);
		else if(i==Project_Sheet_receive.Years+2)
			ptrlistctrl->InsertColumn(i,L"IRR",0,width,10);
		else
		{
			map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
			map<CString,long double>::iterator iter2=iter->second.Project.begin();
			for(int j=0;j!=i-1&&j<Project_Sheet_receive.Years;++j)
				++iter2;
			ptrlistctrl->InsertColumn(i,iter2->first,0,width,10);
		}
	}
	for(int i=0;i<Project_Sheet_receive.Project_Num;++i)
	{
		ptrlistctrl->InsertItem(i,NULL);
		for(int j=0;j<Project_Sheet_receive.Years+1;++j)
		{
			map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
			for(int index=0;index<i;++index)
				++iter;
			if(j==0)
			{
				ptrlistctrl->SetItemText(i,j,iter->first);
			}
			else
			{
				map<CString,long double>::iterator iter2=iter->second.Project.begin();
				for(int index=1;index<j;++index)
					++iter2;
				CString str;
				str.Format(_T("%.2f"),iter2->second);
				ptrlistctrl->SetItemText(i,j,str);
			}
		}
	}
	
}

void DiscountCashFlow::OnBnClickedButtonCalcu()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index=0;//指示是第几行
	map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
	IDCF_Tools *tools;
	HRESULT hResult=CoCreateInstance(CLSID_DCF_Tools,NULL,CLSCTX_INPROC_SERVER,IID_IDCF_Tools,(void**)&tools);
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
		double NPV=0;
		double Return=_wtof(m_edit_r);
		tools->NPV(Return,vsaValue,Project_Sheet_receive.Years,&NPV);
		CListCtrl* ptrlistctrl=(CListCtrl*)this->GetDlgItem(IDC_LIST_CTRL);
		CString str;
		str.Format(_T("%.2f"),NPV);
		ptrlistctrl->SetItemText(index,Project_Sheet_receive.Years+1,str);
		SafeArrayDestroy(psa);
		++index;
	}
	iter=Project_Sheet_receive.Project_Sheet.begin();
	index=0;
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
		double IRR=0;
		tools->IRR(vsaValue,Project_Sheet_receive.Years,&IRR);
		CListCtrl* ptrlistctrl=(CListCtrl*)this->GetDlgItem(IDC_LIST_CTRL);
		CString str;
		if(IRR==0)
			str=L"亏本项目";
		else if(IRR==1)
			str=L"盈利超100%";
		else
			str.Format(_T("%.2f"),IRR);
		ptrlistctrl->SetItemText(index,Project_Sheet_receive.Years+2,str);
		SafeArrayDestroy(psa);
		++index;
	}
	CoUninitialize();
}

BOOL DiscountCashFlow::Get_Project_Sheet_receive(CString project_name,SAFEARRAY *ptr)//
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
	map<CString,long double>::iterator iter2=iter->second.Project.begin();
	_variant_t vValue[MAX_SIZE];
	int vValue_size=0;
	for(int i=0;iter2!=iter->second.Project.end();++iter2,++i)
	{
		vValue[i]=double(iter2->second);
		++vValue_size;
	}
	int j=0;
	for(long i=0;i<vValue_size;++i,++j)
	{
		::SafeArrayPutElement(ptr,&i,&(vValue[j].dblVal));
	}
	return 0;
}


