#pragma once
#include "Vec2.h"
#include "Quad.h"
#include "Player2.h"
class Coin
{
public:
	Vec2 pos;
	Quad quad;
	float width;
	float height;
	bool isAlive;

	Coin();
	void Init();
	void Set(Vec2 pos);
	void Update(Player2& player,float* scroll);
	void Collision(Player2& player, float* scroll);
	void Draw(float* scroll);

};

