// Financial_ToolsDoc.cpp : CFinancial_ToolsDoc 类的实现
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


// CFinancial_ToolsDoc 构造/析构
extern void _declspec(dllimport) ShowDlg_DiscountedCashFlow(ObjectCashFlow_Sheet Data);
extern void _declspec(dllimport) Create_DiscountedCashFlow();
extern void _declspec(dllimport) Refresh_DiscountedCashFlow(ObjectCashFlow_Sheet Data);
extern BOOL _declspec(dllimport) Is_Dialog_Empty();
extern void _declspec(dllimport) Clear_Data(ObjectCashFlow_Sheet& Data);
CFinancial_ToolsDoc::CFinancial_ToolsDoc()
{
	// TODO: 在此添加一次性构造代码

}

CFinancial_ToolsDoc::~CFinancial_ToolsDoc()
{
}

BOOL CFinancial_ToolsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CFinancial_ToolsDoc 序列化

void CFinancial_ToolsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CFinancial_ToolsDoc 诊断

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


// CFinancial_ToolsDoc 命令

void CFinancial_ToolsDoc::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CString FilePath;
	OpenTheFile(FilePath);
	if(Project_Sheet.Project_Num!=0||Project_Sheet.Years!=0)
		Clear_Data(Project_Sheet);
	GetExcelData(Project_Sheet,FilePath);
	if(Is_Dialog_Empty()==FALSE)
		Refresh_DiscountedCashFlow(Project_Sheet);
}

BOOL CFinancial_ToolsDoc::OpenTheFile(CString& FilePath)
{
	BOOL isOpen=TRUE;
	CString DefaultDir = L"C:\\";
	CString FileName = L"";         //默认打开的文件名 
	CString Filter = L"文件 (*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls;*.xlsx||";
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
	  //COleVariant类是对VARIANT结构的封装	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app1.CreateDispatch(_T("Excel.Application"), NULL))
	{
		AfxMessageBox(_T("无法启动Excel服务器!"));
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
	for(int i=2;i<=Max_Rows;++i)
	{
		ObjectCashFlow project_tmp;
		for(int j=2;j<=Max_Colums;++j)
		{
			if(j==2)
				project_tmp.Project_Name=GetCellValueString(sheet,range,i,1);
			project_tmp.Project.insert(make_pair(GetCellValueString(sheet,range,1,j),GetCellValueDouble(sheet,range,i,j)));
		}
		Project_Sheet.Project_Sheet.insert(make_pair(project_tmp.Project_Name,project_tmp));
	}
	Project_Sheet.Project_Num=Max_Rows-1;
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
	range.AttachDispatch(usedRange.get_Rows());	// 获得数目	
	int count = range.get_Count();	// 释放	
	usedRange.ReleaseDispatch();	
	range.ReleaseDispatch();	// 返回	
	return count;
}

int CFinancial_ToolsDoc::GetColumnsCount(CWorksheet& iSheet)
{
	CRange usedRange; 
	usedRange.AttachDispatch(iSheet.get_UsedRange());	
	CRange range;     
	range.AttachDispatch(usedRange.get_Columns());	// 获得数目	
	int count = range.get_Count();	// 释放	
	usedRange.ReleaseDispatch();	
	range.ReleaseDispatch();	// 返回	
	return count;
	return 0;
}

CString CFinancial_ToolsDoc::GetCellValueString(CWorksheet& iSheet,CRange& range,int row,int columns)
{
	range.AttachDispatch(iSheet.get_Cells());
	range.AttachDispatch(range.get_Item(COleVariant((long)row), COleVariant((long)columns)).pdispVal);   //第一变量是行，第二个变量是列，即第二行第一列	vResult = range.get_Value2();
	COleVariant vResult;
	vResult = range.get_Value2();
	CString str = vResult.bstrVal;
	return str;
}

double CFinancial_ToolsDoc::GetCellValueDouble(CWorksheet& iSheet, CRange& range, int row, int columns)
{
	range.AttachDispatch(iSheet.get_Cells());
	range.AttachDispatch(range.get_Item(COleVariant((long)row), COleVariant((long)columns)).pdispVal);   //第一变量是行，第二个变量是列，即第二行第一列	vResult = range.get_Value2();
	COleVariant vResult;
	vResult = range.get_Value2();
	double value = vResult.dblVal;
	return value;
}

ObjectCashFlow_Sheet* CFinancial_ToolsDoc::GetDocData(void)
{
	return &(this->Project_Sheet);
}
