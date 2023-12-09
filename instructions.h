#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// define instruction
#define LDA_I 0xA9
#define LDA_A 0xAD
#define LDA_AX 0xBD
#define LDA_AY 0xB9

#define LDX_I 0xA2
#define LDX_A 0xAE
#define LDX_AY 0xBE

#define LDY_I 0xA0
#define LDY_A 0xAC
#define LDY_AX 0xBC

#define STA_A 0x8D
#define STA_AX 0x9D
#define STA_AY 0x99

#define STX_A 0x8E

#define STY_A 0x8C

#define TAX 0xAA
#define TAY 0xA8
#define TXA 0x8A
#define TYA 0x98

//logicals: purpose is to set flags, no results are kept
#define AND_I 0x29
#define AND_A 0x2D
#define AND_AX 0x3D
#define AND_AY 0x39

#define EOR_I 0x49
#define EOR_A 0x4D
#define EOR_AX 0x5D
#define EOR_AY 0x59

#define ORA_I 0x09
#define ORA_A 0x0D
#define ORA_AX 0x1D
#define ORA_AY 0x19

//jump
#define JMP 0x4C

//arithmetic
#define ADC_I 0x69
#define ADC_A 0x6D
#define ADC_AX 0x7D
#define ADC_AY 0x79

#define SBC_I 0xE9
#define SBC_A 0xED
#define SBC_AX 0xFD
#define SBC_AY 0xF9

//compare
#define CMP_I 0xC9
#define CMP_A 0xD5
#define CMP_AX 0xDD
#define CMP_AY 0xD9


//branch if flags
#define BEQ 0xF0

#endif

