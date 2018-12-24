#pragma once

#include <SFML/Graphics.hpp>

#define PI 3.14159

struct Math
{
	static const float pi;


	static sf::Vector2f rotateVector(sf::Vector2f vec, float angle)
	{
		sf::Vector2f newVec;

		newVec.x = vec.x * cos(angle) - vec.y * sin(angle);
		newVec.y = vec.x * sin(angle) + vec.y * cos(angle);
		
		return newVec;
	}



	static float degreeToRadians(float degree)
	{
		return degree * (180 / PI);
	}

};

