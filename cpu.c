#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "flags.h"

//mem[0] stores current rom pointer, mem[1] stores current ram pointer

typedef unsigned short word;
typedef unsigned char byte;

word PC;
word A, SP, P, X, Y;

//status flags
byte flag;
byte C, Z, N, I, D, B, O;

int mem[65536];

void CPUInit(){
    PC = 0xC000;
    SP = 0x10FF;

    A = 0;
    X = 0;
    Y = 0;

}

int readMem(word addr){
    int data = mem[addr];
    return data; // return data being read given the address of ram memory
}

void writeMem(byte data, word addr){
    mem[addr] = data;
}

void setFlag(){
    C = 0;
    Z = 0;
    I = 0;
    N = 0;
    D = 0;
    B = 0;
    O = 0;
    switch(flag){
        case Cf:
            C = 1;
            break;
        case Zf:
            Z = 1;
            break;
        case If:
            I = 1;
            break;
        case Nf:
            N = 1;
            break;
        case Df:
            D = 1;
            break;
        case Bf:
            B = 1;
            break;
        case Of:
            O = 1;
            break;
    }
}

void execute(){;
    switch(mem[PC]){
        word data;
        word addr;
        //LDA
        case LDA_I:

            printf("%s", "LDA_I");
            printf("\n");   
            PC++;
            data = mem[PC%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            
            break;

        case LDA_Z:
            printf("%s", "LDA_Z");
            printf("\n");   
            PC++;
            data = mem[mem[PC]%(0x00FF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            break;

        case LDA_ZX:
            printf("%s", "LDA_ZX");
            printf("\n");   
            PC++;
            data = mem[X+mem[PC]%(0x00FF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            break;

        case LDA_A:

            printf("%s", "LDA_A");
            printf("\n");   
            PC++;
            data = mem[mem[PC]%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }

            break;
        
        case LDA_AX:

            printf("%s", "LDA_AX");
            printf("\n");   
            PC++;
            data = mem[X+mem[PC]%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }

            break;
        
        case LDA_AY:

            printf("%s", "LDA_AY");
            printf("\n");   
            PC++;
            data = mem[Y+mem[PC]%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            
            break;
        
        case LDA_IX:

            printf("%s", "LDA_IX");
            printf("\n");   
            PC++;
            data = mem[X+(mem[mem[PC]%(0xFFFF+1)]%(0xFFFF+1))];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            
            break;
        
        case LDA_IY:

            printf("%s", "LDA_IY");
            printf("\n");   
            PC++;
            data = mem[Y+(mem[mem[PC]%(0xFFFF+1)]%(0xFFFF+1))];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            
            break;
        
        //STA
        case STA_Z:
            printf("STA_Z");
            printf("\n");
            PC++;
            addr = mem[PC]%(0x00FF+1);
            mem[addr] = A;
            break;
        
        case STA_ZX:
            printf("STA_Z");
            printf("\n");
            PC++;
            addr = X+mem[PC]%(0x00FF+1);
            mem[addr] = A;
            break;
            break;
        
    }
}

void fetch(){

    printf("PC fetch addr: ");
    printf("%d", PC);
    printf("\n");
    printf("current instruction: ");
    printf("%d", mem[PC]);
    printf("\n");
    // printf("increment mem[0]\n");

    execute();
    PC++;
}


