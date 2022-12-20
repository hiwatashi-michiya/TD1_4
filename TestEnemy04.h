#pragma once
#include "Vec2.h"
#include "Quad.h"
#include "Circle.h"
class TestEnemy04
{
private:
	Vec2 WorldPos;
	Vec2 LocalPos;
	float rad;
	Circle circle;

	Vec2 MoveVector;
	Vec2 KnockBackVelocity;

	unsigned int color;

	bool isAlive;
	bool isShield;
	
	int Speed;

public:

	TestEnemy04();

	void Set(Vec2 Pos,float scrollX);

	void Update(float scrollX, Vec2 PlayerPos);

	void HitBomb(Circle BombCircle);

	void HitPlayer(Quad PlayerQuad,Vec2 playerKnockbackVelocity);

	Circle GetCircle() { return circle;};

	void Delete();

	void Draw();

};

