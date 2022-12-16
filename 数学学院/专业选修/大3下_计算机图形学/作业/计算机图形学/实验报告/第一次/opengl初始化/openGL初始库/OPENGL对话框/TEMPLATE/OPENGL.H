#if !defined(AFX_OPENGL_H__99E34DDC_206E_4E76_99C9_95271B2A801C__INCLUDED_)
#define AFX_OPENGL_H__99E34DDC_206E_4E76_99C9_95271B2A801C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenGL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenGL window

class COpenGL : public CWnd
{
// Construction
public:
	COpenGL();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGL)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGL();
////////////////////////////////////////////////////////////////
//添加的成员函数与成员变量
	int MySetPixelFormat(HDC hdc);
	void DrawColorBox(void);
	HDC hdc ;
	HGLRC hglrc;
	GLfloat step,s;
////////////////////////////////////////////////////////////////


	// Generated message map functions
protected:
	//{{AFX_MSG(COpenGL)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGL_H__99E34DDC_206E_4E76_99C9_95271B2A801C__INCLUDED_)
