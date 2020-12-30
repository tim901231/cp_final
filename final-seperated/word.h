#ifndef WORD_H
#define WORD_H

#include<string>
#include <SDL.h>
#include "SDL_image.h"
#include"SDL_ttf.h"
#include"variable.h"
class word {
public:
	int n;
	SDL_Surface* textSurface = NULL;
	SDL_Texture* mTexture = NULL;
	SDL_Color color;
	SDL_Rect quad = { 1650,80,60,80 };
	word(string s, int size, SDL_Color color_);
	void changeword(string s);
	void render();
};
#endif // !WORD_H
