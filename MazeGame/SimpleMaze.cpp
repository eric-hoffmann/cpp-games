#include "Game.h"

using namespace std;

int main()
{
	cout << "Please enter the name of the map you wish to load (filename.txt): ";
	string map;
	cin >> map;
	Game game = Game(map);
	game.playGame();
	return 0;
}



