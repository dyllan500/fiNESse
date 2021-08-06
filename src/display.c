#include "include/display.h"
#include "include/cpu.h"
#include "include/ppu.h"
#include "include/memory.h"
#include "include/cartridge.h"

#define BUTTON_NONE 0
#define BUTTON_DOWN 1
#define BUTTON_UP 2
Uint8 KEYS[1073742106];
Uint8 MOUSE[10];
const unsigned WIDTH  = 256;
const unsigned HEIGHT = 240;
int nSystemClockCounter = 0;
SDL_Texture* gameTexture  = NULL;
SDL_Window *window  = NULL;
SDL_Renderer *renderer = NULL;
int isRunning = 0;
int fullscreen = 0;
const int FPS = 60;
const int frameDelay = 1000.0f / FPS;
Uint32 frameStart;
Uint32 frameTime;
SDL_Event event;

void handleKeys()
{

}

void handleMouse()
{
}

void clock()
{
    PPUClock();
	if (nSystemClockCounter % 3 == 0)
	{
        CPUClock();
	}
	nSystemClockCounter++;
}

void updateFrame(uint32_t pixel[])
{
    SDL_UpdateTexture(gameTexture, NULL, pixel, WIDTH * sizeof(uint32_t));
}

void init()
{
    InitialiseMemory();
    InsertCart();
    ResetCpu();
    InitPPU();

    int flags = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow("Game Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, flags);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        isRunning = 1;
    }
    gameTexture = SDL_CreateTexture (renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}


void run()
{
    while (isRunning)
    {
        frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    isRunning = 0;
                    break;
                case SDL_KEYDOWN:
                    KEYS[event.key.keysym.sym] = BUTTON_DOWN;
                    break;
                case SDL_KEYUP:
                    KEYS[event.key.keysym.sym] = BUTTON_UP;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    MOUSE[event.button.button] = BUTTON_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    MOUSE[event.button.button] = BUTTON_UP;
                    break;
            }
            //handleKeys(cpu, memory);
            //handleMouse();
        }
        //UPDATE GAME
        do { clock(); } while (!frame_complete);
        SDL_UpdateTexture(gameTexture, NULL, pixels, WIDTH * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameTexture, NULL, NULL);
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay)
        {
            SDL_Delay((int)(frameDelay - frameTime));
        }
        fflush(stdout);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(gameTexture);
}
