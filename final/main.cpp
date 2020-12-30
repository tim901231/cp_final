#include <SDL.h>
#include "SDL_image.h"
#include"SDL_ttf.h"
#include <stdio.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include"tower.h"
#include<vector>
#include"enemy.h"
#include"bullet.h"
#include <iostream>

using namespace std;

//variable
const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 1000;
const int TOWER_WIDTH = 90;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* words;
//map's things
enum gamestatus { play, upgrading };
SDL_Texture* background;
SDL_Texture* light;
SDL_Texture* slow;
SDL_Texture* rocket;
SDL_Texture* user;
const SDL_Rect initiallight = { 1720,910,90,90 };
const SDL_Rect initialslow = { 1720,820,90,90 };
const SDL_Rect initialrocket = { 1720,730,90,90 };
SDL_Rect userrect = { 100,100,400,300 };
SDL_Rect lightrect = { 1720,910,80,80 };
SDL_Rect slowrect = { 1720,820,80,80 };
SDL_Rect rocketrect = { 1720,730,80,80 };
SDL_Point mouse_position;
TTF_Font* gFont = NULL;
class word {
	public:
	int n;
	SDL_Surface* textSurface = NULL;
	SDL_Texture* mTexture = NULL;
	SDL_Color color;
	SDL_Rect quad = { 1720,80,80,80 };
	word(string s, int size, SDL_Color color_) {
		n = size;
		color = color_;
		gFont = TTF_OpenFont("lazy.ttf", size);
		textSurface = TTF_RenderText_Solid(gFont, s.c_str(), color_);
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		SDL_FreeSurface(textSurface);
	}
	void changeword(string s) {
		textSurface = TTF_RenderText_Solid(gFont, s.c_str(), color);
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		SDL_FreeSurface(textSurface);
	}
	void render() {
		SDL_RenderCopy(gRenderer, this->mTexture, NULL, &quad);
		return;
	}
};
bool point_in_rect(SDL_Point p, const SDL_Rect r)
{
	if ((p.x > r.x) && (p.x < r.x + r.w) && (p.y > r.y) && (p.y < r.y + r.h)){
		return true;
	}else{
		return false;
	}
}
//map

//tower's thing
tower*** towers = new tower * *[18];
SDL_Texture* tower_pic[9];
SDL_Rect towerClips[6][32];
SDL_Rect towerClips2[3][8];

//tower

//bullet's thing
SDL_Texture* bullet_pic[3];
vector<bullet*> bullets;
//bullet

//enemy's things
vector<ENEMY*> enemies;
ENEMY* DEFAULT = new ENEMY(0);
SDL_Texture *EnemyTexture[10];  //stands for (L)Light (H)Heavy (S)Soldier (T)Tank
SDL_Rect enemyClips[10][50];
int TotalMoney = 30, cntdown = 0;
//bool **MAP = new bool *[18];
//enemy

//init
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Robo Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadmedia()
{
	SDL_Surface* loadedSurface = IMG_Load("pictures/Light_Gun.png");
	tower_pic[0] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Medium_Gun.png");
	tower_pic[1] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Heavy_Gun.png");
	tower_pic[2] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Light_Rocket_Launcher.png");
	tower_pic[3] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Medium_Rocket_Launcher.png");
	tower_pic[4] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Heavy_Rocket_Launcher.png");
	tower_pic[5] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Basic_Slow_Tower.png");
	tower_pic[6] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Upgraded_Slow_Tower.png");
	tower_pic[7] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Advanced_Slow_Tower3.png");
	tower_pic[8] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/Bullet_Small.png");
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
	SDL_FreeSurface(loadedSurface);
	return true;
}

void close()
{
	//Free loaded images
	for (int i = 0; i < 9; i++)
	{
		SDL_DestroyTexture(tower_pic[i]);
		tower_pic[i] = NULL;
	}
	for (int i = 1; i <= 4; i++) {
		SDL_DestroyTexture(EnemyTexture[i]);
		EnemyTexture[i] = NULL;
	}
	SDL_DestroyTexture(light);
	light = NULL;
	SDL_DestroyTexture(slow);
	slow = NULL;
	SDL_DestroyTexture(rocket);
	rocket = NULL;
	SDL_DestroyTexture(background);
	background = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
void upgrade(int x, int y, tower* old)
{
	int c = old->kind + 1;
	delete towers[x][y];
	towers[x][y] = NULL;
	towers[x][y] = new tower(x, y, c);
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
//	srand(time(NULL));
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
		if (rect.x < 80)  nowx += speed;
		else  if (path.shortest_path.size() > 1) {
			if (path.shortest_path[1] - pos == DIR[RIGHT]) {
				nowx += speed;
				dir = RIGHT;
			}
			if (path.shortest_path[1] - pos == DIR[UP]) {
				nowy -= speed;
				dir = UP;
			}
			if (path.shortest_path[1] - pos == DIR[LEFT]) {
				nowx -= speed;
				dir = LEFT;
			}
			if (path.shortest_path[1] - pos == DIR[DOWN]) {
				nowy += speed;
				dir = DOWN;
			}
			if (abs(rect.x - 80 - pos.X * 90) >= 90 || abs(rect.y - 70 - pos.Y * 90) >= 90) {
				pos = path.shortest_path[1];
			}
		}
		else {
			dir = RIGHT;
			if (rect.x < 1800)  nowx += speed;
			else {
				health -= 1;
				money = 0;
				hp = 0;
			}
		}
		rect.x = int(nowx);
		rect.y = int(nowy);
	}
	return true;
}

int main(int argc, char* args[])
{
	//SDL_Color c = { 0xff,0xff,0xff,0xff };
	//word C("a", 28, c);
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 32; i++)
		{
			towerClips[j][i].x = 70 * (i + 1);
			towerClips[j][i].y = 0;
			towerClips[j][i].w = 70;
			towerClips[j][i].h = 70;
		}
	}
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			towerClips2[j][i].x = 70 * (i + 1);
			towerClips2[j][i].y = 0;
			towerClips2[j][i].w = 70;
			towerClips2[j][i].h = 70;
		}
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
	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		//Load media
		LoadEnemyMedia();
		if (!loadmedia()) {
			printf("Failed to load media!\n");
		}
		else {
			//Main loop flag
			int p, q, tempx, tempy;
			bool quit = false;
			bool lightflag = false;
			bool slowflag = false;
			bool rocketflag = false;
			//Event handler
			SDL_Event e;
			gamestatus status = play;
			SDL_Color wordcolor = { 0000,0000,0000,0000 };
			string money = to_string(TotalMoney); //convert int to string
			word currmoney(money, 28, wordcolor);
			int count = 0;
			//While application is running
			while (!quit) {
				count += 1;
				money = to_string(TotalMoney);
				currmoney.changeword(money);
				SDL_SetTextureBlendMode(light, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(light, 255);
				SDL_SetTextureBlendMode(slow, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(slow, 255);
				SDL_SetTextureBlendMode(rocket, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(rocket, 255);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				SDL_RenderCopy(gRenderer, background, NULL, NULL);
				SDL_RenderCopy(gRenderer, light, NULL, &initiallight);
				SDL_RenderCopy(gRenderer, slow, NULL, &initialslow);
				SDL_RenderCopy(gRenderer, rocket, NULL, &initialrocket);
				//If there is no enemy in vector, generate five everytime cntdown is divisible by 10
				if (enemies.empty() && !cntdown) {
					cntdown = 401;
				}

				if (cntdown) {
					if ((-- cntdown) % 100 == 0)  enemies.push_back(Generate_Enemy());
				//	cout << cntdown << ' ' << enemies.size() << '\n';
				}

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					//User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)  quit = true;
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
						if (status == play)
						{
							p = (mouse_position.x - 80) / 90;
							q = (mouse_position.y - 70) / 90;
							if ((lightflag == true || slowflag == true || rocketflag == true))//building mode
							{
								if (p < 18 && p >= 0 && q < 10 && q >= 0) {//check
									if (lightflag == true) {
										if (towers[p][q] == NULL)
										{
											towers[p][q] = new tower(p, q, 0);
										}
										lightflag = false;
									}
									if (slowflag == true) {
										if (towers[p][q] == NULL)
										{
											towers[p][q] = new tower(p, q, 6);
										}
										slowflag = false;
									}
									if (rocketflag == true) {
										if (towers[p][q] == NULL)
										{
											towers[p][q] = new tower(p, q, 3);
										}
										rocketflag = false;
									}
								}
							}
							else {//mutiple funtion
								if (point_in_rect(mouse_position, initiallight) == true)
								{
									lightflag = true;
								}
								else if (point_in_rect(mouse_position, initialslow) == true)
								{
									slowflag = true;
								}
								else if (point_in_rect(mouse_position, initialrocket) == true)
								{
									rocketflag = true;
								}
								else if (p < 18 && p >= 0 && q < 10 && q >= 0)
								{
									if (towers[p][q] != NULL) //trying to upgrade or remove
									{
										tempx = p;
										tempy = q;
										status = upgrading;
									}
								}
							}
						}
						else if (status == upgrading)
						{
							if (point_in_rect(mouse_position, userrect))
							{
								if (mouse_position.x < (userrect.x + 200)) //asking to upgrade
								{
									if (towers[tempx][tempy]->kind != 2 && towers[tempx][tempy]->kind != 5 && towers[tempx][tempy]->kind != 8) {
										upgrade(tempx, tempy, towers[tempx][tempy]);
										//printf("%d", towers[tempx][tempy]->kind);
										status = play;
									}
								}
								else //sell
								{
									delete towers[tempx][tempy];
									towers[tempx][tempy] = NULL;
									status = play;
								}
							}
						}
					}
				}
				/*unfreeze
				for (int i = 0; i < enemies.size(); i++) {
					enemies[i]->freeze = false;
				}
				//this is handled in enemy.h
				*/
				//tower motion
				for (int i = 0; i < 18; i++) {
					for (int j = 0; j < 10; j++) {
						if (towers[i][j] != NULL) {
							//render tower
							if (towers[i][j]->kind < 6) {
								for (int k = 0; k < enemies.size(); k++) {
									if (towers[i][j]->inrange(enemies[k]) == 1)
									{
										//printf("%d\n", count);
										towers[i][j]->rotate(enemies[k]);
										if (towers[i][j]->ableatk(SDL_GetTicks()) == 1) {
											//make a bullet
											bullet* x = new bullet(towers[i][j], enemies[k]);
											bullets.push_back(x);
											break;
										}
									}
								}
								SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerClips[towers[i][j]->kind][towers[i][j]->theta], &towers[i][j]->quad);
							}
							else if(towers[i][j]->kind>=6){//slow tower
								for (int k = 0; k < enemies.size(); k++) {
									if (towers[i][j]->inrange(enemies[k]))
									{
										enemies[k]->freeze = towers[i][j]->atk;
									}
								}
								//printf("%d\n", count);
								towers[i][j]->theta += 1;
								if (towers[i][j]->theta > 7)towers[i][j]->theta -= 8;
								SDL_RenderCopy(gRenderer, tower_pic[towers[i][j]->kind], &towerClips2[towers[i][j]->kind - 6][towers[i][j]->theta], &towers[i][j]->quad);
							}
						}
					}
				}
				//bullets motion
				for (int i = bullets.size() - 1; i >= 0; i--) {
					bullets[i]->move();
					if (bullets[i]->x > 1680 || bullets[i]->x < 40 || bullets[i]->y>1000 || bullets[i]->y < 0) {
						delete bullets[i];
						bullets[i] = NULL;
						bullets.erase(bullets.begin() + i);
						continue;
					}
					for (int j = 0; j < enemies.size(); j++) {
						if (bullets[i]->touch(enemies[j])) {
							enemies[j]->hp -= bullets[i]->atk;//
							delete bullets[i];
							bullets[i] = NULL;
							bullets.erase(bullets.begin() + i);
							break;
						}
					}
					
				}
				for (int i = 0; i < bullets.size(); i++) {
					SDL_RenderCopy(gRenderer, bullet_pic[bullets[i]->kind], NULL, &bullets[i]->quad);
				}
				//enemies motion
				vector<ENEMY*> eliminate_dead_enemy = enemies;
				enemies.clear();
				for (auto enemy : eliminate_dead_enemy) {
					if (enemy->hp > 0) {
						enemies.push_back(enemy);
					}
					else  TotalMoney += enemy->money;  //earn money when an enemy is killed
				}

				for (auto enemy : enemies) {
					enemy->FindPath(1);
					enemy->current_phase += 0.2;
//					cout << enemy->rect.x << ' ' << enemy->rect.y << ' ' << enemy->FindPath(0) << '\n';
					SDL_RenderCopy(gRenderer, enemy->pic, &enemyClips[enemy->TYPE][enemy->period * enemy->dir + ((int(enemy->current_phase)) % enemy->period)], &enemy->rect);
				}

				//render buttom
				if (lightflag == true)
				{
					SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
					lightrect.x = mouse_position.x - 45;//
					lightrect.y = mouse_position.y - 45;
					SDL_SetTextureBlendMode(light, SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(light, 192); //3/4 transparent
					SDL_RenderCopy(gRenderer, light, NULL, &lightrect);
				}
				if (slowflag == true)
				{
					SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
					slowrect.x = mouse_position.x - 45;
					slowrect.y = mouse_position.y - 45;
					SDL_SetTextureBlendMode(slow, SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(slow, 192);
					SDL_RenderCopy(gRenderer, slow, NULL, &slowrect);
				}
				if (rocketflag == true)
				{
					SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
					rocketrect.x = mouse_position.x - 45;
					rocketrect.y = mouse_position.y - 45;
					SDL_SetTextureBlendMode(rocket, SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(rocket, 192);
					SDL_RenderCopy(gRenderer, rocket, NULL, &rocketrect);
				}
				if (status == upgrading) {
					userrect.x = 90*tempx + 35;
					userrect.y = 90*tempy + 25;
					SDL_RenderCopy(gRenderer, user, NULL, &userrect);
				}
				currmoney.render();

				SDL_RenderPresent(gRenderer);
			}
		}
	}
	return 0;
}

//making tower
//towers[i][j] = new tower(x,y,kind);
//destroy tower
//delete towers[i][j];
//towers[i][j]=NULL;

