#include "Tetramino.h"
#include <math.h>

Tetramino::Tetramino(int tetramino[4][4], Vector2i pos, Vector2f pivot)
{
	
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			content[x][y] = tetramino[x][y];
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
	rotation += r * PI;
}

Vector2i Tetramino::GetPositon() 
{
	return position;
}

int* Tetramino::GetTetramino()
{
	int temp[4][4];

	for (int yO = 0; yO < 4; yO++)
	{
		for (int xO = 0; xO < 4; xO++)
		{
			int x = round((cos(rotation) * (xO - pivotPoint.x) - sin(rotation) * (yO - pivotPoint.y)) + pivotPoint.x);
			int y = round((sin(rotation) * (xO - pivotPoint.x) + cos(rotation) * (yO - pivotPoint.y)) + pivotPoint.y);

			temp[x][y] = content[xO][yO];
		}
	}

	return *temp;
}