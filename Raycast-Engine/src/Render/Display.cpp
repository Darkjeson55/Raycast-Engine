#include "Display.h"
#include <iostream>


Display::Display()
{
	m_player.position.x = 22;
	m_player.position.y = 12;


	m_player.direction.x = -1;
	m_player.direction.y = 0;

	buffer.create(RENDER_WIDHT, RENDER_HEIGHT);
	m_player.Camera.x = 0;
	m_player.Camera.y = 0.66;
	buffer.clear(sf::Color::Black);
}




void Display::render(sf::RenderWindow* window)
{

	sf::Sprite bufferSprite(buffer.getTexture());




	int map[24][24] =
	{
	  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	sf::View view(sf::Vector2f(RENDER_WIDHT / 2.0f, RENDER_HEIGHT / 2.0f), sf::Vector2f((float)RENDER_WIDHT, (float)RENDER_HEIGHT));

	window->setView(view);


	sf::VertexArray lines(sf::Lines, ((RENDER_WIDHT) * 2));
	int LineRenderIndex = 0;

	for (uint32_t x = 1; x <= RENDER_WIDHT; x++)
	{

		double cameraX = 2 * x / double(RENDER_WIDHT) - 1; 
		double rayDirX = m_player.direction.x + m_player.Camera.x * cameraX;
		double rayDirY = m_player.direction.y + m_player.Camera.y * cameraX;
		int mapX = int(m_player.position.x);
		int mapY = int(m_player.position.y);

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
			sideDistX = (m_player.position.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - m_player.position.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (m_player.position.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - m_player.position.y) * deltaDistY;
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
			if (map[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0) perpWallDist = (mapX - m_player.position.x + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - m_player.position.y + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(RENDER_HEIGHT / perpWallDist);


		int drawStart = -lineHeight / 2 + RENDER_HEIGHT / 2;
		if (drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + RENDER_HEIGHT / 2;
		if (drawEnd >= RENDER_HEIGHT)drawEnd = RENDER_HEIGHT - 1;

		sf::Color color = sf::Color::Red;
		switch (map[mapX][mapY])
		{
		case 1:  color = sf::Color::Red; break; 
		case 2:  color = sf::Color::Green; break; //green
		case 3:  color = sf::Color::Blue; break; //blue
		case 4:  color = sf::Color::White; break; //white
		default: color = sf::Color::Yellow; break; //yellow
		}

		if (side == 1) { color = sf::Color(color.r / 2, color.g / 2, color.b / 2, 255); }

		lines[LineRenderIndex].position = sf::Vector2f(x, drawStart);
		lines[LineRenderIndex + 1].position = sf::Vector2f(x, drawEnd);

		lines[LineRenderIndex].color = color;
		lines[LineRenderIndex + 1].color = color;
		LineRenderIndex += 2;
	}

	float moveSpeed = 0.01f;
	float rotSpeed = 0.01f;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (map[int(m_player.position.x + m_player.direction.x * moveSpeed)][int(m_player.position.y)] == false)  m_player.position.x += m_player.direction.x * moveSpeed;
		if (map[int(m_player.position.x)][int(m_player.position.y + m_player.direction.y * moveSpeed)] == false)  m_player.position.y += m_player.direction.y * moveSpeed;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (map[int(m_player.position.x - m_player.direction.x * moveSpeed)][int(m_player.position.y)] == false)  m_player.position.x -= m_player.direction.x * moveSpeed;
		if (map[int(m_player.position.x)][int(m_player.position.y - m_player.direction.y * moveSpeed)] == false)  m_player.position.y -= m_player.direction.y * moveSpeed;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		
		m_player.direction = Math::rotateVector(m_player.direction, rotSpeed);
		m_player.Camera = Math::rotateVector(m_player.Camera, rotSpeed);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		
		m_player.direction = Math::rotateVector(m_player.direction, -rotSpeed);
		m_player.Camera = Math::rotateVector(m_player.Camera, -rotSpeed);
	}
	buffer.clear(sf::Color::Black);

	buffer.draw(lines);
	buffer.display();


	window->draw(bufferSprite);
}

Display::~Display()
{
}
