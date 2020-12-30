#include"tower.h"
//#include"enemy.h"
#include"variable.h"
#include"SDL_image.h"
#include<cmath>
#include"bullet.h"

bullet::bullet(tower* tower1, ENEMY* enemy1) {
	quad = { 0,0,80,80 };
	kind = tower1->kind % 3;
	speed = 50;
	atk = tower1->atk;
	x = tower1->x;
	y = tower1->y;
	// modify the position of bullet
	if (kind % 3 == 0) {
		quad.x = x + 22;
		quad.y = y + 22;
		quad.w = 45;
		quad.h = 45;
	}
	else {
		quad.x = x;
		quad.y = y;
		quad.w = 90;
		quad.h = 90;
	}
	v_x = (enemy1->rect.x - tower1->x) * 1.0 / speed * speedy;
	v_y = (enemy1->rect.y - tower1->y) * 1.0 / speed * speedy;
	x_e = x;
	y_e = y;
}
void bullet::move()
{
	x_e += v_x;
	y_e += v_y;
	x = int(x_e);
	y = int(y_e);
	if (kind % 3 == 0) {
		quad.x = x + 22;
		quad.y = y + 22;
	}
	else {
		quad.x = x;
		quad.y = y;
	}
}
bool bullet::touch(ENEMY* enemy1)
{
	//distance unsure
	if (pow(enemy1->rect.x - x, 2) + pow(enemy1->rect.y - y, 2) < 3600) {
		return true;
	}
	else {
		return false;
	}
}
void loadbulletmedia() {
	SDL_Surface* loadedSurface = IMG_Load("pictures/Bullet_Small.png");
	bullet_pic[0] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Bullet_Large.png");
	bullet_pic[1] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Uranium_Bullet.png");
	bullet_pic[2] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Basic_Level_Classic.jpg");
	background = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Light_Gun_user.png");
	light = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Slow_Tower_user.png");
	slow = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Light_Rocket_Launcher_user.png");
	rocket = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/test_user.png"); // new include
	user = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/red.png"); // new include
	cancel = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
}
