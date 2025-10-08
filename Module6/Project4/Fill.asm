// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.

@SCREEN
D=A
@addr
M=D
@i
M=0
@8192
D=A
@n
M=D

(LISTEN)
    @KBD
    D=M
    @FILL
    D;JNE
    @CLEAR
    D;JEQ

(FILL)
    @i
    D=M // d=value of i
    @n
    D=D-M // D = M[i] - M[n]
    @LISTEN
    D;JEQ // if i reached pixel limit go back to listen
    @i
    D=M
    @addr
    A=D+M //value of i + value of addr 
    M=-1
    @i
    D=M
    D=D+1
    @i
    M=D // i is assigned the value of D
    @LISTEN
    0;JMP

(CLEAR)
    @i
    D=M // d=value of i
    @LISTEN
    D;JLT
    @addr
    A=D+M //value of i + value of addr 
    M=0
    @i
    D=M
    D=D-1
    @i
    M=D // i is assigned the value of D
    @LISTEN
    0;JMP







