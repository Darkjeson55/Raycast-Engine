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

	dir = Math::rotateVector(directionVec, player_rotY);
	
	sf::Vector2f lateralVec = Math::rotateVector(dir, -90.0 * 3.1415 / 180.0);
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player_posZ += dir.y * movement_speed * dt.asMilliseconds();
		player_posX += dir.x * movement_speed * dt.asMilliseconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player_posZ -= dir.y * movement_speed * dt.asMilliseconds();
		player_posX -= dir.x * movement_speed * dt.asMilliseconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player_posZ += lateralVec.y * movement_speed * dt.asMilliseconds();
		player_posX += lateralVec.x * movement_speed * dt.asMilliseconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player_posZ -= lateralVec.y * movement_speed * dt.asMilliseconds();
		player_posX -= lateralVec.x * movement_speed * dt.asMilliseconds();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{

		player_rotY -= rot_speed * dt.asMilliseconds();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{

		player_rotY += rot_speed * dt.asMilliseconds();
	}


	Render3D::SetCameraPos(player_posX, player_posY, player_posZ);
	Render3D::SetCaneraRot(0, player_rotY);

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

		frames.push_back(1.0f / elapsedTime.asSeconds());

		if (frames.size() > 100)
		{
			int average = 0.0;
			for (int i = 0; i < frames.size(); i++)
			{
				average += frames.at(i);
			}

			currentFrame = average / frames.size();

			frames.clear();
		}

		ImGui::Begin("Debug");
		ImGui::Text("FPS: %f ", currentFrame);
		ImGui::Text("Direction: ");

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
