#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<thread>
#include<windows.h>

#include "Tetramino.h"


using namespace sf;

Vector2i boardSize(20, 20);
Vector2f cellSize(30, 30);
Tetramino tetraminos[7];

int* board = nullptr;


void CreateTetraminos()
{
    int i[4][4] = { 0,1,0,0,
                   0,1,0,0,
                   0,1,0,0,
                   0,1,0,0, };

    int j[4][4] = { 0,1,0,0,
                    0,1,0,0,
                    1,1,0,0,
                    0,0,0,0, };

    int l[4][4] = { 0,0,1,0,
                   0,0,1,0,
                   0,0,1,1,
                   0,0,0,0, };

    int o[4][4] = { 0,0,0,0,
                    0,1,1,0,
                    0,1,1,0,
                    0,0,0,0, };

    int s[4][4] = { 0,0,1,1,
                   0,1,1,0,
                   0,0,0,0,
                   0,0,0,0, };

    int t[4][4] = { 0,1,0,0,
                    1,1,1,0,
                    0,0,0,0,
                    0,0,0,0, };

    int z[4][4] = {1,1,0,0,
                   0,1,1,0,
                   0,0,0,0,
                   0,0,0,0, };

    tetraminos[0] = Tetramino(i, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[1] = Tetramino(j, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[2] = Tetramino(l, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[3] = Tetramino(o, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[4] = Tetramino(s, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[5] = Tetramino(t, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[6] = Tetramino(z, Vector2i(0, 0), Vector2f(1.5f, 1.5f));

}

void DisplayTetramino(Vector2i pos, int* tetramino) 
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (tetramino[y * 4 + x] == 1)
            {
                board[(y + pos.y) * boardSize.x + x + pos.x] = 1;

            }
        }
    }
}

void ClearTetramino(Vector2i pos, int* tetramino)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (tetramino[y * 4 + x] == 1)
            {
                board[(y + pos.y) * boardSize.x + x + pos.x] = 0;

            }
        }
    }
}


int main()
{

    //Awake
    RenderWindow window(VideoMode(600, 600), "Tetris"); //Create window
    window.setFramerateLimit(60);
    
    board = new int[boardSize.x * boardSize.y];         //create paly board 0 empty, 1 filled

    //fil board
    for (int i = 0; i < boardSize.x * boardSize.y; i++) { board[i] = 0;}

   
    CreateTetraminos();

    //Game varible
    Tetramino curent = tetraminos[0];
    
    //Timing
    int sleepTime = 35;
    int tetaminoStop = 20;
    int counter = 0;

    //Debug
    curent.SetPosition(Vector2i(1,1));
    //    


    //Game loop
    while (window.isOpen())
    {
       
        //--------Timing--------//
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        counter += 1;

        //--------Input--------//

        //Pool event
        Event event;
        while (window.pollEvent(event))
        {
            //Input handle
            if (event.type == Event::Closed)
                window.close();
        }

        //--------Update--------//
        ClearTetramino(curent.GetPositon(), curent.GetTetramino());

        if (counter >= tetaminoStop)
        {
            curent.SetPosition(Vector2i(0, 1));
            counter = 0;
        }
        
        
        DisplayTetramino(curent.GetPositon(), curent.GetTetramino());

        //--------Render--------//


        //clear window
        window.clear();

        //Draw cells
        for (int y = 0; y < boardSize.y; y++)
        {
            for (int x = 0; x < boardSize.x; x++)
            {
                if (board[y * boardSize.x + x] == 1) 
                {
                    RectangleShape cell(cellSize);
                    cell.setPosition(Vector2f(x * cellSize.x, y * cellSize.y));
                    cell.setFillColor(Color::Red);
                    cell.setOutlineColor(Color::Red);

                    window.draw(cell);
                }
            }
        }

    
        window.display();
    }

    return 0;
}
