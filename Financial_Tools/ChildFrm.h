// ChildFrm.h : CChildFrame ��Ľӿ�
//


#pragma once

#include "../ObjectCashFlow_Sheet/ObjectCashFlow_Sheet.h"
class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// ����
public:
    
// ����
public:

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFutureandpresent();
	afx_msg void OnEffectivereturn();
	afx_msg void OnFpa();
	afx_msg void OnNpv();
	afx_msg void OnTwrr();
};
