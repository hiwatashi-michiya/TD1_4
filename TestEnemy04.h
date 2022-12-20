#pragma once
#include "Vec2.h"
#include "Circle.h"
class TestEnemy04
{
private:
	Vec2 WorldPos;
	Vec2 LocalPos;
	float rad;

public:

	TestEnemy04();

	void Update();

	void Draw();

};

