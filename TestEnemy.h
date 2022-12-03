#pragma once
#include "Vec2.h"
#include "Map.h"
#include "Player.h"
class TestEnemy
{
public:
	TestEnemy();
	void Init();
	void Update(Player player,Map map, float slow);
	void Draw();

	Vec2 position;
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;

	bool isAlive;
	bool fallFlag;

	int texture;

	Vec2 vector;
	Vec2 velocity;
	float speed;
};

