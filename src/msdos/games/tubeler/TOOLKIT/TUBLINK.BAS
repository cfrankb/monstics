OPEN "tublink.ini" FOR INPUT AS #1
OPEN "tublink.mxk" FOR OUTPUT AS #2

100 INPUT #1, a$
IF a$ = "[end]" THEN GOTO 200
PRINT #2, a$ + ".tbl" + CHR$(0);

GOTO 100

200 PRINT #2, CHR$(255);
   CLOSE
   SHELL "Tublink Tublink"
   SHELL "erase tublink.mxk"
   SHELL "copy tublink.tbl c:\tubeler\tublink.tbl"
   SYSTEM




