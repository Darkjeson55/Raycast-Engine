#pragma once

#include <SFML/Graphics.hpp>

class RenderBuffer
{

public:
	RenderBuffer(int width, int height);
	~RenderBuffer();

	sf::Uint8* GetPixel(int x, int y);
	void SetPixel(int x, int y, int color);

	sf::Uint8* GetPixelArray();

	void Clear(int color);
private:
	sf::Uint8* m_frameBuffer;

	int m_width, m_height;
};