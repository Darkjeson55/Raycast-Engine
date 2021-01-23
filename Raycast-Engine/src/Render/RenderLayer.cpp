#include "RenderLayer.h"

RenderLayer::RenderLayer(int width, int height, int scale) : m_buffer(width, height)
{
	m_width = width;
	m_height = height;
	m_scale = scale;

	m_texture.create(width, height);
	m_sprite.setScale(scale, scale);
	m_sprite.setTexture(m_texture);
}

void RenderLayer::Draw(sf::RenderWindow* window)
{
	Render();
	m_texture.update(m_buffer.GetPixelArray());
	window->draw(m_sprite);
	m_buffer.Clear(0);
}

RenderLayer::~RenderLayer()
{

}