# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=progman32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to progman32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "progman32 - Win32 Release" && "$(CFG)" !=\
 "progman32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "progman32.mak" CFG="progman32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "progman32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "progman32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "progman32 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "progman32 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\progman32.exe"

CLEAN : 
	-@erase ".\Release\progman32.exe"
	-@erase ".\Release\file.obj"
	-@erase ".\Release\progman32.pch"
	-@erase ".\Release\IconArray.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\IconListBox.obj"
	-@erase ".\Release\DlgNewThing.obj"
	-@erase ".\Release\IconDlg.obj"
	-@erase ".\Release\helper.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\DlgGroup.obj"
	-@erase ".\Release\DlgProg.obj"
	-@erase ".\Release\IconWnd.obj"
	-@erase ".\Release\progman32Doc.obj"
	-@erase ".\Release\DlgRun.obj"
	-@erase ".\Release\DlgNewProg.obj"
	-@erase ".\Release\progman32.obj"
	-@erase ".\Release\progman32View.obj"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\autoarr.obj"
	-@erase ".\Release\progman32.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/progman32.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/progman32.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/progman32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/progman32.pdb" /machine:I386 /out:"$(OUTDIR)/progman32.exe" 
LINK32_OBJS= \
	"$(INTDIR)/file.obj" \
	"$(INTDIR)/IconArray.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/IconListBox.obj" \
	"$(INTDIR)/DlgNewThing.obj" \
	"$(INTDIR)/IconDlg.obj" \
	"$(INTDIR)/helper.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/DlgGroup.obj" \
	"$(INTDIR)/DlgProg.obj" \
	"$(INTDIR)/IconWnd.obj" \
	"$(INTDIR)/progman32Doc.obj" \
	"$(INTDIR)/DlgRun.obj" \
	"$(INTDIR)/DlgNewProg.obj" \
	"$(INTDIR)/progman32.obj" \
	"$(INTDIR)/progman32View.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/autoarr.obj" \
	"$(INTDIR)/progman32.res"

"$(OUTDIR)\progman32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\progman32.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\progman32.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\progman32.exe"
	-@erase ".\Debug\DlgGroup.obj"
	-@erase ".\Debug\DlgRun.obj"
	-@erase ".\Debug\IconArray.obj"
	-@erase ".\Debug\progman32View.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\IconListBox.obj"
	-@erase ".\Debug\IconDlg.obj"
	-@erase ".\Debug\autoarr.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\DlgProg.obj"
	-@erase ".\Debug\IconWnd.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\DlgNewThing.obj"
	-@erase ".\Debug\helper.obj"
	-@erase ".\Debug\file.obj"
	-@erase ".\Debug\progman32Doc.obj"
	-@erase ".\Debug\DlgNewProg.obj"
	-@erase ".\Debug\progman32.obj"
	-@erase ".\Debug\progman32.res"
	-@erase ".\Debug\progman32.ilk"
	-@erase ".\Debug\progman32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/progman32.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/progman32.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/progman32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/progman32.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/progman32.exe" 
LINK32_OBJS= \
	"$(INTDIR)/DlgGroup.obj" \
	"$(INTDIR)/DlgRun.obj" \
	"$(INTDIR)/IconArray.obj" \
	"$(INTDIR)/progman32View.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/IconListBox.obj" \
	"$(INTDIR)/IconDlg.obj" \
	"$(INTDIR)/autoarr.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/DlgProg.obj" \
	"$(INTDIR)/IconWnd.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/DlgNewThing.obj" \
	"$(INTDIR)/helper.obj" \
	"$(INTDIR)/file.obj" \
	"$(INTDIR)/progman32Doc.obj" \
	"$(INTDIR)/DlgNewProg.obj" \
	"$(INTDIR)/progman32.obj" \
	"$(INTDIR)/progman32.res"

"$(OUTDIR)\progman32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "progman32 - Win32 Release"
# Name "progman32 - Win32 Debug"

!IF  "$(CFG)" == "progman32 - Win32 Release"

!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "progman32 - Win32 Release"

!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\progman32.cpp

!IF  "$(CFG)" == "progman32 - Win32 Release"

DEP_CPP_PROGM=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\progman32Doc.h"\
	".\progman32View.h"\
	{$(INCLUDE)}"\autoarr.h"\
	".\..\..\EXTRA\COMMON\helper.h"\
	".\IconArray.h"\
	

"$(INTDIR)\progman32.obj" : $(SOURCE) $(DEP_CPP_PROGM) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

DEP_CPP_PROGM=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\progman32Doc.h"\
	".\progman32View.h"\
	".\IconArray.h"\
	

"$(INTDIR)\progman32.obj" : $(SOURCE) $(DEP_CPP_PROGM) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "progman32 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/progman32.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\progman32.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/progman32.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\progman32.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\MainFrm.h"\
	".\DlgGroup.h"\
	".\DlgNewProg.h"\
	".\DlgNewThing.h"\
	".\DlgRun.h"\
	{$(INCLUDE)}"\autoarr.h"\
	".\..\..\EXTRA\COMMON\helper.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "progman32 - Win32 Release"

DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\ChildFrm.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\ChildFrm.h"\
	
NODEP_CPP_CHILD=\
	".\WM_FILL_CHILD"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\progman32Doc.cpp

!IF  "$(CFG)" == "progman32 - Win32 Release"

DEP_CPP_PROGMA=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\progman32Doc.h"\
	".\IconArray.h"\
	

"$(INTDIR)\progman32Doc.obj" : $(SOURCE) $(DEP_CPP_PROGMA) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

DEP_CPP_PROGMA=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\progman32Doc.h"\
	".\IconArray.h"\
	
NODEP_CPP_PROGMA=\
	".\FORMAT_HEADER"\
	

"$(INTDIR)\progman32Doc.obj" : $(SOURCE) $(DEP_CPP_PROGMA) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\progman32View.cpp

!IF  "$(CFG)" == "progman32 - Win32 Release"

DEP_CPP_PROGMAN=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\progman32Doc.h"\
	".\progman32View.h"\
	".\DlgNewProg.h"\
	".\DlgNewThing.h"\
	".\DlgProg.h"\
	".\..\..\EXTRA\COMMON\helper.h"\
	".\IconArray.h"\
	

"$(INTDIR)\progman32View.obj" : $(SOURCE) $(DEP_CPP_PROGMAN) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

DEP_CPP_PROGMAN=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\progman32Doc.h"\
	".\progman32View.h"\
	".\DlgNewProg.h"\
	".\DlgNewThing.h"\
	".\DlgProg.h"\
	".\..\..\EXTRA\COMMON\helper.h"\
	".\IconArray.h"\
	
NODEP_CPP_PROGMAN=\
	".\.com"\
	

"$(INTDIR)\progman32View.obj" : $(SOURCE) $(DEP_CPP_PROGMAN) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\progman32.rc
DEP_RSC_PROGMAN3=\
	".\res\icon2.ico"\
	".\res\progman32Doc.ico"\
	".\res\uquestio.ico"\
	".\res\uwarning.ico"\
	".\res\icon1.ico"\
	".\res\msdosico.ico"\
	".\res\dataicon.ico"\
	".\res\msdospro.ico"\
	".\res\idr_main.ico"\
	".\res\Toolbar.bmp"\
	".\res\progman32.rc2"\
	

"$(INTDIR)\progman32.res" : $(SOURCE) $(DEP_RSC_PROGMAN3) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgGroup.cpp
DEP_CPP_DLGGR=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\DlgGroup.h"\
	

"$(INTDIR)\DlgGroup.obj" : $(SOURCE) $(DEP_CPP_DLGGR) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgNewProg.cpp
DEP_CPP_DLGNE=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\DlgNewProg.h"\
	

"$(INTDIR)\DlgNewProg.obj" : $(SOURCE) $(DEP_CPP_DLGNE) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgRun.cpp
DEP_CPP_DLGRU=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\DlgRun.h"\
	

"$(INTDIR)\DlgRun.obj" : $(SOURCE) $(DEP_CPP_DLGRU) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconDlg.cpp
DEP_CPP_ICOND=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\IconListBox.h"\
	".\IconDlg.h"\
	

"$(INTDIR)\IconDlg.obj" : $(SOURCE) $(DEP_CPP_ICOND) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconListBox.cpp

!IF  "$(CFG)" == "progman32 - Win32 Release"

DEP_CPP_ICONL=\
	".\StdAfx.h"\
	".\IconListBox.h"\
	

"$(INTDIR)\IconListBox.obj" : $(SOURCE) $(DEP_CPP_ICONL) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

DEP_CPP_ICONL=\
	".\StdAfx.h"\
	".\IconListBox.h"\
	
NODEP_CPP_ICONL=\
	".\struc98.h"\
	

"$(INTDIR)\IconListBox.obj" : $(SOURCE) $(DEP_CPP_ICONL) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconWnd.cpp
DEP_CPP_ICONW=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\IconWnd.h"\
	".\DlgNewProg.h"\
	{$(INCLUDE)}"\autoarr.h"\
	".\..\..\EXTRA\COMMON\helper.h"\
	

"$(INTDIR)\IconWnd.obj" : $(SOURCE) $(DEP_CPP_ICONW) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\extra\common\file.cpp
DEP_CPP_FILE_=\
	".\..\..\extra\common\stdafx.h"\
	".\..\..\extra\common\file.h"\
	

"$(INTDIR)\file.obj" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\extra\common\autoarr.cpp
DEP_CPP_AUTOA=\
	".\..\..\extra\common\stdafx.h"\
	{$(INCLUDE)}"\autoarr.h"\
	".\..\..\EXTRA\COMMON\helper.h"\
	

"$(INTDIR)\autoarr.obj" : $(SOURCE) $(DEP_CPP_AUTOA) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\extra\common\helper.cpp
DEP_CPP_HELPE=\
	".\..\..\extra\common\stdafx.h"\
	".\..\..\EXTRA\COMMON\helper.h"\
	

"$(INTDIR)\helper.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgNewThing.cpp
DEP_CPP_DLGNEW=\
	".\StdAfx.h"\
	".\DlgNewThing.h"\
	

"$(INTDIR)\DlgNewThing.obj" : $(SOURCE) $(DEP_CPP_DLGNEW) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconArray.cpp

!IF  "$(CFG)" == "progman32 - Win32 Release"

DEP_CPP_ICONA=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\IconArray.h"\
	

"$(INTDIR)\IconArray.obj" : $(SOURCE) $(DEP_CPP_ICONA) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ELSEIF  "$(CFG)" == "progman32 - Win32 Debug"

DEP_CPP_ICONA=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\IconArray.h"\
	
NODEP_CPP_ICONA=\
	".\Add"\
	

"$(INTDIR)\IconArray.obj" : $(SOURCE) $(DEP_CPP_ICONA) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgProg.cpp
DEP_CPP_DLGPR=\
	".\StdAfx.h"\
	".\progman32.h"\
	".\DlgProg.h"\
	".\IconDlg.h"\
	".\IconListBox.h"\
	

"$(INTDIR)\DlgProg.obj" : $(SOURCE) $(DEP_CPP_DLGPR) "$(INTDIR)"\
 "$(INTDIR)\progman32.pch"


# End Source File
# End Target
# End Project
################################################################################
