#pragma once

#include"LTexture.h"
#include"LButtonSprite.h"

class LButton {
	SDL_Point mPosition;

	LButtonSprite mCurrentSprite;

	LTexture texture[TOTAL_STATUS_RENDER];

public:
	LButton();

	void setPosition(const int& x, const int& y);

	void handleEvent(SDL_Event* e);

	void render(SDL_Renderer*& renderer);

	void setTexture(const std::string& str, const int& n, const SDL_Color& color, SDL_Renderer*& renderer, TTF_Font*& gFont);

	void free();

	LButtonSprite getStatus();

	void freeStatus();
};
