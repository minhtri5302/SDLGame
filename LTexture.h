#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Console.h"
using namespace std;


class LTexture
{
public:
    LTexture();
    ~LTexture();
    void loadfromfile(SDL_Renderer* gRenderer, string path);
    void render(SDL_Renderer* gRenderer);
    void free();
    SDL_Rect dRect;
private:
    SDL_Texture* gTexture;
};

#endif // LTEXTURE_H_
