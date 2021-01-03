#ifndef VARIABLE_H
#define VARIABLE_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"tower.h"
#include"bullet.h"
#include"SDL_ttf.h"
#include<vector>
#include"enemy.h"
#include"word.h"
#include<string>
using namespace std;
//windows setting
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TOWER_WIDTH;
//variable
extern int TotalMoney;
extern int TotalLife;
extern int speedy;
extern int currentscore;
//map's things
enum gamestatus { play, upgrading, option, menu };
extern SDL_Texture* background;
extern SDL_Texture* light;
extern SDL_Texture* slow;
extern SDL_Texture* rocket;
extern SDL_Texture* cancel;
extern SDL_Texture* user;
extern const SDL_Rect initiallight;
extern const SDL_Rect initialslow;
extern const SDL_Rect initialrocket;
extern const SDL_Rect cancel_rect;
extern SDL_Rect userrect;
extern SDL_Rect lightrect;
extern SDL_Rect slowrect;
extern SDL_Rect rocketrect;
extern SDL_Point mouse_position;
//map
//upgrade
extern SDL_Texture* upgradeorsell[];
extern SDL_Texture* putlist[];
extern SDL_Rect upgradelist[];
//menu's thing
extern SDL_Texture* startbutton;
extern SDL_Texture* startpage;
extern SDL_Texture* startturning1;
extern SDL_Texture* startturning2;
extern SDL_Texture* startturning3;
extern SDL_Texture* title;
//menu
//tower's things
extern tower*** towers;
extern SDL_Texture* tower_pic[];
extern SDL_Rect towerClips[][32];
extern SDL_Rect towerbases;
extern SDL_Rect towerClips2[][8];

//tower
//bullet's thing
extern SDL_Texture* bullet_pic[];
extern vector<bullet*> bullets;
//bullet
//position
extern int p, q, tempx, tempy;
//positoin
//flags
extern bool quit;
extern bool lightflag;
extern bool slowflag;
extern bool rocketflag;
extern bool functionmode;
extern bool startflag;
extern int loop;
//flags
//Event handler
extern SDL_Event e;
extern gamestatus status;
//Event handler
//words
extern SDL_Color wordcolor;
//words
//menu
extern const SDL_Rect turning1;
extern const SDL_Rect turning2;
extern const SDL_Rect turning3;
extern const SDL_Rect titlerect;
extern double degrees;
extern SDL_RendererFlip flipType;
//menu
//enemy's things
extern vector<ENEMY*> enemies;
extern ENEMY* DEFAULT, *add;
extern SDL_Texture* EnemyTexture[], *Green, *Red;  //stands for (L)Light (H)Heavy (S)Soldier (T)Tank
extern SDL_Rect enemyClips[][50], StartButton;
extern int cntdown, num, currentwave, rate;
extern bool canBuild, StartButtonPressed;
extern tower* test;
//enemy
//function's thing
extern SDL_Rect option_bottom;
extern SDL_Texture* option_bottom_pic;
extern SDL_Texture* bottoms_pic[];
extern SDL_Rect bottoms[];
extern SDL_Rect option_list;
extern SDL_Rect pausebottom;
extern SDL_Rect startbottom;
extern SDL_Rect fastbottom;
extern SDL_Rect mutebottom;
extern SDL_Rect leavebottom;// back to menu
extern SDL_Rect exitbottom;//red x
extern SDL_Texture* option_list_pic;
extern SDL_Texture* pausebottom_pic;
extern SDL_Texture* startbottom_pic;
extern SDL_Texture* fastbottom_pic;
extern SDL_Texture* mutebottom_pic;
extern SDL_Texture* leavebottom_pic; // back to menu
extern SDL_Texture* exitbottom_pic; //red x
//WORDS
//extern word* currmoney;
extern string id[];
extern int scores[];
#endif