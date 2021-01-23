#pragma once

#include "RenderLayer.h"
#include "math.h"
#include <SFML/Graphics.hpp>

class Render3D : public RenderLayer
{

public:
	Render3D(int width, int height, int scale);
	~Render3D();
	void Render();
	void DrawFloor();


	static void SetCameraPos(float x, float y, float z);
	static void SetCaneraRot(float xRot, float yRot);

private:
	float m_time;
	int m_width, m_height, m_scale;

	//Camera
	static float m_xPos;
	static float m_yPos;
	static float m_zPos;

	static float m_yRot;
	static float m_xRot;


	sf::Texture tex;
	sf::Image img;
};