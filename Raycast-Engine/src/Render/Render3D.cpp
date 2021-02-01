#include "Render3D.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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

	depthBuffer = new float[width * height];
}

Render3D::~Render3D()
{

}

void Render3D::Render()
{
	OldRender();
	//SIMDRender();
}


void Render3D::SIMDRender()
{
	m_time++;
	//m_yPos = sin(m_time);
	//float halfHeight = m_height / 2.0f;
	//float halfWidth = m_width / 2.0f;

	__m256 halfHeight = _mm256_set1_ps(m_height / 2.0f);
	__m256 halfWidth = _mm256_set1_ps(m_width / 2.0f);
	__m256 mmHeight = _mm256_set1_ps(m_height);
	__m256 yPixelPos, ysub, yd;
	__m256 xPixelPos, xOffseted, xsub, xd, zx_d;
	__m256 CamX = _mm256_set1_ps(m_xPos);
	__m256 CamY = _mm256_set1_ps(m_yPos);
	__m256 CamZ = _mm256_set1_ps(m_zPos);
	__m256 zPixelPos, zadd, zd;
	__m256 _x_offset = _mm256_setr_ps(0,1,2,3,4,5,6,7);

	__m256 redShift = _mm256_set1_ps(pow(2, 24));
	__m256 greenshift = _mm256_set1_ps(pow(2, 16));
	__m256 blueShift = _mm256_set1_ps(pow(2, 8));

	__m256 bitwise = _mm256_set1_ps(15);
	__m256 alpha = _mm256_set1_ps(0xff);

	__m256 bitColorG, bitColorB;

	__m256 colorG;
	__m256 colorB;

	zPixelPos = _mm256_set1_ps(8);

	__m256 colors , colorsA;

	__m256i finalColor;

	for (int y = 0; y < m_height; y++)
	{
		//float yd = (y - halfHeight) / m_height;
		yPixelPos = _mm256_set1_ps(y);
		ysub = _mm256_sub_ps(yPixelPos, halfHeight);
		yd = _mm256_div_ps(ysub, mmHeight);
		
		//zd
		zadd = _mm256_add_ps(zPixelPos, CamY);
		zd = _mm256_div_ps(zadd, yd);

		for (int x = 0; x < m_width; x+=8)
		{
			xPixelPos = _mm256_set1_ps(x);
			xOffseted = _mm256_add_ps(xPixelPos, _x_offset);
			xsub = _mm256_sub_ps(xOffseted, halfWidth);
			xd = _mm256_div_ps(xsub, mmHeight);
			zx_d = _mm256_mul_ps(xd, zd); // xd *= z

			bitColorG = _mm256_and_ps(zx_d, bitwise);
			bitColorB = _mm256_and_ps(zd, bitwise);

			colorG = _mm256_mul_ps(bitColorG, greenshift);
			colorB = _mm256_mul_ps(bitColorB, blueShift);

			colors = _mm256_add_ps(colorG, colorB);
			colorsA = _mm256_add_ps(colors, alpha);

			finalColor = _mm256_castps_si256(colorsA);
			memcpy(GetBuffer().GetPixelArray() + (x + y * m_width) * 4, (int*)&finalColor, sizeof(int) * 8);

			//GetBuffer().SetPixel(x, y, 0xff00ff);
		}
	}
}


void Render3D::OldRender()
{
	m_time++;


	m_yRot = sin(m_time / 20) * 0.2;
	m_xPos = 0;//((int)m_time % 80) / 40.0;
	m_yPos = 0;//sin(m_time / 10.0) * 2;
	m_zPos = 0;//((int)m_time % 80) / 40.0;

	rtSin = sin(m_yRot);
	rtCos = cos(m_yRot);

	float halfHeight = m_height / 2.0f;
	float halfWidth = m_width / 2.0f;
	//float fov = 1 / tan((abs(sin(m_time)) * 1000));

	for (int y = 0; y < m_height; y++)
	{
		float yd = ((y + 0.5) - halfHeight) / m_height;
		float zd = ((4 + m_yPos) / (yd));

		if (yd < 0)
		{
			zd = ((4 - m_yPos) / (-yd));;
		}
		for (int x = 0; x < m_width; x++)
		{
			float xd = (x - halfWidth) / m_height;
			xd *= zd;

			float positionX = xd;
			float positionY = zd;

			float xx = (positionX * rtCos - positionY * rtSin + (m_xPos + 0.5) * 8);
			float yy = (positionX * rtSin + positionY * rtCos + (m_zPos) * 8);

			int xPix = (int)xx * 2;
			int yPix = (int)yy * 2;

			if (xx < 0)
				xPix--;
			if (yy < 0)
				yPix--;

			depthBuffer[x + y * m_width] = zd;


			sf::Color c = img.getPixel((int)(xPix) & 15, (int)(yPix) & 15);
			int r = c.r;
			int g = c.g;
			int b = c.b;

			int color = r << 16 | g << 8 | b;
			GetBuffer().SetPixel(x, y, color);

			c = img.getPixel(((int)(xPix) & 15) + 32, ((int)(yPix) & 15));

			int tex = c.r << 16 | c.g << 8 | c.b;



			//Render Floor
			/*if (yd > 0 && xPix >= 0 && xPix <= 16 && yPix >= 0 && yPix <= 16)
			{
				GetBuffer().SetPixel(x, y, tex);
			}*/

			//DrawFloor(xPix, yPix, yd, x, y);


			//Render Wall




			//end Wall
			RenderFog(x, y, zd);
		}
	}


	DrawWall(0,3,0.5,2.5);

}


void Render3D::RenderFog(int x, int y, int depth)
{
	sf::Uint8* pix = GetBuffer().GetPixel(x, y);

	double bright = (1000 / depth) * 5;

	if (bright < 0)
	{
		bright = 0;
	}

	if (bright > 255)
	{
		bright = 255;
	}

	pix[0] = Math::lerp(0x00, pix[0], bright / 255);
	pix[1] = Math::lerp(0x00, pix[1], bright / 255);
	pix[2] = Math::lerp(0x00, pix[2], bright / 255);

	int color = pix[0] << 16 | pix[1] << 8 | pix[2];

	GetBuffer().SetPixel(x, y, color);
}

void Render3D::DrawWall(float x0, float y0, float x1, float y1)
{

	float xp0 = x0 - 0.5 - m_xPos * 2;
	float u0 = - 0.5 + m_yPos / 4;
	float d0 = + 0.5 + m_yPos / 4;
	float zp0 = y0 - m_zPos * 2;

	float xx0 = xp0 * rtCos + zp0 * rtSin;
	float zz0 = -xp0 * rtSin + zp0 * rtCos;


	float xp1 = x1 - 0.5 - m_xPos * 2;
	float u1 = - 0.5 + m_yPos / 4;
	float d1 = + 0.5 + m_yPos / 4;
	float zp1 = y1 - m_zPos * 2;

	float xx1 = xp1 * rtCos + zp1 * rtSin;
	float zz1 = -xp1 * rtSin + zp1 * rtCos;


	float xPixel0 = xx0 / zz0 * m_height + m_width  / 2.0;
	float xPixel1 = xx1 / zz1 * m_height + m_width / 2.0;


	if (xPixel0 > xPixel1)
		return;
	int xo0 = (int)ceil(xPixel0);
	int xo1 = (int)ceil(xPixel1);

	if (xo0 < 0)
		xo0 = 0;

	if (xo1 > m_width)
		xo1 = m_width;


	float yPixel00 = u0 / zz0 * m_height + m_height / 2.0;
	float yPixel10 = u1 / zz1 * m_height + m_height / 2.0;

	float yPixel01 = d0 / zz0 * m_height + m_height / 2.0;
	float yPixel11 = d1 / zz1 * m_height + m_height / 2.0;

	for (int x = xo0; x < xo1; x++)
	{
		float yPixel0 = yPixel00 + (x - xPixel0) * (yPixel10 - yPixel00) / (xPixel1 - xPixel0);
		float yPixel1 = yPixel01 + (x - xPixel0) * (yPixel11 - yPixel01) / (xPixel1 - xPixel0);


		if (yPixel0 > yPixel1)
			return;
		int yo0 = (int)yPixel0;
		int yo1 = (int)yPixel1;

		if (xo0 < 0)
			xo0 = 0;

		if (xo1 > m_width)
			xo1 = m_width;


		for (int y = yo0; y <= yo1; y++)
		{

			GetBuffer().SetPixel(x, y, 0xff00ff);
		}
	}


	/*if (xPixel >= 0 && xPixel < m_width && yPixel >= 0 && yPixel < m_height)
	{
		GetBuffer().SetPixel(xPixel, yPixel, 0xff00ff);
	}*/
}


void Render3D::DrawFloor(float xPix, float yPix, float yd, int x, int y)
{
	sf::Color c = img.getPixel(((int)(xPix) & 15) + 32, ((int)(yPix) & 15));
	int tex = c.r << 16 | c.g << 8 | c.b;
	if (yd > 0 && xPix >= 0 && xPix <= 16 && yPix >= 0 && yPix <= 16)
	{
		GetBuffer().SetPixel(x, y, tex);
	}
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