#include "Game.h"

using namespace std;

Game::Game(){}

Game::Game(string filename)
{
	maze = Maze(filename);
	player = Player(&maze,maze.getPlayerLoc());
	over = false;
}

void Game::playGame()
{
	while(!over)
	{
		system("cls");
		cout << "Use the arrow keys to move your character!" << endl;
		maze.displayMaze();
		player.checkMove(getInput());
		//loc test = maze.getPlayerLoc();
		//cout << "Player Location: x " <<test.x << " y " << test.y << endl;
		if(player.isWinner())
		{
			system("cls");
			cout << "Use the arrow keys to move your character!" << endl;
			maze.displayMaze();
			cout << "Congratulation! You escaped the maze with a total of " << player.getSteps() << " steps!" << endl;
			cout << "Would you like to try again? Press y for yes or n for no." << endl;
			bool properResponse = false;
			while(!properResponse)
			{
				int response = getInput();
				if(response == -2)
				{
					over = true;
					properResponse = true;
				}
				if(response == -1)
				{
					maze.generateMaze(maze.getMapName());
					player.reset(maze.getPlayerLoc());
					properResponse = true;
				}
			}
		}
	}

}

int Game::getInput()
{
	int key;
	key = _getch ();
	if (key == 0 || key == 0xE0)
	{
	    switch (_getch ())
	    {
	        case 72:
	            return D;
	            break;
	        case 75:
	        	return R;
	        	break;
	        case 80:
	            return U;
	            break;
	        case 77:
	        	return L;
	        	break;
	        default:
	        	return -3;
	        	break;
	    }
	}
	if(key == 'y')
	{
		return -1;
	}
	if (key == 'n')
	{
		return -2;
	}
	return -3;
}

