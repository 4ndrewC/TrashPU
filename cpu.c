#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "instructions.h"
#include "flags.h"
#include "memory.c"

//mem[0] stores current rom pointer, mem[1] stores current ram pointer

typedef uint16_t word;
typedef uint8_t byte;

word PC;
word A, SP, P, X, Y;

//status flags
byte flag;
byte C, Z, N, I, D, B, O;
word maxWrite = 0xC000;
int maxRead = 0xFFFF+1;


void CPUInit(){
    memoryInit();
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
    I = Z = N = D = B = 0;
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

void setArithFlags(byte op, byte ac, int res){
    I = Z = N = D = B = 0;
    C = (res>0xFF)?1:0;
    O = ((ac^op) & 0x80) && ((ac^res) & 0x80);
    N = (res & 0x80)?1:0;
    Z = (res==0)?1:0;
    A = (byte)res;
}

void execute(){;
    switch(mem[PC]){
        int data;
        word addr;
        int res;
        //LDA
        case LDA_I:

            printf("%s", "LDA_I\n");
            PC++;
            data = mem[PC%(maxRead)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }
            
            break;

        case LDA_A:

            printf("%s", "LDA_A\n");
            PC++;
            data = mem[mem[PC]%(maxWrite)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }

            break;
        
        case LDA_AX:

            printf("%s", "LDA_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(maxWrite)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                A = data;
            }

            break;
        
        case LDA_AY:

            printf("%s", "LDA_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(maxWrite)];
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
            data = mem[PC%(maxRead)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                X = data;
            }
            
            break;

        case LDX_A:

            printf("%s", "LDX_A\n");
            PC++;
            data = mem[mem[PC]%(maxWrite)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                X = data;
            }

            break;

        case LDX_AY:

            printf("%s", "LDX_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(maxWrite)];
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
            data = mem[PC%(maxRead)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                Y = data;
            }
            
            break;

        case LDY_A:

            printf("%s", "LDY_A\n");
            PC++;
            data = mem[mem[PC]%(maxWrite)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                Y = data;
            }

            break;
            
        case LDY_AX:

            printf("%s", "LDY_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(maxWrite)];
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            if(!(N || Z)){
                Y = data;
            }
            
            break;
        
        //STA
        case STA_A:
            printf("STA_A\n");
            PC++;
            addr = mem[PC]%(maxWrite);
            mem[addr] = A;
            break;
        
        case STA_AX:
            printf("STA_AX\n");
            PC++;
            addr = (X+mem[PC])%(maxWrite);
            mem[addr] = A;
            break;
        
        case STA_AY:
            printf("STA_AY\n");
            PC++;
            addr = (Y+mem[PC])%(maxWrite);
            mem[addr] = A;
            break;
        

        
        //STX
        case STX_A:
            printf("STX_A\n");
            PC++;
            addr = mem[PC]%(maxWrite);
            mem[addr] = X;
            break;

        //STY
            
        case STY_A:
            printf("STY_A\n");
            PC++;
            addr = mem[PC]%(maxWrite);
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
            data = mem[PC%maxRead] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case AND_A:
            printf("AND_ZX\n");
            PC++;
            data = mem[mem[PC]%(maxWrite)] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case AND_AX:
            printf("AND_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(maxWrite)] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case AND_AY:
            printf("AND_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(maxWrite)] & A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        
        //EOR
        case EOR_I:
            printf("EOR_I\n");
            PC++;
            data = mem[PC%maxRead]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case EOR_A:
            printf("EOR_ZX\n");
            PC++;
            data = mem[mem[PC]%(maxWrite)]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case EOR_AX:
            printf("EOR_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(maxWrite)]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case EOR_AY:
            printf("EOR_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(maxWrite)]^A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        
        //ORA
        case ORA_I:
            printf("ORA_I\n");
            PC++;
            data = mem[PC%maxRead]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case ORA_A:
            printf("ORA_ZX\n");
            PC++;
            data = mem[mem[PC]%(maxWrite)]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case ORA_AX:
            printf("ORA_AX\n");
            PC++;
            data = mem[(X+mem[PC])%(maxWrite)]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;
        case ORA_AY:
            printf("ORA_AY\n");
            PC++;
            data = mem[(Y+mem[PC])%(maxWrite)]|A;
            flag = data<0 ? Nf: data==0 ? Zf: 0;
            setFlag();
            break;

        //jumps and calls
        case JMP:
            printf("JMP\n");
            PC++;
            addr = mem[PC]%(0x3FFF+1) + 0xC000;
            PC = addr;
            break;
        
        //arithmetic
        //add with carry
        case ADC_I:
            printf("ADC_I\n");
            PC++;
            data = mem[PC%(maxRead)];
            res = data + A + C;
            setArithFlags(data, A, res);
            
            break;
        case ADC_A:
            printf("ADC_A\n");
            PC++;
            addr = mem[PC%(maxRead)]%maxWrite;
            data = mem[addr];
            res = data + A + C;
            setArithFlags(data, A, res);
            break;
        case ADC_AX:
            printf("ADC_AX\n");
            PC++;
            addr = (X+mem[PC%(maxRead)])%maxWrite;
            data = mem[addr];
            res = data + A + C;
            setArithFlags(data, A, res);
            break;
        case ADC_AY:
            printf("ADC_AY\n");
            PC++;
            addr = (Y+mem[PC%(maxWrite)])%maxWrite;
            data = mem[addr];
            res = data + A + C;
            setArithFlags(data, A, res);
            break;
        
        //subtract with carry
        case SBC_I:
            printf("SBC_I\n");
            PC++;
            data = mem[PC%(maxRead)];
            res = data - A - C;
            setArithFlags(data, A, res);
            break;
        case SBC_A:
            printf("SBC_A\n");
            PC++;
            addr = mem[PC%(maxRead)]%maxWrite;
            data = mem[addr];
            res = data - A - C;
            setArithFlags(data, A, res);
            break;
        case SBC_AX:
            printf("SBC_AX\n");
            PC++;
            addr = (X+mem[PC%(maxRead)])%maxWrite;
            data = mem[addr];
            res = data - A - C;
            setArithFlags(data, A, res);
            break;
        case SBC_AY:
            printf("SBC_AY\n");
            PC++;
            addr = (Y+mem[PC%(maxWrite)])%maxWrite;
            data = mem[addr];
            res = data - A - C;
            setArithFlags(data, A, res);
            break;

    }
}

void fetch(){

    // printf("PC fetch addr: ");
    // printf("%d", PC);
    // printf("\n");
    // printf("current instruction: ");
    // printf("%d", mem[PC]);
    // printf("\n");

    execute();
    PC++;
}


