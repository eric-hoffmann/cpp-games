/*
 * Game.h
 *
 *  Created on: Dec 15, 2014
 *      Author: 709252
 */

#ifndef GAME_H_
#define GAME_H_

#include "Player.h"
#include "conio.h"

class Game
{
	public:
		Game();
		Game(std::string filename);
		void playGame();
	private:
		bool over;
		int getInput();
		Maze maze;
		Player player;

};



#endif /* GAME_H_ */
