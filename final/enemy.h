#ifndef ENEMY_H
#define ENEMY_H

#include <queue>
#include <utility>

#include "SDL.h"
#include "tower.h"

using namespace std;
typedef pair<int,int> pii;

const int RIGHT = 0;
const int UP = 1;
const int LEFT = 2;
const int DOWN = 3;
const char *Light_Soldier_path = "./pictures/Light_soldier.png";
const char *Heavy_Soldier_path = "./pictures/Heavy_Soldier.png";
const char *Light_Tank_path = "./pictures/Light_Tank.png";
const char *Heavy_Tank_path = "./pictures/Heavy_Tank.png";

#define X first
#define Y second

int health = 10;
pii DIR[4] = {{1,0}, {0, -1}, {-1, 0}, {0, 1}};

pii operator +(const pii &p1, const pii &p2){
	return {p1.X + p2.X, p1.Y + p2.Y};
}

pii operator -(const pii &p1, const pii &p2){
	return {p1.X - p2.X, p1.Y - p2.Y};
}

bool check(pii p){
	return (p.X >= 0 && p.X < 18 && p.Y >= 0 && p.Y < 10);
}

class val{
	public:
		pii pos;
		vector<pair<int, int> > shortest_path;
};

class ENEMY {
public:
	bool CanFly;
	int TYPE, hp, dir, money, freeze, period;
	double speed, nowx, nowy, current_phase;
	pii pos;
	SDL_Texture *pic;
	SDL_Rect rect;
	ENEMY(int type) {
		TYPE = type;
		freeze = 0;
		rect.w = 90;
		rect.h = 90;
		rect.x = 0;
		rect.y = 70 + 5 * 90;
		nowx = rect.x;
		nowy = rect.y;
		CanFly = false;
		dir = RIGHT;
		current_phase = 0;
		pos = { 0,5 };
		switch (type) {
		case 0: {
			hp = 1000000;
			speed = 0;
			money = 1000000;
			break;
		}
		case 1: {  //Light_Soldier
			hp = 75;
			speed = 1;
			money = 2;
			period = 12;
			break;
		}
		case 2: {  //Heavy_Soldier
			hp = 100;
			speed = 0.75;
			money = 1;
			period = 10;
			break;
		}
		case 3: {  //Light_Tank
			hp = 250;
			speed = 0.5;
			money = 5;
			period = 3;
			break;
		}
		case 4: {  //Heavy_Tank
			hp = 500;
			speed = 0.25;
			money = 10;
			period = 10;
			break;
		}
		}
	}
	bool FindPath(bool move);
};
#endif