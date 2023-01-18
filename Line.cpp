#include "Line.h"
#include <Novice.h>
#include "Collision.h"

Line::Line()
{
	Init();
}

void Line::Init()
{
	mPosition = {0.0f,0.0f};
	mSpeed = 15.0f;
	mCount = 0;
	mCountMax = 60;
	stop = 0;
}

void Line::Update(Player2& player)
{
	Move();
	Collision(player);
}

void Line::Move()
{

	if (mCount > mCountMax&& stop % 2 == 0) {
		mPosition.x += mSpeed;
	}
	else {
		mCount++;
	}
}

void Line::Collision(Player2& player)
{
	if (player.GetPlayerPos().x < mPosition.x) {
		player.Init();
		Init();
	}
}

void Line::Draw(float* scrollX)
{
	int x = mPosition.x - *scrollX;
	/*Novice::ScreenPrintf(700,400,"mPosition.x:%f", mPosition.x);*/
	Novice::DrawQuad(0,0, x,0,0,720, x,720,0,0, x,720,0,0x8B0000AA);
}
