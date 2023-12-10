#include <stdio.h>
#include <stdlib.h>
#include "cpu.c"

int main(){
    memoryInit();
    CPUInit();

    while(PC<=0xFFFE){
        fetch();
        // printf("%d\n", A);
    }

    // mem[0xC000] = 0xA9;
    // mem[0xC001] = 1;
    // mem[0xC002] = 0x8D;
    // mem[0xC003] = 0x0000;
    // mem[0xC004] = 0xA9;
    // mem[0xC005] = 3;
    // mem[0xC006] = 0xC9;
    // mem[0xC007] = 3;
    // mem[0xC008] = 0xF0;
    // mem[0xC009] = 0;

    // fetch();
    // fetch();
    // fetch();
    // fetch();
    // fetch();
    // fetch();
    // fetch();
    // fetch();
    // fetch();
    // fetch();
    // fetch();
    // fetch();


    

    // printf("%d", mem[0x0000]);

    return 0;
}