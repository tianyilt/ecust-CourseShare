#if !defined(AFX_OPENGLAW_H__E075ED77_D2A0_44DC_BED3_3C7B5357B945__INCLUDED_)
#define AFX_OPENGLAW_H__E075ED77_D2A0_44DC_BED3_3C7B5357B945__INCLUDED_

// OpenGL单文档aw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see OpenGL单文档.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class COpenGLAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);
};

// This declares the one instance of the COpenGLAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global OpenGLaw.  (Its definition is in OpenGL单文档aw.cpp.)
extern COpenGLAppWiz OpenGLaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLAW_H__E075ED77_D2A0_44DC_BED3_3C7B5357B945__INCLUDED_)
