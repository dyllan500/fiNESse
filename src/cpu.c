#include "include/cpu.h"
#include "include/memory.h"
#include <bits/types.h>
#include <stdio.h>

/* RESETS CPU to startup state */
void ResetCpu(struct CPU *cpu, struct MEMORY *memory)
{
    //SET Program Counter
	cpu->ABS = 0xFFFC;
	uint16_t lo = memory->DATA[cpu->ABS];
	uint16_t hi = memory->DATA[cpu->ABS+1];
	cpu->PC = (hi << 8) | lo;

	// Reset internal registers
	cpu->A = 0;
	cpu->X = 0;
	cpu->Y = 0;
	cpu->SP = 0xFD;
	cpu->PS = 0x00 | U;

	// Clear internal helper variables
	cpu->REL = 0x0000;
	cpu->ABS = 0x0000;

	// Reset takes time
	cpu->cycles = 8;
}

/* Executes the next instruction in the cycle */
void Clock(struct CPU *cpu, struct MEMORY *memory)
{
    while(cpu->cycles > 0)
    {
        printf("Cycles: %d\n", cpu->cycles);
        cpu->INS = FetchByte(cpu, memory);
        switch(cpu->INS)
        {
            case BRK_IMP:
                cpu->cycles = 7;
                cpu->cycles += IMP(cpu);
                cpu->cycles += BRK(cpu, memory);
                break;
            case ORA_IND_X:
                cpu->cycles = 6;
                cpu->cycles += INDX(cpu, memory);
                cpu->cycles += ORA(cpu, memory);
                break;
            case ORA_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += ORA(cpu, memory);
                break;
            case ASL_ZP:
                cpu->cycles = 5;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += ASL(cpu, memory, 0);
                break;
            case PHP_IMP:
                cpu->cycles = 3;
                cpu->cycles += IMP(cpu);
                cpu->cycles += PHP(cpu, memory);
                break;
            case ASL_ACC:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += ASL(cpu, memory, 1);
                break;
            case ORA_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += ORA(cpu, memory);
                break;
            case ASL_ABS:
                cpu->cycles = 6;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += ASL(cpu, memory, 0);
                break;
            case BPL_REL:
                cpu->cycles = 2;
                cpu->cycles += REL(cpu, memory);
                cpu->cycles += BPL(cpu);
                break;
            case ORA_IND_Y:
                cpu->cycles = 5;
                cpu->cycles += INDY(cpu, memory);
                cpu->cycles += ORA(cpu, memory);
                break;
            case ORA_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += ORA(cpu, memory);
                break;
            case ASL_ZP_X:
                cpu->cycles = 6;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += ASL(cpu, memory, 0);
                break;
            case CLC_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += CLC(cpu);
                break;
            case ORA_ABS_Y:
                cpu->cycles = 4;
                cpu->cycles += ABSY(cpu, memory);
                cpu->cycles += ORA(cpu, memory);
                break;
            case ORA_ABS_X:
                cpu->cycles = 4;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += ORA(cpu, memory);
                break;
            case ASL_ABS_X:
                cpu->cycles = 7;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += ASL(cpu, memory, 0);
                break;
            case JSR_ABS:
                cpu->cycles = 6;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += JSR(cpu, memory);
                break;
            case AND_IND_X:
                cpu->cycles = 6;
                cpu->cycles += INDX(cpu, memory);
                cpu->cycles += AND(cpu, memory);
                break;
            case BIT_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += BIT(cpu, memory);
                break;
            case AND_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += AND(cpu, memory);
                break;
            case ROL_ZP:
                cpu->cycles = 5;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += ROL(cpu, memory, 0);
                break;
            case PLP_IMP:
                cpu->cycles = 4;
                cpu->cycles += IMP(cpu);
                cpu->cycles += PLP(cpu, memory);
                break;
            case AND_IMM:
                cpu->cycles = 2;
                cpu->cycles += IMM(cpu);
                cpu->cycles += AND(cpu, memory);
                break;
            case ROL_ACC:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += ROL(cpu, memory, 1);
                break;
            case BIT_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += BIT(cpu, memory);
                break;
            case AND_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += AND(cpu, memory);
                break;
            case ROL_ABS:
                cpu->cycles = 6;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += ROL(cpu, memory, 0);
                break;
            case BMI_REL:
                cpu->cycles = 2;
                cpu->cycles += REL(cpu, memory);
                cpu->cycles += BMI(cpu);
                break;
            case AND_IND_Y:
                cpu->cycles = 5;
                cpu->cycles += INDY(cpu, memory);
                cpu->cycles += AND(cpu, memory);
                break;
            case AND_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += AND(cpu, memory);
                break;
            case ROL_ZP_X:
                cpu->cycles = 6;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += ROL(cpu, memory, 0);
                break;
            case SEC_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += SEC(cpu);
                break;
            case AND_ABS_Y:
                cpu->cycles = 4;
                cpu->cycles += ABSY(cpu, memory);
                cpu->cycles += AND(cpu, memory);
                break;
            case AND_ABS_X:
                cpu->cycles = 4;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += AND(cpu, memory);
                break;
            case ROL_ABS_X:
                cpu->cycles = 7;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += ROL(cpu, memory, 0);
                break;
            case RTI_IMP:
                cpu->cycles = 6;
                cpu->cycles += IMP(cpu);
                cpu->cycles += RTI(cpu, memory);
                break;
            case EOR_IND_X:
                cpu->cycles = 6;
                cpu->cycles += INDX(cpu, memory);
                cpu->cycles += EOR(cpu, memory);
                break;
            case EOR_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += EOR(cpu, memory);
                break;
            case LSR_ZP:
                cpu->cycles = 5;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += LSR(cpu, memory, 0);
                break;
            case PHA_IMP:
                cpu->cycles = 3;
                cpu->cycles += IMP(cpu);
                cpu->cycles += PHA(cpu, memory);
                break;
            case EOR_IMM:
                cpu->cycles = 2;
                cpu->cycles += IMM(cpu);
                cpu->cycles += EOR(cpu, memory);
                break;
            case LSR_ACC:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += LSR(cpu, memory, 1);
                break;
            case JMP_ABS:
                cpu->cycles = 3;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += JMP(cpu);
                break;
            case EOR_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += EOR(cpu, memory);
                break;
            case LSR_ABS:
                cpu->cycles = 6;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += LSR(cpu, memory, 0);
                break;
            case BVC_REL:
                cpu->cycles = 2;
                cpu->cycles += REL(cpu, memory);
                cpu->cycles += BVC(cpu);
                break;
            case EOR_IND_Y:
                cpu->cycles = 5;
                cpu->cycles += INDY(cpu, memory);
                cpu->cycles += EOR(cpu, memory);
                break;
            case EOR_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += EOR(cpu, memory);
                break;
            case LSR_ZP_X:
                cpu->cycles = 6;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += LSR(cpu, memory, 0);
                break;
            case CLI_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += CLI(cpu);
                break;
            case EOR_ABS_Y:
                cpu->cycles = 4;
                cpu->cycles += ABSY(cpu, memory);
                cpu->cycles += EOR(cpu, memory);
                break;
            case EOR_ABS_X:
                cpu->cycles = 4;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += EOR(cpu, memory);
                break;
            case LSR_ABS_X:
                cpu->cycles = 7;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += LSR(cpu, memory, 0);
                break;
            case RTS_IMP:
                cpu->cycles = 6;
                cpu->cycles += IMP(cpu);
                cpu->cycles += RTS(cpu, memory);
                break;
            case ADC_IND_X:
                cpu->cycles = 6;
                cpu->cycles += INDX(cpu, memory);
                cpu->cycles += ADC(cpu, memory);
                break;
            case ADC_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += ADC(cpu, memory);
                break;
            case ROR_ZP:
                cpu->cycles = 5;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += ROR(cpu, memory, 0);
                break;
            case PLA_IMP:
                cpu->cycles = 4;
                cpu->cycles += IMP(cpu);
                cpu->cycles += PLA(cpu, memory);
                break;
            case ADC_IMM:
                cpu->cycles = 2;
                cpu->cycles += IMM(cpu);
                cpu->cycles += ADC(cpu, memory);
                break;
            case ROR_ACC:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += ROR(cpu, memory, 1);
                break;
            case JMP_IND:
                cpu->cycles = 5;
                cpu->cycles += IND(cpu, memory);
                cpu->cycles += JMP(cpu);
                break;
            case ADC_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += ADC(cpu, memory);
                break;
            case ROR_ABS:
                cpu->cycles = 6;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += ROR(cpu, memory, 0);
                break;
            case BVS_REL:
                cpu->cycles = 2;
                cpu->cycles += REL(cpu, memory);
                cpu->cycles += BVS(cpu);
                break;
            case ADC_IND_Y:
                cpu->cycles = 5;
                cpu->cycles += INDY(cpu, memory);
                cpu->cycles += ADC(cpu, memory);
                break;
            case ADC_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += ADC(cpu, memory);
                break;
            case ROR_ZP_X:
                cpu->cycles = 6;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += ROR(cpu, memory, 0);
                break;
            case SEI_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += SEI(cpu);
                break;
            case ADC_ABS_Y:
                cpu->cycles = 4;
                cpu->cycles += ABSY(cpu, memory);
                cpu->cycles += ADC(cpu, memory);
                break;
            case ADC_ABS_X:
                cpu->cycles = 4;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += ADC(cpu, memory);
                break;
            case ROR_ABS_X:
                cpu->cycles = 7;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += ROR(cpu, memory, 0);
                break;
            case STA_IND_X:
                cpu->cycles = 6;
                cpu->cycles += INDX(cpu, memory);
                cpu->cycles += STA(cpu, memory);
                break;
            case STY_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += STY(cpu, memory);
                break;
            case STA_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += STA(cpu, memory);
                break;
            case STX_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += STX(cpu, memory);
                break;
            case DEY_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += DEY(cpu);
                break;
            case TXA_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += TXA(cpu);
                break;
            case STY_ABS:
                cpu->cycles = 3;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += STY(cpu, memory);
                break;
            case STA_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += STA(cpu, memory);
                break;
            case STX_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += STX(cpu, memory);
                break;
            case BCC_REL:
                cpu->cycles = 2;
                cpu->cycles += REL(cpu, memory);
                cpu->cycles += BCC(cpu);
                break;
            case STA_IND_Y:
                cpu->cycles = 6;
                cpu->cycles += INDY(cpu, memory);
                cpu->cycles += STA(cpu, memory);
                break;
            case STY_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += STY(cpu, memory);
                break;
            case STA_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += STA(cpu, memory);
                break;
            case STX_ZP_Y:
                cpu->cycles = 4;
                cpu->cycles += ZPY(cpu, memory);
                cpu->cycles += STX(cpu, memory);
                break;
            case TYA_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += TYA(cpu);
                break;
            case STA_ABS_Y:
                cpu->cycles = 5;
                cpu->cycles += ABSY(cpu, memory);
                cpu->cycles += STA(cpu, memory);
                break;
            case TXS_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += TXS(cpu);
                break;
            case STA_ABS_X:
                cpu->cycles = 5;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += STA(cpu, memory);
                break;
            case LDY_IMM:
                cpu->cycles = 2;
                cpu->cycles += IMM(cpu);
                cpu->cycles += LDY(cpu, memory);
                break;
            case LDA_IND_X:
                cpu->cycles = 6;
                cpu->cycles += INDX(cpu, memory);
                cpu->cycles += LDA(cpu, memory);
                break;
            case LDX_IMM:
                cpu->cycles = 2;
                cpu->cycles += IMM(cpu);
                cpu->cycles += LDX(cpu, memory);
                break;
            case LDY_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += LDY(cpu, memory);
                break;
            case LDA_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += LDA(cpu, memory);
                break;
            case LDX_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += LDX(cpu, memory);
                break;
            case TAY_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += TAY(cpu);
                break;
            case LDA_IMM:
                cpu->cycles = 2;
                cpu->cycles += IMM(cpu);
                cpu->cycles += LDA(cpu, memory);
                break;
            case TAX_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += TAX(cpu);
                break;
            case LDY_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += LDY(cpu, memory);
                break;
            case LDA_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += LDA(cpu, memory);
                break;
            case LDX_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += LDX(cpu, memory);
                break;
            case BCS_REL:
                cpu->cycles = 2;
                cpu->cycles += REL(cpu, memory);
                cpu->cycles += BCS(cpu);
                break;
            case LDA_IND_Y:
                cpu->cycles = 5;
                cpu->cycles += INDY(cpu, memory);
                cpu->cycles += LDA(cpu, memory);
                break;
            case LDY_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += LDY(cpu, memory);
                break;
            case LDA_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += LDA(cpu, memory);
                break;
            case LDX_ZP_Y:
                cpu->cycles = 4;
                cpu->cycles += ZPY(cpu, memory);
                cpu->cycles += LDX(cpu, memory);
                break;
            case CLV_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += CLV(cpu);
                break;
            case LDA_ABS_Y:
                cpu->cycles = 4;
                cpu->cycles += ABSY(cpu, memory);
                cpu->cycles += LDA(cpu, memory);
                break;
            case TSX_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += TSX(cpu);
                break;
            case LDY_ABS_X:
                cpu->cycles = 4;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += LDY(cpu, memory);
                break;
            case LDA_ABS_X:
                cpu->cycles = 4;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += LDA(cpu, memory);
                break;
            case LDX_ABS_Y:
                cpu->cycles = 4;
                cpu->cycles += ABSY(cpu, memory);
                cpu->cycles += LDX(cpu, memory);
                break;
            case CPY_IMM:
                cpu->cycles = 2;
                cpu->cycles += IMM(cpu);
                cpu->cycles += CPY(cpu, memory);
                break;
            case CMP_IND_X:
                cpu->cycles = 6;
                cpu->cycles += INDX(cpu, memory);
                cpu->cycles += CMP(cpu, memory);
                break;
            case CPY_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += CPY(cpu, memory);
                break;
            case CMP_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += CMP(cpu, memory);
                break;
            case DEC_ZP:
                cpu->cycles = 5;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += DEC(cpu, memory);
                break;
            case INY_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += INY(cpu);
                break;
            case CMP_IMM:
                cpu->cycles = 2;
                cpu->cycles += IMM(cpu);
                cpu->cycles += CMP(cpu, memory);
                break;
            case DEX_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += DEX(cpu);
                break;
            case CPY_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += CPY(cpu, memory);
                break;
            case CMP_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += CMP(cpu, memory);
                break;
            case DEC_ABS:
                cpu->cycles = 6;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += DEC(cpu, memory);
                break;
            case BNE_REL:
                cpu->cycles = 2;
                cpu->cycles += REL(cpu, memory);
                cpu->cycles += BNE(cpu);
                break;
            case CMP_IND_Y:
                cpu->cycles = 5;
                cpu->cycles += INDY(cpu, memory);
                cpu->cycles += CMP(cpu, memory);
                break;
            case CMP_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += CMP(cpu, memory);
                break;
            case DEC_ZP_X:
                cpu->cycles = 6;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += DEC(cpu, memory);
                break;
            case CLD_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += CLD(cpu);
                break;
            case CMP_ABS_Y:
                cpu->cycles = 4;
                cpu->cycles += ABSY(cpu, memory);
                cpu->cycles += CMP(cpu, memory);
                break;
            case CMP_ABS_X:
                cpu->cycles = 4;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += CMP(cpu, memory);
                break;
            case DEC_ABS_X:
                cpu->cycles = 7;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += DEC(cpu, memory);
                break;
            case CPX_IMM:
                cpu->cycles = 3;
                cpu->cycles += IMM(cpu);
                cpu->cycles += CPX(cpu, memory);
                break;
            case SBC_IND_X:
                cpu->cycles = 6;
                cpu->cycles += INDX(cpu, memory);
                cpu->cycles += SBC(cpu, memory);
                break;
            case CPX_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += CPX(cpu, memory);
                break;
            case SBC_ZP:
                cpu->cycles = 3;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += SBC(cpu, memory);
                break;
            case INC_ZP:
                cpu->cycles = 5;
                cpu->cycles += ZP(cpu, memory);
                cpu->cycles += INC(cpu, memory);
                break;
            case INX_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += INX(cpu);
                break;
            case SBC_IMM:
                cpu->cycles = 2;
                cpu->cycles += IMM(cpu);
                cpu->cycles += SBC(cpu, memory);
                break;
            case NOP_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += NOP();
                break;
            case CPX_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += CPX(cpu, memory);
                break;
            case SBC_ABS:
                cpu->cycles = 4;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += SBC(cpu, memory);
                break;
            case INC_ABS:
                cpu->cycles = 6;
                cpu->cycles += ABS(cpu, memory);
                cpu->cycles += INC(cpu, memory);
                break;
            case BEQ_REL:
                cpu->cycles = 2;
                cpu->cycles += REL(cpu, memory);
                cpu->cycles += BEQ(cpu);
                break;
            case SBC_IND_Y:
                cpu->cycles = 5;
                cpu->cycles += INDY(cpu, memory);
                cpu->cycles += SBC(cpu, memory);
                break;
            case SBC_ZP_X:
                cpu->cycles = 4;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += SBC(cpu, memory);
                break;
            case INC_ZP_X:
                cpu->cycles = 6;
                cpu->cycles += ZPX(cpu, memory);
                cpu->cycles += INC(cpu, memory);
                break;
            case SED_IMP:
                cpu->cycles = 2;
                cpu->cycles += IMP(cpu);
                cpu->cycles += SED(cpu);
                break;
            case SBC_ABS_Y:
                cpu->cycles = 4;
                cpu->cycles += ABSY(cpu, memory);
                cpu->cycles += SBC(cpu, memory);
                break;
            case SBC_ABS_X:
                cpu->cycles = 4;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += SBC(cpu, memory);
                break;
            case INC_ABS_X:
                cpu->cycles = 7;
                cpu->cycles += ABSX(cpu, memory);
                cpu->cycles += INC(cpu, memory);
                break;
            default:
                break;
        }
        cpu->cycles--;
        printf("INSTRUCTION: %d\n", cpu->INS);
    }
}


void IRQ(struct CPU *cpu, struct MEMORY *memory)
{
    if(GetFlag(cpu, I) == 0)
    {
        memory->DATA[0x100 + cpu->SP] = (cpu->PC >> 8) & 0x00FF;
        cpu->SP--;
        memory->DATA[0x100 + cpu->SP] = cpu->PC & 0x00FF;
        cpu->SP--;

        SetFlag(cpu, B, 0);
        SetFlag(cpu, U, 1);
        SetFlag(cpu, I, 1);
        memory->DATA[0x100 + cpu->SP] = cpu->PS;
        cpu->SP--;

        cpu->ABS = 0xFFFE;
        uint16_t lo = memory->DATA[cpu->ABS+0];
        uint16_t hi = memory->DATA[cpu->ABS+1];
        cpu->PC = (hi << 8) | lo;

        cpu->cycles = 7;
    }
}

void NMI(struct CPU *cpu, struct MEMORY *memory)
{
        memory->DATA[0x100 + cpu->SP] = (cpu->PC >> 8) & 0x00FF;
        cpu->SP--;
        memory->DATA[0x100 + cpu->SP] = cpu->PC & 0x00FF;
        cpu->SP--;

        SetFlag(cpu, B, 0);
        SetFlag(cpu, U, 1);
        SetFlag(cpu, I, 1);
        memory->DATA[0x100 + cpu->SP] = cpu->PS;
        cpu->SP--;

        cpu->ABS = 0xFFFA;
        uint16_t lo = memory->DATA[cpu->ABS+0];
        uint16_t hi = memory->DATA[cpu->ABS+1];
        cpu->PC = (hi << 8) | lo;

        cpu->cycles = 8;
}

uint8_t GetFlag(struct CPU *cpu, enum FLAGS f)
{
    return ((cpu->PS & f) > 0) ? 1 : 0;
}

void SetFlag(struct CPU *cpu, enum FLAGS f, int i)
{
    if(i)
    {
        cpu->PS |= f;
    }
    else
    {
        cpu->PS &= ~f;
    }
}

uint8_t IMP(struct CPU *cpu)
{
    cpu->ABS = cpu->A;
    return 0;
}

uint8_t IMM(struct CPU *cpu)
{
    cpu->ABS = cpu->PC++;
    return 0;
}

uint8_t ZP(struct CPU *cpu, struct MEMORY *memory)
{
    cpu->ABS = memory->DATA[cpu->PC];
    cpu->PC++;
    cpu->ABS &= 0x00FF;
    return 0;
}

uint8_t ZPX(struct CPU *cpu, struct MEMORY *memory)
{
    cpu->ABS = memory->DATA[cpu->PC] + cpu->X;
    cpu->PC++;
    cpu->ABS &= 0x00FF;
    return 0;
}

uint8_t ZPY(struct CPU *cpu, struct MEMORY *memory)
{
    cpu->ABS = memory->DATA[cpu->PC] + cpu->Y;
    cpu->PC++;
    cpu->ABS &= 0x00FF;
    return 0;
}

uint8_t REL(struct CPU *cpu, struct MEMORY *memory)
{
    cpu->REL = memory->DATA[cpu->PC];
    cpu->PC++;
    if (cpu->REL & 0x80)
    {
        cpu->REL |= 0xFF00;
    }
    return 0;
}

uint8_t ABS(struct CPU *cpu, struct MEMORY *memory)
{
    uint16_t lo = memory->DATA[cpu->PC];
    cpu->PC++;
    uint16_t hi = memory->DATA[cpu->PC];
    cpu->PC++;
    cpu->ABS = (hi << 8) | lo;
    return 0;
}

uint8_t ABSX(struct CPU *cpu, struct MEMORY *memory)
{
    uint16_t lo = memory->DATA[cpu->PC];
    cpu->PC++;
    uint16_t hi = memory->DATA[cpu->PC];
    cpu->PC++;
    cpu->ABS = (hi << 8) | lo;
    cpu->ABS += cpu->X;
    if((cpu->ABS & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
       return 0;
    }

}

uint8_t ABSY(struct CPU *cpu, struct MEMORY *memory)
{
    uint16_t lo = memory->DATA[cpu->PC];
    cpu->PC++;
    uint16_t hi = memory->DATA[cpu->PC];
    cpu->PC++;
    cpu->ABS = (hi << 8) | lo;
    cpu->ABS += cpu->Y;
    if((cpu->ABS & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
       return 0;
    }
}

uint8_t IND(struct CPU *cpu, struct MEMORY *memory)
{
    uint16_t lo = memory->DATA[cpu->PC];
    cpu->PC++;
    uint16_t hi = memory->DATA[cpu->PC];
    cpu->PC++;
    uint16_t ptr = (hi << 8) | lo;
    if(lo == 0x00FF)
    {
        cpu->ABS = (memory->DATA[ptr&0xFF00] << 8) | memory->DATA[ptr+0];
    }
    else
    {
        cpu->ABS = (memory->DATA[ptr+1] << 8) | memory->DATA[ptr+0];
    }
    return 0;
}

uint8_t INDX(struct CPU *cpu, struct MEMORY *memory)
{
    uint16_t temp = memory->DATA[cpu->PC];
    cpu->PC++;
    uint16_t lo = memory->DATA[(uint16_t)((temp + cpu->X) & 0x00FF)];
    uint16_t hi = memory->DATA[(uint16_t)((temp + cpu->X + 1) & 0x00FF)];
    cpu->ABS = (hi << 8) | lo;
    return 0;
}

uint8_t INDY(struct CPU *cpu, struct MEMORY *memory)
{
    uint16_t temp = memory->DATA[cpu->PC];
    cpu->PC++;
    uint16_t lo = memory->DATA[temp & 0x00FF];
    uint16_t hi = memory->DATA[(temp+1) & 0x00FF];
    cpu->ABS = (hi << 8) | lo;
    cpu->ABS += cpu->Y;

    if ((cpu->ABS & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t AND(struct CPU *cpu, struct MEMORY *memory)
{
    cpu->A &= memory->DATA[cpu->ABS];
    SetFlag(cpu, Z, cpu->A==0x00);
    SetFlag(cpu, N, cpu->A&0x80);
    return 1;
}

uint8_t BCS(struct CPU *cpu)
{
    if(GetFlag(cpu, C) == 1)
    {
       Branch(cpu);
    }
    return 0;
}

uint8_t BCC(struct CPU *cpu)
{
    if(GetFlag(cpu, C) == 0)
    {
       Branch(cpu);
    }
    return 0;
}

uint8_t BEQ(struct CPU *cpu)
{
    if(GetFlag(cpu, Z) == 1)
    {
        Branch(cpu);
    }
    return 0;
}

uint8_t BMI(struct CPU *cpu)
{
    if(GetFlag(cpu, N) == 1)
    {
        Branch(cpu);
    }
    return 0;
}

uint8_t BNE(struct CPU *cpu)
{
    if(GetFlag(cpu, Z) == 0)
    {
        Branch(cpu);
    }
    return 0;
}

uint8_t BPL(struct CPU *cpu)
{
    if(GetFlag(cpu, N) == 0)
    {
        Branch(cpu);
    }
    return 0;
}

uint8_t BVC(struct CPU *cpu)
{
    if(GetFlag(cpu, V) == 1)
    {
        Branch(cpu);
    }
    return 0;
}

uint8_t BVS(struct CPU *cpu)
{
    if(GetFlag(cpu, V) == 0)
    {
        Branch(cpu);
    }
    return 0;
}

uint8_t BIT(struct CPU *cpu, struct MEMORY *memory)
{
	uint16_t temp = cpu->A & memory->DATA[cpu->ABS];
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x00);
	SetFlag(cpu, N, memory->DATA[cpu->ABS] & (1 << 7));
	SetFlag(cpu, V, memory->DATA[cpu->ABS] & (1 << 6));
	return 0;
}

void Branch(struct CPU *cpu)
{
    cpu->cycles++;
    cpu->ABS = cpu->PC + cpu->REL;
    if((cpu->ABS & 0xFF00) != (cpu->PC & 0xFF00))
    {
        cpu->cycles++;
    }
    cpu->PC = cpu->ABS;
}

uint8_t CLC(struct CPU *cpu)
{
    SetFlag(cpu, C, 0);
    return 0;
}


uint8_t CLD(struct CPU *cpu)
{
    SetFlag(cpu, D, 0);
    return 0;
}

uint8_t CLI(struct CPU *cpu)
{
    SetFlag(cpu, I, 0);
    return 0;
}


uint8_t CLV(struct CPU *cpu)
{
    SetFlag(cpu, V, 0);
    return 0;
}

uint8_t ADC(struct CPU *cpu, struct MEMORY *memory)
{
	uint16_t temp = (uint16_t)cpu->A + (uint16_t)memory->DATA[cpu->ABS] + (uint16_t)GetFlag(cpu, C);
	SetFlag(cpu, C, temp > 255);
	SetFlag(cpu, Z, (temp & 0x00FF) == 0);
	SetFlag(cpu, V, (~((uint16_t)cpu->A ^ (uint16_t)memory->DATA[cpu->ABS]) & ((uint16_t)cpu->A ^ (uint16_t)temp)) & 0x0080);
	SetFlag(cpu, N, temp & 0x80);
	cpu->A = temp & 0x00FF;
	return 1;
}

uint8_t SBC(struct CPU *cpu, struct MEMORY *memory)
{
	uint16_t value = ((uint16_t)memory->DATA[cpu->ABS]) ^ 0x00FF;
	uint16_t temp = (uint16_t)cpu->A + value + (uint16_t)GetFlag(cpu, C);
	SetFlag(cpu, C, (uint8_t)temp & 0xFF00);
	SetFlag(cpu, Z, ((temp & 0x00FF) == 0));
	SetFlag(cpu, V, (temp ^ (uint16_t)cpu->A) & (temp ^ value) & 0x0080);
	SetFlag(cpu, N, temp & 0x0080);
	cpu->A = temp & 0x00FF;
	return 1;
}

uint8_t PHP(struct CPU *cpu, struct MEMORY *memory)
{
    memory->DATA[0x100 + cpu->SP] = cpu->PS | B | U;
	SetFlag(cpu, B, 0);
	SetFlag(cpu, U, 0);
	cpu->SP--;
	return 0;
}

uint8_t PHA(struct CPU *cpu, struct MEMORY *memory)
{
    memory->DATA[0x100 + cpu->SP] = cpu->A;
    cpu->SP--;
    return 0;
}

uint8_t PLA(struct CPU *cpu, struct MEMORY *memory)
{
    cpu->SP++;
    cpu->A = memory->DATA[0x100 + cpu->SP];
    SetFlag(cpu, Z, cpu->A == 0x00);
    SetFlag(cpu, N, cpu->A & 0x80);
    return 0;
}

uint8_t PLP(struct CPU *cpu, struct MEMORY *memory)
{
    cpu->SP++;
    cpu->PS = memory->DATA[0x100 + cpu->SP];
	SetFlag(cpu, U, 1);
	return 0;
}

uint8_t ASL(struct CPU *cpu, struct MEMORY *memory, uint8_t IMP)
{
    uint16_t temp = memory->DATA[cpu->ABS] << 1;
    SetFlag(cpu, C, (temp & 0xFF00) > 0);
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x00);
	SetFlag(cpu, N, temp & 0x80);
    if (IMP==1)
    {
        cpu->A = temp & 0x00FF;
    }
	else
    {
        memory->DATA[cpu->ABS] = temp & 0x00FF;
    }
    return 0;
}

uint8_t BRK(struct CPU *cpu, struct MEMORY *memory)
{
	cpu->PC++;

	SetFlag(cpu, I, 1);
	memory->DATA[0x0100 + cpu->SP] = (cpu->PC >> 8) & 0x00FF;
	cpu->SP--;
	memory->DATA[0x0100 + cpu->SP] = cpu->PC & 0x00FF;
	cpu->SP--;

	SetFlag(cpu, B, 1);
	memory->DATA[0x0100 + cpu->SP] = cpu->PS;
	cpu->SP--;
	SetFlag(cpu, B, 0);

	cpu->PC = (uint16_t)memory->DATA[0xFFFE] | ((uint16_t)memory->DATA[0xFFFF] << 8);
	return 0;
}

uint8_t CMP(struct CPU *cpu, struct MEMORY *memory)
{
	uint16_t temp = (uint16_t)cpu->A - (uint16_t)memory->DATA[cpu->ABS];
	SetFlag(cpu, C, cpu->A >= memory->DATA[cpu->ABS]);
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x0000);
	SetFlag(cpu, N, temp & 0x0080);
	return 1;
}

uint8_t CPX(struct CPU *cpu, struct MEMORY *memory)
{
    uint16_t temp = (uint16_t)cpu->X - (uint16_t)memory->DATA[cpu->ABS];
	SetFlag(cpu, C, cpu->X >= memory->DATA[cpu->ABS]);
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x0000);
	SetFlag(cpu, N, temp & 0x0080);
	return 0;
}

uint8_t CPY(struct CPU *cpu, struct MEMORY *memory)
{
	uint16_t temp = (uint16_t)cpu->Y - (uint16_t)memory->DATA[cpu->ABS];
	SetFlag(cpu, C, cpu->Y >= memory->DATA[cpu->ABS]);
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x0000);
	SetFlag(cpu, N, temp & 0x0080);
	return 0;
}

uint8_t DEC(struct CPU *cpu, struct MEMORY *memory)
{
	uint16_t temp = memory->DATA[cpu->ABS] - 1;
	memory->DATA[cpu->ABS] = temp & 0x00FF;
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x0000);
	SetFlag(cpu, N, temp & 0x0080);
	return 0;
}

uint8_t DEX(struct CPU *cpu)
{
	cpu->X--;
	SetFlag(cpu, Z, cpu->X == 0x00);
	SetFlag(cpu, N, cpu->X & 0x80);
	return 0;
}

uint8_t DEY(struct CPU *cpu)
{
	cpu->Y--;
	SetFlag(cpu, Z, cpu->Y == 0x00);
	SetFlag(cpu, N, cpu->Y & 0x80);
	return 0;
}

uint8_t INC(struct CPU *cpu, struct MEMORY *memory)
{;
	uint16_t temp = memory->DATA[cpu->ABS] + 1;
	memory->DATA[cpu->ABS] = temp & 0x00FF;
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x0000);
	SetFlag(cpu, N, temp & 0x0080);
	return 0;
}

uint8_t INX(struct CPU *cpu)
{
	cpu->X++;
	SetFlag(cpu, Z, cpu->X == 0x00);
	SetFlag(cpu, N, cpu->X & 0x80);
	return 0;
}

uint8_t INY(struct CPU *cpu)
{
	cpu->Y++;
	SetFlag(cpu, Z, cpu->Y == 0x00);
	SetFlag(cpu, N, cpu->Y & 0x80);
	return 0;
}

uint8_t JMP(struct CPU *cpu)
{
	cpu->PC = cpu->ABS;
	return 0;
}

uint8_t JSR(struct CPU *cpu, struct MEMORY *memory)
{
	cpu->PC--;
	memory->DATA[0x0100 + cpu->SP] = (cpu->PC >> 8) & 0x00FF;
	cpu->SP--;
	memory->DATA[0x0100 + cpu->SP] = cpu->PC & 0x00FF;
	cpu->SP--;
	cpu->PC = cpu->ABS;
	return 0;
}

uint8_t LDA(struct CPU *cpu, struct MEMORY *memory)
{
	cpu->A = memory->DATA[cpu->ABS];
	SetFlag(cpu, Z, cpu->A == 0x00);
	SetFlag(cpu, N, cpu->A & 0x80);
	return 1;
}

uint8_t LDX(struct CPU *cpu, struct MEMORY *memory)
{
	cpu->X = memory->DATA[cpu->ABS];
	SetFlag(cpu, Z, cpu->X == 0x00);
	SetFlag(cpu, N, cpu->X & 0x80);
	return 1;
}

uint8_t LDY(struct CPU *cpu, struct MEMORY *memory)
{
	cpu->Y = memory->DATA[cpu->ABS];
	SetFlag(cpu, Z, cpu->Y == 0x00);
	SetFlag(cpu, N, cpu->Y & 0x80);
	return 1;
}

uint8_t LSR(struct CPU *cpu, struct MEMORY *memory, uint8_t imp)
{
	SetFlag(cpu, C, memory->DATA[cpu->ABS] & 0x0001);
	uint16_t temp = memory->DATA[cpu->ABS] >> 1;
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x0000);
	SetFlag(cpu, N, temp & 0x0080);
	if (imp)
    {
        cpu->A = temp & 0x00FF;
    }
	else
    {
        memory->DATA[cpu->ABS] = temp & 0x00FF;
    }
	return 0;
}

uint8_t EOR(struct CPU *cpu, struct MEMORY *memory)
{
	cpu->A = cpu->A ^ memory->DATA[cpu->ABS];
	SetFlag(cpu, Z, cpu->A  == 0x00);
	SetFlag(cpu, N, cpu->A  & 0x80);
	return 1;
}

uint8_t ORA(struct CPU *cpu, struct MEMORY *memory)
{
	cpu->A = cpu->A | memory->DATA[cpu->ABS];
	SetFlag(cpu, Z, cpu->A  == 0x00);
	SetFlag(cpu, N, cpu->A  & 0x80);
	return 1;
}

uint8_t ROL(struct CPU *cpu, struct MEMORY *memory, uint8_t imp)
{
	uint16_t temp = (uint16_t)(memory->DATA[cpu->ABS] << 1) | GetFlag(cpu, C);
	SetFlag(cpu, C, temp & 0xFF00);
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x0000);
	SetFlag(cpu, N, temp & 0x0080);
	if (imp)
    {
        cpu->A = temp & 0x00FF;
    }
	else
    {
        memory->DATA[cpu->ABS] = temp & 0x00FF;
    }
	return 0;
}

uint8_t ROR(struct CPU *cpu, struct MEMORY *memory, uint8_t imp)
{
	uint16_t temp = (uint16_t)(GetFlag(cpu, C) << 7) | (memory->DATA[cpu->ABS] >> 1);
	SetFlag(cpu, C, memory->DATA[cpu->ABS] & 0x01);
	SetFlag(cpu, Z, (temp & 0x00FF) == 0x00);
	SetFlag(cpu, N, temp & 0x0080);
	if (imp)
    {
        cpu->A = temp & 0x00FF;
    }
	else
    {
        memory->DATA[cpu->ABS] = temp & 0x00FF;
    }
	return 0;
}

uint8_t RTI(struct CPU *cpu, struct MEMORY *memory)
{
	cpu->SP++;
	cpu->PS = memory->DATA[0x0100 + cpu->SP];
	cpu->PS &= ~B;
	cpu->PS &= ~U;

	cpu->SP++;
	cpu->PC = (uint16_t)memory->DATA[0x0100 + cpu->SP];
	cpu->SP++;
	cpu->PC |= (uint16_t)memory->DATA[0x0100 + cpu->SP] << 8;
	return 0;
}

uint8_t RTS(struct CPU *cpu, struct MEMORY *memory)
{
	cpu->SP++;
	cpu->PC = (uint16_t)memory->DATA[0x0100 + cpu->SP];
	cpu->SP++;
	cpu->PC |= (uint16_t)memory->DATA[0x0100 + cpu->SP] << 8;
	cpu->PC++;
	return 0;
}

uint8_t SEC(struct CPU *cpu)
{
	SetFlag(cpu, C, 1);
	return 0;
}

uint8_t SED(struct CPU *cpu)
{
	SetFlag(cpu, D, 1);
	return 0;
}

uint8_t SEI(struct CPU *cpu)
{
	SetFlag(cpu, I, 1);
	return 0;
}

uint8_t STA(struct CPU *cpu, struct MEMORY *memory)
{
	memory->DATA[cpu->ABS] = cpu->A;
	return 0;
}

uint8_t STX(struct CPU *cpu, struct MEMORY *memory)
{
	memory->DATA[cpu->ABS] = cpu->X;
	return 0;
}

uint8_t STY(struct CPU *cpu, struct MEMORY *memory)
{
	memory->DATA[cpu->ABS] = cpu->Y;
	return 0;
}

uint8_t TAX(struct CPU *cpu)
{
	cpu->X = cpu->A;
	SetFlag(cpu, Z, cpu->X == 0x00);
	SetFlag(cpu, N, cpu->X & 0x80);
	return 0;
}

uint8_t TAY(struct CPU *cpu)
{
	cpu->Y = cpu->A;
	SetFlag(cpu, Z, cpu->Y == 0x00);
	SetFlag(cpu, N, cpu->Y & 0x80);
	return 0;
}

uint8_t TSX(struct CPU *cpu)
{
	cpu->X = cpu->SP;
	SetFlag(cpu, Z, cpu->X == 0x00);
	SetFlag(cpu, N, cpu->X & 0x80);
	return 0;
}

uint8_t TXA(struct CPU *cpu)
{
	cpu->A = cpu->X;
	SetFlag(cpu, Z, cpu->A == 0x00);
	SetFlag(cpu, N, cpu->A & 0x80);
	return 0;
}

uint8_t TXS(struct CPU *cpu)
{
	cpu->SP = cpu->X;
	return 0;
}

uint8_t TYA(struct CPU *cpu)
{
	cpu->A = cpu->Y;
	SetFlag(cpu, Z, cpu->A == 0x00);
	SetFlag(cpu, N, cpu->A & 0x80);
	return 0;
}

uint8_t NOP()
{
	return 0;
}

/* Fetches byte that is in the memory at where program counter is pointing to */
uint8_t FetchByte(struct CPU *cpu, struct MEMORY *memory)
{
    uint8_t data = memory->DATA[cpu->PC];
    cpu->PC++;
    //cpu->cycles--;
    return data;
}
