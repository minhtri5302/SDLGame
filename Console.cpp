#include "Console.h"

void logError(const string &msg, int flag)
{
    cerr << msg << " " ;
    switch(flag)
    {
        case SDL_ERROR:
            cerr << SDL_GetError() << "\n";
            break;
        case IMG_ERROR:
            cerr << IMG_GetError() << "\n";
            break;
        case MIX_ERROR:
            cerr << Mix_GetError() << "\n";
            break;
        case TTF_ERROR:
            cerr << TTF_GetError() << "\n";
            break;
    }
    exit(1);
}
