#include "Player.h"

using namespace std;

Player::Player(Maze* m, loc place, int s)
{
	maze = m;


	steps = s;
	locat.x = place.x;
	locat.y = place.y;
	maze->setLoc(locat,2);
}
Player::Player(){}//just necessary for the .h default object. Always overwritten

loc Player::getLoc()
{
	return locat;
}

bool Player::isWinner()
{
	return (locat.x == 7);
}
void Player::checkMove(int dir)
{

	switch(dir)
	{
		case 0:
			{
				loc space(locat.x,locat.y+1);
				move(space);
			}
			break;
		case 1:
			{
				loc space(locat.x+1,locat.y);
				move(space);
			}
			break;
		case 2:
			{
				loc space(locat.x,locat.y-1);
				move(space);
			}
			break;
		case 3:
			{
				loc space(locat.x-1,locat.y);
				move(space);
			}
			break;
		default:
			break;
	}

}

void Player::move(loc next)
{
	if(maze->validMove(next))
	{
		//cout << "Player move successful!" << endl;
		maze->setLoc(locat,1);
		maze->setLoc(next,2);
		locat = maze->getPlayerLoc();
		steps++;
	}
}

void Player::reset(loc place)
{
	locat = maze->getPlayerLoc();
	steps = 0;
}

int Player::getSteps()
{
	return steps;
}
