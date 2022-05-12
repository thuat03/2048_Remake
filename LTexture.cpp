#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>

#include"LTexture.h"

LTexture::LTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	free();
}

void LTexture::LoadFromFIle(const std::string& path, SDL_Renderer*& renderer) {
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
}

void LTexture::loadFromRenderedText(const std::string& textureText, SDL_Color textColor, SDL_Renderer*& renderer, TTF_Font*& gFont) {
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	mWidth = textSurface->w;
	mHeight = textSurface->h;
	SDL_FreeSurface(textSurface);
}

void LTexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(const Uint8& red, const Uint8& green, const Uint8& blue) {
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(const SDL_BlendMode& blending) {
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(const Uint8& alpha) {
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Renderer*& renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}