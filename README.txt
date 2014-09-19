README for Assignment 1
P536

Sept 19, 2014

Peter Zhang (yz79)
Eriya Terada (eterada)

Inside the xinu-arm/shell directory:
- We have added the "xsh_hello.c" file.
- We have added the "hello.h" file to the include/ folder.
- We have modified the Makerules file in the shell directory by
  adding "C_FILES += xsh_hello.c"
- We have modified the Makerules file in the apps directory by
  adding "hello.c" to the C_FILES argument
- Within shell.c, we have added "{“hello”, FALSE, xsh_hello}"

Inside xinu-arm/include:
- We have added the line "shellcmd xsh_hello(int, char *[]);"

