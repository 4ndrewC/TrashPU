#include <stdio.h>
#include <stdlib.h>
#include "memory.c"
#include "cpu.c"

int burst;
byte vm1[65536];
byte vm2[65536];
byte op1[65536];
byte op2[65536];
byte vm3[65536];
byte op3[65536];

struct state{
    int PID;
    byte *vm;
    byte *opcodes;
    word PC;
    word A, SP, X, Y;
    byte C, Z, N, I, D, B, O;
};

void saveState(struct state *cur){
    cur -> vm = mem;
    cur -> opcodes = opcodes;
    cur -> PC = PC;
    cur -> A = A;
    cur -> X = X;
    cur -> Y = Y;
    cur -> SP = SP;

    //save flags
    cur -> C = C;
    cur -> Z = Z;
    cur -> N = N;
    cur -> I = I;
    cur -> D = D;
    cur -> B = B;
    cur -> O = O;
}

void loadState(struct state *next){
    mem = next->vm;
    opcodes = next->opcodes;
    PC = next->PC;
    A = next->A;
    X = next->X;
    Y = next->Y;
    SP = next->SP;

    //load flags
    C = next -> C;;
    Z = next -> Z;;
    N = next -> N;;
    I = next -> I;;
    D = next -> D;;
    B = next -> B;;
    O = next -> O;;
    
}

struct Node{
    struct state* cur;
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


void push(struct Queue *queue, struct state* cur){
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

struct state* pop(struct Queue *queue){
    if(queue->front==NULL){
        return NULL;
    }

    struct state* cur = queue->front->cur;
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
        printf("%d -> ", node->cur->PID);
        node = node->next;
    }
    printf("NULL\n");
}



void schedulerRun(){
    // printf("%s\n", "Loading instruction set 1");
    
    struct state p1;
    struct state p2;
    struct state p3;
    p2.PID = 2;
    p1.PID = 1;
    p3.PID = 3;
    memoryInit("instr1.in", vm1, op1);
    // printf("%s\n", "Loading instruction set 2");
    memoryInit("instr2.in", vm2, op2);
    memoryInit("instr3.in", vm3, op3);

    printf("Mem and opcodes initialized\n");

    mem = vm1;
    opcodes = op1;
    saveState(&p1);

    mem = vm2;
    opcodes = op2;
    saveState(&p2);

    mem = vm3;
    opcodes = op3;
    saveState(&p3);

    

    printf("States initialized\n");

    struct Queue q;
    startQueue(&q);
    push(&q, &p1);
    push(&q, &p2);
    push(&q, &p3);

    printQueue(&q);

    printf("Queue initialized\n");

    struct state test;

    // test = *pop(&q);
    // printQueue(&q);
    // printf("%d\n", test.PID);
    // printQueue(&q);
    // push(&q, &p1);
    // printQueue(&q);
    // test = *pop(&q);
    // printQueue(&q);
    // printf("%d\n", test.PID);
    // push(&q, &p2);
    // printQueue(&q);
    // test = *pop(&q);
    // printQueue(&q);
    // printf("%d\n", test.PID);
    // printf("%d\n", p1.vm[0xC003]);
    // printf("%d\n", p2.vm[0xC003]);
    // printf("%d\n", vm1[0xC000]);
    // printf("%d\n", op1[0xC000]);
    // printf("%d\n", op2[0xC000]);
    
    for(int i = 0; 1; i++){
        
        // printf("Before\n");
        // printQueue(&q);

        struct state *cur = pop(&q);
        
        // printf("%s %d\n", "Popped PID:", cur->PID);
        // printf("%s %d\n", "cur.A content", cur->A);
        // printQueue(&q);
        
        loadState(cur);
        fetch();
        
        saveState(cur);
        // printf("%s %d\n", "Popped PID:", cur->PID);
        // printf("%s %d\n", "cur.A content", cur->A);
        if(PC>=0xFFFE) {
            free(cur);
            if(q.front==NULL){
                break;
            }
            continue;
        }

        push(&q, cur);
        // printf("After\n");
        // printQueue(&q);
        
        free(cur);

    }
    
}

