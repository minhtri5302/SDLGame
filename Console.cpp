#include "Console.h"

void logError(const string &msg, int flag)
{
    cout << msg << " " ;
    switch(flag)
    {
        case SDL_ERROR:
            cout << SDL_GetError() << "\n";
            break;
        case IMG_ERROR:
            cout << IMG_GetError() << "\n";
            break;
        case MIX_ERROR:
            cout << Mix_GetError() << "\n";
            break;
        case TTF_ERROR:
            cout << TTF_GetError() << "\n";
            break;
    }
}
