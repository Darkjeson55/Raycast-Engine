#pragma once

#include "RenderBuffer.h"

class RenderLayer
{
public:
	RenderLayer(int width, int height, int scale);
	~RenderLayer();

	virtual void Render() {}

	void Draw(sf::RenderWindow* window);

	RenderBuffer& GetBuffer() { return m_buffer; }

private:
	int m_width;
	int m_height;
	int m_scale;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	RenderBuffer m_buffer;
};