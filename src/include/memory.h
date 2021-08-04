#ifndef __MEMORY_H__
#define __MEMORY_H__
#include "cpu.h"
#include <stdint.h>

#define MAX_MEMORY 1024*64

struct MEMORY
{
    uint8_t DATA[MAX_MEMORY];
};

void InitialiseMemory(struct MEMORY *memory);

/* Write 2 bytes */
void WriteWord(__int32_t cycles, uint16_t value, __int32_t address, struct MEMORY *memory);

#endif
