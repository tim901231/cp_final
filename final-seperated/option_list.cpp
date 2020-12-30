#include"option_list.h"
void option_act() {
	if (point_in_rect(mouse_position, pausebottom)) {
		while (1) {
			if (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					break;
				}
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN) {
					SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
					if (point_in_rect(mouse_position, startbottom)) {
						speedy = 1;
						break;
					}
				}
			}
		}
	}
	if (point_in_rect(mouse_position, startbottom)) {
		speedy = 1;
	}
	if (point_in_rect(mouse_position, fastbottom)) {
		if (speedy <= 2) {
			speedy += 1;
		}
	}
	if (point_in_rect(mouse_position, mutebottom)) {
		//mute music
	}
	if (point_in_rect(mouse_position, leavebottom)) {
		status = menu;
	}
	if (point_in_rect(mouse_position, exitbottom)) {
		status = play;
	}
}
void loadbottommedia() {
	SDL_Surface* surface;
	surface = IMG_Load("pictures/option_pic.jpeg");
	option_list_pic = SDL_CreateTextureFromSurface(gRenderer, surface);
	bottoms_pic[0] = option_list_pic;
	bottoms[0] = option_list;
	surface = IMG_Load("pictures/pause.png");
	pausebottom_pic = SDL_CreateTextureFromSurface(gRenderer, surface);
	bottoms_pic[1] = pausebottom_pic;
	bottoms[1] = pausebottom;
	surface = IMG_Load("pictures/play.png");
	startbottom_pic = SDL_CreateTextureFromSurface(gRenderer, surface);
	bottoms_pic[2] = startbottom_pic;
	bottoms[2] = startbottom;
	surface = IMG_Load("pictures/expedite.png");
	fastbottom_pic = SDL_CreateTextureFromSurface(gRenderer, surface);
	bottoms_pic[3] = fastbottom_pic;
	bottoms[3] = fastbottom;
	surface = IMG_Load("pictures/yellow.png");
	mutebottom_pic = SDL_CreateTextureFromSurface(gRenderer, surface);
	bottoms_pic[4] = mutebottom_pic;
	bottoms[4] = mutebottom;
	surface = IMG_Load("pictures/yellow.png");
	leavebottom_pic = SDL_CreateTextureFromSurface(gRenderer, surface);
	bottoms_pic[5] = leavebottom_pic;
	bottoms[5] = leavebottom;
	surface = IMG_Load("pictures/Light_Gun_user.png");
	exitbottom_pic = SDL_CreateTextureFromSurface(gRenderer, surface);
	bottoms_pic[6] = exitbottom_pic;
	bottoms[6] = exitbottom;
	surface = IMG_Load("pictures/Light_Gun_user.png");
	option_bottom_pic = SDL_CreateTextureFromSurface(gRenderer, surface);
	if (option_bottom_pic == NULL) {
		printf("hi");
	}
	SDL_FreeSurface(surface);
}
void show_option_list() {
	if (status == option) {
		for (int i = 0; i < 7; i++) {
			SDL_RenderCopy(gRenderer, bottoms_pic[i], NULL, &bottoms[i]);
		}
	}
}