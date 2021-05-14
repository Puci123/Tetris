#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace sf;

Vector2i boardSize(10, 10);
Vector2f cellSize(60, 60);




int main()
{

    //Awake
    RenderWindow window(VideoMode(600, 600), "Tetris"); //Create window
    int* board = new int[boardSize.x * boardSize.y];     //playBoard    0 empty, 1 filled

    for (int i = 0; i < boardSize.x * boardSize.y; i++) { board[i] = 0;}

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
