#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics\Color.hpp>
#include <random>
#include <iostream>
#include <math.h>
#include <iomanip>

#include "src\Game.h"



const int WIDTH = 320;
const int HEIGHT = 240;

sf::Uint8* pixels = new sf::Uint8[WIDTH*HEIGHT * 4];

sf::Texture tex;

sf::Image img;

sf::Texture texture;
sf::Sprite sprite(texture); // needed to draw the texture on screen

void init()
{
	texture.create(WIDTH, HEIGHT);
	tex.loadFromFile("image.png");
								// ...
	img = tex.copyToImage();

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, WIDTH, HEIGHT));
	sprite.setColor(sf::Color(255, 255, 255, 255));
	sprite.setScale(1, 1);
	sprite.setPosition(0, 0);

}

int t;

double xCam = 0;
double yCam = 0;
double zCam = 4;

double rot;
double rotY;

void draw()
{

	t++;

	xCam = 0;
	yCam = 0;
	zCam = 0;

	rot = std::sin(t / 60.0) / 2;;
	rotY = std::sin(t / 60.0) / 2;



	for (int y = 0; y < HEIGHT; y++)
	{
		double yDepth = (y - ((float)HEIGHT / 2.0)) / HEIGHT;

		double zd = (8.0 + zCam) / yDepth;

		if (yDepth < 0.0)
			zd = (8.0 - zCam) / -yDepth;

		for (int x = 0; x < WIDTH; x++)
		{
			double xDepth = (x - (WIDTH / 2.0)) / HEIGHT;

			xDepth *= zd;

			int xPix = (int)(xDepth * std::cos(rot) - zd * std::sin(rot)) + xCam;
			int yPix = (int)(xDepth * std::sin(rot) + zd * std::cos(rot)) + yCam;

			sf::Uint8 *Color = pixels + (x + y * WIDTH) * 4;

			// << 8 equivale a moltiplicare per 256

			int final_color = ((yPix & 15) * 16) << 8 | ((xPix & 15) * 16) << 8;


			Color[0] = final_color >> 16;
			Color[1] = (final_color & 0x0ff00) >> 8;
			Color[2] = final_color & 0xff;
			Color[3] = 255;

			if (zd > 200)
			{

				Color[0] = (final_color >> 16) / zd;
				Color[1] = ((final_color & 0x0ff00) >> 8) / zd;
				Color[2] = (final_color & 0xff) / zd;
				Color[3] = 255;
			}



		
			/*const sf::Uint8 *final_color = img.getPixelsPtr() + ((xPix & 255) + (yPix & 255) * 256) * 4;


			Color[0] = final_color[0];
			Color[1] = final_color[1];
			Color[2] = final_color[2];
			Color[3] = 255;*/
			
		}

	}

	texture.update(pixels);

	
}



int main()
{

	Game game;
	game.init();


	return 0;
}