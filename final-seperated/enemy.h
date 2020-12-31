#ifndef ENEMY_H
#define ENEMY_H

#include <queue>
#include <utility>
#include<SDL.h>
#include<vector>

using namespace std;
typedef pair<int,int> pii;

const int RIGHT = 0;
const int UP = 1;
const int LEFT = 2;
const int DOWN = 3;

#define X first
#define Y second

//extern int health;
const int MAX_HEALTH[10] = {1000000, 30, 120, 700, 2000, 6000, 500, 1000, 500, 4000};
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
	bool CanFly, wtflag;
	int TYPE, hp, pos, dir, money, period;
	double speed, freeze, nowx, nowy, current_phase;
	vector<pii> PATH;
	SDL_Texture *pic;
	SDL_Rect rect, green, red;
	ENEMY(int type);
	bool FindPath();
	void GoPath();
	void calculate_hp();
};
void LoadEnemyMedia();
ENEMY* Generate_Enemy();
ENEMY* Generate_Enemy(pii pos);
#endif