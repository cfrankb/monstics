del run95.lib
del 1995\run95.lib
..\ml.exe /c 1995\*.asm
del 1995\*.obj
move *.obj 1995
..\lib.exe run95.lib +1995\95vgahi.obj +1995\94repv2.obj +1995\94statv2.obj +1995\95colors.obj +1995\95string.obj +1995\95stv2_1.obj < 1995.dat
del *.bak
del 1995\*.obj
move run95.lib 1995
pause
