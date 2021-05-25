#include "Tetramino.h"
#include <cmath>
#include<iostream>


Tetramino::Tetramino() 
{
	for (int i = 0; i < 4; i++)
	{
		content[i] = i;
	}

	position = Vector2i(0,0);
	pivotPoint = Vector2f(0, 0);
	rotation = 0;
}

Tetramino::Tetramino(int tetramino[4], Vector2i pos, Vector2f pivot,Vector2i kick[5][4])
{
	
	for (int i = 0; i < 4; i++)
	{
		content[i] = tetramino[i];
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			kickTable[i][j] = kick[i][j];
		}
	}

	position = pos;
	pivotPoint = pivot;
	rotation = 0;
}

Tetramino::~Tetramino() {}

void Tetramino::SetPosition(Vector2i translation) 
{
	position += translation;
}

void Tetramino::SetRotation(int r) 
{
	rotation += r;
}

Vector2i Tetramino::GetPositon() 
{
	return position;
}

Vector2i* Tetramino::GetTetramino(int r)
{
	static Vector2i displayedTetramino[4];
	double a = r * PI;

	for (int i = 0; i < 4; i++)
	{
		//Get Piece Pos
		int x =  (content[i] % 4);
		int y =  (int)(content[i] / 4);

		//Rotate
		int xNew = round((cos(a) * (x - pivotPoint.x) - sin(a) * (y - pivotPoint.y)) + pivotPoint.x);
		int yNew = round((sin(a) * (x - pivotPoint.x) + cos(a) * (y - pivotPoint.y)) + pivotPoint.y);

		displayedTetramino[i] = Vector2i(xNew, yNew);
	}

	return displayedTetramino;
}

Vector2i* Tetramino::GetTetramino()
{
	return Tetramino::GetTetramino(rotation);
}

int Tetramino::GetRoatation() 
{
	return rotation;
}

Vector2i Tetramino::GetFromKickTable(int rotation, int test) 
{
	return kickTable[test][rotation];
}

Vector2f Tetramino::GetPivotPoint() 
{
	return pivotPoint;
}