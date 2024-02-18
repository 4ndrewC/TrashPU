#include <stdio.h>
#include <stdlib.h>
#include "memory.c"
#include "mmu.c"

int burst;
byte vm1[65536];
byte vm2[65536];
byte op1[65536];
byte op2[65536];
byte vm3[65536];
byte op3[65536];



struct Node{
    int cur;
    struct Node* next;
};

struct Queue{
    struct Node* front;
    struct Node* back;
};

void startQueue(struct Queue *queue){
    // printf("starting\n");
    queue->front = NULL;
    // printf("front started\n");
    queue->back = NULL;
};


void push(struct Queue *queue, int cur){
    // printf("%d\n", cur->PID);
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->cur = cur;
    node->next = NULL;

    if(queue->front==NULL){
        queue->front = node;
        queue->back = node;
    }
    else{
        queue->back->next = node;
        queue->back = node;
    }
}

int pop(struct Queue *queue){
    if(queue->front==NULL){
        return -1;
    }

    int cur = queue->front->cur;
    struct Node* temp = queue->front;
    
    queue->front = queue->front->next;

    if(queue->front==NULL){
        queue->back = NULL;
    }

    free(temp);

    return cur;
}

void printQueue(struct Queue *queue){
    if(queue->front==NULL){
        printf("Queue is empty\n");
    }
    struct Node* node = queue->front;
    while(node!=NULL){
        printf("%d -> ", node->cur);
        node = node->next;
    }
    printf("NULL\n");
}

void test(){
    for(int i = 1; i<=3; i++){
        printf("%d", disk[0xC000*i]);
    }
}

void cpoint(){
    printf("%s", "Got here\n");
}

void cpointspec(char *str){
    printf("%s\n", str);
}

void showdisk(int location){
    printf("%s %d\n", "Virtual Mem:", disk[location]);
    printf("%s %d\n", "Virtual Mem Opcode:", diskop[location]);
}

void diskstatus(){
    for(int i = 0; i<10000000; i++){
        if(disk[i]!=0){
            printf("%d%s %d\n", i, ":", disk[i]);
        }
    }
}

void taskstatus(){
    for(int i = 0; i<10; i++){
        if(taskmap[i]!=0){
            printf("%s %d\n", "task:", taskmap[i]);
        }
    }
}

void memstatus(){
    for(int i = 0; i<67000; i++){
        if(mem[i]!=0){
            printf("%s %d%s %d\n", "Memory Location:", i, ":", mem[i]);
        }
    }
}

void showmem(int location){
    printf("%s %d\n", "Mem:", mem[location]);
    printf("%s %d\n", "Mem Opcode:", opcodes[location]);
}

void showtask(){
    printf("%s %d\n", "Current task:", task);
}

void split(){
    printf("%s\n", "--------------------------");
}

void fill(int t, byte *tempmem, byte *tempop){
    for(int k = 0; k<MEMSIZE; k++){
        // cpoint();
        disk[t*MEMSIZE+k] = tempmem[k];
        diskop[t*MEMSIZE+k] = tempop[k];
    }
}

void fillspace(){
    for(int i = 0; i<MEMSIZE; i++){
        space[i] = 2;
    }
}

void cycle(){

}

void schedulerRun(){
    
    struct Queue q;
    startQueue(&q);
    printf("%s", "Queue Initialized\n");
    int totaltasks = 3;
    //fill disk/virtual mem
    for(int t = 0; t<totaltasks; t++){
        byte tempmem[MEMSIZE];
        byte tempop[MEMSIZE];
        char *instr = "instr";
        char taskstr[8];
        char *filename = (char *)malloc(strlen(instr) + strlen(".in") + 1);;
        // cpoint();
        snprintf(taskstr, 8, "%d", t+1);

        // cpointspec(taskstr);

        strcpy(filename, instr);
        strcat(filename, taskstr);
        // cpoint();
        strcat(filename, ".in");
        // cpoint();
        memoryInit(filename, tempmem, tempop);
        // cpoint();
        fill(t, tempmem, tempop);
        // showdisk(0xC004);
        // printf("%d\n", diskop[0xC004]);

        taskmap[t+1] = 0xC000+(t*MEMSIZE);
    }
    printf("%s\n", "Virtual Memory Initialized");   
    fillspace();

    diskstatus();
    taskstatus();

    word scantest = scan(1); 
    printf("%d\n", scantest);

    swapin(scantest*8, 1, 1);
    memstatus();
    
    split();

    showtask();
    showdisk(PC);
    showmem(PC);
    fetch();

    scantest = scan(1); 
    swapout(scantest*8, 1);
    swapin(scantest*8, 2, 1);
    memstatus();

    split();

    showtask();
    showdisk(PC);
    showmem(PC);
    fetch();

    scantest = scan(1); 
    swapout(scantest*8, 1);
    swapin(scantest*8, 3, 1);

    split();

    showtask();
    showdisk(PC);
    showmem(PC);
    fetch();

    scantest = scan(1); 
    swapout(scantest*8, 1);
    swapin(scantest*8, 1, 1);

    split();

    showtask();
    showdisk(PC);
    showmem(PC);
    fetch();

    // scantest = scan(1); 
    // swapout(PC, 1);
    // swapin(scantest*8, 1, 1);

    // split();

    // showtask();
    // showdisk(0xC004);
    // showmem(PC);
    // fetch();
    // showdisk(PC);
    // showmem(PC);
    // fetch();
    // showdisk(PC);
    // showmem(PC);
    
    
    
}
