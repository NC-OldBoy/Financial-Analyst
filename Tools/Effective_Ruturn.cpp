// Effective_Ruturn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tools.h"
#include "Effective_Ruturn.h"


// Effective_Ruturn �Ի���

IMPLEMENT_DYNAMIC(Effective_Ruturn, CDialog)

Effective_Ruturn::Effective_Ruturn(CWnd* pParent /*=NULL*/)
	: CDialog(Effective_Ruturn::IDD, pParent)
	, m_edit_EAR(_T(""))
	, m_edit_PeriodRate(_T(""))
	, m_edit_annual_m(_T(""))
{

}

Effective_Ruturn::~Effective_Ruturn()
{
}

void Effective_Ruturn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_EAR);
	DDX_Text(pDX, IDC_EDIT3, m_edit_PeriodRate);
	DDX_Text(pDX, IDC_EDIT4, m_edit_annual_m);
}


BEGIN_MESSAGE_MAP(Effective_Ruturn, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &Effective_Ruturn::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &Effective_Ruturn::OnBnClickedButton3)
	ON_STN_CLICKED(IDC_STATIC_EAR, &Effective_Ruturn::OnStnClickedStaticEAR)
	ON_STN_CLICKED(IDC_STATIC_PERIOD_RETURN, &Effective_Ruturn::OnStnClickedStaticPeriodReturn)
END_MESSAGE_MAP()


// Effective_Ruturn ��Ϣ�������

void Effective_Ruturn::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	long double EAR,Period_Ruturn;
	int M;
	EAR=_wtof(m_edit_EAR);
	Period_Ruturn=_wtof(m_edit_PeriodRate);
	M=_wtoi(m_edit_annual_m);
	EffectiveAnnualRate(&EAR,&Period_Ruturn,&M);
	m_edit_EAR.Format(_T("%.4lf"),EAR);
	UpdateData(FALSE);
}

void Effective_Ruturn::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit_EAR=L"0.0";
	m_edit_PeriodRate=L"0.0";
	m_edit_annual_m=L"0.0";
	UpdateData(FALSE);
}

BOOL Effective_Ruturn::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_edit_EAR=L"0.0";
	m_edit_PeriodRate=L"0.0";
	m_edit_annual_m=L"0.0";
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void Effective_Ruturn::OnStnClickedStaticEAR()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str_tmp;
	str_tmp.LoadString(1006);
	MessageBox(str_tmp,L"����",MB_OKCANCEL);
}

void Effective_Ruturn::OnStnClickedStaticPeriodReturn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str_tmp;
	str_tmp.LoadString(1007);
	MessageBox(str_tmp,L"����",MB_OKCANCEL);
}
