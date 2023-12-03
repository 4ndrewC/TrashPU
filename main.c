#include <stdio.h>
#include <stdlib.h>
#include "cpu.c"

int main(){
    CPUInit();

    while(1){
        fetch();
        printf("%d\n", A);
    }
    
    return 0;
}