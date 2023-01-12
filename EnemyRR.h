#pragma once
#include "Vec2.h"
#include "Quad.h"
#include "Circle.h"
#include "EnemyRRBullet.h"

class EnemyRR
{
public:
	EnemyRR();

	Vec2 localPos;
	Vec2 worldPos;
	Quad localQuad;
	Quad worldQuad;
	Circle search;

	EnemyRRBullet bullet;

	int radius;
	int width;
	int height;
	int texture;
	int color;


	void Init();
	void Set(Vec2 pos, int width, int height, float searchRadius);
	void Update(Player2& player, float* scrollX);
	void Collision();
	void Move(Player2& player,float* scrollX);
	void Draw(float* scrollX);
};

