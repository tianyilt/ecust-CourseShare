# Microsoft Developer Studio Generated NMAKE File, Based on OpenGL对话框.dsp
!IF $(CFG)" == "
CFG=OpenGL对话框 - Win32 Pseudo-Debug
!MESSAGE No configuration specified. Defaulting to OpenGL对话框 - Win32 Pseudo-Debug.
!ENDIF 

!IF "$(CFG)" != "OpenGL对话框 - Win32 Release" && "$(CFG)" != "OpenGL对话框 - Win32 Pseudo-Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenGL对话框.mak" CFG="OpenGL对话框 - Win32 Pseudo-Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenGL对话框 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGL对话框 - Win32 Pseudo-Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "OpenGL对话框 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\OpenGL对话框.awx" "D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL对话框.awx"


CLEAN :
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\OpenGL对话框.obj"
	-@erase "$(INTDIR)\OpenGL对话框.pch"
	-@erase "$(INTDIR)\OpenGL对话框.res"
	-@erase "$(INTDIR)\OpenGL对话框Aw.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OpenGL对话框.awx"
	-@erase "$(OUTDIR)\OpenGL对话框.exp"
	-@erase "$(OUTDIR)\OpenGL对话框.lib"
	-@erase "D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL对话框.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\OpenGL对话框.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\OpenGL对话框.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenGL对话框.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\OpenGL对话框.pdb" /machine:I386 /out:"$(OUTDIR)\OpenGL对话框.awx" /implib:"$(OUTDIR)\OpenGL对话框.lib" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\OpenGL对话框.obj" \
	"$(INTDIR)\OpenGL对话框Aw.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OpenGL对话框.res"

"$(OUTDIR)\OpenGL对话框.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\OpenGL对话框.awx
TargetName=OpenGL对话框
InputPath=.\Release\OpenGL对话框.awx
SOURCE="$(InputPath)"

"D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL对话框.awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
<< 
	

!ELSEIF  "$(CFG)" == "OpenGL对话框 - Win32 Pseudo-Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\OpenGL对话框.awx" "D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL对话框.awx"


CLEAN :
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\OpenGL对话框.obj"
	-@erase "$(INTDIR)\OpenGL对话框.pch"
	-@erase "$(INTDIR)\OpenGL对话框.res"
	-@erase "$(INTDIR)\OpenGL对话框Aw.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OpenGL对话框.awx"
	-@erase "$(OUTDIR)\OpenGL对话框.exp"
	-@erase "$(OUTDIR)\OpenGL对话框.ilk"
	-@erase "$(OUTDIR)\OpenGL对话框.lib"
	-@erase "$(OUTDIR)\OpenGL对话框.pdb"
	-@erase "D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL对话框.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\OpenGL对话框.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\OpenGL对话框.res" /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenGL对话框.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\OpenGL对话框.pdb" /debug /machine:I386 /out:"$(OUTDIR)\OpenGL对话框.awx" /implib:"$(OUTDIR)\OpenGL对话框.lib" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\OpenGL对话框.obj" \
	"$(INTDIR)\OpenGL对话框Aw.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OpenGL对话框.res"

"$(OUTDIR)\OpenGL对话框.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\OpenGL对话框.awx
TargetName=OpenGL对话框
InputPath=.\Debug\OpenGL对话框.awx
SOURCE="$(InputPath)"

"D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL对话框.awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("OpenGL对话框.dep")
!INCLUDE "OpenGL对话框.dep"
!ELSE 
!MESSAGE Warning: cannot find "OpenGL对话框.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OpenGL对话框 - Win32 Release" || "$(CFG)" == "OpenGL对话框 - Win32 Pseudo-Debug"
SOURCE=.\Debug.cpp

"$(INTDIR)\Debug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL对话框.pch"


SOURCE=".\OpenGL对话框.cpp"

"$(INTDIR)\OpenGL对话框.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL对话框.pch"


SOURCE=".\OpenGL对话框.rc"

"$(INTDIR)\OpenGL对话框.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=".\OpenGL对话框Aw.cpp"

"$(INTDIR)\OpenGL对话框Aw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL对话框.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "OpenGL对话框 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\OpenGL对话框.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OpenGL对话框.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OpenGL对话框 - Win32 Pseudo-Debug"

CPP_SWITCHES=/nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\OpenGL对话框.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OpenGL对话框.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Template\Dialog.cpp
SOURCE=.\Template\OpenGL.cpp
SOURCE=.\Template\root.cpp
SOURCE=.\Template\root.rc
SOURCE=.\Template\StdAfx.cpp

!ENDIF 

