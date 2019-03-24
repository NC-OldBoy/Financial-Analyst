// Financial_ToolsDoc.h : CFinancial_ToolsDoc 类的接口
//


#pragma once

#include "../ObjectCashFlow_Sheet/ObjectCashFlow_Sheet.h"

class CFinancial_ToolsDoc : public CDocument
{
protected: // 仅从序列化创建
	CFinancial_ToolsDoc();
	DECLARE_DYNCREATE(CFinancial_ToolsDoc)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
// 实现
public:
	virtual ~CFinancial_ToolsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	ObjectCashFlow_Sheet Project_Sheet;
	
	afx_msg void OnFileOpen();
	BOOL OpenTheFile(CString& FilePath);
	BOOL CFinancial_ToolsDoc::GetExcelData(ObjectCashFlow_Sheet& Project_Sheet,const CString FilePath);
	int GetRowCount(CWorksheet& iSheet);
	int GetColumnsCount(CWorksheet& iSheet);
	CString GetCellValueString(CWorksheet& iSheet,CRange& range,int row,int columns);
	double GetCellValueDouble(CWorksheet& iSheet, CRange& range, int row, int columns);
	ObjectCashFlow_Sheet* GetDocData(void);
};


