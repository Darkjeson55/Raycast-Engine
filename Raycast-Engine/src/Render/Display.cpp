#include "Display.h"
#include <iostream>


Display::Display()
{

}

void Display::init()
{
	texture.create(RENDER_WIDHT, RENDER_HEIGHT);
	frameBuffer = new sf::Uint8[RENDER_WIDHT * RENDER_HEIGHT * 4];
	sprite.setScale(2, 2);
}



void Display::render(sf::RenderWindow* window)
{
	drawWorld();

	ImGui::SliderFloat("think", &think, 0.0f, 64.0f);
	ImGui::SliderFloat("think2", &think_two, 0.0f, 64.0f);

	texture.update(frameBuffer);
	sprite.setTexture(texture);
	window->draw(sprite);

}


void Display::drawWorld()
{




	for (int y = 0; y < RENDER_HEIGHT; y++)
	{
		double yDepth = (y - ((float)RENDER_HEIGHT / 2.0)) / RENDER_HEIGHT;




		double zd = 8.0 / yDepth;

		if (yDepth < 0)
		{
			zd = 0;
		}

		for (int x = 0; x < RENDER_WIDHT; x++)
		{

			double xDepth = (x - (RENDER_WIDHT / 2.0)) / RENDER_HEIGHT;


			xDepth *= zd;


			int a = think;
			int b = think_two;



			int finalColor = (y % 15) * 16 | (x % 15) * 16 << 8;

			frameBuffer[(x + y * RENDER_WIDHT) * 4] = finalColor >> 16;
			frameBuffer[(x + y * RENDER_WIDHT) * 4 + 1] = (finalColor & 0x00ff00) >> 8;
			frameBuffer[(x + y * RENDER_WIDHT) * 4 + 2] = (finalColor & 0xff);
			frameBuffer[(x + y * RENDER_WIDHT) * 4  + 3] = 0xff;
		}
	}
}

Display::~Display()
{
}
