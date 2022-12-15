#include "TestEnemy3.h"
#include <Novice.h>

TestEnemy3::TestEnemy3()
{
	for (int i = 0; i < 10; i++) {

		bullet[i] = {
			false,
			{0,0},
			10,
			5
		};

	}
}

void TestEnemy3::Init(Vec2 pos)
{
	for (int i = 0; i < 10; i++) {

		bullet[i] = {
			false,
			pos,
			16,
			18
		};

	}
}

void TestEnemy3::update()
{
	for (int i = 0; i < 10; i++) {

		if (bullet[i].isAlive == true) {
			bullet[i].pos.y += bullet[i].speed;

			if (bullet[i].pos.y > 720) {
				bullet[i].isAlive = false;
				bullet[i].pos.y = 0;
			}
		}
	}

	if (time <= 0) {
		for (int i = 0; i < 10; i++) {
			if (bullet[i].isAlive == false) {
				time = TimeMax;
				bullet[i].isAlive = true;
				break;
			}
		}

	}
	else {
		time--;
	}
	
}

void TestEnemy3::Draw()
{
	for (int i = 0; i < 10; i++) {
		Novice::DrawEllipse(bullet[i].pos.x, bullet[i].pos.y, bullet[i].rad, bullet[i].rad,0,BLACK,kFillModeSolid);
	}
}
