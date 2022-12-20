#include "TestEnemy04.h"
#include "Collision.h"
#include <Novice.h>
#include <Math.h>

TestEnemy04::TestEnemy04()
{
	WorldPos = { 9999,9999 };
	LocalPos = { 9999,9999 };
	rad = 64;

	isAlive = false;
	isShield = true;

	Speed = 3;

	MoveVector = { 0,0 };
	KnockBackVelocity = { 0,0 };

	circle = { WorldPos , rad };

	color = 0xFF0000FF;

}

void TestEnemy04::Set(Vec2 Pos, float scrollX)
{
	WorldPos = Pos;

	LocalPos.x = WorldPos.x - scrollX;
	LocalPos.y = WorldPos.y;

	circle = { WorldPos , rad };

	isAlive = true;
	isShield = true;
}

void TestEnemy04::Update(float scrollX,Vec2 PlayerPos)
{

	float MinusSpeed = 1;

	if (KnockBackVelocity.x > 0) {
		KnockBackVelocity.x -= MinusSpeed;
	}
	else if (KnockBackVelocity.x < 0) {
		KnockBackVelocity.x += MinusSpeed;
	}
	if (KnockBackVelocity.x < MinusSpeed && KnockBackVelocity.x > -MinusSpeed) {
		KnockBackVelocity.x = 0;
	}

	if (KnockBackVelocity.y > 0) {
		KnockBackVelocity.y -= MinusSpeed;
	}
	else if (KnockBackVelocity.y < 0) {
		KnockBackVelocity.y += MinusSpeed;
	}
	if (KnockBackVelocity.y < MinusSpeed && KnockBackVelocity.y > -MinusSpeed) {
		KnockBackVelocity.y = 0;
	}

	

	float PlayerDistanceX = PlayerPos.x - WorldPos.x;
	float PlayerDistanceY = PlayerPos.y - WorldPos.y;

	float PlayerDistanceR = sqrtf(PlayerDistanceX * PlayerDistanceX + PlayerDistanceY * PlayerDistanceY);

	MoveVector.x = PlayerDistanceX / PlayerDistanceR * Speed;
	MoveVector.y = PlayerDistanceY / PlayerDistanceR * Speed;

	WorldPos += MoveVector + KnockBackVelocity;

	LocalPos.x = WorldPos.x - scrollX;
	LocalPos.y = WorldPos.y;

	circle = { WorldPos , rad };

}

void TestEnemy04::HitBomb(Circle BombCircle)
{
	if (isAlive == true) {
		if (Collision::CircleToCirlce(circle, BombCircle) && BombCircle.radius == 96 && isShield == false) {

			float BombDistanceX = BombCircle.pos.x - WorldPos.x;
			float BombDistanceY = BombCircle.pos.y - WorldPos.y;

			float BombDistanceR = sqrtf(BombDistanceX * BombDistanceX + BombDistanceY * BombDistanceY);

			KnockBackVelocity.x = BombDistanceX / BombDistanceR * -16;
			KnockBackVelocity.y = BombDistanceY / BombDistanceR * -16;
		}
	}
}


void TestEnemy04::HitPlayer(Quad PlayerQuad, Vec2 playerKnockbackVelocity)
{
	if (isAlive == true) {
		if (playerKnockbackVelocity.x != 0 || playerKnockbackVelocity.y != 0) {
			if (Collision::CircleToQuad(circle, PlayerQuad)) {

				isShield = false;

				KnockBackVelocity.x = playerKnockbackVelocity.x * 2;
				KnockBackVelocity.y = playerKnockbackVelocity.y * 2;
			}
		}
	}
}

void TestEnemy04::Delete()
{

	WorldPos = { 9999,9999 };
	LocalPos = { 9999,9999 };
	rad = 64;

	isAlive = false;

	Speed = 3;

}

void TestEnemy04::Draw()
{


	if (isAlive == true) {
		Novice::DrawEllipse(LocalPos.x, LocalPos.y, rad, rad, 0, color, kFillModeSolid);
	}
}
