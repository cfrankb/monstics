# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MiniApp Reptel - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MiniApp Reptel - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "MiniApp Reptel - Win32 Release" && "$(CFG)" !=\
 "MiniApp Reptel - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MiniApp Reptel.mak" CFG="MiniApp Reptel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MiniApp Reptel - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MiniApp Reptel - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "MiniApp Reptel - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "MiniApp Reptel - Win32 Release"

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

ALL : "$(OUTDIR)\MiniApp Reptel.exe"

CLEAN : 
	-@erase ".\Release\MiniApp Reptel.exe"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\MiniApp Reptel.pch"
	-@erase ".\Release\MiniApp Reptel.obj"
	-@erase ".\Release\Entry.obj"
	-@erase ".\Release\EntryDlg.obj"
	-@erase ".\Release\IconListBox.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\ReptelView.obj"
	-@erase ".\Release\MADialog.obj"
	-@erase ".\Release\IconDlg.obj"
	-@erase ".\Release\ReptelDoc.obj"
	-@erase ".\Release\MiniApp Reptel.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MiniApp Reptel.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/MiniApp Reptel.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MiniApp Reptel.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/MiniApp Reptel.pdb" /machine:I386\
 /out:"$(OUTDIR)/MiniApp Reptel.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/MiniApp Reptel.obj" \
	"$(INTDIR)/Entry.obj" \
	"$(INTDIR)/EntryDlg.obj" \
	"$(INTDIR)/IconListBox.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ReptelView.obj" \
	"$(INTDIR)/MADialog.obj" \
	"$(INTDIR)/IconDlg.obj" \
	"$(INTDIR)/ReptelDoc.obj" \
	"$(INTDIR)/MiniApp Reptel.res"

"$(OUTDIR)\MiniApp Reptel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MiniApp Reptel - Win32 Debug"

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

ALL : "$(OUTDIR)\MiniApp Reptel.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\MiniApp Reptel.exe"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\MiniApp Reptel.pch"
	-@erase ".\Debug\MiniApp Reptel.obj"
	-@erase ".\Debug\MADialog.obj"
	-@erase ".\Debug\ReptelDoc.obj"
	-@erase ".\Debug\EntryDlg.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\ReptelView.obj"
	-@erase ".\Debug\Entry.obj"
	-@erase ".\Debug\IconListBox.obj"
	-@erase ".\Debug\IconDlg.obj"
	-@erase ".\Debug\MiniApp Reptel.res"
	-@erase ".\Debug\MiniApp Reptel.ilk"
	-@erase ".\Debug\MiniApp Reptel.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MiniApp Reptel.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/MiniApp Reptel.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MiniApp Reptel.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/MiniApp Reptel.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/MiniApp Reptel.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/MiniApp Reptel.obj" \
	"$(INTDIR)/MADialog.obj" \
	"$(INTDIR)/ReptelDoc.obj" \
	"$(INTDIR)/EntryDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ReptelView.obj" \
	"$(INTDIR)/Entry.obj" \
	"$(INTDIR)/IconListBox.obj" \
	"$(INTDIR)/IconDlg.obj" \
	"$(INTDIR)/MiniApp Reptel.res"

"$(OUTDIR)\MiniApp Reptel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MiniApp Reptel - Win32 Release"
# Name "MiniApp Reptel - Win32 Debug"

!IF  "$(CFG)" == "MiniApp Reptel - Win32 Release"

!ELSEIF  "$(CFG)" == "MiniApp Reptel - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MiniApp Reptel - Win32 Release"

!ELSEIF  "$(CFG)" == "MiniApp Reptel - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=".\MiniApp Reptel.cpp"
DEP_CPP_MINIA=\
	".\StdAfx.h"\
	".\MiniApp Reptel.h"\
	".\MainFrm.h"\
	".\ReptelDoc.h"\
	".\ReptelView.h"\
	

"$(INTDIR)\MiniApp Reptel.obj" : $(SOURCE) $(DEP_CPP_MINIA) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MiniApp Reptel - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MiniApp Reptel.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MiniApp Reptel.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MiniApp Reptel - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MiniApp Reptel.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MiniApp Reptel.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "MiniApp Reptel - Win32 Release"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\MiniApp Reptel.h"\
	".\Entry.h"\
	".\MainFrm.h"\
	
NODEP_CPP_MAINF=\
	".\{"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


!ELSEIF  "$(CFG)" == "MiniApp Reptel - Win32 Debug"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\MiniApp Reptel.h"\
	".\Entry.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ReptelDoc.cpp
DEP_CPP_REPTE=\
	".\StdAfx.h"\
	".\ReptelDoc.h"\
	".\Entry.h"\
	

"$(INTDIR)\ReptelDoc.obj" : $(SOURCE) $(DEP_CPP_REPTE) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ReptelView.cpp
DEP_CPP_REPTEL=\
	".\StdAfx.h"\
	".\ReptelDoc.h"\
	".\ReptelView.h"\
	".\EntryDlg.h"\
	".\Entry.h"\
	

"$(INTDIR)\ReptelView.obj" : $(SOURCE) $(DEP_CPP_REPTEL) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=".\MiniApp Reptel.rc"
DEP_RSC_MINIAP=\
	".\res\icon3.ico"\
	".\res\josiane_.ico"\
	".\res\yoannis.ico"\
	".\res\sophie_b.ico"\
	".\res\soldier.ico"\
	".\res\slalonde.ico"\
	".\res\s_belang.ico"\
	".\res\punk.ico"\
	".\res\prefonta.ico"\
	".\res\nancy.ico"\
	".\res\melanie.ico"\
	".\res\lepage.ico"\
	".\res\keroak.ico"\
	".\res\jlangl.ico"\
	".\res\jjean.ico"\
	".\res\ivone.ico"\
	".\res\hugo.ico"\
	".\res\diane.ico"\
	".\res\desjardi.ico"\
	".\res\claire.ico"\
	".\res\c_camplo.ico"\
	".\res\ReptelDoc.ico"\
	".\res\ico124.ico"\
	".\res\ico154.ico"\
	".\res\ico159.ico"\
	".\res\ico160.ico"\
	".\res\ico161.ico"\
	".\res\Toolbar.bmp"\
	".\res\MiniApp Reptel.ico"\
	".\res\icon0.ico"\
	".\res\icon1.ico"\
	".\res\icon2.ico"\
	".\res\ico136.ico"\
	".\res\ico152.ico"\
	".\res\ico168.ico"\
	".\res\ico311.ico"\
	".\res\ico313.ico"\
	".\res\ico00001.ico"\
	".\res\icon4.ico"\
	".\res\icon5.ico"\
	".\res\bitmap1.bmp"\
	".\res\MiniApp Reptel.rc2"\
	

"$(INTDIR)\MiniApp Reptel.res" : $(SOURCE) $(DEP_RSC_MINIAP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Entry.cpp
DEP_CPP_ENTRY=\
	".\StdAfx.h"\
	".\MiniApp Reptel.h"\
	".\Entry.h"\
	

"$(INTDIR)\Entry.obj" : $(SOURCE) $(DEP_CPP_ENTRY) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconListBox.cpp
DEP_CPP_ICONL=\
	".\StdAfx.h"\
	".\IconListBox.h"\
	
NODEP_CPP_ICONL=\
	".\struc98.h"\
	

"$(INTDIR)\IconListBox.obj" : $(SOURCE) $(DEP_CPP_ICONL) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EntryDlg.cpp
DEP_CPP_ENTRYD=\
	".\StdAfx.h"\
	".\MiniApp Reptel.h"\
	".\EntryDlg.h"\
	".\IconListBox.h"\
	".\IconDlg.h"\
	

"$(INTDIR)\EntryDlg.obj" : $(SOURCE) $(DEP_CPP_ENTRYD) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MADialog.cpp
DEP_CPP_MADIA=\
	".\StdAfx.h"\
	".\MADialog.h"\
	

"$(INTDIR)\MADialog.obj" : $(SOURCE) $(DEP_CPP_MADIA) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconDlg.cpp
DEP_CPP_ICOND=\
	".\StdAfx.h"\
	".\MiniApp Reptel.h"\
	".\IconListBox.h"\
	".\IconDlg.h"\
	
NODEP_CPP_ICOND=\
	".\struc98.h"\
	

"$(INTDIR)\IconDlg.obj" : $(SOURCE) $(DEP_CPP_ICOND) "$(INTDIR)"\
 "$(INTDIR)\MiniApp Reptel.pch"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section MiniApp Reptel : {B6805000-A509-11CE-A5B0-00AA006BBF16}
# 	1:21:IDR_POPUP_REPTEL_VIEW:102
# End Section
################################################################################
