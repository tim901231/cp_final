#include"SDL.h"
#include"ENEMY.h"
#include"variable.h"
#include<cmath>
#include"tower.h"
#define PI 3.14159265



tower::tower(int num_x, int num_y, int type, int count) :x(80 + num_x * 90), y(70 + num_y * 90), theta(0)
{
    kind = type;
    bquad.x = x;
    bquad.y = y + 15;
    bquad.w = 90;
    bquad.h = 90;
    quad.x = x;
    quad.y = y;
    quad.w = 90;
    quad.h = 90;
    t = count;
    switch (kind) {
    case 0: //gun
        atk = 1;
        cooltime = 50;
        range = 150;
        sellprice = 3;
        break;
    case 1:
        atk = 15;
        cooltime = 50;
        range = 150;
        sellprice = 4;
        break;
    case 2:
        atk = 25;
        cooltime = 50;
        range = 150;
        sellprice = 8;
        break;
    case 3: //roc
        atk = 60;
        cooltime = 200;
        range = 220;
        break;
    case 4:
        atk = 75;
        cooltime = 200;
        range = 220;
        break;
    case 5:
        atk = 90;
        cooltime = 200;
        range = 220;
        break;
    case 6: //slow
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
bool tower::ableatk(int t_c) {
    if (t_c - t > cooltime / speedy) {

        t = t_c;
        return true;
    }
    else {
        false;
    }
}
bool tower::inrange(ENEMY* monster)//check if enemy is in tower range
{
    if (pow((monster->rect.x - x), 2) + pow((monster->rect.y - y), 2) < pow(range, 2))
    {
        return true;
    }
    return false;
}
void tower::rotate(ENEMY* locked_enemy) {
    if (kind < 6)
    {
        //double y = 1.0;
        //double x = 1.0;
        //calculated_theta = 0;
        calculated_theta = atan2(locked_enemy->rect.x - x, y - locked_enemy->rect.y) * 180 / PI;
        //calculated_theta = atan2(x,y);
        //printf("%f\n", calculated_theta);
        if (calculated_theta < 0) {
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
    else {
        theta += 1;
        if (theta > 7)theta -= 8;
    }
}