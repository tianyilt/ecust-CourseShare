; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=C$$Safe_root$$View
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "$$root$$.h"
LastPage=0

ClassCount=7
Class1=C$$Safe_root$$App
Class2=C$$Safe_root$$Doc
Class3=C$$Safe_root$$View
Class4=CMainFrame
Class7=CGLEnabledView

ResourceCount=3
Resource1=IDR_$$DOC$$TYPE
Resource2=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDD_ABOUTBOX

[CLS:C$$Safe_root$$App]
Type=0
HeaderFile=$$root$$.h
ImplementationFile=$$root$$.cpp
Filter=N

[CLS:C$$Safe_root$$Doc]
Type=0
HeaderFile=$$root$$Doc.h
ImplementationFile=$$root$$Doc.cpp
Filter=N

[CLS:C$$Safe_root$$View]
Type=0
HeaderFile=$$root$$View.h
ImplementationFile=$$root$$View.cpp
Filter=C
LastObject=C$$Safe_root$$View
BaseClass=CGLEnabledView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=$$root$$.cpp
ImplementationFile=$$root$$.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_$$DOC$$TYPE]
Type=1
Class=C$$Safe_root$$View
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CGLEnabledView]
Type=0
HeaderFile=GLEnabledView.h
ImplementationFile=GLEnabledView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CGLEnabledView

