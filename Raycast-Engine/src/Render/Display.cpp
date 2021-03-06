#include "Display.h"

#include <iostream>
#include <cmath>

Display::Display()
{

}

void Display::init()
{
	texture.create(RENDER_WIDTH, RENDER_HEIGHT);
	frameBuffer = new sf::Uint8[RENDER_WIDTH * RENDER_HEIGHT * 4];
	sprite.setScale(SCALE, SCALE);

	tex.loadFromFile("image.png");
	img = sf::Image(tex.copyToImage());
}

void Display::render(sf::RenderWindow* window)
{
	//drawWorld();

	draw();

	//ImGui::Sliderdouble("think", &think, 0.0f, 64.0f);
	//ImGui::Sliderdouble("think2", &think_two, 0.0f, 64.0f);

	texture.update(frameBuffer);
	sprite.setTexture(texture);
	window->draw(sprite);

	memset(frameBuffer, 0x00, RENDER_WIDTH * RENDER_HEIGHT * 4);
}

void Display::drawWorld()
{

	for (int y = 0; y < RENDER_HEIGHT; y++)
	{
		double yDepth = (y - ((double)RENDER_HEIGHT / 2.0)) / RENDER_HEIGHT;


		double zd = 6.0 / yDepth;

		if (yDepth < 0)
		{
			zd = -6.0 / yDepth;
		}

		for (int x = 0; x < RENDER_WIDTH; x++)
		{
			double xDepth = (x - (RENDER_WIDTH / 2.0)) / RENDER_HEIGHT;

			xDepth *= zd;

			int finalColor = ((int)zd & 15) * 16 | ((int)xDepth & 15) * 16 << 8;

			drawPixel(x, y, finalColor);
		}
	}
}

float lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

void Display::draw()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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


	for (int x = 0; x < RENDER_WIDTH; x++)
	{
		for (int y = 0; y < RENDER_HEIGHT; y++)
		{
			if (y < RENDER_HEIGHT / 2.0f)
			{



				drawPixel(x, y,0x0098dc);
			}
			else
			{
				drawPixel(x, y, 0x5d5d5d);
			}
		}
	}


	//drawWorld();
	RaycastRender();
	//std::cout << a / b << std::endl;
}

void Display::RaycastRender()
{
	

	for (int x = 0; x < RENDER_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)RENDER_WIDTH - 1;
		double rayDirX = cameraDirection.x + plane.x * cameraX;
		double rayDirY = cameraDirection.y + plane.y * cameraX;

		int mapX = int(playerPosition.x);
		int mapY = int(playerPosition.y);

		double sideDistX;
		double sideDistY;

		double deltaDistX = std::abs(1 / rayDirX);
		double deltaDistY = std::abs(1 / rayDirY);

		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (playerPosition.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - playerPosition.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (playerPosition.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - playerPosition.y) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if (map[mapX + mapY * 10] > 0) hit = 1;
		}

		if (side == 0) perpWallDist = (mapX - playerPosition.x + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - playerPosition.y + (1 - stepY) / 2) / rayDirY;

		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = playerPosition.y + perpWallDist * rayDirY;
		else          wallX = playerPosition.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		float texWidth = tex.getSize().x;

		int texX = int(wallX * double(texWidth));
		if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;



		int h = RENDER_HEIGHT;

		int lineHeight = (int)(h / perpWallDist);

		double step = 1.0 * tex.getSize().y / lineHeight;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)drawEnd = h - 1;

		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (tex.getSize().y - 1);
			texPos += step;
			sf::Color color = img.getPixel(texX, texY);
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			//if (side == 1) color = (color >> 1) & 8355711;

			int col;

			col = (color.r << 16) | (color.g << 8) | (color.b);

			drawPixel(x, y, col);

			//buffer[y][x] = color;
		}

	}
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

	drawPixel(x, y, color);
	drawPixel(pointB.x, pointB.y, color);

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

		drawPixel(x, y, color);
	}

}

void Display::drawPixel(int x, int y, int color)
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
