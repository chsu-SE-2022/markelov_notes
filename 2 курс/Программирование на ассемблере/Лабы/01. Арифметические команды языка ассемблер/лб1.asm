; (a-b+c*2)/(d+5)
CODE SEGMENT
	ORG 100h  
	ASSUME DS:CODE
	     
Start:

MOV BX, a
SUB BX, b   ; a-b=BX-b=12-8=4  result in BX
MOV AX, c
IMUL h       ; c*2=AX*h=2*2=4  result in AX
ADD AX, BX  ; (a-b+c*2)=AX+BX=4+4=8 result in AX

MOV BX, d   
ADD BX, 5   ; d+5=BX+5=3+5=8
XOR DX, DX
IDIV BX     ; (a-b+c*2)/(d+5) = AX/BX = 8/8=1  result in AX

MOV AH, 0
INT 21h

a DW 13
b DW 8
c DW 2
d DW 3
h DW 2	
 
CODE ENDS
	END  Start               