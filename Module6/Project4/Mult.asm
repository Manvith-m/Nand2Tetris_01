// Mult.asm
// Multiplies R0 * R1 and stores result in R2

@R0
D=M // D = R0
@a
M=D // a = R0

@R1
D=M // D = R1
@b
M=D // b = R1

@result
M=0 // result = 0

// check if a == 0 → goto END
@a
D=M
@RESULT
D;JEQ

// check if b == 0 → goto END
@b
D=M
@RESULT
D;JEQ

(LOOP)

@b
D=M
@result
M=D+M // result = result + b

@a
M=M-1 // a = a - 1
D=M
@RESULT
D;JEQ

@LOOP
0;JMP // repeat

(RESULT)
@result
D=M
@R2
M=D // store result into R2
@END
0;JMP // infinite loop to stop