# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=timer - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to timer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "timer - Win32 Release" && "$(CFG)" != "timer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "timer.mak" CFG="timer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "timer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "timer - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "timer - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "timer - Win32 Release"

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

ALL : "$(OUTDIR)\timer.exe"

CLEAN : 
	-@erase ".\Release\timer.exe"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\timer.obj"
	-@erase ".\Release\timer.pch"
	-@erase ".\Release\timerDlg.obj"
	-@erase ".\Release\DlgSetTimer.obj"
	-@erase ".\Release\timer.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/timer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/timer.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/timer.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 \msdev\lib\winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=\msdev\lib\winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/timer.pdb" /machine:I386 /out:"$(OUTDIR)/timer.exe" 
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/timer.obj" \
	"$(INTDIR)/timerDlg.obj" \
	"$(INTDIR)/DlgSetTimer.obj" \
	"$(INTDIR)/timer.res"

"$(OUTDIR)\timer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "timer - Win32 Debug"

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

ALL : "$(OUTDIR)\timer.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\timer.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\timer.exe"
	-@erase ".\Debug\timerDlg.obj"
	-@erase ".\Debug\DlgSetTimer.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\timer.obj"
	-@erase ".\Debug\timer.res"
	-@erase ".\Debug\timer.ilk"
	-@erase ".\Debug\timer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/timer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/timer.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/timer.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 \msdev\lib\winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=\msdev\lib\winmm.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/timer.pdb" /debug /machine:I386 /out:"$(OUTDIR)/timer.exe" 
LINK32_OBJS= \
	"$(INTDIR)/timerDlg.obj" \
	"$(INTDIR)/DlgSetTimer.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/timer.obj" \
	"$(INTDIR)/timer.res"

"$(OUTDIR)\timer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "timer - Win32 Release"
# Name "timer - Win32 Debug"

!IF  "$(CFG)" == "timer - Win32 Release"

!ELSEIF  "$(CFG)" == "timer - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "timer - Win32 Release"

!ELSEIF  "$(CFG)" == "timer - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\timer.cpp
DEP_CPP_TIMER=\
	".\StdAfx.h"\
	".\timer.h"\
	".\timerDlg.h"\
	

"$(INTDIR)\timer.obj" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"\
 "$(INTDIR)\timer.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\timerDlg.cpp

!IF  "$(CFG)" == "timer - Win32 Release"

DEP_CPP_TIMERD=\
	".\StdAfx.h"\
	".\timer.h"\
	".\timerDlg.h"\
	".\DlgSetTimer.h"\
	

"$(INTDIR)\timerDlg.obj" : $(SOURCE) $(DEP_CPP_TIMERD) "$(INTDIR)"\
 "$(INTDIR)\timer.pch"


!ELSEIF  "$(CFG)" == "timer - Win32 Debug"

DEP_CPP_TIMERD=\
	".\StdAfx.h"\
	".\timer.h"\
	".\timerDlg.h"\
	".\DlgSetTimer.h"\
	
NODEP_CPP_TIMERD=\
	".\CDlgSetTimer"\
	".\if"\
	

"$(INTDIR)\timerDlg.obj" : $(SOURCE) $(DEP_CPP_TIMERD) "$(INTDIR)"\
 "$(INTDIR)\timer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "timer - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/timer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\timer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "timer - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/timer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\timer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\timer.rc
DEP_RSC_TIMER_=\
	".\res\timer.ico"\
	".\res\timer.rc2"\
	

"$(INTDIR)\timer.res" : $(SOURCE) $(DEP_RSC_TIMER_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgSetTimer.cpp
DEP_CPP_DLGSE=\
	".\StdAfx.h"\
	".\timer.h"\
	".\DlgSetTimer.h"\
	

"$(INTDIR)\DlgSetTimer.obj" : $(SOURCE) $(DEP_CPP_DLGSE) "$(INTDIR)"\
 "$(INTDIR)\timer.pch"


# End Source File
# End Target
# End Project
################################################################################
