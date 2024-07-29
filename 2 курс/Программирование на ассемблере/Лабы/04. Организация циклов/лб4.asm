.model tiny
.stack 100h
.CODE
Start: 

MOV SI, i
MOV CX, n
MOV DI, result

M1:
MOV AX, j
IMUL h
ADD AX, SI
ADD DI, AX
INC SI

LOOP M1

INT 21h
                     
    END  Start