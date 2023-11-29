#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "memory.c"
#include "flags.h"

//mem[0] stores current rom pointer, mem[1] stores current ram pointer

typedef unsigned short word;
typedef unsigned char byte;

word PC;
word A, SP, P, X, Y;

//status flags
byte flag;

int mem[65536];

void CPUInit(){
    PC = 0xC000;
    SP = 0x10FF;

    A = 0;
    X = 0;
    Y = 0;

}

int readMem(){
    int data = mem[PC];
    // printf("Y should equal this: ");
    // printf("%d", data);
    // printf("\n");
    return data; // return data being read given the address of ram memory
}

void writeMem(int data, word addr){
    mem[addr] = data;
}

void setFlag(){

}

void execute(){;
    switch(mem[PC]){
        case LDA:
        
            printf("%s", "LDA");
            printf("\n");
            
            PC = mem[1];
            mem[1]++;
            // printf("increment mem[1]\n");

            A = readMem();
            // printf("%d", A);
            break;
        
        case LDY:
        
            PC = mem[1];
            mem[1]++;
            Y = readMem();
            break;
        
        case LDX:
        
            printf("%s", "LDX");
            printf("\n");
            PC = mem[1];
            mem[1]++;
            // printf("increment mem[1]\n");
            X = readMem();
            break;
        
        case STA:
        
            PC = mem[0];
            printf("current PC STA opcode: ");
            printf("%d", PC);
            printf("\n");
            mem[0]++;
            // printf("increment mem[0]\n");
            // printf("Y here: ");
            // printf("%d", Y);
            // printf("\n");
            Y = readMem();
            writeMem(A, Y);
            SP--;

            break;
        
        case STX:
        
            PC = mem[0];
            printf("current PC STX opcode: ");
            printf("%d", PC);
            printf("\n");
            mem[0]++;
            // printf("increment mem[0]\n");
            Y = readMem();
            writeMem(X, Y);
            SP--;

            break;
        
        case STY:
        
            PC = mem[0];
            printf("current PC STY opcode: ");
            printf("%d", PC);
            printf("\n");
            mem[0]++;
            // printf("increment mem[0]\n");
            X = readMem();
            writeMem(Y, X);
            SP--;

            break;
        
        case TAX:

            X = A;
            if(X==0){
                flag = Z;
            }
            else if(X<=0){
                flag = N;
            }
            break;
        
        case TAY:
            Y = A;
            if(Y==0){
                flag = Z;
            }
            else if(Y<=0){
                flag = N;
            }
            break;
        
        case TXA:
            A = X;
            if(A==0){
                flag = Z;
            }
            else if(A<=0){
                flag = N;
            }
            break;
        
        case TYA:
            A = Y;
            if(A==0){
                flag = Z;
            }
            else if(A<=0){
                flag = N;
            }
            break;
        
        case TSX:
            X = SP;
            if(X==0){
                flag = Z;
            }
            else if(X<=0){
                flag = N;
            }
            break;
        case TXS:
            SP = X;
        case PHA:
            SP--;
            mem[SP] = A;    
            break;
        case PHP:
            SP--;
            mem[SP] = flag;
            break;
        case PLA:
            A = mem[SP];
            if(A==0){
                flag = Z;
            }
            else if(A<=0){
                flag = N;
            }
            break;
        case PLP:
            flag = mem[SP];
            break;
    }
}

void fetch(){
    
    PC = mem[0];
    printf("current PC fetch: ");
    printf("%d", PC);
    printf("\n");
    mem[0]++;
    // printf("increment mem[0]\n");
    printf("current instruction: ");
    printf("%d", mem[PC]);
    printf("\n");
    execute();
}


int main(){
    CPUInit();

    //ram section
    mem[0x0200] = 34;
    mem[0x0201] = 23;
    mem[0x0202] = 89;


    //rom section
    mem[0xC000] = 1;
    mem[0xC001] = 4;
    mem[0xC002] = 0x0210;
    mem[0xC003] = 3;
    mem[0xC004] = 5;
    mem[0xC005] = 0x0211;
    mem[0xC006] = 2;
    mem[0xC007] = 6;
    mem[0xC008] = 0x0212;

    //initialize zero page address pointers
    mem[0] = 0xC000; 
    mem[1] = 0x0200; 

    fetch();
    fetch();
    fetch();
    fetch();
    fetch();
    fetch();
    
    printf("%d", mem[0x0211]);
    // printf("\n");
    // printf("%d", SP);
    
    return 0;
}