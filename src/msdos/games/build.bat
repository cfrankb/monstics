path c:\masm61\bin;z:\

cd \games\cs3
ml cs3.asm /exepack
del *.obj

cd \games\cs4
ml cs4.asm \masm61\listing\1994\94rep.asm \masm61\listing\1994\94statlb.asm
ml cs4level.asm \masm61\listing\1994\94rep.asm /exepack
del *.obj

cd \games\vlamits
ml vlamits.asm
ml vlalevel.asm
del *.obj

cd \games\vlamits2
ml /c ..\..\MASM61\LISTING\1995\94REPV2.ASM ..\..\MASM61\LISTING\1995\94statv2.ASM ..\..\MASM61\LISTING\1995\95COLORS.ASM 
ml /c ..\..\MASM61\LISTING\1995\95STRING.ASM ..\..\MASM61\LISTING\1995\95STV2_1.ASM
del run95.lib
lib.exe run95.lib +94repv2.obj +94statv2.obj +95colors.obj +95string.obj +95stv2_1.obj < ..\..\MASM61\LISTING\1995.dat
ml vlamits2.asm /link run95.lib /exepack
del *.obj
del run95.lib

cd \games\tubeler
ml sources\tubeler.asm \masm61\listing\1994\94rep.asm \masm61\listing\1994\94statlb.asm /exepack
del *.obj
