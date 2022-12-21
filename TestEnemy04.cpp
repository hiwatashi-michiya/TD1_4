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

	MAXHP = 100;
	HP = MAXHP;
	

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

	if (HP <= 0) {
		HP = 0;
		isAlive = false;
	}

	if (isAlive == true) {
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
}

void TestEnemy04::HitBomb(Circle BombCircle, Player2 player)
{
	if (isAlive == true) {
		if (Collision::CircleToCirlce(circle, BombCircle) && BombCircle.radius == 96 && isShield == false && player.GetIsBig() == false) {

			HP-= 30;

			float BombDistanceX = BombCircle.pos.x - WorldPos.x;
			float BombDistanceY = BombCircle.pos.y - WorldPos.y;

			float BombDistanceR = sqrtf(BombDistanceX * BombDistanceX + BombDistanceY * BombDistanceY);

			KnockBackVelocity.x = BombDistanceX / BombDistanceR * -16;
			KnockBackVelocity.y = BombDistanceY / BombDistanceR * -16;
		}

		if (Collision::CircleToCirlce(circle, BombCircle) && BombCircle.radius == 128 && isShield == false && player.GetIsBig() == true) {

			HP -= 50;

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
				HP -= 10;
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
	
		if (isShield == true) {
			Novice::DrawEllipse(LocalPos.x, LocalPos.y, rad + 10, rad + 10, 0, WHITE, kFillModeWireFrame);
			Novice::DrawEllipse(LocalPos.x, LocalPos.y, rad - 20, rad - 20, 0, WHITE, kFillModeSolid);
		}

		Novice::DrawBox(LocalPos.x - 50, LocalPos.y - rad - 20, 100, 10, 0, GREEN, kFillModeWireFrame);
		Novice::DrawBox(LocalPos.x - 50, LocalPos.y - rad - 20, HP / MAXHP * 100, 10, 0, GREEN, kFillModeSolid);
	}
}
