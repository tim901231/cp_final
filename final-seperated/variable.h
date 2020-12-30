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
//windows setting
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TOWER_WIDTH;
bool init();
//variable
extern int TotalMoney;
extern int TotalLife;
extern int speedy;
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

#endif