#include"word.h"
words::words() {
	
}
words::words(string s, int size, SDL_Color color_) {
	n = size;
	color = color_;
	gFont = TTF_OpenFont("Roboto-Black.ttf", size);
	textSurface = TTF_RenderText_Solid(gFont, s.c_str(), color_);
	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	SDL_FreeSurface(textSurface);
}
void words::changeword(string s) {
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	textSurface = TTF_RenderText_Solid(gFont, s.c_str(), color);
	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	SDL_FreeSurface(textSurface);
}
void words::render() {
	SDL_RenderCopy(gRenderer, this->mTexture, NULL, &quad);
	return;
}
words** rank_id = new words * [5];
words** rank_score = new words * [5];
words* rank_title = NULL; 
words* currmoney = NULL;
words* currlife =NULL;
words* currwave = NULL;
words* SCORE = NULL;
words* me = NULL;
words* my_score = NULL;
words* tip = NULL;
