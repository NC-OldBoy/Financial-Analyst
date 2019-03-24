// ChildFrm.h : CChildFrame 类的接口
//


#pragma once

#include "../ObjectCashFlow_Sheet/ObjectCashFlow_Sheet.h"
class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 属性
public:
    
// 操作
public:

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFutureandpresent();
	afx_msg void OnEffectivereturn();
	afx_msg void OnFpa();
	afx_msg void OnNpv();
};
