#ifndef VARIABLE_H
#define VARIABLE_H
#include<SDL.h>
#include"SDL_ttf.h"
//variable
extern int speedy;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;
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

#endif