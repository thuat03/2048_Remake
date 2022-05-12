#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string>
#include<iostream>
#include<fstream>

#include"const.h"
#include"LButton.h"
#include"LTexture.h"
#include"gameEngine.h"
#include"function.h"
#include"settings.h"


#include"variable.h"
#include"setup.h"
#include"GamePlayRender.h"


int main(int argc, char* args[]) {
	//Setup data and load SDL
	setup();

	//Game loop 
	bool isPlayAgain = false;
	do {
		score = 0;
		int** data = createData();
		int** data_check = createData();
		getEqualArray(data, data_check);
		randomUpgrade(data);

		if (!isPlayAgain) {
			main_menu();
			if (!isDataEmpty && gButton[CONTINUE_MENU].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
				getEqualArray(data_save, data);
				score = loadFile(CurrentScore);
			}

			if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
				deleteData(data);
				deleteData(data_check);
				break;
			}
		}

		//If in menu press Start
		game_play(data, data_check);

		if (gButton[PLAY_AGAIN].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			isPlayAgain = true;
		}
		else {
			isPlayAgain = false;
		}
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			isPlayAgain = false;
		}
		//Giải phóng tài nguyên để chơi lại hoặc kết thúc 
		deleteData(data);
		deleteData(data_check);

		//Reset trạng thái của các nút về mặc định 
		for (int i = 0; i < TOTAL_BUTTON; i++) {
			gButton[i].freeStatus();
		}
		SDL_Delay(250);

	} while (isPlayAgain);

	quitSDL();

	return 0;
}