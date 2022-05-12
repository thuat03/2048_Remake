#pragma once

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

TTF_Font* gFont = NULL;

Mix_Chunk* gMusic = NULL;

std::fstream file("2048_Data/highscore.txt");

std::fstream Matrix("2048_Data/du lieu ma tran.txt");

std::fstream CurrentScore("2048_Data/current score.txt");

LTexture renderTexture;

SDL_Texture* gTexture[13];

SDL_Rect picture[18];

LButton gButton[TOTAL_BUTTON];


int score = 0;

int highscore = 0;

bool isDataEmpty = true;

Settings settings;

int** data_save = createData();

