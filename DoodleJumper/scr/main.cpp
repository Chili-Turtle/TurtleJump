#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Game.h"
#include "windows.h"


using namespace sf;

int main()
{
    Game game;


    //srand(time(0));

    //RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    //app.setFramerateLimit(60);

    while (game.running())
    {
        game.draw();
        game.update();
    }

    return 0;
}
