ORIGIN = PWB
ORIGIN_VER = 2.1.49
PROJ = VLA2_1
PROJFILE = VLA2_1.MAK
DEBUG = 1

ASM  = ml
H2INC  = h2inc
AFLAGS_G  = /W2 /WX
AFLAGS_D  = /Sg /Sc /Zi /Fl
AFLAGS_R  = /nologo
MAPFILE_D  = $(PROJ).map
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /MAP:FULL /NOFA /NOPACKC /NOPACKF
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e

FILES  = VLAMITS2.ASM ..\..\MASM61\LISTING\RUN95.LIB
OBJS  = VLAMITS2.obj
LIBS_EXT  = ..\..\MASM61\LISTING\RUN95.LIB
LIBS  = $(LIBS_EXT)

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .asm

VLAMITS2.obj : VLAMITS2.ASM C:\MASM61\LISTING\SSFSM95.INC\
	C:\MASM61\LISTING\IOSYSTEM.INC
!IF $(DEBUG)
	$(ASM) /c $(AFLAGS_G) $(AFLAGS_D) /FoVLAMITS2.obj VLAMITS2.ASM
!ELSE
	$(ASM) /c $(AFLAGS_G) $(AFLAGS_R) /FoVLAMITS2.obj VLAMITS2.ASM
!ENDIF


$(PROJ).exe : $(OBJS) $(LIBS)
!IF $(DEBUG)
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
	$(LINKER) @$(PROJ).lrf


.asm.obj :
!IF $(DEBUG)
	$(ASM) /c $(AFLAGS_G) $(AFLAGS_D) /Fo$@ $<
!ELSE
	$(ASM) /c $(AFLAGS_G) $(AFLAGS_R) /Fo$@ $<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
