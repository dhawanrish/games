#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver = false;
const int width = 40;
const int height = 40;
int x, y, foodX, foodY ,score;

int xTail[100], yTail[100];
int nTail;

enum eDirection
{
	Stop = 0,
	Left,
	Right,
	Up,
	Down
};

eDirection dir;

void Setup()
{
	gameOver = false;
	dir = Stop;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
}

bool Search(int *arr, int nTail, int item)
{
	for (int i = 0; i < nTail; i++)
	{
		if (arr[i] == item)
			return true;
	}
	return false;
}
void Draw()
{
	system("cls"); // system("clear");

	for (int j = 0; j < width + 1; j++)
		cout << "#";
	cout << endl;
	int k;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width-1)
				cout << "#";
			if (i == y && j == x)
			{
				cout << "O";
			}
			else if (i == foodY && j == foodX)
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (k = 0; k < nTail; k++)
				{
					if (xTail[k] == j && yTail[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}


	for (int j = 0; j < width + 1; j++)
		cout << "#";
	cout << endl;
	cout << "Score :" << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 's':
			dir = Down;
			break;
		case 'w':
			dir = Up;
			break;
		case 'm':
			gameOver = true;
			break;
		}
	}

}

void Logic()
{
	int prevX = xTail[0];
	int prevY = yTail[0];
	int prev2X, prev2Y;
	xTail[0] = x;
	yTail[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = xTail[i];
		prev2Y = yTail[i];
		xTail[i] = prevX;
		yTail[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case Up:
		y--;
		break;
	case Down:
		y++;
		break;
	case Left:
		x--;
		break;
	case Right:
		x++;
		break;
	default:
		break;
	}

	if (x >= width-1 || x<0 || y>=height-1 || y < 0)
		gameOver = true;
	if (x == foodX && y == foodY)
	{
		score += 10;
		foodX = rand() % height;
		foodY = rand() % width;
		nTail++;
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		//Sleep(20);
	}
	return 0;
}
