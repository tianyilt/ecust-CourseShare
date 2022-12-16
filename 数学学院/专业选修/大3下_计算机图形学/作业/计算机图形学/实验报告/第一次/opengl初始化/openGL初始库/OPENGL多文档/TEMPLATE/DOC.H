// $$root$$Doc.h : interface of the C$$Safe_root$$Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMDOPENGLDOC_H__2EA2AE24_6BAC_4C34_A5BC_4DE449FE25AC__INCLUDED_)
#define AFX_MYMDOPENGLDOC_H__2EA2AE24_6BAC_4C34_A5BC_4DE449FE25AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class C$$Safe_root$$Doc : public CDocument
{
protected: // create from serialization only
	C$$Safe_root$$Doc();
	DECLARE_DYNCREATE(C$$Safe_root$$Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C$$Safe_root$$Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C$$Safe_root$$Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C$$Safe_root$$Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMDOPENGLDOC_H__2EA2AE24_6BAC_4C34_A5BC_4DE449FE25AC__INCLUDED_)
