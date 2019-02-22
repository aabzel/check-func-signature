There is not reliable tool to extract functions prototypes from .c file.

cproto fails on #includes lines.

ctags.exe -x --c-kinds=fp --fields=+S -V file.c
unable to parse multi-line C function prototypes
