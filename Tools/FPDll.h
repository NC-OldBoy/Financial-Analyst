#pragma once


// FPDll 对话框


class FPDll : public CDialog
{
	DECLARE_DYNAMIC(FPDll)

public:
	FPDll(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FPDll();

// 对话框数据
	enum { IDD = IDD_DIALOG1};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	CString m_edit_FV;
	CString m_edit_PV;
	CString m_edit_r;
	CString m_edit_N;
	afx_msg void OnBnClickedButton1();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedStaticFv();
	afx_msg void OnStnClickedStaticPv();
	afx_msg void OnStnClickedStaticr();
	afx_msg void OnStnClickedStaticN();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	void MODE_ORDTOCONTINUS(void);
	void MODE_CONTINUSTOORD(void);
	void MODE_ORDTONOANNUAL(void);
	void MODE_NOANNUALTOORD(void);
	CString m_edit_period;
	CString m_edit_period2;
	afx_msg void OnEnUpdateEdit5();
	afx_msg void OnEnUpdateEdit6();
};
