/*
 * Powerup.h
 *
 *  Created on: May 27, 2015
 *      Author: 709252
 */

#ifndef POWERUP_H_
#define POWERUP_H_

#include "Enemy.h"

class Powerup {
public:
	Powerup(BITMAP *map, Player &play);
	void act();
	void genPow();
	vector<object> getPos();
	BITMAP *powerup;
private:
	struct po : anim
	{
		bool dir; //true = up, false = down
		po(int xx, int yy, int xx1, int yy1, int d, int m, int c, bool direct) : anim(xx,yy,xx1,yy1,d,m,c)
		{
			dir = direct;
		}
	};
	const int POW_DELAY;
	void movePow();
	void drawPow();
	void checkCollide();
	Player &player;
	vector<po> pow;
	vector<BITMAP*> power;
	BITMAP *blank;



};

#endif /* POWERUP_H_ */
