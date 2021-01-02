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
		word* currmoney = new word(money, 18, wordcolor);
		word currlife(life, 18, wordcolor);
		word currwave(wave, 18, wordcolor);
		currlife.quad.y = 60; currlife.quad.w = 120;
		currwave.quad.y = 20; currwave.quad.w = 120;
		int startime;
		int endtime;
		int period=10;

		while (!quit) {
			startime = SDL_GetTicks();
			if (status == menu) {
				loop = 0;
				currentwave = 0;
				TotalMoney = 30; //
				TotalLife = 24;
				for (int i = 0; i < 18; i++) {
					for (int j = 0; j < 10; j++) {
						delete towers[i][j];
						towers[i][j] = NULL;
						
					}
				}
				//wave also need reset
				bullets.clear();
				enemies.clear();
			}
			if (status == menu) menu_act();
			
			loop += 1;
			currmoney->changeword("$: " + to_string(TotalMoney));
			currlife.changeword("Life: " + to_string(TotalLife));
			currwave.changeword("Wave: " + to_string(currentwave));
			SDL_SetTextureBlendMode(light, SDL_BLENDMODE_BLEND);
			SDL_SetTextureBlendMode(slow, SDL_BLENDMODE_BLEND);
			SDL_SetTextureBlendMode(rocket, SDL_BLENDMODE_BLEND);
			if (TotalMoney >= 5){
				SDL_SetTextureAlphaMod(light, 255);
			}else{
				SDL_SetTextureAlphaMod(light, 128);
			}
			if (TotalMoney >= 10) {
				SDL_SetTextureAlphaMod(slow, 255);
			}
			else {
				SDL_SetTextureAlphaMod(slow, 128);
			}
			if (TotalMoney >= 20) {
				SDL_SetTextureAlphaMod(rocket, 255);
			}
			else {
				SDL_SetTextureAlphaMod(rocket, 128);
			}
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);
			SDL_RenderCopy(gRenderer, background, NULL, NULL);
			SDL_RenderCopy(gRenderer, light, NULL, &initiallight);
			SDL_RenderCopy(gRenderer, slow, NULL, &initialslow);
			SDL_RenderCopy(gRenderer, rocket, NULL, &initialrocket);
			SDL_RenderCopy(gRenderer, cancel, NULL, &cancel_rect);
			if (!StartButtonPressed) {
				SDL_RenderCopy(gRenderer, startbottom_pic, NULL, &StartButton);
			}

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0) {
				//User requests quit
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)  quit = true;
				if (e.type == SDL_MOUSEMOTION) 
				{
					SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
					if (status == play)
					{
						if (point_in_rect(mouse_position, option_bottom) == true) {
							option_bottom.x = 0;
							option_bottom.y = 940;
							option_bottom.w = 70;
							option_bottom.h = 70;
						}
						else {
							option_bottom.x = 10;
							option_bottom.y = 950;
							option_bottom.w = 50;
							option_bottom.h = 50;
						}
					}
					else if (status == option) {
						if (point_in_rect(mouse_position, bottoms[1]) == true) { //pause
							bottoms[1].x = 680;
							bottoms[1].y = 380;
							bottoms[1].w = 120;
							bottoms[1].h = 120;
						}
						else {
							bottoms[1].x = 690;
							bottoms[1].y = 390;
							bottoms[1].w = 100;
							bottoms[1].h = 100;
						}

						if (point_in_rect(mouse_position, bottoms[2]) == true) { //start
							bottoms[2].x = 850;
							bottoms[2].y = 380;
							bottoms[2].w = 120;
							bottoms[2].h = 120;
						}
						else {
							bottoms[2].x = 860;
							bottoms[2].y = 390;
							bottoms[2].w = 100;
							bottoms[2].h = 100;
						}
						if (point_in_rect(mouse_position, bottoms[3]) == true) {
							bottoms[3].x = 1020;
							bottoms[3].y = 380;
							bottoms[3].w = 120;
							bottoms[3].h = 120;
						}
						else {
							bottoms[3].x = 1030;
							bottoms[3].y = 390;
							bottoms[3].w = 100;
							bottoms[3].h = 100;
						}
						//mute=4
						//back5
						//exit 6

					}
				}
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
					if (!StartButtonPressed && abs(mouse_position.x - 125) <= 45 && abs(mouse_position.y - 565) <= 45) {
						StartButtonPressed = true;
					}
					if (status == play)
					{
						if (mouse_position.x < 80) {
							p = -1;
						}
						else if (mouse_position.y < 70) {
							q = -1;
						}
						else {
							p = (mouse_position.x - 80) / 90;

							q = (mouse_position.y - 70) / 90;
						}
							
						if ((lightflag == true || slowflag == true || rocketflag == true))//building mode
						{
							if (point_in_rect(mouse_position, cancel_rect) == true) {
								lightflag = false;
								slowflag = false;
								rocketflag = false;
							}
							if (point_in_rect(mouse_position, initiallight) == true)
							{
								if (TotalMoney >= 5)
								{
									lightflag = true;
									slowflag = false;
									rocketflag = false;
								}
							}
							if (point_in_rect(mouse_position, initialslow) == true)
							{
								if (TotalMoney >= 10)
								{
									slowflag = true;
									lightflag = false;
									rocketflag = false;
								}
							}
							if (point_in_rect(mouse_position, initialrocket) == true)
							{
								if (TotalMoney >= 20)
								{
									rocketflag = true;
									lightflag = false;
									slowflag = false;
								}
							}
							if (check({p, q})) {//check
								if (towers[p][q] == NULL) {
									towers[p][q] = test;
									canBuild = DEFAULT->FindPath(0);
									for (auto enemy : enemies) {
										if(!enemy->CanFly)  canBuild &= enemy->FindPath(0);
									}
									towers[p][q] = NULL;
									if (p == 0 && q == 5)  canBuild = false;
								}
								if (lightflag == true && canBuild) {
									if (towers[p][q] == NULL)
									{
										TotalMoney -= 5;
										towers[p][q] = new tower(p, q, 0, loop);
									}
									lightflag = false;
								}
								if (slowflag == true) {
									if (towers[p][q] == NULL && canBuild)
									{
										TotalMoney -= 10;
										towers[p][q] = new tower(p, q, 10, loop);
									}
									slowflag = false;
								}
								if (rocketflag == true && canBuild) {
									if (towers[p][q] == NULL)
									{
										TotalMoney -= 20;
										towers[p][q] = new tower(p, q, 5, loop);
									}
									rocketflag = false;
								}
							}
						}
						else {//mutiple funtion
							if (point_in_rect(mouse_position, initiallight) == true)
							{
								if (TotalMoney >= 5)
								{
									lightflag = true;
								}
							}
							else if (point_in_rect(mouse_position, initialslow) == true)
							{
								if (TotalMoney >= 10)
								{
									slowflag = true;
								}
							}
							else if (point_in_rect(mouse_position, initialrocket) == true)
							{
								if (TotalMoney >= 20)
								{
									rocketflag = true;
								}
							}
							else if (p < 18 && p >= 0 && q < 10 && q >= 0)
							{
								if (towers[p][q] != NULL) //trying to upgrade or remove
								{
									tempx = p;
									tempy = q;
									status = upgrading;
									change_upgrade();
								}
							}
							else if (point_in_rect(mouse_position, option_bottom) == true) {
								status = option;
							}
						}
					}
					else if (status == upgrading)
					{
						upgrade_act();
					}
					else if (status == option) {
						option_act();
					}
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
			SDL_RenderCopy(gRenderer, option_bottom_pic, NULL, &option_bottom);
			show_option_list();
			currmoney->render();
			currlife.render();
			currwave.render();
			SDL_RenderPresent(gRenderer);
			endtime = SDL_GetTicks();

			if (endtime - startime < period) {
				SDL_Delay(period + startime - endtime);
			}
		}
		if (currentwave == 100 && TotalLife > 0)  background = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("pictures/victory.jpg"));
		else  background = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("pictures/GameOver.png"));
		while (quit)
		{
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT)  quit = false;
				else  if (e.type = SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)  quit = false;
			}
			SDL_RenderCopy(gRenderer, background, NULL, NULL);
			SDL_RenderPresent(gRenderer);
		}
	}
	close();
	return 0;
}

