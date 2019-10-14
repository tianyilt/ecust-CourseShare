// shortest.h : main header file for the SHORTEST application
//

#if !defined(AFX_SHORTEST_H__EA2C08E6_4709_42E9_BD4A_7C959238B0A3__INCLUDED_)
#define AFX_SHORTEST_H__EA2C08E6_4709_42E9_BD4A_7C959238B0A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShortestApp:
// See shortest.cpp for the implementation of this class
//

class CShortestApp : public CWinApp
{
public:
	CShortestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShortestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTEST_H__EA2C08E6_4709_42E9_BD4A_7C959238B0A3__INCLUDED_)
