#pragma once


// FPA �Ի���

class FPA : public CDialog
{
	DECLARE_DYNAMIC(FPA)

public:
	FPA(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FPA();

// �Ի�������
	enum { IDD = IDD_DIALOG_FPA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_edit_A;
	CString m_edit_FV;
	CString m_edit_r;
	CString m_edit_N;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	int MODE;
	afx_msg void OnStnClickedStaticFv();
	afx_msg void OnStnClickedStaticA();
	afx_msg void OnStnClickedStaticr();
	afx_msg void OnStnClickedStaticN();
	afx_msg void OnBnClickedButton4();
	void MODE_CHANGETOPV(void);
	void MODE_CHANGETOFV(void);
	afx_msg void OnBnClickedButton2();
	void MODE_CHANGETOCONTINUS(void);
	void MODE_CHANGECONTINUSTOFV(void);
	afx_msg void OnBnClickedButton3();
};
