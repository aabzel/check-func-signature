This program verifies that the header file contains all the C function prototypes that are determined in the *.c file.
It is needed when C code migrates to another compiler to eliminate build errors in project.
C function prototypes may be multi-line in .c file. That utility extracts them.

This program will allow you to check the quality of the code automatically and maintain the production code culture in your team in that issue.

There is not reliable tool to extract C functions prototypes from .c file.
1) cproto fails on "#includes" lines.
2) "ctags.exe -x --c-kinds=fp --fields=+S -V file.c" is unable to parse multi-line C function prototypes

Thus, I did my custom tool.
