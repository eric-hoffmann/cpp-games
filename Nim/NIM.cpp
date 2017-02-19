#include <ctime>
#include <string>
#include <iostream>

using namespace std;

bool isSmart, turn, game = true;
int pile = 0;
double smart = 0;

void playerMove()
{
	bool done = false;
	int marble = 0;
	do
	{
		if (pile > 1)
		{
			cout << "Please enter a number between 1 and " << pile/2 << ": ";
			cin >> marble;
			cout << endl;
			if (marble < 1 || marble > pile/2)
			{
				cout << "That is not a valid number. Please enter a correct value." << endl;
			}
			else
			{
				done = !done;
			}
		}
		else
		{
			cout << "Please enter the number 1: ";
			cin >> marble;
			if (marble != 1)
			{
				cout << "That is not a valid number. Please enter the correct value." << endl;
			}
			else
			{
				done = !done;
			}
		}
	}while(!done);
	pile = pile - marble;
	cout << "You take " << marble << " marbles!" << endl;
	cout << "The pile has " << pile << " marbles left." << endl <<endl;
	cout << "Computer's move!" << endl;
}
void compMove()
{
	int marble = 0;

	if (isSmart)
	{
		bool done = false;
		if(pile > 3)
		{
			int take = pile / 2;
			do
			{
				marble = take;
				int left = pile - marble;
				switch (left)
				{
				case 1: done = !done;
					break;
				case 3: done = !done;
					break;
				case 7: done = !done;
					break;
				case 15: done = !done;
					break;
				case 31: done = !done;
					break;
				case 63: done = !done;
					break;
				default:
					break;
				}
				take--;
			}while (!done);
		}
		else
		{
			marble = 1;
		}
	}
	else
	{
		if(pile > 3)
		{
			do
			{
				marble = rand() % (pile / 2);
			}while (marble < 1 || marble > pile/2);
		}
		else
		{
			marble = 1;
		}
	}
	pile = pile - marble;
	cout << "The computer takes " << marble << " marbles!" << endl;
	cout << "The pile has " << pile << " marbles left." << endl <<endl;
	cout << "Your move!" << endl;
}

int main()
{
	
	srand(time(NULL));
	smart =  (rand() % 10) /  10.0;
	isSmart = (smart < .5);
	pile = rand() % 100 + 1;
    isSmart = true;

	cout << "Welcome to the game of nimh!" << endl;
	cout << "The pile size is " << pile << endl;
	cout << "The computer is running in ";
	if (isSmart)
	{
		cout << "smart mode!" << endl;
	}
	else
	{
		cout << "random mode!" << endl;
	}

	if (((rand() % 10) / 10.0) < .5)
	{
		cout << "It's your move first!" << endl;
		turn = true;
	}
	else
	{
		cout << "The computer gets the first move!" << endl;
		turn = false;
		turn = true;
	}
	do
	{
		if(turn)
		{
			playerMove();
		}
		else
		{
			compMove();
		}

		if(pile < 1)
		{
			if (turn)
			{
				cout << "You lose... Thanks for playing!";
			}
			else
			{
				cout << "You win! Thanks for playing!";
			}
			cout << endl;
			game = false;
		}
		turn = !turn;
	}while(game);
	system("pause");
	return 0;
}