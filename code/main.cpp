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
		data_init();
		
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
			bullet_motion();
			if (StartButtonPressed) {
				enemy_motion();
			}			
			show_building();
			change_data_size();
			show_option_list();
			SDL_RenderPresent(gRenderer);
			endtime = SDL_GetTicks();
			if (endtime - startime < period) {
				SDL_Delay(period + startime - endtime);
			}
		}
		end_motion();
	}
	close();
	return 0;
}

