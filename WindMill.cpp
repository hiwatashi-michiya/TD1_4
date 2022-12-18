#include "WindMill.h"
#include "Collision.h"
#include <Novice.h>

WindMill::WindMill()
{
	WorldPos = {9999,9999 };
	LocalPos = { 9999,9999 };
	Radius = 100;
	circle = { LocalPos,Radius};

	isExpHit = false;

	Charge = 0;
}

void WindMill::Set(Vec2 pos, float ScrollX)
{

	WorldPos = pos;
	LocalPos.x = WorldPos.x - ScrollX;
	LocalPos.y = WorldPos.y;
	
	circle = { LocalPos,Radius };
}

void WindMill::Update(float ScrollX)
{

	LocalPos.x = WorldPos.x - ScrollX;
	LocalPos.y = WorldPos.y;

	circle = { LocalPos,Radius };

	if (isExpHit == true) {
		if (Charge < MAXCHARGE) {
			Charge+= 3;
		}

		if (Charge > MAXCHARGE) {
			Charge = MAXCHARGE;
		}
	}
	else {
		if (Charge > 0) {
			Charge--;
		}

		if (Charge < 0) {
			Charge = 0;
		}
	}

}

void WindMill::Hit(Circle TargetCircle)
{
	if (Collision::CircleToCirlce(TargetCircle, circle)) {
		isExpHit = true;
	}
	else {
		isExpHit = false;
	}
}

void WindMill::Draw()
{
	int Color = GREEN;

	if (isExpHit == true) {
		Color = RED;
	}

	Novice::DrawEllipse(LocalPos.x, LocalPos.y, Radius, Radius, 0, Color, kFillModeSolid);

	Novice::DrawBox(LocalPos.x - 100, LocalPos.y - 120, 200, 10, 0, GREEN, kFillModeWireFrame);
	Novice::DrawBox(LocalPos.x - 100, LocalPos.y - 120, Charge / MAXCHARGE * 200, 10, 0, GREEN, kFillModeSolid);
	
}
