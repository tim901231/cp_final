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
				if (!StartButtonPressed)  TotalMoney += 5;
				else  TotalMoney += 3;
				for (auto enemy : enemies) {
					if(!enemy->CanFly)  enemy->FindPath(0);
				}
			}
			else if (towers[tempx][tempy]->kind == 6 || towers[tempx][tempy]->kind == 7) { //Slowgun sell
				if (!StartButtonPressed)  TotalMoney += 10;
				else  TotalMoney += 7;
				for (auto enemy : enemies) {
					if(!enemy->CanFly)  enemy->FindPath(0);
				}
			}
			else if (towers[tempx][tempy]->kind == 3 || towers[tempx][tempy]->kind == 4) { //Rocket sell
				if (!StartButtonPressed)  TotalMoney += 20;
				else  TotalMoney += 12;
				for (auto enemy : enemies) {
					if(!enemy->CanFly)  enemy->FindPath(0);
				}
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
	//buy pic
	SDL_Surface* loadedSurface = IMG_Load("pictures/upgrade_medium_gun.png");
	upgradeorsell[0] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_heavy_gun.png");
	upgradeorsell[1] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_light_antiair.png");
	upgradeorsell[2] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_heavy_antiair.png");
	upgradeorsell[3] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_upgraded_slow.png");
	upgradeorsell[4] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_heavy_slow.png");
	upgradeorsell[5] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_unarmed_teleport.png");
	upgradeorsell[6] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_armed_teleport.png");
	upgradeorsell[7] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_medium_rocket.png");
	upgradeorsell[8] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_heavy_rocket.png");
	upgradeorsell[9] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_artillery.png");
	upgradeorsell[10] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/upgrade_mortar.png");
	upgradeorsell[11] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	//sell pic
	loadedSurface = IMG_Load("pictures/sell_light_gun.png");
	upgradeorsell[12] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_medium_gun.png");
	upgradeorsell[13] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_heavy_gun.png");
	upgradeorsell[14] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_light_slow.png");
	upgradeorsell[15] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_medium_slow.png");
	upgradeorsell[16] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_heavy_slow.png");
	upgradeorsell[17] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_light_rocket.png");
	upgradeorsell[18] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_medium_rocket.png");
	upgradeorsell[19] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_heavy_rocket.png");
	upgradeorsell[20] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_light_antiair.png");
	upgradeorsell[21] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_heavy_antiair.png");
	upgradeorsell[22] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_teleport.png");
	upgradeorsell[23] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_artillery.png");
	upgradeorsell[24] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/sell_mortar.png");
	upgradeorsell[25] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	loadedSurface = IMG_Load("pictures/test_user.png"); // upgrade page:4columns
	user = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	loadedSurface = IMG_Load("pictures/red.png"); // new include
	cancel = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
}