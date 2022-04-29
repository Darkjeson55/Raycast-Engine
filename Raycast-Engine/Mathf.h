#pragma once
#include <math.h>

struct vec2 {
	float x, y;
};

struct vec3 {
	float x, y, z;
};

inline vec2 Rotate2DVector(const vec2& in, const float& rot)
{
	float x = in.x * cos(rot) - sin(rot) * in.y;
	float y = in.x * sin(rot) + cos(rot) * in.y;

	return vec2{x,y};
}

inline float Vector2DLenght(const vec2& in)
{
	return sqrt(pow(in.x, 2) + pow(in.y, 2));
}

inline vec2 Normalize2DVector(const vec2& in) {
	float lenght = Vector2DLenght(in);
	return vec2{ in.x / lenght , in.y / lenght };
}
