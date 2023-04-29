#include "Game.h";

void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 400;
	this->videoMode.width = 533;
	this->window = new sf::RenderWindow(this->videoMode, "Turtle Jump", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initPlatforms();
}

void Game::pollEvents()
{
	Event e;
	while (this->window->pollEvent(e))
	{
		if (e.type == Event::Closed)
			this->window->close();
		if (e.type == Event::KeyPressed)
		{
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
		}
	}
}

void Game::initTextures()
{
	Texture t1, t2, t3;
	t1.loadFromFile("scr/Images/background.png");
	t2.loadFromFile("scr/Images/platform.png");
	t3.loadFromFile("scr/Images/trutle character sing.png");
	MyTextures* t = new MyTextures(t1, t2, t3);
	mytex = t;

	std::cout << "texture inti";
}

const int PlatformAmount = 10;
void Game::initPlatforms() //init platforms and player
{
	// platform allocation
	point* myPoint = new point();
	point plat[10];

	std::cout << "player sprite inti";
	Actor* p = new Actor();
	PlayerActor = p;

	// start pos
	PlayerActor->px = 200; // int x = 100, y = 100, h = 200;
	PlayerActor->py = 200;

	PlayerActor->sprite.setTexture(mytex->t3);
	PlayerActor->sprite.setScale(.08f, 0.08f);

	for (int i = 0; i < 10; i++)
	{
		platforms[i] = new Actor();
	}

	// platform placement
	for (int i = 0; i < 10; i++)
	{
		platforms[i]->px = rand() % 400;
		platforms[i]->py = rand() % 533;
	}
}

Game::~Game()
{
	delete this->window;
}

//starting pos
void Game::update()
{

	this->pollEvents();

	// controlles
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		PlayerActor->px += 3;
		std::cout << PlayerActor->px << std::endl;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		PlayerActor->px -= 3;
		std::cout << PlayerActor->px << std::endl;
	}

	// gravity
	PlayerActor->accGrav += 0.2f;
	PlayerActor->py += PlayerActor->accGrav;

	// game over, make a gamerover logic, not like this... 
	if (PlayerActor->py > 500)  this->window->close();


	// scrolling
	const int h = 50; // scroll start height
	if (PlayerActor->py < h) // player near the screen scroll / moving the platforms
		for (int i = 0; i < PlatformAmount; i++)
		{
			PlayerActor->py = h;
			platforms[i]->py = platforms[i]->py - PlayerActor->accGrav;
			if (platforms[i]->py > 430) // platform is not visible(down screen), relocate
			{
				platforms[i]->py = 0; platforms[i]->px = rand() % 450;
			}
		}

	// platform collision, if between does coordinates jump boost
	for (int i = 0; i < PlatformAmount; i++)
		if ((PlayerActor->px + 50 > platforms[i]->px) && (PlayerActor->px + 20 < platforms[i]->px + 68)
			&& (PlayerActor->py + 70 > platforms[i]->py) && (PlayerActor->py + 70 < platforms[i]->py + 14) && (PlayerActor->accGrav > 0))  PlayerActor->accGrav = -10;

	// move
	PlayerActor->sprite.setPosition(PlayerActor->px, PlayerActor->py);
}

void Game::draw()
{
	this->window->clear();

	// get the textures
	Sprite tsBackground(mytex->t1);
	Sprite PlatformsSp(mytex->t2);
	Sprite PlayerSp(mytex->t3);
	PlayerSp.scale(0.1f, 0.1f);

	PlayerSp.setPosition(200, 200);

	this->window->draw(tsBackground);
	this->window->draw(PlatformsSp);
	this->window->draw(PlayerActor->sprite);

	// draw new the platforms
	for (int i = 0; i < 10; i++)
	{
		PlatformsSp.setPosition(platforms[i]->px, platforms[i]->py);
		this->window->draw(PlatformsSp);
	}

	this->window->display();
}

const bool Game::running() const
{
	return this->window->isOpen();
}
