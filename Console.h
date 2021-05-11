#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


using namespace std;
enum num_ERROR
{
    SDL_ERROR = 0,
    IMG_ERROR,
    TTF_ERROR,
    MIX_ERROR
};

//Log Error
void logError(const string &msg, int flag);


#endif // CONSOLE_H_
