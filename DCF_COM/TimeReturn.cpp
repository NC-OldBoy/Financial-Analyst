// TimeReturn.cpp : CTimeReturn 的实现

#include "stdafx.h"
#include "TimeReturn.h"
#include <cmath>
#define  MAX_READ 256

// CTimeReturn


STDMETHODIMP CTimeReturn::TimeWeightRateRuturn(VARIANT Valueflow, SHORT Years, DOUBLE* TWRR_Return)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加实现代码
	double buf[MAX_READ];
	long index=0;
	for(;index<Years;++index)
	{
		SafeArrayGetElement(Valueflow.parray,&index,buf+index);
	}
	double buf_r[MAX_READ];
	int i=0;
	for(;i<index-1;++i)
	{
		buf_r[i]=(fabs(buf[i+1])-fabs(buf[i]))/fabs(buf[i]);
	}
	double r_all=1;
	for(int j=0;j<i;++j)
		r_all*=1+buf_r[j];
	*TWRR_Return=pow(r_all,-i)-1;
	return S_OK;
}
