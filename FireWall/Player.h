/*
 * Player.h
 *
 *  Created on: May 27, 2015
 *      Author: 709252
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#define DARK_GREEN makecol(0,100,0)
#define BRIGHT_GREEN makecol(0,255,0)
#include <string> // temporary
#include <sstream>
#include <allegro.h> //temporary
#include <vector>

struct object
{
	int x;
	int y;
	int x1;
	int y1;
	object(int xx, int yy, int xx1, int yy1)
	{
		x = xx;
		y = yy;
		x1 = xx1;
		y1 = yy1;
	}
	object()
	{
		x = 0;
		y = 0;
		x1 = 0;
		y1 = 0;
	}
};

struct anim : object
{
	int delay;
	int maxFrame;
	int curFrame;
	int counter;
	anim(int xx, int yy, int xx1, int yy1, int d, int m, int c) : object(xx,yy,xx1,yy1)
	{
		delay = d;
		maxFrame = m;
		curFrame = c;
		counter = 0;
	}
};
using std::string;
using std::stringstream;
using std::vector;

BITMAP* grabframe(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame);

class Player {

private:
	const int SPEED_CAP;
	const float INCREMENT;
	const int MAX_COOL;
	const int PROJ_DELAY;
	int score;
	int shots;
	int count;
	BITMAP *blank;
	BITMAP *playfire;
	BITMAP *orbsprite;
	vector<BITMAP*> orb;


	float vel;
	int cool;
	void move();
	void moveProj();
	void generateProj();
	void drawPlayer();
	void drawProj();
public:
	object pos;
	//Player();
	BITMAP *play;
	Player(BITMAP* map);
	object getPos();
	vector<object> getProj();
	vector<anim> proj;
	const int MAX_SHOTS;
	void act();
	void addScore(int s);
	int getScore();
	void setShots();
	int getShots();

};

#endif /* PLAYER_H_ */
