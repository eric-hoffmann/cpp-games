/*
 * Enemy.h
 *
 *  Created on: May 27, 2015
 *      Author: 709252
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "Player.h"

class Enemy
{
public:
	Enemy(BITMAP *map, Player &play);
	BITMAP *enemy;
	vector<object> getPos();
	void act();
	void genEnem();
	void checkCollide();
private:
	struct en : object
	{
		bool direction;//true = up, false = down
		en(int xx, int yy, int xx1, int yy1, bool d) : object(xx,yy,xx1,yy1)
		{
			direction = d;
		}
	};

	void drawEnem();
	void move();

	BITMAP *blank;
	Player &player;
	vector<en> pos;

};

#endif /* ENEMY_H_ */
