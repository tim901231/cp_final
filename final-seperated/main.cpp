#include <SDL.h>
#include "SDL_image.h"
#include"SDL_ttf.h"
#include <stdio.h>
#include <string>
#include <ctime>
#include<cmath>
#include <cstdlib>
#include"tower.h"
#include<vector>
#include"enemy.h"
#include"bullet.h"
#include <iostream>
#include "wave.h"
#include"variable.h"
#include"word.h"
#include"sys_act.h"
#include"menu.h"
#include"option_list.h"
using namespace std;
int digit(int);
void close()
{
	//Free loaded images
	
	for (int i = 0; i < 7;  i++) {
		SDL_DestroyTexture(bottoms_pic[i]);
		bullet_pic[i] = NULL;
	}
	SDL_DestroyTexture(option_bottom_pic);
	option_bottom_pic = NULL;
	for (int i = 0; i < 3; i++) {
		SDL_DestroyTexture(bullet_pic[i]);
		bullet_pic[i] = NULL;
	}
	for (int i = 0; i < 26; i++) {
		SDL_DestroyTexture(upgradeorsell[i]);
		upgradeorsell[i] = NULL;
	}
	for (int i = 0; i < 15; i++)
	{
		SDL_DestroyTexture(tower_pic[i]);
		tower_pic[i] = NULL;
	}
	for (int i = 1; i < 10; i++) {
		SDL_DestroyTexture(EnemyTexture[i]);
		EnemyTexture[i] = NULL;
	}
	SDL_DestroyTexture(startbutton);
	startbutton = NULL;
	SDL_DestroyTexture(startpage);
	startpage = NULL;
	SDL_DestroyTexture(startturning1);
	startturning1 = NULL;
	SDL_DestroyTexture(startturning2);
	startturning2 = NULL;
	SDL_DestroyTexture(startturning3);
	startturning3 = NULL;
	SDL_DestroyTexture(title);
	title = NULL;
	SDL_DestroyTexture(light);
	light = NULL;
	SDL_DestroyTexture(slow);
	slow = NULL;
	SDL_DestroyTexture(rocket);
	rocket = NULL;
	SDL_DestroyTexture(user);
	user = NULL;
	SDL_DestroyTexture(cancel);
	cancel = NULL;
	SDL_DestroyTexture(Green);
	Green = NULL;
	SDL_DestroyTexture(Red);
	Red = NULL;
	SDL_DestroyTexture(background);
	background = NULL;
	TTF_CloseFont(gFont);
	gFont = NULL;
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


int main(int argc, char* args[])
{
	tower_init();
	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		//Load media
		LoadEnemyMedia();
		loadbottommedia();
		loadmenumedia();
		loadtowermedia();
		loadbulletmedia();
		loadothermedia();
		Enemy_Queue_INIT();
		upgrade_list_init();

		string life = "Life: " + to_string(TotalLife);
		string wave = "Wave: " + to_string(currentwave);
		string money = "$: " + to_string(TotalMoney);
		string score = "Score: " + to_string(currentscore);
		word* currmoney = new word(money, 18, wordcolor);
		word currlife(life, 18, wordcolor);
		word currwave(wave, 18, wordcolor);
		word SCORE(score, 18, wordcolor);
		currlife.quad.y = 60; currlife.quad.w = 120;
		currwave.quad.y = 20; currwave.quad.w = 120;
		SCORE.quad.x = 10, SCORE.quad.y = 10; SCORE.quad.w = 140;
		int startime;
		int endtime;
		int period=8;

		while (!quit) {
			startime = SDL_GetTicks();
			if (status == menu) {
				set_everything_zero();	
				menu_act();
			}		
			loop += 1;
			currmoney->changeword("$: " + to_string(TotalMoney));
			currlife.changeword("Life: " + to_string(TotalLife));
			currwave.changeword("Wave: " + to_string(currentwave));
			SCORE.changeword("Score: " + to_string(currentscore));
			render_botton();

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0) {
				//User requests quit
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)  quit = true;
				if (e.type == SDL_MOUSEMOTION) 
				{
					animation();
				}
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					click_motion();
				}
			}
			tower_motion();
			//bullets motion
			bullet_motion();
			if (StartButtonPressed) {
				enemy_motion();
			}
			
			show_building();
			if (TotalMoney < 10) //Change font rectangle
			{
				currmoney->quad.w = 70;
			}
			else if (TotalMoney >= 100)
			{
				currmoney->quad.w = 130;
			}
			else if (TotalMoney >= 10 && TotalMoney < 100)
			{
				currmoney->quad.w = 100;
			}
			//render option things
			if (currentwave < 10)
			{
				currwave.quad.w = 120;
			}
			else {
				currwave.quad.w = 150;
			}
			if (currentscore < 10) {
				SCORE.quad.w = 120;
			}
			else if (currentscore < 100) {
				SCORE.quad.w = 150;
			}
			else if (currentscore < 1000) {
				SCORE.quad.w = 180;
			}
			else {
				SCORE.quad.w = 210;
			}
			SDL_RenderCopy(gRenderer, option_bottom_pic, NULL, &option_bottom);
			show_option_list();
			currmoney->render();
			currlife.render();
			currwave.render();
			SCORE.render();
			SDL_RenderPresent(gRenderer);
			endtime = SDL_GetTicks();
			//printf("%d\n", endtime - startime);
			if (endtime - startime < period) {
				SDL_Delay(period + startime - endtime);
			}
		}
		if (currentwave == 100 && TotalLife > 0)  background = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("pictures/victory.jpg"));
		else  background = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("pictures/GameOver.png"));
		int num = loadLeaderboard();
		word** rank_id = new word*[5];
		for (int i = 0; i < 5; i++) {
			rank_id[i] = new word(id[i],18,wordcolor);
			rank_id[i]->quad.y = 490 + i * 50;
			rank_id[i]->quad.w = id[i].length() * 30;
			rank_id[i]->quad.x = 870- rank_id[i]->quad.w;
		}
		word** rank_score = new word * [5];
		for (int i = 0; i < 5; i++) {
			rank_score[i] = new word(to_string(scores[i]), 18, wordcolor);
			
			rank_score[i]->quad.y = 490 + i * 50;
			rank_score[i]->quad.w = digit(scores[i]) * 30;
			rank_score[i]->quad.x = 1100-rank_score[i]->quad.w;
		}
		word rank_title("R A N K", 50, wordcolor);
		rank_title.quad.x = 750;
		rank_title.quad.y = 380;
		rank_title.quad.w = 300;
		rank_title.quad.h = 100;
		int time0 = SDL_GetTicks();
		int time1;
		while (quit)
		{
			time1 = SDL_GetTicks();
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT)  quit = false;
				else  if (e.type = SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)  quit = false;
			}
			SDL_RenderCopy(gRenderer, background, NULL, NULL);
			if (time1 - time0 > 3000) {
				SDL_RenderCopy(gRenderer, ranking, NULL, &rank_rect);
				rank_title.render();
				for (int i = 0; i < 5; i++) {
					rank_id[i]->render();
					rank_score[i]->render();
				}
			}
			
			SDL_RenderPresent(gRenderer);
			//cout << id[0] << " " << scores[0] << endl;
		}
	}
	close();
	return 0;
}

int digit(int a) {
	if (a == 0) return 1;
	int c = 0;
	while (a > 0) {
		a = a / 10;
		c += 1;
	}
	return c;
}