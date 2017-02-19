/*
 * Powerup.cpp
 *
 *  Created on: May 27, 2015
 *      Author: 709252
 */

#include "Powerup.h"

Powerup::Powerup(BITMAP *map, Player &play) : POW_DELAY(20),player(play), blank(map)
{
	powerup = load_bitmap("powerup.bmp",NULL);
	for(int i = 0; i < 7; i++)
	{
		power.push_back(grabframe(powerup,61,61,0,0,4,i));
	}
}

void Powerup::act()
{
	movePow();
	drawPow();
	checkCollide();
}

void Powerup::genPow()
{
	if(rand() % 2 == 0)
	{
		pow.push_back(po(1281,51,1342,112,POW_DELAY,4,0,false));
	}
	else
	{
		pow.push_back(po(1281,830,1342,899,POW_DELAY,4,0,true));
	}
}

void Powerup::movePow()
{
	for (int i = pow.size()-1; i >= 0; i--)
		{
			pow[i].x--;
			pow[i].x1--;
			if(pow[i].y <=51)
			{
				pow[i].dir = false;
			}
			if(pow[i].y1 >=899)
			{
				pow[i].dir = true;
			}
			if(pow[i].dir)
			{
				pow[i].y--;
				pow[i].y1--;
			}
			else
			{
				pow[i].y++;
				pow[i].y1++;
			}
			if(pow[i].x1 < 0)
			{
				pow.erase(pow.begin()+i);
			}
		}
}

void Powerup::drawPow()
{
	for (unsigned int i = 0; i < pow.size(); ++i)
		{
			if(pow[i].counter >= pow[i].delay)
			{
				if(pow[i].curFrame < pow[i].maxFrame-1)
				{
					pow[i].curFrame++;
				}
				else
				{
					pow[i].curFrame = 0;
				}
				pow[i].counter = 0;
			}
			draw_sprite(blank,power[pow[i].curFrame],pow[i].x,pow[i].y);
			pow[i].counter++;
		}
}

void Powerup::checkCollide()
{
	for (int i = pow.size()-1; i >= 0; i--)
	{
		vector<object> temp = player.getProj();
		for(int j = temp.size()-1; j >= 0; j--)
		{
			if((temp[j].x < pow[i].x1 && temp[j].x > pow[i].x && temp[j].y > pow[i].y && temp[j].y < pow[i].y1)
			||(temp[j].x1 > pow[i].x && temp[j].x1 <pow[i].x1 && temp[j].y < pow[i].y1 && temp[j].y > pow[i].y)
			||(temp[j].x > pow[i].x && temp[j].x < pow[i].x1 && temp[j].y1 < pow[i].y1 && temp[j].y1 > pow[i].y)
			||(temp[j].x1 > pow[i].x && temp[j].x1 < pow[i].x1 && temp[j].y1 < pow[i].y1 && temp[j].y1 > pow[i].y))
			{
				pow.erase(pow.begin()+i);
				player.proj.erase(player.proj.begin()+j);
				player.addScore(50);
				player.setShots();
				break;
			}
		}
	}
	for (int i = pow.size()-1; i >= 0; i--)
	{
		object temp = player.getPos();
		if((temp.x < pow[i].x1 && temp.x > pow[i].x && temp.y > pow[i].y && temp.y < pow[i].y1)
		||(temp.x1 > pow[i].x && temp.x1 <pow[i].x1 && temp.y < pow[i].y1 && temp.y > pow[i].y)
		||(temp.x > pow[i].x && temp.x < pow[i].x1 && temp.y1 < pow[i].y1 && temp.y1 > pow[i].y)
		||(temp.x1 > pow[i].x && temp.x1 < pow[i].x1 && temp.y1 < pow[i].y1 && temp.y1 > pow[i].y))
		{
			pow.erase(pow.begin()+i);
			player.addScore(50);
			player.setShots();
			break;
		}
	}
}

vector<object> Powerup::getPos()
{
	vector<object> temp;
	for(unsigned int i = 0; i < pow.size(); i++)
	{
		temp.push_back(object(pow[i].x,pow[i].y,pow[i].x1,pow[i].y1));
	}
	return temp;
}


