// OpenGL对话框.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "OpenGL对话框.h"
#include "OpenGL对话框aw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE OpenGLDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("OPENGL对话框.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(OpenGLDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(OpenGLDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&OpenGLaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("OPENGL对话框.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(OpenGLDLL);
	}
	return 1;   // ok
}
