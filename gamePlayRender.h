#pragma once

bool isClickedQuit = false;

void main_menu() {
	bool quit = false;
	SDL_Event e;
	while (!quit) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				quitSDL();
				exit(0);
			}

			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);

			gButton[START].handleEvent(&e);
			gButton[EXIT].handleEvent(&e);
			if (settings.music) {
				gButton[MUSIC_ON].handleEvent(&e);
			}
			else {
				gButton[MUSIC_OFF].handleEvent(&e);
			}
			if (!isDataEmpty) {
				gButton[CONTINUE_MENU].handleEvent(&e);
			}
		}


		gButton[START].render(renderer);
		gButton[EXIT].render(renderer);
		if (settings.music) {
			gButton[MUSIC_ON].render(renderer);
		}
		else {
			gButton[MUSIC_OFF].render(renderer);
		}
		if (!isDataEmpty) {
			gButton[CONTINUE_MENU].render(renderer);
		}

		renderTexture.loadFromRenderedText("Welcome to 2048!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		//Ấn vào start để bắt đầu 
		if (gButton[START].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			quit = true;
		}

		//Ấn vào exit để thoát 
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			quit = true;
		}

		//
		if (gButton[MUSIC_ON].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && settings.music) {
			settings.music = false;

			gButton[MUSIC_ON].freeStatus();
		}

		if (gButton[MUSIC_OFF].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && !settings.music) {

			settings.music = true;
		
			Mix_PlayChannel(-1, gMusic, 0);
		
			gButton[MUSIC_OFF].freeStatus();
		}
		//
		if (!isDataEmpty) {
			if (gButton[CONTINUE_MENU].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
				if (settings.music) {
					Mix_PlayChannel(-1, gMusic, 0);
				}
				quit = true;
			}
		}

		//Update screen
		SDL_RenderPresent(renderer);

		//Dừng SDL 
		SDL_Delay(1000 / FPS);
	}
}

void save_and_exit(int** matrix) {
	bool quit = false;
	isClickedQuit = false;
	SDL_Event e;
	while (!quit) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				quitSDL();
				exit(0);
			}

			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);

			gButton[CONTINUE_GAMEPLAY].handleEvent(&e);
			gButton[SAVE_AND_EXIT].handleEvent(&e);

			if (settings.music) {
				gButton[MUSIC_ON].handleEvent(&e);
			}
			else {
				gButton[MUSIC_OFF].handleEvent(&e);
			}
			if (!isDataEmpty) {
				gButton[CONTINUE_MENU].handleEvent(&e);
			}


		}


		SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);
		gButton[CONTINUE_GAMEPLAY].render(renderer);
		gButton[SAVE_AND_EXIT].render(renderer);

		if (settings.music) {
			gButton[MUSIC_ON].render(renderer);
		}
		else {
			gButton[MUSIC_OFF].render(renderer);
		}

		renderTexture.loadFromRenderedText("Game Paused!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		if (gButton[MUSIC_ON].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && settings.music) {
			settings.music = false;
			gButton[MUSIC_ON].freeStatus();
		}
		if (gButton[MUSIC_OFF].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && !settings.music) {
			settings.music = true;
			
			Mix_PlayChannel(-1, gMusic, 0);
	
			gButton[MUSIC_OFF].freeStatus();
		}

		//Ấn vào continue để chơi tiếp
		if (gButton[CONTINUE_GAMEPLAY].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			quit = true;
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			gButton[CONTINUE_GAMEPLAY].freeStatus();
		}

		//Ấn vào Save and exit để lưu và thoát.
		if (gButton[SAVE_AND_EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			isClickedQuit = true;
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			gButton[SAVE_AND_EXIT].freeStatus();
			quit = true;
			saveMatrix(matrix);
		}

		SDL_RenderPresent(renderer);
		//Dừng SDL 
		SDL_Delay(1000 / FPS);
	}
}

void win() {
	bool quit = false;
	SDL_Event e;
	while (!quit) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
			SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);

			gButton[PLAY_AGAIN].handleEvent(&e);
			gButton[EXIT].handleEvent(&e);


		}


		SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);
		gButton[PLAY_AGAIN].render(renderer);
		gButton[EXIT].render(renderer);

		renderTexture.loadFromRenderedText("You Win!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		//Ấn vào "Play Again" để chơi lại 
		if (gButton[PLAY_AGAIN].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			quit = true;
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			break;
		}

		//Ấn vào exit để thoát 
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			quit = true;
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
		}

		SDL_RenderPresent(renderer);
		//Dừng SDL 
		SDL_Delay(1000 / FPS);
	}
}

void lose() {
	bool quit = false;
	SDL_Event e;
	while (!quit) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}

			SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);

			gButton[PLAY_AGAIN].handleEvent(&e);
			gButton[EXIT].handleEvent(&e);

		}


		SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);
		gButton[PLAY_AGAIN].render(renderer);
		gButton[EXIT].render(renderer);

		renderTexture.loadFromRenderedText("You Lose!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		//Ấn vào "Play Again" để chơi lại 
		if (gButton[PLAY_AGAIN].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			quit = true;
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			break;

		}

		//Ấn vào exit để thoát 
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			quit = true;
		}

		SDL_RenderPresent(renderer);
		//Dừng SDL 
		SDL_Delay(1000 / FPS);
	}
}

void game_play(int** data, int** data_check) {
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit) {

		SDL_RenderClear(renderer);

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {

			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
			if (e.key.repeat == 0 && e.type == SDL_KEYDOWN) {
				getEqualArray(data, data_check);
				switch (e.key.keysym.sym) {
				case SDLK_w: {
					updateData(data, 'w', score);
					if (isPossibleMove(data, data_check)) {

						randomUpgrade(data);
						if (settings.music) {
							Mix_PlayChannel(-1, gMusic, 0);
						}
					}
					break;
				}
				case SDLK_a: {
					updateData(data, 'a', score);
					if (isPossibleMove(data, data_check)) {

						randomUpgrade(data);
						if (settings.music) {
							Mix_PlayChannel(-1, gMusic, 0);
						}
					}
					break;
				}
				case SDLK_s: {
					updateData(data, 's', score);
					if (isPossibleMove(data, data_check)) {

						randomUpgrade(data);
						if (settings.music) {
							Mix_PlayChannel(-1, gMusic, 0);
						}
					}
					break;
				}
				case SDLK_d: {
					updateData(data, 'd', score);
					if (isPossibleMove(data, data_check)) {

						randomUpgrade(data);
						if (settings.music) {
							Mix_PlayChannel(-1, gMusic, 0);
						}
					}
					break;
				}
				case SDLK_ESCAPE: {
					if (settings.music) {
						Mix_PlayChannel(-1, gMusic, 0);
					}
					save_and_exit(data);
					if (isClickedQuit) {
						saveScore(highscore, "2048_Data/highscore.txt");
						saveScore(score, "2048_Data/current score.txt");
						exit(0);
					}
					break;
				}
				}

				if (score > highscore) {
					highscore = score;
				}
			}
		}


		SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);
		//Văn bản chuẩn bị xuất hiện trên nền 
		std::string currentscore = "Your score: " + std::to_string(score);
		std::string _highscore = "High score: " + std::to_string(highscore);

		//Hiển thị khung hình hiện tại 

		SDL_RenderCopy(renderer, gTexture[0], NULL, &picture[0]);// Kết xuất hình ảnh nền

		//Kết xuất từng ô một 

		Render_Copy(renderer, gTexture, picture, data);



		renderTexture.loadFromRenderedText(currentscore, BLUE_COLOR, renderer, gFont);//Nội dung cần vẽ + Màu vẽ. (vẽ chữ)
		renderTexture.render(5, 5, renderer);//Tọa độ cần vẽ (chữ): x,y;

		renderTexture.loadFromRenderedText(_highscore, BLUE_COLOR, renderer, gFont);
		renderTexture.render(5, 55, renderer);
		//Cập nhật màn hình 
		SDL_RenderPresent(renderer);

		//Dừng SDL 
		SDL_Delay(1000 / FPS);

		if (check_win(data)) {
			SDL_Delay(1000);
			win();
			break;
		}
		if (check_lose(data)) {
			SDL_Delay(1000);
			lose();
			break;
		}
	}
}
