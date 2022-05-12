#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<fstream>
#include<string>
#include<iostream>

#include"const.h"
#include"LTexture.h"
#include"LButton.h"
#include"LButtonSprite.h"
#include"function.h"

void init(SDL_Window*& window, SDL_Renderer*& renderer) {
	//Create window
	window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Create vsynced renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, WHITE_COLOR.r, WHITE_COLOR.g, WHITE_COLOR.b, WHITE_COLOR.a);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);

	//Initialize SDL_ttf
	TTF_Init();

	//Initialize SDL_Mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer*& renderer) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

void loadFont(TTF_Font*& gFont) {
	//load font for use
	gFont = TTF_OpenFont("2048_Data/font.ttf", 32);
	if (gFont == NULL) {
		std::cout << "Unable to load Font!" << SDL_GetError() << std::endl;
	}
}

void setupButton(LButton& button, const std::string& title, const int& x, const int& y, SDL_Renderer*& renderer, TTF_Font*& gFont) {
	button.setTexture(title, DEFAULT_STATUS, GREEN_COLOR, renderer, gFont);
	button.setTexture(title, TRIGGERED_STATUS, RED_COLOR, renderer, gFont);

	button.setPosition(x, y);
}

void loadPicture(SDL_Texture** gTexture, SDL_Renderer*& renderer) {
	//load picture for use
	gTexture[0] = loadTexture("2048_Data/background.png", renderer);
	gTexture[1] = loadTexture("2048_Data/2.png", renderer);
	gTexture[2] = loadTexture("2048_Data/4.png", renderer);
	gTexture[3] = loadTexture("2048_Data/8.png", renderer);
	gTexture[4] = loadTexture("2048_Data/16.png", renderer);
	gTexture[5] = loadTexture("2048_Data/32.png", renderer);
	gTexture[6] = loadTexture("2048_Data/64.png", renderer);
	gTexture[7] = loadTexture("2048_Data/128.png", renderer);
	gTexture[8] = loadTexture("2048_Data/256.png", renderer);
	gTexture[9] = loadTexture("2048_Data/512.png", renderer);
	gTexture[10] = loadTexture("2048_Data/1024.png", renderer);
	gTexture[11] = loadTexture("2048_Data/2048.png", renderer);
	gTexture[12] = loadTexture("2048_Data/background menu.jpg", renderer);
	for (int i = 0; i < 13; i++) {
		if (gTexture[i] == NULL) {
			std::cout << "Unable to load image!" << SDL_GetError() << std::endl;
		}
	}
}

int loadFile(std::fstream& file) {
	//Lấy dữ liệu từ file (file chỉ gồm 1 dòng duy nhất chứa highscore)
	int n;
	file >> n;
	return n;
}

void loadMatrix(std::fstream& file, int** matrix, bool& isDataEmpty) {
	int num = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			file >> num;
			matrix[i][j] = num;
			if (num != 0)isDataEmpty = false;
		}
	}
}

void saveScore(const int& score, const std::string& path) {

	//Xoá dữ liệu trong file chuẩn bị cho việc lưu dữ liệu mới 
	std::ofstream ofs;
	ofs.open(path, std::ios::out, std::ios::trunc);
	ofs.close();

	//Lưu dữ liệu mới 
	std::ofstream saveData(path);
	saveData << score;
	saveData.close();
}

void saveMatrix(int** matrix) {
	//Xoá dữ liệu trong file chuẩn bị cho việc lưu dữ liệu mới 
	std::ofstream ofs;
	ofs.open("2048_Data/du lieu ma tran.txt", std::ios::out, std::ios::trunc);
	ofs.close();

	//Lưu dữ liệu mới 
	std::ofstream saveData("2048_Data/du lieu ma tran.txt");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			saveData << matrix[i][j] << ' ';
		}
	}
	saveData.close();
}

void loadSound(Mix_Chunk*& gMusic) {
	//Load sound effect
	gMusic = Mix_LoadWAV("2048_Data/sound.wav");
	if (gMusic == NULL) {
		std::cout << "Unable to load music!" << SDL_GetError() << std::endl;
	}
}

void setPositionOfPicture(SDL_Rect* picture) {
	picture[0].x = 0;	//Tọa độ x
	picture[0].y = 100;	//Tọa độ y	
	picture[0].w = 400;	//Chiều rộng cuả ảnh (mong muốn)
	picture[0].h = 400;	//Chièu cao của ảnh (mong muốn)

	picture[1].x = 10;
	picture[1].y = 110;
	picture[1].w = 87;
	picture[1].h = 87;

	picture[2].x = 107;
	picture[2].y = 110;
	picture[2].w = 87;
	picture[2].h = 87;

	picture[3].x = 204;
	picture[3].y = 110;
	picture[3].w = 87;
	picture[3].h = 87;

	picture[4].x = 301;
	picture[4].y = 110;
	picture[4].w = 87;
	picture[4].h = 87;

	picture[5].x = 10;
	picture[5].y = 207;
	picture[5].w = 87;
	picture[5].h = 87;

	picture[6].x = 107;
	picture[6].y = 207;
	picture[6].w = 87;
	picture[6].h = 87;

	picture[7].x = 204;
	picture[7].y = 207;
	picture[7].w = 87;
	picture[7].h = 87;

	picture[8].x = 301;
	picture[8].y = 207;
	picture[8].w = 87;
	picture[8].h = 87;

	picture[9].x = 10;
	picture[9].y = 304;
	picture[9].w = 87;
	picture[9].h = 87;

	picture[10].x = 107;
	picture[10].y = 304;
	picture[10].w = 87;
	picture[10].h = 87;

	picture[11].x = 204;
	picture[11].y = 304;
	picture[11].w = 87;
	picture[11].h = 87;

	picture[12].x = 301;
	picture[12].y = 304;
	picture[12].w = 87;
	picture[12].h = 87;

	picture[13].x = 10;
	picture[13].y = 401;
	picture[13].w = 87;
	picture[13].h = 87;

	picture[14].x = 107;
	picture[14].y = 401;
	picture[14].w = 87;
	picture[14].h = 87;

	picture[15].x = 204;
	picture[15].y = 401;
	picture[15].w = 87;
	picture[15].h = 87;

	picture[16].x = 301;
	picture[16].y = 401;
	picture[16].w = 87;
	picture[16].h = 87;

	//Background game.
	picture[17].x = 0;
	picture[17].y = 0;
	picture[17].w = 400;
	picture[17].h = 500;
}

void Render_Copy(SDL_Renderer*& renderer, SDL_Texture** Texture, SDL_Rect* picture, int** matran) {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			switch (matran[i - 1][j - 1]) {
			case 2: {
				SDL_RenderCopy(renderer, Texture[1], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 4: {
				SDL_RenderCopy(renderer, Texture[2], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 8: {
				SDL_RenderCopy(renderer, Texture[3], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 16: {
				SDL_RenderCopy(renderer, Texture[4], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 32: {
				SDL_RenderCopy(renderer, Texture[5], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 64: {
				SDL_RenderCopy(renderer, Texture[6], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 128: {
				SDL_RenderCopy(renderer, Texture[7], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 256: {
				SDL_RenderCopy(renderer, Texture[8], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 512: {
				SDL_RenderCopy(renderer, Texture[9], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 1024: {
				SDL_RenderCopy(renderer, Texture[10], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			case 2048: {
				SDL_RenderCopy(renderer, Texture[11], NULL, &picture[(i - 1) * 4 + j]);
				break;
			}
			}
		}
	}
}

void freeButtons(LButton& button) {
	button.free();
}

void freeTexture(LTexture& renderTexture) {
	renderTexture.free();
}

void freeSoundEffects(Mix_Chunk*& gMusic) {
	//Free the sound effects
	Mix_FreeChunk(gMusic);
	gMusic = NULL;
}

void freeFont(TTF_Font*& gFont) {
	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
}

void freeWindowAndRenderer(SDL_Window*& window, SDL_Renderer*& renderer) {
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
}

void quit() {
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}