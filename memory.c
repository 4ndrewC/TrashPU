#include <stdlib.h>
#include <stdio.h>

typedef unsigned char Byte;
typedef unsigned short Word;

struct Memory{
    Byte zero[256];
    Byte stack[256];
    Byte ram[32256];
    Byte io[16384];
    Byte rom[16384];
};