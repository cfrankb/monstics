# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=scr4edit_2 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to scr4edit_2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "scr4edit_2 - Win32 Release" && "$(CFG)" !=\
 "scr4edit_2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "scr4edit_2.mak" CFG="scr4edit_2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "scr4edit_2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "scr4edit_2 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "scr4edit_2 - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\scr4edit_2.exe"

CLEAN : 
	-@erase ".\Release\scr4edit_2.exe"
	-@erase ".\Release\scr4editDoc.obj"
	-@erase ".\Release\scr4edit.obj"
	-@erase ".\Release\strvalarray.obj"
	-@erase ".\Release\DlgTagEdit.obj"
	-@erase ".\Release\DbPage4.obj"
	-@erase ".\Release\obl3array.obj"
	-@erase ".\Release\GameFile3.obj"
	-@erase ".\Release\SortArray.obj"
	-@erase ".\Release\reverse.obj"
	-@erase ".\Release\DlgExportPal.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\ProtoPage2.obj"
	-@erase ".\Release\DlgClassList.obj"
	-@erase ".\Release\DlgIntArray.obj"
	-@erase ".\Release\DlgObjectsList.obj"
	-@erase ".\Release\DbPage3.obj"
	-@erase ".\Release\ExtraData.obj"
	-@erase ".\Release\GameSettings.obj"
	-@erase ".\Release\Splash.obj"
	-@erase ".\Release\StrVal.obj"
	-@erase ".\Release\DlgFrameEdit.obj"
	-@erase ".\Release\SndArray.obj"
	-@erase ".\Release\DlgTagList.obj"
	-@erase ".\Release\extracore.obj"
	-@erase ".\Release\DlgMoveLevel.obj"
	-@erase ".\Release\lgckarr.obj"
	-@erase ".\Release\ProtoPage1.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\proto.obj"
	-@erase ".\Release\Stack.obj"
	-@erase ".\Release\Snd.obj"
	-@erase ".\Release\extraarray.obj"
	-@erase ".\Release\DlgObjectsMain.obj"
	-@erase ".\Release\Module3.obj"
	-@erase ".\Release\shared.obj"
	-@erase ".\Release\DbPage2.obj"
	-@erase ".\Release\DbSheet.obj"
	-@erase ".\Release\ProtoPage5.obj"
	-@erase ".\Release\file.obj"
	-@erase ".\Release\scr4editView.obj"
	-@erase ".\Release\DlgFrameList.obj"
	-@erase ".\Release\scriptentry.obj"
	-@erase ".\Release\BmpWrap.obj"
	-@erase ".\Release\OBL3Filter.obj"
	-@erase ".\Release\DlgIntAll.obj"
	-@erase ".\Release\scriptarray.obj"
	-@erase ".\Release\DlgObjsWiz.obj"
	-@erase ".\Release\DbPage1.obj"
	-@erase ".\Release\ss3frame.obj"
	-@erase ".\Release\DlgNameDesc.obj"
	-@erase ".\Release\ProtoPage4.obj"
	-@erase ".\Release\ProtoSheet.obj"
	-@erase ".\Release\paldata.obj"
	-@erase ".\Release\TagEntry.obj"
	-@erase ".\Release\common.obj"
	-@erase ".\Release\DlgEditLocal.obj"
	-@erase ".\Release\DlgIntBox.obj"
	-@erase ".\Release\lgckcmd.obj"
	-@erase ".\Release\TagArray.obj"
	-@erase ".\Release\DlgMessageBox.obj"
	-@erase ".\Release\DlgClassedit.obj"
	-@erase ".\Release\ProtoPage3.obj"
	-@erase ".\Release\protoarray.obj"
	-@erase ".\Release\scr4edit.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/scr4edit_2.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "NDEBUG"
# ADD RSC /l 0xc0c /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/scr4edit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/scr4edit_2.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib zlib.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=ddraw.lib zlib.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/scr4edit_2.pdb" /machine:I386 /out:"$(OUTDIR)/scr4edit_2.exe" 
LINK32_OBJS= \
	"$(INTDIR)/scr4editDoc.obj" \
	"$(INTDIR)/scr4edit.obj" \
	"$(INTDIR)/strvalarray.obj" \
	"$(INTDIR)/DlgTagEdit.obj" \
	"$(INTDIR)/DbPage4.obj" \
	"$(INTDIR)/obl3array.obj" \
	"$(INTDIR)/GameFile3.obj" \
	"$(INTDIR)/SortArray.obj" \
	"$(INTDIR)/reverse.obj" \
	"$(INTDIR)/DlgExportPal.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ProtoPage2.obj" \
	"$(INTDIR)/DlgClassList.obj" \
	"$(INTDIR)/DlgIntArray.obj" \
	"$(INTDIR)/DlgObjectsList.obj" \
	"$(INTDIR)/DbPage3.obj" \
	"$(INTDIR)/ExtraData.obj" \
	"$(INTDIR)/GameSettings.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/StrVal.obj" \
	"$(INTDIR)/DlgFrameEdit.obj" \
	"$(INTDIR)/SndArray.obj" \
	"$(INTDIR)/DlgTagList.obj" \
	"$(INTDIR)/extracore.obj" \
	"$(INTDIR)/DlgMoveLevel.obj" \
	"$(INTDIR)/lgckarr.obj" \
	"$(INTDIR)/ProtoPage1.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/proto.obj" \
	"$(INTDIR)/Stack.obj" \
	"$(INTDIR)/Snd.obj" \
	"$(INTDIR)/extraarray.obj" \
	"$(INTDIR)/DlgObjectsMain.obj" \
	"$(INTDIR)/Module3.obj" \
	"$(INTDIR)/shared.obj" \
	"$(INTDIR)/DbPage2.obj" \
	"$(INTDIR)/DbSheet.obj" \
	"$(INTDIR)/ProtoPage5.obj" \
	"$(INTDIR)/file.obj" \
	"$(INTDIR)/scr4editView.obj" \
	"$(INTDIR)/DlgFrameList.obj" \
	"$(INTDIR)/scriptentry.obj" \
	"$(INTDIR)/BmpWrap.obj" \
	"$(INTDIR)/OBL3Filter.obj" \
	"$(INTDIR)/DlgIntAll.obj" \
	"$(INTDIR)/scriptarray.obj" \
	"$(INTDIR)/DlgObjsWiz.obj" \
	"$(INTDIR)/DbPage1.obj" \
	"$(INTDIR)/ss3frame.obj" \
	"$(INTDIR)/DlgNameDesc.obj" \
	"$(INTDIR)/ProtoPage4.obj" \
	"$(INTDIR)/ProtoSheet.obj" \
	"$(INTDIR)/paldata.obj" \
	"$(INTDIR)/TagEntry.obj" \
	"$(INTDIR)/common.obj" \
	"$(INTDIR)/DlgEditLocal.obj" \
	"$(INTDIR)/DlgIntBox.obj" \
	"$(INTDIR)/lgckcmd.obj" \
	"$(INTDIR)/TagArray.obj" \
	"$(INTDIR)/DlgMessageBox.obj" \
	"$(INTDIR)/DlgClassedit.obj" \
	"$(INTDIR)/ProtoPage3.obj" \
	"$(INTDIR)/protoarray.obj" \
	"$(INTDIR)/scr4edit.res"

"$(OUTDIR)\scr4edit_2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\scr4edit_2.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\scr4edit_2.exe"
	-@erase ".\Debug\scr4edit.obj"
	-@erase ".\Debug\scriptentry.obj"
	-@erase ".\Debug\DbPage1.obj"
	-@erase ".\Debug\ExtraData.obj"
	-@erase ".\Debug\ProtoPage5.obj"
	-@erase ".\Debug\DlgObjectsList.obj"
	-@erase ".\Debug\protoarray.obj"
	-@erase ".\Debug\DlgIntBox.obj"
	-@erase ".\Debug\scriptarray.obj"
	-@erase ".\Debug\OBL3Filter.obj"
	-@erase ".\Debug\DlgNameDesc.obj"
	-@erase ".\Debug\TagEntry.obj"
	-@erase ".\Debug\Module3.obj"
	-@erase ".\Debug\DlgObjsWiz.obj"
	-@erase ".\Debug\DlgExportPal.obj"
	-@erase ".\Debug\obl3array.obj"
	-@erase ".\Debug\ProtoPage4.obj"
	-@erase ".\Debug\GameFile3.obj"
	-@erase ".\Debug\SortArray.obj"
	-@erase ".\Debug\ProtoSheet.obj"
	-@erase ".\Debug\common.obj"
	-@erase ".\Debug\Snd.obj"
	-@erase ".\Debug\file.obj"
	-@erase ".\Debug\DbPage4.obj"
	-@erase ".\Debug\reverse.obj"
	-@erase ".\Debug\GameSettings.obj"
	-@erase ".\Debug\DlgFrameEdit.obj"
	-@erase ".\Debug\scr4editDoc.obj"
	-@erase ".\Debug\strvalarray.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\ProtoPage3.obj"
	-@erase ".\Debug\DlgMoveLevel.obj"
	-@erase ".\Debug\paldata.obj"
	-@erase ".\Debug\DlgMessageBox.obj"
	-@erase ".\Debug\extraarray.obj"
	-@erase ".\Debug\DlgEditLocal.obj"
	-@erase ".\Debug\extracore.obj"
	-@erase ".\Debug\DlgTagEdit.obj"
	-@erase ".\Debug\DbPage3.obj"
	-@erase ".\Debug\proto.obj"
	-@erase ".\Debug\Stack.obj"
	-@erase ".\Debug\DlgClassedit.obj"
	-@erase ".\Debug\lgckcmd.obj"
	-@erase ".\Debug\DlgIntArray.obj"
	-@erase ".\Debug\ss3frame.obj"
	-@erase ".\Debug\scr4editView.obj"
	-@erase ".\Debug\lgckarr.obj"
	-@erase ".\Debug\ProtoPage2.obj"
	-@erase ".\Debug\DlgFrameList.obj"
	-@erase ".\Debug\SndArray.obj"
	-@erase ".\Debug\Splash.obj"
	-@erase ".\Debug\StrVal.obj"
	-@erase ".\Debug\DbPage2.obj"
	-@erase ".\Debug\DlgObjectsMain.obj"
	-@erase ".\Debug\DbSheet.obj"
	-@erase ".\Debug\DlgIntAll.obj"
	-@erase ".\Debug\DlgTagList.obj"
	-@erase ".\Debug\TagArray.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\BmpWrap.obj"
	-@erase ".\Debug\DlgClassList.obj"
	-@erase ".\Debug\ProtoPage1.obj"
	-@erase ".\Debug\shared.obj"
	-@erase ".\Debug\scr4edit.res"
	-@erase ".\Debug\scr4edit_2.ilk"
	-@erase ".\Debug\scr4edit_2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/scr4edit_2.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "_DEBUG"
# ADD RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/scr4edit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/scr4edit_2.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ddraw.lib zlib.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=ddraw.lib zlib.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/scr4edit_2.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/scr4edit_2.exe" 
LINK32_OBJS= \
	"$(INTDIR)/scr4edit.obj" \
	"$(INTDIR)/scriptentry.obj" \
	"$(INTDIR)/DbPage1.obj" \
	"$(INTDIR)/ExtraData.obj" \
	"$(INTDIR)/ProtoPage5.obj" \
	"$(INTDIR)/DlgObjectsList.obj" \
	"$(INTDIR)/protoarray.obj" \
	"$(INTDIR)/DlgIntBox.obj" \
	"$(INTDIR)/scriptarray.obj" \
	"$(INTDIR)/OBL3Filter.obj" \
	"$(INTDIR)/DlgNameDesc.obj" \
	"$(INTDIR)/TagEntry.obj" \
	"$(INTDIR)/Module3.obj" \
	"$(INTDIR)/DlgObjsWiz.obj" \
	"$(INTDIR)/DlgExportPal.obj" \
	"$(INTDIR)/obl3array.obj" \
	"$(INTDIR)/ProtoPage4.obj" \
	"$(INTDIR)/GameFile3.obj" \
	"$(INTDIR)/SortArray.obj" \
	"$(INTDIR)/ProtoSheet.obj" \
	"$(INTDIR)/common.obj" \
	"$(INTDIR)/Snd.obj" \
	"$(INTDIR)/file.obj" \
	"$(INTDIR)/DbPage4.obj" \
	"$(INTDIR)/reverse.obj" \
	"$(INTDIR)/GameSettings.obj" \
	"$(INTDIR)/DlgFrameEdit.obj" \
	"$(INTDIR)/scr4editDoc.obj" \
	"$(INTDIR)/strvalarray.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ProtoPage3.obj" \
	"$(INTDIR)/DlgMoveLevel.obj" \
	"$(INTDIR)/paldata.obj" \
	"$(INTDIR)/DlgMessageBox.obj" \
	"$(INTDIR)/extraarray.obj" \
	"$(INTDIR)/DlgEditLocal.obj" \
	"$(INTDIR)/extracore.obj" \
	"$(INTDIR)/DlgTagEdit.obj" \
	"$(INTDIR)/DbPage3.obj" \
	"$(INTDIR)/proto.obj" \
	"$(INTDIR)/Stack.obj" \
	"$(INTDIR)/DlgClassedit.obj" \
	"$(INTDIR)/lgckcmd.obj" \
	"$(INTDIR)/DlgIntArray.obj" \
	"$(INTDIR)/ss3frame.obj" \
	"$(INTDIR)/scr4editView.obj" \
	"$(INTDIR)/lgckarr.obj" \
	"$(INTDIR)/ProtoPage2.obj" \
	"$(INTDIR)/DlgFrameList.obj" \
	"$(INTDIR)/SndArray.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/StrVal.obj" \
	"$(INTDIR)/DbPage2.obj" \
	"$(INTDIR)/DlgObjectsMain.obj" \
	"$(INTDIR)/DbSheet.obj" \
	"$(INTDIR)/DlgIntAll.obj" \
	"$(INTDIR)/DlgTagList.obj" \
	"$(INTDIR)/TagArray.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/BmpWrap.obj" \
	"$(INTDIR)/DlgClassList.obj" \
	"$(INTDIR)/ProtoPage1.obj" \
	"$(INTDIR)/shared.obj" \
	"$(INTDIR)/scr4edit.res"

"$(OUTDIR)\scr4edit_2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "scr4edit_2 - Win32 Release"
# Name "scr4edit_2 - Win32 Debug"

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgClassedit.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgClassList.cpp

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

DEP_CPP_DLGCL=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgClassList.h"\
	".\DlgClassedit.h"\
	

"$(INTDIR)\DlgClassList.obj" : $(SOURCE) $(DEP_CPP_DLGCL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

DEP_CPP_DLGCL=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgClassList.h"\
	".\DlgClassedit.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	".\scr4editDoc.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\DlgClassList.obj" : $(SOURCE) $(DEP_CPP_DLGCL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgClassList.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgEditLocal.cpp
DEP_CPP_DLGED=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgEditLocal.h"\
	".\shared.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	".\ProtoSheet.h"\
	".\DlgObjectsList.h"\
	".\ProtoPage1.h"\
	".\ProtoPage2.h"\
	".\ProtoPage3.h"\
	".\ProtoPage4.h"\
	".\ProtoPage5.h"\
	

"$(INTDIR)\DlgEditLocal.obj" : $(SOURCE) $(DEP_CPP_DLGED) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgEditLocal.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgExportPal.cpp
DEP_CPP_DLGEX=\
	".\StdAfx.h"\
	".\DlgExportPal.h"\
	

"$(INTDIR)\DlgExportPal.obj" : $(SOURCE) $(DEP_CPP_DLGEX) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgExportPal.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgFrameEdit.cpp
DEP_CPP_DLGFR=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgFrameEdit.h"\
	

"$(INTDIR)\DlgFrameEdit.obj" : $(SOURCE) $(DEP_CPP_DLGFR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgFrameEdit.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgFrameList.cpp
DEP_CPP_DLGFRA=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgFrameList.h"\
	".\DlgFrameEdit.h"\
	".\DlgMessageBox.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\DlgFrameList.obj" : $(SOURCE) $(DEP_CPP_DLGFRA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgFrameList.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgIntAll.cpp
DEP_CPP_DLGIN=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgIntAll.h"\
	".\DlgIntArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\DlgIntAll.obj" : $(SOURCE) $(DEP_CPP_DLGIN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgIntAll.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgIntArray.cpp
DEP_CPP_DLGINT=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgIntArray.h"\
	".\DlgIntBox.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	

"$(INTDIR)\DlgIntArray.obj" : $(SOURCE) $(DEP_CPP_DLGINT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgIntArray.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgIntBox.cpp
DEP_CPP_DLGINTB=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgIntBox.h"\
	

"$(INTDIR)\DlgIntBox.obj" : $(SOURCE) $(DEP_CPP_DLGINTB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgIntBox.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgMessageBox.cpp
DEP_CPP_DLGME=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgMessageBox.h"\
	

"$(INTDIR)\DlgMessageBox.obj" : $(SOURCE) $(DEP_CPP_DLGME) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgMessageBox.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgMoveLevel.cpp
DEP_CPP_DLGMO=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgMoveLevel.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\DlgMoveLevel.obj" : $(SOURCE) $(DEP_CPP_DLGMO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgMoveLevel.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgNameDesc.cpp
DEP_CPP_DLGNA=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgNameDesc.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\DlgNameDesc.obj" : $(SOURCE) $(DEP_CPP_DLGNA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgNameDesc.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgObjectsList.cpp
DEP_CPP_DLGOB=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgObjectsList.h"\
	".\ProtoSheet.h"\
	".\shared.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	".\ProtoPage1.h"\
	".\ProtoPage2.h"\
	".\ProtoPage3.h"\
	".\ProtoPage4.h"\
	".\ProtoPage5.h"\
	

"$(INTDIR)\DlgObjectsList.obj" : $(SOURCE) $(DEP_CPP_DLGOB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgObjectsList.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgObjectsMain.cpp
DEP_CPP_DLGOBJ=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgObjectsMain.h"\
	".\ProtoSheet.h"\
	".\shared.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	".\ProtoPage1.h"\
	".\ProtoPage2.h"\
	".\ProtoPage3.h"\
	".\ProtoPage4.h"\
	".\ProtoPage5.h"\
	".\DlgObjectsList.h"\
	

"$(INTDIR)\DlgObjectsMain.obj" : $(SOURCE) $(DEP_CPP_DLGOBJ) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgObjectsMain.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgObjsWiz.cpp
DEP_CPP_DLGOBJS=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgObjsWiz.h"\
	".\DlgClassedit.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\DlgObjsWiz.obj" : $(SOURCE) $(DEP_CPP_DLGOBJS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgObjsWiz.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgTagEdit.cpp
DEP_CPP_DLGTA=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgTagEdit.h"\
	

"$(INTDIR)\DlgTagEdit.obj" : $(SOURCE) $(DEP_CPP_DLGTA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgTagEdit.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgTagList.cpp
DEP_CPP_DLGTAG=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgTagList.h"\
	".\DlgTagEdit.h"\
	{$(INCLUDE)}"\TagArray.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	

"$(INTDIR)\DlgTagList.obj" : $(SOURCE) $(DEP_CPP_DLGTAG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgTagList.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\paldata.h"\
	".\DlgExportPal.h"\
	".\..\..\obl4_data\source\common.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\Splash.h"\
	{$(INCLUDE)}"\ddraw.h"\
	
NODEP_CPP_MAINF=\
	".\)"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\paldata.h"\
	".\DlgExportPal.h"\
	".\..\..\obl4_data\source\common.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\Splash.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoPage1.cpp
DEP_CPP_PROTO=\
	".\StdAfx.h"\
	".\ProtoPage1.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\ProtoPage1.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoPage1.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoPage2.cpp
DEP_CPP_PROTOP=\
	".\StdAfx.h"\
	".\ProtoPage2.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\ProtoPage2.obj" : $(SOURCE) $(DEP_CPP_PROTOP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoPage2.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoPage3.cpp
DEP_CPP_PROTOPA=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\ProtoPage3.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\ProtoPage3.obj" : $(SOURCE) $(DEP_CPP_PROTOPA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoPage3.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoPage4.cpp
DEP_CPP_PROTOPAG=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\ProtoPage4.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\ProtoPage4.obj" : $(SOURCE) $(DEP_CPP_PROTOPAG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoPage4.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoSheet.cpp
DEP_CPP_PROTOS=\
	".\StdAfx.h"\
	".\ProtoSheet.h"\
	".\ProtoPage1.h"\
	".\ProtoPage2.h"\
	".\ProtoPage3.h"\
	".\ProtoPage4.h"\
	".\ProtoPage5.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\ProtoSheet.obj" : $(SOURCE) $(DEP_CPP_PROTOS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoSheet.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scr4edit.cpp
DEP_CPP_SCR4E=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\MainFrm.h"\
	".\scr4editDoc.h"\
	".\scr4editView.h"\
	".\Splash.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\scr4edit.obj" : $(SOURCE) $(DEP_CPP_SCR4E) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scr4edit.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scr4edit.rc
DEP_RSC_SCR4ED=\
	".\res\scr4editDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\scr4edit.ico"\
	".\res\Splsh16.bmp"\
	".\resource.hm"\
	".\res\scr4edit.rc2"\
	

"$(INTDIR)\scr4edit.res" : $(SOURCE) $(DEP_RSC_SCR4ED) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scr4editDoc.cpp
DEP_CPP_SCR4EDI=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\scr4editDoc.h"\
	".\DlgClassList.h"\
	".\DlgNameDesc.h"\
	".\DlgFrameList.h"\
	".\DlgMessageBox.h"\
	".\DlgObjsWiz.h"\
	{$(INCLUDE)}"\SortArray.h"\
	".\MainFrm.h"\
	".\DlgEditLocal.h"\
	".\DlgMoveLevel.h"\
	".\DlgObjectsList.h"\
	".\DlgTagList.h"\
	".\DlgIntArray.h"\
	".\DlgIntAll.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\DbSheet.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	".\DbPage1.h"\
	".\DbPage2.h"\
	".\DbPage3.h"\
	".\DbPage4.h"\
	

"$(INTDIR)\scr4editDoc.obj" : $(SOURCE) $(DEP_CPP_SCR4EDI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scr4editDoc.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scr4editView.cpp
DEP_CPP_SCR4EDIT=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\scr4editDoc.h"\
	".\scr4editView.h"\
	".\DlgTagList.h"\
	".\DlgEditLocal.h"\
	".\shared.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\Draw.h"\
	{$(INCLUDE)}"\paldata.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	".\ProtoSheet.h"\
	".\DlgObjectsList.h"\
	".\ProtoPage1.h"\
	".\ProtoPage2.h"\
	".\ProtoPage3.h"\
	".\ProtoPage4.h"\
	".\ProtoPage5.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\scr4editView.obj" : $(SOURCE) $(DEP_CPP_SCR4EDIT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scr4editView.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\shared.cpp
DEP_CPP_SHARE=\
	".\StdAfx.h"\
	".\shared.h"\
	".\ProtoSheet.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\proto.h"\
	".\scr4edit.h"\
	".\DlgObjectsList.h"\
	".\ProtoPage1.h"\
	".\ProtoPage2.h"\
	".\ProtoPage3.h"\
	".\ProtoPage4.h"\
	".\ProtoPage5.h"\
	".\scr4editDoc.h"\
	{$(INCLUDE)}"\obl3array.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	

"$(INTDIR)\shared.obj" : $(SOURCE) $(DEP_CPP_SHARE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\shared.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Splash.cpp
DEP_CPP_SPLAS=\
	".\StdAfx.h"\
	".\Splash.h"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Splash.h

!IF  "$(CFG)" == "scr4edit_2 - Win32 Release"

!ELSEIF  "$(CFG)" == "scr4edit_2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgClassedit.cpp
DEP_CPP_DLGCLA=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DlgClassedit.h"\
	

"$(INTDIR)\DlgClassedit.obj" : $(SOURCE) $(DEP_CPP_DLGCLA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\TagEntry.cpp
DEP_CPP_TAGEN=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	

"$(INTDIR)\TagEntry.obj" : $(SOURCE) $(DEP_CPP_TAGEN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\common.cpp
DEP_CPP_COMMO=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\obl4_data\source\common.h"\
	

"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\extraarray.cpp
DEP_CPP_EXTRA=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	

"$(INTDIR)\extraarray.obj" : $(SOURCE) $(DEP_CPP_EXTRA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\extracore.cpp
DEP_CPP_EXTRAC=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\obl4_data\source\extracore.h"\
	

"$(INTDIR)\extracore.obj" : $(SOURCE) $(DEP_CPP_EXTRAC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\ExtraData.cpp
DEP_CPP_EXTRAD=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	

"$(INTDIR)\ExtraData.obj" : $(SOURCE) $(DEP_CPP_EXTRAD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\file.cpp
DEP_CPP_FILE_=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	

"$(INTDIR)\file.obj" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\GameFile3.cpp
DEP_CPP_GAMEF=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\GameFile3.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\paldata.h"\
	{$(INCLUDE)}"\obl3array.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	{$(INCLUDE)}"\TagArray.h"\
	{$(INCLUDE)}"\ExtraArray.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	{$(INCLUDE)}"\Draw.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\GameFile3.obj" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\lgckarr.cpp
DEP_CPP_LGCKA=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\obl4_data\source\lgckarr.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	".\..\..\obl4_data\source\LgckCmd.h"\
	

"$(INTDIR)\lgckarr.obj" : $(SOURCE) $(DEP_CPP_LGCKA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\lgckcmd.cpp
DEP_CPP_LGCKC=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\obl4_data\source\LgckCmd.h"\
	

"$(INTDIR)\lgckcmd.obj" : $(SOURCE) $(DEP_CPP_LGCKC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\Module3.cpp
DEP_CPP_MODUL=\
	".\..\..\obl4_data\source\common.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\obl4_data\source\Module3.h"\
	".\..\..\Win32\lc4\const.h"\
	{$(INCLUDE)}"\TagArray.h"\
	".\..\..\obl4_data\source\lgckarr.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	".\..\..\obl4_data\source\LgckCmd.h"\
	

"$(INTDIR)\Module3.obj" : $(SOURCE) $(DEP_CPP_MODUL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\obl3array.cpp
DEP_CPP_OBL3A=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\obl3array.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	".\..\..\obl4_data\source\common.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	

"$(INTDIR)\obl3array.obj" : $(SOURCE) $(DEP_CPP_OBL3A) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\OBL3Filter.cpp
DEP_CPP_OBL3F=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\OBL4_DATA\SOURCE\obl3filter.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	".\..\..\obl4_data\source\common.h"\
	

"$(INTDIR)\OBL3Filter.obj" : $(SOURCE) $(DEP_CPP_OBL3F) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\paldata.cpp
DEP_CPP_PALDA=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\paldata.h"\
	".\..\..\obl4_data\source\common.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\Draw.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\paldata.obj" : $(SOURCE) $(DEP_CPP_PALDA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\proto.cpp
DEP_CPP_PROTO_=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\proto.h"\
	

"$(INTDIR)\proto.obj" : $(SOURCE) $(DEP_CPP_PROTO_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\protoarray.cpp
DEP_CPP_PROTOA=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\OBL4_DATA\SOURCE\protoarray.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\zlib.h"\
	{$(INCLUDE)}"\proto.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	".\..\..\EXTRA\INCLUDE\MYSQL\zconf.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\protoarray.obj" : $(SOURCE) $(DEP_CPP_PROTOA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\scriptarray.cpp
DEP_CPP_SCRIP=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptarray.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	{$(INCLUDE)}"\zlib.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	{$(INCLUDE)}"\proto.h"\
	".\..\..\EXTRA\INCLUDE\MYSQL\zconf.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\scriptarray.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\scriptentry.cpp
DEP_CPP_SCRIPT=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\OBL4_DATA\SOURCE\scriptentry.h"\
	{$(INCLUDE)}"\proto.h"\
	{$(INCLUDE)}"\ExtraData.h"\
	

"$(INTDIR)\scriptentry.obj" : $(SOURCE) $(DEP_CPP_SCRIPT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\Snd.cpp
DEP_CPP_SND_C=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\obl4_data\source\Snd.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\..\..\..\DIRECTX\7.0A\INCLUDE\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\..\..\..\DIRECTX\7.0A\INCLUDE\d3dvec.inl"\
	

"$(INTDIR)\Snd.obj" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\SndArray.cpp
DEP_CPP_SNDAR=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\obl4_data\source\SndArray.h"\
	".\..\..\obl4_data\source\Snd.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\..\..\..\DIRECTX\7.0A\INCLUDE\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\..\..\..\DIRECTX\7.0A\INCLUDE\d3dvec.inl"\
	

"$(INTDIR)\SndArray.obj" : $(SOURCE) $(DEP_CPP_SNDAR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\SortArray.cpp
DEP_CPP_SORTA=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\SortArray.h"\
	

"$(INTDIR)\SortArray.obj" : $(SOURCE) $(DEP_CPP_SORTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\ss3frame.cpp
DEP_CPP_SS3FR=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\OBL4_DATA\SOURCE\ss3frame.h"\
	{$(INCLUDE)}"\zlib.h"\
	".\..\..\EXTRA\INCLUDE\MYSQL\zconf.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\ss3frame.obj" : $(SOURCE) $(DEP_CPP_SS3FR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\Stack.cpp
DEP_CPP_STACK=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\Stack.obj" : $(SOURCE) $(DEP_CPP_STACK) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\StrVal.cpp
DEP_CPP_STRVA=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	".\..\..\OBL4_DATA\SOURCE\file.h"\
	

"$(INTDIR)\StrVal.obj" : $(SOURCE) $(DEP_CPP_STRVA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\strvalarray.cpp
DEP_CPP_STRVAL=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\strvalarray.h"\
	".\..\..\OBL4_DATA\SOURCE\strval.h"\
	

"$(INTDIR)\strvalarray.obj" : $(SOURCE) $(DEP_CPP_STRVAL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\TagArray.cpp
DEP_CPP_TAGAR=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\TagArray.h"\
	".\..\..\OBL4_DATA\SOURCE\TagEntry.h"\
	

"$(INTDIR)\TagArray.obj" : $(SOURCE) $(DEP_CPP_TAGAR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\BmpWrap.cpp
DEP_CPP_BMPWR=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\obl4_data\source\BmpWrap.h"\
	

"$(INTDIR)\BmpWrap.obj" : $(SOURCE) $(DEP_CPP_BMPWR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\Win32\lc4\reverse.cpp
DEP_CPP_REVER=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\reverse.obj" : $(SOURCE) $(DEP_CPP_REVER) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoPage5.cpp
DEP_CPP_PROTOPAGE=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\ProtoPage5.h"\
	

"$(INTDIR)\ProtoPage5.obj" : $(SOURCE) $(DEP_CPP_PROTOPAGE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DbSheet.cpp
DEP_CPP_DBSHE=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DbSheet.h"\
	".\DbPage1.h"\
	".\DbPage2.h"\
	".\DbPage3.h"\
	".\DbPage4.h"\
	

"$(INTDIR)\DbSheet.obj" : $(SOURCE) $(DEP_CPP_DBSHE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DbPage1.cpp
DEP_CPP_DBPAG=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DbPage1.h"\
	

"$(INTDIR)\DbPage1.obj" : $(SOURCE) $(DEP_CPP_DBPAG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DbPage2.cpp
DEP_CPP_DBPAGE=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DbPage2.h"\
	

"$(INTDIR)\DbPage2.obj" : $(SOURCE) $(DEP_CPP_DBPAGE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DbPage3.cpp
DEP_CPP_DBPAGE3=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DbPage3.h"\
	".\..\..\obl4_data\source\common.h"\
	

"$(INTDIR)\DbPage3.obj" : $(SOURCE) $(DEP_CPP_DBPAGE3) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DbPage4.cpp
DEP_CPP_DBPAGE4=\
	".\StdAfx.h"\
	".\scr4edit.h"\
	".\DbPage4.h"\
	

"$(INTDIR)\DbPage4.obj" : $(SOURCE) $(DEP_CPP_DBPAGE4) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\GameSettings.cpp
DEP_CPP_GAMES=\
	{$(INCLUDE)}"\StdAfx.h"\
	".\..\..\obl4_data\source\GameSettings.h"\
	

"$(INTDIR)\GameSettings.obj" : $(SOURCE) $(DEP_CPP_GAMES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
