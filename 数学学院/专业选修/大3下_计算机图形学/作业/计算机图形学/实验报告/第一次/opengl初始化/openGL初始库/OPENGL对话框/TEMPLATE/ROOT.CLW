; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COpenGL
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "$$root$$.h"

ClassCount=4
Class1=C$$Safe_root$$App
Class2=C$$Safe_root$$Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_$$SAFE_ROOT$$_DIALOG
Class4=COpenGL

[CLS:C$$Safe_root$$App]
Type=0
HeaderFile=$$root$$.h
ImplementationFile=$$root$$.cpp
Filter=N

[CLS:C$$Safe_root$$Dlg]
Type=0
HeaderFile=$$root$$Dlg.h
ImplementationFile=$$root$$Dlg.cpp
Filter=D

[CLS:CAboutDlg]
Type=0
HeaderFile=$$root$$Dlg.h
ImplementationFile=$$root$$Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_$$SAFE_ROOT$$_DIALOG]
Type=1
Class=C$$Safe_root$$Dlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:COpenGL]
Type=0
HeaderFile=OpenGL.h
ImplementationFile=OpenGL.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=COpenGL

