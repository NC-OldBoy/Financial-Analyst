// Financial_ToolsDoc.cpp : CFinancial_ToolsDoc ���ʵ��
//

#include "stdafx.h"
#include "Financial_Tools.h"

#include "Financial_ToolsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFinancial_ToolsDoc

IMPLEMENT_DYNCREATE(CFinancial_ToolsDoc, CDocument)

BEGIN_MESSAGE_MAP(CFinancial_ToolsDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CFinancial_ToolsDoc::OnFileOpen)
END_MESSAGE_MAP()


// CFinancial_ToolsDoc ����/����
extern void _declspec(dllimport) ShowDlg_DiscountedCashFlow_DCF(ObjectCashFlow_Sheet Data);
extern void _declspec(dllimport) Create_DiscountedCashFlow_DCF();
extern void _declspec(dllimport) Refresh_DiscountedCashFlow_DCF(ObjectCashFlow_Sheet Data);
extern void _declspec(dllimport) ShowDlg_DiscountedCashFlow_TWRR(ObjectCashFlow_Sheet Data);
extern void _declspec(dllimport) Create_DiscountedCashFlow_TWRR();
extern void _declspec(dllimport) Refresh_DiscountedCashFlow_TWRR(ObjectCashFlow_Sheet Data);
extern BOOL _declspec(dllimport) Is_Dialog_Empty();
extern void _declspec(dllimport) Clear_Data(ObjectCashFlow_Sheet& Data);
CFinancial_ToolsDoc::CFinancial_ToolsDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CFinancial_ToolsDoc::~CFinancial_ToolsDoc()
{
}

BOOL CFinancial_ToolsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CFinancial_ToolsDoc ���л�

void CFinancial_ToolsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CFinancial_ToolsDoc ���

#ifdef _DEBUG
void CFinancial_ToolsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFinancial_ToolsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFinancial_ToolsDoc ����

void CFinancial_ToolsDoc::OnFileOpen()
{
	// TODO: �ڴ���������������
	CString FilePath;
	OpenTheFile(FilePath);
	if(Project_Sheet.Project_Num!=0||Project_Sheet.Years!=0)
		Clear_Data(Project_Sheet);
	GetExcelData(Project_Sheet,FilePath);
	if(Is_Dialog_Empty()==FALSE)
		Refresh_DiscountedCashFlow_DCF(Project_Sheet);
}

BOOL CFinancial_ToolsDoc::OpenTheFile(CString& FilePath)
{
	BOOL isOpen=TRUE;
	CString DefaultDir = L"C:\\";
	CString FileName = L"";         //Ĭ�ϴ򿪵��ļ��� 
	CString Filter = L"�ļ� (*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls;*.xlsx||";
	CFileDialog openFileDlg(isOpen, DefaultDir, FileName, OFN_HIDEREADONLY|OFN_READONLY, Filter, NULL); 
	INT_PTR result = openFileDlg.DoModal(); 
	if(result == IDOK) 
	{
		FilePath = openFileDlg.GetPathName();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CFinancial_ToolsDoc::GetExcelData(ObjectCashFlow_Sheet& Project_Sheet,const CString FilePath)
{
	CApplication app1;	
	CWorkbooks books;	
	CWorkbook book;	
	CWorksheets sheets;	
	CWorksheet sheet;	
	CRange range;	
	CRange iCell;	
	LPDISPATCH lpDisp;	
	  //COleVariant���Ƕ�VARIANT�ṹ�ķ�װ	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app1.CreateDispatch(_T("Excel.Application"), NULL))
	{
		AfxMessageBox(_T("�޷�����Excel������!"));
		return 0;
	}
	books.AttachDispatch(app1.get_Workbooks());
	lpDisp = books.Open(FilePath,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
	book.AttachDispatch(lpDisp);
	sheets.AttachDispatch(book.get_Worksheets());
	lpDisp = book.get_ActiveSheet();
	sheet.AttachDispatch(lpDisp);
	int Max_Rows,Max_Colums;
	Max_Rows=GetRowCount(sheet);
	Max_Colums=GetColumnsCount(sheet);
	for(int i=2;i<=Max_Rows;i+=2)
	{
		ObjectCashFlow project_tmp;
		for(int j=2;j<=Max_Colums;++j)
		{
			if(j==2)
				project_tmp.Project_Name=GetCellValueString(sheet,range,i,1);
			project_tmp.Project_OutFlow.insert(make_pair(GetCellValueString(sheet,range,1,j),GetCellValueDouble(sheet,range,i,j)));
			project_tmp.Project_InFlow.insert(make_pair(GetCellValueString(sheet,range,1,j),GetCellValueDouble(sheet,range,i+1,j)));
			project_tmp.Project.insert(make_pair(GetCellValueString(sheet,range,1,j),GetCellValueDouble(sheet,range,i+1,j)+GetCellValueDouble(sheet,range,i,j)));

		}
		Project_Sheet.Project_Sheet.insert(make_pair(project_tmp.Project_Name,project_tmp));
	}
	Project_Sheet.Project_Num=(Max_Rows-1)/2;
	Project_Sheet.Years=Max_Colums-1;
	books.Close();
	app1.Quit();
	range.ReleaseDispatch();	
	sheet.ReleaseDispatch();	
	sheets.ReleaseDispatch();	
	book.ReleaseDispatch();	
	books.ReleaseDispatch();	
	app1.ReleaseDispatch();
	return 1;
}

int CFinancial_ToolsDoc::GetRowCount(CWorksheet& iSheet)
{
	CRange usedRange; 
	usedRange.AttachDispatch(iSheet.get_UsedRange());	
	CRange range;     
	range.AttachDispatch(usedRange.get_Rows());	// �����Ŀ	
	int count = range.get_Count();	// �ͷ�	
	usedRange.ReleaseDispatch();	
	range.ReleaseDispatch();	// ����	
	return count;
}

int CFinancial_ToolsDoc::GetColumnsCount(CWorksheet& iSheet)
{
	CRange usedRange; 
	usedRange.AttachDispatch(iSheet.get_UsedRange());	
	CRange range;     
	range.AttachDispatch(usedRange.get_Columns());	// �����Ŀ	
	int count = range.get_Count();	// �ͷ�	
	usedRange.ReleaseDispatch();	
	range.ReleaseDispatch();	// ����	
	return count;
	return 0;
}

CString CFinancial_ToolsDoc::GetCellValueString(CWorksheet& iSheet,CRange& range,int row,int columns)
{
	range.AttachDispatch(iSheet.get_Cells());
	range.AttachDispatch(range.get_Item(COleVariant((long)row), COleVariant((long)columns)).pdispVal);   //��һ�������У��ڶ����������У����ڶ��е�һ��	vResult = range.get_Value2();
	COleVariant vResult;
	vResult = range.get_Value2();
	CString str = vResult.bstrVal;
	return str;
}

double CFinancial_ToolsDoc::GetCellValueDouble(CWorksheet& iSheet, CRange& range, int row, int columns)
{
	range.AttachDispatch(iSheet.get_Cells());
	range.AttachDispatch(range.get_Item(COleVariant((long)row), COleVariant((long)columns)).pdispVal);   //��һ�������У��ڶ����������У����ڶ��е�һ��	vResult = range.get_Value2();
	COleVariant vResult;
	vResult = range.get_Value2();
	double value = vResult.dblVal;
	return value;
}

ObjectCashFlow_Sheet* CFinancial_ToolsDoc::GetDocData(void)
{
	return &(this->Project_Sheet);
}
