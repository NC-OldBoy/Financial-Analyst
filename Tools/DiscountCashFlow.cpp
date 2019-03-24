// DiscountCashFlow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tools.h"
#include "DiscountCashFlow.h"

// DiscountCashFlow �Ի���

IMPLEMENT_DYNAMIC(DiscountCashFlow, CDialog)

DiscountCashFlow::DiscountCashFlow(CWnd* pParent /*=NULL*/)
	: CDialog(DiscountCashFlow::IDD, pParent)
{
	Project_Sheet_receive=NULL;
}

DiscountCashFlow::~DiscountCashFlow()
{
	
}

void DiscountCashFlow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DiscountCashFlow, CDialog)
END_MESSAGE_MAP()


// DiscountCashFlow ��Ϣ�������

void DiscountCashFlow::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialog::PostNcDestroy();
}

void DiscountCashFlow::GetDataFromChild(ObjectCashFlow_Sheet* Data)
{
	Project_Sheet_receive=Data;
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
	int width=(tmp_rect.right-tmp_rect.left)/(Project_Sheet_receive->Years+3);
	for(int i=0;i<Project_Sheet_receive->Years+3;++i)
	{
		if(i==0)
			ptrlistctrl->InsertColumn(i,L"Project",0,width,10);
		else if(i==Project_Sheet_receive->Years+1)
			ptrlistctrl->InsertColumn(i,L"NPV",0,width,10);
		else if(i==Project_Sheet_receive->Years+2)
			ptrlistctrl->InsertColumn(i,L"IRR",0,width,10);
		else
		{
			map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive->Project_Sheet.begin();
			map<CString,long double>::iterator iter2=iter->second.Project.begin();
			for(int j=0;j!=i-1&&j<Project_Sheet_receive->Years;++j)
				++iter2;
			ptrlistctrl->InsertColumn(i,iter2->first,0,width,10);
		}
	}
	for(int i=0;i<Project_Sheet_receive->Project_Num;++i)
	{
		ptrlistctrl->InsertItem(i,NULL);
		for(int j=0;j<Project_Sheet_receive->Years+1;++j)
		{
			map<CString,ObjectCashFlow>::iterator iter=Project_Sheet_receive->Project_Sheet.begin();
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
