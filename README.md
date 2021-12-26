# Brainfuck Interpreter #
An Interpreter for Brainfuck Programming Language

## Precompiled Binaries ##
You can use the binaries given in the ```binaries``` folder if you have a Windows/Linux machine with a x64 processor. Else you can compile the given source code for your machine.

## Instructions to compile ## 

You can use the provided makefile to create a binary for your machine. This makefile requires that you have GCC compiler preinstalled. 

[or]

Just compile the given ```brainfuck.c``` program with any C compiler.

## Program execution ##
Write your brainfuck program in a file, save it (preferably with .bf extension), and execute the binary with your brainfuck program as the first argument.

## Things to note ##
* This interpreter does not require the file extension of your program to be '.bf'. It can read any text file.
* All the errors are directed to stdout stream and not to stderr stream.
* Code written in one OS may not work as expected when executed by an interpreter created for a different OS due to differences in newline standards. Please write and execute your code on the same OS. Else, make appropriate conversions.




