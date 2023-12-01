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
    C = I = Z = N = D = B = O = 0;
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
        int data;
        word addr;
        //LDA
        case LDA_I:

            printf("%s", "LDA_I\n");
            PC++;
            data = mem[PC%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            
            break;

        case LDA_Z:
            printf("%s", "LDA_Z\n");
            PC++;
            data = mem[mem[PC]%(0x00FF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            break;

        case LDA_ZX:
            printf("%s", "LDA_ZX\n");
            PC++;
            data = mem[(X+mem[PC])%(0x00FF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            break;

        case LDA_A:

            printf("%s", "LDA_A\n");
            PC++;
            data = mem[mem[PC]%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }

            break;
        
        case LDA_AX:

            printf("%s", "LDA_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }

            break;
        
        case LDA_AY:

            printf("%s", "LDA_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            
            break;


        //LDX
        case LDX_I:

            printf("%s", "LDX_I\n");
            PC++;
            data = mem[PC%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                X = data;
            }
            
            break;

        case LDX_Z:
            printf("%s", "LDX_Z\n");
            PC++;
            data = mem[mem[PC]%(0x00FF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                X = data;
            }
            break;

        case LDX_ZY:
            printf("%s", "LDX_ZY\n");
            PC++;
            data = mem[(Y+mem[PC])%(0x00FF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                X = data;
            }
            break;

        case LDX_A:

            printf("%s", "LDX_A\n");
            PC++;
            data = mem[mem[PC]%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                X = data;
            }

            break;

        case LDX_AY:

            printf("%s", "LDX_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                X = data;
            }
            
            break;

        //LDY
        case LDY_I:

            printf("%s", "LDY_I\n");
            PC++;
            data = mem[PC%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                Y = data;
            }
            
            break;

        case LDY_Z:
            printf("%s", "LDX_Z\n");
            PC++;
            data = mem[mem[PC]%(0x00FF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                Y = data;
            }
            break;

        case LDY_ZX:
            printf("%s", "LDY_ZX\n");
            PC++;
            data = mem[(X+mem[PC])%(0x00FF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                Y = data;
            }
            break;

        case LDY_A:

            printf("%s", "LDY_A\n");
            PC++;
            data = mem[mem[PC]%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                Y = data;
            }

            break;
            
        case LDY_AX:

            printf("%s", "LDY_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(0xFFFF+1)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                Y = data;
            }
            
            break;
        
        //STA
        case STA_Z:
            printf("STA_Z\n");
            PC++;
            addr = mem[PC]%(0x00FF+1);
            mem[addr] = A;
            break;
        
        case STA_ZX:
            printf("STA_Z\n");
            PC++;
            addr = X+mem[PC]%(0x00FF+1);
            mem[addr] = A;
            break;
            
        case STA_A:
            printf("STA_A\n");
            PC++;
            addr = mem[PC]%(0xFFFF+1);
            mem[addr] = A;
            break;
        
        case STA_AX:
            printf("STA_AX\n");
            PC++;
            addr = (X+mem[PC])%(0xFFFF+1);
            mem[addr] = A;
            break;
        
        case STA_AY:
            printf("STA_AY\n");
            PC++;
            addr = (Y+mem[PC])%(0xFFFF+1);
            mem[addr] = A;
            break;
        

        
        //STX
        case STX_Z:
            printf("STX_Z\n");
            PC++;
            addr = mem[PC]%(0x00FF+1);
            mem[addr] = X;
            break;
        case STX_ZY:
            printf("STX_ZY\n");
            PC++;
            addr = (Y+mem[PC])%(0x00FF+1);
            mem[addr] = X;
            break;

        case STX_A:
            printf("STX_A\n");
            PC++;
            addr = mem[PC]%(0xFFFF+1);
            mem[addr] = X;
            break;

        //STY
        case STY_Z:
            printf("STY_Z\n");
            PC++;
            addr = mem[PC]%(0x00FF+1);
            mem[addr] = Y;
            break;
        case STY_ZX:
            printf("STY_ZX\n");
            PC++;
            addr = (X+mem[PC])%(0x00FF+1);
            mem[addr] = Y;
            break;
            
        case STY_A:
            printf("STY_A\n");
            PC++;
            addr = mem[PC]%(0xFFFF+1);
            mem[addr] = Y;
            break;
        

        //Transfers
        case TAX:
            printf("TAX\n");
            flag = A<0 ? Nf: A==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                X = A;
            }
            break;
        case TAY:
            printf("TAY\n");
            flag = A<0 ? Nf: A==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                Y = A;
            }
            break;
        case TXA:
            printf("TXA\n");
            flag = X<0 ? Nf: X==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = X;
            }
            break;
        case TYA:
            printf("TYA\n");
            flag = Y<0 ? Nf: Y==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = Y;
            }
            break;


        //logicals

        //AND
        case AND_I:
            printf("AND_I\n");
            PC++;
            data = mem[PC] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case AND_Z:
            printf("AND_Z\n");
            PC++;
            data = mem[mem[PC]%(0x00FF+1)] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case AND_ZX:
            printf("AND_ZX\n");
            PC++;
            data = mem[(X+mem[PC])%(0x00FF+1)] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case AND_A:
            printf("AND_ZX\n");
            PC++;
            data = mem[mem[PC]%(0xFFFF+1)] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case AND_AX:
            printf("AND_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(0xFFFF+1)] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case AND_AY:
            printf("AND_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(0xFFFF+1)] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        
        //EOR
        case EOR_I:
            printf("EOR_I\n");
            PC++;
            data = mem[PC]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case EOR_Z:
            printf("EOR_Z\n");
            PC++;
            data = mem[mem[PC]%(0x00FF+1)]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case EOR_ZX:
            printf("EOR_ZX\n");
            PC++;
            data = mem[(X+mem[PC])%(0x00FF+1)]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case EOR_A:
            printf("EOR_ZX\n");
            PC++;
            data = mem[mem[PC]%(0xFFFF+1)]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case EOR_AX:
            printf("EOR_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(0xFFFF+1)]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case EOR_AY:
            printf("EOR_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(0xFFFF+1)]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        
        //ORA
        case ORA_I:
            printf("ORA_I\n");
            PC++;
            data = mem[PC]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case ORA_Z:
            printf("ORA_Z\n");
            PC++;
            data = mem[mem[PC]%(0x00FF+1)]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case ORA_ZX:
            printf("ORA_ZX\n");
            PC++;
            data = mem[(X+mem[PC])%(0x00FF+1)]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case ORA_A:
            printf("ORA_ZX\n");
            PC++;
            data = mem[mem[PC]%(0xFFFF+1)]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case ORA_AX:
            printf("ORA_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(0xFFFF+1)]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case ORA_AY:
            printf("ORA_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(0xFFFF+1)]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;

        //jumps and calls
        case JMP:
            printf("JMP\n");
            PC++;
            addr = mem[PC]%0x3FFF + 0xC000;
            PC = addr;
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


