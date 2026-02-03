;(a & 4 - (b + c | 8) * 2) / !((d ^ 1) + 5)
CODE SEGMENT
	ORG 100h  
	ASSUME DS:CODE
Start:

MOV AX, a
MOV BX, b
MOV CX, c
MOV DX, d

ADD BX, CX ; BX+CX (b+c) = 25(19) - result in BX
OR BX, 8   ; BX OR 8 (b + c | 8) = 25(19) - result in BX
SHL BX, 1  ; BX * 2 (b + c | 8) * 2 = 50(32) - result in BX
MOV CX, 4
SUB CX, BX ; CX - BX (4 - ((b + c | 8) * 2)) = 46(2E)  - result in CX
AND AX, CX ; AX AND CX (a & 4 - (b + c | 8) * 2) = 2 - result in AX

XOR DX, 1  ; DX XOR 1 = 11(B) - result in DX
ADD DX, 5  ; DX+5 ((d ^ 1) + 5) = 16(10) - result in DX
NOT DX    ; -DX = -16(-10) - result in DX

MOV BX, DX
XOR DX, DX
IDIV BX 

MOV AH, 0
INT 21h

a DW -12
b DW -6
c DW -19
d DW -21	
 
CODE ENDS
	END  Start