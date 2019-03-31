// DiscountCashFlow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tools.h"
#include "DiscountCashFlow.h"
#include <comdef.h>
#import "C:\Users\tgw\Documents\Visual Studio 2008\Projects\Financial-Analyst-master\DCF_COM\Debug\DCF_COM.dll" no_namespace 
// DiscountCashFlow �Ի���
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
	ON_BN_CLICKED(IDC_BUTTON2, &DiscountCashFlow::OnBnClickedButton2)
END_MESSAGE_MAP()


// DiscountCashFlow ��Ϣ�������

void DiscountCashFlow::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void DiscountCashFlow::SetInitialItem_NPV_IRR(void)
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int index=0;//ָʾ�ǵڼ���
	map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
	CoInitialize(NULL);
	CLSID clsid;
	CLSIDFromProgID(OLESTR("DCF_COM.DCF_Tools"),&clsid);
	CComPtr<IDCF_Tools> tools;
	tools.CoCreateInstance(clsid);
	for (;iter!=Project_Sheet_receive.Project_Sheet.end();++iter)
	{
		SAFEARRAYBOUND arrbound[1];//���ð�ȫ�����ά��
		VARIANT vsaValue;//����variant����
		int arrsize=Project_Sheet_receive.Years;
		arrbound[0].lLbound=0;
		arrbound[0].cElements=(long)arrsize;
		SAFEARRAY *psa=SafeArrayCreate(VT_R8,1,arrbound);
		if(psa==NULL)
		{
			MessageBox(_T("����ʧ��"));
		}
		Get_Project_Sheet_receive(iter->first,psa);
		vsaValue.vt= VT_ARRAY|VT_VARIANT;
		vsaValue.parray = psa;//��װsafearray;
		double NPV=0;
		double Return=_wtof(m_edit_r);
		NPV=tools->NPV(Return,vsaValue,Project_Sheet_receive.Years);
		CListCtrl* ptrlistctrl=(CListCtrl*)this->GetDlgItem(IDC_LIST_CTRL);
		CString str;
		str.Format(_T("%.2f"),NPV);
		ptrlistctrl->SetItemText(index,Project_Sheet_receive.Years+1,str);
		SafeArrayDestroy(psa);
		++index;
	}
	tools.Release();
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
		MessageBox(_T("û�ж�Ӧ����Ŀ"));
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



void DiscountCashFlow::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int index=0;//ָʾ�ǵڼ���
	map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
	CoInitialize(NULL);
	CLSID clsid;
	CLSIDFromProgID(OLESTR("DCF_COM.DCF_Tools"),&clsid);
	CComPtr<IDCF_Tools> tools;
	tools.CoCreateInstance(clsid);
	for (;iter!=Project_Sheet_receive.Project_Sheet.end();++iter)
	{
		SAFEARRAYBOUND arrbound[1];//���ð�ȫ�����ά��
		VARIANT vsaValue;//����variant����
		int arrsize=Project_Sheet_receive.Years;
		arrbound[0].lLbound=0;
		arrbound[0].cElements=(long)arrsize;
		SAFEARRAY *psa=SafeArrayCreate(VT_R8,1,arrbound);
		if(psa==NULL)
		{
			MessageBox(_T("����ʧ��"));
		}
		Get_Project_Sheet_receive(iter->first,psa);
		vsaValue.vt= VT_ARRAY|VT_VARIANT;
		vsaValue.parray = psa;//��װsafearray;
		double IRR=0;
		IRR=tools->IRR(vsaValue,Project_Sheet_receive.Years);
		CListCtrl* ptrlistctrl=(CListCtrl*)this->GetDlgItem(IDC_LIST_CTRL);
		CString str;
		if(IRR==0)
			str=L"������Ŀ";
		else if(IRR==1)
			str=L"ӯ����100%";
		else
			str.Format(_T("%.5f"),IRR);
		ptrlistctrl->SetItemText(index,Project_Sheet_receive.Years+2,str);
		SafeArrayDestroy(psa);
		++index;
	}
	tools.Release();
	CoUninitialize();
}

