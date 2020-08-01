                                                         
      'GAME MODULE FOR LGCK
      'Programmed by Francois Blanchette
     
10000 DEF SEG = &H6700
      d$ = CHR$(PEEK(0)) + ":"
      SCREEN 8
      LOCATE 12, 1
      COLOR 5
      PRINT "                INSERT GAME DISK IN "; d$
      PRINT "                Press [space] to continue, [ESC] to abbord or"
      PRINT "                [P] to enter passcode."
10005 lv = 0: a$ = INKEY$
      IF a$ = " " THEN 10010
      IF a$ = "p" OR a$ = "P" THEN 23000
      IF a$ = CHR$(27) OR a$ = CHR$(9) THEN 22000
      GOTO 10005

10010 'GAME SETUP
      SCREEN 13
      DEF SEG = &H7000
      BLOAD d$ + "ITEMS.LGC", 0
      DEF SEG = &H6800
      BLOAD d$ + "graphics.lgc", 0
      DEF SEG = &H7050
      BLOAD d$ + "setup.lgc", 0
      POKE 10, 0
      POKE 11, 1
      POKE 12, 0
      DEF SEG = &H7060
      BLOAD "prnshape.mxe", 0
      DEF SEG = &H6700
      d$ = CHR$(PEEK(0)) + ":"
      DEF SEG = &H7050
      l = PEEK(0)  'nb of lives
      nl = PEEK(1) 'nb of levels
      pl = PEEK(2) * 100 + 500'pts for an extra life
      fs = PEEK(3) 'fall in squares
      cf = PEEK(4) 'control fall
      jf = PEEK(5) 'jump function
      
      ne = pl

10100 'LEVEL ENTRY FUNCTION
      lv = lv + 1
10105 l$ = MID$(STR$(lv), 2): IF lv < 10 THEN l$ = "0" + l$
      DEF SEG = &H7100: tnt = 0
      BLOAD d$ + "lev" + l$ + ".lgc", 0
      
      DEF SEG = &H7050
      CALL absolute(&H209)
      GOSUB 60000: GOSUB 64000

20000 'MAIN GAME
      'PF - player form
      'PX - player X
      'PY - player Y
      'CG - number of Collectives goals
      'PV - position value
       
       DEF SEG = &H7000
       pt = PEEK(pv + &H180)
       IF pt = 1 OR pt = 2 THEN sc = sc + pt * 50: GOSUB 60000
       IF pt = 3 THEN sc = sc + 250: GOSUB 60000
       IF pt = 4 THEN sc = sc + 500: GOSUB 60000
      
       DEF SEG = &H7000
       sa = PEEK(pv + &H100)
       IF sa = 1 THEN 20800
       IF sa = 2 THEN l = l + 1: GOSUB 60000
       IF sa = 3 THEN 21000
       IF sa = 4 THEN tnt = tnt + 1: GOSUB 60000

20020  DEF SEG = &H7000
       ac = PEEK(pv + &H80)
       IF ac > 1 THEN 20700
       IF PEEK(pv) <> 1 THEN pv = PEEK(pv + &H300)

       DEF SEG = &H7100
       pu = PEEK(px + py * 40 + 40)
       POKE px + py * 40, pv

       DEF SEG = &H7000
       IF PEEK(pu + &H80) > 1 THEN 20700
       IF PEEK(pv + &H80) > 1 THEN 20700
       IF PEEK(pu) = 0 AND PEEK(pv) = 0 THEN 20600
       IF sc >= ne THEN ne = ne + pl: l = l + 1: GOSUB 60000

20100 REM CONTROL MODULE
      a$ = INKEY$: wy = py: wx = px
      IF a$ = "8" AND py > 1 THEN wy = py - 1: GOTO 20500
      IF a$ = "2" AND py < 24 THEN wy = py + 1: GOTO 20500
      IF a$ = "4" AND px > 0 THEN wx = px - 1: GOTO 20500
      IF a$ = "6" AND px < 39 THEN wx = px + 1: GOTO 20500
      IF a$ = "`" THEN 20700
      IF a$ = CHR$(9) OR a$ = CHR$(27) THEN 22000
      IF a$ = CHR$(13) AND tnt > 0 THEN GOTO 62000
      IF a$ = "7" OR a$ = "9" THEN 20900
      GOTO 20000

20500 REM WANTED POSITION
      DEF SEG = &H7100
      wv = PEEK(wx + wy * 40):
      DEF SEG = &H7000
      IF PEEK(wv) > 2 OR PEEK(wv) = 1 THEN 20100
      iv = PEEK(pv + &H280)
      sx = px: sy = py: GOSUB 65000
      sx = wx: sy = wy: iv = pf: GOSUB 65000
      px = wx: py = wy: pv = wv
      DEF SEG = &H7000
      ef = PEEK(pv + &H200)
      IF ef = 2 OR ef = 0 THEN a% = 64: b% = 255: SOUND b%, a% / 1000
      IF ef = 3 THEN BEEP
      IF ef = 4 THEN FOR a = 0 TO 8 STEP 2: x% = a * 128: SOUND x%, x% / 500: NEXT: GOSUB 63000
      GOTO 20000

20600 REM FALLING INTO THE DEEP
      f = 0
20605 DEF SEG = &H7100
      pv = PEEK(px + py * 40)
      pu = PEEK(px + py * 40 + 40)
      DEF SEG = &H7000
      vs = PEEK(pv): vu = PEEK(pu)
      IF vs > 0 OR vu > 0 THEN GOTO 20610
      iv = PEEK(pv + &H280)
      sx = px: sy = py: GOSUB 65000
      DEF SEG = &H7000
      py = py + 1: sy = py:
      iv = pf: GOSUB 65000
      f = f + 1: IF py + 1 > 24 THEN 20700
      GOTO 20605
20610 IF f >= fs THEN 20700
      GOTO 20000

20700 REM DEATH ROUTINE
      DEF SEG = &HA000
      hd = px * 8 + py * 320 * 8
      FOR a = 16 TO 0 STEP -1
      x% = a * 64: IF x% > 0 THEN SOUND x%, x% / 1000
      FOR b = 0 TO 7:
      FOR c = 0 TO 7
      IF PEEK(hd + b * 320 + c) <> 0 THEN POKE hd + b * 320 + c, a
      NEXT
      NEXT
      NEXT
      DEF SEG = &H7000
      sx = px: sy = py
      iv = PEEK(&H280)
      GOSUB 65000
      l = l - 1: IF l > 0 THEN 10105
20725 LOCATE 13, 12: PRINT "PUSH [SPACE]"
      LOCATE 14, 12: PRINT "TO RESTART!!!"
      DEF SEG = &H7050
      CALL absolute(&H226)
      CALL absolute(&H209)
      GOSUB 60000
20750 IF INKEY$ <> " " THEN 20750
      RUN

20800 REM NUMBER OF GOAL -1
      cg = cg - 1: IF cg = 0 THEN 20850
      GOTO 20020

20850 IF lv < nl THEN 10100
      sc = sc + l * 50 + tnt * 25
      LOCATE 13, 12: PRINT "PUSH [SPACE]"
      LOCATE 14, 12: PRINT "TO RESTART!!!"
      DEF SEG = &H7050
      CALL absolute(&H209)
      COLOR 6: LOCATE 1, 1: FOR a = 0 TO 39: PRINT " "; : NEXT
      LOCATE 1, 1: PRINT "YOU WIN!!! FINAL SCORE"; sc
      CALL absolute(&H226)
      GOTO 20750

20900 REM JUMP ROUTINE
      pp = px + py * 40
      IF jf = 0 THEN 20000
      IF a$ = "9" THEN 20920
      DEF SEG = &H7100
      nv = PEEK(pp - 1): fv = PEEK(pp - 2)
      DEF SEG = &H7000
      IF PEEK(nv) > 2 OR PEEK(fv) > 2 THEN 20000
      IF px - 2 < 0 THEN 20000
      iv = PEEK(pv + &H280)
      sx = px: sy = py: GOSUB 65000
      DEF SEG = &H7000
      px = px - 2: sx = px
      iv = pf: GOSUB 65000
      pv = fv: GOSUB 20930
      GOTO 20000

20920 DEF SEG = &H7100
      nv = PEEK(pp + 1): fv = PEEK(pp + 2)
      DEF SEG = &H7000
      IF PEEK(nv) > 2 OR PEEK(fv) > 2 THEN 20000
      IF px + 2 > 39 THEN 20000
      iv = PEEK(pv + &H280)
      sx = px: sy = py: GOSUB 65000
      DEF SEG = &H7000
      px = px + 2: sx = px
      iv = pf: GOSUB 65000
      pv = fv: GOSUB 20930
      GOTO 20000

20930 REM JUMP SOUND...!!!
      'FOR a = 0 TO 8 STEP 2: x% = a * 48
      'SOUND x%, x% / 1000: NEXT:
      'FOR a = 0 TO 25: NEXT
      GOTO 63000

21000 REM ATTIVATE TRIGGER
      DEF SEG = &H7000
      tr = PEEK(pv + &H380)
      'pv = PEEK(pv + &H300)
      FOR sy = 1 TO 24
      FOR sx = 0 TO 39
      DEF SEG = &H7100
      tv = PEEK(sx + sy * 40)
      IF tv = tr THEN 21010
21005 NEXT: NEXT
      DEF SEG = &H7100
      GOTO 20020

21010 DEF SEG = &H7000
      tc = PEEK(tv + &H300)
      iv = PEEK(tc + &H280)
      GOSUB 65000
      DEF SEG = &H7100
      POKE sx + sy * 40, tc
      GOTO 21005

22000 IF a$ = CHR$(27) THEN RUN
      DEF SEG = &H7100
      BLOAD d$ + "lev01.lgc"
      RUN "menu.bas"

23000 REM ENTER PASSCODE
      CLS : SCREEN 1
23005 a$ = "": INPUT "ENTER PASSCODE:"; a$
      IF a$ = "" THEN RUN
      l$ = MID$(a$, 1, 2)
      IF VAL(l$) < 1 OR VAL(l$) > 25 THEN PRINT "Wrong code!!!": GOTO 23005
      DEF SEG = &H7100
      BLOAD d$ + "lev" + l$ + ".lgc"
      pw = 0
      FOR sy = 1 TO 24
      FOR sx = 0 TO 39
      iw = PEEK(sx + sy * 40): pw = pw + iw
      NEXT sx
      NEXT sy
      pw$ = l$ + MID$(STR$(pw AND 9999), 2)
      IF a$ <> pw$ THEN PRINT "Wrong code!!!": GOTO 23005
      lv = VAL(l$) - 1
      GOTO 10010
END
60000 REM PRINT TITLE LINE
      COLOR 6: LOCATE 1, 1: FOR a = 0 TO 39: PRINT " "; : NEXT
      LOCATE 1, 1: PRINT "LEVEL"; lv; "LIVES"; l; "SCORE"; sc; "TNT"; tnt
      DEF SEG = &H7050
      CALL absolute(&H226)
      RETURN

62000 REM USE TNT ROUTINE
      tnt = tnt - 1: GOSUB 60000: FOR x = 0 TO 9:
      DEF SEG = &H7050
      CALL absolute(&H209): NEXT
      DEF SEG = &H7100
      zz = PEEK(py * 40 + px + 40)
      DEF SEG = &H7000
      IF PEEK(zz) = 4 THEN 20000
      sy = py + 1: sx = px: pu = PEEK(zz + &H300)
      iv = PEEK(pu + &H280)
      DEF SEG = &H7100
      POKE py * 40 + px + 40, pu
      GOSUB 65000:
      DEF SEG = &H7000
      IF PEEK(zz + &H100) = 1 THEN 20800
      GOTO 20000

63000 REM WAIT FOR SOUND TO WEAR-OFF
      FOR a = 0 TO 500: NEXT
63005 a$ = INKEY$: IF a$ = CHR$(9) OR a$ = CHR$(27) THEN 22000
      IF INKEY$ <> "" THEN 63005
      RETURN

64000 REM DRAW GAME SCREEN
      px = 1: py = 1: pw = 0
      cg = 0: pv = 0
      FOR sy = 1 TO 24
      FOR sx = 0 TO 39
      DEF SEG = &H7100
      iw = PEEK(sx + sy * 40): pw = pw + iw
      aq = 0: DEF SEG = &H7000
      IF PEEK(&H100 + iw) = 1 THEN cg = cg + 1
      iv = PEEK(512 + 128 + iw):
      IF PEEK(&H80 + iw) = 1 THEN px = sx: py = sy: pf = iv: pv = iw
      GOSUB 65000
      NEXT sx
      NEXT sy
      pw$ = l$ + MID$(STR$(pw AND 9999), 2)
      PRINT pw$
      RETURN

65000 REM put item onto screen
      REM sx - screen x
      REM sy - screen y
      REM iv - valeur of graphics shape
      DEF SEG = &H7050
      POKE &H13, sx: POKE &H14, 0
      POKE &H15, sy: POKE &H16, 0
      POKE &H17, iv: POKE &H18, 0
      CALL absolute(&H163)
      RETURN

