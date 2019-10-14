// $$root$$Doc.cpp : implementation of the C$$Safe_root$$Doc class
//

#include "stdafx.h"
#include "$$root$$.h"

#include "$$root$$Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$Doc

IMPLEMENT_DYNCREATE(C$$Safe_root$$Doc, CDocument)

BEGIN_MESSAGE_MAP(C$$Safe_root$$Doc, CDocument)
	//{{AFX_MSG_MAP(C$$Safe_root$$Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$Doc construction/destruction

C$$Safe_root$$Doc::C$$Safe_root$$Doc()
{
	// TODO: add one-time construction code here

}

C$$Safe_root$$Doc::~C$$Safe_root$$Doc()
{
}

BOOL C$$Safe_root$$Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$Doc serialization

void C$$Safe_root$$Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$Doc diagnostics

#ifdef _DEBUG
void C$$Safe_root$$Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void C$$Safe_root$$Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$Doc commands
