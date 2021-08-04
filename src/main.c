#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "include/cpu.h"
#include "include/memory.h"

typedef unsigned char BYTE;
typedef unsigned short WORD;

int main(int argc, char *argv[])
{
    struct CPU cpu;
    struct MEMORY memory;
    InitialiseMemory(&memory);
    uint8_t array[28] = {0xA2, 0x0A, 0x8E, 0x00, 0x00, 0xA2, 0x03, 0x8E, 0x01, 0x00, 0xAC, 0x00, 0x00, 0xA9, 0x00, 0x18, 0x6D, 0x01, 0x00, 0x88, 0xD0, 0xFA, 0x8D, 0x02, 0x00, 0xEA, 0xEA, 0xEA};
    uint16_t nOffset = 0x8000;
    int x = 0;
    while (x<29)
    {
        memory.DATA[nOffset++] = array[x];
        x++;
    }

    // Set Reset Vector
    memory.DATA[0xFFFC] = 0x00;
    memory.DATA[0xFFFD] = 0x80;
    ResetCpu(&cpu, &memory);
    printf("PC: %d\n", cpu.PC);
    printf("DATA: %d\n", memory.DATA[1]);
    Clock(&cpu, &memory);
    printf("MEM: %d\n", memory.DATA[0x0002]);
    printf("END");
    return 0;
}
