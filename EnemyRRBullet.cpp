#include "EnemyRRBullet.h"
#include "Matrix33 .h"
#include "Collision.h"
#include <Novice.h>


EnemyRRBullet::EnemyRRBullet()
{
	Init();
}

void EnemyRRBullet::Init()
{
	mLocalCircle = { {0,0},mRadius };
	mWorldCircle = { {0,0},mRadius };
	mRadius = 10;
	mColor = WHITE;
	mSpeed = 20;
	mIsAlive = false;
}

void EnemyRRBullet::Set(Vec2 pos,Player2& player)
{
	if (!mIsAlive) {
		mWorldCircle = { {pos},mRadius };
		mVector = player.GetPlayerPos() - pos;
		mVector = mVector.Normalized();
		mIsAlive = true;
	}
}


void EnemyRRBullet::Update(Player2& player, Vec2 pos, float* scrollX)
{
	Set(pos,player);
	Collision(player, scrollX);
	Move(player);
}

void EnemyRRBullet::Move(Player2& player)
{
	if (mIsAlive) {
		mVelocity = mVector * mSpeed;
		mWorldCircle.pos += mVelocity;
	}
}

void EnemyRRBullet::Collision(Player2& player, float* scrollX)
{
	if (mWorldCircle.pos.x  < -mRadius + *scrollX || mWorldCircle.pos.x > 1280 + mRadius - *scrollX || mWorldCircle.pos.y < -mRadius  || mWorldCircle.pos.y > 720 + mRadius ) {
		mIsAlive = false;
	}
}

void EnemyRRBullet::Draw(float* scrollX)
{
	Novice::ScreenPrintf(100,200,"mIsAlive:%d", mIsAlive);
	if (mIsAlive) {
		mLocalCircle.pos = { mWorldCircle.pos.x - *scrollX,mWorldCircle.pos.y };
		Novice::DrawEllipse(mLocalCircle.pos.x, mLocalCircle.pos.y, mLocalCircle.radius, mWorldCircle.radius, 0.0f, mColor, kFillModeSolid);
	}
}
