/*
 * Game.h
 *
 *  Created on: May 27, 2015
 *      Author: 709252
 */

#ifndef GAME_H_
#define GAME_H_
#include "Powerup.h"


class Game {
public:
	//Game();
	Game(BITMAP* map, Enemy &enem, Player &play, Powerup &power);
	void playGame(bool first);
	FONT *console;
	FONT *consoleSmall;
	FONT *consoleSmaller;
	bool checkCollide(object thing, vector<object> stuff);
	void startScreen();
	void endScreen();
//	static BITMAP* grabframe(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame);
private:

	BITMAP *blank;
	Enemy &enemy;
	Player &player;
	Powerup &powerup;
	string back[16];
	vector<object> obj;
	const int DELAY;
	const int UPDATE_DELAY;
	const int COOL_MAX;
	int updateDelay;
	int cool;
	int counter;
	void drawBack();
	void drawObj();
	string generateLine();
	void generateObj();
	void moveObj();

};

#endif /* GAME_H_ */
