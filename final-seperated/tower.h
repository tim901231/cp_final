#ifndef TOWER_H
#define TOWER_H

#define PI 3.14159265
#include<SDL.h>
#include"enemy.h"
#include<vector>
class tower {
public:
    friend class ENEMY;
    tower(int num_x, int num_y, int type, int time);
    int a_g; // 0 for ground, 1 for air, 2 for both;
    bool ableatk(int t_c);
    bool inrange(ENEMY* monster);
    void rotate(ENEMY* locked_enemy);
    int money;
    int theta;
    int kind;
    SDL_Rect quad;
    SDL_Rect bquad;
    int x, y;
    int atk;
    int range;
    int t;
    int sellprice;
    double calculated_theta;
    int cooltime;
    //vector<int> can_upgrade;
};
void loadtowermedia();
void tower_init();
void tower_motion();
void upgrade(int x, int y, int kind, int t);
#endif
/*new variable
SDL_Texture* tower_pic[15];
SDL_Rect towerClips[15][32];
SDL_Rect towerbases = { 0,0,70,70 };
new*/

