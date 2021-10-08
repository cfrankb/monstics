# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=SdiApp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SdiApp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SdiApp - Win32 Release" && "$(CFG)" != "SdiApp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SdiApp.mak" CFG="SdiApp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SdiApp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SdiApp - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "SdiApp - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "SdiApp - Win32 Release"

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

ALL : "$(OUTDIR)\SdiApp.exe"

CLEAN : 
	-@erase ".\Release\SdiApp.exe"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\App.obj"
	-@erase ".\Release\MemoDialog.obj"
	-@erase ".\Release\Splash.obj"
	-@erase ".\Release\AlarmsListDialog.obj"
	-@erase ".\Release\ClockDialog.obj"
	-@erase ".\Release\EditEx.obj"
	-@erase ".\Release\AppView.obj"
	-@erase ".\Release\StaticEx.obj"
	-@erase ".\Release\AlarmNode.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\Note.obj"
	-@erase ".\Release\AppDoc.obj"
	-@erase ".\Release\BipBox.obj"
	-@erase ".\Release\SdiApp.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SdiApp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/SdiApp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SdiApp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 \msdev\lib\winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=\msdev\lib\winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SdiApp.pdb" /machine:I386 /out:"$(OUTDIR)/SdiApp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/App.obj" \
	"$(INTDIR)/MemoDialog.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/AlarmsListDialog.obj" \
	"$(INTDIR)/ClockDialog.obj" \
	"$(INTDIR)/EditEx.obj" \
	"$(INTDIR)/AppView.obj" \
	"$(INTDIR)/StaticEx.obj" \
	"$(INTDIR)/AlarmNode.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Note.obj" \
	"$(INTDIR)/AppDoc.obj" \
	"$(INTDIR)/BipBox.obj" \
	"$(INTDIR)/SdiApp.res"

"$(OUTDIR)\SdiApp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

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

ALL : "$(OUTDIR)\SdiApp.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\SdiApp.exe"
	-@erase ".\Debug\Splash.obj"
	-@erase ".\Debug\App.obj"
	-@erase ".\Debug\AlarmsListDialog.obj"
	-@erase ".\Debug\EditEx.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\BipBox.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\ClockDialog.obj"
	-@erase ".\Debug\AppDoc.obj"
	-@erase ".\Debug\StaticEx.obj"
	-@erase ".\Debug\Note.obj"
	-@erase ".\Debug\AlarmNode.obj"
	-@erase ".\Debug\AppView.obj"
	-@erase ".\Debug\MemoDialog.obj"
	-@erase ".\Debug\SdiApp.res"
	-@erase ".\Debug\SdiApp.ilk"
	-@erase ".\Debug\SdiApp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/SdiApp.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/SdiApp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SdiApp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 \msdev\lib\winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=\msdev\lib\winmm.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SdiApp.pdb" /debug /machine:I386 /out:"$(OUTDIR)/SdiApp.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/App.obj" \
	"$(INTDIR)/AlarmsListDialog.obj" \
	"$(INTDIR)/EditEx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/BipBox.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ClockDialog.obj" \
	"$(INTDIR)/AppDoc.obj" \
	"$(INTDIR)/StaticEx.obj" \
	"$(INTDIR)/Note.obj" \
	"$(INTDIR)/AlarmNode.obj" \
	"$(INTDIR)/AppView.obj" \
	"$(INTDIR)/MemoDialog.obj" \
	"$(INTDIR)/SdiApp.res"

"$(OUTDIR)\SdiApp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "SdiApp - Win32 Release"
# Name "SdiApp - Win32 Debug"

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AlarmsListDialog.cpp
DEP_CPP_ALARM=\
	".\StdAfx.h"\
	".\App.h"\
	".\AlarmsListDialog.h"\
	".\ClockDialog.h"\
	".\AppView.h"\
	".\AppDoc.h"\
	".\StaticEx.h"\
	".\AlarmNode.h"\
	".\EditEx.h"\
	

"$(INTDIR)\AlarmsListDialog.obj" : $(SOURCE) $(DEP_CPP_ALARM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\App.cpp
DEP_CPP_APP_C=\
	".\StdAfx.h"\
	".\StaticEx.h"\
	".\Note.h"\
	".\App.h"\
	".\MainFrm.h"\
	".\AppDoc.h"\
	".\AppView.h"\
	".\Splash.h"\
	".\AlarmNode.h"\
	".\EditEx.h"\
	

"$(INTDIR)\App.obj" : $(SOURCE) $(DEP_CPP_APP_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AppDoc.cpp
DEP_CPP_APPDO=\
	".\StdAfx.h"\
	".\StaticEx.h"\
	".\AppDoc.h"\
	".\AppView.h"\
	".\App.h"\
	".\Note.h"\
	".\AlarmNode.h"\
	".\EditEx.h"\
	

"$(INTDIR)\AppDoc.obj" : $(SOURCE) $(DEP_CPP_APPDO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AppView.cpp
DEP_CPP_APPVI=\
	".\StdAfx.h"\
	".\StaticEx.h"\
	".\AppDoc.h"\
	".\AppView.h"\
	".\App.h"\
	".\Note.h"\
	".\MemoDialog.h"\
	".\ClockDialog.h"\
	".\AlarmsListDialog.h"\
	".\BipBox.h"\
	".\AlarmNode.h"\
	".\EditEx.h"\
	

"$(INTDIR)\AppView.obj" : $(SOURCE) $(DEP_CPP_APPVI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BipBox.cpp
DEP_CPP_BIPBO=\
	".\StdAfx.h"\
	".\App.h"\
	".\BipBox.h"\
	

"$(INTDIR)\BipBox.obj" : $(SOURCE) $(DEP_CPP_BIPBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ClockDialog.cpp

!IF  "$(CFG)" == "SdiApp - Win32 Release"

DEP_CPP_CLOCK=\
	".\StdAfx.h"\
	".\App.h"\
	".\ClockDialog.h"\
	".\AppDoc.h"\
	".\AppView.h"\
	".\StaticEx.h"\
	".\AlarmNode.h"\
	".\EditEx.h"\
	

"$(INTDIR)\ClockDialog.obj" : $(SOURCE) $(DEP_CPP_CLOCK) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

DEP_CPP_CLOCK=\
	".\StdAfx.h"\
	".\App.h"\
	".\ClockDialog.h"\
	

"$(INTDIR)\ClockDialog.obj" : $(SOURCE) $(DEP_CPP_CLOCK) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\App.h"\
	".\MainFrm.h"\
	".\Splash.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MemoDialog.cpp
DEP_CPP_MEMOD=\
	".\StdAfx.h"\
	".\App.h"\
	".\MemoDialog.h"\
	

"$(INTDIR)\MemoDialog.obj" : $(SOURCE) $(DEP_CPP_MEMOD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Note.cpp
DEP_CPP_NOTE_=\
	".\StdAfx.h"\
	".\App.h"\
	".\Note.h"\
	

"$(INTDIR)\Note.obj" : $(SOURCE) $(DEP_CPP_NOTE_) "$(INTDIR)"


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

SOURCE=.\StaticEx.cpp
DEP_CPP_STATI=\
	".\StdAfx.h"\
	".\App.h"\
	".\StaticEx.h"\
	

"$(INTDIR)\StaticEx.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AlarmNode.cpp
DEP_CPP_ALARMN=\
	".\StdAfx.h"\
	".\App.h"\
	".\AlarmNode.h"\
	

"$(INTDIR)\AlarmNode.obj" : $(SOURCE) $(DEP_CPP_ALARMN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SdiApp.rc
DEP_RSC_SDIAP=\
	".\res\SdiAppDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\SdiApp.ico"\
	".\res\Splsh16.bmp"\
	".\res\bmp00001.bmp"\
	".\resource.hm"\
	".\res\SdiApp.rc2"\
	

"$(INTDIR)\SdiApp.res" : $(SOURCE) $(DEP_RSC_SDIAP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AlarmsListDialog.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\App.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AppDoc.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AppView.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BipBox.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ClockDialog.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MemoDialog.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Note.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.hm

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Splash.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StaticEx.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AlarmNode.h

!IF  "$(CFG)" == "SdiApp - Win32 Release"

!ELSEIF  "$(CFG)" == "SdiApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EditEx.cpp
DEP_CPP_EDITE=\
	".\StdAfx.h"\
	".\EditEx.h"\
	

"$(INTDIR)\EditEx.obj" : $(SOURCE) $(DEP_CPP_EDITE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section SdiApp : {3050F3FD-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLPluginsCollection
# 	2:10:HeaderFile:htmlpluginscollection.h
# 	2:8:ImplFile:htmlpluginscollection.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F35C-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLScreen
# 	2:10:HeaderFile:htmlscreen.h
# 	2:8:ImplFile:htmlscreen.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F1F7-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLFormElement
# 	2:10:HeaderFile:htmlformelement.h
# 	2:8:ImplFile:htmlformelement.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F25A-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLSelectionObject
# 	2:10:HeaderFile:htmlselectionobject.h
# 	2:8:ImplFile:htmlselectionobject.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {163BB1E0-6E00-11CF-837A-48DC04C10000}
# 	2:5:Class:CHTMLLocation
# 	2:10:HeaderFile:htmllocation.h
# 	2:8:ImplFile:htmllocation.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F38C-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLOptionElementFactory
# 	2:10:HeaderFile:htmloptionelementfactory.h
# 	2:8:ImplFile:htmloptionelementfactory.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F401-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLOpsProfile
# 	2:10:HeaderFile:htmlopsprofile.h
# 	2:8:ImplFile:htmlopsprofile.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {CE04B591-2B1F-11D2-8D1E-00A0C959BC0A}
# 	2:5:Class:CDHTMLEdit
# 	2:10:HeaderFile:dhtmledit.h
# 	2:8:ImplFile:dhtmledit.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F25E-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLStyle
# 	2:10:HeaderFile:htmlstyle.h
# 	2:8:ImplFile:htmlstyle.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F3FC-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLMimeTypesCollection
# 	2:10:HeaderFile:htmlmimetypescollection.h
# 	2:8:ImplFile:htmlmimetypescollection.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F2E3-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLStyleSheet
# 	2:10:HeaderFile:htmlstylesheet.h
# 	2:8:ImplFile:htmlstylesheet.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {FECEAAA2-8405-11CF-8BA1-00AA00476DA6}
# 	2:5:Class:COmHistory
# 	2:10:HeaderFile:omhistory.h
# 	2:8:ImplFile:omhistory.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F211-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLOptionElement
# 	2:10:HeaderFile:htmloptionelement.h
# 	2:8:ImplFile:htmloptionelement.cpp
# End Section
################################################################################
################################################################################
# Section OLE Controls
# 	{2D360200-FFF5-11D1-8D03-00A0C959BC0A}
# End Section
################################################################################
################################################################################
# Section SdiApp : {332C4427-26CB-11D0-B483-00C04FD90119}
# 	2:5:Class:CHTMLWindow2
# 	2:10:HeaderFile:htmlwindow2.h
# 	2:8:ImplFile:htmlwindow2.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F3CF-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLRuleStyle
# 	2:10:HeaderFile:htmlrulestyle.h
# 	2:8:ImplFile:htmlrulestyle.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F357-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLStyleSheetRule
# 	2:10:HeaderFile:htmlstylesheetrule.h
# 	2:8:ImplFile:htmlstylesheetrule.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F240-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLImgElement
# 	2:10:HeaderFile:htmlimgelement.h
# 	2:8:ImplFile:htmlimgelement.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F38E-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLImageElementFactory
# 	2:10:HeaderFile:htmlimageelementfactory.h
# 	2:8:ImplFile:htmlimageelementfactory.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F37E-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLStyleSheetsCollection
# 	2:10:HeaderFile:htmlstylesheetscollection.h
# 	2:8:ImplFile:htmlstylesheetscollection.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {FECEAAA5-8405-11CF-8BA1-00AA00476DA6}
# 	2:5:Class:COmNavigator
# 	2:10:HeaderFile:omnavigator.h
# 	2:8:ImplFile:omnavigator.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F3EE-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLFiltersCollection
# 	2:10:HeaderFile:htmlfilterscollection.h
# 	2:8:ImplFile:htmlfilterscollection.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F32D-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLEventObj
# 	2:10:HeaderFile:htmleventobj.h
# 	2:8:ImplFile:htmleventobj.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F2E5-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLStyleSheetRulesCollection
# 	2:10:HeaderFile:htmlstylesheetrulescollection.h
# 	2:8:ImplFile:htmlstylesheetrulescollection.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {332C4426-26CB-11D0-B483-00C04FD90119}
# 	2:5:Class:CHTMLFramesCollection2
# 	2:10:HeaderFile:htmlframescollection2.h
# 	2:8:ImplFile:htmlframescollection2.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {2D360200-FFF5-11D1-8D03-00A0C959BC0A}
# 	0:15:HTMLRuleStyle.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLRuleStyle.h
# 	0:22:HTMLStyleSheetRule.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyleSheetRule.cpp
# 	0:17:HTMLFormElement.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLFormElement.h
# 	0:14:HTMLEventObj.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLEventObj.h
# 	0:15:HTMLWindow2.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLWindow2.cpp
# 	0:21:HTMLSelectionObject.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLSelectionObject.h
# 	0:12:HTMLScreen.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLScreen.h
# 	0:25:HTMLMimeTypesCollection.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLMimeTypesCollection.h
# 	0:25:HTMLFramesCollection2.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLFramesCollection2.cpp
# 	0:13:HTMLElement.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLElement.h
# 	0:21:HTMLOptionElement.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLOptionElement.cpp
# 	0:25:HTMLElementCollection.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLElementCollection.cpp
# 	0:15:HTMLDocument2.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLDocument2.h
# 	0:31:HTMLStyleSheetRulesCollection.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyleSheetRulesCollection.h
# 	0:14:HTMLScreen.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLScreen.cpp
# 	0:14:HTMLLocation.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLLocation.h
# 	0:17:HTMLDocument2.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLDocument2.cpp
# 	0:19:HTMLOptionElement.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLOptionElement.h
# 	0:26:HTMLOptionElementFactory.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLOptionElementFactory.h
# 	0:27:HTMLImageElementFactory.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLImageElementFactory.cpp
# 	0:25:HTMLImageElementFactory.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLImageElementFactory.h
# 	0:25:HTMLFiltersCollection.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLFiltersCollection.cpp
# 	0:23:HTMLElementCollection.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLElementCollection.h
# 	0:19:HTMLFormElement.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLFormElement.cpp
# 	0:11:OmHistory.h:E:\toolkit\Mfc\MiniAppCalendar\OmHistory.h
# 	0:16:HTMLImgElement.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLImgElement.h
# 	0:13:HTMLStyle.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyle.cpp
# 	0:11:HTMLStyle.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyle.h
# 	0:20:HTMLStyleSheetRule.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyleSheetRule.h
# 	0:29:HTMLStyleSheetsCollection.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyleSheetsCollection.cpp
# 	0:27:HTMLStyleSheetsCollection.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyleSheetsCollection.h
# 	0:13:HTMLWindow2.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLWindow2.h
# 	0:13:DHTMLEdit.cpp:E:\toolkit\Mfc\MiniAppCalendar\DHTMLEdit.cpp
# 	0:11:DHTMLEdit.h:E:\toolkit\Mfc\MiniAppCalendar\DHTMLEdit.h
# 	0:18:HTMLStyleSheet.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyleSheet.cpp
# 	0:16:HTMLLocation.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLLocation.cpp
# 	0:23:HTMLSelectionObject.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLSelectionObject.cpp
# 	0:17:HTMLRuleStyle.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLRuleStyle.cpp
# 	0:33:HTMLStyleSheetRulesCollection.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyleSheetRulesCollection.cpp
# 	0:15:OmNavigator.cpp:E:\toolkit\Mfc\MiniAppCalendar\OmNavigator.cpp
# 	0:16:HTMLEventObj.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLEventObj.cpp
# 	0:18:HTMLOpsProfile.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLOpsProfile.cpp
# 	0:27:HTMLMimeTypesCollection.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLMimeTypesCollection.cpp
# 	0:15:HTMLElement.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLElement.cpp
# 	0:28:HTMLOptionElementFactory.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLOptionElementFactory.cpp
# 	0:25:HTMLPluginsCollection.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLPluginsCollection.cpp
# 	0:13:OmHistory.cpp:E:\toolkit\Mfc\MiniAppCalendar\OmHistory.cpp
# 	0:16:HTMLOpsProfile.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLOpsProfile.h
# 	0:23:HTMLPluginsCollection.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLPluginsCollection.h
# 	0:13:OmNavigator.h:E:\toolkit\Mfc\MiniAppCalendar\OmNavigator.h
# 	0:23:HTMLFramesCollection2.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLFramesCollection2.h
# 	0:16:HTMLStyleSheet.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLStyleSheet.h
# 	0:18:HTMLImgElement.cpp:E:\toolkit\Mfc\MiniAppCalendar\HTMLImgElement.cpp
# 	0:23:HTMLFiltersCollection.h:E:\toolkit\Mfc\MiniAppCalendar\HTMLFiltersCollection.h
# 	2:21:DefaultSinkHeaderFile:dhtmledit.h
# 	2:16:DefaultSinkClass:CDHTMLEdit
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F1FF-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLElement
# 	2:10:HeaderFile:htmlelement.h
# 	2:8:ImplFile:htmlelement.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {B6805000-A509-11CE-A5B0-00AA006BBF16}
# 	1:18:IDR_POPUP_APP_VIEW:102
# End Section
################################################################################
################################################################################
# Section SdiApp : {4CBFB8C3-7386-11D1-BE2C-444553540000}
# 	0:8:Splash.h:C:\!Projet\Mfc\MiniAppCalendar\Splash.h
# 	0:10:Splash.cpp:C:\!Projet\Mfc\MiniAppCalendar\Splash.cpp
# 	1:10:IDB_SPLASH:108
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
# Section SdiApp : {332C4425-26CB-11D0-B483-00C04FD90119}
# 	2:5:Class:CHTMLDocument2
# 	2:10:HeaderFile:htmldocument2.h
# 	2:8:ImplFile:htmldocument2.cpp
# End Section
################################################################################
################################################################################
# Section SdiApp : {3050F21F-98B5-11CF-BB82-00AA00BDCE0B}
# 	2:5:Class:CHTMLElementCollection
# 	2:10:HeaderFile:htmlelementcollection.h
# 	2:8:ImplFile:htmlelementcollection.cpp
# End Section
################################################################################
