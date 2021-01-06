#include"menu.h"
void menu_act(){
	while (status == menu) {
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
				status = play;
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
				startflag = false;
				if (point_in_rect(mouse_position, turning1))
				{
					startflag = true;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
				if (point_in_rect(mouse_position, turning1))
				{
					status = play;
				}
			}
		}
		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, startpage, NULL, NULL);

		if (startflag == true)
		{
			SDL_RenderCopyEx(gRenderer, startturning3, NULL, &turning3, degrees, NULL, flipType);
			SDL_RenderCopyEx(gRenderer, startturning1, NULL, &turning1, 1.3 * degrees, NULL, flipType);
			SDL_RenderCopyEx(gRenderer, startturning2, NULL, &turning2, -1.6 * degrees, NULL, flipType);
			degrees += 1;
		}
		else
		{
			SDL_RenderCopyEx(gRenderer, startturning3, NULL, &turning3, degrees, NULL, flipType);
			SDL_RenderCopyEx(gRenderer, startturning1, NULL, &turning1, 1.3 * degrees, NULL, flipType);
			SDL_RenderCopyEx(gRenderer, startturning2, NULL, &turning2, -1.6 * degrees, NULL, flipType);
			degrees += 0.1;
		}
		SDL_RenderCopy(gRenderer, startbutton, NULL, &turning1);
		SDL_RenderCopy(gRenderer, title, NULL, &titlerect);
		SDL_RenderPresent(gRenderer);
	}
}
void loadmenumedia()
{
	SDL_Surface* loadedSurface = IMG_Load("pictures/startbutton.png");
	startbutton = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/startpage.png");
	startpage = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/startturning1.png");
	startturning1 = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/startturning2.png");
	startturning2 = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/startturning3.png");
	startturning3 = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/title.png");
	title = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
	//return true;
}
void set_everything_zero() {
	loop = 0;
	currentwave = 0;
	TotalMoney = 500; //
	TotalLife = 24;
	currentscore = 0;
	StartButtonPressed = false;
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