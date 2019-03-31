// Tools.h : Tools DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <cstdlib>
#include <cmath>
#include "../ObjectCashFlow_Sheet/ObjectCashFlow_Sheet.h"
#include "Discountcashflow.h"
#include "TimeWeightRateReturn.h"
#include <OAIdl.h>

//判别想求什么
#define WANT_GET 0
#define WANT_GET_FV 1
#define WANT_GET_PV 2
#define WANT_GET_N 3
#define WANT_GET_R 4
#define WANT_GET_A 5
// CToolsApp
// 有关此类实现的信息，请参阅 Tools.cpp
//
BOOL FutureAndPresentValue(long double *FV,long double *PV,long double *r,double *N);
BOOL FutureAndPresentValue_NoAnnual(long double *FV,long double *PV,long double *r,double *N,int *M);
BOOL FutureAndPresentValue_Continuous(long double *FV,long double *PV,long double *r,double *N);
BOOL EffectiveAnnualRate(long double *EAR,long double *PeriodicRate,int *m);
BOOL FutureValueOfCashFlow(long double *FV,long double *A,long double *r,double *N);
BOOL PresentValueOfCashFlow(long double *PV,long double *A,long double *r,double *N);
BOOL PresentValueInfiniteEqualCashFlow(long double *PV,long double *A,long double *r);
void ShowDlg_FPDll(void);
void ShowDlg_Effective_Return(void);
void ShowDlg_FPA(void);
void ShowDlg_DiscountedCashFlow_DCF(ObjectCashFlow_Sheet Data);
void Create_DiscountedCashFlow_DCF();
void Refresh_DiscountedCashFlow_DCF(ObjectCashFlow_Sheet Data);
void ShowDlg_DiscountedCashFlow_TWRR(ObjectCashFlow_Sheet Data);
void Create_DiscountedCashFlow_TWRR();
void Refresh_DiscountedCashFlow_TWRR(ObjectCashFlow_Sheet Data);
BOOL Is_Dialog_Empty();
void Clear_Data(ObjectCashFlow_Sheet& Data);
extern DiscountCashFlow DCF_Dialog;
extern TimeWeightRateReturn TWRR_Dialog;
class CToolsApp : public CWinApp
{
public:
	CToolsApp();

// 重写
public:
	virtual BOOL InitInstance();
    
	DECLARE_MESSAGE_MAP()
	
	virtual int ExitInstance();
};
