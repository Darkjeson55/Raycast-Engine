#ifndef GAME_HEADER
#define GAME_HEADER

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

#include "Render/Display.h"
#include "math.h" 


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

	const sf::Color clear_color;
	static const sf::Time	TimePerFrame;
	sf::RenderWindow* m_window;

	Display* m_dispalay;

};

#endif