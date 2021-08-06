#pragma once
#ifndef __CARTRIDGE_H__
#define __CARTRIDGE_H__
#include <stdint.h>
#include "memory.h"

enum MIRROR
{
    HORIZONTAL,
    VERTICAL,
    ONESCREEN_LO,
    ONESCREEN_HI,
};


struct CARTRIDGE
{
    char *filename;                 //ROM FileName
    uint8_t mapperID;               //mapper id
	uint8_t PRGSize;                //size of multiplier for prg memory
	uint8_t CHRSize;                //size of multiplier for chr memory
    uint8_t PRGMemory[255*16384];   //prg memory
    uint8_t CHRMemory[255*8192];    //chr memory
    enum MIRROR mirror;             //screen mirror
    uint32_t mapper;                //mapper struct id
};

typedef struct CARTRIDGE CARTRIDGE;
extern CARTRIDGE cartridge;

struct HEADER
{
    char nesConstant[4];     //0-3: Constant $4E $45 $53 $1A ("NES" followed by MS-DOS end-of-file)
    uint8_t PRGROMSize;  //4: Size of PRG ROM in 16 KB units
    uint8_t CHRROMSize;  //5: Size of CHR ROM in 8 KB units (Value 0 means the board uses CHR RAM)
    uint8_t trainer;         //6: Flags 6 - Mapper, mirroring, battery, trainer
    uint8_t mapper;         //7: Flags 7 - Mapper, VS/Playchoice, NES 2.0
    uint8_t PRGRAMSize;    //8: Flags 8 - PRG-RAM size (rarely used extension)
    uint8_t tv1;      //9: Flags 9 - TV system (rarely used extension)
    uint8_t tv2;      //10: Flags 10 - TV system, PRG-RAM presence (unofficial, rarely used extension)
    char unused[5];          //11-15: Unused padding (should be filled with zero, but some rippers put their name across bytes 7-15)
};

void InsertCart();

#endif
