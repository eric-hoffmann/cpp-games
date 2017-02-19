/*
 * Game.cpp
 *
 *  Created on: May 27, 2015
 *      Author: 709252
 */

#include "Game.h"


//Game::Game()
//{
//	console = load_font("console_36.pcx",NULL,NULL);
//	blank = create_bitmap(1280,960);
//	counter = 0;
//	cool=0;
//	obj.push_back(object(1,830,1280,960));
//	obj.push_back(object(1,1,1280,120));
//	for(int i = 0; i < 16; i++)
//	{
//		stringstream temp;
//		while(text_length(console,temp.str().c_str()) < screen->w -5)
//		{
//			int ran = rand() % 2;
//			temp << ran;
//		}
//		back[i]=temp.str();
//	}
//}

Game::Game(BITMAP* map, Enemy &enem, Player &play, Powerup &power) : enemy(enem),player(play),powerup(power),DELAY(60),UPDATE_DELAY(10),COOL_MAX(300)
{
	console = load_font("console_36.pcx",NULL,NULL);
	consoleSmall = load_font("console_26.pcx",NULL,NULL);
	consoleSmaller = load_font("console_16.pcx",NULL,NULL);
	blank = map;
	counter = 0;
	cool=0;
	updateDelay = UPDATE_DELAY;
	obj.push_back(object(1,900,1280,960));
	obj.push_back(object(1,0,1280,50));
	for(int i = 0; i < 16; i++)
	{
		stringstream temp;
		while(text_length(console,temp.str().c_str()) < screen->w -5)
		{
			int ran = rand() % 2;
			temp << ran;
		}
		back[i]=temp.str();
	}
}

void Game::playGame(bool first)
{
	drawBack();
	generateObj();
	moveObj();
	drawObj();
	player.act();
	enemy.act();
	powerup.act();
	if(first)
	{
		textprintf_ex(blank,consoleSmaller,player.pos.x,player.pos.y1+12,BRIGHT_GREEN,0,"Press the Spacebar!");
		blit(blank,screen,0,0,0,0,1280,960);
		while(!key[KEY_SPACE]){}

	}
}

string Game::generateLine()
{
	stringstream temp;
	while(text_length(console,temp.str().c_str()) < screen->w -5)
	{
		int ran = rand() % 2;
		temp << ran;
	}
	return temp.str();
}

//void Game::drawBack()
//{
//	if( counter == DELAY)
//	{
//		counter = 0;
//		for(int i = 15; i > 0; i--)
//		{
//			back[i] = back[i-1];
//		}
//		back[0]=generateLine();
//	}
//	for(int y = 0, i = 0;y <screen->h;y+= text_height(console), i++)
//	{
//		textout_ex(blank,console,back[i].c_str(),5,y,DARK_GREEN,-1);
//	}
//	counter++;
//}
void Game::drawBack()
{
	if(updateDelay == UPDATE_DELAY)
	{
		updateDelay = 0;
		if(counter == DELAY)
		{
			counter = 0;
			for(int i = 15; i > 0; i--)
			{
				back[i] = back[i-1];
			}
			back[0]=generateLine();
		}

		counter++;
	}
	for(int y = 0, i = 0;y <screen->h;y+= text_height(console), i++)
	{
		textout_ex(blank,console,back[i].c_str(),5,y+counter,DARK_GREEN,-1);
	}
	updateDelay++;
}

void Game::generateObj()
{
	if(cool == 0)
	{
		int wmax = 50 + (rand() % 51);
		int hmax = 250 + (rand() % 281); //200
		int ran = rand() % 7;
		if(ran <3)
		{

			obj.push_back(object(1280,960,1280+wmax,960-hmax));
		}
		else if (ran < 5)
		{
			obj.push_back(object(1280,0,1280+wmax,hmax));
		}
		else if (ran < 6)
		{
			enemy.genEnem();
		}
		else
		{
			powerup.genPow();
		}
		cool = COOL_MAX + (rand()% 50);
	}

}

void Game::drawObj()
{
	for(unsigned int i = 0;i < obj.size(); i++)
	{
		rectfill(blank,obj[i].x,obj[i].y,obj[i].x1,obj[i].y1,BRIGHT_GREEN);
	}
}

void Game::moveObj()
{
	for(unsigned int i = 2;i < obj.size(); i++)
	{
		obj[i].x--;
		obj[i].x1--;
		if(obj[i].x1 <1)
		{
			obj.erase(obj.begin()+i);
		}
	}
	cool--;
}
bool Game::checkCollide(object thing,vector<object> stuff)
{
	for(unsigned int i = 0; i < obj.size();i++)
	{
		if(obj[i].y > obj[i].y1)//obstacle on bottom
		{
			if((thing.x < obj[i].x1 && thing.x > obj[i].x && thing.y > obj[i].y1 && thing.y < obj[i].y)
			||(thing.x1 > obj[i].x && thing.x1 <obj[i].x1 && thing.y < obj[i].y && thing.y > obj[i].y1)
			||(thing.x > obj[i].x && thing.x < obj[i].x1 && thing.y1 < obj[i].y && thing.y1 > obj[i].y1)
			||(thing.x1 > obj[i].x && thing.x1 < obj[i].x1 && thing.y1 < obj[i].y && thing.y1 > obj[i].y1))
			{
				return true;
			}
		}
		else//obstacle on top
		{
			if((thing.x < obj[i].x1 && thing.x > obj[i].x && thing.y > obj[i].y && thing.y < obj[i].y1)
			||(thing.x1 > obj[i].x && thing.x1 <obj[i].x1 && thing.y < obj[i].y1 && thing.y > obj[i].y)
			||(thing.x > obj[i].x && thing.x < obj[i].x1 && thing.y1 < obj[i].y1 && thing.y1 > obj[i].y)
			||(thing.x1 > obj[i].x && thing.x1 < obj[i].x1 && thing.y1 < obj[i].y1 && thing.y1 > obj[i].y))
			{
				return true;
			}
		}
	}
	for(unsigned int i = 0; i < stuff.size();i++)
	{
		if((thing.x < stuff[i].x1 && thing.x > stuff[i].x && thing.y > stuff[i].y && thing.y < stuff[i].y1)
		||(thing.x1 > stuff[i].x && thing.x1 <stuff[i].x1 && thing.y < stuff[i].y1 && thing.y > stuff[i].y)
		||(thing.x > stuff[i].x && thing.x < stuff[i].x1 && thing.y1 < stuff[i].y1 && thing.y1 > stuff[i].y)
		||(thing.x1 > stuff[i].x && thing.x1 < stuff[i].x1 && thing.y1 < stuff[i].y1 && thing.y1 > stuff[i].y))
		{
			return true;
		}
	}
	return false;
}

void Game::startScreen()
{
	drawBack();
	rectfill(blank,1,900,1280,960,BRIGHT_GREEN);
	rectfill(blank,1,0,1280,50,BRIGHT_GREEN);
	rectfill(blank,1,0,50,960,BRIGHT_GREEN);
	rectfill(blank,1230,0,1280,960,BRIGHT_GREEN);
	rectfill(blank,160,430,640,630,0);
	rectfill(blank,730,430,1110,530,0);
	rectfill(blank,730,650,1120,730,0);
	textprintf_centre_ex(blank,console,640,100,BRIGHT_GREEN,0,"Welcome to FireWall!");
	textprintf_centre_ex(blank,consoleSmall,640,200,BRIGHT_GREEN,0,"Directions:");
	textprintf_ex(blank,consoleSmaller,160,250,BRIGHT_GREEN,0,"This is you, the hacker:");
	textprintf_ex(blank,consoleSmaller,160,430,BRIGHT_GREEN,0,"Use the spacebar to");
	textprintf_ex(blank,consoleSmaller,160,430+25,BRIGHT_GREEN,0,"ascend. Use the up");
	textprintf_ex(blank,consoleSmaller,160,430+25+25,BRIGHT_GREEN,0,"arrow to fire orbs.");
	textprintf_ex(blank,consoleSmaller,160,430+25+25+25,BRIGHT_GREEN,0,"You have 10 orbs max");
	textprintf_ex(blank,consoleSmaller,160,430+25+25+25+25,BRIGHT_GREEN,0,"that regenerate over time.");
	textprintf_ex(blank,consoleSmaller,160,430+25+25+25+25+25,BRIGHT_GREEN,0,"Your goal is to survive as");
	textprintf_ex(blank,consoleSmaller,160,430+25+25+25+25+25+25,BRIGHT_GREEN,0,"long as possible by avoiding");
	textprintf_ex(blank,consoleSmaller,160,430+25+25+25+25+25+25+25,BRIGHT_GREEN,0,"enemies and obstacles.");
	draw_sprite(blank,player.play,330,290);
	textprintf_ex(blank,consoleSmaller,730,250,BRIGHT_GREEN,0,"This is an enemy virus:");
	draw_sprite(blank,enemy.enemy,850,290);
	textprintf_ex(blank,consoleSmaller,730,430,BRIGHT_GREEN,0,"Avoid them or vaporize");
	textprintf_ex(blank,consoleSmaller,730,430+25,BRIGHT_GREEN,0,"them with an orb.");
	textprintf_ex(blank,consoleSmaller,730,430+25+25,BRIGHT_GREEN,0,"Each kill is worth");
	textprintf_ex(blank,consoleSmaller,730,430+25+25+25,BRIGHT_GREEN,0,"25 points.");
	textprintf_ex(blank,consoleSmaller,730,550,BRIGHT_GREEN,0,"This is a powerup:");
	masked_blit(powerup.powerup,blank,0,0,850,580,61,61);
	textprintf_ex(blank,consoleSmaller,730,650,BRIGHT_GREEN,0,"Shoot or run into this");
	textprintf_ex(blank,consoleSmaller,730,650+25,BRIGHT_GREEN,0,"to recieve 50 points");
	textprintf_ex(blank,consoleSmaller,730,650+25+25,BRIGHT_GREEN,0,"and maximum ammo.");
	textprintf_centre_ex(blank,console,640,800,BRIGHT_GREEN,0,"Good Luck!");
	textprintf_centre_ex(blank,consoleSmaller,640,860,BRIGHT_GREEN,0,"Press Y to continue.");

}

void Game::endScreen()
{
	drawBack();
	rectfill(blank,1,900,1280,960,BRIGHT_GREEN);
	rectfill(blank,1,0,1280,50,BRIGHT_GREEN);
	rectfill(blank,1,0,50,960,BRIGHT_GREEN);
	rectfill(blank,1230,0,1280,960,BRIGHT_GREEN);
	rectfill(blank,350,200,930,390,0);
	textprintf_centre_ex(blank,console,640,100,BRIGHT_GREEN,0,"Game Over!");
	textprintf_centre_ex(blank,consoleSmall,640,200,BRIGHT_GREEN,0,"Your final score was");
	textprintf_centre_ex(blank,consoleSmall,640,250,BRIGHT_GREEN,0,"%i",player.getScore());
	textprintf_centre_ex(blank,consoleSmall,640,300,BRIGHT_GREEN,0,"Thanks for playing,");
	textprintf_centre_ex(blank,consoleSmall,640,350,BRIGHT_GREEN,0,"Press Escape to exit.");

}
//BITMAP* Game::grabframe(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame)
//{
//	BITMAP *temp = create_bitmap(width,height);
//	int x = startx + (frame % columns) * width;
//	int y = starty + (frame / columns) * height;
//	blit(source,temp,x,y,0,0,width,height);
//	return temp;
//}
