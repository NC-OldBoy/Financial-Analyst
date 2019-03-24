// Financial_ToolsDoc.h : CFinancial_ToolsDoc ��Ľӿ�
//


#pragma once

#include "../ObjectCashFlow_Sheet/ObjectCashFlow_Sheet.h"

class CFinancial_ToolsDoc : public CDocument
{
protected: // �������л�����
	CFinancial_ToolsDoc();
	DECLARE_DYNCREATE(CFinancial_ToolsDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
// ʵ��
public:
	virtual ~CFinancial_ToolsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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


