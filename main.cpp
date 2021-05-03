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
const string OldInfoFile = "OldInfoSys.txt";
fstream fio;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


void init();
void loadmedia(const string &path);
void render();
void close();

//Khai báo
int n, cntMove;
int highscore[10];
int MinMove[10];
pair<int, int> SavePos[10][10][10]; // Dữ liệu cũ;
string SavePicture[10]; //Đường dẫn ảnh cũ
pair<int, int> curPos[10][10][10]; // Ô hiện tại của bức tranh (i,j) ;
pair<int, int> nowPos[10][10][10]; // Ô (i,j) hiện tại thuộc về bức tranh nào

//Texture
LTexture gTexture;

//Game Loop
int Rand(int Minn, int Maxx);
void RenderSmallPicture();
void MoveBlank(int addX, int addY);
bool CheckWin();
void ResetGame(int option);
void ResetMap(int option);
void InitMap(int option);
string RandPicture();
void ReadOldInfo();
void WriteOldInfo();


int main(int argc, char* argv[])
{
    srand(time(NULL));

    ReadOldInfo();

    n = 3;
    InitMap(n);
    init();
    bool quit = false;
    SDL_Event e;
    loadmedia(SavePicture[n]);
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

                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        if(curPos[n][n][n].S > 1)
                            MoveBlank(0, -1);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        if(curPos[n][n][n].S < n)
                            MoveBlank(0, 1);
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        if(curPos[n][n][n].F > 1)
                            MoveBlank(-1, 0);
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        if(curPos[n][n][n].F < n)
                            MoveBlank(1, 0);
                        break;
                    }
                }
            }
        }
        SDL_RenderClear(gRenderer);
        RenderSmallPicture();
        render();
        //if(CheckWin()) cout << 1 << " ";
    }
    gTexture.free();
    close();
    WriteOldInfo();
}
void ReadOldInfo()
{
    fio.open(OldInfoFile, ios::in);
    if(1)
    {
        FOR(x, 3, 6)
        {
            fio >> highscore[x];
            fio >> SavePicture[x];
            fio >> MinMove[x];
            FOR(i, 1, x)
            FOR(j, 1, x) fio >> SavePos[x][i][j].F >> SavePos[x][i][j].S;
        }
    }
    else FOR(x, 3, 6) ResetMap(x);
    fio.close();
}
void WriteOldInfo()
{
    fio.open(OldInfoFile, ios::out);
    FOR(x, 3, 6)
    {
        fio << highscore[x] << "\n";
        fio << SavePicture[x] << "\n";
        fio << MinMove[x] << "\n";
        FOR(i, 1, x)
        {
            FOR(j, 1, x) fio << SavePos[x][i][j].F << " " << SavePos[x][i][j].S << " ";
            fio << "\n";
        }
    }
    fio.close();
}
string RandPicture()
{
    int id = Rand(1, 19);
    string newid = to_string(id);
    string image_newid = "image/image" + newid + ".jpg";
    return image_newid;
}
void InitMap(int option)
{
    FOR(i, 1, option)
        FOR(j, 1, option) curPos[option][i][j] = nowPos[option][i][j] =  SavePos[option][i][j] ;
    cntMove = 0;
}
void ResetMap(int option)
{
    int op = option;
    //Lấy ngẫu nhiên 1 trạng thái Map
    //MinMove = ;
    FOR(i, 1, option)
        FOR(j, 1, option) SavePos[option][i][j] = {i, j};

    //Đặt lại vị trí các ô theo Map mới và lưu lại dữ liệu
    FOR(i, 1, option)
        FOR(j, 1, option) curPos[option][i][j] = nowPos[option][i][j] =  SavePos[option][i][j];


    //Reset các thông số.
    highscore[option] = 0;
    cntMove = 0;

    //Map
    SavePicture[option] = RandPicture();

}
void ResetGame(int option)
{
    FOR(i, 1, option)
        FOR(j, 1, option) curPos[option][i][j] = nowPos[option][i][j] =  SavePos[option][i][j];
    cntMove = 0;
}
int Rand(int Minn, int Maxx)
{
    return rand() % (Maxx - Minn + 1) + Minn;
}

bool CheckWin()
{
    FOR(i, 1, n)
        FOR(j, 1, n) if(curPos[n][i][j]!=make_pair(i, j)) return 0;
    return 1;
}

void MoveBlank(int addX, int addY)
{
    pair<int, int> &Blank = curPos[n][n][n];
    pair<int, int> temp1 = nowPos[n][Blank.F+addX][Blank.S+addY];
    pair<int, int> temp2 = curPos[n][temp1.F][temp1.S];
    pair<int, int> temp3 = Blank;
    pair<int, int> temp4 = {n, n};
    curPos[n][temp1.F][temp1.S] = temp3;
    nowPos[n][temp3.F][temp3.S] = temp1;
    Blank = temp2;
    nowPos[n][Blank.F][Blank.S] = temp4;
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

            DRect.x = XPos + (curPos[n][i][j].F-1) * (kt + kc);
            DRect.y = YPos + (curPos[n][i][j].S-1) * (kt + kc);
            DRect.w = DRect.h = kt;
            gTexture.render(gRenderer, SRect, DRect);
        }
}
void loadmedia(const string &path)
{
    gTexture.loadfromfile(gRenderer, path);
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
