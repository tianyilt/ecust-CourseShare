# Microsoft Developer Studio Generated NMAKE File, Based on OpenGL多文档.dsp
!IF $(CFG)" == "
CFG=OpenGL多文档 - Win32 Pseudo-Debug
!MESSAGE No configuration specified. Defaulting to OpenGL多文档 - Win32 Pseudo-Debug.
!ENDIF 

!IF "$(CFG)" != "OpenGL多文档 - Win32 Release" && "$(CFG)" != "OpenGL多文档 - Win32 Pseudo-Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenGL多文档.mak" CFG="OpenGL多文档 - Win32 Pseudo-Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenGL多文档 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGL多文档 - Win32 Pseudo-Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "OpenGL多文档 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\OpenGL多文档.awx" "D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL多文档.awx"


CLEAN :
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\OpenGL多文档.obj"
	-@erase "$(INTDIR)\OpenGL多文档.pch"
	-@erase "$(INTDIR)\OpenGL多文档.res"
	-@erase "$(INTDIR)\OpenGL多文档Aw.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OpenGL多文档.awx"
	-@erase "$(OUTDIR)\OpenGL多文档.exp"
	-@erase "$(OUTDIR)\OpenGL多文档.lib"
	-@erase "D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL多文档.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\OpenGL多文档.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\OpenGL多文档.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenGL多文档.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\OpenGL多文档.pdb" /machine:I386 /out:"$(OUTDIR)\OpenGL多文档.awx" /implib:"$(OUTDIR)\OpenGL多文档.lib" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\OpenGL多文档.obj" \
	"$(INTDIR)\OpenGL多文档Aw.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OpenGL多文档.res"

"$(OUTDIR)\OpenGL多文档.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\OpenGL多文档.awx
TargetName=OpenGL多文档
InputPath=.\Release\OpenGL多文档.awx
SOURCE="$(InputPath)"

"D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL多文档.awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
<< 
	

!ELSEIF  "$(CFG)" == "OpenGL多文档 - Win32 Pseudo-Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\OpenGL多文档.awx" "D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL多文档.awx"


CLEAN :
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\OpenGL多文档.obj"
	-@erase "$(INTDIR)\OpenGL多文档.pch"
	-@erase "$(INTDIR)\OpenGL多文档.res"
	-@erase "$(INTDIR)\OpenGL多文档Aw.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OpenGL多文档.awx"
	-@erase "$(OUTDIR)\OpenGL多文档.exp"
	-@erase "$(OUTDIR)\OpenGL多文档.ilk"
	-@erase "$(OUTDIR)\OpenGL多文档.lib"
	-@erase "$(OUTDIR)\OpenGL多文档.pdb"
	-@erase "D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL多文档.awx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\OpenGL多文档.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\OpenGL多文档.res" /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OpenGL多文档.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\OpenGL多文档.pdb" /debug /machine:I386 /out:"$(OUTDIR)\OpenGL多文档.awx" /implib:"$(OUTDIR)\OpenGL多文档.lib" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\OpenGL多文档.obj" \
	"$(INTDIR)\OpenGL多文档Aw.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OpenGL多文档.res"

"$(OUTDIR)\OpenGL多文档.awx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\OpenGL多文档.awx
TargetName=OpenGL多文档
InputPath=.\Debug\OpenGL多文档.awx
SOURCE="$(InputPath)"

"D:\program files\Microsoft Visual Studio\Common\MSDev98\Template\OpenGL多文档.awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("OpenGL多文档.dep")
!INCLUDE "OpenGL多文档.dep"
!ELSE 
!MESSAGE Warning: cannot find "OpenGL多文档.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OpenGL多文档 - Win32 Release" || "$(CFG)" == "OpenGL多文档 - Win32 Pseudo-Debug"
SOURCE=.\Debug.cpp

"$(INTDIR)\Debug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL多文档.pch"


SOURCE=".\OpenGL多文档.cpp"

"$(INTDIR)\OpenGL多文档.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL多文档.pch"


SOURCE=".\OpenGL多文档.rc"

"$(INTDIR)\OpenGL多文档.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=".\OpenGL多文档Aw.cpp"

"$(INTDIR)\OpenGL多文档Aw.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OpenGL多文档.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "OpenGL多文档 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\OpenGL多文档.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OpenGL多文档.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OpenGL多文档 - Win32 Pseudo-Debug"

CPP_SWITCHES=/nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\OpenGL多文档.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OpenGL多文档.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Template\ChildFrm.cpp
SOURCE=.\Template\Doc.cpp
SOURCE=.\Template\GLEnabledView.cpp
SOURCE=.\Template\MainFrm.cpp
SOURCE=.\Template\root.cpp
SOURCE=.\Template\root.rc
SOURCE=.\Template\StdAfx.cpp
SOURCE=.\Template\View.cpp

!ENDIF 

