#ifndef TOWER_H
#define TOWER_H
#include"SDL.h"
#include"ENEMY.h"
//#include"final/const.h"
#include<cmath>
#define PI 3.14159265


class tower{
    public:
	    friend class ENEMY;
        tower(int num_x, int num_y, int type) :x(80+num_x*90), y(70+num_y*90), theta(0)
        {
            kind = type;
            quad.x = x;
            quad.y = y;
            t = SDL_GetTicks();
            switch (kind){
            case 0:
                atk = 5;
                cooltime = 1000;
                range = 270;
                break;
            case 1:
                atk = 5;
                cooltime = 200;
                range = 1000;
                break;
            case 2:
                atk = 5;
                cooltime = 200;
                range = 1000;
                break;
            case 3:
                atk = 5;
                cooltime = 200;
                range = 1000;
                break;
            case 4:
                atk = 5;
                cooltime = 200;
                range = 1000;
                break;
            case 5:
                atk = 5;
                cooltime = 200;
                range = 1000;
                break;
            case 6:
                atk = 5;
                range = 1000;
                break;
            case 7:
                atk = 5;
                range = 1000;
                break;
            case 8:
                atk = 5;
                range = 1000;
                break;
            default:
                break;
            }
        }
        bool ableatk(int t_c){
            //printf("t=%d\n", t);
            //printf("t_c=%d\n", t_c);
            if (t_c-t>cooltime){
               
                t = t_c;
                //printf("hi\n");
                return true;
            }
            else{
                //printf("%d", t_c);
                //printf("%d", t);
                false;
            }
        }
        bool inrange(ENEMY* monster)//check if enemy is in tower range
        {
            if (pow((monster->rect.x - x), 2) + pow((monster->rect.y - y), 2) < pow(range, 2))
            {
                return true;
            }
            return false;
        }
        void rotate(ENEMY* locked_enemy){
            if(kind<6)
            {
                
                calculated_theta = (atan2(y-locked_enemy->rect.y,locked_enemy->rect.x-x))*180/3.1416;
                theta = int(calculated_theta/11.25);
                if (theta < 0) {
                    theta += 16;
                }
                if (locked_enemy->rect.x < x) {
                    theta += 16;
                }
                  
            }
            else{
                theta+= 1;
                if(theta>7)theta-=8;
            }
        }
	int theta;
	int kind=1;
	SDL_Rect quad={0,0,90,90};
    int x,y;
    int atk;
    int range;
    int t;
    double calculated_theta;
    int cooltime;
    
    
};
#endif

