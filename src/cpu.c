#include "include/cpu.h"
#include "include/memory.h"
#include <bits/types.h>
#include <stdio.h>

CPU cpu;

/* RESETS CPU to startup state */
void ResetCpu()
{
    //SET Program Counter
	cpu.ABS = 0xFFFC;
    printf("ABS: %d\n", memory.CPURAM[cpu.ABS]);
	uint16_t lo = memory.CPURAM[cpu.ABS];
	uint16_t hi = memory.CPURAM[cpu.ABS+1];
	cpu.PC = (hi << 8) | lo;

	// Reset internal registers
	cpu.A = 0;
	cpu.X = 0;
	cpu.Y = 0;
	cpu.SP = 0xFD;
	cpu.PS = 0x00 | U;

	// Clear internal helper variables
	cpu.REL = 0x0000;
	cpu.ABS = 0x0000;

	// Reset takes time
	cpu.cycles = 8;
}

/* Executes the next instruction in the cycle */
void CPUClock()
{
        //printf("PC: %d\n", cpu.PC);
        //printf("Cycles: %d\n", cpu.cycles);
        cpu.INS = FetchByte();
        switch(cpu.INS)
        {
            case BRK_IMP:
                cpu.cycles = 7;
                cpu.cycles += IMP();
                cpu.cycles += BRK();
                break;
            case ORA_IND_X:
                cpu.cycles = 6;
                cpu.cycles += INDX();
                cpu.cycles += ORA();
                break;
            case ORA_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += ORA();
                break;
            case ASL_ZP:
                cpu.cycles = 5;
                cpu.cycles += ZP();
                cpu.cycles += ASL(0);
                break;
            case PHP_IMP:
                cpu.cycles = 3;
                cpu.cycles += IMP();
                cpu.cycles += PHP();
                break;
            case ASL_ACC:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += ASL(1);
                break;
            case ORA_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += ORA();
                break;
            case ASL_ABS:
                cpu.cycles = 6;
                cpu.cycles += ABS();
                cpu.cycles += ASL(0);
                break;
            case BPL_REL:
                cpu.cycles = 2;
                cpu.cycles += REL();
                cpu.cycles += BPL();
                break;
            case ORA_IND_Y:
                cpu.cycles = 5;
                cpu.cycles += INDY();
                cpu.cycles += ORA();
                break;
            case ORA_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += ORA();
                break;
            case ASL_ZP_X:
                cpu.cycles = 6;
                cpu.cycles += ZPX();
                cpu.cycles += ASL(0);
                break;
            case CLC_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += CLC();
                break;
            case ORA_ABS_Y:
                cpu.cycles = 4;
                cpu.cycles += ABSY();
                cpu.cycles += ORA();
                break;
            case ORA_ABS_X:
                cpu.cycles = 4;
                cpu.cycles += ABSX();
                cpu.cycles += ORA();
                break;
            case ASL_ABS_X:
                cpu.cycles = 7;
                cpu.cycles += ABSX();
                cpu.cycles += ASL(0);
                break;
            case JSR_ABS:
                cpu.cycles = 6;
                cpu.cycles += ABS();
                cpu.cycles += JSR();
                break;
            case AND_IND_X:
                cpu.cycles = 6;
                cpu.cycles += INDX();
                cpu.cycles += AND();
                break;
            case BIT_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += BIT();
                break;
            case AND_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += AND();
                break;
            case ROL_ZP:
                cpu.cycles = 5;
                cpu.cycles += ZP();
                cpu.cycles += ROL(0);
                break;
            case PLP_IMP:
                cpu.cycles = 4;
                cpu.cycles += IMP();
                cpu.cycles += PLP();
                break;
            case AND_IMM:
                cpu.cycles = 2;
                cpu.cycles += IMM();
                cpu.cycles += AND();
                break;
            case ROL_ACC:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += ROL(1);
                break;
            case BIT_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += BIT();
                break;
            case AND_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += AND();
                break;
            case ROL_ABS:
                cpu.cycles = 6;
                cpu.cycles += ABS();
                cpu.cycles += ROL(0);
                break;
            case BMI_REL:
                cpu.cycles = 2;
                cpu.cycles += REL();
                cpu.cycles += BMI();
                break;
            case AND_IND_Y:
                cpu.cycles = 5;
                cpu.cycles += INDY();
                cpu.cycles += AND();
                break;
            case AND_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += AND();
                break;
            case ROL_ZP_X:
                cpu.cycles = 6;
                cpu.cycles += ZPX();
                cpu.cycles += ROL(0);
                break;
            case SEC_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += SEC();
                break;
            case AND_ABS_Y:
                cpu.cycles = 4;
                cpu.cycles += ABSY();
                cpu.cycles += AND();
                break;
            case AND_ABS_X:
                cpu.cycles = 4;
                cpu.cycles += ABSX();
                cpu.cycles += AND();
                break;
            case ROL_ABS_X:
                cpu.cycles = 7;
                cpu.cycles += ABSX();
                cpu.cycles += ROL(0);
                break;
            case RTI_IMP:
                cpu.cycles = 6;
                cpu.cycles += IMP();
                cpu.cycles += RTI();
                break;
            case EOR_IND_X:
                cpu.cycles = 6;
                cpu.cycles += INDX();
                cpu.cycles += EOR();
                break;
            case EOR_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += EOR();
                break;
            case LSR_ZP:
                cpu.cycles = 5;
                cpu.cycles += ZP();
                cpu.cycles += LSR(0);
                break;
            case PHA_IMP:
                cpu.cycles = 3;
                cpu.cycles += IMP();
                cpu.cycles += PHA();
                break;
            case EOR_IMM:
                cpu.cycles = 2;
                cpu.cycles += IMM();
                cpu.cycles += EOR();
                break;
            case LSR_ACC:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += LSR(1);
                break;
            case JMP_ABS:
                cpu.cycles = 3;
                cpu.cycles += ABS();
                cpu.cycles += JMP();
                break;
            case EOR_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += EOR();
                break;
            case LSR_ABS:
                cpu.cycles = 6;
                cpu.cycles += ABS();
                cpu.cycles += LSR(0);
                break;
            case BVC_REL:
                cpu.cycles = 2;
                cpu.cycles += REL();
                cpu.cycles += BVC();
                break;
            case EOR_IND_Y:
                cpu.cycles = 5;
                cpu.cycles += INDY();
                cpu.cycles += EOR();
                break;
            case EOR_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += EOR();
                break;
            case LSR_ZP_X:
                cpu.cycles = 6;
                cpu.cycles += ZPX();
                cpu.cycles += LSR(0);
                break;
            case CLI_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += CLI();
                break;
            case EOR_ABS_Y:
                cpu.cycles = 4;
                cpu.cycles += ABSY();
                cpu.cycles += EOR();
                break;
            case EOR_ABS_X:
                cpu.cycles = 4;
                cpu.cycles += ABSX();
                cpu.cycles += EOR();
                break;
            case LSR_ABS_X:
                cpu.cycles = 7;
                cpu.cycles += ABSX();
                cpu.cycles += LSR(0);
                break;
            case RTS_IMP:
                cpu.cycles = 6;
                cpu.cycles += IMP();
                cpu.cycles += RTS();
                break;
            case ADC_IND_X:
                cpu.cycles = 6;
                cpu.cycles += INDX();
                cpu.cycles += ADC();
                break;
            case ADC_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += ADC();
                break;
            case ROR_ZP:
                cpu.cycles = 5;
                cpu.cycles += ZP();
                cpu.cycles += ROR(0);
                break;
            case PLA_IMP:
                cpu.cycles = 4;
                cpu.cycles += IMP();
                cpu.cycles += PLA();
                break;
            case ADC_IMM:
                cpu.cycles = 2;
                cpu.cycles += IMM();
                cpu.cycles += ADC();
                break;
            case ROR_ACC:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += ROR(1);
                break;
            case JMP_IND:
                cpu.cycles = 5;
                cpu.cycles += IND();
                cpu.cycles += JMP();
                break;
            case ADC_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += ADC();
                break;
            case ROR_ABS:
                cpu.cycles = 6;
                cpu.cycles += ABS();
                cpu.cycles += ROR(0);
                break;
            case BVS_REL:
                cpu.cycles = 2;
                cpu.cycles += REL();
                cpu.cycles += BVS();
                break;
            case ADC_IND_Y:
                cpu.cycles = 5;
                cpu.cycles += INDY();
                cpu.cycles += ADC();
                break;
            case ADC_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += ADC();
                break;
            case ROR_ZP_X:
                cpu.cycles = 6;
                cpu.cycles += ZPX();
                cpu.cycles += ROR(0);
                break;
            case SEI_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += SEI();
                break;
            case ADC_ABS_Y:
                cpu.cycles = 4;
                cpu.cycles += ABSY();
                cpu.cycles += ADC();
                break;
            case ADC_ABS_X:
                cpu.cycles = 4;
                cpu.cycles += ABSX();
                cpu.cycles += ADC();
                break;
            case ROR_ABS_X:
                cpu.cycles = 7;
                cpu.cycles += ABSX();
                cpu.cycles += ROR(0);
                break;
            case STA_IND_X:
                cpu.cycles = 6;
                cpu.cycles += INDX();
                cpu.cycles += STA();
                break;
            case STY_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += STY();
                break;
            case STA_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += STA();
                break;
            case STX_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += STX();
                break;
            case DEY_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += DEY();
                break;
            case TXA_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += TXA();
                break;
            case STY_ABS:
                cpu.cycles = 3;
                cpu.cycles += ABS();
                cpu.cycles += STY();
                break;
            case STA_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += STA();
                break;
            case STX_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += STX();
                break;
            case BCC_REL:
                cpu.cycles = 2;
                cpu.cycles += REL();
                cpu.cycles += BCC();
                break;
            case STA_IND_Y:
                cpu.cycles = 6;
                cpu.cycles += INDY();
                cpu.cycles += STA();
                break;
            case STY_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += STY();
                break;
            case STA_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += STA();
                break;
            case STX_ZP_Y:
                cpu.cycles = 4;
                cpu.cycles += ZPY();
                cpu.cycles += STX();
                break;
            case TYA_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += TYA();
                break;
            case STA_ABS_Y:
                cpu.cycles = 5;
                cpu.cycles += ABSY();
                cpu.cycles += STA();
                break;
            case TXS_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += TXS();
                break;
            case STA_ABS_X:
                cpu.cycles = 5;
                cpu.cycles += ABSX();
                cpu.cycles += STA();
                break;
            case LDY_IMM:
                cpu.cycles = 2;
                cpu.cycles += IMM();
                cpu.cycles += LDY();
                break;
            case LDA_IND_X:
                cpu.cycles = 6;
                cpu.cycles += INDX();
                cpu.cycles += LDA();
                break;
            case LDX_IMM:
                cpu.cycles = 2;
                cpu.cycles += IMM();
                cpu.cycles += LDX();
                break;
            case LDY_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += LDY();
                break;
            case LDA_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += LDA();
                break;
            case LDX_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += LDX();
                break;
            case TAY_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += TAY();
                break;
            case LDA_IMM:
                cpu.cycles = 2;
                cpu.cycles += IMM();
                cpu.cycles += LDA();
                break;
            case TAX_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += TAX();
                break;
            case LDY_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += LDY();
                break;
            case LDA_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += LDA();
                break;
            case LDX_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += LDX();
                break;
            case BCS_REL:
                cpu.cycles = 2;
                cpu.cycles += REL();
                cpu.cycles += BCS();
                break;
            case LDA_IND_Y:
                cpu.cycles = 5;
                cpu.cycles += INDY();
                cpu.cycles += LDA();
                break;
            case LDY_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += LDY();
                break;
            case LDA_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += LDA();
                break;
            case LDX_ZP_Y:
                cpu.cycles = 4;
                cpu.cycles += ZPY();
                cpu.cycles += LDX();
                break;
            case CLV_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += CLV();
                break;
            case LDA_ABS_Y:
                cpu.cycles = 4;
                cpu.cycles += ABSY();
                cpu.cycles += LDA();
                break;
            case TSX_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += TSX();
                break;
            case LDY_ABS_X:
                cpu.cycles = 4;
                cpu.cycles += ABSX();
                cpu.cycles += LDY();
                break;
            case LDA_ABS_X:
                cpu.cycles = 4;
                cpu.cycles += ABSX();
                cpu.cycles += LDA();
                break;
            case LDX_ABS_Y:
                cpu.cycles = 4;
                cpu.cycles += ABSY();
                cpu.cycles += LDX();
                break;
            case CPY_IMM:
                cpu.cycles = 2;
                cpu.cycles += IMM();
                cpu.cycles += CPY();
                break;
            case CMP_IND_X:
                cpu.cycles = 6;
                cpu.cycles += INDX();
                cpu.cycles += CMP();
                break;
            case CPY_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += CPY();
                break;
            case CMP_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += CMP();
                break;
            case DEC_ZP:
                cpu.cycles = 5;
                cpu.cycles += ZP();
                cpu.cycles += DEC();
                break;
            case INY_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += INY();
                break;
            case CMP_IMM:
                cpu.cycles = 2;
                cpu.cycles += IMM();
                cpu.cycles += CMP();
                break;
            case DEX_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += DEX();
                break;
            case CPY_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += CPY();
                break;
            case CMP_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += CMP();
                break;
            case DEC_ABS:
                cpu.cycles = 6;
                cpu.cycles += ABS();
                cpu.cycles += DEC();
                break;
            case BNE_REL:
                cpu.cycles = 2;
                cpu.cycles += REL();
                cpu.cycles += BNE();
                break;
            case CMP_IND_Y:
                cpu.cycles = 5;
                cpu.cycles += INDY();
                cpu.cycles += CMP();
                break;
            case CMP_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += CMP();
                break;
            case DEC_ZP_X:
                cpu.cycles = 6;
                cpu.cycles += ZPX();
                cpu.cycles += DEC();
                break;
            case CLD_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += CLD();
                break;
            case CMP_ABS_Y:
                cpu.cycles = 4;
                cpu.cycles += ABSY();
                cpu.cycles += CMP();
                break;
            case CMP_ABS_X:
                cpu.cycles = 4;
                cpu.cycles += ABSX();
                cpu.cycles += CMP();
                break;
            case DEC_ABS_X:
                cpu.cycles = 7;
                cpu.cycles += ABSX();
                cpu.cycles += DEC();
                break;
            case CPX_IMM:
                cpu.cycles = 3;
                cpu.cycles += IMM();
                cpu.cycles += CPX();
                break;
            case SBC_IND_X:
                cpu.cycles = 6;
                cpu.cycles += INDX();
                cpu.cycles += SBC();
                break;
            case CPX_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += CPX();
                break;
            case SBC_ZP:
                cpu.cycles = 3;
                cpu.cycles += ZP();
                cpu.cycles += SBC();
                break;
            case INC_ZP:
                cpu.cycles = 5;
                cpu.cycles += ZP();
                cpu.cycles += INC();
                break;
            case INX_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += INX();
                break;
            case SBC_IMM:
                cpu.cycles = 2;
                cpu.cycles += IMM();
                cpu.cycles += SBC();
                break;
            case NOP_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += NOP();
                break;
            case CPX_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += CPX();
                break;
            case SBC_ABS:
                cpu.cycles = 4;
                cpu.cycles += ABS();
                cpu.cycles += SBC();
                break;
            case INC_ABS:
                cpu.cycles = 6;
                cpu.cycles += ABS();
                cpu.cycles += INC();
                break;
            case BEQ_REL:
                cpu.cycles = 2;
                cpu.cycles += REL();
                cpu.cycles += BEQ();
                break;
            case SBC_IND_Y:
                cpu.cycles = 5;
                cpu.cycles += INDY();
                cpu.cycles += SBC();
                break;
            case SBC_ZP_X:
                cpu.cycles = 4;
                cpu.cycles += ZPX();
                cpu.cycles += SBC();
                break;
            case INC_ZP_X:
                cpu.cycles = 6;
                cpu.cycles += ZPX();
                cpu.cycles += INC();
                break;
            case SED_IMP:
                cpu.cycles = 2;
                cpu.cycles += IMP();
                cpu.cycles += SED();
                break;
            case SBC_ABS_Y:
                cpu.cycles = 4;
                cpu.cycles += ABSY();
                cpu.cycles += SBC();
                break;
            case SBC_ABS_X:
                cpu.cycles = 4;
                cpu.cycles += ABSX();
                cpu.cycles += SBC();
                break;
            case INC_ABS_X:
                cpu.cycles = 7;
                cpu.cycles += ABSX();
                cpu.cycles += INC();
                break;
            default:
                break;
        }
        cpu.cycles--;
       //printf("INSTRUCTION: %d\n", cpu.INS);
}


void IRQ()
{
    if(GetFlag(I) == 0)
    {
        memory.CPURAM[0x100 + cpu.SP] = (cpu.PC >> 8) & 0x00FF;
        cpu.SP--;
        memory.CPURAM[0x100 + cpu.SP] = cpu.PC & 0x00FF;
        cpu.SP--;

        SetFlag(B, 0);
        SetFlag(U, 1);
        SetFlag(I, 1);
        memory.CPURAM[0x100 + cpu.SP] = cpu.PS;
        cpu.SP--;

        cpu.ABS = 0xFFFE;
        uint16_t lo = memory.CPURAM[cpu.ABS+0];
        uint16_t hi = memory.CPURAM[cpu.ABS+1];
        cpu.PC = (hi << 8) | lo;

        cpu.cycles = 7;
    }
}

void NMI()
{
        memory.CPURAM[0x100 + cpu.SP] = (cpu.PC >> 8) & 0x00FF;
        cpu.SP--;
        memory.CPURAM[0x100 + cpu.SP] = cpu.PC & 0x00FF;
        cpu.SP--;

        SetFlag(B, 0);
        SetFlag(U, 1);
        SetFlag(I, 1);
        memory.CPURAM[0x100 + cpu.SP] = cpu.PS;
        cpu.SP--;

        cpu.ABS = 0xFFFA;
        uint16_t lo = memory.CPURAM[cpu.ABS+0];
        uint16_t hi = memory.CPURAM[cpu.ABS+1];
        cpu.PC = (hi << 8) | lo;

        cpu.cycles = 8;
}

uint8_t GetFlag(enum FLAGS f)
{
    return ((cpu.PS & f) > 0) ? 1 : 0;
}

void SetFlag(enum FLAGS f, int i)
{
    if(i)
    {
        cpu.PS |= f;
    }
    else
    {
        cpu.PS &= ~f;
    }
}

uint8_t IMP()
{
    cpu.ABS = cpu.A;
    return 0;
}

uint8_t IMM()
{
    cpu.ABS = cpu.PC++;
    return 0;
}

uint8_t ZP()
{
    cpu.ABS = memory.CPURAM[cpu.PC];
    cpu.PC++;
    cpu.ABS &= 0x00FF;
    return 0;
}

uint8_t ZPX()
{
    cpu.ABS = memory.CPURAM[cpu.PC] + cpu.X;
    cpu.PC++;
    cpu.ABS &= 0x00FF;
    return 0;
}

uint8_t ZPY()
{
    cpu.ABS = memory.CPURAM[cpu.PC] + cpu.Y;
    cpu.PC++;
    cpu.ABS &= 0x00FF;
    return 0;
}

uint8_t REL()
{
    cpu.REL = memory.CPURAM[cpu.PC];
    cpu.PC++;
    if (cpu.REL & 0x80)
    {
        cpu.REL |= 0xFF00;
    }
    return 0;
}

uint8_t ABS()
{
    uint16_t lo = memory.CPURAM[cpu.PC];
    cpu.PC++;
    uint16_t hi = memory.CPURAM[cpu.PC];
    cpu.PC++;
    cpu.ABS = (hi << 8) | lo;
    return 0;
}

uint8_t ABSX()
{
    uint16_t lo = memory.CPURAM[cpu.PC];
    cpu.PC++;
    uint16_t hi = memory.CPURAM[cpu.PC];
    cpu.PC++;
    cpu.ABS = (hi << 8) | lo;
    cpu.ABS += cpu.X;
    if((cpu.ABS & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
       return 0;
    }

}

uint8_t ABSY()
{
    uint16_t lo = memory.CPURAM[cpu.PC];
    cpu.PC++;
    uint16_t hi = memory.CPURAM[cpu.PC];
    cpu.PC++;
    cpu.ABS = (hi << 8) | lo;
    cpu.ABS += cpu.Y;
    if((cpu.ABS & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
       return 0;
    }
}

uint8_t IND()
{
    uint16_t lo = memory.CPURAM[cpu.PC];
    cpu.PC++;
    uint16_t hi = memory.CPURAM[cpu.PC];
    cpu.PC++;
    uint16_t ptr = (hi << 8) | lo;
    if(lo == 0x00FF)
    {
        cpu.ABS = (memory.CPURAM[ptr&0xFF00] << 8) | memory.CPURAM[ptr+0];
    }
    else
    {
        cpu.ABS = (memory.CPURAM[ptr+1] << 8) | memory.CPURAM[ptr+0];
    }
    return 0;
}

uint8_t INDX()
{
    uint16_t temp = memory.CPURAM[cpu.PC];
    cpu.PC++;
    uint16_t lo = memory.CPURAM[(uint16_t)((temp + cpu.X) & 0x00FF)];
    uint16_t hi = memory.CPURAM[(uint16_t)((temp + cpu.X + 1) & 0x00FF)];
    cpu.ABS = (hi << 8) | lo;
    return 0;
}

uint8_t INDY()
{
    uint16_t temp = memory.CPURAM[cpu.PC];
    cpu.PC++;
    uint16_t lo = memory.CPURAM[temp & 0x00FF];
    uint16_t hi = memory.CPURAM[(temp+1) & 0x00FF];
    cpu.ABS = (hi << 8) | lo;
    cpu.ABS += cpu.Y;

    if ((cpu.ABS & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t AND()
{
    cpu.A &= memory.CPURAM[cpu.ABS];
    SetFlag(Z, cpu.A==0x00);
    SetFlag(N, cpu.A&0x80);
    return 1;
}

uint8_t BCS()
{
    if(GetFlag(C) == 1)
    {
       Branch();
    }
    return 0;
}

uint8_t BCC()
{
    if(GetFlag(C) == 0)
    {
       Branch();
    }
    return 0;
}

uint8_t BEQ()
{
    if(GetFlag(Z) == 1)
    {
        Branch();
    }
    return 0;
}

uint8_t BMI()
{
    if(GetFlag(N) == 1)
    {
        Branch();
    }
    return 0;
}

uint8_t BNE()
{
    if(GetFlag(Z) == 0)
    {
        Branch();
    }
    return 0;
}

uint8_t BPL()
{
    if(GetFlag(N) == 0)
    {
        Branch();
    }
    return 0;
}

uint8_t BVC()
{
    if(GetFlag(V) == 1)
    {
        Branch();
    }
    return 0;
}

uint8_t BVS()
{
    if(GetFlag(V) == 0)
    {
        Branch();
    }
    return 0;
}

uint8_t BIT()
{
	uint16_t temp = cpu.A & memory.CPURAM[cpu.ABS];
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, memory.CPURAM[cpu.ABS] & (1 << 7));
	SetFlag(V, memory.CPURAM[cpu.ABS] & (1 << 6));
	return 0;
}

void Branch()
{
    cpu.cycles++;
    cpu.ABS = cpu.PC + cpu.REL;
    if((cpu.ABS & 0xFF00) != (cpu.PC & 0xFF00))
    {
        cpu.cycles++;
    }
    cpu.PC = cpu.ABS;
}

uint8_t CLC()
{
    SetFlag(C, 0);
    return 0;
}


uint8_t CLD()
{
    SetFlag(D, 0);
    return 0;
}

uint8_t CLI()
{
    SetFlag(I, 0);
    return 0;
}


uint8_t CLV()
{
    SetFlag(V, 0);
    return 0;
}

uint8_t ADC()
{
	uint16_t temp = (uint16_t)cpu.A + (uint16_t)memory.CPURAM[cpu.ABS] + (uint16_t)GetFlag(C);
	SetFlag(C, temp > 255);
	SetFlag(Z, (temp & 0x00FF) == 0);
	SetFlag(V, (~((uint16_t)cpu.A ^ (uint16_t)memory.CPURAM[cpu.ABS]) & ((uint16_t)cpu.A ^ (uint16_t)temp)) & 0x0080);
	SetFlag(N, temp & 0x80);
	cpu.A = temp & 0x00FF;
	return 1;
}

uint8_t SBC()
{
	uint16_t value = ((uint16_t)memory.CPURAM[cpu.ABS]) ^ 0x00FF;
	uint16_t temp = (uint16_t)cpu.A + value + (uint16_t)GetFlag(C);
	SetFlag(C, (uint8_t)temp & 0xFF00);
	SetFlag(Z, ((temp & 0x00FF) == 0));
	SetFlag(V, (temp ^ (uint16_t)cpu.A) & (temp ^ value) & 0x0080);
	SetFlag(N, temp & 0x0080);
	cpu.A = temp & 0x00FF;
	return 1;
}

uint8_t PHP()
{
    memory.CPURAM[0x100 + cpu.SP] = cpu.PS | B | U;
	SetFlag(B, 0);
	SetFlag(U, 0);
	cpu.SP--;
	return 0;
}

uint8_t PHA()
{
    memory.CPURAM[0x100 + cpu.SP] = cpu.A;
    cpu.SP--;
    return 0;
}

uint8_t PLA()
{
    cpu.SP++;
    cpu.A = memory.CPURAM[0x100 + cpu.SP];
    SetFlag(Z, cpu.A == 0x00);
    SetFlag(N, cpu.A & 0x80);
    return 0;
}

uint8_t PLP()
{
    cpu.SP++;
    cpu.PS = memory.CPURAM[0x100 + cpu.SP];
	SetFlag(U, 1);
	return 0;
}

uint8_t ASL(uint8_t IMP)
{
    uint16_t temp = memory.CPURAM[cpu.ABS] << 1;
    SetFlag(C, (temp & 0xFF00) > 0);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
    if (IMP==1)
    {
        cpu.A = temp & 0x00FF;
    }
	else
    {
        memory.CPURAM[cpu.ABS] = temp & 0x00FF;
    }
    return 0;
}

uint8_t BRK()
{
	cpu.PC++;
	SetFlag(I, 1);
	memory.CPURAM[0x0100 + cpu.SP] = (cpu.PC >> 8) & 0x00FF;
	cpu.SP--;
	memory.CPURAM[0x0100 + cpu.SP] = cpu.PC & 0x00FF;
	cpu.SP--;

	SetFlag(B, 1);
	memory.CPURAM[0x0100 + cpu.SP] = cpu.PS;
	cpu.SP--;
	SetFlag(B, 0);

	cpu.PC = (uint16_t)memory.CPURAM[0xFFFE] | ((uint16_t)memory.CPURAM[0xFFFF] << 8);
	return 0;
}

uint8_t CMP()
{
	uint16_t temp = (uint16_t)cpu.A - (uint16_t)memory.CPURAM[cpu.ABS];
	SetFlag(C, cpu.A >= memory.CPURAM[cpu.ABS]);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 1;
}

uint8_t CPX()
{
    uint16_t temp = (uint16_t)cpu.X - (uint16_t)memory.CPURAM[cpu.ABS];
	SetFlag(C, cpu.X >= memory.CPURAM[cpu.ABS]);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t CPY()
{
	uint16_t temp = (uint16_t)cpu.Y - (uint16_t)memory.CPURAM[cpu.ABS];
	SetFlag(C, cpu.Y >= memory.CPURAM[cpu.ABS]);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t DEC()
{
	uint16_t temp = memory.CPURAM[cpu.ABS] - 1;
	memory.CPURAM[cpu.ABS] = temp & 0x00FF;
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t DEX()
{
	cpu.X--;
	SetFlag(Z, cpu.X == 0x00);
	SetFlag(N, cpu.X & 0x80);
	return 0;
}

uint8_t DEY()
{
	cpu.Y--;
	SetFlag(Z, cpu.Y == 0x00);
	SetFlag(N, cpu.Y & 0x80);
	return 0;
}

uint8_t INC()
{;
	uint16_t temp = memory.CPURAM[cpu.ABS] + 1;
	memory.CPURAM[cpu.ABS] = temp & 0x00FF;
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t INX()
{
	cpu.X++;
	SetFlag(Z, cpu.X == 0x00);
	SetFlag(N, cpu.X & 0x80);
	return 0;
}

uint8_t INY()
{
	cpu.Y++;
	SetFlag(Z, cpu.Y == 0x00);
	SetFlag(N, cpu.Y & 0x80);
	return 0;
}

uint8_t JMP()
{
	cpu.PC = cpu.ABS;
	return 0;
}

uint8_t JSR()
{
	cpu.PC--;
	memory.CPURAM[0x0100 + cpu.SP] = (cpu.PC >> 8) & 0x00FF;
	cpu.SP--;
	memory.CPURAM[0x0100 + cpu.SP] = cpu.PC & 0x00FF;
	cpu.SP--;
	cpu.PC = cpu.ABS;
	return 0;
}

uint8_t LDA()
{
	cpu.A = memory.CPURAM[cpu.ABS];
	SetFlag(Z, cpu.A == 0x00);
	SetFlag(N, cpu.A & 0x80);
	return 1;
}

uint8_t LDX()
{
	cpu.X = memory.CPURAM[cpu.ABS];
	SetFlag(Z, cpu.X == 0x00);
	SetFlag(N, cpu.X & 0x80);
	return 1;
}

uint8_t LDY()
{
	cpu.Y = memory.CPURAM[cpu.ABS];
	SetFlag(Z, cpu.Y == 0x00);
	SetFlag(N, cpu.Y & 0x80);
	return 1;
}

uint8_t LSR(uint8_t imp)
{
	SetFlag(C, memory.CPURAM[cpu.ABS] & 0x0001);
	uint16_t temp = memory.CPURAM[cpu.ABS] >> 1;
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	if (imp)
    {
        cpu.A = temp & 0x00FF;
    }
	else
    {
        memory.CPURAM[cpu.ABS] = temp & 0x00FF;
    }
	return 0;
}

uint8_t EOR()
{
	cpu.A = cpu.A ^ memory.CPURAM[cpu.ABS];
	SetFlag(Z, cpu.A  == 0x00);
	SetFlag(N, cpu.A  & 0x80);
	return 1;
}

uint8_t ORA()
{
	cpu.A = cpu.A | memory.CPURAM[cpu.ABS];
	SetFlag(Z, cpu.A  == 0x00);
	SetFlag(N, cpu.A  & 0x80);
	return 1;
}

uint8_t ROL(uint8_t imp)
{
	uint16_t temp = (uint16_t)(memory.CPURAM[cpu.ABS] << 1) | GetFlag(C);
	SetFlag(C, temp & 0xFF00);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	if (imp)
    {
        cpu.A = temp & 0x00FF;
    }
	else
    {
        memory.CPURAM[cpu.ABS] = temp & 0x00FF;
    }
	return 0;
}

uint8_t ROR(uint8_t imp)
{
	uint16_t temp = (uint16_t)(GetFlag(C) << 7) | (memory.CPURAM[cpu.ABS] >> 1);
	SetFlag(C, memory.CPURAM[cpu.ABS] & 0x01);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x0080);
	if (imp)
    {
        cpu.A = temp & 0x00FF;
    }
	else
    {
        memory.CPURAM[cpu.ABS] = temp & 0x00FF;
    }
	return 0;
}

uint8_t RTI()
{
	cpu.SP++;
	cpu.PS = memory.CPURAM[0x0100 + cpu.SP];
	cpu.PS &= ~B;
	cpu.PS &= ~U;

	cpu.SP++;
	cpu.PC = (uint16_t)memory.CPURAM[0x0100 + cpu.SP];
	cpu.SP++;
	cpu.PC |= (uint16_t)memory.CPURAM[0x0100 + cpu.SP] << 8;
	return 0;
}

uint8_t RTS()
{
	cpu.SP++;
	cpu.PC = (uint16_t)memory.CPURAM[0x0100 + cpu.SP];
	cpu.SP++;
	cpu.PC |= (uint16_t)memory.CPURAM[0x0100 + cpu.SP] << 8;
	cpu.PC++;
	return 0;
}

uint8_t SEC()
{
	SetFlag(C, 1);
	return 0;
}

uint8_t SED()
{
	SetFlag(D, 1);
	return 0;
}

uint8_t SEI()
{
	SetFlag(I, 1);
	return 0;
}

uint8_t STA()
{
	memory.CPURAM[cpu.ABS] = cpu.A;
	return 0;
}

uint8_t STX()
{
	memory.CPURAM[cpu.ABS] = cpu.X;
	return 0;
}

uint8_t STY()
{
	memory.CPURAM[cpu.ABS] = cpu.Y;
	return 0;
}

uint8_t TAX()
{
	cpu.X = cpu.A;
	SetFlag(Z, cpu.X == 0x00);
	SetFlag(N, cpu.X & 0x80);
	return 0;
}

uint8_t TAY()
{
	cpu.Y = cpu.A;
	SetFlag(Z, cpu.Y == 0x00);
	SetFlag(N, cpu.Y & 0x80);
	return 0;
}

uint8_t TSX()
{
	cpu.X = cpu.SP;
	SetFlag(Z, cpu.X == 0x00);
	SetFlag(N, cpu.X & 0x80);
	return 0;
}

uint8_t TXA()
{
	cpu.A = cpu.X;
	SetFlag(Z, cpu.A == 0x00);
	SetFlag(N, cpu.A & 0x80);
	return 0;
}

uint8_t TXS()
{
	cpu.SP = cpu.X;
	return 0;
}

uint8_t TYA()
{
	cpu.A = cpu.Y;
	SetFlag(Z, cpu.A == 0x00);
	SetFlag(N, cpu.A & 0x80);
	return 0;
}

uint8_t NOP()
{
	return 0;
}

/* Fetches byte that is in the memory at where program counter is pointing to */
uint8_t FetchByte()
{
    uint8_t data = memory.CPURAM[cpu.PC];
    cpu.PC++;
    return data;
}
