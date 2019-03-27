// DCF_Tools.h : CDCF_Tools ������

#pragma once
#include "resource.h"       // ������

#include "DCF_COM_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CDCF_Tools

class ATL_NO_VTABLE CDCF_Tools :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDCF_Tools, &CLSID_DCF_Tools>,
	public IDispatchImpl<IDCF_Tools, &IID_IDCF_Tools, &LIBID_DCF_COMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDCF_Tools()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DCF_TOOLS)


BEGIN_COM_MAP(CDCF_Tools)
	COM_INTERFACE_ENTRY(IDCF_Tools)
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


	STDMETHOD(NPV)(DOUBLE r, VARIANT CashFlow, SHORT Years, DOUBLE* NPV_Result);
	STDMETHOD(IRR)(VARIANT Cashflow, SHORT Years, DOUBLE* IRR_Return);
};

OBJECT_ENTRY_AUTO(__uuidof(DCF_Tools), CDCF_Tools)
