#include "Game.h"



#include <SFML/Window/Event.hpp>


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);


using namespace sf;

Game::Game() : clear_color(0x6C7A89)
{

}


void Game::init()
{
	m_dispalay = new Display();
	m_window = new sf::RenderWindow(sf::VideoMode(RENDER_WIDTH * SCALE, RENDER_HEIGHT * SCALE), "3D render");
	ImGui::SFML::Init(*m_window);


	m_dispalay->init();

	//m_window->resetGLStates();



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
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
			
		}
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

		ImGui::SFML::Update(*m_window, TimePerFrame);


		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::End();



		m_window->clear(clear_color);
		render(m_window);
		ImGui::SFML::Render(*m_window);
		m_window->display();

	}
	ImGui::SFML::Shutdown();
	close();
}

void Game::close()
{
}





Game::~Game()
{
	delete(m_window);
	delete(m_dispalay);
}
