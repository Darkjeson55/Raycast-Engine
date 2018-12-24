#include "Game.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);


using namespace sf;

Game::Game() : m_WIDTH(800), m_HEIGHT(600) , clear_color(0x6C7A89)
{
}


void Game::init()
{

	m_dispalay = new Display();



	m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "3D render");
	mainLoop();
}

void Game::update(sf::Time dt)
{


}


void Game::poolEvent()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close();
	}
}




void Game::render(sf::RenderWindow* window)
{
	m_dispalay->render(window);
}



void Game::mainLoop()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window->isOpen())
	{

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			poolEvent();
			update(TimePerFrame);
		}

		m_window->clear(clear_color);
		render(m_window);
		m_window->display();
	}

	close();
}

void Game::close()
{
}





Game::~Game()
{
	delete(m_window);
}
