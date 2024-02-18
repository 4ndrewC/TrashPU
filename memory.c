#include <stdio.h>
#include <string.h>
#include "instructions.h"
#include <stdint.h>
#include <stdlib.h>

uint16_t pointer;
// uint8_t *mem;



const uint8_t getInstruct(const char* str) {
    if (strcmp(str, "LDA_I") == 0) return 0xA9;
    if (strcmp(str, "LDA_A") == 0) return 0xAD;
    if (strcmp(str, "LDA_AX") == 0) return 0xBD;
    if (strcmp(str, "LDA_AY") == 0) return 0xB9;

    if (strcmp(str, "LDX_I") == 0) return 0xA2;
    if (strcmp(str, "LDX_A") == 0) return 0xAE;
    if (strcmp(str, "LDX_AY") == 0) return 0xBE;

    if (strcmp(str, "LDY_I") == 0) return 0xA0;
    if (strcmp(str, "LDY_A") == 0) return 0xAC;
    if (strcmp(str, "LDY_AX") == 0) return 0xBC;

    if (strcmp(str, "STA_A") == 0) return 0x8D;
    if (strcmp(str, "STA_AX") == 0) return 0x9D;
    if (strcmp(str, "STA_AY") == 0) return 0x99;

    if (strcmp(str, "STX_A") == 0) return 0x8E;

    if (strcmp(str, "STY_A") == 0) return 0x8C;

    if (strcmp(str, "TAX_A") == 0) return 0xAA;
    if (strcmp(str, "TAY_A") == 0) return 0xA8;
    if (strcmp(str, "TXA_A") == 0) return 0x8A;
    if (strcmp(str, "TYA_A") == 0) return 0x98;

    if (strcmp(str, "AND_I") == 0) return 0x29;
    if (strcmp(str, "AND_A") == 0) return 0x2D;
    if (strcmp(str, "AND_AX") == 0) return 0x3D;
    if (strcmp(str, "AND_AY") == 0) return 0x39;

    if (strcmp(str, "EOR_I") == 0) return 0x49;
    if (strcmp(str, "EOR_A") == 0) return 0x4D;
    if (strcmp(str, "EOR_AX") == 0) return 0x5D;
    if (strcmp(str, "EOR_AY") == 0) return 0x59;

    if (strcmp(str, "ORA_I") == 0) return 0x09;
    if (strcmp(str, "ORA_A") == 0) return 0x0D;
    if (strcmp(str, "ORA_AX") == 0) return 0x1D;
    if (strcmp(str, "ORA_AY") == 0) return 0x19;

    if (strcmp(str, "JMP_A") == 0) return 0x4C;

    if (strcmp(str, "ADC_I") == 0) return 0x69;
    if (strcmp(str, "ADC_A") == 0) return 0x6D;
    if (strcmp(str, "ADC_AX") == 0) return 0x7D;
    if (strcmp(str, "ADC_AY") == 0) return 0x79;

    if (strcmp(str, "SBC_I") == 0) return 0xE9;
    if (strcmp(str, "SBC_A") == 0) return 0xED;
    if (strcmp(str, "SBC_AX") == 0) return 0xFD;
    if (strcmp(str, "SBC_AY") == 0) return 0xF9;

    if (strcmp(str, "CMP_I") == 0) return CMP_I;
    if (strcmp(str, "CMP_A") == 0) return CMP_A;
    if (strcmp(str, "CMP_AX") == 0) return CMP_AX;
    if (strcmp(str, "CMP_AY") == 0) return CMP_AY;

    if (strcmp(str, "BEQ_A") == 0) return BEQ;

    return 0;
}

struct instruct{
    char instruction[100];
    int opcode;
};

void parseLine(char *line, uint8_t *mem, uint8_t *opcodes) {
    
    char instruction[100];
    char *token = strtok(line, " "); // assuming space separates "text" and "$43043,x"
    char opcode[100];   
    if (token != NULL) {
        strcpy(instruction, token);

        token = strtok(NULL, " ");
        if (token != NULL) {
            int i = 0;
            while (token[i] != '\0' && token[i] != ',' && (token[i] < '0' || token[i] > '9')) {
                i++;
            }

            int j = 0;
            while (token[i] >= '0' && token[i] <= '9') {
                opcode[j++] = token[i++];
            }
            opcode[j] = '\0';
            if (strstr(token, "$") != NULL && strstr(token, ",x") != NULL) {
                strcat(instruction, "_AX");
            } else if (strstr(token, "$") != NULL && strstr(token, ",y") != NULL) {
                strcat(instruction, "_AY");
            } else if (token[0] == '$') {
                strcat(instruction, "_A");
            } else if (token[0]=='#') {
                strcat(instruction, "_I");
            }
            
            

            printf("Modified Instruction: %s\n", instruction);
            printf("Opcode: %s\n", opcode);
            // struct instruct current;
            // strcpy(current.instruction, instruction);
            // current.opcode = atoi(opcode);
            mem[pointer] = (uint8_t)getInstruct(instruction);
            opcodes[pointer] = atoi(opcode);
            pointer++;
        }
    }
}


int memoryInit(char *filename, uint8_t *vm, uint8_t *vmop) {
    uint8_t *mem = vm;
    uint8_t *opcodes = vmop;
    pointer = 0xC000;
    // mem = vm;
    FILE *file = fopen(filename, "r");
    // printf("Loading ");
    printf("\n%s %s %s\n\n", "Loading", (char *)filename, "into mem");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[256]; // Assuming a maximum line length of 255 characters
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline character from the end of the line
        size_t length = strlen(line);
        if (line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        parseLine(line, mem, opcodes);
        // printf("%d", mem[0xC008]);
    }

    fclose(file);
}
