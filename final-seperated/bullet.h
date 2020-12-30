#ifndef BULLET_H
#define BULLET_H
#include<SDL.h>
#include"enemy.h"
class bullet
{
public:
	friend class tower;
	bullet(tower* tower1, ENEMY* enemy1);
	void move();
	bool touch(ENEMY* enemy1);
	SDL_Rect quad;
	int x, y, speed, atk, kind;
	double x_e, y_e, v_x, v_y;
};
#endif
		