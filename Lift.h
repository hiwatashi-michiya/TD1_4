#pragma once
#include "Quad.h"
class Lift
{
public:
	int texture;
	Quad quad;
	int width;
	int height;
	unsigned int color;
	Vec2 worldPosition;
	Vec2 localPosition;
	float velocity;

	Lift();
	void Init();
	void Set(Vec2 Position, int Width, int Height);
	void Move();
	void Collision();
	void Update(float Scroll);
	void Draw();
};

