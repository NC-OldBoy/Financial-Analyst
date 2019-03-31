// TimeReturn.h : CTimeReturn ������

#pragma once
#include "resource.h"       // ������

#include "DCF_COM_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CTimeReturn

class ATL_NO_VTABLE CTimeReturn :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTimeReturn, &CLSID_TimeReturn>,
	public IDispatchImpl<ITimeReturn, &IID_ITimeReturn, &LIBID_DCF_COMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CTimeReturn()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TIMERETURN)


BEGIN_COM_MAP(CTimeReturn)
	COM_INTERFACE_ENTRY(ITimeReturn)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(TimeWeightRateRuturn)(VARIANT Valueflow, SHORT Years, DOUBLE* TWRR_Return);
};

OBJECT_ENTRY_AUTO(__uuidof(TimeReturn), CTimeReturn)
