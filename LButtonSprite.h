#pragma once

//Thông số của các nút 
const int BUTTON_WIDTH = 175;
const int BUTTON_HEIGHT = 50;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_TOTAL = 3
};

enum LButtonStatusRender {
	DEFAULT_STATUS = 0,
	TRIGGERED_STATUS = 1,
	TOTAL_STATUS_RENDER = 2
};

enum TheGameStatus {
	MAIN_MENU_STATUS = 0,
	GAME_PLAY_STATUS = 1,
	WIN_STATUS = 2,
	LOSE_STATUS = 3,
	PAUSE_STATUS = 4,
	EXIT_STATUS = 5,
	TOTAL_STATUS = 6
};

enum TheButton {
	START = 0,
	EXIT = 1,
	PLAY_AGAIN = 2,
	CONTINUE_MENU = 3,
	CONTINUE_GAMEPLAY = 4,
	SAVE_AND_EXIT = 5,
	MUSIC_ON = 6,
	MUSIC_OFF = 7,
	TOTAL_BUTTON = 8
};