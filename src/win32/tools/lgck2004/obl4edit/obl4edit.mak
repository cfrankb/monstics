# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=obl4edit - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to obl4edit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "obl4edit - Win32 Release" && "$(CFG)" !=\
 "obl4edit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "obl4edit.mak" CFG="obl4edit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "obl4edit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "obl4edit - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "obl4edit - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "obl4edit - Win32 Release"

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

ALL : "$(OUTDIR)\obl4edit.exe" "$(OUTDIR)\_obl4edit.exe"

CLEAN : 
	-@erase ".\Release\_obl4edit.exe"
	-@erase ".\Release\obl4edit.exe"
	-@erase ".\Release\DlgSplitExport.obj"
	-@erase ".\Release\obl4edit.pch"
	-@erase ".\Release\Splash.obj"
	-@erase ".\Release\obl4edit.obj"
	-@erase ".\Release\DlgImportBmp.obj"
	-@erase ".\Release\BmpWrap.obj"
	-@erase ".\Release\obl4editDoc.obj"
	-@erase ".\Release\DlgImageSize.obj"
	-@erase ".\Release\DlgImportOBL.obj"
	-@erase ".\Release\OBL3Filter.obj"
	-@erase ".\Release\file.obj"
	-@erase ".\Release\ClrBox.obj"
	-@erase ".\Release\PreviewWnd.obj"
	-@erase ".\Release\SortArray.obj"
	-@erase ".\Release\DotArray.obj"
	-@erase ".\Release\ColorListBox.obj"
	-@erase ".\Release\obl4editView.obj"
	-@erase ".\Release\Dot.obj"
	-@erase ".\Release\common.obj"
	-@erase ".\Release\DlgPasteBmp.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\DlgExportPal.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\paldata.obj"
	-@erase ".\Release\ss3frame.obj"
	-@erase ".\Release\DlgExportBmp.obj"
	-@erase ".\Release\obl4edit.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/obl4edit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/obl4edit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/obl4edit.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib zlib.lib newmode.obj /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=ddraw.lib zlib.lib newmode.obj /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/obl4edit.pdb" /machine:I386\
 /out:"$(OUTDIR)/obl4edit.exe" 
LINK32_OBJS= \
	"$(INTDIR)/DlgSplitExport.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/obl4edit.obj" \
	"$(INTDIR)/DlgImportBmp.obj" \
	"$(INTDIR)/BmpWrap.obj" \
	"$(INTDIR)/obl4editDoc.obj" \
	"$(INTDIR)/DlgImageSize.obj" \
	"$(INTDIR)/DlgImportOBL.obj" \
	"$(INTDIR)/OBL3Filter.obj" \
	"$(INTDIR)/file.obj" \
	"$(INTDIR)/ClrBox.obj" \
	"$(INTDIR)/PreviewWnd.obj" \
	"$(INTDIR)/SortArray.obj" \
	"$(INTDIR)/DotArray.obj" \
	"$(INTDIR)/ColorListBox.obj" \
	"$(INTDIR)/obl4editView.obj" \
	"$(INTDIR)/Dot.obj" \
	"$(INTDIR)/common.obj" \
	"$(INTDIR)/DlgPasteBmp.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/DlgExportPal.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/paldata.obj" \
	"$(INTDIR)/ss3frame.obj" \
	"$(INTDIR)/DlgExportBmp.obj" \
	"$(INTDIR)/obl4edit.res"

"$(OUTDIR)\obl4edit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
InputDir=.\Release
InputPath=.\Release\obl4edit.exe
InputName=obl4edit
SOURCE=$(InputPath)

"$(InputDir)\_$(InputName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   petite -p0 -y $(InputPath) -o$(InputDir)\_$(InputName).exe

# End Custom Build

!ELSEIF  "$(CFG)" == "obl4edit - Win32 Debug"

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

ALL : "$(OUTDIR)\obl4edit.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\obl4edit.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\obl4edit.exe"
	-@erase ".\Debug\DotArray.obj"
	-@erase ".\Debug\Splash.obj"
	-@erase ".\Debug\DlgSplitExport.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\obl4edit.obj"
	-@erase ".\Debug\BmpWrap.obj"
	-@erase ".\Debug\OBL3Filter.obj"
	-@erase ".\Debug\DlgExportBmp.obj"
	-@erase ".\Debug\ClrBox.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\paldata.obj"
	-@erase ".\Debug\DlgImageSize.obj"
	-@erase ".\Debug\DlgImportOBL.obj"
	-@erase ".\Debug\obl4editDoc.obj"
	-@erase ".\Debug\DlgPasteBmp.obj"
	-@erase ".\Debug\common.obj"
	-@erase ".\Debug\PreviewWnd.obj"
	-@erase ".\Debug\ColorListBox.obj"
	-@erase ".\Debug\SortArray.obj"
	-@erase ".\Debug\obl4editView.obj"
	-@erase ".\Debug\DlgImportBmp.obj"
	-@erase ".\Debug\Dot.obj"
	-@erase ".\Debug\DlgExportPal.obj"
	-@erase ".\Debug\ss3frame.obj"
	-@erase ".\Debug\file.obj"
	-@erase ".\Debug\obl4edit.res"
	-@erase ".\Debug\obl4edit.ilk"
	-@erase ".\Debug\obl4edit.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/obl4edit.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/obl4edit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/obl4edit.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ddraw.lib zlib.lib newmode.obj /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /incremental:no
LINK32_FLAGS=ddraw.lib zlib.lib newmode.obj /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/obl4edit.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/obl4edit.exe" 
LINK32_OBJS= \
	"$(INTDIR)/DotArray.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/DlgSplitExport.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/obl4edit.obj" \
	"$(INTDIR)/BmpWrap.obj" \
	"$(INTDIR)/OBL3Filter.obj" \
	"$(INTDIR)/DlgExportBmp.obj" \
	"$(INTDIR)/ClrBox.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/paldata.obj" \
	"$(INTDIR)/DlgImageSize.obj" \
	"$(INTDIR)/DlgImportOBL.obj" \
	"$(INTDIR)/obl4editDoc.obj" \
	"$(INTDIR)/DlgPasteBmp.obj" \
	"$(INTDIR)/common.obj" \
	"$(INTDIR)/PreviewWnd.obj" \
	"$(INTDIR)/ColorListBox.obj" \
	"$(INTDIR)/SortArray.obj" \
	"$(INTDIR)/obl4editView.obj" \
	"$(INTDIR)/DlgImportBmp.obj" \
	"$(INTDIR)/Dot.obj" \
	"$(INTDIR)/DlgExportPal.obj" \
	"$(INTDIR)/ss3frame.obj" \
	"$(INTDIR)/file.obj" \
	"$(INTDIR)/obl4edit.res"

"$(OUTDIR)\obl4edit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "obl4edit - Win32 Release"
# Name "obl4edit - Win32 Debug"

!IF  "$(CFG)" == "obl4edit - Win32 Release"

!ELSEIF  "$(CFG)" == "obl4edit - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\obl4edit.cpp
DEP_CPP_OBL4E=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\MainFrm.h"\
	".\obl4editDoc.h"\
	".\obl4editView.h"\
	".\Splash.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	".\ClrBox.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\ColorListBox.h"\
	{$(INCLUDE)}"\OBL3Filter.h"\
	".\previewwnd.h"\
	".\DotArray.h"\
	".\Dot.h"\
	

"$(INTDIR)\obl4edit.obj" : $(SOURCE) $(DEP_CPP_OBL4E) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "obl4edit - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/obl4edit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\obl4edit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "obl4edit - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/obl4edit.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\obl4edit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\Splash.h"\
	{$(INCLUDE)}"\paldata.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	".\ClrBox.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\ColorListBox.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\obl4editDoc.cpp

!IF  "$(CFG)" == "obl4edit - Win32 Release"

DEP_CPP_OBL4ED=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\obl4editDoc.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\BmpWrap.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\DlgImportBmp.h"\
	".\DlgExportBmp.h"\
	".\DlgImportOBL.h"\
	".\DlgSplitExport.h"\
	{$(INCLUDE)}"\SortArray.h"\
	{$(INCLUDE)}"\paldata.h"\
	".\DlgExportPal.h"\
	{$(INCLUDE)}"\OBL3Filter.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	".\ClrBox.h"\
	".\ColorListBox.h"\
	

"$(INTDIR)\obl4editDoc.obj" : $(SOURCE) $(DEP_CPP_OBL4ED) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


!ELSEIF  "$(CFG)" == "obl4edit - Win32 Debug"

DEP_CPP_OBL4ED=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\obl4editDoc.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\BmpWrap.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\DlgImportBmp.h"\
	".\DlgExportBmp.h"\
	".\DlgImportOBL.h"\
	".\DlgSplitExport.h"\
	{$(INCLUDE)}"\SortArray.h"\
	{$(INCLUDE)}"\paldata.h"\
	".\DlgExportPal.h"\
	{$(INCLUDE)}"\OBL3Filter.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	".\ClrBox.h"\
	".\ColorListBox.h"\
	
NODEP_CPP_OBL4ED=\
	".\pWnd"\
	

"$(INTDIR)\obl4editDoc.obj" : $(SOURCE) $(DEP_CPP_OBL4ED) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obl4edit.rc
DEP_RSC_OBL4EDI=\
	".\res\obl4editDoc.ico"\
	".\res\obl4edit.ico"\
	".\res\Toolbar.bmp"\
	".\res\flood.cur"\
	".\res\colorsel.cur"\
	".\res\Splsh16.bmp"\
	".\res\pen.cur"\
	".\res\obl4edit.rc2"\
	

"$(INTDIR)\obl4edit.res" : $(SOURCE) $(DEP_RSC_OBL4EDI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dot.cpp
DEP_CPP_DOT_C=\
	".\StdAfx.h"\
	".\Dot.h"\
	

"$(INTDIR)\Dot.obj" : $(SOURCE) $(DEP_CPP_DOT_C) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DotArray.cpp
DEP_CPP_DOTAR=\
	".\StdAfx.h"\
	".\DotArray.h"\
	".\Dot.h"\
	

"$(INTDIR)\DotArray.obj" : $(SOURCE) $(DEP_CPP_DOTAR) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ClrBox.cpp
DEP_CPP_CLRBO=\
	".\StdAfx.h"\
	".\ClrBox.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\ColorListBox.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	{$(INCLUDE)}"\Draw.h"\
	

"$(INTDIR)\ClrBox.obj" : $(SOURCE) $(DEP_CPP_CLRBO) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorListBox.cpp
DEP_CPP_COLOR=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\ColorListBox.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	".\ClrBox.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Draw.h"\
	

"$(INTDIR)\ColorListBox.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PreviewWnd.cpp
DEP_CPP_PREVI=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\previewwnd.h"\
	".\MainFrm.h"\
	".\obl4editDoc.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	".\ClrBox.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\ColorListBox.h"\
	{$(INCLUDE)}"\OBL3Filter.h"\
	

"$(INTDIR)\PreviewWnd.obj" : $(SOURCE) $(DEP_CPP_PREVI) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgSplitExport.cpp
DEP_CPP_DLGSP=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\DlgSplitExport.h"\
	".\obl4editDoc.h"\
	{$(INCLUDE)}"\OBL3Filter.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	

"$(INTDIR)\DlgSplitExport.obj" : $(SOURCE) $(DEP_CPP_DLGSP) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgImportBmp.cpp
DEP_CPP_DLGIM=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\DlgImportBmp.h"\
	

"$(INTDIR)\DlgImportBmp.obj" : $(SOURCE) $(DEP_CPP_DLGIM) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\obl4editView.cpp
DEP_CPP_OBL4EDIT=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	{$(INCLUDE)}"\OBL3Filter.h"\
	".\obl4editDoc.h"\
	".\obl4editView.h"\
	".\DlgImageSize.h"\
	".\DlgPasteBmp.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\previewwnd.h"\
	".\DotArray.h"\
	".\Dot.h"\
	".\ClrBox.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\ColorListBox.h"\
	

"$(INTDIR)\obl4editView.obj" : $(SOURCE) $(DEP_CPP_OBL4EDIT) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgExportBmp.cpp
DEP_CPP_DLGEX=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\DlgExportBmp.h"\
	".\obl4editDoc.h"\
	{$(INCLUDE)}"\OBL3Filter.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	

"$(INTDIR)\DlgExportBmp.obj" : $(SOURCE) $(DEP_CPP_DLGEX) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgPasteBmp.cpp
DEP_CPP_DLGPA=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\DlgPasteBmp.h"\
	

"$(INTDIR)\DlgPasteBmp.obj" : $(SOURCE) $(DEP_CPP_DLGPA) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgImportOBL.cpp
DEP_CPP_DLGIMP=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\DlgImportOBL.h"\
	

"$(INTDIR)\DlgImportOBL.obj" : $(SOURCE) $(DEP_CPP_DLGIMP) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgImageSize.cpp
DEP_CPP_DLGIMA=\
	".\StdAfx.h"\
	".\obl4edit.h"\
	".\DlgImageSize.h"\
	

"$(INTDIR)\DlgImageSize.obj" : $(SOURCE) $(DEP_CPP_DLGIMA) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Splash.cpp
DEP_CPP_SPLAS=\
	".\StdAfx.h"\
	".\Splash.h"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\OBL3Filter.cpp

!IF  "$(CFG)" == "obl4edit - Win32 Release"

DEP_CPP_OBL3F=\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\OBL3Filter.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	

"$(INTDIR)\OBL3Filter.obj" : $(SOURCE) $(DEP_CPP_OBL3F) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "obl4edit - Win32 Debug"

DEP_CPP_OBL3F=\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\OBL3Filter.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	
NODEP_CPP_OBL3F=\
	".\..\..\obl4_data\source\file"\
	

"$(INTDIR)\OBL3Filter.obj" : $(SOURCE) $(DEP_CPP_OBL3F) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\BmpWrap.cpp
DEP_CPP_BMPWR=\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\BmpWrap.h"\
	

"$(INTDIR)\BmpWrap.obj" : $(SOURCE) $(DEP_CPP_BMPWR) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\SortArray.cpp
DEP_CPP_SORTA=\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\SortArray.h"\
	

"$(INTDIR)\SortArray.obj" : $(SOURCE) $(DEP_CPP_SORTA) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\ss3frame.cpp

!IF  "$(CFG)" == "obl4edit - Win32 Release"

DEP_CPP_SS3FR=\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	{$(INCLUDE)}"\zlib.h"\
	".\..\..\EXTRA\INCLUDE\MYSQL\zconf.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\ss3frame.obj" : $(SOURCE) $(DEP_CPP_SS3FR) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "obl4edit - Win32 Debug"

DEP_CPP_SS3FR=\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\ss3frame.h"\
	{$(INCLUDE)}"\zlib.h"\
	".\..\..\EXTRA\INCLUDE\MYSQL\zconf.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	
NODEP_CPP_SS3FR=\
	".\..\..\obl4_data\source\, int nMode)"\
	

"$(INTDIR)\ss3frame.obj" : $(SOURCE) $(DEP_CPP_SS3FR) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\common.cpp
DEP_CPP_COMMO=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\common.h"\
	

"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\paldata.cpp
DEP_CPP_PALDA=\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\paldata.h"\
	".\..\..\obl4_data\source\common.h"\
	".\..\..\obl4_data\source\file.h"\
	{$(INCLUDE)}"\Draw.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\paldata.obj" : $(SOURCE) $(DEP_CPP_PALDA) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\file.cpp
DEP_CPP_FILE_=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\file.h"\
	

"$(INTDIR)\file.obj" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgExportPal.cpp
DEP_CPP_DLGEXP=\
	".\StdAfx.h"\
	".\DlgExportPal.h"\
	

"$(INTDIR)\DlgExportPal.obj" : $(SOURCE) $(DEP_CPP_DLGEXP) "$(INTDIR)"\
 "$(INTDIR)\obl4edit.pch"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section obl4edit : {3383B134-64C1-11D2-B9A9-BCDE05C10000}
# 	0:8:Splash.h:C:\!Projet\Mfc\obl4edit\Splash.h
# 	0:10:Splash.cpp:C:\!Projet\Mfc\obl4edit\Splash.cpp
# 	1:10:IDB_SPLASH:104
# 	2:10:ResHdrName:resource.h
# 	2:11:ProjHdrName:stdafx.h
# 	2:10:WrapperDef:_SPLASH_SCRN_
# 	2:12:SplClassName:CSplashWnd
# 	2:21:SplashScreenInsertKey:4.0
# 	2:10:HeaderName:Splash.h
# 	2:10:ImplemName:Splash.cpp
# 	2:7:BmpID16:IDB_SPLASH
# End Section
################################################################################
################################################################################
# Section obl4edit : {B6805000-A509-11CE-A5B0-00AA006BBF16}
# 	1:26:CG_IDR_POPUP_OBL4EDIT_VIEW:102
# 	1:24:CG_IDR_POPUP_PREVIEW_WND:103
# End Section
################################################################################
