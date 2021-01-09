#pragma once


#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdlib.h> 

#include "../math.h"

#define RENDER_WIDTH 240
#define RENDER_HEIGHT (RENDER_WIDTH * 3 / 4)
#define SCALE 2


#define PLAYER_HEIGHT 32
#define WALL_HEIGHT 64

#define PI 3.14159265

#define P2 = PI / 2
#define P3 = (3 * PI) / 2


class Display
{
public:
	Display();

	void init();

	void render(sf::RenderWindow* window);



	void drawWorld();

	void draw();

	void RaycastRender();

	int rndColor() {
		int color;

		int r = (rand() % 256) << 16;
		int g = (rand() % 256) << 8;
		int b = (rand() % 256);

		color = r | g | b;


		return color;
	}

	void drawPixel(int x, int y, int color);

	void drawLine(sf::Vector2f pointA, sf::Vector2f pointB, int color);


	~Display();


private:
	sf::Uint8* frameBuffer;
	sf::Texture texture;
	sf::Sprite sprite;

	float movimentSpeed = 0.01f;

	sf::Vector2f plane = sf::Vector2f(0,0.66f);
	sf::Vector2f playerPosition = sf::Vector2f(4,2);
	sf::Vector2f cameraDirection = sf::Vector2f(-1.0f,0.0f);

	sf::Texture tex;
	sf::Image img;
	int map[100] = {
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,0,0,0,0,0,0,1,
		1,0,1,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,1,0,1,
		1,0,1,0,0,1,0,1,0,1,
		1,1,1,0,0,1,1,1,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
	};

};

	