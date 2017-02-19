/*
 * Player.h
 *
 *  Created on: Dec 11, 2014
 *      Author: 709252
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Maze.h"

enum
{
	U,L,D,R
};

class Player
{

	public:
		Player();
		Player(Maze* m, loc place = loc(3,0), int s = 0);
		void checkMove(int dir);
		loc getLoc();
		bool isWinner();
		int getSteps();
		void reset(loc place);

	private:
		void move(loc next);
		Maze* maze;
		loc locat;
		int steps;
};




#endif /* PLAYER_H_ */
