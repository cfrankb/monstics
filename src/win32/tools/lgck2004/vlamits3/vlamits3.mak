# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=vlamits3 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to vlamits3 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "vlamits3 - Win32 Release" && "$(CFG)" !=\
 "vlamits3 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "vlamits3.mak" CFG="vlamits3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vlamits3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "vlamits3 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "vlamits3 - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

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

ALL : "$(OUTDIR)\vlamits3.exe"

CLEAN : 
	-@erase ".\Release\vlamits3.exe"
	-@erase ".\Release\DlgOptions.obj"
	-@erase ".\Release\BmpWrap.obj"
	-@erase ".\Release\DlgSelectEpisode.obj"
	-@erase ".\Release\scriptentry.obj"
	-@erase ".\Release\Music.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\ss3frame.obj"
	-@erase ".\Release\reverse.obj"
	-@erase ".\Release\ExtraData.obj"
	-@erase ".\Release\TagEntry.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\scriptarray.obj"
	-@erase ".\Release\paldata.obj"
	-@erase ".\Release\DlgSave.obj"
	-@erase ".\Release\TagArray.obj"
	-@erase ".\Release\DlgWait.obj"
	-@erase ".\Release\GameSettings.obj"
	-@erase ".\Release\lgckcmd.obj"
	-@erase ".\Release\vlamits3Doc.obj"
	-@erase ".\Release\protoarray.obj"
	-@erase ".\Release\proto.obj"
	-@erase ".\Release\DlgText.obj"
	-@erase ".\Release\OBL3Filter.obj"
	-@erase ".\Release\common.obj"
	-@erase ".\Release\file.obj"
	-@erase ".\Release\strvalarray.obj"
	-@erase ".\Release\Splash.obj"
	-@erase ".\Release\vlamits3.obj"
	-@erase ".\Release\SndArray.obj"
	-@erase ".\Release\DlgErrorBox.obj"
	-@erase ".\Release\lgckarr.obj"
	-@erase ".\Release\extraarray.obj"
	-@erase ".\Release\game.obj"
	-@erase ".\Release\vlamits3View.obj"
	-@erase ".\Release\DlgLoad.obj"
	-@erase ".\Release\Module3.obj"
	-@erase ".\Release\obl3array.obj"
	-@erase ".\Release\GameFile3.obj"
	-@erase ".\Release\SortArray.obj"
	-@erase ".\Release\DlgYesNoAbort.obj"
	-@erase ".\Release\StrVal.obj"
	-@erase ".\Release\Snd.obj"
	-@erase ".\Release\vlamits3.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/vlamits3.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/vlamits3.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/vlamits3.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 zlib.lib winmm.lib ole32.lib ddraw.lib dsound.lib dinput.lib dxguid.lib newmode.obj /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=zlib.lib winmm.lib ole32.lib ddraw.lib dsound.lib dinput.lib\
 dxguid.lib newmode.obj /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/vlamits3.pdb" /machine:I386 /out:"$(OUTDIR)/vlamits3.exe" 
LINK32_OBJS= \
	"$(INTDIR)/DlgOptions.obj" \
	"$(INTDIR)/BmpWrap.obj" \
	"$(INTDIR)/DlgSelectEpisode.obj" \
	"$(INTDIR)/scriptentry.obj" \
	"$(INTDIR)/Music.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ss3frame.obj" \
	"$(INTDIR)/reverse.obj" \
	"$(INTDIR)/ExtraData.obj" \
	"$(INTDIR)/TagEntry.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/scriptarray.obj" \
	"$(INTDIR)/paldata.obj" \
	"$(INTDIR)/DlgSave.obj" \
	"$(INTDIR)/TagArray.obj" \
	"$(INTDIR)/DlgWait.obj" \
	"$(INTDIR)/GameSettings.obj" \
	"$(INTDIR)/lgckcmd.obj" \
	"$(INTDIR)/vlamits3Doc.obj" \
	"$(INTDIR)/protoarray.obj" \
	"$(INTDIR)/proto.obj" \
	"$(INTDIR)/DlgText.obj" \
	"$(INTDIR)/OBL3Filter.obj" \
	"$(INTDIR)/common.obj" \
	"$(INTDIR)/file.obj" \
	"$(INTDIR)/strvalarray.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/vlamits3.obj" \
	"$(INTDIR)/SndArray.obj" \
	"$(INTDIR)/DlgErrorBox.obj" \
	"$(INTDIR)/lgckarr.obj" \
	"$(INTDIR)/extraarray.obj" \
	"$(INTDIR)/game.obj" \
	"$(INTDIR)/vlamits3View.obj" \
	"$(INTDIR)/DlgLoad.obj" \
	"$(INTDIR)/Module3.obj" \
	"$(INTDIR)/obl3array.obj" \
	"$(INTDIR)/GameFile3.obj" \
	"$(INTDIR)/SortArray.obj" \
	"$(INTDIR)/DlgYesNoAbort.obj" \
	"$(INTDIR)/StrVal.obj" \
	"$(INTDIR)/Snd.obj" \
	"$(INTDIR)/vlamits3.res"

"$(OUTDIR)\vlamits3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

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

ALL : "$(OUTDIR)\vlamits3.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\vlamits3.exe"
	-@erase ".\Debug\scriptarray.obj"
	-@erase ".\Debug\DlgSave.obj"
	-@erase ".\Debug\DlgOptions.obj"
	-@erase ".\Debug\lgckarr.obj"
	-@erase ".\Debug\vlamits3Doc.obj"
	-@erase ".\Debug\DlgLoad.obj"
	-@erase ".\Debug\proto.obj"
	-@erase ".\Debug\Module3.obj"
	-@erase ".\Debug\Snd.obj"
	-@erase ".\Debug\GameSettings.obj"
	-@erase ".\Debug\Splash.obj"
	-@erase ".\Debug\strvalarray.obj"
	-@erase ".\Debug\BmpWrap.obj"
	-@erase ".\Debug\ss3frame.obj"
	-@erase ".\Debug\DlgYesNoAbort.obj"
	-@erase ".\Debug\reverse.obj"
	-@erase ".\Debug\SndArray.obj"
	-@erase ".\Debug\file.obj"
	-@erase ".\Debug\Music.obj"
	-@erase ".\Debug\protoarray.obj"
	-@erase ".\Debug\TagEntry.obj"
	-@erase ".\Debug\ExtraData.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\paldata.obj"
	-@erase ".\Debug\OBL3Filter.obj"
	-@erase ".\Debug\TagArray.obj"
	-@erase ".\Debug\DlgWait.obj"
	-@erase ".\Debug\DlgErrorBox.obj"
	-@erase ".\Debug\lgckcmd.obj"
	-@erase ".\Debug\obl3array.obj"
	-@erase ".\Debug\DlgText.obj"
	-@erase ".\Debug\GameFile3.obj"
	-@erase ".\Debug\SortArray.obj"
	-@erase ".\Debug\StrVal.obj"
	-@erase ".\Debug\game.obj"
	-@erase ".\Debug\common.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\vlamits3View.obj"
	-@erase ".\Debug\scriptentry.obj"
	-@erase ".\Debug\extraarray.obj"
	-@erase ".\Debug\vlamits3.obj"
	-@erase ".\Debug\DlgSelectEpisode.obj"
	-@erase ".\Debug\vlamits3.res"
	-@erase ".\Debug\vlamits3.ilk"
	-@erase ".\Debug\vlamits3.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/vlamits3.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/vlamits3.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/vlamits3.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib ole32.lib ddraw.lib dsound.lib dinput.lib dxguid.lib newmode.obj zlib.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=winmm.lib ole32.lib ddraw.lib dsound.lib dinput.lib dxguid.lib\
 newmode.obj zlib.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/vlamits3.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/vlamits3.exe" 
LINK32_OBJS= \
	"$(INTDIR)/scriptarray.obj" \
	"$(INTDIR)/DlgSave.obj" \
	"$(INTDIR)/DlgOptions.obj" \
	"$(INTDIR)/lgckarr.obj" \
	"$(INTDIR)/vlamits3Doc.obj" \
	"$(INTDIR)/DlgLoad.obj" \
	"$(INTDIR)/proto.obj" \
	"$(INTDIR)/Module3.obj" \
	"$(INTDIR)/Snd.obj" \
	"$(INTDIR)/GameSettings.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/strvalarray.obj" \
	"$(INTDIR)/BmpWrap.obj" \
	"$(INTDIR)/ss3frame.obj" \
	"$(INTDIR)/DlgYesNoAbort.obj" \
	"$(INTDIR)/reverse.obj" \
	"$(INTDIR)/SndArray.obj" \
	"$(INTDIR)/file.obj" \
	"$(INTDIR)/Music.obj" \
	"$(INTDIR)/protoarray.obj" \
	"$(INTDIR)/TagEntry.obj" \
	"$(INTDIR)/ExtraData.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/paldata.obj" \
	"$(INTDIR)/OBL3Filter.obj" \
	"$(INTDIR)/TagArray.obj" \
	"$(INTDIR)/DlgWait.obj" \
	"$(INTDIR)/DlgErrorBox.obj" \
	"$(INTDIR)/lgckcmd.obj" \
	"$(INTDIR)/obl3array.obj" \
	"$(INTDIR)/DlgText.obj" \
	"$(INTDIR)/GameFile3.obj" \
	"$(INTDIR)/SortArray.obj" \
	"$(INTDIR)/StrVal.obj" \
	"$(INTDIR)/game.obj" \
	"$(INTDIR)/common.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/vlamits3View.obj" \
	"$(INTDIR)/scriptentry.obj" \
	"$(INTDIR)/extraarray.obj" \
	"$(INTDIR)/vlamits3.obj" \
	"$(INTDIR)/DlgSelectEpisode.obj" \
	"$(INTDIR)/vlamits3.res"

"$(OUTDIR)\vlamits3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "vlamits3 - Win32 Release"
# Name "vlamits3 - Win32 Debug"

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\vlamits3View.h

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgOptions.h

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\game.cpp

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

DEP_CPP_GAME_=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\game.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\DlgOptions.h"\
	".\DlgSelectEpisode.h"\
	".\DlgWait.h"\
	".\..\..\obl4_data\source\paldata.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\dmusicc.h"\
	{$(INCLUDE)}"\dmusici.h"\
	".\..\..\obl4_data\source\GameFile3.h"\
	".\..\..\obl4_data\source\SndArray.h"\
	{$(INCLUDE)}"\file.h"\
	".\music.h"\
	".\..\scr4edit\vlamits3.txt"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dtypes.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dvec.inl"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dls1.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmerror.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmdls.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmusbuff.h"\
	".\..\..\obl4_data\source\obl3array.h"\
	".\..\..\obl4_data\source\scriptarray.h"\
	".\..\..\obl4_data\source\protoarray.h"\
	".\..\..\obl4_data\source\strvalarray.h"\
	".\..\..\obl4_data\source\tagArray.h"\
	".\..\..\obl4_data\source\extraarray.h"\
	".\..\..\obl4_data\source\gamesettings.h"\
	".\..\..\obl4_data\source\obl3filter.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\ss3frame.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\strval.h"\
	".\..\..\obl4_data\source\TagEntry.h"\
	".\..\..\obl4_data\source\file.h"\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\Snd.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

DEP_CPP_GAME_=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\game.h"\
	{$(INCLUDE)}"\Draw.h"\
	".\DlgOptions.h"\
	".\DlgSelectEpisode.h"\
	".\DlgWait.h"\
	".\..\..\obl4_data\source\paldata.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\game.h

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

DEP_CPP_MAINF=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\MainFrm.h"\
	".\..\..\obl4_data\source\midi.h"\
	".\game.h"\
	".\Splash.h"\
	".\DlgOptions.h"\
	".\DlgErrorBox.h"\
	".\DlgLoad.h"\
	".\DlgSave.h"\
	".\DlgText.h"\
	".\..\..\obl4_data\source\Snd.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dvec.inl"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\dmusicc.h"\
	{$(INCLUDE)}"\dmusici.h"\
	".\..\..\obl4_data\source\GameFile3.h"\
	".\..\..\obl4_data\source\SndArray.h"\
	{$(INCLUDE)}"\file.h"\
	".\music.h"\
	".\..\scr4edit\vlamits3.txt"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dls1.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmerror.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmdls.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmusbuff.h"\
	".\..\..\obl4_data\source\obl3array.h"\
	".\..\..\obl4_data\source\scriptarray.h"\
	".\..\..\obl4_data\source\protoarray.h"\
	".\..\..\obl4_data\source\strvalarray.h"\
	".\..\..\obl4_data\source\tagArray.h"\
	".\..\..\obl4_data\source\extraarray.h"\
	".\..\..\obl4_data\source\gamesettings.h"\
	".\..\..\obl4_data\source\obl3filter.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\ss3frame.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\strval.h"\
	".\..\..\obl4_data\source\TagEntry.h"\
	".\..\..\obl4_data\source\file.h"\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

DEP_CPP_MAINF=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\MainFrm.h"\
	".\..\..\obl4_data\source\midi.h"\
	".\game.h"\
	".\Splash.h"\
	".\DlgOptions.h"\
	".\DlgErrorBox.h"\
	".\DlgLoad.h"\
	".\DlgSave.h"\
	".\DlgText.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\dmusicc.h"\
	{$(INCLUDE)}"\dmusici.h"\
	".\..\..\obl4_data\source\GameFile3.h"\
	".\..\..\obl4_data\source\SndArray.h"\
	{$(INCLUDE)}"\file.h"\
	".\music.h"\
	".\..\scr4edit\vlamits3.txt"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dtypes.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dvec.inl"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dls1.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmerror.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmdls.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmusbuff.h"\
	".\..\..\obl4_data\source\obl3array.h"\
	".\..\..\obl4_data\source\scriptarray.h"\
	".\..\..\obl4_data\source\protoarray.h"\
	".\..\..\obl4_data\source\strvalarray.h"\
	".\..\..\obl4_data\source\tagArray.h"\
	".\..\..\obl4_data\source\extraarray.h"\
	".\..\..\obl4_data\source\gamesettings.h"\
	".\..\..\obl4_data\source\obl3filter.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\ss3frame.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\strval.h"\
	".\..\..\obl4_data\source\TagEntry.h"\
	".\..\..\obl4_data\source\file.h"\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\Snd.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.h

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.h

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vlamits3.cpp
DEP_CPP_VLAMI=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\MainFrm.h"\
	".\vlamits3Doc.h"\
	".\vlamits3View.h"\
	".\Splash.h"\
	".\game.h"\
	".\..\..\obl4_data\source\Snd.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\dmusicc.h"\
	{$(INCLUDE)}"\dmusici.h"\
	".\..\..\obl4_data\source\GameFile3.h"\
	".\..\..\obl4_data\source\SndArray.h"\
	{$(INCLUDE)}"\file.h"\
	".\music.h"\
	".\..\scr4edit\vlamits3.txt"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dtypes.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dvec.inl"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dls1.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmerror.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmdls.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmusbuff.h"\
	".\..\..\obl4_data\source\obl3array.h"\
	".\..\..\obl4_data\source\scriptarray.h"\
	".\..\..\obl4_data\source\protoarray.h"\
	".\..\..\obl4_data\source\strvalarray.h"\
	".\..\..\obl4_data\source\tagArray.h"\
	".\..\..\obl4_data\source\extraarray.h"\
	".\..\..\obl4_data\source\gamesettings.h"\
	".\..\..\obl4_data\source\obl3filter.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\ss3frame.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\strval.h"\
	".\..\..\obl4_data\source\TagEntry.h"\
	".\..\..\obl4_data\source\file.h"\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\vlamits3.obj" : $(SOURCE) $(DEP_CPP_VLAMI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\vlamits3.h

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vlamits3.rc
DEP_RSC_VLAMIT=\
	".\res\vlamits3.ico"\
	".\res\Transprt.wav"\
	".\res\Shorjump.wav"\
	".\res\Click4.wav"\
	".\res\Walk99.wav"\
	".\res\Pouflght.wav"\
	".\res\Fall.wav"\
	".\res\jump.wav"\
	".\res\metal2.wav"\
	".\res\Walk5.wav"\
	".\res\ouchfast.wav"\
	".\Splsh16.bmp"\
	".\res\vlamits3.rc2"\
	

"$(INTDIR)\vlamits3.res" : $(SOURCE) $(DEP_RSC_VLAMIT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\vlamits3Doc.cpp
DEP_CPP_VLAMITS=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\vlamits3Doc.h"\
	

"$(INTDIR)\vlamits3Doc.obj" : $(SOURCE) $(DEP_CPP_VLAMITS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\vlamits3Doc.h

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vlamits3View.cpp
DEP_CPP_VLAMITS3=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\vlamits3Doc.h"\
	".\vlamits3View.h"\
	

"$(INTDIR)\vlamits3View.obj" : $(SOURCE) $(DEP_CPP_VLAMITS3) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgOptions.cpp
DEP_CPP_DLGOP=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\DlgOptions.h"\
	".\MainFrm.h"\
	".\game.h"\
	{$(INCLUDE)}"\dinput.h"\
	".\..\..\obl4_data\source\Snd.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dvec.inl"\
	{$(INCLUDE)}"\dmusicc.h"\
	{$(INCLUDE)}"\dmusici.h"\
	".\..\..\obl4_data\source\GameFile3.h"\
	".\..\..\obl4_data\source\SndArray.h"\
	{$(INCLUDE)}"\file.h"\
	".\music.h"\
	".\..\scr4edit\vlamits3.txt"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dls1.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmerror.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmdls.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmusbuff.h"\
	".\..\..\obl4_data\source\obl3array.h"\
	".\..\..\obl4_data\source\scriptarray.h"\
	".\..\..\obl4_data\source\protoarray.h"\
	".\..\..\obl4_data\source\strvalarray.h"\
	".\..\..\obl4_data\source\tagArray.h"\
	".\..\..\obl4_data\source\extraarray.h"\
	".\..\..\obl4_data\source\gamesettings.h"\
	".\..\..\obl4_data\source\obl3filter.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\ss3frame.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\strval.h"\
	".\..\..\obl4_data\source\TagEntry.h"\
	".\..\..\obl4_data\source\file.h"\
	".\..\..\obl4_data\source\stdafx.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\DlgOptions.obj" : $(SOURCE) $(DEP_CPP_DLGOP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\TagEntry.cpp
DEP_CPP_TAGEN=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\TagEntry.h"\
	".\..\..\obl4_data\source\file.h"\
	

"$(INTDIR)\TagEntry.obj" : $(SOURCE) $(DEP_CPP_TAGEN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\ExtraData.cpp
DEP_CPP_EXTRA=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\file.h"\
	

"$(INTDIR)\ExtraData.obj" : $(SOURCE) $(DEP_CPP_EXTRA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\file.cpp
DEP_CPP_FILE_=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\file.h"\
	

"$(INTDIR)\file.obj" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\GameFile3.cpp
DEP_CPP_GAMEF=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\GameFile3.h"\
	".\..\..\obl4_data\source\file.h"\
	".\..\..\obl4_data\source\paldata.h"\
	".\..\..\obl4_data\source\obl3array.h"\
	".\..\..\obl4_data\source\scriptarray.h"\
	".\..\..\obl4_data\source\protoarray.h"\
	".\..\..\obl4_data\source\strvalarray.h"\
	".\..\..\obl4_data\source\tagArray.h"\
	".\..\..\obl4_data\source\extraarray.h"\
	".\..\..\obl4_data\source\gamesettings.h"\
	".\..\..\obl4_data\source\obl3filter.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\ss3frame.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\strval.h"\
	".\..\..\obl4_data\source\TagEntry.h"\
	{$(INCLUDE)}"\Draw.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\GameFile3.obj" : $(SOURCE) $(DEP_CPP_GAMEF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\obl3array.cpp
DEP_CPP_OBL3A=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\obl3array.h"\
	".\..\..\obl4_data\source\file.h"\
	".\..\..\obl4_data\source\common.h"\
	".\..\..\obl4_data\source\obl3filter.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\ss3frame.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\obl4_data\source\extradata.h"\
	

"$(INTDIR)\obl3array.obj" : $(SOURCE) $(DEP_CPP_OBL3A) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\OBL3Filter.cpp
DEP_CPP_OBL3F=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\obl3filter.h"\
	".\..\..\obl4_data\source\ss3frame.h"\
	".\..\..\obl4_data\source\common.h"\
	

"$(INTDIR)\OBL3Filter.obj" : $(SOURCE) $(DEP_CPP_OBL3F) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\proto.cpp
DEP_CPP_PROTO=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\proto.h"\
	

"$(INTDIR)\proto.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\protoarray.cpp
DEP_CPP_PROTOA=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\protoarray.h"\
	".\..\..\obl4_data\source\file.h"\
	{$(INCLUDE)}"\zlib.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\EXTRA\INCLUDE\MYSQL\zconf.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\protoarray.obj" : $(SOURCE) $(DEP_CPP_PROTOA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\scriptarray.cpp
DEP_CPP_SCRIP=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\scriptarray.h"\
	".\..\..\obl4_data\source\file.h"\
	{$(INCLUDE)}"\zlib.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\EXTRA\INCLUDE\MYSQL\zconf.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\scriptarray.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\scriptentry.cpp
DEP_CPP_SCRIPT=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\scriptentry.h"\
	".\..\..\obl4_data\source\proto.h"\
	".\..\..\obl4_data\source\extradata.h"\
	

"$(INTDIR)\scriptentry.obj" : $(SOURCE) $(DEP_CPP_SCRIPT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\Snd.cpp
DEP_CPP_SND_C=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\Snd.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dvec.inl"\
	

"$(INTDIR)\Snd.obj" : $(SOURCE) $(DEP_CPP_SND_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\SndArray.cpp
DEP_CPP_SNDAR=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\SndArray.h"\
	".\..\..\obl4_data\source\Snd.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dvec.inl"\
	

"$(INTDIR)\SndArray.obj" : $(SOURCE) $(DEP_CPP_SNDAR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\SortArray.cpp
DEP_CPP_SORTA=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\SortArray.h"\
	

"$(INTDIR)\SortArray.obj" : $(SOURCE) $(DEP_CPP_SORTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\ss3frame.cpp
DEP_CPP_SS3FR=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\ss3frame.h"\
	{$(INCLUDE)}"\zlib.h"\
	".\..\..\EXTRA\INCLUDE\MYSQL\zconf.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\ss3frame.obj" : $(SOURCE) $(DEP_CPP_SS3FR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\StrVal.cpp
DEP_CPP_STRVA=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\strval.h"\
	".\..\..\obl4_data\source\file.h"\
	

"$(INTDIR)\StrVal.obj" : $(SOURCE) $(DEP_CPP_STRVA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\strvalarray.cpp
DEP_CPP_STRVAL=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\strvalarray.h"\
	".\..\..\obl4_data\source\strval.h"\
	

"$(INTDIR)\strvalarray.obj" : $(SOURCE) $(DEP_CPP_STRVAL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\TagArray.cpp
DEP_CPP_TAGAR=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\tagArray.h"\
	".\..\..\obl4_data\source\TagEntry.h"\
	

"$(INTDIR)\TagArray.obj" : $(SOURCE) $(DEP_CPP_TAGAR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Toolkit\obl4_data\source\BmpWrap.cpp
DEP_CPP_BMPWR=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\BmpWrap.h"\
	

"$(INTDIR)\BmpWrap.obj" : $(SOURCE) $(DEP_CPP_BMPWR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Music.cpp
DEP_CPP_MUSIC=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\music.h"\
	{$(INCLUDE)}"\dmusicc.h"\
	{$(INCLUDE)}"\dmusici.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dls1.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmerror.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmdls.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\dmusbuff.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\..\..\..\msdev\Extra\Directx\7.0a\include\d3dvec.inl"\
	

"$(INTDIR)\Music.obj" : $(SOURCE) $(DEP_CPP_MUSIC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgErrorBox.cpp

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

DEP_CPP_DLGER=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\DlgErrorBox.h"\
	

"$(INTDIR)\DlgErrorBox.obj" : $(SOURCE) $(DEP_CPP_DLGER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

DEP_CPP_DLGER=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\DlgErrorBox.h"\
	
NODEP_CPP_DLGER=\
	".\IDC_TEXT"\
	

"$(INTDIR)\DlgErrorBox.obj" : $(SOURCE) $(DEP_CPP_DLGER) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Splash.cpp
DEP_CPP_SPLAS=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\Splash.h"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\extraarray.cpp

!IF  "$(CFG)" == "vlamits3 - Win32 Release"

DEP_CPP_EXTRAA=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\extraarray.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\file.h"\
	

"$(INTDIR)\extraarray.obj" : $(SOURCE) $(DEP_CPP_EXTRAA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vlamits3 - Win32 Debug"

DEP_CPP_EXTRAA=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\extraarray.h"\
	".\..\..\obl4_data\source\extradata.h"\
	".\..\..\obl4_data\source\file.h"\
	
NODEP_CPP_EXTRAA=\
	".\..\..\obl4_data\source\{"\
	".\..\..\obl4_data\source\}"\
	

"$(INTDIR)\extraarray.obj" : $(SOURCE) $(DEP_CPP_EXTRAA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\paldata.cpp
DEP_CPP_PALDA=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\paldata.h"\
	".\..\..\obl4_data\source\common.h"\
	".\..\..\obl4_data\source\file.h"\
	{$(INCLUDE)}"\Draw.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\paldata.obj" : $(SOURCE) $(DEP_CPP_PALDA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\Module3.cpp
DEP_CPP_MODUL=\
	".\..\..\obl4_data\source\common.h"\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\Module3.h"\
	".\..\..\Win32\lc4\const.h"\
	".\..\..\obl4_data\source\tagArray.h"\
	".\..\..\obl4_data\source\LgckArr.h"\
	".\..\..\obl4_data\source\TagEntry.h"\
	".\..\..\obl4_data\source\LgckCmd.h"\
	

"$(INTDIR)\Module3.obj" : $(SOURCE) $(DEP_CPP_MODUL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\lgckcmd.cpp
DEP_CPP_LGCKC=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\LgckCmd.h"\
	

"$(INTDIR)\lgckcmd.obj" : $(SOURCE) $(DEP_CPP_LGCKC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\lgckarr.cpp
DEP_CPP_LGCKA=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\LgckArr.h"\
	".\..\..\obl4_data\source\file.h"\
	".\..\..\obl4_data\source\LgckCmd.h"\
	

"$(INTDIR)\lgckarr.obj" : $(SOURCE) $(DEP_CPP_LGCKA) "$(INTDIR)"
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

SOURCE=\toolkit\obl4_data\source\common.cpp
DEP_CPP_COMMO=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\common.h"\
	

"$(INTDIR)\common.obj" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\obl4_data\source\GameSettings.cpp
DEP_CPP_GAMES=\
	".\..\..\obl4_data\source\stdafx.h"\
	".\..\..\obl4_data\source\gamesettings.h"\
	

"$(INTDIR)\GameSettings.obj" : $(SOURCE) $(DEP_CPP_GAMES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgYesNoAbort.cpp
DEP_CPP_DLGYE=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\DlgYesNoAbort.h"\
	

"$(INTDIR)\DlgYesNoAbort.obj" : $(SOURCE) $(DEP_CPP_DLGYE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgSave.cpp
DEP_CPP_DLGSA=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\DlgSave.h"\
	".\DlgYesNoAbort.h"\
	

"$(INTDIR)\DlgSave.obj" : $(SOURCE) $(DEP_CPP_DLGSA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgLoad.cpp
DEP_CPP_DLGLO=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\DlgLoad.h"\
	

"$(INTDIR)\DlgLoad.obj" : $(SOURCE) $(DEP_CPP_DLGLO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgText.cpp
DEP_CPP_DLGTE=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\DlgText.h"\
	

"$(INTDIR)\DlgText.obj" : $(SOURCE) $(DEP_CPP_DLGTE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgSelectEpisode.cpp
DEP_CPP_DLGSE=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\DlgSelectEpisode.h"\
	

"$(INTDIR)\DlgSelectEpisode.obj" : $(SOURCE) $(DEP_CPP_DLGSE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgWait.cpp
DEP_CPP_DLGWA=\
	".\..\..\Mfc\vlamits3\stdafx.h"\
	".\..\..\Mfc\vlamits3\vlamits3.h"\
	".\DlgWait.h"\
	

"$(INTDIR)\DlgWait.obj" : $(SOURCE) $(DEP_CPP_DLGWA) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section vlamits3 : {EC6C194F-CF8E-11D4-8808-DB83FA25754E}
# 	0:8:Splash.h:E:\toolkit\Mfc\vlamits3\Splash.h
# 	0:10:Splash.cpp:E:\toolkit\Mfc\vlamits3\Splash.cpp
# 	1:10:IDB_SPLASH:102
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
