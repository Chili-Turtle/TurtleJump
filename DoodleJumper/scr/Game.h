#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

struct point
{
	int x, y;
};

class MyTextures
{
public:

	Texture t1, t2, t3;

	Sprite Background;
	Sprite PlayerS;
	Sprite PlatformS;

	MyTextures(Texture bg, Texture playerS, Texture platformS)
	{
		t1 = bg;
		t2 = playerS;
		t3 = platformS;

		PlayerS.setTexture(t1);
		std::cout << "myTextrues init";
	}

	~MyTextures()
	{
		std::cout << "destroyed";
	}
};

struct Actor
{
public:
	int px, py;
	float accGrav;
	Sprite sprite;
};

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	
	void initVariables();
	void initWindow();
	void initPlatforms();
public:
	MyTextures* mytex;
	Actor* platforms[10];
	point plat[10];
	Actor* PlayerActor;

	// constructor / deconstructor
	Game();
	virtual ~Game();

	// accesors
	const bool running() const;

	// functions
	void initTextures();
	void pollEvents();
	void update();
	void draw();
};