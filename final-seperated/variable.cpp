#include"variable.h"

//windows setting
SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer=NULL;
TTF_Font* gFont=NULL;
const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 1000;
const int TOWER_WIDTH = 90;

//variable
int TotalMoney = 30;
int TotalLife = 24;
int speedy=1;

//map's things
SDL_Texture* background;
SDL_Texture* light;
SDL_Texture* slow;
SDL_Texture* rocket;
SDL_Texture* cancel;
SDL_Texture* user;
const SDL_Rect initiallight = { 1720,910,90,90 };
const SDL_Rect initialslow = { 1720,820,90,90 };
const SDL_Rect initialrocket = { 1720,730,90,90 };
const SDL_Rect cancel_rect = { 1720,640,90,90 };
SDL_Rect userrect = { 100,100,400,300 };
SDL_Rect lightrect = { 1720,910,80,80 };
SDL_Rect slowrect = { 1720,820,80,80 };
SDL_Rect rocketrect = { 1720,730,80,80 };
SDL_Point mouse_position;
//map

//menu's thing
SDL_Texture* startbutton = NULL;
SDL_Texture* startpage = NULL;
SDL_Texture* startturning1 = NULL;
SDL_Texture* startturning2 = NULL;
SDL_Texture* startturning3 = NULL;
SDL_Texture* title = NULL;
//menu
//tower's things
tower*** towers = new tower **[18];
SDL_Texture* tower_pic[15];
SDL_Rect towerClips[15][32];
SDL_Rect towerbases = { 0,0,70,70 };
//tower
//bullet's thing
SDL_Texture* bullet_pic[3];
vector<bullet*> bullets;
//bullet
//position
int p = 0, q = 0, tempx, tempy;
//positoin
//flags
bool quit = false;
bool lightflag = false;
bool slowflag = false;
bool rocketflag = false;
bool functionmode = false;
bool startflag = false;
int loop = 0;
//flags
//Event handler
SDL_Event e;
gamestatus status = menu;
//Event handler
//words
SDL_Color wordcolor = { 0000,0000,0000,0000 };
//words
//menu
const SDL_Rect turning1 = { 715,330,300,300 };
const SDL_Rect turning2 = { 640,255,450,450 };
const SDL_Rect turning3 = { 540,155,650,650 };
const SDL_Rect titlerect = { 900,50,800,160 };
double degrees = 0;
SDL_RendererFlip flipType = SDL_FLIP_NONE;
//menu
//enemy's things
vector<ENEMY*> enemies;
ENEMY* DEFAULT = new ENEMY(0);
SDL_Texture* EnemyTexture[10];  //stands for (L)Light (H)Heavy (S)Soldier (T)Tank
SDL_Rect enemyClips[10][50];
int cntdown = 0;
//
bool canBuild;
tower* test = new tower(0, 0, 0, 0);
//enemy
//function's thing
SDL_Rect option_bottom = { 10,950,50,50 };
SDL_Texture* option_bottom_pic;
SDL_Texture* bottoms_pic[7];
SDL_Rect bottoms[7];
SDL_Rect option_list = { 605,310,590,380 };
SDL_Rect pausebottom = { 690,390,100,100 };
SDL_Rect startbottom = { 860,390,100,100 };
SDL_Rect fastbottom = { 1030,390,100,100 };
SDL_Rect mutebottom = { 800,550,80,80 };
SDL_Rect leavebottom = { 920,550,80,80 };// back to menu
SDL_Rect exitbottom = { 1150,310,45,45 };//red x
SDL_Texture* option_list_pic = NULL;
SDL_Texture* pausebottom_pic = NULL;
SDL_Texture* startbottom_pic = NULL;
SDL_Texture* fastbottom_pic = NULL;
SDL_Texture* mutebottom_pic = NULL;
SDL_Texture* leavebottom_pic = NULL; // back to menu
SDL_Texture* exitbottom_pic = NULL; //red x