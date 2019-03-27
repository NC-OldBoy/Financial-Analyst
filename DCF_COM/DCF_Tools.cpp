// DCF_Tools.cpp : CDCF_Tools 的实现

#include "stdafx.h"
#include "DCF_Tools.h"
#include <cmath>
#define  MAX_READ 256
// CDCF_Tools



STDMETHODIMP CDCF_Tools::NPV(DOUBLE r, VARIANT CashFlow, SHORT Years, DOUBLE* NPV_Result)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加实现代码
	double buf[MAX_READ];
	double NPV_TMP=0;
	for(long index=0;index<Years;++index)
	{
		SafeArrayGetElement(CashFlow.parray,&index,buf+index);
	}
	for(int i=0;i<Years;++i)
	{
		NPV_TMP+=buf[i]/pow(1+r,i);
	}
	*NPV_Result=NPV_TMP;
	return S_OK;
}

STDMETHODIMP CDCF_Tools::IRR( VARIANT Cashflow, SHORT Years, DOUBLE* IRR_Return)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加实现代码
	double buf[MAX_READ];
	for(long index=0;index<Years;++index)
	{
		SafeArrayGetElement(Cashflow.parray,&index,buf+index);
	}
	double r=0;
	double NPV_TMP=0;
	for(r=0;NPV_TMP>=0&&r<1;r=r+0.0001)
	{
		for(int i=0;i<Years;++i)
		{
			NPV_TMP+=buf[i]/pow(1+r,i);
		}
	}
	*IRR_Return=r;
	return S_OK;
}
