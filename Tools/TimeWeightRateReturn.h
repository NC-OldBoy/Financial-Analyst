#pragma once
#include "Tools.h"


// TimeWeightRateReturn �Ի���

class TimeWeightRateReturn : public CDialog
{
	DECLARE_DYNAMIC(TimeWeightRateReturn)

public:
	TimeWeightRateReturn(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TimeWeightRateReturn();

// �Ի�������
	enum { IDD = IDD_DIALOG_TWRR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void GetDataFromChild(ObjectCashFlow_Sheet* Data);
	ObjectCashFlow_Sheet Project_Sheet_receive;
	void SetInitialItem_TWRR(void);
	BOOL Get_Project_Sheet_receive(CString project_name, SAFEARRAY* ptr);
	afx_msg void OnBnClickedButton1();
};
