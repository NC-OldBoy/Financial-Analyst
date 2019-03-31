#pragma once
#include "Tools.h"


// TimeWeightRateReturn 对话框

class TimeWeightRateReturn : public CDialog
{
	DECLARE_DYNAMIC(TimeWeightRateReturn)

public:
	TimeWeightRateReturn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TimeWeightRateReturn();

// 对话框数据
	enum { IDD = IDD_DIALOG_TWRR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void GetDataFromChild(ObjectCashFlow_Sheet* Data);
	ObjectCashFlow_Sheet Project_Sheet_receive;
	void SetInitialItem_TWRR(void);
	BOOL Get_Project_Sheet_receive(CString project_name, SAFEARRAY* ptr);
	afx_msg void OnBnClickedButton1();
};
