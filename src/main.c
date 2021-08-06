#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "include/cpu.h"
#include "include/ppu.h"
#include "include/memory.h"
#include "include/cartridge.h"
#include "include/display.h"

int main(int argc, char *argv[])
{
    cartridge.filename = argv[1];
    init();
    run();
    return EXIT_SUCCESS;
}
