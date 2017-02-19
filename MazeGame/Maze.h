/*
 * Maze.h
 *
 *  Created on: Dec 11, 2014
 *      Author: 709252
 */

#ifndef MAZE_H_
#define MAZE_H_

#include "windows.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <fstream>
struct loc
{
	int x;
	int y;
	loc()
	{
		x = 0;
		y = 0;
	}
	loc(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
};

class Maze
{
	public:
		Maze();
		Maze(const std::string file);
		void generateMaze(std::string in);
		void displayMaze();
		bool validMove(loc location);
		void setLoc(loc loc,int value);
		int getElement(loc);
		loc getPlayerLoc();
		std::string getMapName();

	private:
		int maze[7][8];
		std::string mapName;

};




#endif /* MAZE_H_ */
