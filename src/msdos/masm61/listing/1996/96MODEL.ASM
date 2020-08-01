;**********************************************************************
; RUNTIME LIBRAIRY FOR PMODE
;**********************************************************************
; NAME       : 96REPV3.ASM
; DESCRIPTION: Runtime librairy for PMODE programs. Code in this module
;              only works under PMODE.   Code will crash in real mode.
;
;**********************************************************************
;
; CODE WRITTEN           : F.Blanchette
; EXTERNAL DEFS & MACROS : Tran (a.k.a. Thomas Pytel) of Renaissance
;                    	   (Tran -> author of PMODE)
;
;***********************************************************************
.386p
.include \masm61\listing\386.inc
;#####################################################
;.model flat
code32  segment para public use32
        assume cs:code32, ds:code32, gs:nothing
;#####################################################


;#####################################################
code32 ends
end
;#####################################################
