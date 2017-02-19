/*
 * Player.cpp
 *
 *  Created on: May 27, 2015
 *      Author: 709252
 */

#include "Player.h"

Player::Player(BITMAP* map) : SPEED_CAP(2),INCREMENT(.0625/1.25),MAX_COOL(50),PROJ_DELAY(20),blank(map),MAX_SHOTS(10)
{
	cool = 0;
	play = load_bitmap("player.bmp",NULL);
	playfire = load_bitmap("playerfire.bmp",NULL);
	orbsprite = load_bitmap("plasmafinal.bmp",NULL);
	for(int i = 0; i < 7; i++)
	{
		orb.push_back(grabframe(orbsprite,20,20,0,0,7,i));
	}
	score = 0;
	shots = MAX_SHOTS;
	count = 0;
	vel = 0;
	pos = object(170,420,252,548);
}

void Player::act()
{
	move();
	drawPlayer();
	generateProj();
	moveProj();
	drawProj();
}

object Player::getPos()
{
	return pos;
}

void Player::move()
{
	if(key[KEY_SPACE])
	{
		if(vel > 0-SPEED_CAP)
		vel-=INCREMENT;
	}
	else
	{
		if(vel < SPEED_CAP)
		vel+=INCREMENT;
	}

	if(pos.y+vel > 0 && pos.y1+vel < 960 )
	{
		pos.y+=vel;
		pos.y1+=vel;
	}
	count++;
	if(count  % 20 == 0)
	{
		score++;
	}
	if(count % 1000 == 0 && shots < MAX_SHOTS)
	{
		shots++;
	}
 }

void Player::drawPlayer()
{
	if(key[KEY_UP])
	{
		draw_sprite(blank,playfire,pos.x,pos.y);
	}
	else
	{
		draw_sprite(blank,play,pos.x,pos.y);
	}

}
void Player::generateProj()
{
	if(key[KEY_UP] && shots > 0 && cool == 0)
	{
		proj.push_back(anim(pos.x+75,pos.y+20,pos.x+95,pos.y+40,PROJ_DELAY,7,0));
		cool = MAX_COOL;
		shots -= 1;
	}

}

void Player::moveProj()
{
	for (int i = proj.size()-1; i >= 0; i--)
	{
		proj[i].x++;
		proj[i].x1++;
		if(proj[i].x > 1280)
		{
			proj.erase(proj.begin()+i);
		}
	}
	if(cool > 0)
		cool--;
}

void Player::drawProj()
{
	for (unsigned int i = 0; i < proj.size(); ++i)
	{
		if(proj[i].counter >= proj[i].delay)
		{
			if(proj[i].curFrame < proj[i].maxFrame-1)
			{
				proj[i].curFrame++;
			}
			else
			{
				proj[i].curFrame = 0;
			}
			proj[i].counter = 0;
		}
		draw_sprite(blank,orb[proj[i].curFrame],proj[i].x,proj[i].y);
		proj[i].counter++;
	}

}
vector<object> Player::getProj()
{
	vector<object> temp;
	for(unsigned int i = 0; i < proj.size(); i++)
	{
		temp.push_back(object(proj[i].x,proj[i].y,proj[i].x1,proj[i].y1));
	}
	return temp;
}

void Player::addScore(int s)
{
	score+=s;
}

int Player::getScore()
{
	return score;
}
void Player::setShots()
{
	shots = 10;
}
int Player::getShots()
{
	return shots;
}


BITMAP* grabframe(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame)
{
	BITMAP *temp = create_bitmap(width,height);
	int x = startx + (frame % columns) * width;
	int y = starty + (frame / columns) * height;
	blit(source,temp,x,y,0,0,width,height);
	return temp;
}


