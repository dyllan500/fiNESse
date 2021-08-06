#include "include/memory.h"

MEMORY memory;

void InitialiseMemory()
{
    for(__int32_t i = 0; i < MAX_CPU_MEMORY; i++)
    {
        memory.CPURAM[i] = 0x00;
    }
    //for(__int32_t i = 0; i < MAX_PPU_MEMORY; i++)
    //{
     //   memory->PPURAM[i] = 0x00;
    //}
}
