#ifndef TOWER_H
#define TOWER_H

#define PI 3.14159265
#include<SDL.h>

class tower{
    public:
	    friend class ENEMY;
        tower(int num_x, int num_y, int type, int count);
        bool ableatk(int t_c);
        bool inrange(ENEMY* monster);
        void rotate(ENEMY* locked_enemy);
        int money; 
	    int theta;
	    int kind;
        SDL_Rect quad;
        SDL_Rect bquad;
        int x,y;
        int atk;
        int range;
        int t;
        int sellprice;
        double calculated_theta;
        int cooltime;
};
void loadtowermedia();
#endif

