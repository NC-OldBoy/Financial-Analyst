// dllmain.cpp : DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "DCF_COM_i.h"
#include "dllmain.h"

CDCF_COMModule _AtlModule;

class CDCF_COMApp : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CDCF_COMApp, CWinApp)
END_MESSAGE_MAP()

CDCF_COMApp theApp;

BOOL CDCF_COMApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CDCF_COMApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
