/*
 * Maze.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: 709252
 */

#include "Maze.h"

using namespace std;

int maze[7][8];

Maze::Maze(){}

Maze::Maze(string filename)
{
	fill_n(maze[0],56,0);
	mapName = filename;
	generateMaze(filename);
}

loc Maze::getPlayerLoc()
{
	for(int row = 0; row < 7; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			if(maze[row][col]==2)
			{
				return loc(col,row);
			}

		}
	}
	return loc(-1,-1);
}
void Maze::setLoc(loc loc, int value)
{
	maze[loc.y][loc.x] = value;
}

int Maze::getElement(loc place)
{
	return maze[place.y][place.x];
}

bool Maze::validMove(loc move)
{
	if(move.x <0 || move.x > 7 || move.y < 0 || move.y > 6)
	{
		return false;
	}
	else
	{
		return (getElement(move) == 1);
	}
}

void Maze::displayMaze()
{
	for(int row = 0; row < 7; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			if(maze[row][col]==0)
			{
				cout << char(254) << " ";
			}
			if(maze[row][col]==1)
			{
				cout << " " << " ";
			}
			if(maze[row][col]==2)
			{
				cout << char(30) << " ";
			}

		}
		cout << endl;
	}
}

void Maze::generateMaze(string in)
{
	ifstream file(in.c_str());
	if(file.is_open())
	{
		for(int row = 0; row <7 ; row++)
		{
			for(int col = 0; col < 9; col++)
			{
				char data = file.get();
				if(data == 'X')
				{
					maze[row][col] = 0;
				}
				if(data == 'O')
				{
					maze[row][col] = 1;
				}
				if(data == 'P')
				{
					maze[row][col] = 2;
				}
			}
		}
	}
	else
	{
		cout << "Couldn't find file! Please restart the program and try again." << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
}

string Maze::getMapName()
{
	return mapName;
}
