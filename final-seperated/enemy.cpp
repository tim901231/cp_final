#include"enemy.h"
#include"SDL_image.h"
#include"variable.h"
#include<ctime>
pii operator +(const pii& p1, const pii& p2) {
	return { p1.X + p2.X, p1.Y + p2.Y };
}

pii operator -(const pii& p1, const pii& p2) {
	return { p1.X - p2.X, p1.Y - p2.Y };
}

bool check(pii p) {
	return (p.X >= 0 && p.X < 18 && p.Y >= 0 && p.Y < 10);
}
ENEMY::ENEMY(int type) {
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
		hp = 30;
		speed = 1;
		money = 1;
		period = 12;
		break;
	}
	case 2: {  //Heavy_Soldier
		hp = 120;
		speed = 0.75;
		money = 3;
		period = 16;
		break;
	}
	case 3: {  //Light_Tank
		hp = 700;
		speed = 0.5;
		money = 5;
		period = 3;
		break;
	}
	case 4: {  //Heavy_Tank
		hp = 2000;
		speed = 0.25;
		money = 10;
		period = 10;
		break;
	}
	case 5: {  //Titan
		hp = 6000;
		speed = 0.5;
		money = 50;
		period = 10;
	}
	case 6: {  //jet
		hp = 500;
		speed = 1.5;
		money = 10;
		period = 1;
		CanFly = true;
	}
	case 7: {  //Helicopter
		hp = 380;
		speed = 0.75;
		money = 8;
		period = 6;
		CanFly = true;
	}
	case 8: {  //Runner
		hp = 80;
		speed = 2;
		money = 2;
		period = 12;
	}
	case 9: {  //MotherShip
		hp = 1000;
		speed = 0.5;
		money = 30;
		period = 1;
		CanFly = true;
	}
	}
}
void ENEMY::calculate_hp() {
	green.w = hp / MAX_HEALTH[TYPE];
	green.h = 10;
	red.w = 90 - green.w;
	red.h = 10;
	green.x = rect.x;
	green.y = rect.y + 90;
	red.x = green.x + green.w;
	red.y = green.y;
}
void LoadEnemyMedia() {
	SDL_Surface* surface;
	surface = IMG_Load("pictures/Light_Soldier.png");
	EnemyTexture[1] = SDL_CreateTextureFromSurface(gRenderer, surface);
	surface = IMG_Load("pictures/Heavy_Soldier.png");
	EnemyTexture[2] = SDL_CreateTextureFromSurface(gRenderer, surface);
	surface = IMG_Load("pictures/Light_Tank.png");
	EnemyTexture[3] = SDL_CreateTextureFromSurface(gRenderer, surface);
	surface = IMG_Load("pictures/Heavy_Tank.png");
	EnemyTexture[4] = SDL_CreateTextureFromSurface(gRenderer, surface);
	SDL_FreeSurface(surface);
	for (int i = 1; i <= 4; i++) {
		if (i == 1) {
			for (int j = 0; j < 48; j++) {
				enemyClips[i][j].x = 70 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 70;
				enemyClips[i][j].h = 70;
			}
		}
		else  if (i == 2) {
			for (int j = 0; j < 40; j++) {
				enemyClips[i][j].x = 70 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 70;
				enemyClips[i][j].h = 140;
			}
		}
		else  if (i == 3) {
			for (int j = 0; j < 12; j++) {
				enemyClips[i][j].x = 70 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 70;
				enemyClips[i][j].h = 70;
			}
		}
		else {
			for (int j = 0; j < 40; j++) {
				enemyClips[i][j].x = 70 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 70;
				enemyClips[i][j].h = 70;
			}
		}
	}
}
ENEMY* Generate_Enemy() {
	srand(time(NULL));
	int type = rand() % 4 + 1;
	ENEMY* ret = new ENEMY(type);
	ret->pic = EnemyTexture[type];
	return ret;
}
bool ENEMY::FindPath(bool move) {  //return false if there isn't any path
	queue<val> q;
	bool visited[18][10] = {}, exist_path = false;
	val start, path;
	start.pos = pos;
	start.shortest_path.push_back(pos);
	q.push(start);
	visited[pos.X][pos.Y] = true;
	while (!q.empty()) {
		path = q.front();
		q.pop();
		if (path.pos == make_pair(17, 5)) {
			exist_path = true;
			break;
		}
		for (int i = 0; i < 4; i++) {
			if (check(path.pos + DIR[i]) && !visited[path.pos.X + DIR[i].X][path.pos.Y + DIR[i].Y] && !towers[path.pos.X + DIR[i].X][path.pos.Y + DIR[i].Y]) {
				visited[path.pos.X + DIR[i].X][path.pos.Y + DIR[i].Y] = true;
				val tmp = path;
				tmp.pos = path.pos + DIR[i];
				tmp.shortest_path.push_back(tmp.pos);
				q.push(tmp);
			}
		}
	}
	if (!exist_path)  return false;
	else if (move) {
		if (rect.x < 80)  nowx += speed * (1 - freeze / 100) * speedy;
		else  if (path.shortest_path.size() > 1) {
			if (path.shortest_path[1] - pos == DIR[RIGHT]) {
				nowx += speed * (1 - freeze / 100) * speedy;
				dir = RIGHT;
			}
			if (path.shortest_path[1] - pos == DIR[UP]) {
				nowy -= speed * (1 - freeze / 100) * speedy;
				dir = UP;
			}
			if (path.shortest_path[1] - pos == DIR[LEFT]) {
				nowx -= speed * (1 - freeze / 100) * speedy;
				dir = LEFT;
			}
			if (path.shortest_path[1] - pos == DIR[DOWN]) {
				nowy += speed * (1 - freeze / 100) * speedy;
				dir = DOWN;
			}
			if (abs(rect.x - 80 - pos.X * 90) >= 90 || abs(rect.y - 70 - pos.Y * 90) >= 90) {
				pos = path.shortest_path[1];
			}
		}
		else {
			dir = RIGHT;
			if (rect.x < 1800)  nowx += speed * (1 - freeze / 100) * speedy;
			else {
				TotalLife -= 1;
				money = 0;
				hp = 0;
			}
		}
		rect.x = int(nowx);
		rect.y = int(nowy);
	}
	return true;
}