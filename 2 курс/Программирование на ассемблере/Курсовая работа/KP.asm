.MODEL LARGE
.STACK 100H

.DATA
FOOD STRUC
DISH DB 255 DUP (?)
PRODUCT DB 255 DUP (?)
MEAT DB ?
CCAL DW ?
FOOD ENDS
D FOOD<'Seld pod shuboy','Seld',0,189>, <'Olivye','Kolbasa',1,150>, <'Kartofel pecheniy', 'Kartofel', 0, 145>, <'Myaso po-francuzski', 'Myaso', 1, 264>, <'Kraboviy salat', 'Krabovie palochki', 0, 128>, <'Buterbrod s ikroy', 'Ikra', 0, 180>, <'Holodec', 'Myaso', 1, 350>, <'Zalivnaya riba', 'Riba', 0, 100>, <'Salat Mimoza', 'Kartofel', 0, 183>, <'Shokoladniy pirog', 'Muka', 0, 478>
;D FOOD<'Cezar','Salat',1,218>, <'Ovoshnoy salat', 'Ogurets', 0, 20>, <'Yaichnitsa s kolbasoy','Yaico',1,230>, <'Sharlotka', 'Muka', 0, 145>, <'Kuritsa pechenaya', 'Kuritsa', 1, 223>, <'Lazanya', 'Makaroni', 1, 244>, <'Golubci', 'Kapusta', 1, 139>, <'Cheburek', 'Muka', 1, 279>, <'Mannaya kasha', 'Mannaya krupa', 0, 83>, <'Shashlik', 'Myaso', 1, 180>
;D FOOD<'Cezar','Salat',1,218>, <'Yaichnitsa s kolbasoy','Yaico',1, 230>, <'Lazanya', 'Makaroni', 1, 244>, <'Golubci', 'Kapusta', 1, 139>, <'Cheburek', 'Muka', 1, 279>, <'Shashlik', 'Myaso', 1, 180>,  <'Olivye','Kolbasa',1,150>,  <'Holodec', 'Myaso', 1, 350>, <'Myaso po-francuzski', 'Myaso', 1, 264>, <'Kuritsa pechenaya', 'Kuritsa', 1, 223> 
;D FOOD<'Seld pod shuboy','Seld',0,189>, <'Kartofel pecheniy', 'Kartofel', 0, 145>, <'Kraboviy salat', 'Krabovie palochki', 0, 128>, <'Buterbrod s ikroy', 'Ikra', 0, 180>, <'Zalivnaya riba', 'Riba', 0, 100>, <'Salat Mimoza', 'Kartofel', 0, 183>, <'Shokoladniy pirog', 'Muka', 0, 478>, <'Ovoshnoy salat', 'Ogurets', 0, 20>, <'Mannaya kasha', 'Mannaya krupa', 0, 83>, <'Sharlotka', 'Muka', 0, 145>
;D FOOD<'Seld pod shuboy','Seld',0,189>, <'Kartofel pecheniy', 'Kartofel', 0, 145>, <'Kraboviy salat', 'Krabovie palochki', 0, 128>, <'Holodec', 'Myaso', 1, 350>, <'Salat Mimoza', 'Kartofel', 0, 183>, <'Cezar','Salat',1,218>, <'Yaichnitsa s kolbasoy','Yaico',1,230>, <'Kuritsa pechenaya', 'Kuritsa', 1, 223>, <'Golubci', 'Kapusta', 1, 139>, <'Mannaya kasha', 'Mannaya krupa', 0, 83>

.CODE
Start:

    MOV AX, @DATA
    MOV DS, AX
    XOR AX, AX
    MOV CX, 10
    XOR BX, BX
    XOR DI, DI
    CMP CX, 0
    JA M1
    JMP stop
               
    M1: 
        XOR DL, DL
        MOV DL, D.MEAT[BX] 
        CMP DL, 0      
        JE M2
        ADD BX, TYPE FOOD
        DEC CX
        CMP CX, 0
        JA M1
        JMP stop
        
    M2: 
        INC DI
        ADD BX, TYPE FOOD
        DEC CX
        CMP CX, 0
        JA M1
        JMP stop
               
    stop:
    MOV AX, 4C00h
    INT 21h

END Start

