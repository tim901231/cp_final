#include"word.h"
word::word(string s, int size, SDL_Color color_) {
	n = size;
	color = color_;
	gFont = TTF_OpenFont("Roboto-Black.ttf", size);
	textSurface = TTF_RenderText_Solid(gFont, s.c_str(), color_);
	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	SDL_FreeSurface(textSurface);
}
void word::changeword(string s) {
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	textSurface = TTF_RenderText_Solid(gFont, s.c_str(), color);
	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	SDL_FreeSurface(textSurface);
}
void word::render() {
	SDL_RenderCopy(gRenderer, this->mTexture, NULL, &quad);
	return;
}

