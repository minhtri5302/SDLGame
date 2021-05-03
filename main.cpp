// My SDL Game
#include <bits/stdc++.h>
#include "LTexture.h"
#include "Console.h"
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const string gametitle = "mygame";

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void init();
void render();
void close();
LTexture test;
int main(int argc, char* argv[])
{
    init();
    bool quit = false;
    SDL_Event e;
    test.loadfromfile(gRenderer, "image/hello_world.bmp");
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        test.render(gRenderer);
        render();
    }
    test.free();
    close();
}
void init()
 {
    //Initialize SDL
    if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
        logError("SDL_Init", SDL_ERROR);

    //Create Window
    gWindow = SDL_CreateWindow(gametitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(gWindow == NULL)
        logError("CreateWindow", SDL_ERROR);

    //Create renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL)
        logError("CreateRenderer", SDL_ERROR);

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init( imgFlags ) & imgFlags))
        logError("SDL Init", IMG_ERROR);

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
        logError("TTF Init", TTF_ERROR);

    //Initialize SDL_mixer


 }

 void render()
 {
     //SDL_RenderClear(gRenderer);

     SDL_RenderPresent(gRenderer);
 }

 void close()
 {
    //Free music

    //Free Font

    //Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

    //Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
 }
