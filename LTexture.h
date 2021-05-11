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
    SDL_Rect sRect;
    SDL_Rect dRect;
    LTexture();
    LTexture(SDL_Rect _sRect, SDL_Rect _dRect);
    ~LTexture();
    void loadfromfile(SDL_Renderer* gRenderer, const string &path);
    void render(SDL_Renderer* gRenderer, const SDL_Rect &SRect, const SDL_Rect &DRect);
    void render(SDL_Renderer* gRenderer);
    void free();

private:
    SDL_Texture* mTexture;
};

#endif // LTEXTURE_H_
