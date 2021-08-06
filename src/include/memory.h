#pragma once
#ifndef __MEMORY_H__
#define __MEMORY_H__
#include "cpu.h"
#include <stdint.h>

#define MAX_CPU_MEMORY 1024*64
#define MAX_PPU_MEMORY 1024*16

struct MEMORY
{
    uint8_t CPURAM[MAX_CPU_MEMORY];
    uint8_t PPURAM[MAX_PPU_MEMORY];
};
typedef struct MEMORY MEMORY;

extern MEMORY memory;

void InitialiseMemory();

#endif
