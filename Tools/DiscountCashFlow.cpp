// DiscountCashFlow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tools.h"
#include "DiscountCashFlow.h"
#include "../DCF_COM/DCF_COM_i.h"
#include "../DCF_COM/DCF_COM_i.c"
//#import "C:\Users\tgw\Documents\Visual Studio 2008\Projects\Financial-Analyst-master\DCF_COM\Debug\DCF_COM.dll" no_namespace 
// DiscountCashFlow �Ի���

IMPLEMENT_DYNAMIC(DiscountCashFlow, CDialog)

DiscountCashFlow::DiscountCashFlow(CWnd* pParent /*=NULL*/)
	: CDialog(DiscountCashFlow::IDD, pParent)
	, m_edit_r1(0)
{
	
}

DiscountCashFlow::~DiscountCashFlow()
{
	
}

void DiscountCashFlow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(DiscountCashFlow, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DiscountCashFlow::OnBnClickedButtonCalcu)
END_MESSAGE_MAP()


// DiscountCashFlow ��Ϣ�������

void DiscountCashFlow::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialog::PostNcDestroy();
}

void DiscountCashFlow::GetDataFromChild(ObjectCashFlow_Sheet* Data)
{
	Project_Sheet_receive=*Data;
}
BOOL DiscountCashFlow::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int index=0;//ָʾ�ǵڼ���
	map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive.Project_Sheet.begin();
	IDCF_Tools *tools;
	if(CoInitialize(NULL)!=S_OK)
	{
		MessageBox(_T("��ʼ�����ʧ��"));
	}
	HRESULT hResult=CoCreateInstance(CLSID_DCF_Tools,NULL,CLSCTX_INPROC_SERVER,IID_IDCF_Tools,(void**)&tools);
	for (;iter!=Project_Sheet_receive.Project_Sheet.end();++iter)
	{
		SAFEARRAY *psa;
		SAFEARRAYBOUND arrbound[1];//���ð�ȫ�����ά��
		VARIANT vsaValue;//����variant����
		int arrsize=Project_Sheet_receive.Years;
		arrbound[0].lLbound=0;
		arrbound[1].cElements=(long)arrsize;
		psa=SafeArrayCreate(VT_R8,1,arrbound);
		Get_Project_Sheet_receive(iter->first,psa);
		vsaValue.vt= VT_ARRAY|VT_VARIANT;
		V_ARRAY(&vsaValue) = psa;//��װsafearray;
		double *NPV=0;
		*NPV=tools->NPV(m_edit_r1,vsaValue,Project_Sheet_receive.Years,NPV);
		CListCtrl* ptrlistctrl=(CListCtrl*)this->GetDlgItem(IDC_LIST_CTRL);
		CString str;
		str.Format(_T("%.2f"),NPV);
		ptrlistctrl->SetItemText(index,Project_Sheet_receive.Years,str);
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
		MessageBox(_T("û�ж�Ӧ����Ŀ"));
		return FALSE;
	}
	map<CString,long double>::iterator iter2=iter->second.Project.begin();
	for(long i=0;iter2!=iter->second.Project.end();++iter2,++i)
	{
		SafeArrayPutElement(ptr,&i,&(iter2->second));
	}
	return 0;
}
