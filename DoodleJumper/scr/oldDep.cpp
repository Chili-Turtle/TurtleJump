#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

struct point
{
    int x, y;
};

const int PlatformAmount = 10;

int mainer()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("scr/Images/background.png");
    t2.loadFromFile("scr/Images/platform.png");
    t3.loadFromFile("scr/Images/trutle character sing.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    // scale playser
    sPers.setScale(.07f, .07f);



    // platform allocation
    point plat[PlatformAmount];


    // platform placement
    for (int i = 0; i < PlatformAmount; i++)
    {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 533;
    }


    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        // controlles
        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;

        // gravity
        dy += 0.2;
        y += dy;

        // game over, make a gamerover logic, not like this... 
        if (y > 500)  app.close();


        // scrolling
        if (y < h)
            for (int i = 0; i < PlatformAmount; i++)
            {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533)
                {
                    plat[i].y = 0; plat[i].x = rand() % 400;
                }
            }

        // platform collision, if between does coordinates jump boost
        for (int i = 0; i < PlatformAmount; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;

        // move
        sPers.setPosition(x, y);

        app.draw(sBackground);
        app.draw(sPers);

        // draw the platforms
        for (int i = 0; i < PlatformAmount; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);
            app.draw(sPlat);
        }

        app.display();
    }

    return 0;
}
