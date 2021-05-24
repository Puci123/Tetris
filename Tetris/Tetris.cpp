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

Vector2i boardSize(12, 22);
Vector2f boardOffset(40, 40);
Vector2f cellSize(15, 15);
Tetramino tetraminos[8];

int* board = nullptr;

Tetramino NewTetramino() 
{
    Tetramino temp = tetraminos[rand() % 7];
    //Tetramino temp = tetraminos[4];

    temp.SetPosition(Vector2i(1,1));

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
    int empty[4] = { -1,-1,-1,-1};


    tetraminos[0] = Tetramino(i, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[1] = Tetramino(j, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[2] = Tetramino(l, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[3] = Tetramino(o, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[4] = Tetramino(s, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[5] = Tetramino(t, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[6] = Tetramino(z, Vector2i(0, 0), Vector2f(1.5f, 1.5f));
    tetraminos[7] = Tetramino(empty, Vector2i(0, 0), Vector2f(1.5f, 1.5f));

}

void ChangeBoardValue(Vector2i pos, int* tetramino, int value) 
{
    for (int i = 0; i < 4; i++)
    {
        int x = (tetramino[i] % 4) + pos.x;
        int y = int(tetramino[i] / 4) + pos.y;

        board[y * boardSize.x + x] = value;
    }
}

void DropStack(int line) 
{
    for (int y = line; y > 1; y--)
    {
        for (int x = 1; x < boardSize.x - 1; x++)
        {
            board[y * boardSize.x + x] = board[(y - 1) * boardSize.x + x];
        }
    }

    std::cout << "Drop Down stack" << std::endl;
}

int CheckLines(int line)
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
            std::cout << "Complete line" << std::endl;
            completed++;
            DropStack(y);   
        }
    }

    return completed;
}

bool ColisionDetecd(Vector2i pos, int* tetramino) 
{
    for (int i = 0; i < 4; i++)
    {
        int x = (tetramino[i] % 4) + pos.x;
        int y = int(tetramino[i] / 4) + pos.y;

        if (board[y * boardSize.x + x] != 0)
            return true;
    }

    return false;
}

void CreateBoard() 
{
  
    board = new int[boardSize.x * boardSize.y];         //create paly board 0 empty, 1 tetramino , 2 wall


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
}

void DrawBoard(RenderWindow &window,Text &scoreText, Text &lvlText) 
{
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

    //Show score
    window.draw(scoreText);
    window.draw(lvlText);

    window.display();
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

bool InputHnadle(RenderWindow& window) 
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
    //std::cout << "Game over" << std::endl;

    window.clear();


    //Move text
    scoreText.setPosition(Vector2f(boardSize.x + boardOffset.x + 210, 150));
    scoreText.setCharacterSize(25);
    lvlText.setPosition((Vector2f(boardSize.x + boardOffset.x + 210, 180)));
    lvlText.setCharacterSize(25);

    //Game over text
    Text goText;
    goText.setFont(font);
    goText.setCharacterSize(50);
    goText.setFillColor(Color::White);
    goText.setPosition(Vector2f(boardSize.x + boardOffset.x + 110, 50));
    goText.setString("Game over !!!");
    
    //Inofo text
    Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(Color::White);
    infoText.setPosition(Vector2f(boardSize.x + boardOffset.x + 150, 250));
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
    CreateBoard();

    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(Vector2f(boardSize.x + boardOffset.x + 200, 20));
    scoreText.setString("Score 0");

    lvlText.setCharacterSize(20);
    lvlText.setFillColor(Color::White);
    lvlText.setPosition(Vector2f(boardSize.x + boardOffset.x + 201, 40));
    lvlText.setString("level 1");

    //--------Game varible--------//
    Tetramino curent = tetraminos[0];
    bool isPlaying = true;

    //Input
    bool preasdRoateButton = false;

    //Timing
    int sleepTime = 35;
    int tetaminoStop = 20;
    int counter = 0;

    //Debug
    curent.SetPosition(Vector2i(1, 1));

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

        ChangeBoardValue(curent.GetPositon(), curent.GetTetramino(),0);



        //Horizontal
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            if (!ColisionDetecd(curent.GetPositon() + Vector2i(1, 0), curent.GetTetramino()))
            {
                curent.SetPosition(Vector2i(1, 0));
            }

        }
        else if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if (!ColisionDetecd(curent.GetPositon() + Vector2i(-1, 0), curent.GetTetramino()))
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
            if (!ColisionDetecd(curent.GetPositon(), curent.GetTetramino(curent.GetRoatation() + 1)))
            {
                curent.SetRotation(1);
            }

            preasdRoateButton = true;

        }


        //--------Update--------//

        if (counter >= tetaminoStop)
        {
            //Move down
            if (!ColisionDetecd(curent.GetPositon() + Vector2i(0, 1), curent.GetTetramino()))
            {
                curent.SetPosition(Vector2i(0, 1));
            }
            else
            {
                ChangeBoardValue(curent.GetPositon(), curent.GetTetramino(),1);

                //Is line complete
                int temp = CheckLines(curent.GetPositon().y);
                if (temp > 0)
                {
                    score += temp * temp; // add score
                    lines += temp;        // count lines

                    std::cout << "Score: " << score << std::endl;
                    std::cout << "Lines: " << lines << std::endl;

                    //Level up
                    if (lines >= 5)
                    {
                        lvl++;
                        std::cout << "Curent level: " << lvl << std::endl;
                        lvlText.setString("Level " + std::to_string(lvl));

                        tetaminoStop = (int)(tetaminoStop * 0.75f);
                        std::cout << "Game speed: " << tetaminoStop << std::endl;
                        lines = 0;

                    }

                    //Display score
                    scoreText.setString("Score " + std::to_string(score));

                }
                //Create new teramino
                curent = NewTetramino();

                //Game over
                if (ColisionDetecd(curent.GetPositon(), curent.GetTetramino()))
                {
                    isPlaying = false;
                }

            }
            counter = 0;
        }

        ChangeBoardValue(curent.GetPositon(), curent.GetTetramino(),1);

        //--------Render--------//
        DrawBoard(window, scoreText, lvlText);


    }
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
