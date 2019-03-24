// FPA.cpp : 实现文件
//

#include "stdafx.h"
#include "Tools.h"
#include "FPA.h"

#define MODE_GETFV  0
#define MODE_GETPV 1
#define MODE_CONTINOUS_PV 2
// FPA 对话框

IMPLEMENT_DYNAMIC(FPA, CDialog)
CRect rect_r,rect_edit;
FPA::FPA(CWnd* pParent /*=NULL*/)
	: CDialog(FPA::IDD, pParent)
	, m_edit_A(_T(""))
	, m_edit_FV(_T(""))
	, m_edit_r(_T(""))
	, m_edit_N(_T(""))
	, MODE(0)
{

}

FPA::~FPA()
{
}

void FPA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_edit_A);
	DDX_Text(pDX, IDC_EDIT1, m_edit_FV);
	DDX_Text(pDX, IDC_EDIT3, m_edit_r);
	DDX_Text(pDX, IDC_EDIT4, m_edit_N);
}


BEGIN_MESSAGE_MAP(FPA, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &FPA::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_STATIC_FV, &FPA::OnStnClickedStaticFv)
	ON_STN_CLICKED(IDC_STATIC_A, &FPA::OnStnClickedStaticA)
	ON_STN_CLICKED(IDC_STATIC_r, &FPA::OnStnClickedStaticr)
	ON_STN_CLICKED(IDC_STATIC_N, &FPA::OnStnClickedStaticN)
	ON_BN_CLICKED(IDC_BUTTON4, &FPA::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &FPA::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &FPA::OnBnClickedButton3)
END_MESSAGE_MAP()


// FPA 消息处理程序

BOOL FPA::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_edit_FV=L"0.0";
	m_edit_A=L"0.0";
	m_edit_r=L"0.0";
	m_edit_N=L"0.0";
	MODE=MODE_GETFV;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void FPA::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int get;
	if (m_edit_FV=="0.0")
		get=WANT_GET_FV;
	else if(m_edit_A=="0.0")
		get=WANT_GET_A;
	else if(m_edit_N=="0.0")
		get=WANT_GET_N;
	else
		get=WANT_GET_R;
	long double FV,A,r;
	double N;
	FV=_wtof(m_edit_FV);
	A=_wtof(m_edit_A);
	N=_wtof(m_edit_N);
	r=_wtof(m_edit_r);
	if(MODE==MODE_GETFV)
		FutureValueOfCashFlow(&FV,&A,&r,&N);
	else if(MODE==MODE_GETPV)
		PresentValueOfCashFlow(&FV,&A,&r,&N);
	else
		PresentValueInfiniteEqualCashFlow(&FV,&A,&r);
	switch (get)
	{
	case WANT_GET_FV:
		m_edit_FV.Format(_T("%.4lf"),FV);
		UpdateData(FALSE);
		break;
	case WANT_GET_PV:
		m_edit_A.Format(_T("%.4lf"),A);
		UpdateData(FALSE);
		break;
	case WANT_GET_R:
		m_edit_r.Format(_T("%.4lf"),r);
		UpdateData(FALSE);
		break;
	case WANT_GET_N:
		m_edit_N.Format(_T("%.2f"),N);
		UpdateData(FALSE);
		break;
	}
}

void FPA::OnStnClickedStaticFv()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_tmp;
	str_tmp.LoadString(IDS_STRING_FV);
	MessageBox(str_tmp,L"解释",MB_OKCANCEL);
}

void FPA::OnStnClickedStaticA()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_tmp;
	str_tmp.LoadString(IDS_STRING_A);
	MessageBox(str_tmp,L"解释",MB_OKCANCEL);
}

void FPA::OnStnClickedStaticr()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_tmp;
	str_tmp.LoadString(1004);
	MessageBox(str_tmp,L"解释",MB_OKCANCEL);
}

void FPA::OnStnClickedStaticN()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_tmp;
	str_tmp.LoadString(1003);
	MessageBox(str_tmp,L"解释",MB_OKCANCEL);
}

void FPA::OnBnClickedButton4()//切换到求PV的模式
{
	// TODO: 在此添加控件通知处理程序代码
	if (MODE==MODE_GETFV)
		MODE_CHANGETOPV();
	else if(MODE==MODE_GETPV)
		MODE_CHANGETOFV();
	else
	{
		MODE_CHANGECONTINUSTOFV();
		MODE_CHANGETOPV();
	}

}

void FPA::MODE_CHANGETOPV(void)
{
	MODE=MODE_GETPV;
	this->GetDlgItem(IDC_STATIC_FV)->SetWindowText(_T("PV"));
	this->GetDlgItem(IDC_STATIC_MINUS)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_MINUS3)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_MINUS2)->SetWindowText(_T("+"));
}

void FPA::MODE_CHANGETOFV(void)
{
	MODE=MODE_GETFV;
	this->GetDlgItem(IDC_STATIC_FV)->SetWindowText(_T("FV"));
	this->GetDlgItem(IDC_STATIC_MINUS)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_MINUS3)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_MINUS2)->SetWindowText(_T("-"));
}

void FPA::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MODE==MODE_GETFV)
		MODE_CHANGETOCONTINUS();
	else if (MODE==MODE_CONTINOUS_PV)
		MODE_CHANGECONTINUSTOFV();
	else
	{
		MODE_CHANGETOFV();
		MODE_CHANGETOCONTINUS();
	}
}

void FPA::MODE_CHANGETOCONTINUS(void)
{
	MODE=MODE_CONTINOUS_PV;
	this->GetDlgItem(IDC_STATIC_MUTIPLY)->SetWindowText(_T("/"));
	this->GetDlgItem(IDC_STATIC_MINUS3)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_CG1)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_CG2)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_CG3)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_CG4)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_MINUS)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_N)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_EDIT4)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_MINUS2)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_MINUSONE)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_HELL)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_r2)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_STATIC_r)->GetWindowRect(rect_r);
	this->ScreenToClient(&rect_r);
	CRect crect1=rect_r;
	crect1.OffsetRect(CSize(-60,25));
	this->GetDlgItem(IDC_STATIC_r)->MoveWindow(&crect1,1);
	this->GetDlgItem(IDC_EDIT3)->GetWindowRect(rect_edit);
	this->ScreenToClient(&rect_edit);
	CRect crect2=rect_edit;
	crect2.OffsetRect(CSize(-60,25));
	this->GetDlgItem(IDC_EDIT3)->MoveWindow(&crect2,1);
}

void FPA::MODE_CHANGECONTINUSTOFV(void)
{
	MODE=MODE_GETFV;
	this->GetDlgItem(IDC_STATIC_MUTIPLY)->SetWindowText(_T("*"));
	this->GetDlgItem(IDC_STATIC_CG1)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_CG2)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_CG3)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_r)->MoveWindow(&rect_r,1);
	this->GetDlgItem(IDC_EDIT3)->MoveWindow(&rect_edit,1);
	this->GetDlgItem(IDC_STATIC_CG4)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_N)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_EDIT4)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_MINUS2)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_MINUSONE)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_HELL)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_r2)->ShowWindow(TRUE);
}



void FPA::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit_FV=L"0.0";
	m_edit_A=L"0.0";
	m_edit_r=L"0.0";
	m_edit_N=L"0.0";
	UpdateData(FALSE);
	UpdateData(TRUE);
}
