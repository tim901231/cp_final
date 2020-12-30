#include"variable.h"

//variable
int speedy = 1;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
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
