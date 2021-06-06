
#include <iostream>
#include  <stdlib.h>


using namespace std;



void dispalyBoard(int SIZE, int **board)
{
	
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (board[i][j] == -9)
				cout << "	X	";
			else if (board[i][j] == -4)
				cout << "	O	";
			else
				cout << "	" <<board[i][j] << "	";
			if (j == SIZE - 1) 
			{
				cout << "	";
			}else cout << "|";
		}
		cout << endl;
		if (i != SIZE - 1) 
		{
			for (int k = 0; k < SIZE; k++)
			{
				if (k == SIZE - 1) { cout << "-----------------"; }
				else
					cout << "-----------------";

			}
		}
		cout << endl;
	}
}

void initialise(int** board, int SIZE)
{
	// Wype³nienie tablicy 1-SIZE*SIZE (pusta)
	int nr_pola = 1;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			board[i][j] = nr_pola;
			nr_pola++;
		}
	}

	
}

void makeMove(int** board, int SIZE, int move, int turn)
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (board[i][j] == move)
			{
				board[i][j] = turn;
			}
			
		}
	}
}

bool isValidMove(int** board, int SIZE, int move)
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (board[i][j] == move && board[i][j] != -9 && board[i][j] != -4)
			{
				return true;
			}
		}
	}
	return false;
}

bool isMovesLeft(int** board, int SIZE)
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (board[i][j] != -9 && board[i][j] != -4)
				return true;
	return false;
}

int evaluate(int** board, int SIZE)
{
	int x = 0;
	int o = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == -9)
			{
				x++;
			}
			else if (board[i][j] == -4)
			{
				o++;
			}
		}
		if (x == SIZE)
			return -10;
		if (o == SIZE)
			return +10;
		x = 0;
		o = 0;
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[j][i] == -9)
			{
				x++;
			}
			else if (board[j][i] == -4)
			{
				o++;
			}
		}
		if (x == SIZE)
			return -10;
		if (o == SIZE)
			return +10;
		x = 0;
		o = 0;
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (board[i][i] == -9)
		{
			x++;
		}
		else if (board[i][i] == -4)
		{
			o++;
		}
	}
	if (x == SIZE)
		return -10;
	if (o == SIZE)
		return +10;
	x = 0;
	o = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (board[i][SIZE - 1 - i] == -9)
		{
			x++;
		}
		else if (board[i][SIZE - 1 - i] == -4)
		{
			o++;
		}
	}
	if (x == SIZE)
		return -10;
	if (o == SIZE)
		return +10;
	x = 0;
	o = 0;

	return 0;
}

int minimax(int** board, int SIZE, int depth, bool isMax)
{
	int score = evaluate(board,SIZE);
	int temp=0;

	if (score == 10)
		return score;

	if (score == -10)
		return score;
	
	if (isMovesLeft(board,SIZE) == false)
		return 0;
	
	if (isMax)
	{
		int best = -1000;


		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
			
				if (board[i][j] != -9 && board[i][j] != -4) // !-9 && !-4
				{
					
					 temp = board[i][j];
					board[i][j] = -4;

					
					best = max(best,
						minimax(board,SIZE ,depth + 1, !isMax));
					
					board[i][j] = temp;
					temp = 0;
				}
			}
		}
		return best;
	}
	else
	{
		int best = 1000;

		
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
			
				if (board[i][j] != -9 && board[i][j] != -4)
				{
				
					temp = board[i][j];
					board[i][j] = -9;

					
					best = min(best,
						minimax(board,SIZE ,depth + 1, !isMax));
					
					board[i][j] = temp;
					temp = 0;
				}
			}
		}
		return best;
	}
	
}

int findBestMove(int** board, int SIZE)
{
	int bestVal = -1000;
	int bestMove;

	int temp = 0;


	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
	
			if (board[i][j] != -9 && board[i][j] != -4)
			{
				temp = board[i][j];
				board[i][j] = -4;
				
				int moveVal = minimax(board,SIZE ,0, false);

			
				board[i][j] = temp;
				temp = 0;

				if (moveVal > bestVal)
				{
					bestMove = (j + 1) + i * SIZE;
					
					bestVal = moveVal;
				}
			}
		}
	}

	return bestMove;
}

bool gameOver(int**board, int SIZE)
{
	int x = 0;
	int o = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == -9)
			{
				x++;
			}
			else if (board[i][j] == -4)
			{
				o++;
			}
		}
		if (x == SIZE)
		{
			cout << "WYGRANA!" << endl;
			return true;
		}
		if (o == SIZE)
		{
			cout << "Przegrana :(" << endl;
			return true;
		}
		x = 0;
		o = 0;
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[j][i] == -9)
			{
				x++;
			}
			else if (board[j][i] == -4)
			{
				o++;
			}
		}
		if (x == SIZE)
		{
			cout << "WYGRANA!" << endl;
			return true;
		}
		if (o == SIZE)
		{
			cout << "Przegrana :(" << endl;
			return true;
		}
		x = 0;
		o = 0;
	}

	for (int i = 0; i < SIZE; i++)
	{
		if (board[i][i] == -9)
		{
			x++;
		}
		else if (board[i][i] == -4)
		{
			o++;
		}
	}

	if (x == SIZE)
	{
		cout << "WYGRANA!" << endl;
		return true;
	}
	if (o == SIZE)
	{
		cout << "Przegrana :(" << endl;
		return true;
	}
	x = 0;
	o = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (board[i][SIZE -1 - i] == -9)
		{
			x++;
		}
		else if (board[i][SIZE -1 - i] == -4)
		{
			o++;
		}
	}
	if (x == SIZE)
	{
		cout << "WYGRANA!" << endl;
		return true;
	}
	if (o == SIZE)
	{
		cout << "Przegrana :(" << endl;
		return true;
	}
	x = 0;
	o = 0;

	if (isMovesLeft(board, SIZE) == false) 
	{
		cout << "Remis" << endl;
		return true;
	}
	return false;
}

void play()
{
	int SIZE;
	int b=1;

	cout << "TIC TAC TOE" << endl;
	cout << "Podaj wielkosc planszy (dlugosc boku): ";
	cin >> SIZE;

	int** board = new int* [SIZE];
	for (int i = 0; i < SIZE; ++i)
	{
		board[i] = new int[SIZE];
	}


	initialise(board, SIZE);
	dispalyBoard(SIZE, board);

	while (1)
	{
		int move = 0;
		int move2 = 0;
		int move_temp = 0;
		
		cout << "Podaj swoj ruch: ";
		while (isValidMove(board, SIZE, move) == false)
		{
			cin >> move;
			isValidMove(board, SIZE, move);
		}
		makeMove(board, SIZE, move, -9);
		gameOver(board, SIZE);
		system("cls");
		dispalyBoard(SIZE, board);
		if (gameOver(board, SIZE) == true)
			break;
		if (b <= SIZE / 2 && SIZE !=3)
		{
			move_temp = move-1;
			while (isValidMove(board, SIZE, move_temp) == false)
			{
				move_temp++;
				if (move_temp == SIZE * SIZE)
				{
					move_temp--;
				}

			}
			makeMove(board, SIZE, move_temp, -4);
			gameOver(board, SIZE);
			system("cls");
			dispalyBoard(SIZE, board);
			if (gameOver(board, SIZE) == true)
				break;
		}
		else 
		{
			move2 = findBestMove(board, SIZE);
			makeMove(board, SIZE, move2, -4);
			gameOver(board, SIZE);
			system("cls");
			dispalyBoard(SIZE, board);
			if (gameOver(board, SIZE) == true)
				break;
		}
		b++;

	/*	Move bestMove = findBestMove(board, SIZE);
		move2 = (bestMove.col + 1) + bestMove.row * SIZE;
		makeMove(board, SIZE, move2, -4);
		gameOver(board, SIZE);
		system("cls");
		dispalyBoard(SIZE, board);
		if (gameOver(board, SIZE) == true)
			break;
			*/
	}

	for (int i = 0; i < SIZE; ++i)
	{
		delete[] board[i];
	}
	delete[] board;	
}

int main()
{ 
	
	play();
	
	return 0;
}