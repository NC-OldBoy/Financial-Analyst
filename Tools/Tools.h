// Tools.h : Tools DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <cstdlib>
#include <cmath>
#include "../ObjectCashFlow_Sheet/ObjectCashFlow_Sheet.h"
#include "discountcashflow.h"
#include <OAIdl.h>
//�б�����ʲô
#define WANT_GET 0
#define WANT_GET_FV 1
#define WANT_GET_PV 2
#define WANT_GET_N 3
#define WANT_GET_R 4
#define WANT_GET_A 5
// CToolsApp
// �йش���ʵ�ֵ���Ϣ������� Tools.cpp
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
void ShowDlg_DiscountedCashFlow(ObjectCashFlow_Sheet Data);
void Create_DiscountedCashFlow();
void Refresh_DiscountedCashFlow(ObjectCashFlow_Sheet Data);
BOOL Is_Dialog_Empty();
void Clear_Data(ObjectCashFlow_Sheet& Data);
extern DiscountCashFlow DCF_Dialog;
class CToolsApp : public CWinApp
{
public:
	CToolsApp();

// ��д
public:
	virtual BOOL InitInstance();
    
	DECLARE_MESSAGE_MAP()
	
	virtual int ExitInstance();
};
