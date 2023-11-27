#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "memory.c"

//mem[0] stores current rom pointer, mem[1] stores current ram pointer

int IR, A, X, Y, SP, PC;
int mem[65536];

void CPUInit(){
    PC = 0xC000;
    SP = 255;

    A = 0;
    X = 0;
    Y = 0;
}

int readMem(){
    int data;
    //if current instruction is STA STX or STY
    if(mem[PC]==4 || mem[PC]==5 || mem[PC]==6){
        // printf("it is reading from rom");
        // read from rom
        PC = mem[0];
        
        data = mem[PC];
        // printf("%d", data);
        mem[0]++;
        return data;
    }
    PC = mem[1]; //pc gets the address of next data from ram memory
    data = mem[PC];
    mem[1]++;
    return data; // return data being read given the address of ram memory
}

void writeMem(int data){
    mem[Y] = data;
}

void execute(int instruction){
    IR = instruction;
    switch(IR){
        case LDA:
            // printf("%s", "LDA");
            A = readMem();
            // printf("%d", A);
            break;
        case LDY:
            Y = readMem();
            break;
        case LDX:
            X = readMem();
            break;
        case STA:
            // printf("STA");
            //readmem() only reads ram memory, not rom memory, so it will not fetch the address stored in the next address of rom
            Y = readMem();
            // printf("%s", "write");
            // printf("%d", Y);
            writeMem(A);
    }
}

void fetch(){
    
    PC = mem[0];
    int instruction = mem[PC];
    mem[0]++;
    execute(instruction);
}

struct CPU{
    // capture states
    Byte C : 1;
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte O : 1;
    Byte N : 1;
};

int main(){
    CPUInit();

    //ram section
    mem[0x0200] = 34;

    //rom section
    mem[0xC000] = 1;
    mem[0xC001] = 4;
    mem[0xC002] = 0x0203;

    //initialize zero page address pointers
    mem[0] = 0xC000; 
    mem[1] = 0x0200; 
    fetch();
    fetch();
    printf("%d", mem[0x0203]);
    
    return 0;
}