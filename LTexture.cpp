#include <iostream>
#include "LTexture.h"

using namespace std;



LTexture::LTexture()
{
    gTexture = NULL;
}
LTexture::~LTexture()
{
    gTexture = NULL;
}
void LTexture::loadfromfile(SDL_Renderer* gRenderer, string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
        logError("Unable to load image %s! SDL_image Error:", IMG_ERROR);
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface );
        if(newTexture == NULL)
           // logError("Unable to create texture from %s! SDL Error:", SDL_ERROR);
        SDL_FreeSurface( loadedSurface );
    }
    gTexture = newTexture;
}
void LTexture::render(SDL_Renderer* gRenderer)
{
    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
}

void LTexture::free()
{
    //Free texture if it exists
	if( gTexture != NULL )
	{
		SDL_DestroyTexture( gTexture );
		gTexture = NULL;
	}
}

