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
    int x, y, w, h;
    LTexture();
    ~LTexture();
    void loadfromfile(SDL_Renderer* gRenderer, const string &path);
    void render(SDL_Renderer* gRenderer, const SDL_Rect &SRect, const SDL_Rect &DRect);
    void render(SDL_Renderer* gRenderer);
    void setsRect(int _x, int _y, int _w, int _h);
    void setdRect(int _x, int _y, int _w, int _h);
    void free();

private:

    SDL_Texture* mTexture;
};

#endif // LTEXTURE_H_
