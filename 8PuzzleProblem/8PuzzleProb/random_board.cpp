/*
Author: Alec Frey
Installation: MTSU
Profesor: Dr. Phillips
Class: CSCI4350
Purpse: This lab implements the puzzle to solve in the 8 puzzle problem.
*/

#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

const int BOARDSIZE = 3;

void InitializeBoard(char board[BOARDSIZE][BOARDSIZE]);
void DisplayBoard(char const board[BOARDSIZE][BOARDSIZE]);
void ShuffleBoard(char board[BOARDSIZE][BOARDSIZE], int seed, int moves);
void MoveRight(char board[BOARDSIZE][BOARDSIZE], int& x, int& y);
void MoveLeft(char board[BOARDSIZE][BOARDSIZE], int& x, int& y);
void MoveUp(char board[BOARDSIZE][BOARDSIZE], int& x, int& y);
void MoveDown(char board[BOARDSIZE][BOARDSIZE], int& x, int& y);

int main(int argc, char *argv[])
{
	//holds the board state
	char	board[BOARDSIZE][BOARDSIZE];
	int		seed = atoi(argv[1]);
	int		moves = atoi(argv[2]);
	
	//set board to initial
	InitializeBoard(board);

	//shuffle the board
	ShuffleBoard(board , seed, moves);

	//displays the board
	DisplayBoard(board);


	return 0;
}


void InitializeBoard(char board[BOARDSIZE][BOARDSIZE])
{
	for (int i = 0; i < BOARDSIZE; i++)
	{
		char a, b, c;
		cin >> a >> b >> c;
		board[i][0] = a;
		board[i][1] = b;
		board[i][2] = c;
	}

}

void ShuffleBoard(char board[BOARDSIZE][BOARDSIZE], int seed, int moves)
{
	//initialize random
	srand(seed);

	//holds the location of the 0
	int zeroX = 0;
	int zeroY = 0;

	//shuffle the board randomly based on the moves
	for (int i = 0; i < moves; i++)
	{
		//randomly selects a number between 0 and 4 
		int number = rand() % 4;
		switch (number)
		{
			case 0: // move left 
			{
				if (zeroY == 0) // cant move left, move right instead
				{
					MoveRight(board, zeroX, zeroY);
					break;
				}
				else
				{
					MoveLeft(board, zeroX, zeroY);
					break;
				}
			}
			case 1: // move up 
			{
				if (zeroX == 0) // cant move up, move down instead
				{
					MoveDown(board, zeroX, zeroY);
					break;
				}
				else
				{
					MoveUp(board, zeroX, zeroY);
					break;
				}
			}
			case 2:	// move right
			{
				if (zeroY == 2) // cant move right, move left instead
				{
					MoveLeft(board, zeroX, zeroY);
					break;
				}
				else
				{
					MoveRight(board, zeroX, zeroY);
					break;
				}
			}
			case 3:	// move down 
			{
				if (zeroX == 2) // cant move down, move up instead
				{
					MoveUp(board, zeroX, zeroY);
					break;
				}
				else
				{
					MoveDown(board, zeroX, zeroY);
					break;
				}
			}	

		}

	}

}

//moves the zero to the right
void MoveRight(char board[BOARDSIZE][BOARDSIZE], int& x, int& y)
{
	//swap the elements
	char temp = board[x][y + 1];
	board[x][y + 1] = '0';
	board[x][y] = temp;

	y += 1; // add 1 -> moved right
}

//moves the zero to the left
void MoveLeft(char board[BOARDSIZE][BOARDSIZE], int& x, int& y)
{
	//swap the elements
	char temp = board[x][y - 1];
	board[x][y - 1] = '0';
	board[x][y] = temp;

	y -= 1; // sub 1 from y-> moved right
}

//moves the zero up
void MoveUp(char board[BOARDSIZE][BOARDSIZE], int& x, int& y)
{
	//swap the elements
	char temp = board[x - 1][y];
	board[x - 1][y] = '0';
	board[x][y] = temp;

	x -= 1; // add to x -> moved up
}


//moves the zero down
void MoveDown(char board[BOARDSIZE][BOARDSIZE], int& x, int& y)
{
	//swap the elements
	char temp = board[x + 1][y];
	board[x + 1][y] = '0';
	board[x][y] = temp;

	x += 1; // sub 1 from y -> moved down
}

//displays the board 
void DisplayBoard(char const board[BOARDSIZE][BOARDSIZE])
{
	//loop through the board and output the data
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}
