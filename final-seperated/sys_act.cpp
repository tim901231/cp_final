#include"sys_act.h"
using namespace std;
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

void setrect(SDL_Rect r, int a, int b, int c, int d) 
{
	r.x = a;
	r.y = b;
	r.w = c;
	r.h = d;
	return;
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


void change_upgrade() {
	switch (towers[tempx][tempy]->kind)
	{
	case 0://gun
		putlist[0] = upgradeorsell[12];
		putlist[1] = upgradeorsell[0];
		if (TotalMoney < 6) {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 128); //3/4 transparent
		}
		else {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 255); 
		}
		putlist[2] = upgradeorsell[2];
		if (TotalMoney < 20) {
			SDL_SetTextureBlendMode(putlist[2], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[2], 128); //3/4 transparent
		}
		else {
			SDL_SetTextureBlendMode(putlist[2], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[2], 255);
		}
		break;

	case 1://medium gun
		putlist[0] = upgradeorsell[13];
		putlist[1] = upgradeorsell[1];
		if (TotalMoney < 8) {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 128); //3/4 transparent
		}
		else {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 255);
		}
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
		if (TotalMoney < 32) {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 128); //3/4 transparent
		}
		else {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 255);
		}
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
		if (TotalMoney < 30) {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 128); //3/4 transparent
		}
		else {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 255);
		}
		putlist[2] = upgradeorsell[10];
		if (TotalMoney < 50) {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 128); //3/4 transparent
		}
		else {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 255);
		}
		break;

	case 6: //medium rocket
		putlist[0] = upgradeorsell[19];
		putlist[1] = upgradeorsell[9];
		if (TotalMoney < 50) {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 128); //3/4 transparent
		}
		else {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 255);
		}
		putlist[2] = NULL;
		break;
	case 7: //heavy rocket
		putlist[0] = upgradeorsell[20];
		putlist[1] = NULL;
		putlist[2] = NULL;
		break;
	case 8: //artillery
		putlist[0] = upgradeorsell[24];
		if (TotalMoney < 70) {
			SDL_SetTextureBlendMode(upgradeorsell[11], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(upgradeorsell[11], 128);
		}
		else {
			SDL_SetTextureBlendMode(upgradeorsell[11], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(upgradeorsell[11], 255);
		}
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
		if (TotalMoney < 15) {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 128);
		}
		else {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 255);
		}
		putlist[2] = upgradeorsell[6];
		if (TotalMoney < 12) {
			SDL_SetTextureBlendMode(putlist[2], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[2], 128);
		}
		else {
			SDL_SetTextureBlendMode(putlist[2], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[2], 255);
		}
		break;
	case 11: //upgraded slow
		putlist[0] = upgradeorsell[16];
		putlist[1] = upgradeorsell[5];
		if (TotalMoney < 15) {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 128);
		}
		else {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 255);
		}
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
		if (TotalMoney < 3) {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 128);
		}
		else {
			SDL_SetTextureBlendMode(putlist[1], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(putlist[1], 255);
		}
		putlist[2] = NULL;
		break;
	case 14: //armed teleport
		putlist[0] = upgradeorsell[23];
		putlist[1] = NULL;
		putlist[2] = NULL;
		break;
	}
}
void upgrade_act() {
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
				if (!StartButtonPressed)  TotalMoney += 11;
				else  TotalMoney += 4;
				break;
			case 2:
				if (!StartButtonPressed)  TotalMoney += 19;
				else  TotalMoney += 6;
				break;
			case 3:
				if (!StartButtonPressed)  TotalMoney += 25;
				else  TotalMoney += 12;
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
				if (!StartButtonPressed)  TotalMoney += 25;
				else  TotalMoney += 10;
				break;
			case 12:
				TotalMoney += 20;
				break;
			case 13:
				if (!StartButtonPressed)  TotalMoney += 22;
				else  TotalMoney += 16;
				break;
			case 14:
				if (!StartButtonPressed)  TotalMoney += 25;
				else  TotalMoney += 16;
				break;
			}
			delete towers[tempx][tempy];
			towers[tempx][tempy] = NULL;
			for (auto enemy : enemies) {
				if (!enemy->CanFly)  enemy->FindPath(0);
			}
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
				SDL_RenderCopy(gRenderer, white, NULL, &upgradelist[i]);
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
	loadedSurface = IMG_Load("pictures/exit_bottom.png");
	cancel = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	loadedSurface = IMG_Load("pictures/white.png");
	white = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	SDL_SetTextureBlendMode(white, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(white, 180);

	SDL_SetTextureBlendMode(cancel, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(cancel, 128);
	
	SDL_FreeSurface(loadedSurface);
}
void animation() {
	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	if (status == play)
	{
		if (point_in_rect(mouse_position, option_bottom) == true) {
			option_bottom.x = 0;
			option_bottom.y = 940;
			option_bottom.w = 70;
			option_bottom.h = 70;
			//setrect(option_bottom, 0, 940, 70, 70);
		}
		else {
			option_bottom.x = 10;
			option_bottom.y = 950;
			option_bottom.w = 50;
			option_bottom.h = 50;
			//setrect(option_bottom, 10, 950, 50, 50);
		}
	}
	else if (status == option)
	{
		if (point_in_rect(mouse_position, bottoms[1]) == true) { //pause
			bottoms[1].x = 680;
			bottoms[1].y = 380;
			bottoms[1].w = 120;
			bottoms[1].h = 120;
			//setrect(bottoms[1], 680, 380, 120, 120);
		}
		else {
			bottoms[1].x = 690;
			bottoms[1].y = 390;
			bottoms[1].w = 100;
			bottoms[1].h = 100;
			//setrect(bottoms[1], 690, 390, 100, 100);
		}

		if (point_in_rect(mouse_position, bottoms[2]) == true) { //start
			bottoms[2].x = 850;
			bottoms[2].y = 380;
			bottoms[2].w = 120;
			bottoms[2].h = 120;
			//setrect(bottoms[2], 850, 380, 120, 120);
		}
		else {
			bottoms[2].x = 860;
			bottoms[2].y = 390;
			bottoms[2].w = 100;
			bottoms[2].h = 100;
			//setrect(bottoms[2], 860, 390, 100, 100);
		}

		if (point_in_rect(mouse_position, bottoms[3]) == true) {
			bottoms[3].x = 1020;
			bottoms[3].y = 380;
			bottoms[3].w = 120;
			bottoms[3].h = 120;
			//setrect(bottoms[3], 1020, 380, 120, 120);
		}
		else {
			bottoms[3].x = 1030;
			bottoms[3].y = 390;
			bottoms[3].w = 100;
			bottoms[3].h = 100;
			//setrect(bottoms[3], 1030, 390, 100, 100);
		}

		if (point_in_rect(mouse_position, bottoms[4]) == true) {
			bottoms[4].x = 790;
			bottoms[4].y = 540;
			bottoms[4].w = 100;
			bottoms[4].h = 100;
			//setrect(bottoms[4],790, 540, 100, 100);
		}
		else {
			bottoms[4].x = 800;
			bottoms[4].y = 550;
			bottoms[4].w = 80;
			bottoms[4].h = 80;
			//setrect(bottoms[4], 800, 550, 80, 80);
		}

		if (point_in_rect(mouse_position, bottoms[5]) == true) {
			bottoms[5].x = 910;
			bottoms[5].y = 540;
			bottoms[5].w = 100;
			bottoms[5].h = 100;
			//setrect(bottoms[5], 910, 540, 100, 100);
		}
		else {
			bottoms[5].x = 920;
			bottoms[5].y = 550;
			bottoms[5].w = 80;
			bottoms[5].h = 80;
			//setrect(bottoms[5], 920, 550, 80, 80);
		}

		if (point_in_rect(mouse_position, bottoms[6]) == true) {
			bottoms[6].x = 1140;
			bottoms[6].y = 300;
			bottoms[6].w = 65;
			bottoms[6].h = 65;
			//setrect(bottoms[6], 1140, 300, 65, 65);
		}
		else {
			bottoms[6].x = 1150;
			bottoms[6].y = 310;
			bottoms[6].w = 45;
			bottoms[6].h = 45;
			//setrect(bottoms[6], 1150, 310, 45, 45);
		}
	}
}
void click_motion() {
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
			if (check({ p, q })) {//check
				if (towers[p][q] == NULL) {
					towers[p][q] = test;
					canBuild = DEFAULT->FindPath(0);
					for (auto enemy : enemies) {
						if (!enemy->CanFly)  canBuild &= enemy->FindPath(0);
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
void render_botton() {
	SDL_SetTextureBlendMode(light, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(slow, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(rocket, SDL_BLENDMODE_BLEND);
	if (TotalMoney >= 5) {
		SDL_SetTextureAlphaMod(light, 255);
	}
	else {
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
}
int loadLeaderboard() {
	int n = -1;
	fstream file;
	file.open("rank.txt", ios::in);
	for (int i = 0; i < 5; i++) {
		file >> id[i] >> scores[i];
	}
	for (int i = 0; i < 5; i++) {
		if (currentscore > scores[i]) {
			for (int j = 4; j > i; j--) {
				scores[j] = scores[j-1];
				id[j] = id[j - 1];
			}
			scores[i] = currentscore;
			id[i] = "Yourname";
			n = i;
			break;
		}
	}
	SDL_Surface* loadedSurface = IMG_Load("pictures/green.png");
	ranking = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	SDL_SetTextureBlendMode(ranking, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(ranking, 180);
	rank_rect.x = 620;
	rank_rect.y = 260;
	rank_rect.w = 530;
	rank_rect.h = 450;
	for (int i = 0; i < 5; i++) {
		rank_id[i] = new words(id[i], 18, wordcolor);
		rank_id[i]->quad.y = 390 + i * 50;
		rank_id[i]->quad.w = id[i].length() * 30;
		rank_id[i]->quad.x = 870 - rank_id[i]->quad.w;
	}
	for (int i = 0; i < 5; i++) {
		rank_score[i] = new words(to_string(scores[i]), 18, wordcolor);

		rank_score[i]->quad.y = 390 + i * 50;
		rank_score[i]->quad.w = digit(scores[i]) * 30;
		rank_score[i]->quad.x = 1100 - rank_score[i]->quad.w;
	}
	me = new words("you", 18, wordcolor);
	my_score = new words(to_string(currentscore), 18, wordcolor);
	tip = new words("enter your name", 18, wordcolor);
	if (n == -1) {
		me->quad.y = 640;
		me->quad.w = 3 * 30;
		me->quad.x = 870 - me->quad.w;
		my_score->quad.y = 640;
		my_score->quad.w = digit(currentscore) * 30;
		my_score->quad.x = 1100 - my_score->quad.w;
	}
	else {
		tip->quad.y = 640;
		tip->quad.w = 15 * 30;
		tip->quad.x = 885 - tip->quad.w/2;
	}
	rank_title = new words("R A N K", 50, wordcolor);
	rank_title->quad.x = 750;
	rank_title->quad.y = 280;
	rank_title->quad.w = 300;
	rank_title->quad.h = 100;
	
	file.close();
	SDL_FreeSurface(loadedSurface);
	return n;
}
void save_leaderboard() {
	fstream file;
	printf("hi");
	file.open("rank.txt", ios::trunc|ios::out);
	for (int i = 0; i < 5; i++) {
		file << id[i] << " " << scores[i] << "\n";
	}
	file.close();
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
void data_init() {
	currmoney = new words(money, 18, wordcolor);
	currlife = new words(life, 18, wordcolor);
	currwave = new words(wave, 18, wordcolor);
	SCORE = new words(score, 18, wordcolor);
	currlife->quad.y = 60; currlife->quad.w = 120;
	currwave->quad.y = 20; currwave->quad.w = 120;
	SCORE->quad.x = 10, SCORE->quad.y = 10; SCORE->quad.w = 140;
}
void change_data_size() {
	currmoney->changeword("$: " + to_string(TotalMoney));
	currlife->changeword("Life: " + to_string(TotalLife));
	currwave->changeword("Wave: " + to_string(currentwave));
	SCORE->changeword("Score: " + to_string(currentscore));
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
		currwave->quad.w = 120;
	}
	else {
		currwave->quad.w = 150;
	}
	if (currentscore < 10) {
		SCORE->quad.w = 120;
	}
	else if (currentscore < 100) {
		SCORE->quad.w = 150;
	}
	else if (currentscore < 1000) {
		SCORE->quad.w = 180;
	}
	else {
		SCORE->quad.w = 210;
	}
	currmoney->render();
	currlife->render();
	currwave->render();
	SCORE->render();
}
void close()
{
	//Free loaded images

	for (int i = 0; i < 7; i++) {
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
void end_motion() {
	if (currentwave == 100 && TotalLife > 0)  background = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("pictures/victory.jpg"));
	else  background = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("pictures/GameOver.png"));
	int num = loadLeaderboard();
	int time0 = SDL_GetTicks();
	int time1;
	SDL_StartTextInput();
	bool input_flag = false;
	bool sure = false;
	SDL_Rect anime = { 0,0,0,0 };
	while (quit)
	{
		time1 = SDL_GetTicks();
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)  quit = false;
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)  quit = false;
			if (num != -1 && sure == false) {
				if (e.type == SDL_TEXTINPUT) {
					if (!input_flag) {
						input_flag = true;
						id[num] = "";
					}
					if (id[num].size() <= 7) {
						id[num] = id[num] + e.text.text;
						rank_id[num]->changeword(id[num]);
						rank_id[num]->quad.w = id[num].length() * 30;
						rank_id[num]->quad.x = 870 - rank_id[num]->quad.w;
					}
				}
				else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && id[num].size()) {
					id[num].pop_back();
					rank_id[num]->changeword(id[num]);
					rank_id[num]->quad.w = id[num].length() * 30;
					rank_id[num]->quad.x = 870 - rank_id[num]->quad.w;
				}
				else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
				{
					sure = true;
					save_leaderboard();
				}
			}
		}
		SDL_RenderCopy(gRenderer, background, NULL, NULL);
		if (time1 - time0 > 2000) {
			if (time1 - time0 < 2500) {
				int u = time1 - time0 - 2000;
				anime.w = 4 * u;
				anime.h = 2 * u;
				anime.x = 900 - anime.w / 2;
				anime.y = 500 - anime.h / 2;
				SDL_RenderCopy(gRenderer, white, NULL, &anime);
			}
			else {
				SDL_RenderCopy(gRenderer, white, NULL, NULL);
				SDL_RenderCopy(gRenderer, ranking, NULL, &rank_rect);
				rank_title->render();
				for (int i = 0; i < 5; i++) {
					rank_id[i]->render();
					rank_score[i]->render();
				}
				if (num == -1) {
					me->render();
					my_score->render();
				}
				else {
					tip->render();
				}
			}	
			
		}
		SDL_RenderPresent(gRenderer);
	}
}