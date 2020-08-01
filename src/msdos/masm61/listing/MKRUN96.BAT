@echo off
rem copy \run96p\run96p\96repv3.* 1996\*.*
lib run96.lib -+ 1996\96repv3.obj -+1996\pmode.obj -+1996\file.obj  <auto.dat
echo.
del run96.bak
pause