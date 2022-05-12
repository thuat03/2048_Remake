#pragma once

class LTexture {
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

public:
	LTexture();

	~LTexture();

	void LoadFromFIle(const std::string& path, SDL_Renderer*& renderer);

	void loadFromRenderedText(const std::string& textureText, SDL_Color textColor, SDL_Renderer*& renderer, TTF_Font*& gFont);

	void free();

	void setColor(const Uint8& red, const Uint8& green, const Uint8& blue);

	void setBlendMode(const SDL_BlendMode& blending);

	void setAlpha(const Uint8& alpha);

	void render(int x, int y, SDL_Renderer*& renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();

	int getHeight();
};
