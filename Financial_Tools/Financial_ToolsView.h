// Financial_ToolsView.h : CFinancial_ToolsView ��Ľӿ�
//


#pragma once


class CFinancial_ToolsView : public CView
{
protected: // �������л�����
	CFinancial_ToolsView();
	DECLARE_DYNCREATE(CFinancial_ToolsView)

// ����
public:
	CFinancial_ToolsDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CFinancial_ToolsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
};

#ifndef _DEBUG  // Financial_ToolsView.cpp �еĵ��԰汾
inline CFinancial_ToolsDoc* CFinancial_ToolsView::GetDocument() const
   { return reinterpret_cast<CFinancial_ToolsDoc*>(m_pDocument); }
#endif

