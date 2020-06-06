#pragma once
#include "raylib.h"

struct Particle
{
	Vector2 position = {0.0f, 0.0f};
	Vector2 velocity = {0.0f, 0.0f};
	Color colour =  WHITE;
	float life = 0.0f; //seconds
	float scale  = 1.0f;
	float rotation  = 0.0f;
};