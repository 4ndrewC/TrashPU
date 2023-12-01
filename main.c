#include <stdio.h>
#include <stdlib.h>
#include "cpu.c"

int main(){
    CPUInit();

    //ram section
    // mem[0x0000] = 20;
    mem[0x0001] = 3;
    mem[0x0005] = 89;
    mem[0x0008] = 78;
    // mem[0x0003] = -2;
    // mem[0x0009] = 23;
    // mem[0x0090] = 0x0091;
    

    //rom section
    // mem[0xC000] = 0xA9;
    // mem[0xC001] = 78;
    // //loaded A with 23
    // mem[0xC002] = 0xBD;
    // mem[0xC003] = 0x0000;
    // //tried to load A with -2, but negative flag raised
    // mem[0xC004] = 0xB1;
    // mem[0xC005] = 0x0001;
    // mem[0xC006] = 0x8D;
    // mem[0xC007] = 0x0001;

    // //test STA_ZX
    // mem[0xC008] = 0x95;
    // mem[0xC009] = 0x0000;

    // //test STA_IX
    // mem[0xC00A] = 0x81;
    // mem[0xC00B] = 0x0090;

    //testing LDY instructions
    mem[0xC000] = 0xA6;
    mem[0xC001] = 0x0001;
    mem[0xC002] = 0xBC;
    mem[0xC003] = 0x0005;

    //testing STX/STY
    mem[0xC004] = 0x84;
    mem[0xC005] = 0x0032;

    //testing transfers
    mem[0xC006] = 0x98;
    mem[0xC007] = 0xAA;


    

    

    

    fetch();
    fetch();
    fetch();
    fetch();
    fetch();
    // fetch();
    // fetch();
    // fetch();
    
    
    printf("%d", X);
    // printf("\n");
    // printf("%d", SP);
    
    return 0;
}