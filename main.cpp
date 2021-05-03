// My SDL Game

//Include libraries
#include <bits/stdc++.h>
#include "LTexture.h"
#include "Console.h"

//Define
#define F first
#define S second
#define FOR(i, x, y) for(int i = x; i <= y; ++i)
#define FORN(i, x, y) for(int i = x; i >= y; --i)

using namespace std;
//Enum
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//Game Engine
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 550;
const string gametitle = "Đẩy Hình";

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


void init();
void loadmedia();
void render();
void close();

int n, cntMove;
//Texture
LTexture gTexture;
void RenderSmallPicture();
void MoveBlank(int addX, int addY);
bool CheckWin();

pair<int, int> curPos[10][10]; // Ô hiện tại của bức tranh (i,j) ;
pair<int, int> nowPos[10][10]; // Ô (i,j) hiện tại thuộc về bức tranh nào
int main(int argc, char* argv[])
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) curPos[i][j] = {i, j}, nowPos[i][j] = {i, j};
    init();
    bool quit = false;
    SDL_Event e;
    loadmedia();
    RenderSmallPicture();
    render();
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        if(curPos[n][n].S > 1)
                            MoveBlank(0, -1);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        if(curPos[n][n].S < n)
                            MoveBlank(0, 1);
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        if(curPos[n][n].F > 1)
                            MoveBlank(-1, 0);
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        if(curPos[n][n].F < n)
                            MoveBlank(1, 0);
                        break;
                    }
                }
            }
        }
        SDL_RenderClear(gRenderer);
        RenderSmallPicture();
        render();
        if(CheckWin()) cout << 1 << " ";
    }
    gTexture.free();
    close();
}

bool CheckWin()
{
    FOR(i, 1, n)
        FOR(j, 1, n) if(curPos[i][j]!=make_pair(i, j)) return 0;
    return 1;
}

void MoveBlank(int addX, int addY)
{
    pair<int, int> &Blank = curPos[n][n];
    pair<int, int> temp1 = nowPos[Blank.F+addX][Blank.S+addY];
    pair<int, int> temp2 = curPos[temp1.F][temp1.S];
    pair<int, int> temp3 = Blank;
    pair<int, int> temp4 = {n, n};
    curPos[temp1.F][temp1.S] = temp3;
    nowPos[temp3.F][temp3.S] = temp1;
    Blank = temp2;
    nowPos[Blank.F][Blank.S] = temp4;
    cntMove++;
}

void RenderSmallPicture()
{
    int kt = 480/n;
    int kc = 2;
    int XPos = 1, YPos = 1;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
        {
            if(i == n && j == n) continue;
            SDL_Rect SRect, DRect;
            SRect.x = (i-1) * kt + 1;
            SRect.y = (j-1) * kt + 1;
            SRect.w = kt;
            SRect.h = kt;

            DRect.x = XPos + (curPos[i][j].F-1) * (kt + kc);
            DRect.y = YPos + (curPos[i][j].S-1) * (kt + kc);
            DRect.w = DRect.h = kt;
            gTexture.render(gRenderer, SRect, DRect);
        }
}
void loadmedia()
{
    gTexture.loadfromfile(gRenderer, "image/image1.jpg");
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
