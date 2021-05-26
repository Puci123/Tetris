#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<thread>
#include<windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "Tetramino.h"


using namespace sf;

Vector2f cellSize(15, 15);
Tetramino tetraminos[7];

Tetramino NewTetramino() 
{
    Tetramino temp = tetraminos[rand() % 7];
    return temp;
}

void CreateTetraminos()
{
    int i[4] = { 4,5,6,7  };
    int j[4] = { 0,4,5,6  };
    int l[4] = { 5,6,7,3  };
    int o[4] = { 5,6,9,10 };
    int s[4] = { 5,6,2,3  };
    int t[4] = { 1,4,5,6  };
    int z[4] = { 0,1,5,6 };
    
    Vector2i baseKickiTable[5][4];
    Vector2i iKickiTable[5][4];
    Vector2i oKickTable[5][4];

    //-------------JLSTZ---------------//
    //1
    baseKickiTable[0][0] = Vector2i(0,0);
    baseKickiTable[0][1] = Vector2i(0,0);
    baseKickiTable[0][2] = Vector2i(0,0);
    baseKickiTable[0][3] = Vector2i(0,0);

    //2
    baseKickiTable[1][0] = Vector2i(-1, 0);
    baseKickiTable[1][1] = Vector2i(1, 0);
    baseKickiTable[1][2] = Vector2i(1, 0);
    baseKickiTable[1][3] = Vector2i(-1, 0);

    //3
    baseKickiTable[2][0] = Vector2i(-1, -1);
    baseKickiTable[2][1] = Vector2i(1, -1);
    baseKickiTable[2][2] = Vector2i(1, 1);
    baseKickiTable[2][3] = Vector2i(-1, -1);

    //4
    baseKickiTable[3][0] = Vector2i(0, -2);
    baseKickiTable[3][1] = Vector2i(0, 2);
    baseKickiTable[3][2] = Vector2i(0, -2);
    baseKickiTable[3][3] = Vector2i(0, 2);

    //5
    baseKickiTable[4][0] = Vector2i(-1, -2);
    baseKickiTable[4][1] = Vector2i(1, 2);
    baseKickiTable[4][2] = Vector2i(1, -2);
    baseKickiTable[4][3] = Vector2i(-1, 2);

    //-------------I---------------//
    
    //1
    iKickiTable[0][0] = Vector2i(0, 0);
    iKickiTable[0][1] = Vector2i(0, 0);
    iKickiTable[0][2] = Vector2i(0, 0);
    iKickiTable[0][3] = Vector2i(0, 0);

    //2
    iKickiTable[1][0] = Vector2i(-2, 0);
    iKickiTable[1][1] = Vector2i(-1, 0);
    iKickiTable[1][2] = Vector2i(2, 0);
    iKickiTable[1][3] = Vector2i(1, 0);

    //3
    iKickiTable[2][0] = Vector2i(1,  0);
    iKickiTable[2][1] = Vector2i(2,  0);
    iKickiTable[2][2] = Vector2i(-1, 0);
    iKickiTable[2][3] = Vector2i(-2, 0);

    //4
    iKickiTable[3][0] = Vector2i(-2, 1);
    iKickiTable[3][1] = Vector2i(-1, 2);
    iKickiTable[3][2] = Vector2i(2, 1);
    iKickiTable[3][3] = Vector2i(1,-2);

    //5
    iKickiTable[4][0] = Vector2i(1, 2);
    iKickiTable[4][1] = Vector2i(2, -1);
    iKickiTable[4][2] = Vector2i(-1, -2);
    iKickiTable[4][3] = Vector2i(-2, 1);

    //-------------O---------------//
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            oKickTable[i][j] = Vector2i(0,0);
        }
    }

    tetraminos[0] = Tetramino(i, Vector2i(5, 0), Vector2f(1.5f, 1.5f),iKickiTable);
    tetraminos[1] = Tetramino(j, Vector2i(4, 0), Vector2f(1, 1),baseKickiTable);
    tetraminos[2] = Tetramino(l, Vector2i(4, 0), Vector2f(2, 1), baseKickiTable);
    tetraminos[3] = Tetramino(o, Vector2i(5, 0), Vector2f(1.5f, 1.5f),oKickTable);
    tetraminos[4] = Tetramino(s, Vector2i(4, 0), Vector2f(2, 1), baseKickiTable);
    tetraminos[5] = Tetramino(t, Vector2i(4, 0), Vector2f(1, 1), baseKickiTable);
    tetraminos[6] = Tetramino(z, Vector2i(4, 0), Vector2f(1, 1), baseKickiTable);
}

void ChangeBoardValue(Vector2i pos, Vector2i* tetramino, int value, int* canvas,Vector2i cnavasSize)
{
    for (int i = 0; i < 4; i++)
    {

        int y = tetramino[i].y + pos.y;
        int x = tetramino[i].x + pos.x;

        canvas[y * cnavasSize.x + x] = value;
    }
}

void DropStack(int line, int* board,Vector2i boardSize) 
{
    for (int y = line; y > 1; y--)
    {
        for (int x = 1; x < boardSize.x - 1; x++)
        {
            board[y * boardSize.x + x] = board[(y - 1) * boardSize.x + x];
        }
    }
}

int CheckLines(int line, int* board,Vector2i boardSize)
{
    int completed = 0;

    for (int y = line; y < line + 5 && y < boardSize.y - 1; y++)
    {
        bool found = true;
        
        for (int x = 1; x < boardSize.x - 1; x++)
        {
            if (board[y * boardSize.x + x] == 0) 
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            completed++;
            DropStack(y,board,boardSize);   
        }
    }

    return completed;
}

bool ColisionDetecd(Vector2i pos, Vector2i* tetramino, int* board, Vector2i boardSize)
{
    
    for (int i = 0; i < 4; i++)
    {

        int y = tetramino[i].y + pos.y;
        int x = tetramino[i].x + pos.x;

        if (board[y * boardSize.x + x] != 0)
            return true;
    }

    return false;
}

void CreateBoard(int* canvas, Vector2i size) 
{
  
    //create paly board 0 empty, 1 tetramino , 2 wall
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {

            if (y == size.y - 1 || x == 0 || x == size.x - 1)
            {
                canvas[y * size.x + x] = 2;
            }
            else
            {
                canvas[y * size.x + x] = 0;
            }
        }
    }
}

void DrawBoard(RenderWindow &window, Vector2f offset, Vector2i size, int* toDraw) 
{
  

    //Draw cells 0 empty, 1 tetramino , 2 wall
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            if (toDraw[y * size.x + x] > 0)
            {

                RectangleShape cell(Vector2f(cellSize.x - 2, cellSize.y - 2));
                cell.setPosition(Vector2f(x * cellSize.x + offset.x, y * cellSize.y + offset.y));
                
                if (toDraw[y * size.x + x] == 1)
                {
                    cell.setFillColor(Color::Red);
                    cell.setOutlineColor(Color::Red);

                }
                else if (toDraw[y * size.x + x] == 2)
                {
                    cell.setSize(Vector2f(cellSize.x, cellSize.y));
                    cell.setFillColor(Color::Blue);
                    cell.setOutlineColor(Color::Blue);

                }

                window.draw(cell);

            }
        }
    }
}

void InputHnadle(RenderWindow &window, bool & preasdRoateButton)
{
    //Pool event
    Event event;
    while (window.pollEvent(event))
    {
        //Input handle
        if (event.type == Event::Closed)
            window.close();
        else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Up)
            preasdRoateButton = false;

    }
}

bool InputHnadle(RenderWindow &window) 
{
    //Pool event
    Event event;
    while (window.pollEvent(event))
    {
        //Input handle
        if (event.type == Event::Closed) 
        {
            window.close();
            return false;
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
        {
            return true;

        }    
    }

    return false;
}

void GameOver(Text &scoreText, Text  &lvlText,  RenderWindow &window, Font &font)
{
   
    window.clear();

    //Move text
    scoreText.setPosition(Vector2f(230, 150));
    scoreText.setCharacterSize(25);
    lvlText.setPosition((Vector2f(230, 180)));
    lvlText.setCharacterSize(25);

    //Game over text
    Text goText;
    goText.setFont(font);
    goText.setCharacterSize(50);
    goText.setFillColor(Color::White);
    goText.setPosition(Vector2f(140, 50));
    goText.setString("Game over !!!");
    
    //Inofo text
    Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(Color::White);
    infoText.setPosition(Vector2f(165, 250));
    infoText.setString("Pres enter to continue");

    window.draw(infoText);
    window.draw(goText);
    window.draw(lvlText);   
    window.draw(scoreText);
    window.display();

    while (true)
    {
        if (InputHnadle(window)) 
        {
            break;
        }
    }
}

void Game(RenderWindow &window, Font font, Text &scoreText,Text &lvlText)
{
    //------Game Start------//
    
    Vector2i nextCanvasSize(7, 7);
    Vector2f nextCanvasOffset(2, 2);

    Vector2i boardSize(12, 22);
    Vector2f boardOffset(40, 40);

    int* nextDisplay = new int[nextCanvasSize.x * nextCanvasSize.y];
    int* board = new int[boardSize.x * boardSize.y];

    for (int i = 0; i < nextCanvasSize.x * nextCanvasSize.y; i++)
    {
        nextDisplay[i] = 0;
    }

    CreateBoard(board,boardSize);
    //CreateBoard(nextDisplay, nextCanvasSize);

    //Score text
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(Vector2f(boardSize.x + boardOffset.x + 220, 20));
    scoreText.setString("Score 0");

    //lvl text
    lvlText.setCharacterSize(20);
    lvlText.setFillColor(Color::White);
    lvlText.setPosition(Vector2f(boardSize.x + boardOffset.x + 221, 40));
    lvlText.setString("level 1");

    //Next text
    Text pText;
    pText.setFont(font);
    pText.setCharacterSize(20);
    pText.setFillColor(Color::White);
    pText.setPosition(Vector2f(boardSize.x + boardOffset.x + 225, 80));
    pText.setString("Next");

    nextCanvasOffset = Vector2f(boardSize.x + boardOffset.x + 205,110);

    //--------Game varible--------//
    Tetramino curent = NewTetramino();
    Tetramino next = NewTetramino();

    bool isPlaying = true;

    //Input
    bool preasdRoateButton = false;

    //Timing
    int sleepTime = 35;
    int tetaminoStop = 20;
    int counter = 0;

    //Score
    int score = 0;
    int lines = 0;
    int lvl = 1;

    while (isPlaying)
    {
        Vector2i traslation(0, 0);
        bool roatate = false;

        //--------Timing--------//
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        counter += 1;

        //--------Input--------//

        InputHnadle(window, preasdRoateButton);



        //--------Move handle--------//
        
        ChangeBoardValue(curent.GetPositon(), curent.GetTetramino(),0,board,boardSize);

        //Horizontal
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            if (!ColisionDetecd(curent.GetPositon() + Vector2i(1, 0), curent.GetTetramino(),board,boardSize))
            {
                curent.SetPosition(Vector2i(1, 0));
            }

        }
        else if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if (!ColisionDetecd(curent.GetPositon() + Vector2i(-1, 0), curent.GetTetramino(),board,boardSize))
            {
                curent.SetPosition(Vector2i(-1, 0));
            }
        }

        //Vertical
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            counter = sleepTime;
        }

        //Roatation
        if (Keyboard::isKeyPressed(Keyboard::Up) && !preasdRoateButton)
        {
           
            int roatation = curent.GetRoatation() % 4;

            for (int i = 0; i < 5; i++)
            {
                 if (!ColisionDetecd(curent.GetPositon() + curent.GetFromKickTable(roatation,i), curent.GetTetramino(curent.GetRoatation() + 1),board,boardSize))
                 {
                    curent.SetRotation(1);
                    curent.SetPosition(curent.GetFromKickTable(roatation, i));
                    break;
                 }
            }
            
            
            

            preasdRoateButton = true;

        }


        //--------Update--------//

        if (counter >= tetaminoStop)
        {
            //Move down
            if (!ColisionDetecd(curent.GetPositon() + Vector2i(0, 1), curent.GetTetramino(),board,boardSize))
            {
                curent.SetPosition(Vector2i(0, 1));
            }
            else
            {
                ChangeBoardValue(curent.GetPositon(), curent.GetTetramino(),1,board,boardSize);

                //Is line complete
                int temp = CheckLines(curent.GetPositon().y,board,boardSize);
                if (temp > 0)
                {
                    score += temp * temp; // add score
                    lines += temp;        // count lines

                    //Level up
                    if (lines >= 5)
                    {
                        lvl++;
                        lvlText.setString("Level " + std::to_string(lvl));

                        tetaminoStop = (int)(tetaminoStop * 0.75f);
                        lines = 0;

                    }

                    //Display score
                    scoreText.setString("Score " + std::to_string(score));

                }
                //Create new teramino
                ChangeBoardValue(Vector2i(1, 1), next.GetTetramino(), 0, nextDisplay, nextCanvasSize);
                curent = next;
                next = NewTetramino();

                //Game over
                if (ColisionDetecd(curent.GetPositon(), curent.GetTetramino(),board,boardSize))
                {
                    isPlaying = false;
                }

            }
            counter = 0;
        }

        ChangeBoardValue(curent.GetPositon(), curent.GetTetramino(),1,board,boardSize);
        ChangeBoardValue(Vector2i(1,1), next.GetTetramino(), 1, nextDisplay, nextCanvasSize);

        //--------Render--------//
        //clear window
        window.clear();

        DrawBoard(window,boardOffset,boardSize,board);
        DrawBoard(window, nextCanvasOffset, nextCanvasSize, nextDisplay);

        //Show score
        window.draw(scoreText);
        window.draw(lvlText);
        window.draw(pText);

        window.display();
    }

    delete[] nextDisplay;
    delete[] board;
}

int main()
{

    //---------Awake---------//
    RenderWindow window(VideoMode(600, 600), "Tetris"); //Create window
    window.setFramerateLimit(60);
    
   
    //Load font
    Font font;

    if (!font.loadFromFile("arcadeFont.ttf"))
    {
        throw("ERRO, FONT LOAD");
        return -1;
    }

    //Score Text
    Text scoreText;
    scoreText.setFont(font);
  

    //Level Text
    Text lvlText;
    lvlText.setFont(font);
   
    //CreateSeed
    srand(unsigned(time(NULL)));
    CreateTetraminos();

    //--------Window loop--------//
    while (window.isOpen())
    {
        Game(window,font, scoreText, lvlText);
        GameOver(scoreText, lvlText, window, font);
    }
    return 0;
}
