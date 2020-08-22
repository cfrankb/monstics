@echo off
pkzip obl4edt.zip -rp -xbackup\*.* -xdebug\*.* -xrelease\*.* -x*.dll -x*.scr -x*.zip -x*.ncb -x*.aps -x*.clw *.*
rem move *.zip ..\..\backup
e:\toolkit\dateme32.exe obl4edt.zip
move *.zip backup
pause