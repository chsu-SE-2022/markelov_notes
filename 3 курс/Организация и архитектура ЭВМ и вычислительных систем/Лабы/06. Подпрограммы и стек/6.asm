RD #85
WR R1
RD #14
WR R2
RD #0
WR R3
CALL M
WR R7
RD #100
WR R1
RD #4
WR R2
RD #0
WR R3
CALL M
WR R8
RD #110
WR R1
RD #9
WR R2
RD #0
WR R3
CALL M
WR R9
RD R4
ADD R7
ADD R8
ADD R9
DIV #3
WR R4
OUT
HLT

M: 
RD @R1
JNS M1
RD R1
ADD #1
WR R1
RD R2
SUB #1
WR R2
RD R3
ADD #1
WR R3
RD R2
JZ M2
JMP M
M1: RD R3
JMP M2
M2: RET

