#include "Render3D.h"


float Render3D::m_xPos = 0;
float Render3D::m_yPos = 0;
float Render3D::m_zPos = 0;

float Render3D::m_yRot = 0;
float Render3D::m_xRot = 0;

Render3D::Render3D(int width, int height, int scale) : RenderLayer(width, height, scale)
{
	m_width = width;
	m_height = height;
	m_scale = scale;


	tex.loadFromFile("floor-tileset.png");
	img = sf::Image(tex.copyToImage());
}

Render3D::~Render3D()
{

}

void Render3D::Render()
{
	m_time++;

	float fov = 1 / tan((abs(sin(m_time)) * 1000));

	for (int y = 0; y < m_height; y++)
	{
		float yd = (y - (m_height / 2.0)) / m_height;
		float zd = ((8 + m_yPos) / (yd));

		if (yd < 0)
		{
			zd = ((8 - m_yPos) / -yd);
		}

		for (int x = 0; x < m_width; x++)
		{
			float xd = (x - (m_width / 2.0)) / m_height;
			xd *= zd;

			

			float positionX = xd;
			float positionY = zd;


			int xPix = positionX * cos(m_yRot) - positionY * sin(m_yRot) + m_xPos;
			int yPix = positionX * sin(m_yRot) + positionY * cos(m_yRot) + m_zPos;


			sf::Color c = img.getPixel((int)(xPix) & 15, (int)(yPix) & 15);
			int r = c.r;
			int g = c.g;
			int b = c.b;

			double bright = 5000 / zd;

			if (bright < 0)
			{
				bright = 0;
			}

			if (bright > 255)
			{
				bright = 255;
			}

			r *= bright / 255;
			g *= bright / 255;
			b *= bright / 255;

			int color = r << 16 | g << 8 | b;
			GetBuffer().SetPixel(x, y, color);
		}
	}
}

void DrawFloor()
{

}


void Render3D::SetCameraPos(float x, float y, float z)
{
	m_xPos = x;
	m_yPos = y;
	m_zPos = z;
}


void Render3D::SetCaneraRot(float xRot, float yRot)
{
	m_xRot = xRot;
	m_yRot = yRot;
}