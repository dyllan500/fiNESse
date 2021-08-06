#pragma once
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>
#include <SDL2/SDL.h>


void handleKeys();

void handleMouse();

void clock();

void updateFrame(uint32_t pixel[]);

void init();

void run();

#endif

