#pragma once


// Effective_Ruturn �Ի���

class Effective_Ruturn : public CDialog
{
	DECLARE_DYNAMIC(Effective_Ruturn)

public:
	Effective_Ruturn(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Effective_Ruturn();

// �Ի�������
	enum { IDD = IDD_DIALOG_EFFECTIVE_R };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_edit_EAR;
	CString m_edit_PeriodRate;
	CString m_edit_annual_m;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedStaticEAR();
	afx_msg void OnStnClickedStaticPeriodReturn();
};
