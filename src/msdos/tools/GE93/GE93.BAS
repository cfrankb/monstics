
      REM GRAPHICS EDITOR 93
      REM by Francois Blanchette
      REM all right reserved!
      DEF SEG = &H9010
      BLOAD "c:\other\ge93\ge93.mxe", 0

10000 SCREEN 13
      CLS
      FOR x = 0 TO 15
      LOCATE x + 1, 17
      COLOR 15: PRINT "#"
      NEXT
      FOR x = 0 TO 16
      PRINT "#"; : NEXT
      COLOR 5
      LOCATE 10, 20: PRINT "[] change set"
      LOCATE 11, 20: PRINT "B/N change image"
      LOCATE 12, 20: PRINT "CTRL/ALT to LOAD/SAVE"
      
21000 hd = ec * 256: COLOR 15: LOCATE 1, 20: PRINT "Image:"; ec
      GOSUB 21800

      DEF SEG = &H9000
      POKE 4, 0: POKE 5, ec
      CALL absolute(&H141)
      CALL absolute(&H161)
      CALL absolute(&H189)


21010 REM Editor's grild
      ck$ = "qwertyui"
      x = 0: y = 0
21015 DEF SEG = &H6800:
      pc = PEEK(x + y * 16)
21020 REM Little cursor flash
      cc = cc + 1: IF cc = 16 THEN cc = 0
      kd = 8 * x + y * 8 * 320
      DEF SEG = &HA000
      FOR ky = 1 TO 6
      POKE kd + 320 * ky, cc: POKE kd + 7 + 320 * ky, cc
      NEXT
      FOR kx = 0 TO 7
      POKE kd + kx, cc: POKE kd + 7 * 320 + kx, cc:
      NEXT
      DEF SEG = &H6800

21030 REM Cursor moving routine
      GOSUB 30000: a$ = INKEY$: wx = x: wy = y
      IF a$ = "8" AND y > 0 THEN wy = y - 1: GOTO 21040
      IF a$ = "2" AND y < 15 THEN wy = y + 1: GOTO 21040
      IF a$ = "4" AND x > 0 THEN wx = x - 1: GOTO 21040
      IF a$ = "6" AND x < 15 THEN wx = x + 1: GOTO 21040
      IF a$ = CHR$(13) THEN 21060
      IF a$ = "b" AND ec > 0 THEN ec = ec - 1: GOTO 21000
      IF a$ = "n" AND ec < 127 THEN ec = ec + 1: GOTO 21000
      DEF SEG = 2
      IF a$ = "=" THEN 40000
      IF a$ = "-" THEN 40100
      IF a$ = "c" THEN 21070
      IF a$ = "g" THEN 21100
      IF a$ = "d" THEN 21200
      IF a$ = "l" THEN 21300
      IF a$ = "." THEN 21400
      IF a$ = "," THEN 21500
      IF a$ = ";" OR a$ = "'" THEN 21600
      IF a$ = "/" THEN 21700
      IF a$ >= "a" AND a$ <= "z" THEN 21050
      IF a$ = " " THEN pc = 0: GOTO 21057
      IF a$ = "`" THEN pc = 19: GOTO 21057
      IF a$ = "[" AND cs > 0 THEN cs = cs - 1: GOSUB 21800
      IF a$ = "]" AND cs < 31 THEN cs = cs + 1: GOSUB 21800
      IF a$ = "\" THEN 21057
      IF a$ = "~" THEN 22000
      GOTO 21020

21040 LOCATE y + 1, x + 1
      COLOR pc: PRINT "Û"
      y = wy: x = wx: GOTO 21015

21050 REM Change drop color
      FOR a = 1 TO LEN(ck$)
      IF MID$(ck$, a, 1) = a$ THEN 21055
      NEXT: GOTO 21020
21055 DEF SEG = &H6800: pc = (a + 8 * cs) AND 255:
21057 DEF SEG = &H6800:
      POKE x + y * 16, pc:
      GOTO 21040

21060 REM Save shape into memory
      FOR y = 0 TO 15
      FOR x = 0 TO 15:
      DEF SEG = &H6800
      v = PEEK(x + y * 16)
      DEF SEG = &H6820
      POKE ec * 256 + x + y * 16, v
      NEXT
      NEXT:
      DEF SEG = &H9000
      CALL absolute(&H189)
      CALL absolute(&H161)
      GOTO 21010
  
21070 REM Clear grild
      COLOR 0
      LOCATE 1, 1: FOR y = 0 TO 15
      FOR x = 0 TO 15: PRINT "Û"; : NEXT: PRINT
      NEXT
      DEF SEG = &H6800
      FOR a = 0 TO 256: POKE a, 0: NEXT
      GOTO 21010

21100 REM Rotate Shape
      GOSUB 30010
      tx = 15
      FOR sy = 0 TO 15
      FOR sx = 0 TO 15
      DEF SEG = &H6810
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE tx + sx * 16, v
      NEXT: tx = tx - 1: NEXT
      GOSUB 30020
      GOTO 21015

21200 REM flip up/down
      GOSUB 30010
      FOR sy = 0 TO 15
      FOR sx = 0 TO 15
      DEF SEG = &H6810
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx + (15 - sy) * 16, v
      NEXT: NEXT
      GOSUB 30020: GOTO 21015

21300 REM flip left/right
      GOSUB 30010
      FOR sy = 0 TO 15
      FOR sx = 0 TO 15
      DEF SEG = &H6810
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE 15 - sx + sy * 16, v
      NEXT: NEXT
      GOSUB 30020: GOTO 21015

21400 REM SHIFT RIGHT
      GOSUB 30010
      FOR sy = 0 TO 15
      FOR sx = 0 TO 14
      DEF SEG = &H6810
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx + 1 + sy * 16, v
      NEXT
      DEF SEG = &H6810
      v = PEEK(sy * 16 + 15)
      DEF SEG = &H6800
      POKE sy * 16, v: NEXT
      GOSUB 30020: GOTO 21015

21500 REM SHIFT LEFT
      GOSUB 30010
      FOR sy = 0 TO 15
      FOR sx = 1 TO 15
      DEF SEG = &H6810
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx - 1 + sy * 16, v
      NEXT
      DEF SEG = &H6810
      v = PEEK(sy * 16 + 0)
      DEF SEG = &H6800
      POKE sy * 16 + 15, v: NEXT
      GOSUB 30020: GOTO 21015

21600 REM SHIFT UP
      GOSUB 30010
      FOR sy = 1 TO 15
      FOR sx = 0 TO 15
      DEF SEG = &H6810
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx + (sy - 1) * 16, v
      NEXT: NEXT
      FOR sx = 0 TO 15
      DEF SEG = &H6810
      v = PEEK(sx)
      DEF SEG = &H6800
      POKE 15 * 16 + sx, v: NEXT
      GOSUB 30020: GOTO 21015

21700 REM SHIFT DOWN
      GOSUB 30010
      FOR sy = 0 TO 14
      FOR sx = 0 TO 15
      DEF SEG = &H6810
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx + (sy + 1) * 16, v
      NEXT: NEXT
      FOR sx = 0 TO 15
      DEF SEG = &H6810
      v = PEEK(sx + 15 * 16)
      DEF SEG = &H6800
      POKE sx, v: NEXT
      GOSUB 30020: GOTO 21015

21800 REM colors set
      COLOR 15
      LOCATE 5, 20: PRINT "color set:"; cs:
      LOCATE 6, 20
      FOR z = 0 TO 7
      COLOR (cs * 8 + z + 1) AND 255:
      PRINT "Û"; : NEXT
      LOCATE 7, 20: COLOR 15
      PRINT "QWERTYUI"
      RETURN

22000 REM INVERSE GRAPHICS AS &HF0
      DEF SEG = &H6800
      FOR qp = 0 TO 255: POKE qp, PEEK(qp) XOR &HF0: NEXT
      GOSUB 30020: GOTO 21015

30000 DEF SEG = 0
      POKE 1047, (PEEK(1047) OR 32 OR 16) AND (255 - 64):
      DEF SEG = &H6800: RETURN

30010 REM TRANSFER SHAPE INTO HIGH BUFFER
      FOR a = 0 TO 256
      DEF SEG = &H6800
      v = PEEK(a)
      DEF SEG = &H6810
      POKE a, v
      NEXT: DEF SEG = &H6800
      RETURN

30020 REM PRINT SHAPE BACK INTO GRILD
      DEF SEG = &H9000
      CALL absolute(&H189)
      RETURN

40000 RUN 40010
40010 COLOR 5
      INPUT "ENTER SAVE NAME"; a$
      IF a$ = "" THEN RUN
      a$ = MID$(a$, 1, 8)
      INPUT "YOU WANT TO SAVE FROM IMAGE 0 TO:"; np
      np = np + 1
      DEF SEG = &H6820
      BSAVE "a:\" + a$ + ".mcg", 0, np * 256: RUN

40100 RUN 40110
40110 COLOR 5
      INPUT "ENTER LOAD NAME"; a$
      IF a$ = "$" THEN SHELL "dir a:\*.mcg /p/w/on": a$ = "": GOTO 40110
      IF a$ = "" THEN RUN
      a$ = MID$(a$, 1, 8)
      DEF SEG = &H6820
      BLOAD "a:\" + a$ + ".mcg", 0: RUN


