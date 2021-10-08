# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=mysql_buddy - Win32 Release
!MESSAGE No configuration specified.  Defaulting to mysql_buddy - Win32\
 Release.
!ENDIF 

!IF "$(CFG)" != "mysql_buddy - Win32 Release" && "$(CFG)" !=\
 "mysql_buddy - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "mysql_buddy.mak" CFG="mysql_buddy - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mysql_buddy - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "mysql_buddy - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "mysql_buddy - Win32 Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\mysql_buddy.exe"

CLEAN : 
	-@erase ".\Release\mysql_buddy.exe"
	-@erase ".\Release\Server.obj"
	-@erase ".\Release\mysql_buddy.pch"
	-@erase ".\Release\SQLCmd.obj"
	-@erase ".\Release\Field.obj"
	-@erase ".\Release\DlgConfig.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\ServerArr.obj"
	-@erase ".\Release\Table.obj"
	-@erase ".\Release\SQLMother.obj"
	-@erase ".\Release\mysql_buddyDoc.obj"
	-@erase ".\Release\TextArray.obj"
	-@erase ".\Release\DlgDatabase.obj"
	-@erase ".\Release\DlgNewThing.obj"
	-@erase ".\Release\WndTable.obj"
	-@erase ".\Release\DlgField.obj"
	-@erase ".\Release\mysql_buddy.obj"
	-@erase ".\Release\mysql_buddyView.obj"
	-@erase ".\Release\DlgMySQLTable.obj"
	-@erase ".\Release\DlgDescription.obj"
	-@erase ".\Release\DlgTable.obj"
	-@erase ".\Release\DlgSQL.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\mysql_buddy.res"
	-@erase ".\Release\mysql_buddy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O1 /Ob0 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O1 /Ob0 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/mysql_buddy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "NDEBUG"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/mysql_buddy.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mysql_buddy.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 mysqlclient.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=mysqlclient.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/mysql_buddy.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/mysql_buddy.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Server.obj" \
	"$(INTDIR)/SQLCmd.obj" \
	"$(INTDIR)/Field.obj" \
	"$(INTDIR)/DlgConfig.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ServerArr.obj" \
	"$(INTDIR)/Table.obj" \
	"$(INTDIR)/SQLMother.obj" \
	"$(INTDIR)/mysql_buddyDoc.obj" \
	"$(INTDIR)/TextArray.obj" \
	"$(INTDIR)/DlgDatabase.obj" \
	"$(INTDIR)/DlgNewThing.obj" \
	"$(INTDIR)/WndTable.obj" \
	"$(INTDIR)/DlgField.obj" \
	"$(INTDIR)/mysql_buddy.obj" \
	"$(INTDIR)/mysql_buddyView.obj" \
	"$(INTDIR)/DlgMySQLTable.obj" \
	"$(INTDIR)/DlgDescription.obj" \
	"$(INTDIR)/DlgTable.obj" \
	"$(INTDIR)/DlgSQL.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/mysql_buddy.res"

"$(OUTDIR)\mysql_buddy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\mysql_buddy.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\mysql_buddy.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\mysql_buddy.exe"
	-@erase ".\Debug\DlgMySQLTable.obj"
	-@erase ".\Debug\DlgTable.obj"
	-@erase ".\Debug\TextArray.obj"
	-@erase ".\Debug\Field.obj"
	-@erase ".\Debug\DlgNewThing.obj"
	-@erase ".\Debug\mysql_buddyDoc.obj"
	-@erase ".\Debug\mysql_buddy.obj"
	-@erase ".\Debug\Table.obj"
	-@erase ".\Debug\mysql_buddyView.obj"
	-@erase ".\Debug\DlgSQL.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\Server.obj"
	-@erase ".\Debug\SQLCmd.obj"
	-@erase ".\Debug\DlgDescription.obj"
	-@erase ".\Debug\DlgDatabase.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\DlgConfig.obj"
	-@erase ".\Debug\ServerArr.obj"
	-@erase ".\Debug\WndTable.obj"
	-@erase ".\Debug\SQLMother.obj"
	-@erase ".\Debug\DlgField.obj"
	-@erase ".\Debug\mysql_buddy.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/mysql_buddy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0c /d "_DEBUG"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/mysql_buddy.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mysql_buddy.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 mysqlclientd.lib /nologo /subsystem:windows /profile /debug /machine:I386
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=mysqlclientd.lib /nologo /subsystem:windows /profile /debug\
 /machine:I386 /out:"$(OUTDIR)/mysql_buddy.exe" 
LINK32_OBJS= \
	"$(INTDIR)/DlgMySQLTable.obj" \
	"$(INTDIR)/DlgTable.obj" \
	"$(INTDIR)/TextArray.obj" \
	"$(INTDIR)/Field.obj" \
	"$(INTDIR)/DlgNewThing.obj" \
	"$(INTDIR)/mysql_buddyDoc.obj" \
	"$(INTDIR)/mysql_buddy.obj" \
	"$(INTDIR)/Table.obj" \
	"$(INTDIR)/mysql_buddyView.obj" \
	"$(INTDIR)/DlgSQL.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Server.obj" \
	"$(INTDIR)/SQLCmd.obj" \
	"$(INTDIR)/DlgDescription.obj" \
	"$(INTDIR)/DlgDatabase.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/DlgConfig.obj" \
	"$(INTDIR)/ServerArr.obj" \
	"$(INTDIR)/WndTable.obj" \
	"$(INTDIR)/SQLMother.obj" \
	"$(INTDIR)/DlgField.obj" \
	"$(INTDIR)/mysql_buddy.res"

"$(OUTDIR)\mysql_buddy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "mysql_buddy - Win32 Release"
# Name "mysql_buddy - Win32 Debug"

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mysql_buddy.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_MYSQL=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\MainFrm.h"\
	".\mysql_buddyDoc.h"\
	".\mysql_buddyView.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\mysql_buddy.obj" : $(SOURCE) $(DEP_CPP_MYSQL) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_MYSQL=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\MainFrm.h"\
	".\mysql_buddyDoc.h"\
	".\mysql_buddyView.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\mysql_buddy.obj" : $(SOURCE) $(DEP_CPP_MYSQL) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O1 /Ob0 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/mysql_buddy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\mysql_buddy.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/mysql_buddy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\mysql_buddy.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\MainFrm.h"\
	".\WndTable.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\Table.h"\
	".\SQLMother.h"\
	".\Field.h"\
	".\Server.h"\
	".\ServerArr.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\MainFrm.h"\
	".\WndTable.h"\
	".\Table.h"\
	".\SQLMother.h"\
	".\Field.h"\
	".\Server.h"\
	".\ServerArr.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mysql_buddyDoc.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_MYSQL_=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\mysql_buddyDoc.h"\
	".\Field.h"\
	".\Table.h"\
	".\SQLMother.h"\
	".\WndTable.h"\
	".\DlgTable.h"\
	".\DlgDatabase.h"\
	".\DlgConfig.h"\
	".\DlgNewThing.h"\
	".\DlgDescription.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\MainFrm.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\DlgField.h"\
	".\TextArray.h"\
	

"$(INTDIR)\mysql_buddyDoc.obj" : $(SOURCE) $(DEP_CPP_MYSQL_) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_MYSQL_=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\mysql_buddyDoc.h"\
	".\Field.h"\
	".\Table.h"\
	".\SQLMother.h"\
	".\WndTable.h"\
	".\DlgTable.h"\
	".\DlgDatabase.h"\
	".\DlgConfig.h"\
	".\DlgNewThing.h"\
	".\DlgDescription.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\DlgField.h"\
	".\TextArray.h"\
	

"$(INTDIR)\mysql_buddyDoc.obj" : $(SOURCE) $(DEP_CPP_MYSQL_) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mysql_buddyView.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_MYSQL_B=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\mysql_buddyDoc.h"\
	".\mysql_buddyView.h"\
	".\WndTable.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\MainFrm.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\mysql_buddyView.obj" : $(SOURCE) $(DEP_CPP_MYSQL_B) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_MYSQL_B=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\mysql_buddyDoc.h"\
	".\mysql_buddyView.h"\
	".\WndTable.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\mysql_buddyView.obj" : $(SOURCE) $(DEP_CPP_MYSQL_B) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mysql_buddy.rc
DEP_RSC_MYSQL_BU=\
	".\res\mysql_buddy.ico"\
	".\res\mysql_buddyDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\mysql_buddy.rc2"\
	

"$(INTDIR)\mysql_buddy.res" : $(SOURCE) $(DEP_RSC_MYSQL_BU) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgTable.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_DLGTA=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgTable.h"\
	".\DlgField.h"\
	".\DlgSQL.h"\
	".\DlgNewThing.h"\
	".\SQLMother.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\Table.h"\
	".\Field.h"\
	".\Server.h"\
	".\ServerArr.h"\
	

"$(INTDIR)\DlgTable.obj" : $(SOURCE) $(DEP_CPP_DLGTA) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_DLGTA=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgTable.h"\
	".\DlgField.h"\
	".\DlgSQL.h"\
	".\DlgNewThing.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Field.h"\
	".\Server.h"\
	".\ServerArr.h"\
	

"$(INTDIR)\DlgTable.obj" : $(SOURCE) $(DEP_CPP_DLGTA) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgField.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_DLGFI=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgField.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\Field.h"\
	

"$(INTDIR)\DlgField.obj" : $(SOURCE) $(DEP_CPP_DLGFI) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_DLGFI=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgField.h"\
	".\Field.h"\
	

"$(INTDIR)\DlgField.obj" : $(SOURCE) $(DEP_CPP_DLGFI) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Field.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_FIELD=\
	".\StdAfx.h"\
	".\Field.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	

"$(INTDIR)\Field.obj" : $(SOURCE) $(DEP_CPP_FIELD) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_FIELD=\
	".\StdAfx.h"\
	".\Field.h"\
	

"$(INTDIR)\Field.obj" : $(SOURCE) $(DEP_CPP_FIELD) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Table.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_TABLE=\
	".\StdAfx.h"\
	".\Table.h"\
	".\SQLMother.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\Field.h"\
	".\Server.h"\
	".\ServerArr.h"\
	

"$(INTDIR)\Table.obj" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_TABLE=\
	".\StdAfx.h"\
	".\Table.h"\
	".\SQLMother.h"\
	".\Field.h"\
	".\Server.h"\
	".\ServerArr.h"\
	

"$(INTDIR)\Table.obj" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgSQL.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_DLGSQ=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgSQL.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\Table.h"\
	".\Field.h"\
	

"$(INTDIR)\DlgSQL.obj" : $(SOURCE) $(DEP_CPP_DLGSQ) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_DLGSQ=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgSQL.h"\
	".\Table.h"\
	".\Field.h"\
	

"$(INTDIR)\DlgSQL.obj" : $(SOURCE) $(DEP_CPP_DLGSQ) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SQLMother.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_SQLMO=\
	".\StdAfx.h"\
	".\SQLMother.h"\
	".\WndTable.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\SQLMother.obj" : $(SOURCE) $(DEP_CPP_SQLMO) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_SQLMO=\
	".\StdAfx.h"\
	".\SQLMother.h"\
	".\WndTable.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\SQLMother.obj" : $(SOURCE) $(DEP_CPP_SQLMO) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TextArray.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_TEXTA=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\TextArray.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	

"$(INTDIR)\TextArray.obj" : $(SOURCE) $(DEP_CPP_TEXTA) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_TEXTA=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\TextArray.h"\
	

"$(INTDIR)\TextArray.obj" : $(SOURCE) $(DEP_CPP_TEXTA) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgDatabase.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_DLGDA=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgDatabase.h"\
	".\DlgNewThing.h"\
	".\DlgSQL.h"\
	".\DlgTable.h"\
	".\DlgMySQLTable.h"\
	".\SQLCmd.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\SQLMother.h"\
	".\TextArray.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	".\DlgField.h"\
	

"$(INTDIR)\DlgDatabase.obj" : $(SOURCE) $(DEP_CPP_DLGDA) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_DLGDA=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgDatabase.h"\
	".\DlgNewThing.h"\
	".\DlgSQL.h"\
	".\DlgTable.h"\
	".\DlgMySQLTable.h"\
	".\SQLCmd.h"\
	".\SQLMother.h"\
	".\TextArray.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	".\DlgField.h"\
	

"$(INTDIR)\DlgDatabase.obj" : $(SOURCE) $(DEP_CPP_DLGDA) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgNewThing.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_DLGNE=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgNewThing.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	

"$(INTDIR)\DlgNewThing.obj" : $(SOURCE) $(DEP_CPP_DLGNE) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_DLGNE=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgNewThing.h"\
	

"$(INTDIR)\DlgNewThing.obj" : $(SOURCE) $(DEP_CPP_DLGNE) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Server.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_SERVE=\
	".\StdAfx.h"\
	".\Server.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	

"$(INTDIR)\Server.obj" : $(SOURCE) $(DEP_CPP_SERVE) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_SERVE=\
	".\StdAfx.h"\
	".\Server.h"\
	

"$(INTDIR)\Server.obj" : $(SOURCE) $(DEP_CPP_SERVE) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ServerArr.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_SERVER=\
	".\StdAfx.h"\
	".\ServerArr.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\Server.h"\
	

"$(INTDIR)\ServerArr.obj" : $(SOURCE) $(DEP_CPP_SERVER) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_SERVER=\
	".\StdAfx.h"\
	".\ServerArr.h"\
	".\Server.h"\
	

"$(INTDIR)\ServerArr.obj" : $(SOURCE) $(DEP_CPP_SERVER) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgConfig.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_DLGCO=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgConfig.h"\
	".\DlgNewThing.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\ServerArr.h"\
	".\Server.h"\
	

"$(INTDIR)\DlgConfig.obj" : $(SOURCE) $(DEP_CPP_DLGCO) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_DLGCO=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgConfig.h"\
	".\DlgNewThing.h"\
	".\ServerArr.h"\
	".\Server.h"\
	

"$(INTDIR)\DlgConfig.obj" : $(SOURCE) $(DEP_CPP_DLGCO) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SQLCmd.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_SQLCM=\
	".\StdAfx.h"\
	".\SQLCmd.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\SQLCmd.obj" : $(SOURCE) $(DEP_CPP_SQLCM) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_SQLCM=\
	".\StdAfx.h"\
	".\SQLCmd.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\SQLCmd.obj" : $(SOURCE) $(DEP_CPP_SQLCM) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgMySQLTable.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_DLGMY=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgMySQLTable.h"\
	".\SQLCmd.h"\
	".\DlgSQL.h"\
	".\DlgField.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\TextArray.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\DlgMySQLTable.obj" : $(SOURCE) $(DEP_CPP_DLGMY) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_DLGMY=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgMySQLTable.h"\
	".\SQLCmd.h"\
	".\DlgSQL.h"\
	".\DlgField.h"\
	".\TextArray.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\DlgMySQLTable.obj" : $(SOURCE) $(DEP_CPP_DLGMY) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WndTable.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_WNDTA=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\WndTable.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\Table.h"\
	".\SQLMother.h"\
	".\Field.h"\
	".\Server.h"\
	".\ServerArr.h"\
	

"$(INTDIR)\WndTable.obj" : $(SOURCE) $(DEP_CPP_WNDTA) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_WNDTA=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\WndTable.h"\
	".\Table.h"\
	".\SQLMother.h"\
	".\Field.h"\
	".\Server.h"\
	".\ServerArr.h"\
	

"$(INTDIR)\WndTable.obj" : $(SOURCE) $(DEP_CPP_WNDTA) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgDescription.cpp

!IF  "$(CFG)" == "mysql_buddy - Win32 Release"

DEP_CPP_DLGDE=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgDescription.h"\
	{$(INCLUDE)}"\mysql.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\file.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\..\..\extra\include\mysql\mysql_com.h"\
	".\..\..\..\extra\include\mysql\mysql_version.h"\
	{$(INCLUDE)}"\config-win.h"\
	{$(INCLUDE)}"\my_config.h"\
	{$(INCLUDE)}"\sys\Timeb.h"\
	{$(INCLUDE)}"\dbug.h"\
	{$(INCLUDE)}"\sys\Locking.h"\
	".\..\..\..\extra\common\stdafx.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\DlgDescription.obj" : $(SOURCE) $(DEP_CPP_DLGDE) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ELSEIF  "$(CFG)" == "mysql_buddy - Win32 Debug"

DEP_CPP_DLGDE=\
	".\StdAfx.h"\
	".\mysql_buddy.h"\
	".\DlgDescription.h"\
	".\SQLMother.h"\
	".\Table.h"\
	".\Server.h"\
	".\ServerArr.h"\
	".\Field.h"\
	

"$(INTDIR)\DlgDescription.obj" : $(SOURCE) $(DEP_CPP_DLGDE) "$(INTDIR)"\
 "$(INTDIR)\mysql_buddy.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section mysql_buddy : {EC6C1948-CF8E-11D4-8808-DB83FA25754E}
# 	2:15:CMysql_buddyDoc:MAPI Support Added
# 	2:12:InitInstance:MAPI Support Added
# End Section
################################################################################
################################################################################
# Section mysql_buddy : {B6805000-A509-11CE-A5B0-00AA006BBF16}
# 	1:29:CG_IDR_POPUP_MYSQL_BUDDY_VIEW:102
# End Section
################################################################################
