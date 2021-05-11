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
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
using namespace std;


//Game Engine
const int SCREEN_WIDTH = 842;
const int SCREEN_HEIGHT = 587;
const string gametitle = "Đẩy Hình";
const string OldInfoFile = "OldInfoSys.txt";
const string Backgroundimage="image/GameBack.png";
const string Backgameimage3="image/Back3x3.png";
const string Backgameimage4="image/Back4x4.png";
const string Backgameimage5="image/Back5x5.png";
const string Backgameimage6="image/Back6x6.png";

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void init();
void render();
void close();
SDL_Rect CreateRect(int x, int y, int w, int h);

//Khai báo
int n = 3, cntMove;
int highscore[7];
int MinMove[7], cntOption[7];
pair<int, int> SavePos[7][7][7]; // Dữ liệu cũ;
string SavePicture[7]; //Đường dẫn ảnh cũ
pair<int, int> curPos[7][7][7]; // Ô hiện tại của bức tranh (i,j) ;
pair<int, int> nowPos[7][7][7]; // Ô (i,j) hiện tại thuộc về bức tranh nào

//Biến để tạo map
map<vector<pii>, int> mm[7];
vector<vector<pii>> Data[7];
vector<pii> State1;
int cnt;
int dState[7][10000000];
int times = 10;

//Texture
LTexture Background;
LTexture gTexture[7];
LTexture BackGame[7];

void getAllTexture();

//Game Loop
int Rand(int Minn, int Maxx);
void RenderSmallPicture(int option);
void MoveBlank(int option, int addX, int addY);
bool CheckWin(int option);
void ResetGame(int option);
void ResetMap(int option);
void InitMap(int option);
string RandPicture();
void ReadOldInfo();
void WriteOldInfo();
void CreateData(int option);
void MakeState(int &option, int idState, int &posswap, queue<int> &q, vector<pii> &curState);
void RandStateMap();

int main(int argc, char* argv[])
{
    srand(time(NULL));


    RandStateMap();
    ReadOldInfo();

    init();
    getAllTexture();

    InitMap(n);

    bool quit = false;
    SDL_Event e;
    RenderSmallPicture(n);
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
                        if(curPos[n][n][n].S < n)
                            MoveBlank(n, 0, 1);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        if(curPos[n][n][n].S > 1)
                            MoveBlank(n, 0, -1);
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        if(curPos[n][n][n].F < n)
                            MoveBlank(n, 1, 0);
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        if(curPos[n][n][n].F > 1)
                            MoveBlank(n, -1, 0);
                        break;
                    }
                }
            }
        }
        SDL_RenderClear(gRenderer);
        RenderSmallPicture(n);
        render();
    }

    if(highscore[n] == 0) highscore[n] = cntMove;
        else highscore[n] = min(highscore[n], cntMove);

    close();
    WriteOldInfo();
}
void getAllTexture()
{
     Background.loadfromfile(gRenderer, Backgroundimage);

     BackGame[3].loadfromfile(gRenderer, Backgameimage3);
     BackGame[4].loadfromfile(gRenderer, Backgameimage4);
     BackGame[5].loadfromfile(gRenderer, Backgameimage5);
     BackGame[6].loadfromfile(gRenderer, Backgameimage6);

     gTexture[3].loadfromfile(gRenderer, SavePicture[3]);
     gTexture[4].loadfromfile(gRenderer, SavePicture[4]);
     gTexture[5].loadfromfile(gRenderer, SavePicture[5]);
     gTexture[6].loadfromfile(gRenderer, SavePicture[6]);
}
SDL_Rect CreateRect(int x, int y, int w, int h)
{
    SDL_Rect temp;
    temp.x = x;
    temp.y = y;
    temp.w = w;
    temp.h = h;
    return temp;
}
void RandStateMap()
{
    FOR(i, 3, 6) CreateData(i);
}
void MakeState(int &option, int idState, int &posswap, queue<int> &q, vector<pii> &curState)
{
    swap(curState[posswap], curState[option*option-1]);
    if(mm[option][curState]==0)
    {
        mm[option][curState] = ++cnt;
        Data[option].pb(curState);
        q.push(cnt);
        dState[option][cnt] = dState[option][idState] + 1;
    }
    swap(curState[posswap], curState[option*option-1]);
}
void CreateData(int option)
{
    cnt = 1;
    State1.clear();
    FOR(i, 1, option)
        FOR(j, 1, option)
        {
            pii temp = {i, j};
            State1.pb(temp);
        }
    mm[option][State1] = 1;
    dState[option][cnt]= 0;
    Data[option].pb(State1);
    queue<int> q;
    q.push(mm[option][State1]);
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        if(dState[option][x] > times) continue;
        vector<pii> curState = Data[option][x-1];
        pii blank = curState[option*option-1];
        pii left, right, up, down;
        int pleft=-1, pright=-1, pup=-1, pdown=-1;
        FOR(i, 0, option*option-2)
        {
            auto v = curState[i];
            if(blank.F > 1 && v.F == blank.F-1 && v.S == blank.S)
                left = v, pleft = i;
            if(blank.S > 1 && v.F == blank.F && v.S == blank.S-1)
                up = v, pup = i;
            if(blank.F < option && v.F == blank.F+1 && v.S == blank.S)
                right = v, pright = i;
            if(blank.S < option && v.F == blank.F && v.S == blank.S+1)
                down = v, pdown = i;
        }
        if(blank.F > 1) MakeState(option, x, pleft, q, curState);
        if(blank.S > 1) MakeState(option, x, pup, q, curState);
        if(blank.F < option) MakeState(option, x, pright, q, curState);
        if(blank.S < option) MakeState(option, x, pdown, q, curState);
    }
    cntOption[option] = cnt;
}
void ReadOldInfo()
{
    freopen(OldInfoFile.c_str(),"r", stdin);
    bool ok = 0;
    cin >> ok;
    if(ok)
    {
        FOR(x, 3, 6)
        {
            cin >> highscore[x];
            cin >> SavePicture[x];
            cin >> MinMove[x];
            FOR(i, 1, x)
                FOR(j, 1, x) cin >> SavePos[x][i][j].F >> SavePos[x][i][j].S;
        }
    }
    else FOR(x, 3, 6) ResetMap(x);
}
void WriteOldInfo()
{
    freopen(OldInfoFile.c_str(),"w", stdout);
    cout << 1 << "\n";
    FOR(x, 3, 6)
    {
        cout << highscore[x] << "\n";
        cout << SavePicture[x] << "\n";
        cout << MinMove[x] << "\n";
        FOR(i, 1, x)
        {
            FOR(j, 1, x) cout << SavePos[x][i][j].F << " " << SavePos[x][i][j].S << " ";
            cout << "\n";
        }
    }
}
string RandPicture()
{
    //int id = Rand(1, 4);
    int id = 1;
    string newid = to_string(id);
    string image_newid = "image/image" + newid + ".jpg";
    return image_newid;
}
void InitMap(int option)
{
    FOR(i, 1, option)
        FOR(j, 1, option)
        {
            curPos[option][i][j] =  SavePos[option][i][j];
            pii temp = curPos[option][i][j];
            nowPos[option][temp.F][temp.S] = {i, j};
        }
    cntMove = 0;
}
void ResetMap(int option)
{
    //Lấy ngẫu nhiên 1 trạng thái Map
    int curMap = Rand(2, cntOption[option]);
    vector<pii> curState = Data[option][curMap-1];
    FOR(i, 1, option)
        FOR(j, 1, option)
        {
            int id = (i-1)*option+j-1;
            SavePos[option][i][j] = {curState[id].F, curState[id].S};
        }
    MinMove[option] = dState[option][curMap];

    //Đặt lại vị trí các ô theo Map mới và lưu lại dữ liệu
    FOR(i, 1, option)
        FOR(j, 1, option)
        {
            curPos[option][i][j] =  SavePos[option][i][j];
            pii temp = curPos[option][i][j];
            nowPos[option][temp.F][temp.S] = {i, j};
        }

    //Reset các thông số.
    highscore[option] = 0;
    cntMove = 0;

    //Map
    SavePicture[option] = RandPicture();

}
void ResetGame(int option)
{
    FOR(i, 1, option)
        FOR(j, 1, option)
        {
            curPos[option][i][j] =  SavePos[option][i][j];
            pii temp = curPos[option][i][j];
            nowPos[option][temp.F][temp.S] = {i, j};
        }
    cntMove = 0;
}
int Rand(int Minn, int Maxx)
{
    return rand() % (Maxx - Minn + 1) + Minn;
}

bool CheckWin(int option)
{
    FOR(i, 1, option)
        FOR(j, 1, option) if(curPos[option][i][j]!=make_pair(i, j)) return 0;
    return 1;
}

void MoveBlank(int option, int addX, int addY)
{
    pair<int, int> &Blank = curPos[option][option][option];
    pair<int, int> temp1 = nowPos[option][Blank.F+addX][Blank.S+addY];
    pair<int, int> temp2 = curPos[option][temp1.F][temp1.S];
    pair<int, int> temp3 = Blank;
    pair<int, int> temp4 = {option, option};
    curPos[option][temp1.F][temp1.S] = temp3;
    nowPos[option][temp3.F][temp3.S] = temp1;
    Blank = temp2;
    nowPos[option][Blank.F][Blank.S] = temp4;
    cntMove++;
}

void RenderSmallPicture(int option)
{
    SDL_Rect SRect1, DRect1;
    DRect1.x = 0;
    DRect1.y = 0;
    DRect1.w= 842;
    DRect1.h= 587;
    SRect1 = DRect1;
    Background.render(gRenderer, SRect1, DRect1);
    DRect1.x = 3;
    DRect1.y = 3;
    DRect1.w = 556;
    DRect1.h = 581;
    SRect1 = DRect1;
    SRect1.x = 0;
    SRect1.y = 0;
    BackGame[option].render(gRenderer, SRect1, DRect1);
    int kt = 480/option;
    int kc = 2;
    int XPos = 39, YPos = 39;
    for(int i = 1; i <= option; ++i)
        for(int j = 1; j <= option; ++j)
        {
            if(i == option && j == option) continue;
            SDL_Rect SRect, DRect;
            SRect.x = (i-1) * kt + 1;
            SRect.y = (j-1) * kt + 1;
            SRect.w = kt;
            SRect.h = kt;

            DRect.x = XPos + (curPos[option][i][j].F-1) * (kt + kc);
            DRect.y = YPos + (curPos[option][i][j].S-1) * (kt + kc);
            DRect.w = DRect.h = kt;
            gTexture[option].render(gRenderer, SRect, DRect);
        }
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

    //Free Texture
    Background.free();

    BackGame[3].free();
    BackGame[4].free();
    BackGame[5].free();
    BackGame[6].free();

    gTexture[3].free();
    gTexture[4].free();
    gTexture[5].free();
    gTexture[6].free();

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


