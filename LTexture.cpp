#include <iostream>
#include "LTexture.h"

using namespace std;



LTexture::LTexture()
{
    this->mTexture = NULL;
}
LTexture::LTexture(SDL_Rect _sRect, SDL_Rect _dRect)
{
    this->mTexture = NULL;
    this->sRect = sRect;
    this->dRect = dRect;
}
LTexture::~LTexture()
{
    this->mTexture = NULL;
}
void LTexture::loadfromfile(SDL_Renderer* gRenderer, const string &path)
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
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
           // logError("Unable to create texture from %s! SDL Error:", SDL_ERROR);
        SDL_FreeSurface( loadedSurface );
    }
    this->mTexture = newTexture;
}
void LTexture::render(SDL_Renderer* gRenderer, const SDL_Rect &SRect, const SDL_Rect &DRect)
{
    SDL_RenderCopy(gRenderer, this->mTexture, &SRect, &DRect);
}
void LTexture::render(SDL_Renderer* gRenderer)
{
    SDL_RenderCopy(gRenderer, this->mTexture, &(this->sRect), &(this->dRect));
}

void LTexture::free()
{
    //Free texture if it exists
	if( this->mTexture != NULL )
	{
		SDL_DestroyTexture( this->mTexture );
		this->mTexture = NULL;
	}
}

