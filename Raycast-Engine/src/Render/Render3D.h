#pragma once

#include "RenderLayer.h"
#include "math.h"
#include "../math.h"
#include <SFML/Graphics.hpp>

#include <immintrin.h>

class Render3D : public RenderLayer
{

public:
	Render3D(int width, int height, int scale);
	~Render3D();
	void Render();

	void SIMDRender();

	void OldRender();
	void ShaderRender();

	void RenderFog();

	void DrawFloor(float xPix, float yPix, float yd, int x, int y);

	void DrawWall(float x0, float y0, float x1, float y1);


	static void SetCameraPos(float x, float y, float z);
	static void SetCaneraRot(float xRot, float yRot);

private:
	float* depthBuffer;
	float* depthBufferWall;


	float m_time;
	int m_width, m_height, m_scale;

	//Camera
	static float m_xPos;
	static float m_yPos;
	static float m_zPos;

	static float m_yRot;
	static float m_xRot;


	float rtSin;
	float rtCos;

	sf::Texture tex;
	sf::Image img;
};