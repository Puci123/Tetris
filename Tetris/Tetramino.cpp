#include "Tetramino.h"
#include <math.h>


Tetramino::Tetramino() 
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			content[y * 4 + x] = 0;
		}
	}

	position = Vector2i(0,0);
	pivotPoint = Vector2f(0, 0);
	rotation = 0;
}

Tetramino::Tetramino(int tetramino[4][4], Vector2i pos, Vector2f pivot)
{
	
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			content[y * 4 + x] = tetramino[x][y];
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

int* Tetramino::GetTetramino(int r)
{
	static int temp[16];
	float a = r * PI;

	for (int yO = 0; yO < 4; yO++)
	{
		for (int xO = 0; xO < 4; xO++)
		{
			int x = round((cos(a) * (xO - pivotPoint.x) - sin(a) * (yO - pivotPoint.y)) + pivotPoint.x);
			int y = round((sin(a) * (xO - pivotPoint.x) + cos(a) * (yO - pivotPoint.y)) + pivotPoint.y);

			temp[y * 4 + x] = content[yO * 4 + xO];
		}
	}

	return temp;
}

int* Tetramino::GetTetramino() 
{
	return Tetramino::GetTetramino(rotation);
}

int Tetramino::GetRoatation() 
{
	return rotation;
}