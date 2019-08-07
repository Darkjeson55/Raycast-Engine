#pragma once


#include <SFML/Graphics.hpp>

#include "../math.h"
#include "../../IMGUI/imgui.h"
#include "../../IMGUI/imgui-SFML.h"

#define RENDER_WIDHT 400
#define RENDER_HEIGHT (RENDER_WIDHT * 3 / 4)
#define SCALE 4


#define PLAYER_HEIGHT 32
#define WALL_HEIGHT 64




class Display
{
public:
	Display();

	void init();

	void render(sf::RenderWindow* window);

	void drawWorld();

	void drawWalls();


	~Display();


private:
	sf::Uint8* frameBuffer;
	sf::Texture texture;
	sf::Sprite sprite;

	float think;
	float think_two;

};

	