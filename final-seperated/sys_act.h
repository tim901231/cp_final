#ifndef SYS_ACT_H
#define SYS_ACT_H
#include"variable.h"
#include"option_list.h"
#include<fstream>
bool init();
bool point_in_rect(SDL_Point p, const SDL_Rect r);
void setrect(SDL_Rect r, int a, int b, int c, int d);
void upgrade_list_init();
void upgrade_act();
void show_building();
void loadothermedia();
void change_upgrade();
void animation();
void click_motion();
void render_botton();
int loadLeaderboard();
#endif