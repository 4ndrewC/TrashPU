#include <stdio.h>
#include <stdlib.h>
#include "cpu.c"
#include "pageinfo.h"
#include "meminfo.h"

//can store a few tasks, each task by default takes up 64kb
byte disk[10000000];
byte diskop[10000000];

byte mmu[PAGES];
byte space[PAGES];
byte tasktracker[PAGES];
//need something to map task numbers to virtual location for PC
//arbitrarily set maximum tasks to 1000

//finding open slot for new page to be swapped in
word scan(int req_pages){
    for(word i = 6144; i<PAGES; i++){
        //add space[i]>req_pages later
        if(mmu[i]==0){
            return i;
        }
    }
}

void loadRegisters(int task, int loc){
    int regstart = (task-1)*13;
    //only PC register must reflect physical state
    PC = loc;

    A = mem[regstart+1];
    SP = mem[regstart+2];
    X = mem[regstart+3];
    Y = mem[regstart+4];
    flag = mem[regstart+5];
    C = mem[regstart+6];
    Z = mem[regstart+7];
    N = mem[regstart+8];
    I = mem[regstart+9];
    D = mem[regstart+10];
    B = mem[regstart+11];
    O = mem[regstart+12];
}

void saveRegisters(int task, int loc){
    int regstart = (task-1)*13;
    //no need to save PC anywhere since it is physical location
    mem[regstart+1] = A;
    mem[regstart+2] = SP;
    mem[regstart+3] = X;
    mem[regstart+4] = Y;
    mem[regstart+5] = flag;
    mem[regstart+6] = C;
    mem[regstart+7] = Z;
    mem[regstart+8] = N;
    mem[regstart+9] = I;
    mem[regstart+10] = D;
    mem[regstart+11] = B;
    mem[regstart+12] = O;
}

//swap after every burst
void swapout(int loc, int req_pages){
    int ta = tasktracker[loc];
    //disk loc or virtual loc acquired through mapping task number to virtual PC
    int diskloc = taskmap[ta];
    int pos = loc;
    for(int i = diskloc; i<diskloc+(req_pages*PAGESIZE); i++){
        disk[i] = mem[pos];
        diskop[i] = opcodes[pos];
        pos++;
    }
    // space[loc] = req_pages;
    saveRegisters(ta, loc);
}

void swapin(int loc, int ta, int req_pages){
    task = ta;
    loadRegisters(task, loc);
    // tasktracker[loc] = task;
    int diskloc = taskmap[ta];
    printf("%s %d\n", "start swapping in loctation:", taskmap[task]);
    int pos = loc;
    printf("%s\n", "swapping in new pages");
    for(int i = diskloc; i<diskloc+(req_pages*PAGESIZE); i++){
        mem[pos] = disk[i];
        // printf("%d\n", disk[i]);
        // printf("%d\n", mem[pos]);
        opcodes[pos] = diskop[i];
        pos++;
    }
    printf("%s\n", "swapping finished");
    // space[loc] = 0;
    
}



