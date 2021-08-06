#include "include/cartridge.h"
#include "include/memory.h"
#include <stdio.h>

CARTRIDGE cartridge;

void InsertCart()
{
    struct HEADER header;
    FILE *fp = NULL;
    uint8_t buff[16];
    fp = fopen(cartridge.filename , "r");
    if(fp != NULL)
    {
        //Load header of ROM file
        int x = 0;
        while(x<16)
        {
            buff[x] = fgetc((FILE*)fp);
            x++;
        }

        //NES file Constants
        header.nesConstant[0] = (char)buff[0];
        header.nesConstant[1] = (char)buff[1];
        header.nesConstant[2] = (char)buff[2];
        header.nesConstant[3] = (char)buff[3];

        //NES file header info
        header.PRGROMSize = buff[4];
        header.CHRROMSize = buff[5];
        header.trainer = buff[6];
        header.mapper = buff[7];
        header.PRGRAMSize = buff[8];
        header.tv1 = buff[9];
        header.tv2 = buff[10];

        //NES file header used bytes
        header.unused[0] = (char)buff[11];
        header.unused[1] = (char)buff[12];
        header.unused[2] = (char)buff[13];
        header.unused[3] = (char)buff[14];
        header.unused[4] = (char)buff[15];

        //Skip trainer
        if (header.trainer & 0x04)
        {
            x = 0;
            while(x<513)
            {
                fgetc((FILE*)fp);
                x++;
            }
        }

		cartridge.mapperID = ((header.mapper >> 4) << 4) | (header.trainer >> 4);
		cartridge.mirror = (header.trainer & 0x01) ? VERTICAL : HORIZONTAL;

		uint8_t fileType = 1;
		if (fileType == 0)
		{

		}
		if (fileType == 1)
		{
			cartridge.PRGSize = header.PRGROMSize;
            x = 0;
            while(x<(16384*cartridge.PRGSize)+1)
            {
                cartridge.PRGMemory[x] = fgetc((FILE*)fp);
                x++;
            }

			cartridge.CHRSize = header.CHRROMSize;
            x = 0;
            while(x<(8192*cartridge.CHRSize)+1)
            {
                cartridge.CHRMemory[x] = fgetc((FILE*)fp);
                x++;
            }
		}
		if (fileType == 2)
		{

		}
        uint32_t index = 0x0000;
		switch (cartridge.mapperID)
		{
            case 0:
                index = 0x8000;
                if(cartridge.PRGSize == 1)
                {
                    x = 0;
                    while(index < 0xC000)
                    {
                        memory.CPURAM[index] = cartridge.PRGMemory[x];
                        memory.CPURAM[index+16385] = cartridge.PRGMemory[x];
                        index++;
                        x++;
                    }
                }
                else
                {
                    x = 0;
                    while(index <= 0xFFFF)
                    {
                        memory.CPURAM[index] = cartridge.PRGMemory[x];
                        index++;
                        x++;
                    }
                }
                x = 0;
                index = 0;
                while(index < (8192*cartridge.CHRSize)+1)
                {
                    memory.PPURAM[index] = cartridge.CHRMemory[x];
                    index++;
                    x++;
                }
                break;
		}
        fclose(fp);
    }
}
