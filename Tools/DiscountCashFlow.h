#pragma once


// DiscountCashFlow �Ի���
#include "Tools.h"

class  DiscountCashFlow : public CDialog
{
	DECLARE_DYNAMIC(DiscountCashFlow)

public:
	DiscountCashFlow(CWnd* pParent = NULL);   // ��׼���캯��
    void GetDataFromChild(ObjectCashFlow_Sheet* Data);
	virtual ~DiscountCashFlow();

// �Ի�������
	enum { IDD = IDD_DIALOG_DiscountedCashFlow };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	ObjectCashFlow_Sheet Project_Sheet_receive;
	virtual BOOL OnInitDialog();
	void SetInitialItem(void);
	afx_msg void OnBnClickedButtonCalcu();
	BOOL Get_Project_Sheet_receive(CString project_name,SAFEARRAY *ptr);

	CString m_edit_r;
//	virtual BOOL DestroyWindow();
};
