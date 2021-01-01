#include"enemy.h"
#include"SDL_image.h"
#include"variable.h"
#include "wave.h"
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
	wtflag = false;
	dir = RIGHT;
	current_phase = 0;
	pos = 0;
	PATH.push_back({ 0,5 });
	switch (type) {
	case 0: {
		hp = 1000000;
		speed = 0;
		money = 1000000;
		break;
	}
	case 1: {  //Light_Soldier
		hp = MAX_HEALTH[TYPE] * rate;
		speed = 1;
		money = 1;
		period = 12;
		break;
	}
	case 2: {  //Heavy_Soldier
		hp = MAX_HEALTH[TYPE] * rate;
		speed = 0.75;
		money = 3;
		period = 16;
		break;
	}
	case 3: {  //Light_Tank
		hp = MAX_HEALTH[TYPE] * rate;
		speed = 0.5;
		money = 5;
		period = 3;
		break;
	}
	case 4: {  //Heavy_Tank
		hp = MAX_HEALTH[TYPE] * rate;
		speed = 0.25;
		money = 10;
		period = 10;
		break;
	}
	case 5: {  //Titan
		hp = MAX_HEALTH[TYPE] * rate;
		speed = 0.5;
		money = 50;
		period = 10;
		break;
	}
	case 6: {  //jet
		hp = MAX_HEALTH[TYPE] * rate;
		speed = 1.5;
		money = 10;
		period = 1;
		CanFly = true;
		break;
	}
	case 7: {  //Helicopter
		hp = MAX_HEALTH[TYPE] * rate;
		speed = 0.75;
		money = 8;
		period = 6;
		CanFly = true;
		break;
	}
	case 8: {  //Runner
		hp = MAX_HEALTH[TYPE] * rate;
		speed = 2;
		money = 2;
		period = 12;
		break;
	}
	case 9: {  //MotherShip
		hp = MAX_HEALTH[TYPE] * rate;
		speed = 0.5;
		money = 30;
		period = 1;
		CanFly = true;
		wtflag = true;
		break;
	}
	}
}
void ENEMY::calculate_hp() {
	green.w = hp * 90 / (MAX_HEALTH[TYPE] * rate);
	green.h = 10;
	red.w = 90 - green.w;
	red.h = 10;
	green.x = rect.x;
	green.y = rect.y + 90;
	red.x = green.x + green.w;
	red.y = green.y;
}
//ENEMY
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
	surface = IMG_Load("pictures/Titan.png");
	EnemyTexture[5] = SDL_CreateTextureFromSurface(gRenderer, surface);
	surface = IMG_Load("pictures/Jet.png");   //
	EnemyTexture[6] = SDL_CreateTextureFromSurface(gRenderer, surface);
	surface = IMG_Load("pictures/Helicopter.png"); //
	EnemyTexture[7] = SDL_CreateTextureFromSurface(gRenderer, surface);
	surface = IMG_Load("pictures/Runner.png");    //
	EnemyTexture[8] = SDL_CreateTextureFromSurface(gRenderer, surface);
	surface = IMG_Load("pictures/Mothership.png");    //
	EnemyTexture[9] = SDL_CreateTextureFromSurface(gRenderer, surface);  //
	surface = IMG_Load("pictures/green.png");
	Green = SDL_CreateTextureFromSurface(gRenderer, surface);
	surface = IMG_Load("pictures/red.png");
	Red = SDL_CreateTextureFromSurface(gRenderer, surface);
	SDL_FreeSurface(surface);
	for (int i = 1; i < 10; i++) {
		if (i == 1) {
			for (int j = 0; j < 48; j++) {
				enemyClips[i][j].x = 70 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 70;
				enemyClips[i][j].h = 70;
			}
		}
		else  if (i == 2) {
			for (int j = 0; j < 64; j++) {
				enemyClips[i][j].x = 70 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 70;
				enemyClips[i][j].h = 70;
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
		else if (i == 4) {
			for (int j = 0; j < 40; j++) {
				enemyClips[i][j].x = 70 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 70;
				enemyClips[i][j].h = 70;
			}
		}
		else if (i == 5) {
			for (int j = 0; j < 40; j++) {
				enemyClips[i][j].x = 70 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 70;
				enemyClips[i][j].h = 140;
			}
		}
		else if (i == 6) {
			for (int j = 0; j < 4; j++) {
				enemyClips[i][j].x = 105 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 105;
				enemyClips[i][j].h = 175;
			}
		}
		else if (i == 7) {
			for (int j = 0; j < 24; j++) {
				enemyClips[i][j].x = 105 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 105;
				enemyClips[i][j].h = 175;
			}
		}
		else if (i == 8) {
			for (int j = 0; j < 48; j++) {
				enemyClips[i][j].x = 70 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 70;
				enemyClips[i][j].h = 70;
			}
		}
		else {
			for (int j = 0; j < 4; j++) {
				enemyClips[i][j].x = 105 * j;
				enemyClips[i][j].y = 0;
				enemyClips[i][j].w = 105;
				enemyClips[i][j].h = 151;
			}
		}
	}
}
ENEMY* Generate_Enemy() {
	ENEMY* ret = new ENEMY(waves[currentwave][num] - '0');
	ret->pic = EnemyTexture[waves[currentwave][num] - '0'];
	++num;
	if (num == waves[currentwave].size()) {
		num = 0;
		++currentwave;
		if (currentwave == 65 || currentwave == 81)  rate *= 2;
	}
	ret->FindPath(ret->CanFly);
	return ret;
}

ENEMY* Generate_Enemy(pii origin) {
	ENEMY* ret = new ENEMY(1);
	ret->pic = EnemyTexture[1];
	ret->rect.x = 80 + 90 * origin.X;
	ret->rect.y = 70 + 90 * origin.Y;
	ret->nowx = ret->rect.x;
	ret->nowy = ret->rect.y;
	ret->PATH.clear();
	ret->PATH.push_back(origin);
	ret->FindPath(0);
	return ret;
}

bool ENEMY::FindPath(bool isair) {  //return false if there isn't any path
	if (isair) {
		PATH.clear();
		pos = 0;
		for (int i = 0; i < 18; i++) {
			PATH.push_back({ i,5 });
		}
		return true;
	}
	queue<val> q;
	val start, path;
	start.pos = PATH[pos];
	start.shortest_path.push_back(start.pos);
	q.push(start);
	bool visited[18][10] = {}, exist_path = false;
	visited[start.pos.X][start.pos.Y] = true;
	while (!q.empty()) {
		path = q.front();
		q.pop();
		if (path.pos == make_pair(17, 5)) {
			exist_path = true;
			PATH.clear();
			PATH = path.shortest_path;
			pos = 0;
			while (!q.empty())  q.pop();
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
	return exist_path;
}
void ENEMY::GoPath() {
	if (rect.x < 80)  nowx += speed * (1 - freeze / 100) * speedy;
	else  if (pos + 1 < PATH.size()) {
		if (PATH[pos + 1] - PATH[pos] == DIR[RIGHT]) {
			nowx += speed * (1 - freeze / 100) * speedy;
			dir = RIGHT;
		}
		if (PATH[pos + 1] - PATH[pos] == DIR[UP]) {
			nowy -= speed * (1 - freeze / 100) * speedy;
			dir = UP;
		}
		if (PATH[pos + 1] - PATH[pos] == DIR[LEFT]) {
			nowx -= speed * (1 - freeze / 100) * speedy;
			if (nowx < 80)  nowx = 80; //this caused a bug
			dir = LEFT;
		}
		if (PATH[pos + 1] - PATH[pos] == DIR[DOWN]) {
			nowy += speed * (1 - freeze / 100) * speedy;
			dir = DOWN;
		}
		if (abs(rect.x - 80 - PATH[pos].X * 90) >= 90 || abs(rect.y - 70 - PATH[pos].Y * 90) >= 90) {
			++ pos;
			if (TYPE == 9 && !towers[PATH[pos].X][PATH[pos].Y] && PATH[pos].X < 17)  wtflag = true;
		}
		if (wtflag) {
			add = Generate_Enemy(PATH[pos]);
			wtflag = false;
		}
	}
	else {
		dir = RIGHT;
		if (rect.x < 1800)  nowx += speed * (1 - freeze / 100) * speedy;
		else {
			TotalLife -= 1;
			if (TotalLife <= 0)  quit = true;
			money = 0;
			hp = 0;
		}
	}
	rect.x = int(nowx);
	rect.y = int(nowy);
	calculate_hp();
//	cout << PATH.size() << ' ' << pos << ' ' << nowx << ' ' << nowy << '\n';
}

void enemy_motion(){
	if (enemies.empty() && !cntdown) {
		if (currentwave == 100) {
			quit = true;
			return ;
		}
		cntdown = (waves[currentwave].size() - 1) * 50 + 1;
	}

	if (cntdown) {
		if ((--cntdown) % 50 == 0)  enemies.push_back(Generate_Enemy());
		//	cout << cntdown << ' ' << enemies.size() << '\n';
	}
	vector<ENEMY*> eliminate_dead_enemy = enemies;
	enemies.clear();
	for (auto enemy : eliminate_dead_enemy) {
		if (enemy->hp > 0) {
			enemies.push_back(enemy);
		}
		else {
			TotalMoney += enemy->money;  //earn money when an enemy is killed
		}
	}
	eliminate_dead_enemy.clear();
	for (auto enemy : enemies) {
		enemy->GoPath();
		if (enemy->freeze)  --enemy->freeze;
		enemy->current_phase += 0.2;
		SDL_RenderCopy(gRenderer, enemy->pic, &enemyClips[enemy->TYPE][enemy->period * enemy->dir + (int(enemy->current_phase) % enemy->period)], &enemy->rect);
		SDL_RenderCopy(gRenderer, Green, NULL, &enemy->green);
		SDL_RenderCopy(gRenderer, Red, NULL, &enemy->red);
	}
	if (add) {
		enemies.push_back(add);
		add = NULL;
	}
}