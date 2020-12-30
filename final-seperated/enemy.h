#ifndef ENEMY_H
#define ENEMY_H

#include <queue>
#include <utility>
#include<SDL.h>

using namespace std;
typedef pair<int,int> pii;

const int RIGHT = 0;
const int UP = 1;
const int LEFT = 2;
const int DOWN = 3;

#define X first
#define Y second

//extern int health;
const int MAX_HEALTH[10] = {1000000, 15, 30, 50, 100, 0, 0, 0, 0, 0};
const pii DIR[4] = {{1,0}, {0, -1}, {-1, 0}, {0, 1}};

pii operator +(const pii& p1, const pii& p2);

pii operator -(const pii& p1, const pii& p2);

bool check(pii p);

class val{
	public:
		pii pos;
		vector<pair<int, int> > shortest_path;
};

class ENEMY {
public:
	bool CanFly;
	int TYPE, hp, dir, money, period;
	double speed, freeze, nowx, nowy, current_phase;
	pii pos;
	SDL_Texture *pic;
	SDL_Rect rect, green, red;
	ENEMY(int type);
	bool FindPath(bool move);
	void calculate_hp();
};
#endif