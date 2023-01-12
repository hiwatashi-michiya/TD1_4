#pragma once
#include "Quad.h"
#include "Player2.h"
class Lift
{
public:
	int texture;
	Quad quad;
	Quad localQuad;
	int width;
	int height;
	unsigned int color;
	Vec2 worldPosition;
	Vec2 localPosition;
	float velocity;

	Lift();
	void Init();
	void Set(Vec2 Position, int Width, int Height);
	void Move(Player2& player);
	void Collision(Player2& player);
	void Update(Player2& player);
	void Draw(float* scrollX);
};

