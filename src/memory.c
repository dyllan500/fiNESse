#include "include/memory.h"

void InitialiseMemory(struct MEMORY *memory)
{
    for(__int32_t i = 0; i < MAX_MEMORY; i++)
    {
        memory->DATA[i] = 0x00;
    }
}

/* Write 2 bytes */
void WriteWord(__int32_t cycles, uint16_t value, __int32_t address, struct MEMORY *memory)
{
    memory->DATA[address] = value & 0xFF;
    cycles --;
    memory->DATA[address+1] = (value >> 8);
    cycles--;
}
