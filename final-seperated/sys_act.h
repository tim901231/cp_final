#ifndef SYS_ACT_H
#define SYS_ACT_H
#include"variable.h"
bool init();
bool point_in_rect(SDL_Point p, const SDL_Rect r);
void upgrade_list_init();
void upgrade_act();
void show_building();
void loadothermedia();
#endif