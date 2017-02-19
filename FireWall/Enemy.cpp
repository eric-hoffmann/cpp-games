/*
 * Enemy.cpp
 *
 *  Created on: May 27, 2015
 *      Author: 709252
 */

#include "Enemy.h"

Enemy::Enemy(BITMAP *map,Player &play) : blank(map),player(play)
{
	enemy = load_bitmap("enemy.bmp",NULL);
}

vector<object> Enemy::getPos()
{
	vector<object> temp;
	for(unsigned int i = 0; i < pos.size(); i++)
	{
		temp.push_back(object(pos[i].x,pos[i].y,pos[i].x1,pos[i].y1));
	}
	return temp;
}

void Enemy::act()
{
	move();
	drawEnem();
	checkCollide();
}

void Enemy::genEnem()
{
	if(rand() % 2 == 0)
	{
		pos.push_back(en(1281,51,1351,172,false));
	}
	else
	{
		pos.push_back(en(1281,778,1351,899,true));
	}

}

void Enemy::move()
{
	for (int i = pos.size()-1; i >= 0; i--)
	{
		pos[i].x--;
		pos[i].x1--;
		if(pos[i].y <=51)
		{
			pos[i].direction = false;
		}
		if(pos[i].y1 >=899)
		{
			pos[i].direction = true;
		}
		if(pos[i].direction)
		{
			pos[i].y--;
			pos[i].y1--;
		}
		else
		{
			pos[i].y++;
			pos[i].y1++;
		}
		if(pos[i].x1 < 0)
		{
			pos.erase(pos.begin()+i);
		}
	}
}

void Enemy::drawEnem()
{
	for(unsigned int i = 0; i < pos.size(); i++)
	{
		draw_sprite(blank,enemy,pos[i].x,pos[i].y);
	}

}

void Enemy::checkCollide()
{
	for (int i = pos.size()-1; i >= 0; i--)
	{
		vector<object> temp = player.getProj();
		for(int j = temp.size()-1; j >= 0; j--)
		{
			if((temp[j].x < pos[i].x1 && temp[j].x > pos[i].x && temp[j].y > pos[i].y && temp[j].y < pos[i].y1)
			||(temp[j].x1 > pos[i].x && temp[j].x1 <pos[i].x1 && temp[j].y < pos[i].y1 && temp[j].y > pos[i].y)
			||(temp[j].x > pos[i].x && temp[j].x < pos[i].x1 && temp[j].y1 < pos[i].y1 && temp[j].y1 > pos[i].y)
			||(temp[j].x1 > pos[i].x && temp[j].x1 < pos[i].x1 && temp[j].y1 < pos[i].y1 && temp[j].y1 > pos[i].y))
			{
				pos.erase(pos.begin()+i);
				player.proj.erase(player.proj.begin()+j);
				player.addScore(25);
				break;
			}
		}
	}
}


