#pragma once
#include "Vec2.h"
#include "Player2.h"

class Line
{
public:
	Vec2 mPosition;
	float mSpeed;
	int mCount;
	int mCountMax;

	int stop;

	Line();

	void Init();
	void Update(Player2& player);
	void Move();
	void Collision(Player2& player);
	void Draw(float* scrollX);
};