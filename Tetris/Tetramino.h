#pragma once
#include<SFML/Graphics.hpp>
#include <cmath>

#define PI 1.5707963268

using namespace sf;

class Tetramino
{
	private:
		int content[4];
		int rotation;
		Vector2i kickTable[5][4];

		Vector2i position;
		Vector2f pivotPoint;
		

	public: 
		Tetramino(int[4],Vector2i,Vector2f,Vector2i[5][4]);
		Tetramino();
		~Tetramino();
		
		void SetPosition(Vector2i);
		void SetRotation(int);

		Vector2i* GetTetramino();
		Vector2i* GetTetramino(int);

		Vector2i GetPositon();
		Vector2i GetFromKickTable(int rotation, int test);
		int GetRoatation();
};

