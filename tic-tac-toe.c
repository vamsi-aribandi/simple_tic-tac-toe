/*
 * CS50x Final project: tic-tac-toe using sdl2 and c
 * By Vamsi Krishna Aribandi(vka0000 on edx.org)
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define WINDOW_WIDTH (600)
#define WINDOW_HEIGHT (600)
// initialize global variables
char player = 'x';
SDL_Window* win;
SDL_Renderer* rend;
SDL_Texture* boardTexture = NULL;
int history[9];
int turn = 0;
SDL_Texture* tex[9] = {NULL};
char board[3][3] = {
						{'1', '2', '3'},
						{'4', '5', '6'},
						{'7', '8', '9'}
					};
// declare functions
void change_player(void);
void insert_and_check(int i);
void display_board(void);

int main(void) {
	// attempt to initialize graphics
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return 1;
	// create a window for the game
	win = SDL_CreateWindow("tic-tac-toe",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							WINDOW_WIDTH, WINDOW_HEIGHT,0);
	if (!win) {
		SDL_Quit();
		return 1;
	}
	// create a renderer, which sets up the graphics hardware
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	rend = SDL_CreateRenderer(win, -1, render_flags);
	if (!rend) {
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	// load the initial image data(the starting screen) into the graphics hardware's memory
	SDL_Texture* initial = IMG_LoadTexture(rend, "resources/initial.jpg");
	if (!initial) {
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, initial, NULL, NULL);
	SDL_RenderPresent(rend);
	int init = 0;
	// start screen loop
	while (!init) {
		// process events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					SDL_DestroyTexture(initial);
					SDL_DestroyRenderer(rend);
					SDL_DestroyWindow(win);
					SDL_Quit();
					return 0;
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_SPACE:
							init = 1;
							SDL_DestroyTexture(initial);
							break;
					}
			}
		}
	}
	// load the board image data into the graphics hardware's memory
	boardTexture = IMG_LoadTexture(rend, "resources/board.png");
	if (!boardTexture) {
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, boardTexture, NULL, NULL);
	SDL_RenderPresent(rend);
	int close_requested = 0;
	// game loop
	while (!close_requested) {
		// process events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					close_requested = 1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_1:
							if(board[0][0] == '1') {
								history[turn] = player * 1;
								turn++;
								display_board();
								insert_and_check(1);
								change_player();
								break;
							}
						case SDL_SCANCODE_2:
							if(board[0][1] == '2') {
								history[turn] = player * 2;
								turn++;
								display_board();
								insert_and_check(2);
								change_player();
								break;
							}
						case SDL_SCANCODE_3:
							if(board[0][2] == '3') {
								history[turn] = player * 3;
								turn++;
								display_board();
								insert_and_check(3);
								change_player();
								break;
							}
						case SDL_SCANCODE_4:
							if(board[1][0] == '4') {
								history[turn] = player * 4;
								turn++;
								display_board();
								insert_and_check(4);
								change_player();
								break;
							}
						case SDL_SCANCODE_5:
							if(board[1][1] == '5') {
								history[turn] = player * 5;
								turn++;
								display_board();
								insert_and_check(5);
								change_player();
								break;
							}
						case SDL_SCANCODE_6:
							if(board[1][2] == '6') {
								history[turn] = player * 6;
								turn++;
								display_board();
								insert_and_check(6);
								change_player();
								break;
							}
						case SDL_SCANCODE_7:
							if(board[2][0] == '7') {
								history[turn] = player * 7;
								turn++;
								display_board();
								insert_and_check(7);
								change_player();
								break;
							}
						case SDL_SCANCODE_8:
							if(board[2][1] == '8') {
								history[turn] = player * 8;
								turn++;
								display_board();
								insert_and_check(8);
								change_player();
								break;
							}
						case SDL_SCANCODE_9:
							if(board[2][2] == '9') {
								history[turn] = player * 9;
								turn++;
								display_board();
								insert_and_check(9);
								change_player();
								break;
							}
					}
			}
		}
	}
	SDL_DestroyTexture(boardTexture);
	for(int i = 0; i < 9; i++)
		SDL_DestroyTexture(tex[i]);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

// function to update board of what moves have been played and show the result of the game if it is done
void insert_and_check(int i) {
	int row = --i/3;
	int column = i%3;
	board[row][column] = player;
	char winner = 0;
	//Check diagnols for winning line
	if( (board[0][0] == board[1][1] && board[0][0] == board[2][2]) ||
		(board[0][2] == board[1][1] && board[0][2] == board[2][0]) )
		winner = player;
	else
	// Check rows and columns for a winning line
		for(int line = 0; line <= 2; line ++)
			if( (board[line][0] == board[line][1] && board[line][0] == board[line][2]) ||
				(board[0][line] == board[1][line] && board[0][line] == board[2][line]) )
				winner = player;
	// displaying result of game
	char *winnerFileName = NULL;
	if(winner == 'x')
		winnerFileName = "resources/winner_x.jpg";
	else if(winner == 'o')
		winnerFileName = "resources/winner_o.jpg";
	else if(turn == 9)
		winnerFileName = "resources/tie.jpg";
	if(winner != 0 || turn == 9) {
		SDL_Texture* winnerTexture = IMG_LoadTexture(rend, winnerFileName);
		if (!winnerTexture) {
			SDL_DestroyRenderer(rend);
			SDL_DestroyWindow(win);
			SDL_Quit();
		}
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, winnerTexture, NULL, NULL);
		SDL_RenderPresent(rend);
	}
}

// function to change player after a turn is done
void change_player(void) {
	if(player == 'x')
		player = 'o';
	else if(player == 'o')
		player = 'x';
}

// function clear the old board and show the new one
void display_board(void) {
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, boardTexture, NULL, NULL);
	SDL_Rect dest;
	// loop to show all the moves from "history"
	for(int i = 0; i < turn; i++) {
		if(history[i] % 'x' == 0)
			tex[i] = IMG_LoadTexture(rend, "resources/x.png");
		else if(history[i] % 'o' == 0)
			tex[i] = IMG_LoadTexture(rend, "resources/o.png");
		if (!tex[i]) {
			SDL_DestroyRenderer(rend);
			SDL_DestroyWindow(win);
			SDL_Quit();
		}
		dest.w = (int) WINDOW_WIDTH/3;
		dest.h = (int) WINDOW_HEIGHT/3;
		if(history[i] / 'x' == 1 || history[i] / 'o' == 1) {
			dest.x = 0;
			dest.y = 0;
		}
		if(history[i] / 'x' == 2 || history[i] / 'o' == 2) {
			dest.x = WINDOW_WIDTH/3;
			dest.y = 0;
		}
		if(history[i] / 'x' == 3 || history[i] / 'o' == 3) {
			dest.x = WINDOW_WIDTH*2/3;
			dest.y = 0;
		}
		if(history[i] / 'x' == 4 || history[i] / 'o' == 4) {
			dest.x = 0;
			dest.y = WINDOW_HEIGHT/3;
		}
		if(history[i] / 'x' == 5 || history[i] / 'o' == 5) {
			dest.x = WINDOW_WIDTH/3;
			dest.y = WINDOW_HEIGHT/3;
		}
		if(history[i] / 'x' == 6 || history[i] / 'o' == 6) {
			dest.x = WINDOW_WIDTH*2/3;
			dest.y = WINDOW_HEIGHT/3;
		}
		if(history[i] / 'x' == 7 || history[i] / 'o' == 7) {
			dest.x = 0;
			dest.y = WINDOW_HEIGHT*2/3;
		}
		if(history[i] / 'x' == 8 || history[i] / 'o' == 8) {
			dest.x = WINDOW_WIDTH/3;
			dest.y = WINDOW_HEIGHT*2/3;
		}
		if(history[i] / 'x' == 9 || history[i] / 'o' == 9) {
			dest.x = WINDOW_WIDTH*2/3;
			dest.y = WINDOW_HEIGHT*2/3;
		}
		SDL_RenderCopy(rend, tex[i], NULL, &dest);
	}
	SDL_RenderPresent(rend);
}
