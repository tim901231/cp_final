#ifndef WORD_H
#define WORD_H

#include<string>
#include <SDL.h>
#include "SDL_image.h"
#include"SDL_ttf.h"
#include"variable.h"
class words {
public:
	int n;
	SDL_Surface* textSurface = NULL;
	SDL_Texture* mTexture = NULL;
	SDL_Color color;
	SDL_Rect quad = { 1650,100,60,60 };
	words();
	words(string s, int size, SDL_Color color_);
	void changeword(string s);
	void render();
};
extern words** rank_id;
extern words** rank_score;
extern words* rank_title;
extern words* rank_title;
extern words* currmoney;
extern words* currlife;
extern words* currwave;
extern words* SCORE;
extern words* me;
extern words* my_score;
extern words* tip;
#endif // !WORD_H
