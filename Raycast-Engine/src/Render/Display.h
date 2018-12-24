#pragma once


#include <SFML/Graphics.hpp>

#include "../math.h"


#define RENDER_WIDHT 160
#define RENDER_HEIGHT (RENDER_WIDHT * 3 / 4)
#define SCALE 4


#define PLAYER_HEIGHT 32
#define WALL_HEIGHT 64


struct Player
{
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::Vector2f Camera;

	float rotation;
};



class Display
{
public:
	Display();

	void render(sf::RenderWindow* window);


	~Display();


private:


	//Render Stuff
	sf::View Render;
	sf::RenderTexture buffer;


	Player m_player;
};

