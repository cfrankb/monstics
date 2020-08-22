@echo off
pkzip backup.zip -rp -xbackup\*.* -xdebug\*.* -xrelease\*.* -x*.dll -x*.scr -x*.zip -x*.ncb -x*.aps -x*.clw *.*
rem move *.zip backup.zip
rem move *.zip ..\..\backup
e:\toolkit\dateme32 backup.zip
pause