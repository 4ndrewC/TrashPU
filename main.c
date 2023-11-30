#include <stdio.h>
#include <stdlib.h>
#include "cpu.c"

int main(){
    CPUInit();

    //ram section
    mem[0x0000] = 20;
    mem[0x0001] = 0x0002;
    mem[0x0003] = 40;
    mem[0x0009] = 23;
    X = 9;
    Y = 1;
    

    //rom section
    mem[0xC000] = 0xA9;
    mem[0xC001] = 78;
    mem[0xC002] = 0xBD;
    mem[0xC003] = 0x0000;
    mem[0xC004] = 0xB1;
    mem[0xC005] = 0x0001;
    mem[0xC006] = 0x85;
    mem[0xC007] = 0x0100;
    mem[0xC008] = 0x95;
    mem[0xC009] = 0x0000;
    

    fetch();
    fetch();
    fetch();
    fetch();
    fetch();
    
    
    printf("%d", mem[0x0009]);
    // printf("\n");
    // printf("%d", SP);
    
    return 0;
}