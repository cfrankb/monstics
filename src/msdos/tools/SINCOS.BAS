   
        Filename$ = "c:\masm61\listing\sin_cos.inc"


   
    OPEN Filename$ FOR OUTPUT AS #1
   
    FOR X = 0 TO 360
       PRINT #1, "DD "; SIN(X)
    NEXT


    CLOSE 1


