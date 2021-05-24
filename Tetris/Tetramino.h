#pragma once
#include<SFML/Graphics.hpp>
#define PI 1.5707963268

using namespace sf;

class Tetramino
{
	private:
		int content[4];
		int rotation;
		
		Vector2i position;
		Vector2f pivotPoint;
		

	public: 
		Tetramino(int[4],Vector2i,Vector2f);
		Tetramino();
		~Tetramino();
		
		void SetPosition(Vector2i);
		void SetRotation(int);

		int* GetTetramino();
		int* GetTetramino(int);

		Vector2i GetPositon();
		int GetRoatation();
};

