#pragma once

void setup() {

	init(window, renderer);

	loadFont(gFont);

	loadPicture(gTexture, renderer);

	loadSound(gMusic);

	setupButton(gButton[START], "Start", 50, 150, renderer, gFont);
	setupButton(gButton[EXIT], "Exit", 50, 225, renderer, gFont);
	setupButton(gButton[PLAY_AGAIN], "Play Again", 50, 150, renderer, gFont);
	setupButton(gButton[CONTINUE_MENU], "Continue", 50, 375, renderer, gFont);
	setupButton(gButton[CONTINUE_GAMEPLAY], "Continue", 50, 150, renderer, gFont);
	setupButton(gButton[SAVE_AND_EXIT], "Save and exit", 50, 225, renderer, gFont);
	setupButton(gButton[MUSIC_ON], "Music: On", 50, 300, renderer, gFont);
	setupButton(gButton[MUSIC_OFF], "Music: Off", 50, 300, renderer, gFont);

	setPositionOfPicture(picture);

	highscore = loadFile(file);

	loadMatrix(Matrix, data_save, isDataEmpty);
}

void quitSDL() {
	//Đóng file
	file.close();

	Matrix.close();

	CurrentScore.close();

	//Lưu dữ liệu 
	saveScore(highscore, "2048_Data/highscore.txt");

	saveScore(0, "2048_Data/current score.txt");

	saveMatrix(createData());

	//Giải phóng các nút 

	for (int i = 0; i < TOTAL_BUTTON; i++) {
		freeButtons(gButton[i]);
	}

	//Giaỉ phóng dữ liệu và kết thúc chương trình 
	freeTexture(renderTexture);

	freeSoundEffects(gMusic);

	freeFont(gFont);

	freeWindowAndRenderer(window, renderer);

	quit();
}