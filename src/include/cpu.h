#pragma once
#ifndef __CPU_H__
#define __CPU_H__
#include "memory.h"
#include <stdint.h>

enum INSTUCTIONS
{
    BRK_IMP = 0x00,   //Instruction: Force Interrupt Implied
    ORA_IND_X = 0x01, //Instruction: Inclusive OR Indirect X
    ORA_ZP = 0x05,    //Instruction: Inclusive OR Zero Page
    ASL_ZP = 0x06,    //Instruction: Arithmetic Shift Left Zero Page
    PHP_IMP = 0x08,   //Instruction: Push Processor Status Implied
    ASL_ACC = 0x0A,   //Instruction: Arithmetic Shift Left Accumulator
    ORA_ABS = 0x0D,   //Instruction: Inclusive OR Absolute
    ASL_ABS = 0x0E,   //Instruction: Arithmetic Shift Left Absolute
    BPL_REL = 0x10,   //Instruction: Branch if Positive Relative
    ORA_IND_Y = 0x11, //Instruction: Inclusive OR Indirect X
    ORA_ZP_X = 0x15,  //Instruction: Inclusive OR Zero Page X
    ASL_ZP_X = 0x16,  //Instruction: Arithmetic Shift Left Zero Page X
    CLC_IMP = 0x18,   //Instruction: Clear Carry Flag Implied
    ORA_ABS_Y = 0x19, //Instruction: Inclusive OR Absolute Y
    ORA_ABS_X = 0x1D, //Instruction: Inclusive OR Absolute X
    ASL_ABS_X = 0x1E, //Instruction: Arithmetic Shift Left Absolute X
    JSR_ABS = 0x20,   //Instruction: Jump to Subroutine
    AND_IND_X = 0x21, //Instruction: Logical AND Indirect X
    BIT_ZP = 0x24,    //Instruction: Bit Test Zero Page
    AND_ZP = 0x25,    //Instruction: Logical AND Zero Page
    ROL_ZP = 0x26,    //Instruction: Rotate Left Zero Page
    PLP_IMP = 0x28,   //Instruction: Pull Processor Status Implied
    AND_IMM = 0x29,   //Instruction: Logical AND Immediate
    ROL_ACC = 0x2A,   //Instruction: Rotate Left Accumulator
    BIT_ABS = 0x2C,   //Instruction: Bit Test Absolute
    AND_ABS = 0x2D,   //Instruction: Logical AND Absolute
    ROL_ABS = 0x2E,   //Instruction: Rotate Left Absolute
    BMI_REL = 0x30,   //Instruction: Branch if Minus Relative
    AND_IND_Y = 0x31, //Instruction: Logical AND Indirect Y
    AND_ZP_X = 0x35,  //Instruction: Logical AND Zero Page X
    ROL_ZP_X = 0x36,  //Instruction: Rotate Left Zero Page X
    SEC_IMP = 0x38,   //Instruction: Set Carry Flag Implied
    AND_ABS_Y = 0x39, //Instruction: Logical AND Absolute Y
    AND_ABS_X = 0x3D, //Instruction: Logical AND Absolute X
    ROL_ABS_X = 0x3E, //Instruction: Rotate Left Accumulator
    RTI_IMP = 0x40,   //Instruction: Return from Interrupt Implied
    EOR_IND_X = 0x41, //Instruction: Exclusive OR Indirect X
    EOR_ZP = 0x42,    //Instruction: Exclusive OR Zero Page
    LSR_ZP = 0x46,    //Instruction: Logical Shift Right
    PHA_IMP = 0x48,   //Instruction: Push Accumulator Implied
    EOR_IMM = 0x49,   //Instruction: Exclusive OR Immediate
    LSR_ACC = 0x4A,   //Instruction: Logical Shift Right Accumulator
    JMP_ABS = 0x4C,   //Instruction: Jump Absolute
    EOR_ABS = 0x4D,   //Instruction: Exclusive OR Absolute
    LSR_ABS = 0x4E,   //Instruction: Logical Shift Right Absolute
    BVC_REL = 0x50,   //Instruction: Branch if Overflow Clear
    EOR_IND_Y = 0x51, //Instruction: Exclusive OR Indirect Y
    EOR_ZP_X = 0x55,  //Instruction: Exclusive OR Zero Page X
    LSR_ZP_X = 0x56,  //Instruction: Logical Shift Right Zero Page X
    CLI_IMP = 0x58,   //Instruction: Clear Interrupt Disable Implied
    EOR_ABS_Y = 0x59, //Instruction: Exclusive OR Absolute Y
    EOR_ABS_X = 0x5D, //Instruction: Exclusive OR Absolute X
    LSR_ABS_X = 0x5E, //Instruction: Logical Shift Right Absolute X
    RTS_IMP = 0x60,   //Instruction: Return from Subroutine Implied
    ADC_IND_X = 0x61, //Instruction: Add with Carry Indirect X
    ADC_ZP = 0x65,    //Instruction: Add with Carry Zero Page
    ROR_ZP = 0x66,    //Instruction: Rotate Right Zero Page
    PLA_IMP = 0x68,   //Instruction: Pull Accumulator Implied
    ADC_IMM = 0x69,   //Instruction: Add with Carry Immediate
    ROR_ACC = 0x6A,   //Instruction: Rotate Right Accumulator
    JMP_IND = 0x6C,   //Instruction: Jump Indirect
    ADC_ABS = 0x6D,   //Instruction: Add with Carry Absolute
    ROR_ABS = 0x6E,   //Instruction: Rotate Right Absolute
    BVS_REL = 0x70,   //Instruction: Branch if Overflow Set Relative
    ADC_IND_Y = 0x71, //Instruction: Add with Carry Indirect Y
    ADC_ZP_X = 0x75,  //Instruction: Add with Carry Zero Page X
    ROR_ZP_X = 0x76,  //Instruction: Rotate Right Zero Page X
    SEI_IMP = 0x78,   //Instruction: Set Interrupt Disable Implied
    ADC_ABS_Y = 0x79, //Instruction: Add with Carry Absolute Y
    ADC_ABS_X = 0x7D, //Instruction: Add with Carry Absolute X
    ROR_ABS_X = 0x7E, //Instruction: Rotate Right Absolute X
    STA_IND_X = 0x81, //Instruction: Store Accumulator Indirect X
    STY_ZP = 0x84,    //Instruction: Store Y Register Zero Page
    STA_ZP = 0x85,    //Instruction: Store Accumulator Zero Page
    STX_ZP = 0x86,    //Instruction: Store Y Register Zero Page
    DEY_IMP = 0x88,   //Instruction: Decrement Y Register Implied
    TXA_IMP = 0x8A,   //Instruction: Transfer X to Accumulator Implied
    STY_ABS = 0x8C,   //Instruction: Store Y Register Absolute
    STA_ABS = 0x8D,   //Instruction: Store Accumulator Absolute
    STX_ABS = 0x8E,   //Instruction: Store X Register Absolute
    BCC_REL = 0x90,   //Instruction: Branch if Carry Clear Relative
    STA_IND_Y = 0x91, //Instruction: Store Accumulator Indirect Y
    STY_ZP_X = 0x94,  //Instruction: Store Y Register Zero Page X
    STA_ZP_X = 0x95,  //Instruction: Store Accumulator Zero Page X
    STX_ZP_Y = 0x96,  //Instruction: Store X Register Zero Page Y
    TYA_IMP = 0x98,   //Instruction: Transfer Y to Accumulator Implied
    STA_ABS_Y = 0x99, //Instruction: Store Accumulator Absolute X
    TXS_IMP = 0x9A,   //Instruction: Transfer X to Stack Pointer Implied
    STA_ABS_X = 0x9D, //Instruction: Store Accumulator Absolute X
    LDY_IMM = 0xA0,   //Instruction: Load Y Register Immediate
    LDA_IND_X = 0xA1, //Instruction: Load Accumulator Indirect X
    LDX_IMM = 0xA2,   //Instruction: Load X Register Immediate
    LDY_ZP = 0xA4,    //Instruction: Load Y Register Zero Page
    LDA_ZP = 0xA5,    //Instruction: Load Accumulator Zero Page
    LDX_ZP = 0xA6,    //Instruction: Load X Register Zero Page
    TAY_IMP = 0xA8,   //Instruction: Transfer Accumulator to Y Implied
    LDA_IMM = 0xA9,   //Instruction: Load Accumulator Immediate
    TAX_IMP = 0xAA,   //Instruction: Transfer Accumulator to X Implied
    LDY_ABS = 0xAC,   //Instruction: Load Y Register Absolute
    LDA_ABS = 0xAD,   //Instruction: Load Accumulator Absolute
    LDX_ABS = 0xAE,   //Instruction: Load X Register Absolute
    BCS_REL = 0xB0,   //Instruction: Branch if Carry Set Relative
    LDA_IND_Y = 0xB1, //Instruction: Load Accumulator Indirect Y
    LDY_ZP_X = 0xB4,  //Instruction: Load Y Register Zero Page X
    LDA_ZP_X = 0xB5,  //Instruction: Load Accumulator Zero Page X
    LDX_ZP_Y = 0xB6,  //Instruction: Load X Register Zero Page Y
    CLV_IMP = 0xB8,   //Instruction: Clear Overflow Flag Implied
    LDA_ABS_Y = 0xB9, //Instruction: Load Accumulator Absolute Y
    TSX_IMP = 0xBA,   //Instruction: Transfer Stack Pointer to X Implied
    LDY_ABS_X = 0xBC, //Instruction: Load Y Register Absolute X
    LDA_ABS_X = 0xBD, //Instruction: Load Accumulator Absolute X
    LDX_ABS_Y = 0xBE, //Instruction: Load X Register Absolute Y
    CPY_IMM = 0xC0,   //Instruction: Compare Y Register Immediate
    CMP_IND_X = 0xC1, //Instruction: Compare Indirect X
    CPY_ZP = 0xC4,    //Instruction: Compare Y Register Zero Page
    CMP_ZP = 0xC5,    //Instruction: Compare Zero Page
    DEC_ZP = 0xC6,    //Instruction: Decrement Memory Zero Page
    INY_IMP = 0xC8,   //Instruction: Increment Y Register Implied
    CMP_IMM = 0xC9,   //Instruction: Compare Immediate
    DEX_IMP = 0xCA,   //Instruction: Decrement X Register Implied
    CPY_ABS = 0xCC,   //Instruction: Compare Y Register Absolute
    CMP_ABS = 0xCD,   //Instruction: Compare Absolute
    DEC_ABS = 0xCE,   //Instruction: Decrement Memory Absolute
    BNE_REL = 0xD0,   //Instruction: Branch if Not Equal Relative
    CMP_IND_Y = 0xD1, //Instruction: Compare Indirect Y
    CMP_ZP_X = 0xD5,  //Instruction: Compare Zero Page X
    DEC_ZP_X = 0xD6,  //Instruction: Decrement Memory Zero Page X
    CLD_IMP = 0xD8,   //Instruction: Clear Decimal Mode Implied
    CMP_ABS_Y = 0xD9, //Instruction: Compare Absolute Y
    CMP_ABS_X = 0xDD, //Instruction: Compare Absolute X
    DEC_ABS_X = 0xDE, //Instruction: Decrement Memory Absolute X
    CPX_IMM = 0xE0,   //Instruction: Compare X Register Immediate
    SBC_IND_X = 0xE1, //Instruction: Subtract with Carry Indirect X
    CPX_ZP = 0xE4,    //Instruction: Compare X Register Zero Page
    SBC_ZP = 0xE5,    //Instruction: Subtract with Carry Zero Page
    INC_ZP = 0xE6,    //Instruction: Increment Memory Zero Page
    INX_IMP = 0xE8,   //Instruction: Increment X Register Implied
    SBC_IMM = 0xE9,   //Instruction: Subtract with Carry Immediate
    NOP_IMP = 0xEA,   //Instruction: No Operation Implied
    CPX_ABS = 0xEC,   //Instruction: Compare X Register Absolute
    SBC_ABS = 0xED,   //Instruction: Subtract with Carry Absolute
    INC_ABS = 0xEE,   //Instruction: Increment Memory Absolute
    BEQ_REL = 0xF0,   //Instruction: Branch if Equal Relative
    SBC_IND_Y = 0xF1, //Instruction: Subtract with Carry Indirect Y
    SBC_ZP_X = 0xF5,  //Instruction: Subtract with Carry Zero Page X
    INC_ZP_X = 0xF6,  //Instruction: Increment Memory Zero Page X
    SED_IMP = 0xF8,   //Instruction: Set Decimal Flag Implied
    SBC_ABS_Y = 0xF9, //Instruction: Subtract with Carry Absolute Y
    SBC_ABS_X = 0xFD, //Instruction: Subtract with Carry Absolute X
    INC_ABS_X = 0xFE, //Instruction: Increment Memory Absolute X
};


struct CPU
{
    uint32_t cycles;//CPU Cycles
    uint16_t PC;    //Program Counter
    uint16_t ABS;   //Absolute Address
    uint16_t REL;   //Relative Address
    uint8_t INS;    //Current Instruction
    uint8_t SP;     //Stack Pointer
    uint8_t A;      //Accumulator
    uint8_t X;      //Index Register X
    uint8_t Y;      //Index Register Y
    uint8_t PS;     //Processor Status
};

enum FLAGS
{
    C = (1 << 0),  //Processor Status Carry Flag
    Z = (1 << 1),  //Processor Status Zero Flag
    I = (1 << 2),  //Processor Status Interrupt Disable
    D = (1 << 3),  //Processor Status Decimal Mode Flag
    B = (1 << 4),  //Processor Status Break Command
    U = (1 << 5),  //Processor Status Unused
    V = (1 << 6),  //Processor Status Overflow Flag
    N = (1 << 7),  //Processor Status Negative Flag
};

struct MEMORY;

/* RESETS CPU to startup state */
void ResetCpu(struct CPU *cpu, struct MEMORY *memory);

/* Executes the next instruction in the cycle */
void Clock(struct CPU *cpu, struct MEMORY *memory);

void IRQ(struct CPU *cpu, struct MEMORY *memory);

void NMI(struct CPU *cpu, struct MEMORY *memory);

uint8_t GetFlag(struct CPU *cpu, enum FLAGS f);

void SetFlag(struct CPU *cpu, enum FLAGS f, int i);



uint8_t IMP(struct CPU *cpu);

uint8_t IMM(struct CPU *cpu);

uint8_t ZP(struct CPU *cpu, struct MEMORY *memory);

uint8_t ZPX(struct CPU *cpu, struct MEMORY *memory);

uint8_t ZPY(struct CPU *cpu, struct MEMORY *memory);

uint8_t ABS(struct CPU *cpu, struct MEMORY *memory);

uint8_t REL(struct CPU *cpu, struct MEMORY *memory);

uint8_t ABSX(struct CPU *cpu, struct MEMORY *memory);

uint8_t ABSY(struct CPU *cpu, struct MEMORY *memory);

uint8_t IND(struct CPU *cpu, struct MEMORY *memory);

uint8_t INDX(struct CPU *cpu, struct MEMORY *memory);

uint8_t INDY(struct CPU *cpu, struct MEMORY *memory);



uint8_t AND(struct CPU *cpu, struct MEMORY *memory);

uint8_t BCS(struct CPU *cpu);

uint8_t BCC(struct CPU *cpu);

uint8_t BEQ(struct CPU *cpu);

uint8_t BMI(struct CPU *cpu);

uint8_t BNE(struct CPU *cpu);

uint8_t BPL(struct CPU *cpu);

uint8_t BVC(struct CPU *cpu);

uint8_t BVS(struct CPU *cpu);

uint8_t BIT(struct CPU *cpu, struct MEMORY *memory);

void Branch(struct CPU *cpu);

uint8_t CLC(struct CPU *cpu);

uint8_t CLD(struct CPU *cpu);

uint8_t CLI(struct CPU *cpu);

uint8_t CLV(struct CPU *cpu);

uint8_t ADC(struct CPU *cpu, struct MEMORY *memory);

uint8_t SBC(struct CPU *cpu, struct MEMORY *memory);

uint8_t PHA(struct CPU *cpu, struct MEMORY *memory);

uint8_t PHP(struct CPU *cpu, struct MEMORY *memory);

uint8_t PLA(struct CPU *cpu, struct MEMORY *memory);

uint8_t PLP(struct CPU *cpu, struct MEMORY *memory);

uint8_t ASL(struct CPU *cpu, struct MEMORY *memory, uint8_t IMP);

uint8_t BRK(struct CPU *cpu, struct MEMORY *memory);

uint8_t CMP(struct CPU *cpu, struct MEMORY *memory);

uint8_t CPX(struct CPU *cpu, struct MEMORY *memory);

uint8_t CPY(struct CPU *cpu, struct MEMORY *memory);

uint8_t DEC(struct CPU *cpu, struct MEMORY *memory);

uint8_t DEX(struct CPU *cpu);

uint8_t DEY(struct CPU *cpu);

uint8_t INC(struct CPU *cpu, struct MEMORY *memory);

uint8_t INX(struct CPU *cpu);

uint8_t INY(struct CPU *cpu);

uint8_t JMP(struct CPU *cpu);

uint8_t JSR(struct CPU *cpu, struct MEMORY *memory);

uint8_t LDA(struct CPU *cpu, struct MEMORY *memory);

uint8_t LDX(struct CPU *cpu, struct MEMORY *memory);

uint8_t LDY(struct CPU *cpu, struct MEMORY *memory);

uint8_t LSR(struct CPU *cpu, struct MEMORY *memory, uint8_t imp);

uint8_t EOR(struct CPU *cpu, struct MEMORY *memory);

uint8_t ORA(struct CPU *cpu, struct MEMORY *memory);

uint8_t ROL(struct CPU *cpu, struct MEMORY *memory, uint8_t imp);

uint8_t ROR(struct CPU *cpu, struct MEMORY *memory, uint8_t imp);

uint8_t RTI(struct CPU *cpu, struct MEMORY *memory);

uint8_t RTS(struct CPU *cpu, struct MEMORY *memory);

uint8_t SEC(struct CPU *cpu);

uint8_t SED(struct CPU *cpu);

uint8_t SEI(struct CPU *cpu);

uint8_t STA(struct CPU *cpu, struct MEMORY *memory);

uint8_t STX(struct CPU *cpu, struct MEMORY *memory);

uint8_t STY(struct CPU *cpu, struct MEMORY *memory);

uint8_t TAX(struct CPU *cpu);

uint8_t TAY(struct CPU *cpu);

uint8_t TSX(struct CPU *cpu);

uint8_t TXA(struct CPU *cpu);

uint8_t TXS(struct CPU *cpu);

uint8_t TYA(struct CPU *cpu);

uint8_t NOP();



/* Fetches byte that is in the memory at where program counter is pointing to */
uint8_t FetchByte(struct CPU *cpu, struct MEMORY *memory);

#endif
