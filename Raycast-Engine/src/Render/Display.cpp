#include "Display.h"

#include <iostream>
#include <math.h>

Display::Display() : render3D(RENDER_WIDTH, RENDER_HEIGHT, SCALE)
{

}

void Display::init()
{
	//frameBuffer = new sf::Uint8[RENDER_WIDTH * RENDER_HEIGHT * 4];
	//texture.create(RENDER_WIDTH, RENDER_HEIGHT);
	//sprite.setScale(SCALE, SCALE);
}

void Display::render(sf::RenderWindow* window)
{
	render3D.Draw(window);

	/*draw();

	texture.update(frameBuffer);
	sprite.setTexture(texture);
	window->draw(sprite);

	memset(frameBuffer, 0x00, RENDER_WIDTH * RENDER_HEIGHT * 4);*/
}

void Display::drawWorld()
{
	
}

float lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

void Display::draw()
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		playerPosition.y += movimentSpeed * cameraDirection.y;
		playerPosition.x += movimentSpeed * cameraDirection.x;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerPosition.x -= movimentSpeed * cameraDirection.x;
		playerPosition.y -= movimentSpeed * cameraDirection.y;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerPosition.x -= movimentSpeed * cameraDirection.x;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerPosition.x += movimentSpeed * cameraDirection.x;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		plane = Math::rotateVector(plane, 0.01f);

		cameraDirection = Math::rotateVector(cameraDirection, 0.01f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		plane = Math::rotateVector(plane, -0.01f);
		cameraDirection = Math::rotateVector(cameraDirection, -0.01f);
	}

	drawWorld();*/
}

void Display::drawLine(sf::Vector2f pointA, sf::Vector2f pointB, int color)
{

	bool swap = false;

	int DX = pointB.x - pointA.x;
	int DY = pointB.y - pointA.y;

	if (abs(DX) < abs(DY))
	{
		int temp = DX;

		DX = DY;
		DY = temp;

		swap = true;
	}


	int	a = abs(DY);
	int b = -abs(DX);

	int x = pointA.x;
	int y = pointA.y;

	int d = 2 * a + b;

	int q = 1;
	int s = 1;

	if (pointA.x > pointB.x) q = -1;
	if (pointA.y > pointB.y) s = -1;

	DrawPixel(x, y, color);
	DrawPixel(pointB.x, pointB.y, color);

	for (int k = 0; k < -b; k++)
	{
		if (d > 0)
		{
			x = x + q;
			y = y + s;
			d = d + 2 * (a + b);
		}
		else
		{
			x = x + q;
			if (swap)
			{
				y += s;
				x -= q;
			}

			d = d + 2 * a;
		}

		DrawPixel(x, y, color);
	}

}

void Display::DrawPixel(int x, int y, int color)
{
	if (x < 0 || x > RENDER_WIDTH || y < 0 || y > RENDER_HEIGHT)
	{
		return;
	}

	sf::Uint8* pix = &frameBuffer[(x + y * RENDER_WIDTH) * 4];

	pix[0] = color >> 16;
	pix[1] = (color & 0x00ff00) >> 8;
	pix[2] = (color & 0xff);
	pix[3] = 0xff;
}

Display::~Display()
{
	delete(frameBuffer);
}
