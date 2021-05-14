#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Tetramino.h"


using namespace sf;

Vector2i boardSize(10, 10);
Vector2f cellSize(60, 60);
Tetramino tetraminos[7];



void CreateTetraminos()
{
    int i[4][4] = { 0,0,0,0,
                   0,0,0,0,
                   0,0,0,0,
                   0,0,0,0, };

    int j[4][4] = { 0,0,0,0,
                    0,0,0,0,
                    0,0,0,0,
                    0,0,0,0, };

    int l[4][4] = { 0,0,0,0,
                   0,0,0,0,
                   0,0,0,0,
                   0,0,0,0, };

    int o[4][4] = { 0,0,0,0,
                    0,0,0,0,
                    0,0,0,0,
                    0,0,0,0, };

    int s[4][4] = { 0,0,0,0,
                   0,0,0,0,
                   0,0,0,0,
                   0,0,0,0, };

    int t[4][4] = { 0,0,0,0,
                    0,0,0,0,
                    0,0,0,0,
                    0,0,0,0, };

    int z[4][4] = { 0,0,0,0,
                   0,0,0,0,
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

int main()
{

    //Awake
    RenderWindow window(VideoMode(600, 600), "Tetris"); //Create window
    int* board = new int[boardSize.x * boardSize.y];     //playBoard    0 empty, 1 filled

    for (int i = 0; i < boardSize.x * boardSize.y; i++) { board[i] = 0;}

    CreateTetraminos();

    //Game varible
    Vector2i curentPos(0, 0);

    //Game loop
    while (window.isOpen())
    {
        
        
        
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
