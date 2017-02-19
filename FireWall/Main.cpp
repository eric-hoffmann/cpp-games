/*
 * Main.cpp
 *
 *  Created on: May 8, 2015
 *      Author: 709252
 */
#include "Game.h"
#include <ctime>
#define BLAZE_ORANGE makecol(255,102,0)

using namespace std;
// 1280x960
void init();
void deinit();

int main() {
	init();
	srand(time(NULL));
	BITMAP *blank = create_bitmap(1280,960);
	Player player(blank);
	Enemy enemy(blank,player);
	Powerup powerup(blank,player);
	Game game(blank,enemy,player,powerup);
	bool gameOver = false;
	bool first = true;
	while(!key[KEY_ESC] && !key[KEY_Y])
	{
		clear_bitmap(blank);
		game.startScreen();
		blit(blank,screen,0,0,0,0,1280,960);
	}
	while (!key[KEY_ESC] && !gameOver)
	{
		clear_bitmap(blank);
		game.playGame(first);
		first=false;
		textprintf_ex(blank,game.consoleSmall,5,5,BRIGHT_GREEN,0,"Score: %i",player.getScore());
		textprintf_ex(blank,game.consoleSmall,5,910,BRIGHT_GREEN,0,"Shots Left: %i",player.getShots());
		if(game.checkCollide(player.getPos(),enemy.getPos()))
		{
			gameOver=true;
		}

		blit(blank,screen,0,0,0,0,1280,960);
	}
	while (!key[KEY_ESC])
	{
		clear_bitmap(blank);
		game.endScreen();
		blit(blank,screen,0,0,0,0,1280,960);
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 960, 720, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}



