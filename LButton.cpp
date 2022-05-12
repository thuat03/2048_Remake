#include<SDL.h>
#include <SDL_ttf.h>
#include<string>

#include"LButton.h"


LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(const int& x, const int& y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;

			}
		}
	}
}

void LButton::render(SDL_Renderer*& renderer)
{
	//Show current button sprite
	switch (mCurrentSprite) {
	case BUTTON_SPRITE_MOUSE_OUT: {
		texture[DEFAULT_STATUS].render(mPosition.x, mPosition.y, renderer);
		break;
	}
	case BUTTON_SPRITE_MOUSE_OVER_MOTION: {
		texture[TRIGGERED_STATUS].render(mPosition.x, mPosition.y, renderer);
	}
	}
}

void LButton::setTexture(const std::string& str, const int& n, const SDL_Color& color, SDL_Renderer*& renderer, TTF_Font*& gFont) {
	texture[n].loadFromRenderedText(str, color, renderer, gFont);
}

void LButton::free() {
	for (int i = 0; i < 2; i++) {
		texture[i].free();
	}
}

void LButton::freeStatus() {
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
}

LButtonSprite LButton::getStatus() {
	return mCurrentSprite;
}