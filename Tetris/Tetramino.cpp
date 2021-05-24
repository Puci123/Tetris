#include "Tetramino.h"
#include <math.h>
#include<iostream>


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

Tetramino::Tetramino(int tetramino[4], Vector2i pos, Vector2f pivot)
{
	
	for (int i = 0; i < 4; i++)
	{
		content[i] = tetramino[i];
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
	return content;
}

int* Tetramino::GetTetramino() 
{
	return Tetramino::GetTetramino(rotation);
}

int Tetramino::GetRoatation() 
{
	return rotation;
}