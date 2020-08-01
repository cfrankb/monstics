20090 REM Graphics Editor's Setup
      DATA 1,2,3,4,5,6,7,8,9,10,12,14,15
      SCREEN 13: COLOR 5
      LOCATE 11, 1: ec = 1
      PRINT "C>lear or S>tore Shape"
      PRINT "B>ack  or N>ext  Shape"
      PRINT "D>own  or L>eft  Flip"
      PRINT "G>Rotate shape"
      PRINT ""
      PRINT : PRINT "[space],Q,W,E,R,T,Y,U,I,O,P> draw color"
      PRINT "[,],[.],[;],[/]> to scroll Shape"
21000 REM Graphics editor
      hd = 0
      COLOR 15
      FOR y = 0 TO 7
      LOCATE y + 1, 9: PRINT "#"
      NEXT
      LOCATE 9, 1: PRINT "#########"
      LOCATE 4, 12: PRINT "Shape no."; ec
      ep = 64 * ec
      FOR y = 0 TO 7
      FOR x = 0 TO 7:
      DEF SEG = &H6800
                                           
      v = PEEK(ep + x + y * 8)
      LOCATE y + 1, x + 1
      COLOR v: PRINT "Û"
      POKE hd + x + y * 8, v
      'POKE 320 * 9 + x + y * 320 + 120, v
      NEXT
      NEXT
      DEF SEG = &H7050
      POKE &H13, 15: POKE &H14, 0
      POKE &H15, 1: POKE &H16, 0
      POKE &H17, ec: POKE &H18, 0
      CALL absolute(&H163)

21010 REM Editor's grild
      ck$ = "qwertyuiop[]\"
      x = 0: y = 0: cd = 1
21015 DEF SEG = &H6800:
      pc = PEEK(hd + x + y * 8)
21020 REM Little cursor flash
      DEF SEG = &H7050
      POKE &H19, x
      POKE &H1B, y
      POKE &H1D, RND(1) * 255
      CALL absolute(&H205)

      DEF SEG = &H6800

21030 REM Cursor moving routine
      GOSUB 30000: a$ = INKEY$: wx = x: wy = y
      IF a$ = "h" THEN GOSUB 60000
      IF a$ = "8" AND y > 0 THEN wy = y - 1: GOTO 21040
      IF a$ = "2" AND y < 7 THEN wy = y + 1: GOTO 21040
      IF a$ = "4" AND x > 0 THEN wx = x - 1: GOTO 21040
      IF a$ = "6" AND x < 7 THEN wx = x + 1: GOTO 21040
      IF a$ = "s" OR a$ = CHR$(13) THEN 21060
      IF a$ = "b" AND ec > 1 THEN ec = ec - 1: GOTO 21000
      IF a$ = "n" AND ec < 127 THEN ec = ec + 1: GOTO 21000
      IF a$ = "c" THEN 21070
      IF a$ = "g" THEN 21100
      IF a$ = "d" THEN 21200
      IF a$ = "l" THEN 21300
      IF a$ = "." THEN 21400
      IF a$ = "," THEN 21500
      IF a$ = ";" OR a$ = "'" THEN 21600
      IF a$ = "/" THEN 21700
      IF a$ = " " THEN qc = 0: GOTO 21055
      IF a$ = CHR$(27) OR a$ = CHR$(9) THEN RUN "menu.bas"
      IF a$ <> "" THEN GOTO 21050
      GOTO 21020

21040 LOCATE y + 1, x + 1
      COLOR pc: PRINT "Û"
      y = wy: x = wx: GOTO 21015

21050 REM Change drop color
      RESTORE: FOR a = 1 TO LEN(ck$)
      READ qc
      IF MID$(ck$, a, 1) = a$ THEN 21055
      NEXT: GOTO 21020
21055 pc = qc: POKE hd + x + y * 8, qc: GOTO 21040

21060 REM Save shape into memory
      FOR y = 0 TO 7
      FOR x = 0 TO 7:
      DEF SEG = &H6800
      v = PEEK(hd + x + y * 8)
      LOCATE y + 1, x + 1
      COLOR v: PRINT "Û"
      POKE ep + x + y * 8, v
      'DEF SEG = &HA000
      'POKE 320 * 9 + x + y * 320 + 120, v
      NEXT
      NEXT: GOTO 21000
   
21070 REM Clear grild
      COLOR 0
      LOCATE 1, 1: FOR y = 0 TO 7
      FOR x = 0 TO 7: PRINT "Û"; : NEXT: PRINT
      NEXT
      FOR a = 0 TO 63: POKE hd + a, 0: NEXT
      GOTO 21010

21100 REM Rotate Shape
      GOSUB 30010
      tx = 7
      FOR sy = 0 TO 7
      FOR sx = 0 TO 7
      DEF SEG = &H70E0
      v = PEEK(sx + sy * 8)
      DEF SEG = &H6800
      POKE tx + sx * 8, v
      NEXT: tx = tx - 1: NEXT
      GOSUB 30020
      GOTO 21015

21200 REM flip up/down
      GOSUB 30010
      FOR sy = 0 TO 7
      FOR sx = 0 TO 7
      DEF SEG = &H70E0
      v = PEEK(sx + sy * 8)
      DEF SEG = &H6800
      POKE sx + (7 - sy) * 8, v
      NEXT: NEXT
      GOSUB 30020: GOTO 21015

21300 REM rotate left/right
      GOSUB 30010
      FOR sy = 0 TO 7
      FOR sx = 0 TO 7
      DEF SEG = &H70E0
      v = PEEK(sx + sy * 8)
      DEF SEG = &H6800
      POKE 7 - sx + sy * 8, v
      NEXT: NEXT
      GOSUB 30020: GOTO 21015

21400 REM SHIFT RIGHT
      GOSUB 30010
      FOR sy = 0 TO 7
      FOR sx = 0 TO 6
      DEF SEG = &H70E0
      v = PEEK(sx + sy * 8)
      DEF SEG = &H6800
      POKE sx + 1 + sy * 8, v
      NEXT
      DEF SEG = &H70E0
      v = PEEK(sy * 8 + 7)
      DEF SEG = &H6800
      POKE sy * 8, v: NEXT
      GOSUB 30020: GOTO 21015

21500 REM SHIFT LEFT
      GOSUB 30010
      FOR sy = 0 TO 7
      FOR sx = 1 TO 7
      DEF SEG = &H70E0
      v = PEEK(sx + sy * 8)
      DEF SEG = &H6800
      POKE sx - 1 + sy * 8, v
      NEXT
      DEF SEG = &H70E0
      v = PEEK(sy * 8 + 0)
      DEF SEG = &H6800
      POKE sy * 8 + 7, v: NEXT
      GOSUB 30020: GOTO 21015

21600 REM SHIFT UP
      GOSUB 30010
      FOR sy = 1 TO 7
      FOR sx = 0 TO 7
      DEF SEG = &H70E0
      v = PEEK(sx + sy * 8)
      DEF SEG = &H6800
      POKE sx + (sy - 1) * 8, v
      NEXT: NEXT
      FOR sx = 0 TO 7
      DEF SEG = &H70E0
      v = PEEK(sx)
      DEF SEG = &H6800
      POKE 7 * 8 + sx, v: NEXT
      GOSUB 30020: GOTO 21015

21700 REM SHIFT DOWN
      GOSUB 30010
      FOR sy = 0 TO 6
      FOR sx = 0 TO 7
      DEF SEG = &H70E0
      v = PEEK(sx + sy * 8)
      DEF SEG = &H6800
      POKE sx + (sy + 1) * 8, v
      NEXT: NEXT
      FOR sx = 0 TO 7
      DEF SEG = &H70E0
      v = PEEK(sx + 7 * 8)
      DEF SEG = &H6800
      POKE sx, v: NEXT
      GOSUB 30020: GOTO 21015



30000 DEF SEG = 0
      POKE 1047, (PEEK(1047) OR 32 OR 16) AND (255 - 64):
      DEF SEG = &H6800: RETURN

30010 REM TRANSFER SHAPE INTO HIGH BUFFER
      FOR a = 0 TO 63
      DEF SEG = &H6800
      v = PEEK(a)
      DEF SEG = &H70E0
      POKE a, v
      NEXT: DEF SEG = &H6800
      RETURN

30020 REM PRINT SHAPE BACK INTO GRILD
      DEF SEG = &H6800
      FOR sx = 0 TO 7
      FOR sy = 0 TO 7
      LOCATE sy + 1, sx + 1
      COLOR PEEK(sx + sy * 8)
      PRINT "Û"; : NEXT: NEXT
      RETURN

60000 DEF SEG = &HA000
      BSAVE "screen.bit", 0, &HFFFF
      CLS
      COLOR 5: PRINT
      PRINT "HELP SCREEN:": PRINT
      PRINT "Follow the instructions on the screen..."
      PRINT : PRINT "LOGICAL STEPS:"
      PRINT "1.Creat shapes with the graphics editor"
      PRINT "2.Set the SETUP"
      PRINT "3.Design items & levels"
      PRINT "4.Test your game"
      PRINT ""
      PRINT "To return to menu press [ESC] or [TAB]!"
     
      PRINT "NOTE:Press [H] at any time to get help."
    
      PRINT : PRINT "Press any key to return..."
60005 a$ = INKEY$
      IF a$ = CHR$(27) THEN RUN "menu.bas"
      IF a$ <> "" THEN 60010
      GOTO 60005

60010 BLOAD "screen.bit", 0
      RETURN

