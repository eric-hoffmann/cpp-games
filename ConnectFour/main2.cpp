#include <cstdlib>
#include <iostream>
#include "color.h"
#include <conio.h>
#include <limits>

using namespace std;
void displayBoard(int b[][7]);
void resetBoard(int b[][7]);
void placePiece(int b[][7]);
bool checkForWin(int b[][7]);
void changePlayer();
bool lineCheck(bool rorc,int index, int b[][7]);
bool checkFullBoard(int b[][7]);
bool diagCheck(int b[][7]);
bool gameOver = false;

int player = 1;

//system("cls");
int main(int argc, char *argv[])
{
    int board[6][7] = {{0, 1, 0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0, 0},
                      {0, 0, 2, 0, 0, 0, 0},
                      {0, 1, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 2, 1, 2, 1}};

    setcolor(BLUE, RED);
    cout<<"This is a test of the color"<<endl;
    setcolor(MAGENTA, BLUE);
    cout<<"Now to change color"<<endl;
    setcolor(WHITE, BLUE);
    for (int i = 1; i < 256; i++)
    {
        cout <<char(i)<<i<<" ";
        if (i%10 == 0)
        {
           cout <<endl<<endl;
           cout <<" "; 
        }
    }
    setcolor(BLUE, WHITE);
    cout <<endl << "Outputting my board"<<endl<<endl;
    displayBoard(board);
    resetBoard(board);
    cout << "Empty Board:" << endl;
    displayBoard(board);
    while(!gameOver)
    {
    	placePiece(board);
    	displayBoard(board);
    	if(checkForWin(board))
    	{
    		gameOver = true;
    	}
    	else
    	{
    		if(!checkFullBoard(board))
    		{
    			changePlayer();
    		}
    		else
    		{
    			gameOver = true;
    		}
    	}
    }
    if(player == 1)
    {
    	cout << "Congratulations Player 1! You Win!"<< endl;
    }
    else if(player == 2)
    {
    	cout << "Congratulations Player 2! You Win!"<< endl;
    }
    else
    {
    	cout << "Tie game! The board is full!" << endl;
    }
    cout <<endl<<endl;
    

    
    setcolor(WHITE, BLACK);
    system("PAUSE");
    return EXIT_SUCCESS;
}
bool checkFullBoard(int b[][7])
{
	for (int row = 0; row < 6; row ++)
	{
		for (int col = 0; col < 7; col ++)
		{
			if (b[row][col] == 0)
			{
				return false;
			}
		}
	}
	player = 3;
	return true;
}
bool checkForWin(int b[][7])
{

	for(int row = 0; row <6; ++row)
	{
		if(lineCheck(true,row,b))
		{
			cout << "Winning Row!" << endl;
			return true;
		}
	}
	for(int col = 0; col <7; ++col)
	{
		if(lineCheck(false,col,b))
		{
			cout << "Winning Column!" << endl;
			return true;
		}
	}
	if(diagCheck(b))
	{
		cout << "Winning Diagonal!" << endl;
		return true;
	}
	return false;
}
bool diagCheck(int b[][7])
{
	int count = 0;
	int connected = 0;
	for (int row = 5; row >= 3; row--)
	{
		for (int col = 0; col < 4; col++)
	    {
			count = 0;
			for (int i = 0, j = 0; i <= row || j <= (6-col); i++, j++)
			{
				if(b[row-i][col+j] == player)
				{
					count++;
				}
				else
				{
					count = 0;
				}
				if(count > connected)
				{
					connected = count;
				}
			}
	    }
		for (int col = 6; col >= 3; col--)
		{
			count=0;
			for (int i = 0, j = 0; i <= row || j <= col; i++, j++)
			{
				if(b[row-i][col-j] == player)
				{
					count++;
				}
				else
				{
					count = 0;
				}
				if(count > connected)
				{
					connected = count;
				}
			}
		}

	}
	if(connected >= 4)
	{
		return true;
	}
	return false;
}


bool lineCheck(bool rorc,int index, int b[][7]) //bool rorc - Is the function checking a row or column? - true = row, false = column
{
	int limit;
	int count = 0;
	int connected = 0;
	if(rorc)
	{
		limit = 7;
	}
	else
	{
		limit = 6;
	}

	for(int i = 0; i < limit; i++)
	{
		if(rorc)
		{
			if(b[index][i] == player)
			{
				count++;
			}
			else
			{
				count = 0;
			}

		}
		else
		{
			if(b[i][index] == player)
			{
				count++;
			}
			else
			{
				count = 0;
			}
		}
		if(count > connected)
		{
			connected = count;
		}

	}
	if (connected > 3)
	{
		return true;
	}
	return false;
}

void placePiece(int b[][7])
{
	int col;
	cout << "Player " << player <<", Please enter the column (1-7) in which you wish to place your piece: ";
	cin >> col;
	if(!cin.fail())
	{
		if(col > 0 && col < 8)
		{
			col--;
			for(int row = 5; row >= 0; row--)
			{
				if(b[row][col] == 0 )
				{
					b[row][col] = player;
					return;
				}
			}
		}
	}
	else
	{
		cin.clear();
		cin.ignore(numeric_limits<int>::max(),'\n');
	}
	cout << "That is not a valid input" << endl;
	placePiece(b);
}
void changePlayer()
{
	if(player == 1)
	{
		player = 2;
	}
	else
	{
		player = 1;
	}
}

void resetBoard(int b[][7])
{
	for (int row = 0; row < 6; row ++)
	{
		for (int col = 0; col < 7; col ++)
	    {
			b[row][col] = 0;
	    }
	}
	player = 1;
	gameOver = false;
}

void displayBoard(int b[][7])
{
     for (int row = 0; row < 6; row ++)
     {
         for (int col = 0; col < 7; col ++)
         {
             if (b[row][col] == 0)
             setcolor(WHITE, WHITE);
             else if (b[row][col] == 1)
             setcolor(RED, WHITE);
             else
             setcolor(BLACK, WHITE);
             cout << char(2)<<" ";
         }
         setcolor(WHITE,BLACK);
         cout << endl;
     }   
     setcolor(WHITE,BLACK);
     cout << endl<<endl;

}


