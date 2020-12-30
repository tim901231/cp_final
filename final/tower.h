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
        tower(int num_x, int num_y, int type, int count) :x(80+num_x*90), y(70+num_y*90), theta(0)
        {
            kind = type;
            bquad.x = x;
            bquad.y = y + 15;
            quad.x = x;
            quad.y = y;
            t = count;
            switch (kind){
            case 0:
                atk = 10;
                cooltime = 15;
                range = 150;
                sellprice = 3;
                break;
            case 1:
                atk = 15;
                cooltime = 15;
                range = 150;
                sellprice = 4;
                break;
            case 2:
                atk = 25;
                cooltime = 15;
                range = 150;
                sellprice = 8;
                break;
            case 3:
                atk = 2;
                cooltime = 500;
                range = 200;
                break;
            case 4:
                atk = 3;
                cooltime = 450;
                range = 210;
                break;
            case 5:
                atk = 4;
                cooltime = 400;
                range = 220;
                break;
            case 6:
                atk = 10;
                range = 300;
                break;
            case 7:
                atk = 20;
                range = 300;
                break;
            case 8:
                atk = 30;
                range = 300;
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
                //double y = 1.0;
                //double x = 1.0;
                //calculated_theta = 0;
                calculated_theta = atan2(locked_enemy->rect.x - x,y-locked_enemy->rect.y)*180/PI;
                //calculated_theta = atan2(x,y);
                //printf("%f\n", calculated_theta);
                if (calculated_theta<0) {
                    calculated_theta += 360;
                }
                
                if (calculated_theta < 354.375) {
                    calculated_theta += 5.625;
                    theta = int(calculated_theta / 11.25);
                }
                else {
                   
                    theta = 0;
                }
                
                
                  
            }
            else{
                theta+= 1;
                if(theta>7)theta-=8;
            }
        }
    int money; 
	int theta;
	int kind=1;
	SDL_Rect quad={0,0,90,90};
    SDL_Rect bquad = { 0,0,90,90 };
    int x,y;
    int atk;
    int range;
    int t;
    int sellprice;
    double calculated_theta;
    int cooltime;
    
    
};
#endif

