#ifndef GAME_HEADER
#define GAME_HEADER

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

#include "Render/Display.h"
#include "Render/Render3D.h"
#include "math.h" 


#include <imgui.h>
#include <imgui-SFML.h>

class Game
{
public:
	Game();
	
	void init();

	void update(sf::Time dt);

	void poolEvent();

	void render(sf::RenderWindow* window);

	void mainLoop();

	void close();

	~Game();

private:

	float player_posX;
	float player_posY;
	float player_posZ;

	float rot_speed = 0.005f;
	float movement_speed = 0.12f;


	sf::Vector2f directionVec = sf::Vector2f(0.0f, 1.0f);
	sf::Vector2f dir;


	float player_rotY;


	const sf::Color clear_color;
	static const sf::Time	TimePerFrame;
	sf::RenderWindow* m_window;

	Display* m_dispalay;

};

#endif