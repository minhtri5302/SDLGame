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

//Game Back Image Direction
const string Backgroundimage="system_image/GameBack.png";
const string Backgameimage3="system_image/Back3x3.png";
const string Backgameimage4="system_image/Back4x4.png";
const string Backgameimage5="system_image/Back5x5.png";
const string Backgameimage6="system_image/Back6x6.png";
const string Backwingameimage ="system_image/WinGameBack.png";
const string Backoptionimage ="system_image/OptionBack.png";
const string Backmenuimage = "system_image/MenuBack.png";
const string Backdemoimage = "system_image/PictureBack.png";
const string Backbeforegameimage = "system_image/BeforeGameBack.png";
//Button Image Direction
const string Playbuttonimage = "system_image/PlayButton.png";
const string Exitbuttonimage = "system_image/ExitButton.png";
const string Resetbuttonimage = "system_image/ResetButton.png";
const string Newbuttonimage = "system_image/NewButton.png";
const string Menubuttonimage = "system_image/MenuButton.png";
const string Lookbackbuttonimage = "system_image/LookBackButton.png";
const string Button3x3image = "system_image/3x3Button.png";
const string Button4x4image = "system_image/4x4Button.png";
const string Button5x5image = "system_image/5x5Button.png";
const string Button6x6image = "system_image/6x6Button.png";

//Number
const string Numberimage = "system_image/Number.png";

//SDL
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void init();
void close();

//Declare
int cntMove;
int highscore[7];
int MinMove[7], cntOption[7];
pair<int, int> SavePos[7][7][7]; // Dữ liệu cũ;
string SavePicture[7]; //Đường dẫn ảnh cũ
pair<int, int> curPos[7][7][7]; // Ô hiện tại của bức tranh (i,j) ;
pair<int, int> nowPos[7][7][7]; // Ô (i,j) hiện tại thuộc về bức tranh nào

//Var to Creat Map
map<vector<pii>, int> mm[7];
vector<vector<pii>> Data[7];
vector<pii> State1;
int cnt;
int dState[7][10000000];
int times = 10;

//Texture manage
LTexture Background;
LTexture gTexture[7];
LTexture BackGame[7];
LTexture BackWinGame;
LTexture BackOption;
LTexture BackMenu;
LTexture BackDemo;
LTexture BackBeforeGame;


LTexture PlayButton;
LTexture _PlayButton;

LTexture ExitButton;
LTexture _ExitButton;

LTexture ResetButton1;
LTexture _ResetButton1;

LTexture ResetButton2;
LTexture _ResetButton2;

LTexture NewButton1;
LTexture _NewButton1;

LTexture NewButton2;
LTexture _NewButton2;

LTexture MenuButton1;
LTexture _MenuButton1;

LTexture MenuButton2;
LTexture _MenuButton2;

LTexture LookBackButton;
LTexture _LookBackButton;

LTexture ButtonOption[7];
LTexture _ButtonOption[7];

LTexture Number;

void getAllTexture();
void setUpTexture();


//Game function
void waitGameMenu();
void waitOption();
void FullPictureDemo(int option);
void waitGamePlay(int option);
void waitGameOver(int option);

bool inside(int x, int y, LTexture &Button);
void RenderSmallPicture(int option);
void MoveBlank(int option, int addX, int addY);
bool CheckWin(int option);
void ResetGame(int option);
void ResetMap(int option);
void InitMap(int option);
void RenderNumber(int option, int kind);

//Rand Function
int Rand(int Minn, int Maxx);
string RandPicture();

//Read and Write Old Info
void ReadOldInfo();
void WriteOldInfo();

//Creat Map by BFS and Save
void RandStateMap();
void CreateData(int option);
void MakeState(int &option, int idState, int &posswap, queue<int> &q, vector<pii> &curState);


int main(int argc, char* argv[])
{
    srand(time(NULL));

    //Tạo map bằng BFS
    RandStateMap();

    //Read Old Info
    ReadOldInfo();

    //Init Game
    init();
    getAllTexture();
    setUpTexture();

    //Game loop
    while(1)
        waitGameMenu();

    //Free Objects
    close();

    //Write Old Info
    WriteOldInfo();
}
bool inside(int x, int y, LTexture &Button)
{
    if(x >= Button.x && x <= Button.x + Button.w - 1 &&
       y >= Button.y && y <= Button.y + Button.h - 1) return 1;
    return 0;
}
void waitGameMenu()
{
    BackMenu.render(gRenderer);
    SDL_RenderPresent(gRenderer);

    SDL_Event e;
    int touchStatus = 0;
    while(1)
    {
        if(SDL_WaitEvent(&e) == 0) continue;
        if(e.type == SDL_QUIT) exit(0);
        if(e.type == SDL_MOUSEMOTION)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(inside(x, y, PlayButton) && touchStatus != 1)
            {
                BackMenu.render(gRenderer);
                _PlayButton.render(gRenderer);
                SDL_RenderPresent(gRenderer);
                touchStatus = 1;
            }
            if(inside(x, y, ExitButton) && touchStatus != 2)
            {
                BackMenu.render(gRenderer);
                _ExitButton.render(gRenderer);
                SDL_RenderPresent(gRenderer);
                touchStatus = 2;
            }
            if(!inside(x, y, PlayButton) && !inside(x, y, ExitButton))
            {
                BackMenu.render(gRenderer);
                SDL_RenderPresent(gRenderer);
                touchStatus = 0;
            }
        }
        if(e.type == SDL_MOUSEBUTTONUP)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(inside(x, y, PlayButton))
            {
                waitOption();
                return;
            }
            if(inside(x, y, ExitButton))
            {
                exit(0);
            }
        }
    }
}
void waitOption()
{
    BackOption.render(gRenderer);
    SDL_RenderPresent(gRenderer);

    SDL_Event e;
    int touchStatus = 0;
    while(1)
    {
        if(SDL_WaitEvent(&e) == 0) continue;
        if(e.type == SDL_QUIT) exit(0);
        if(e.type == SDL_MOUSEMOTION)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(inside(x, y, ButtonOption[3]) && touchStatus != 1)
            {
                BackOption.render(gRenderer);
                _ButtonOption[3].render(gRenderer);
                SDL_RenderPresent(gRenderer);
                touchStatus = 1;
            }
            if(inside(x, y, ButtonOption[4]) && touchStatus != 2)
            {
                BackOption.render(gRenderer);
                _ButtonOption[4].render(gRenderer);
                SDL_RenderPresent(gRenderer);
                touchStatus = 2;
            }
            if(inside(x, y, ButtonOption[5]) && touchStatus != 3)
            {
                BackOption.render(gRenderer);
                _ButtonOption[5].render(gRenderer);
                SDL_RenderPresent(gRenderer);
                touchStatus = 3;
            }
            if(inside(x, y, ButtonOption[6]) && touchStatus != 4)
            {
                BackOption.render(gRenderer);
                _ButtonOption[6].render(gRenderer);
                SDL_RenderPresent(gRenderer);
                touchStatus = 4;
            }
            if(!inside(x, y, ButtonOption[3]) && !inside(x, y, ButtonOption[4])
                && !inside(x, y, ButtonOption[5]) && !inside(x, y, ButtonOption[6]))
            {
                BackOption.render(gRenderer);
                SDL_RenderPresent(gRenderer);
                touchStatus = 0;
            }
        }
        if(e.type == SDL_MOUSEBUTTONUP)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(inside(x, y, ButtonOption[3]))
            {
                FullPictureDemo(3);
                return;
            }
            if(inside(x, y, ButtonOption[4]))
            {
                FullPictureDemo(4);
                return;
            }
            if(inside(x, y, ButtonOption[5]))
            {
                FullPictureDemo(5);
                return;
            }
            if(inside(x, y, ButtonOption[6]))
            {
                FullPictureDemo(6);
                return;
            }
        }
    }
}
void FullPictureDemo(int option)
{
    BackBeforeGame.render(gRenderer);
    BackDemo.render(gRenderer);
    SDL_Rect DRect;
    DRect.x = 37, DRect.y = 60, DRect.w = 480, DRect.h = 480;
    gTexture[option].render(gRenderer, gTexture[option].sRect, DRect);
    SDL_RenderPresent(gRenderer);

    SDL_Event e;
    while(1)
    {
        if(SDL_WaitEvent(&e) == 0) continue;
        if(e.type == SDL_QUIT) exit(0);
        if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            case SDLK_RETURN:
            {
                waitGamePlay(option);
                return;
            }

        }
    }
}
void waitGamePlay(int option)
{
    InitMap(option);

    Background.render(gRenderer);
    BackGame[option].render(gRenderer);
    RenderSmallPicture(option);
    RenderNumber(option, 2);
    SDL_RenderPresent(gRenderer);

    SDL_Event e;
    int touchStatus = 0;
    while(!CheckWin(option))
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) exit(0);
            if( e.type == SDL_KEYDOWN )
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        if(curPos[option][option][option].S < option)
                            MoveBlank(option, 0, 1);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        if(curPos[option][option][option].S > 1)
                            MoveBlank(option, 0, -1);
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        if(curPos[option][option][option].F < option)
                            MoveBlank(option, 1, 0);
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        if(curPos[option][option][option].F > 1)
                            MoveBlank(option, -1, 0);
                        break;
                    }
                }
                Background.render(gRenderer);
                BackGame[option].render(gRenderer);
                RenderSmallPicture(option);
                RenderNumber(option, 2);
                SDL_RenderPresent(gRenderer);
            }
            if(e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(inside(x, y, ResetButton1) && touchStatus != 1)
                {
                    _ResetButton1.render(gRenderer);
                    SDL_RenderPresent(gRenderer);
                    touchStatus = 1;
                }
                if(inside(x, y, NewButton1) && touchStatus != 2)
                {
                    _NewButton1.render(gRenderer);
                    SDL_RenderPresent(gRenderer);
                    touchStatus = 2;

                }
                if(inside(x, y, MenuButton1) && touchStatus != 3)
                {
                    _MenuButton1.render(gRenderer);
                    SDL_RenderPresent(gRenderer);
                    touchStatus = 3;
                }
                if(inside(x, y, LookBackButton) && touchStatus != 4)
                {
                    _LookBackButton.render(gRenderer);
                    SDL_RenderPresent(gRenderer);
                    touchStatus = 4;
                }
                if(!inside(x, y, LookBackButton) && !inside(x, y, ResetButton1)
                    && !inside(x, y, NewButton1) && !inside(x, y, MenuButton1))
                {
                    Background.render(gRenderer);
                    BackGame[option].render(gRenderer);
                    RenderSmallPicture(option);
                    RenderNumber(option, 2);
                    SDL_RenderPresent(gRenderer);
                    touchStatus = 0;
                }
            }
            if(e.type == SDL_MOUSEBUTTONUP)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(inside(x, y, ResetButton1))
                {
                    ResetGame(option);
                    Background.render(gRenderer);
                    BackGame[option].render(gRenderer);
                    RenderSmallPicture(option);
                    _ResetButton1.render(gRenderer);
                    RenderNumber(option, 2);
                    SDL_RenderPresent(gRenderer);
                }
                if(inside(x, y, NewButton1))
                {
                    ResetMap(option);
                    FullPictureDemo(option);
                    return;
                }
                if(inside(x, y, MenuButton1))
                {
                    waitGameMenu();
                    return;
                }
                if(inside(x, y, LookBackButton))
                {
                    Background.render(gRenderer);
                    BackDemo.render(gRenderer);
                    SDL_Rect DRect;
                    DRect.x = 37, DRect.y = 60, DRect.w = 480, DRect.h = 480;
                    gTexture[option].render(gRenderer, gTexture[option].sRect, DRect);
                    _LookBackButton.render(gRenderer);
                    RenderNumber(option, 2);
                    SDL_RenderPresent(gRenderer);
                }
            }
        }
    }
    waitGameOver(option);
}
void waitGameOver(int option)
{
    highscore[option] = min(highscore[option], cntMove);
    BackWinGame.render(gRenderer);
    SDL_Rect DRect;
    DRect.x = 37, DRect.y = 60, DRect.w = 480, DRect.h = 480;
    gTexture[option].render(gRenderer, gTexture[option].sRect, DRect);
    RenderNumber(option, 3);
    SDL_RenderPresent(gRenderer);

    SDL_Event e;
    int touchStatus = 0;
    while(1)
    {
        if(SDL_WaitEvent(&e) == 0) continue;
        if(e.type == SDL_QUIT) exit(0);
        if(e.type == SDL_MOUSEMOTION)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(inside(x, y, ResetButton2) && touchStatus != 1)
            {
                BackWinGame.render(gRenderer);
                gTexture[option].render(gRenderer, gTexture[option].sRect, DRect);
                _ResetButton2.render(gRenderer);
                RenderNumber(option, 3);
                SDL_RenderPresent(gRenderer);
                touchStatus = 1;
            }
            if(inside(x, y, NewButton2) && touchStatus != 2)
            {
                BackWinGame.render(gRenderer);
                gTexture[option].render(gRenderer, gTexture[option].sRect, DRect);
                _NewButton2.render(gRenderer);
                RenderNumber(option, 3);
                SDL_RenderPresent(gRenderer);
                touchStatus = 2;
            }
            if(inside(x, y, MenuButton2) && touchStatus != 3)
            {
                BackWinGame.render(gRenderer);
                gTexture[option].render(gRenderer, gTexture[option].sRect, DRect);
                _MenuButton2.render(gRenderer);
                RenderNumber(option, 3);
                SDL_RenderPresent(gRenderer);
                touchStatus = 3;
            }
            if(!inside(x, y, ResetButton2) && !inside(x, y, NewButton2) && !inside(x, y, MenuButton2))
            {
                BackWinGame.render(gRenderer);
                gTexture[option].render(gRenderer, gTexture[option].sRect, DRect);
                RenderNumber(option, 3);
                SDL_RenderPresent(gRenderer);
                touchStatus = 0;
            }
        }
        else if(e.type == SDL_MOUSEBUTTONUP)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(inside(x, y, ResetButton2))
            {
                ResetGame(option);
                FullPictureDemo(option);
                return;
            }
            if(inside(x, y, NewButton2))
            {
                ResetMap(option);
                FullPictureDemo(option);
                return;
            }
            if(inside(x, y, MenuButton2))
            {
                waitGameMenu();
                return;
            }
        }
    }
}
//Creat Map by BFS and Save
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

//Read and Write Old Info
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

//Rand Function
string RandPicture()
{
    int id = Rand(1, 4);
    //int id = 2;
    string newid = to_string(id);
    string image_newid = "image/image" + newid + ".jpg";
    return image_newid;
}

int Rand(int Minn, int Maxx)
{
    return rand() % (Maxx - Minn + 1) + Minn;
}

//Game function
void RenderNumber(int option, int kind)
{
    SDL_Rect num[10];
    for (int i = 0; i < 10; ++i)
        num[i] = {i * 16, 0, 16, 16};
    string _highscore = to_string(highscore[option]);
    string _optimal = to_string(MinMove[option]);
    string _score = to_string(cntMove);
    if(kind== 2)
    {
        int XPos = 728 , YPos = 80;
        for (int i = 0; i < _score.length(); ++i)
        {
            SDL_Rect dRect = {XPos+ i*16, YPos, 16, 16};
            Number.render(gRenderer, num[_score[i]-'0'], dRect);
        }
        XPos = 744, YPos = 128;
        for(int i = 0; i < _optimal.length(); ++i)
        {
            SDL_Rect dRect = {XPos+ i*16, YPos, 16, 16};
            Number.render(gRenderer, num[_optimal[i]-'0'], dRect);
        }
    }
    else if(kind== 3)
    {
        int XPos = 728 , YPos = 112;
        for (int i = 0; i < _score.length(); ++i)
        {
            SDL_Rect dRect = {XPos+ i*16, YPos, 16, 16};
            Number.render(gRenderer, num[_score[i]-'0'], dRect);
        }
        XPos = 744, YPos = 208;
        for(int i = 0; i < _optimal.length(); ++i)
        {
            SDL_Rect dRect = {XPos+ i*16, YPos, 16, 16};
            Number.render(gRenderer, num[_optimal[i]-'0'], dRect);
        }
        XPos = 728, YPos = 170;
        for(int i = 0; i < _highscore.length(); ++i)
        {
            SDL_Rect dRect = {XPos+ i*16, YPos, 16, 16};
            Number.render(gRenderer, num[_highscore[i]-'0'], dRect);
        }
    }
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
    gTexture[option].loadfromfile(gRenderer, SavePicture[option]);

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
    int kt = 480/option;
    int kc = 2;
    for(int i = 1; i <= option; ++i)
        for(int j = 1; j <= option; ++j)
        {
            if(i == option && j == option) continue;
            SDL_Rect SRect, DRect;
            SRect.x = (i-1) * kt + 1;
            SRect.y = (j-1) * kt + 1;
            SRect.w = kt;
            SRect.h = kt;

            DRect.x = gTexture[option].x + (curPos[option][i][j].F-1) * (kt + kc);
            DRect.y = gTexture[option].y + (curPos[option][i][j].S-1) * (kt + kc);
            DRect.w = DRect.h = kt;
            gTexture[option].render(gRenderer, SRect, DRect);
        }
}

//Texture manage
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

     BackWinGame.loadfromfile(gRenderer, Backwingameimage);
     BackOption.loadfromfile(gRenderer, Backoptionimage);
     BackMenu.loadfromfile(gRenderer, Backmenuimage);
     BackDemo.loadfromfile(gRenderer, Backdemoimage);
     BackBeforeGame.loadfromfile(gRenderer, Backbeforegameimage);

     PlayButton.loadfromfile(gRenderer, Playbuttonimage);
     _PlayButton.loadfromfile(gRenderer, Playbuttonimage);

     ExitButton.loadfromfile(gRenderer, Exitbuttonimage);
     _ExitButton.loadfromfile(gRenderer, Exitbuttonimage);

     ResetButton1.loadfromfile(gRenderer, Resetbuttonimage);
     _ResetButton1.loadfromfile(gRenderer, Resetbuttonimage);

     ResetButton2.loadfromfile(gRenderer, Resetbuttonimage);
     _ResetButton2.loadfromfile(gRenderer, Resetbuttonimage);

     NewButton1.loadfromfile(gRenderer, Newbuttonimage);
     _NewButton1.loadfromfile(gRenderer, Newbuttonimage);

     NewButton2.loadfromfile(gRenderer, Newbuttonimage);
     _NewButton2.loadfromfile(gRenderer, Newbuttonimage);

     MenuButton1.loadfromfile(gRenderer, Menubuttonimage);
     _MenuButton1.loadfromfile(gRenderer, Menubuttonimage);

     MenuButton2.loadfromfile(gRenderer, Menubuttonimage);
     _MenuButton2.loadfromfile(gRenderer, Menubuttonimage);

     LookBackButton.loadfromfile(gRenderer, Lookbackbuttonimage);
     _LookBackButton.loadfromfile(gRenderer, Lookbackbuttonimage);

     ButtonOption[3].loadfromfile(gRenderer, Button3x3image);
     _ButtonOption[3].loadfromfile(gRenderer, Button3x3image);

     ButtonOption[4].loadfromfile(gRenderer, Button4x4image);
     _ButtonOption[4].loadfromfile(gRenderer, Button4x4image);

     ButtonOption[5].loadfromfile(gRenderer, Button5x5image);
     _ButtonOption[5].loadfromfile(gRenderer, Button5x5image);

     ButtonOption[6].loadfromfile(gRenderer, Button6x6image);
     _ButtonOption[6].loadfromfile(gRenderer, Button6x6image);

     Number.loadfromfile(gRenderer, Numberimage);
}
void setUpTexture()
{
    Background.setsRect(0, 0, 842, 587);
    Background.setdRect(0, 0, 842, 587);

    gTexture[3].setsRect(0, 0, 480, 480);
    gTexture[3].setdRect(39, 39, 556, 581);

    gTexture[4].setsRect(0, 0, 480, 480);
    gTexture[4].setdRect(38, 38, 558, 583);

    gTexture[5].setsRect(0, 0, 480, 480);
    gTexture[5].setdRect(37, 37, 560, 585);

    gTexture[6].setsRect(0, 0, 480, 480);
    gTexture[6].setdRect(36, 36, 480, 480);

    BackGame[3].setsRect(0, 0, 556, 581);
    BackGame[3].setdRect(3, 3, 556, 581);

    BackGame[4].setsRect(0, 0, 558, 583);
    BackGame[4].setdRect(2, 2, 558, 583);

    BackGame[5].setsRect(0, 0, 560, 585);
    BackGame[5].setdRect(1, 1, 560, 585);

    BackGame[6].setsRect(0, 0, 562, 587);
    BackGame[6].setdRect(0, 0, 562, 587);

    BackMenu.setsRect(0, 0, 842, 587);
    BackMenu.setdRect(0, 0, 842, 587);

    BackOption.setsRect(0, 0, 842, 587);
    BackOption.setdRect(0, 0, 842, 587);

    BackWinGame.setsRect(0, 0, 842, 587);
    BackWinGame.setdRect(0, 0, 842, 587);

    BackDemo.setsRect(0, 0, 562, 587);
    BackDemo.setdRect(0, 0, 562, 587);

    BackBeforeGame.setsRect(0, 0, 842, 587);
    BackBeforeGame.setdRect(0, 0, 842, 587);

    PlayButton.setsRect(0, 0, 194, 104);
    PlayButton.setdRect(324, 334, 194, 104);

    _PlayButton.setsRect(194, 0, 194, 104);
    _PlayButton.setdRect(324, 334, 194, 104);

    ExitButton.setsRect(0, 0, 194, 104);
    ExitButton.setdRect(324, 457, 194, 104);

    _ExitButton.setsRect(194, 0, 194, 104);
    _ExitButton.setdRect(324, 457, 194, 104);

    ButtonOption[3].setsRect(0, 0, 248, 248);
    ButtonOption[3].setdRect(37, 60, 248, 248);

    _ButtonOption[3].setsRect(248, 0, 248, 248);
    _ButtonOption[3].setdRect(37, 60, 248, 248);

    ButtonOption[4].setsRect(0, 0, 248, 248);
    ButtonOption[4].setdRect(281, 60, 248, 248);

    _ButtonOption[4].setsRect(248, 0, 248, 248);
    _ButtonOption[4].setdRect(281, 60, 248, 248);

    ButtonOption[5].setsRect(0, 0, 248, 248);
    ButtonOption[5].setdRect(37, 304, 248, 248);

    _ButtonOption[5].setsRect(248, 0, 248, 248);
    _ButtonOption[5].setdRect(37, 304, 248, 248);

    ButtonOption[6].setsRect(0, 0, 248, 248);
    ButtonOption[6].setdRect(281, 304, 281, 304);

    _ButtonOption[6].setsRect(248, 0, 248, 248);
    _ButtonOption[6].setdRect(281, 304, 248, 248);

    ResetButton1.setsRect(0, 0, 80, 108);
    ResetButton1.setdRect(614, 164, 80, 108);

    _ResetButton1.setsRect(80, 0, 80, 108);
    _ResetButton1.setdRect(614, 164, 80, 108);

    ResetButton2.setsRect(0, 0, 80, 108);
    ResetButton2.setdRect(614, 260, 80, 108);

    _ResetButton2.setsRect(80, 0, 80, 108);
    _ResetButton2.setdRect(614, 260, 80, 108);

    NewButton1.setsRect(0, 0, 80, 108);
    NewButton1.setdRect(710, 164, 80, 108);

    _NewButton1.setsRect(80, 0, 80, 108);
    _NewButton1.setdRect(710, 164, 80, 108);

    NewButton2.setsRect(0, 0, 80, 108);
    NewButton2.setdRect(710, 260, 80, 108);

    _NewButton2.setsRect(80, 0, 80, 108);
    _NewButton2.setdRect(710, 260, 80, 108);

    MenuButton1.setsRect(0, 0, 80, 108);
    MenuButton1.setdRect(614, 288, 80, 108);

    _MenuButton1.setsRect(80, 0, 80, 108);
    _MenuButton1.setdRect(614, 288, 80, 108);

    MenuButton2.setsRect(0, 0, 80, 108);
    MenuButton2.setdRect(662, 384, 80, 108);

    _MenuButton2.setsRect(80, 0, 80, 108);
    _MenuButton2.setdRect(662, 384, 80, 108);

    LookBackButton.setsRect(0, 0, 80, 108);
    LookBackButton.setdRect(710, 288, 80, 108);

    _LookBackButton.setsRect(80, 0, 80, 108);
    _LookBackButton.setdRect(710, 288, 80, 108);

}


//SDL
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
 void close()
 {
    //Free music

    //Destroy Texture
    Background.free();

    BackGame[3].free();
    BackGame[4].free();
    BackGame[5].free();
    BackGame[6].free();

    gTexture[3].free();
    gTexture[4].free();
    gTexture[5].free();
    gTexture[6].free();

    BackWinGame.free();
    BackOption.free();
    BackMenu.free();
    BackDemo.free();
    BackBeforeGame.free();

    PlayButton.free();
    _PlayButton.free();

    ExitButton.free();
    _ExitButton.free();

    ResetButton1.free();
    _ResetButton1.free();

    ResetButton2.free();
    _ResetButton2.free();

    NewButton1.free();
    _NewButton1.free();

    NewButton2.free();
    _NewButton2.free();

    MenuButton1.free();
    _MenuButton1.free();

    MenuButton2.free();
    _MenuButton2.free();

    LookBackButton.free();
    _LookBackButton.free();

    ButtonOption[3].free();
    _ButtonOption[3].free();

    ButtonOption[4].free();
    _ButtonOption[4].free();

    ButtonOption[5].free();
    _ButtonOption[5].free();

    ButtonOption[6].free();
    _ButtonOption[6].free();

    Number.free();

    //Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

    //Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
 }


