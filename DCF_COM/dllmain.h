// dllmain.h : 模块类的声明。

class CDCF_COMModule : public CAtlDllModuleT< CDCF_COMModule >
{
public :
	DECLARE_LIBID(LIBID_DCF_COMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DCF_COM, "{2FCAA4E5-37F9-4D3D-9785-5393422DC4FA}")
};

extern class CDCF_COMModule _AtlModule;
