ml /c ..\..\MASM61\LISTING\1995\94REPV2.ASM ..\..\MASM61\LISTING\1995\94statv2.ASM ..\..\MASM61\LISTING\1995\95COLORS.ASM 
ml /c ..\..\MASM61\LISTING\1995\95STRING.ASM ..\..\MASM61\LISTING\1995\95STV2_1.ASM
del run95.*
lib.exe run95.lib +94repv2.obj +94statv2.obj +95colors.obj +95string.obj +95stv2_1.obj < ..\..\MASM61\LISTING\1995.dat
pause
ml vlamits2.asm /link run95.lib /exepack

