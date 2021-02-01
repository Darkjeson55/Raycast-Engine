#pragma once

#include <SFML/Graphics.hpp>

#define PI 3.14159

struct Math
{

	static sf::Vector2f rotateVector(sf::Vector2f vec, float angle)
	{
		sf::Vector2f newVec;

		newVec.x = vec.x * cos(angle) - vec.y * sin(angle);
		newVec.y = vec.x * sin(angle) + vec.y * cos(angle);
		
		return newVec;
	}

	static float vectorLenght(sf::Vector2f vec)
	{
		return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	}

	static float RandomFloat(float a)
	{
		return (float(rand()) / float(RAND_MAX) * a);
	}

	static sf::Vector2f normalize(sf::Vector2f vec)
	{
		float lenght = vectorLenght(vec);
		return sf::Vector2f(vec.x / lenght, vec.y / lenght);
	}

	static float degreeToRadians(float degree)
	{
		return degree * (PI / 180);
	}

	static float lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}
};

