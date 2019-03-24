// Financial_ToolsView.h : CFinancial_ToolsView 类的接口
//


#pragma once


class CFinancial_ToolsView : public CView
{
protected: // 仅从序列化创建
	CFinancial_ToolsView();
	DECLARE_DYNCREATE(CFinancial_ToolsView)

// 属性
public:
	CFinancial_ToolsDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CFinancial_ToolsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
};

#ifndef _DEBUG  // Financial_ToolsView.cpp 中的调试版本
inline CFinancial_ToolsDoc* CFinancial_ToolsView::GetDocument() const
   { return reinterpret_cast<CFinancial_ToolsDoc*>(m_pDocument); }
#endif

