#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(int width, int height)
{
	m_width = width;
	m_height = height;

	m_frameBuffer = new sf::Uint8[(int)(width * height * 4)];
}

sf::Uint8* RenderBuffer::GetPixel(int x, int y)
{
	return &m_frameBuffer[(x + y * m_width) * 4];
}

void RenderBuffer::SetPixel(int x, int y, int color)
{
	if (x < 0 || x > m_width || y < 0 || y > m_height)
	{
		return;
	}

	sf::Uint8* pix = &m_frameBuffer[(x + y * m_width) * 4];

	pix[0] = color >> 16;
	pix[1] = (color & 0x00ff00) >> 8;
	pix[2] = (color & 0xff);
	pix[3] = 0xff;
}

sf::Uint8* RenderBuffer::GetPixelArray()
{
	return m_frameBuffer;
}

void RenderBuffer::Clear(int color)
{
	memset(m_frameBuffer, 255 << 24 | 255 << 16 | 255 << 8 | 255, (int)(m_width * m_height * 4));
}

RenderBuffer::~RenderBuffer()
{
	delete(m_frameBuffer);
}