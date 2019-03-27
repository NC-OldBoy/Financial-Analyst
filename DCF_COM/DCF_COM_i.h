

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Mar 27 23:36:07 2019
 */
/* Compiler settings for .\DCF_COM.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DCF_COM_i_h__
#define __DCF_COM_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDCF_Tools_FWD_DEFINED__
#define __IDCF_Tools_FWD_DEFINED__
typedef interface IDCF_Tools IDCF_Tools;
#endif 	/* __IDCF_Tools_FWD_DEFINED__ */


#ifndef __DCF_Tools_FWD_DEFINED__
#define __DCF_Tools_FWD_DEFINED__

#ifdef __cplusplus
typedef class DCF_Tools DCF_Tools;
#else
typedef struct DCF_Tools DCF_Tools;
#endif /* __cplusplus */

#endif 	/* __DCF_Tools_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDCF_Tools_INTERFACE_DEFINED__
#define __IDCF_Tools_INTERFACE_DEFINED__

/* interface IDCF_Tools */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDCF_Tools;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B040A339-BBEC-491F-B151-2228DD10D3CC")
    IDCF_Tools : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NPV( 
            /* [in] */ DOUBLE r,
            /* [in] */ VARIANT CashFlow,
            /* [in] */ SHORT Years,
            /* [retval][out] */ DOUBLE *NPV_Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRR( 
            /* [in] */ VARIANT Cashflow,
            SHORT Years,
            /* [retval][out] */ DOUBLE *IRR_Return) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDCF_ToolsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDCF_Tools * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDCF_Tools * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDCF_Tools * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDCF_Tools * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDCF_Tools * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDCF_Tools * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDCF_Tools * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NPV )( 
            IDCF_Tools * This,
            /* [in] */ DOUBLE r,
            /* [in] */ VARIANT CashFlow,
            /* [in] */ SHORT Years,
            /* [retval][out] */ DOUBLE *NPV_Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IRR )( 
            IDCF_Tools * This,
            /* [in] */ VARIANT Cashflow,
            SHORT Years,
            /* [retval][out] */ DOUBLE *IRR_Return);
        
        END_INTERFACE
    } IDCF_ToolsVtbl;

    interface IDCF_Tools
    {
        CONST_VTBL struct IDCF_ToolsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDCF_Tools_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDCF_Tools_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDCF_Tools_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDCF_Tools_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDCF_Tools_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDCF_Tools_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDCF_Tools_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDCF_Tools_NPV(This,r,CashFlow,Years,NPV_Result)	\
    ( (This)->lpVtbl -> NPV(This,r,CashFlow,Years,NPV_Result) ) 

#define IDCF_Tools_IRR(This,Cashflow,Years,IRR_Return)	\
    ( (This)->lpVtbl -> IRR(This,Cashflow,Years,IRR_Return) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDCF_Tools_INTERFACE_DEFINED__ */



#ifndef __DCF_COMLib_LIBRARY_DEFINED__
#define __DCF_COMLib_LIBRARY_DEFINED__

/* library DCF_COMLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DCF_COMLib;

EXTERN_C const CLSID CLSID_DCF_Tools;

#ifdef __cplusplus

class DECLSPEC_UUID("03770159-705D-4EFB-B817-05FFA45F7F5A")
DCF_Tools;
#endif
#endif /* __DCF_COMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


