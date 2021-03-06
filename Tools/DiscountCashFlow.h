#pragma once


// DiscountCashFlow 对话框
#include "Tools.h"

class  DiscountCashFlow : public CDialog
{
	DECLARE_DYNAMIC(DiscountCashFlow)

public:
	DiscountCashFlow(CWnd* pParent = NULL);   // 标准构造函数
    void GetDataFromChild(ObjectCashFlow_Sheet* Data);
	virtual ~DiscountCashFlow();

// 对话框数据
	enum { IDD = IDD_DIALOG_DiscountedCashFlow };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	ObjectCashFlow_Sheet Project_Sheet_receive;
	virtual BOOL OnInitDialog();
	void SetInitialItem_NPV_IRR(void);
	afx_msg void OnBnClickedButtonCalcu();
	BOOL Get_Project_Sheet_receive(CString project_name,SAFEARRAY *ptr);

	CString m_edit_r;
//	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButton2();
};
