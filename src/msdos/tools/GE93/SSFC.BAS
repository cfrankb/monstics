
      REM GRAPHICS EDITOR 93 for SSFC
      REM by Francois Blanchette
      REM all rights reserved!
    
      DEF SEG = &H9010
      BLOAD "c:\other\ge93\ssfc.mxe", 0
      
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
21000 hd = (ec + e% * 4) * 256:
      sa = hd
      sh = sa / 256!
      sl = (sh - INT(sh)) * 256!
      COLOR 15: LOCATE 1, 20: PRINT "Segment:"; ec; "Frame:"; e%
      GOSUB 21800

      DEF SEG = &H9000
      POKE 0, 0: POKE 1, &H69
      POKE 2, 0: POKE 3, &HA0
      POKE 4, 0: POKE 5, e% * 4
      POKE 6, &HA0: POKE 7, &HA
      
      POKE &HC, sl: POKE &HD, sh
      POKE &HE, 0: POKE &HF, 0

      DEF SEG = &H9010
      CALL absolute(0)
      CALL absolute(&H189)
      CALL absolute(&H119)

21010 REM Editor's grild
      ck$ = "qwertyui"
      x = 0: y = 0
21015 DEF SEG = &H6800:
      pc = PEEK(x + y * 16)
21020 REM Little cursor flash
      DEF SEG = &H9000
      POKE 8, x: POKE 9, y

      DEF SEG = &H9010
      CALL absolute(&H3F)
     
      DEF SEG = &H6800

21030 REM Cursor moving routine
      GOSUB 30000: a$ = INKEY$: wx = x: wy = y
      IF a$ = "8" AND y > 0 THEN wy = y - 1: GOTO 21040
      IF a$ = "2" AND y < 15 THEN wy = y + 1: GOTO 21040
      IF a$ = "4" AND x > 0 THEN wx = x - 1: GOTO 21040
      IF a$ = "6" AND x < 15 THEN wx = x + 1: GOTO 21040
      IF a$ = CHR$(13) THEN 21060
      IF a$ = "b" AND ec > 0 THEN ec = ec - 1: GOTO 21000
      IF a$ = "n" AND ec < 2 THEN ec = ec + 1: GOTO 21000
      IF a$ = "z" AND e% > 0 THEN e% = e% - 1: GOTO 21000
      IF a$ = "x" THEN e% = e% + 1: GOTO 21000
      DEF SEG = 2
      IF PEEK(&H3F8) = 2 THEN 40000
      IF PEEK(&H3F8) = 1 THEN 40100
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
      IF a$ = "[" AND cs > 0 THEN cs = cs - 1: GOSUB 21800
      IF a$ = "]" AND cs < 32 THEN cs = cs + 1: GOSUB 21800
      IF a$ = "\" THEN 21057
      IF a$ = "`" THEN pc = 19: GOTO 21057
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
      FOR x = 0 TO 15
      DEF SEG = &H6800
      v = PEEK(x + y * 16)
      DEF SEG = &H6900
      POKE hd + x + y * 16, v
      NEXT
      NEXT: GOTO 21000

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
      DEF SEG = &H6840
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
      DEF SEG = &H6840
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx + (15 - sy) * 16, v
      NEXT: NEXT
      GOSUB 30020: GOTO 21015

21300 REM flip left/right
      GOSUB 30010
      FOR sy = 0 TO 15
      FOR sx = 0 TO 15
      DEF SEG = &H6840
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE 15 - sx + sy * 16, v
      NEXT: NEXT
      GOSUB 30020: GOTO 21015

21400 REM SHIFT RIGHT
      GOSUB 30010
      FOR sy = 0 TO 15
      FOR sx = 0 TO 14
      DEF SEG = &H6840
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx + 1 + sy * 16, v
      NEXT
      DEF SEG = &H6840
      v = PEEK(sy * 16 + 15)
      DEF SEG = &H6800
      POKE sy * 16, v: NEXT
      GOSUB 30020: GOTO 21015

21500 REM SHIFT LEFT
      GOSUB 30010
      FOR sy = 0 TO 15
      FOR sx = 1 TO 15
      DEF SEG = &H6840
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx - 1 + sy * 16, v
      NEXT
      DEF SEG = &H6840
      v = PEEK(sy * 16 + 0)
      DEF SEG = &H6800
      POKE sy * 16 + 15, v: NEXT
      GOSUB 30020: GOTO 21015

21600 REM SHIFT UP
      GOSUB 30010
      FOR sy = 1 TO 15
      FOR sx = 0 TO 15
      DEF SEG = &H6840
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx + (sy - 1) * 16, v
      NEXT: NEXT
      FOR sx = 0 TO 15
      DEF SEG = &H6840
      v = PEEK(sx)
      DEF SEG = &H6800
      POKE 15 * 16 + sx, v: NEXT
      GOSUB 30020: GOTO 21015

21700 REM SHIFT DOWN
      GOSUB 30010
      FOR sy = 0 TO 14
      FOR sx = 0 TO 15
      DEF SEG = &H6840
      v = PEEK(sx + sy * 16)
      DEF SEG = &H6800
      POKE sx + (sy + 1) * 16, v
      NEXT: NEXT
      FOR sx = 0 TO 15
      DEF SEG = &H6840
      v = PEEK(sx + 15 * 16)
      DEF SEG = &H6800
      POKE sx, v: NEXT
      GOSUB 30020: GOTO 21015

21800 REM colors set
      COLOR 15
      LOCATE 5, 25: PRINT "color set:"; cs:
      LOCATE 6, 25
      FOR z = 0 TO 7
      COLOR (cs * 8 + z + 1) AND 255:
      PRINT "Û"; : NEXT
      LOCATE 7, 25: COLOR 15
      PRINT "QWERTYUI"
      RETURN

30000 DEF SEG = 0
      POKE 1047, (PEEK(1047) OR 32 OR 16) AND (255 - 64):
      DEF SEG = &H6800: RETURN

30010 REM TRANSFER SHAPE INTO HIGH BUFFER
      FOR a = 0 TO 256
      DEF SEG = &H6800
      v = PEEK(a)
      DEF SEG = &H6840
      POKE a, v
      NEXT: DEF SEG = &H6800
      RETURN

30020 REM PRINT SHAPE BACK INTO GRILD
      DEF SEG = &H9010
      CALL absolute(&H119)
      RETURN

40000 RUN 40010
40010 COLOR 5
      INPUT "ENTER SAVE NAME"; a$
      IF a$ = "" THEN RUN
      INPUT "SAVE FROM FRAME 0 TO:"; np
      IF np = 0 THEN np = 3: z = 1
      IF z = 0 THEN np = (np + 1) * 4
      DEF SEG = &H6900
      BSAVE "a:\!sprites\" + a$ + ".mcg", 0, np * 256: RUN


40100 RUN 40110
40110 COLOR 5
      INPUT "ENTER LOAD NAME"; a$
      IF a$ = "$" THEN SHELL "dir a:\!sprites\*.*/w/p": a$ = "": GOTO 40110
      IF a$ = "" THEN RUN
      DEF SEG = &H6900
      BLOAD "a:\!sprites\" + a$ + ".mcg", 0: RUN

