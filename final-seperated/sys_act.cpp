#include"sys_act.h"
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
bool point_in_rect(SDL_Point p, const SDL_Rect r)
{
	if ((p.x > r.x) && (p.x < r.x + r.w) && (p.y > r.y) && (p.y < r.y + r.h)) {
		return true;
	}
	else {
		return false;
	}
}
void upgrade_act() {
	if (point_in_rect(mouse_position, userrect))
	{
		if (mouse_position.x < (userrect.x + 200)) //asking to upgrade
		{
			if (towers[tempx][tempy]->kind == 0 || towers[tempx][tempy]->kind == 1) { //Lightgun upgrade
				if (TotalMoney >= 4)
				{
					TotalMoney -= 4;
					upgrade(tempx, tempy, 2, loop);
					status = play;
				}
			}
			else if (towers[tempx][tempy]->kind == 6 || towers[tempx][tempy]->kind == 7) { //Slowgun upgrade
				if (TotalMoney > 15)
				{
					TotalMoney -= 15;
					upgrade(tempx, tempy, 8, loop);
					status = play;
				}
			}
			else if (towers[tempx][tempy]->kind == 3 || towers[tempx][tempy]->kind == 4) { //Rocket upgrade
				if (TotalMoney > 30)
				{
					TotalMoney -= 30;
					upgrade(tempx, tempy, 5, loop);
					status = play;
				}
			}
		}
		else //sell
		{
			if (towers[tempx][tempy]->kind == 0 || towers[tempx][tempy]->kind == 1) { //Lightgun sell
				TotalMoney += 3;
			}
			else if (towers[tempx][tempy]->kind == 6 || towers[tempx][tempy]->kind == 7) { //Slowgun sell
				TotalMoney += 7;
			}
			else if (towers[tempx][tempy]->kind == 3 || towers[tempx][tempy]->kind == 4) { //Rocket sell
				TotalMoney += 12;
			}
			delete towers[tempx][tempy];
			towers[tempx][tempy] = NULL;
			status = play;
		}
	}
}
void show_building() {
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
		userrect.x = 90 * tempx + 35;
		userrect.y = 90 * tempy + 25;
		SDL_RenderCopy(gRenderer, user, NULL, &userrect);
	}
}
void loadothermedia() {
	SDL_Surface* loadedSurface = IMG_Load("pictures/test_user.png"); // new include
	user = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/red.png"); // new include
	cancel = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
}