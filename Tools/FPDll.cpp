// FPDll.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tools.h"
#include "FPDll.h"
#define MODE_ORD  0
#define MODE_CONTINUS 1
#define MODE_NOANNUAL 2

// FPDll �Ի���

IMPLEMENT_DYNAMIC(FPDll, CDialog)
int MODE;
CRect rect1,rect2,rect3,rect4,rect5,rect6,rect7,rect8;//��¼ԭʼλ��
FPDll::FPDll(CWnd* pParent /*=NULL*/)
	: CDialog(FPDll::IDD, pParent)
	, m_edit_FV(_T(""))
	, m_edit_PV(_T(""))
	, m_edit_r(_T(""))
	, m_edit_N(_T(""))
	, m_edit_period(_T(""))
	, m_edit_period2(_T(""))
{

}

FPDll::~FPDll()
{
}

void FPDll::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_FV);
	DDX_Text(pDX, IDC_EDIT2, m_edit_PV);
	DDX_Text(pDX, IDC_EDIT3, m_edit_r);
	DDX_Text(pDX, IDC_EDIT4, m_edit_N);
	DDX_Text(pDX, IDC_EDIT5, m_edit_period);
	DDX_Text(pDX, IDC_EDIT6, m_edit_period2);
}


BEGIN_MESSAGE_MAP(FPDll, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON1, &FPDll::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_STATIC_FV, &FPDll::OnStnClickedStaticFv)
	ON_STN_CLICKED(IDC_STATIC_PV, &FPDll::OnStnClickedStaticPv)
	ON_STN_CLICKED(IDC_STATIC_r, &FPDll::OnStnClickedStaticr)
	ON_STN_CLICKED(IDC_STATIC_N, &FPDll::OnStnClickedStaticN)
	ON_BN_CLICKED(IDC_BUTTON2, &FPDll::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &FPDll::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &FPDll::OnBnClickedButton4)
	ON_EN_UPDATE(IDC_EDIT5, &FPDll::OnEnUpdateEdit5)
	ON_EN_UPDATE(IDC_EDIT6, &FPDll::OnEnUpdateEdit6)
END_MESSAGE_MAP()


// FPDll ��Ϣ�������

int FPDll::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

BOOL FPDll::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_edit_FV=L"0.0";
	m_edit_PV=L"0.0";
	m_edit_r=L"0.0";
	m_edit_N=L"0.0";
	m_edit_period=L"0.0";
	m_edit_period2=L"0.0";
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void FPDll::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int get;
	if (m_edit_FV=="0.0")
		get=WANT_GET_FV;
	else if(m_edit_PV=="0.0")
		get=WANT_GET_PV;
	else if(m_edit_N=="0.0")
		get=WANT_GET_N;
	else
		get=WANT_GET_R;
	long double FV,PV,r;
	double N;
	int M;
	FV=_wtof(m_edit_FV);
	PV=_wtof(m_edit_PV);
	N=_wtof(m_edit_N);
	r=_wtof(m_edit_r);
	if(MODE==MODE_NOANNUAL)
		M=_wtoi(m_edit_period);
	if(MODE==MODE_ORD)
		FutureAndPresentValue(&FV,&PV,&r,&N);
	else if(MODE==MODE_CONTINUS)
		FutureAndPresentValue_Continuous(&FV,&PV,&r,&N);
	else
		FutureAndPresentValue_NoAnnual(&FV,&PV,&r,&N,&M);
	switch (get)
	{
	case WANT_GET_FV:
		m_edit_FV.Format(_T("%.4lf"),FV);
		this->GetDlgItem(IDC_STATIC_MINUS)->ShowWindow(FALSE);
		UpdateData(FALSE);
		break;
	case WANT_GET_PV:
		m_edit_PV.Format(_T("%.4lf"),PV);
		this->GetDlgItem(IDC_STATIC_MINUS)->ShowWindow(TRUE);
		UpdateData(FALSE);
		break;
	case WANT_GET_R:
		m_edit_r.Format(_T("%.4lf"),r);
		this->GetDlgItem(IDC_STATIC_MINUS)->ShowWindow(FALSE);
		UpdateData(FALSE);
		break;
	case WANT_GET_N:
		m_edit_N.Format(_T("%.2f"),N);
		this->GetDlgItem(IDC_STATIC_MINUS)->ShowWindow(FALSE);
		UpdateData(FALSE);
		break;
	}
}

//BOOL FPDll::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//    m_stat.RelayEvent(pMsg);
//	return CDialog::PreTranslateMessage(pMsg);
//}

void FPDll::OnStnClickedStaticFv()
{
	CString str_tmp;
	str_tmp.LoadString(1002);
	MessageBox(str_tmp,L"����",MB_OKCANCEL);
}

void FPDll::OnStnClickedStaticPv()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str_tmp;
	str_tmp.LoadString(1001);
	MessageBox(str_tmp,L"����",MB_OKCANCEL);
}

void FPDll::OnStnClickedStaticr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str_tmp;
	str_tmp.LoadString(1004);
	MessageBox(str_tmp,L"����",MB_OKCANCEL);
}

void FPDll::OnStnClickedStaticN()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str_tmp;
	str_tmp.LoadString(1003);
	MessageBox(str_tmp,L"����",MB_OKCANCEL);
}

void FPDll::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MODE==MODE_ORD)
	{
		MODE_ORDTOCONTINUS();
		MessageBox(_T("�л���Contious��Ϣģʽ"),_T("ע��"),0);
	}
	else if(MODE==MODE_CONTINUS)
	{
		MODE_CONTINUSTOORD();
		MessageBox(_T("�л�����ȼ�Ϣģʽ"),_T("ע��"),0);
	}
	else//Ŀǰ�Ի�����NOANNUALģʽ����Ҫת��Continus
	{
		MODE_NOANNUALTOORD();
		MODE_ORDTOCONTINUS();
		MessageBox(_T("�л���Contious��Ϣģʽ"),_T("ע��"),0);
	}
}

void FPDll::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit_FV=L"0.0";
	m_edit_PV=L"0.0";
	m_edit_r=L"0.0";
	m_edit_N=L"0.0";
	UpdateData(FALSE);
}

void FPDll::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MODE==MODE_ORD)
	{
		MODE_ORDTONOANNUAL();
		MessageBox(_T("�л�������ȼ�Ϣģʽ"),_T("ע��"),0);
	}
	else if(MODE==MODE_CONTINUS)
	{
		MODE_CONTINUSTOORD();
		MODE_ORDTONOANNUAL();
		MessageBox(_T("�л�������ȼ�Ϣģʽ"),_T("ע��"),0);
	}
	else
	{
		MODE_NOANNUALTOORD();
		MessageBox(_T("�л�����ȼ�Ϣģʽ"),_T("ע��"),0);
	}
}

void FPDll::MODE_ORDTOCONTINUS(void)
{
	MODE=MODE_CONTINUS;
	this->GetDlgItem(IDC_STATIC_CG1)->SetWindowText(_T("e"));
	this->GetDlgItem(IDC_STATIC_CG2)->SetWindowText(_T(""));
	this->GetDlgItem(IDC_STATIC_CG3)->SetWindowText(_T(""));
	this->GetDlgItem(IDC_STATIC_CG4)->SetWindowText(_T("*"));
    //����ԭʼλ��
	this->GetDlgItem(IDC_STATIC_r)->GetWindowRect(rect1);
	this->GetDlgItem(IDC_EDIT3)->GetWindowRect(rect2);
	this->GetDlgItem(IDC_STATIC_CG4)->GetWindowRect(rect3);
	this->GetDlgItem(IDC_STATIC_N)->GetWindowRect(rect4);
	this->GetDlgItem(IDC_EDIT4)->GetWindowRect(rect5);
	this->ScreenToClient(&rect1);
	this->ScreenToClient(&rect2);
	this->ScreenToClient(&rect3);
	this->ScreenToClient(&rect4);
	this->ScreenToClient(&rect5);
	//����ԭʼλ��
	this->GetDlgItem(IDC_STATIC_r)->SetWindowPos(NULL,210,107,8,13,SWP_NOZORDER);
	this->GetDlgItem(IDC_EDIT3)->SetWindowPos(NULL,220,100,46,26,SWP_NOZORDER);
	this->GetDlgItem(IDC_STATIC_CG4)->SetWindowPos(NULL,270,107,8,8,SWP_NOZORDER);
	this->GetDlgItem(IDC_STATIC_N)->SetWindowPos(NULL,285,107,8,13,SWP_NOZORDER);
	this->GetDlgItem(IDC_EDIT4)->SetWindowPos(NULL,300,100,46,26,SWP_NOZORDER);
}

void FPDll::MODE_CONTINUSTOORD(void)
{
	MODE=MODE_ORD;
	this->GetDlgItem(IDC_STATIC_CG1)->SetWindowText(_T("("));
	this->GetDlgItem(IDC_STATIC_CG2)->SetWindowText(_T("1"));
	this->GetDlgItem(IDC_STATIC_CG3)->SetWindowText(_T("+"));
	this->GetDlgItem(IDC_STATIC_CG4)->SetWindowText(_T(")"));
	this->GetDlgItem(IDC_STATIC_r)->MoveWindow(&rect1,1);
	this->GetDlgItem(IDC_EDIT3)->MoveWindow(&rect2,1);
	this->GetDlgItem(IDC_STATIC_CG4)->MoveWindow(&rect3,1);
	this->GetDlgItem(IDC_STATIC_N)->MoveWindow(&rect4,1);
	this->GetDlgItem(IDC_EDIT4)->MoveWindow(&rect5,1);

}
void FPDll::MODE_ORDTONOANNUAL(void)
{
	MODE=MODE_NOANNUAL;
	this->GetDlgItem(IDC_STATIC_r)->GetWindowRect(rect1);
	this->GetDlgItem(IDC_EDIT3)->GetWindowRect(rect2);
	this->ScreenToClient(&rect1);
	this->ScreenToClient(&rect2);
	CRect crect1=rect1;
	crect1.OffsetRect(CSize(0,-20));
	this->GetDlgItem(IDC_STATIC_r)->MoveWindow(&crect1,1);
	CRect crect2=rect2;
	crect2.OffsetRect(CSize(0,-20));
	this->GetDlgItem(IDC_EDIT3)->MoveWindow(&crect2,1);
	this->GetDlgItem(IDC_STATIC_HELL)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_HELL)->GetWindowRect(rect6);
	this->ScreenToClient(&rect6);//��ס�˳��ŵ�ԭʼλ��;
	CRect crect6=rect6;
	crect6.OffsetRect(CSize(0,-20));
	this->GetDlgItem(IDC_STATIC_HELL)->MoveWindow(&crect6,1);
	this->GetDlgItem(IDC_STATIC_m)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_m)->GetWindowRect(rect7);
	this->ScreenToClient(&rect7);//��ס��m��ԭʼλ��;
	CRect crect7=rect7;
	crect7.OffsetRect(CSize(0,-20));
	this->GetDlgItem(IDC_STATIC_m)->MoveWindow(&crect7,1);
	this->GetDlgItem(IDC_EDIT5)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_EDIT5)->GetWindowRect(rect8);
	this->ScreenToClient(&rect8);//��ס��m��ԭʼλ��;
	CRect crect8=rect8;
	crect8.OffsetRect(CSize(0,-20));
	this->GetDlgItem(IDC_EDIT5)->MoveWindow(&crect8,1);
	this->GetDlgItem(IDC_EDIT6)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_m2)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_STATIC_N2)->ShowWindow(TRUE);
}

void FPDll::MODE_NOANNUALTOORD(void)
{
	MODE=MODE_ORD;
	this->GetDlgItem(IDC_STATIC_r)->MoveWindow(&rect1,1);
	this->GetDlgItem(IDC_EDIT3)->MoveWindow(&rect2,1);
	this->GetDlgItem(IDC_STATIC_HELL)->MoveWindow(&rect6,1);
	this->GetDlgItem(IDC_EDIT5)->MoveWindow(&rect8,1);
	this->GetDlgItem(IDC_STATIC_m)->MoveWindow(&rect7,1);
    this->GetDlgItem(IDC_STATIC_HELL)->ShowWindow(FALSE);
    this->GetDlgItem(IDC_STATIC_m)->ShowWindow(FALSE);
    this->GetDlgItem(IDC_EDIT5)->ShowWindow(FALSE);
    this->GetDlgItem(IDC_EDIT6)->ShowWindow(FALSE);
    this->GetDlgItem(IDC_STATIC_m2)->ShowWindow(FALSE);
    this->GetDlgItem(IDC_STATIC_N2)->ShowWindow(FALSE);
}

void FPDll::OnEnUpdateEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str_tmp;
	this->GetDlgItem(IDC_EDIT5)->GetWindowText(str_tmp);
	this->GetDlgItem(IDC_EDIT6)->SetWindowText(str_tmp);
	UpdateData(TRUE);
}

void FPDll::OnEnUpdateEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str_tmp;
	this->GetDlgItem(IDC_EDIT6)->GetWindowText(str_tmp);
	this->GetDlgItem(IDC_EDIT5)->SetWindowText(str_tmp);
	UpdateData(TRUE);
}
