
This program verifies that the header files contain all the prototypes that are declared in the *.c file.
It is needed when code migrates to another compiler to eliminate  build errors in project.
C function prototypes may be multi-line in .c file. That utility extracts them.

This program will allow you to check the quality of the code automatically and maintain the production culture in the company in that issue.

There is not reliable tool to extract C functions prototypes from .c file.
1) cproto fails on "#includes" lines.
2) "ctags.exe -x --c-kinds=fp --fields=+S -V file.c" unable to parse multi-line C function prototypes

Thus, I did my custom tool.
