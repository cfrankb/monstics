
TITLE DIALOG_EXTENSIONS_FOR_ADOS
include c:\Masm61\listing\SsfsMac.INC

; Enables all externals definitions...
;UseRep		; 94REP.ASM
;UseSSFSLB	; 94SSFSLB.ASM
;UseSTATLB	; 94STATLB.ASM
;UseDial	; 94DIAL.ASM

PUBLIC GLOBALTOPICSSTATUS
PUBLIC LOCALTOPICSSTATUS
PUBLIC PERSONALQUESTIONS
PUBLIC GLOBALPOINTERS
PUBLIC LOCALPOINTERS
PUBLIC QUESTIONSPOINTERS
PUBLIC GLOBALTEXTS
PUBLIC LOCALTEXTS

DATA SEGMENT PUBLIC 'DATA'
GLOBALTOPICSSTATUS	db 40 DUP (0)
LOCALTOPICSSTATUS       db 20 DUP (0)
PERSONALQUESTIONS	db 10 DUP (0)
align 2
GLOBALPOINTERS		dw 40 DUP (0)
LOCALPOINTERS		dw 20 DUP (0)
QUESTIONSPOINTERS	dw 10 DUP (0)
GLOBALTEXTS		db 500 DUP (0)
LOCALTEXTS		db 15000 DUP (0)
DATA ENDS
END

CODE SEGMENT PUBLIC 'CODE'
.386
CODE ENDS