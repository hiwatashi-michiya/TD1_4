#pragma once
#include "Vec2.h" 
class TestEnemy3
{
private:
	struct BulletStruct {
		bool isAlive;
		Vec2 pos;
		int rad;
		float speed;
	};

	int TimeMax = 40;
	int time = TimeMax;

	BulletStruct bullet[10];
public:
	
	TestEnemy3();

	void Init(Vec2 pos);

	void update();

	void Draw();
};

