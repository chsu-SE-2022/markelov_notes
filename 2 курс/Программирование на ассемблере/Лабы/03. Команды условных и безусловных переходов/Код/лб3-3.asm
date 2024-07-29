CODE SEGMENT
	ORG 100h  
	ASSUME DS:CODE
Start: 

MOV CL, k
MOV BL, a
MOV DL, c
CMP BL, b
JBE f

f:
MOV AL, BL
XOR AH, AH
IDIV h
ADD AH, AL
CMP AH, CL
JZ true 
INC BL
CMP BL, b 
JBE f
CMP BL, b 
JA stop

true:
INC DL
INC BL
CMP BL, b 
JBE f
CMP BL, b 
JA stop

stop:
MOV AL, DL
XOR AH, AH
INT 21h

k DB 12
a DB 10
b DB 99
c DB 0
h DB 10 
	                       
 
CODE ENDS
	END  Start   
	
	