// $$root$$View.h : interface of the C$$Safe_root$$View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMDOPENGLVIEW_H__127960DD_48CD_46AE_8514_722C40289CF3__INCLUDED_)
#define AFX_MYMDOPENGLVIEW_H__127960DD_48CD_46AE_8514_722C40289CF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
////////////////////////////////////////////////////////////////////////////////
//包含类CGLEnabledView的说明文件
#include "GLEnabledView.h"
////////////////////////////////////////////////////////////////////////////////

class C$$Safe_root$$View : public CGLEnabledView
{
protected: // create from serialization only
	C$$Safe_root$$View();
	DECLARE_DYNCREATE(C$$Safe_root$$View)

// Attributes
public:
	C$$Safe_root$$Doc* GetDocument();

// Operations
public:
//////////////////////////////////////////////////////////////////////////////////////
//改写CGLEnabledView类的场景绘制虚函数
	void OnDrawGL();
//////////////////////////////////////////////////////////////////////////////////////

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C$$Safe_root$$View)
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C$$Safe_root$$View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C$$Safe_root$$View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////
//添加私有成员变量
private:
	CPoint MouseDownPoint;
	double X_Angle;
	double Y_Angle;
////////////////////////////////////////////////////////////////////////////////

};

#ifndef _DEBUG  // debug version in $$root$$View.cpp
inline C$$Safe_root$$Doc* C$$Safe_root$$View::GetDocument()
   { return (C$$Safe_root$$Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMDOPENGLVIEW_H__127960DD_48CD_46AE_8514_722C40289CF3__INCLUDED_)
