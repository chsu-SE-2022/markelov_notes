CODE SEGMENT
	ORG 100h  
	ASSUME DS:CODE
Start:

MOV AL, a
CMP AL, b
JBE maxB
CMP AL, c
JBE maxC
MOV d, AL
MOV DL, d
MOV AH, 0
INT 21h

maxB:
MOV BL, b
CMP BL, c
JBE maxC
MOV d, BL
MOV DL, d
MOV AH, 0
INT 21h

maxC:
MOV CL, c
MOV d, CL
MOV DL, d
MOV AH, 0
INT 21h	

a DB 5
b DB 9
c DB 7
d DB 0                       
 
CODE ENDS
	END  Start