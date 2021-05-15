#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<thread>
#include<windows.h>

#include "Tetramino.h"


using namespace sf;

Vector2i boardSize(12, 22);
Vector2f boardOffset(40, 40);
Vector2f cellSize(15, 15);
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

bool ColisionDetecd(Vector2i pos, int* tetramino) 
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (tetramino[y * 4 + x] * board[(pos.y + y) * boardSize.x + x + pos.x] > 0)
                return true;
        }

    }

    return false;
}

int main()
{

    //Awake
    RenderWindow window(VideoMode(600, 600), "Tetris"); //Create window
    window.setFramerateLimit(60);
    
    board = new int[boardSize.x * boardSize.y];         //create paly board 0 empty, 1 tetramino , 2 wall

    //fil board
    for (int y = 0; y < boardSize.y; y++)
    {
        for (int x = 0; x < boardSize.x; x++)
        {

            if (y == boardSize.y - 1 || x == 0 || x == boardSize.x - 1)
            {
                board[y * boardSize.x + x] = 2;
            }
            else
            {
                board[y * boardSize.x + x] = 0;
            }
        }
    }

   
    CreateTetraminos();

    //Game varible
    Tetramino curent = tetraminos[0];
    curent.SetPosition(Vector2i( 2, 0));

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
     
        Vector2i traslation(0, 0);
        bool roatate = false;

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

        ClearTetramino(curent.GetPositon(), curent.GetTetramino());


        //--------Move handle--------//
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            std::cout << "R" << std::endl;
            if (!ColisionDetecd(curent.GetPositon() + Vector2i(1,0), curent.GetTetramino()))
            {
                curent.SetPosition(Vector2i(1, 0));
            }
            
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            std::cout << "L" << std::endl;
            if (!ColisionDetecd(curent.GetPositon() + Vector2i(-1, 0), curent.GetTetramino()))
            {
                curent.SetPosition(Vector2i(-1, 0));
            }
        }
        
        

        //--------Update--------//

        if (counter >= tetaminoStop)
        {
            //Move down
            if (!ColisionDetecd(curent.GetPositon() + Vector2i(0,1),curent.GetTetramino()))
            {
                curent.SetPosition(Vector2i(0, 1));
            }
            
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
                    RectangleShape cell(Vector2f(cellSize.x - 2, cellSize.y - 2));
                    cell.setPosition(Vector2f(x * cellSize.x + boardOffset.x, y * cellSize.y + boardOffset.y));
                    cell.setFillColor(Color::Red);
                    cell.setOutlineColor(Color::Red);

                    window.draw(cell);
                }
                else if (board[y * boardSize.x + x] == 2)
                {
                    RectangleShape cell(Vector2f(cellSize.x, cellSize.y));
                    cell.setPosition(Vector2f(x * cellSize.x + boardOffset.x, y * cellSize.y + boardOffset.y));
                    cell.setFillColor(Color::Blue);
                    cell.setOutlineColor(Color::Blue);

                    window.draw(cell);
                }
               
            }
        }

    
        window.display();
    }

    return 0;
}
