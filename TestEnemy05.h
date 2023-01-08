#pragma once
#include "Vec2.h"
#include "Map.h"
#include "Player2.h"

enum E5MOVEDIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class TestEnemy05
{
public:
	TestEnemy05(Vec2 pos, Vec2 speed, E5MOVEDIRECTION direction);

	void Update(Map map, bool* redSwitch, bool* greenSwitch, bool* blueSwitch, bool* isHitredSwitch, bool* isHitgreenSwitch, bool* isHitblueSwitch);

	void Draw(float* scrollX);

private:

	Vec2 mPosition;
	Vec2 mSpeed;

	

	E5MOVEDIRECTION e5MoveDIrection;

};

