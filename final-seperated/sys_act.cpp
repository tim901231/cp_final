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

void upgrade_list_init() {
	for (int i = 0; i < 3; i++) {
		putlist[i] = NULL;
	}
	upgradelist[0].x = 361;
	upgradelist[0].y = 193;
	upgradelist[1].x = 910;
	upgradelist[1].y = 193;
	upgradelist[2].x = 361;
	upgradelist[2].y = 505;
	for (int i = 0; i < 3; i++) {
		upgradelist[i].w = 529;
		upgradelist[i].h = 302;
	}
	return;
}



void upgrade_act() {
	switch (towers[tempx][tempy]->kind)
	{
	case 0://gun
		putlist[0] = upgradeorsell[12];
		putlist[1]= upgradeorsell[0];
		putlist[2] = upgradeorsell[2];
		break;
	case 1://medium gun
		putlist[0] = upgradeorsell[13];
		putlist[1] = upgradeorsell[1];
		putlist[2] = NULL;
		break;
	case 2: //heavy gun
		putlist[0] = upgradeorsell[14];
		putlist[1] = NULL;
		putlist[2] = NULL;
		break;
	case 3: //aircanon
		putlist[0] = upgradeorsell[21];
		putlist[1] = upgradeorsell[3];
		putlist[2] = NULL;
		break;
	case 4:
		putlist[0] = upgradeorsell[22];
		putlist[1] = NULL;
		putlist[2] = NULL;
		break;
	case 5: //rocket
		putlist[0] = upgradeorsell[18];
		putlist[1] = upgradeorsell[8];
		putlist[2] = upgradeorsell[10];
		break;
	case 6: //medium rocket
		putlist[0] = upgradeorsell[19];
		putlist[1] = upgradeorsell[9];
		putlist[2] = NULL;
		break;
	case 7: //heavy rocket
		putlist[0] = upgradeorsell[20];
		putlist[1] = NULL;
		putlist[2] = NULL;
		break;
	case 8: //artillery
		putlist[0] = upgradeorsell[24];
		putlist[1] = upgradeorsell[11]; 
		putlist[2] = NULL;
		break;
	case 9: //mortar
		putlist[0] = upgradeorsell[25];
		putlist[1] = NULL;
		putlist[2] = NULL;
		break;
	case 10: //slow
		putlist[0] = upgradeorsell[15];
		putlist[1] = upgradeorsell[4];
		putlist[2] = upgradeorsell[6];
		break;
	case 11: //upgraded slow
		putlist[0] = upgradeorsell[16];
		putlist[1] = upgradeorsell[5];
		putlist[2] = NULL;
		break;
	case 12: //advanced slow
		putlist[0] = upgradeorsell[17];
		putlist[1] = NULL;
		putlist[2] = NULL;
		break;
	case 13: //teleport 
		putlist[0] = upgradeorsell[23];
		putlist[1] = upgradeorsell[7];
		putlist[2] = NULL;
		break;
	case 14: //armed teleport
		putlist[0] = upgradeorsell[23];
		putlist[1] = NULL;
		putlist[2] = NULL;
		break;
	}

	if (point_in_rect(mouse_position, upgradelist[0]) || point_in_rect(mouse_position, upgradelist[1]) || point_in_rect(mouse_position, upgradelist[2]))
	{
		if (point_in_rect(mouse_position, upgradelist[0]))  //sell
		{
			switch (towers[tempx][tempy]->kind)
			{
			case 0: //gun
				if (!StartButtonPressed)  TotalMoney += 5;
				else  TotalMoney += 3;
				break;
			case 1:
				TotalMoney += 4;
				break;
			case 2:
				TotalMoney += 6;
				break;
			case 3:
				TotalMoney += 12;
				break;
			case 4:
				TotalMoney += 24;
				break;
			case 5: //rocket
				if (!StartButtonPressed)  TotalMoney += 20;
				else  TotalMoney += 10;
				break;
			case 6:
				TotalMoney += 15;
				break;
			case 7:
				TotalMoney += 30;
				break;
			case 8:
				TotalMoney += 28;
				break;
			case 9:
				TotalMoney += 56;
				break;
			case 10: //slow
				if (!StartButtonPressed)  TotalMoney += 10;
				else  TotalMoney += 5;
				break;
			case 11:
				TotalMoney += 10;
				break;
			case 12:
				TotalMoney += 20;
				break;
			case 13:
				TotalMoney += 16;
				break;
			case 14:
				TotalMoney += 16;
				break;
			}
			for (auto enemy : enemies) {
				if (!enemy->CanFly)  enemy->FindPath(0);
			}
			delete towers[tempx][tempy];
			towers[tempx][tempy] = NULL;
			status = play;
		}
		else if (point_in_rect(mouse_position, upgradelist[1]))
		{
			if (putlist[1] != NULL) //there exists an upgrading option
			{
				switch (towers[tempx][tempy]->kind)
				{
				case 0:
					if (TotalMoney >= 6)
					{
						TotalMoney -= 6;
						upgrade(tempx, tempy, 1, loop);
						status = play;
					}
					break;
				case 1:
					if (TotalMoney >= 8)
					{
						TotalMoney -= 8;
						upgrade(tempx, tempy, 2, loop);
						status = play;
					}
					break;
				case 3:
					if (TotalMoney >= 32)
					{
						TotalMoney -= 32;
						upgrade(tempx, tempy, 4, loop);
						status = play;
					}
					break;
				case 5:
					if (TotalMoney >= 30)
					{
						TotalMoney -= 30;
						upgrade(tempx, tempy, 6, loop);
						status = play;
					}
					break;
				case 6:
					if (TotalMoney >= 50)
					{
						TotalMoney -= 50;
						upgrade(tempx, tempy, 7, loop);
						status = play;
					}
					break;
				case 8:
					if (TotalMoney >= 70)
					{
						TotalMoney -= 70;
						upgrade(tempx, tempy, 9, loop);
						status = play;
					}
					break;
				case 10:
					if (TotalMoney >= 15)
					{
						TotalMoney -= 15;
						upgrade(tempx, tempy, 11, loop);
						status = play;
					}
					break;
				case 11:
					if (TotalMoney >= 20)
					{
						TotalMoney -= 20;
						upgrade(tempx, tempy, 12, loop);
						status = play;
					}
					break;
				case 13:
					if (TotalMoney >= 3)
					{
						TotalMoney -= 3;
						upgrade(tempx, tempy, 14, loop);
						status = play;
					}
					break;
				}
			}
		}
		else if (point_in_rect(mouse_position, upgradelist[2]))
		{
			if (putlist[2] != NULL) //there exists an upgrading option
			{
				switch (towers[tempx][tempy]->kind)
				{
				case 0:
					if (TotalMoney >= 20)
					{
						TotalMoney -= 20;
						upgrade(tempx, tempy, 3, loop);
						status = play;
					}
					break;
				case 5:
					if (TotalMoney >= 50)
					{
						TotalMoney -= 50;
						upgrade(tempx, tempy, 8, loop);
						status = play;
					}
					break;
				case 10:
					if (TotalMoney >= 12)
					{
						TotalMoney -= 12;
						upgrade(tempx, tempy, 13, loop);
						status = play;
					}
					break;
				}
			}
		}
	}
	else//if click not on the rect, quit otherwise.
	{
		status = play;
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
		for (int i = 0; i < 3; i++) {
			if (putlist[i] != NULL)
			{
				SDL_RenderCopy(gRenderer, putlist[i], NULL, &upgradelist[i]);
			}
		}
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