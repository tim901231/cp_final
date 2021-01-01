#include"SDL.h"
#include"ENEMY.h"
#include"variable.h"
#include<cmath>
#include"tower.h"
#include"SDL_image.h"
#include<vector>
#include <iostream>
#define PI 3.14159265

tower::tower(int num_x, int num_y, int type, int time) :x(80 + num_x * 90), y(70 + num_y * 90), theta(0)
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
    t = time;
    switch (kind) {
    case 0: //gun
        atk = 5;
        cooltime = 50;
        range = 150;
        sellprice = 3;
        can_upgrade.push_back(1);
        can_upgrade.push_back(3);
        break;
    case 1:
        atk = 10;
        cooltime = 50;
        range = 150;
        sellprice = 4;
        can_upgrade.push_back(2);
        break;
    case 2:
        atk = 15;
        cooltime = 50;
        range = 150;
        sellprice = 6;
        break;
    case 3: //aircanon
        atk = 100;
        cooltime = 200;
        range = 220;
        sellprice = 12;
        can_upgrade.push_back(4);
        break;
    case 4:
        atk = 120;
        cooltime = 200;
        range = 220;
        sellprice = 24;
        break;
    case 5://rocket
        atk = 50;
        cooltime = 200;
        range = 220;
        sellprice = 10;
        can_upgrade.push_back(6);
        can_upgrade.push_back(8);
        break;
    case 6: 
        atk = 65;
        cooltime = 200;
        range = 220;
        sellprice = 15;
        can_upgrade.push_back(7);
        break;
    case 7:
        atk = 80;
        cooltime = 200;
        range = 220;
        sellprice = 30;
        break;
    case 8://mortar
        atk = 70;
        cooltime = 200;
        range = 400;
        sellprice = 28;
        can_upgrade.push_back(9);
        break;
    case 9:
        atk = 100;
        cooltime = 200;
        range = 400;
        sellprice = 56;
        break;
    case 10: //slow
        atk = 30;
        range = 220;
        sellprice = 5;
        can_upgrade.push_back(11);
        can_upgrade.push_back(13);
        break;
    case 11:
        atk = 50;
        range = 220;
        sellprice = 10;
        can_upgrade.push_back(12);
        break;
    case 12:
        atk = 70;
        range = 220;
        sellprice = 20;
        break;
    case 13: //teleport
        range = 220;
        sellprice = 16;
        break;
    case 14:
        range = 220;
        sellprice = 16;
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
    return false;
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
    if (kind < 8)
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
    else if (kind >= 10 && kind < 13) {
        theta += 1;
        if (theta > 7)theta -= 8;
    }
    else if (kind == 14) {
        theta += 1;
        if (theta > 15)theta -= 16;
    }
}
void loadtowermedia() {
    SDL_Surface* loadedSurface = IMG_Load("pictures/Light_Gun.png");
    tower_pic[0] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Medium_Gun.png");
    tower_pic[1] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Heavy_Gun.png");
    tower_pic[2] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Light_Antiair_Cannon.png");
    tower_pic[3] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Heavy_Antiair_Cannon.png");
    tower_pic[4] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Light_Rocket_Launcher.png");
    tower_pic[5] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Medium_Rocket_Launcher.png");
    tower_pic[6] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Heavy_Rocket_Launcher.png");
    tower_pic[7] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Artillery.png");
    tower_pic[8] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Mortar.png");
    tower_pic[9] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Basic_Slow_Tower.png");
    tower_pic[10] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Upgraded_Slow_Tower.png");
    tower_pic[11] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Advanced_Slow_Tower3.png");
    tower_pic[12] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Teleport_Tower_Unarmed.png");
    tower_pic[13] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Teleport_Tower_Armed.png");
    tower_pic[14] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}
void tower_init() {
    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 32; i++)
        {
            towerClips[j][i].x = 70 * (i + 1);
            towerClips[j][i].y = 0;
            towerClips[j][i].w = 70;
            towerClips[j][i].h = 70;
        }
    }
    for (int j = 8; j < 10; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            towerClips[j][i].x = 70 * i;
            towerClips[j][i].y = 0;
            towerClips[j][i].w = 70;
            towerClips[j][i].h = 70;
        }
    }
    for (int j = 10; j < 13; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            towerClips[j][i].x = 70 * (i + 1);
            towerClips[j][i].y = 0;
            towerClips[j][i].w = 70;
            towerClips[j][i].h = 70;
        }
    }
    for (int i = 0; i < 16; i++)
    {
        towerClips[14][i].x = 70 * (i + 1);
        towerClips[14][i].y = 0;
        towerClips[14][i].w = 70;
        towerClips[14][i].h = 70;
    }
    for (int i = 0; i < 18; i++)
    {
        towers[i] = new tower * [10];
    }
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            towers[i][j] = NULL;
        }
    }
}
void tower_motion() {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 10; j++) {
            if (towers[i][j] != NULL) {
                //render tower
                if (towers[i][j]->kind < 8) {
                    for (int k = 0; k < enemies.size(); k++) {
                        if (towers[i][j]->inrange(enemies[k]) == 1)
                        {
                            towers[i][j]->rotate(enemies[k]);
                            if (towers[i][j]->ableatk(loop) == 1) {
                                //make a bullet
                                bullet* x = new bullet(towers[i][j], enemies[k]);
                                bullets.push_back(x);
                                break;
                            }
                        }
                    }
                    SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerbases, &towers[i][j]->bquad);
                    SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerClips[towers[i][j]->kind][towers[i][j]->theta], &towers[i][j]->quad);
                }
                else if (towers[i][j]->kind == 8 || towers[i][j]->kind == 9) {
                    SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerClips[towers[i][j]->kind][0], &towers[i][j]->quad);
                    towers[i][j]->y -= 30;
                    SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerClips[towers[i][j]->kind][0], &towers[i][j]->quad);
                    towers[i][j]->y += 30;
                }
                else if (towers[i][j]->kind >= 10 && towers[i][j]->kind <= 12) {//slow tower
                    for (int k = 0; k < enemies.size(); k++) {
                        if (towers[i][j]->inrange(enemies[k]))
                        {
                            enemies[k]->freeze = towers[i][j]->atk;
                        }
                    }
                    towers[i][j]->theta += 1;
                    if (towers[i][j]->theta > 7) towers[i][j]->theta -= 8;
                    SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerbases, &towers[i][j]->bquad);
                    SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerClips[towers[i][j]->kind][towers[i][j]->theta], &towers[i][j]->quad);
                }
                else if (towers[i][j]->kind == 13) {
                    SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], NULL, &towers[i][j]->quad);
                }
                else if (towers[i][j]->kind == 14) {
                    for (auto enemy : enemies) {
                        if (towers[i][j]->inrange(enemy) == 1)
                        {
                            towers[i][j]->rotate(enemy);
                            if (towers[i][j]->ableatk(loop) == 1) {
                                //teleport
                                cout << "triggered\n";  //For Debug
                                enemy->pos = 0;
                                enemy->rect.x = 0;
                                enemy->rect.y = 520;
                                enemy->nowx = enemy->rect.x;
                                enemy->nowy = enemy->rect.y;
                                enemy->PATH.clear();
                                enemy->PATH.push_back({ 0,5 });
                                enemy->FindPath(enemy->CanFly);
                                break;
                            }
                        }
                    }
                    towers[i][j]->theta += 1;
                    if (towers[i][j]->theta > 15) towers[i][j]->theta -= 16;
                    SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerbases, &towers[i][j]->bquad);
                    SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerClips[towers[i][j]->kind][towers[i][j]->theta], &towers[i][j]->quad);
                }
            }
        }
    }
}
void upgrade(int x, int y, int kind, int t)
{
    delete towers[x][y];
    towers[x][y] = NULL;
    towers[x][y] = new tower(x, y, kind, t);
}