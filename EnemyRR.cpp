#include "EnemyRR.h"
#include "Matrix33 .h"
#include "Collision.h"
#include "EnemyRRBullet.h"
#include <Novice.h>

EnemyRR::EnemyRR()
{
	Init();
}

void EnemyRR::Init()
{
	localPos = { 0,0 };
	worldPos = { 0,0 };
	localQuad = { {0,0},{0,0},{0,0},{0,0} };
	worldQuad = { {0,0},{0,0},{0,0},{0,0} };
	/*radius = 0;*/
	width = 0;
	height = 0;
	texture = 0;
	color = 0xFFFFFFFF;
	search = { worldPos,0 };
	bullet.Init();
}

void EnemyRR::Set(Vec2 pos,int width,int height,float searchRadius)
{
	worldPos = pos;
	worldQuad = { {0.0f,0.0f}, width, height };
	this->width = width;
	this->height = height;
	search = { worldPos ,searchRadius };
}

void EnemyRR::Update(Player2& player, float* scrollX)
{
	Collision();
	Move(player,scrollX);
}

void EnemyRR::Collision()
{

}

void EnemyRR::Move(Player2& player, float* scrollX)
{
	Circle tmp = { {search.pos.x - *scrollX ,search.pos.y},search.radius };
	float length = tmp.pos.DistanceFrom({ player.GetPlayerPos().x - *scrollX,player.GetPlayerPos().y });
	if (length < search.radius) {
		bullet.Set(worldPos,player);
	}
	if (bullet.mIsAlive) {
		bullet.Update(player,worldPos, scrollX);
	}
}


void EnemyRR::Draw(float* scrollX)
{
	Circle tmpCircle = { {search.pos.x - *scrollX ,search.pos.y},search.radius };
	Novice::DrawEllipse(tmpCircle.pos.x, tmpCircle.pos.y, tmpCircle.radius, tmpCircle.radius, 0.0f, WHITE, kFillModeWireFrame);
	localPos = { worldPos.x - *scrollX,worldPos.y };
	Matrix33 tmp = Matrix33::MakeAffine({ 1,1 }, 0, { localPos});
	localQuad = worldQuad * tmp;
	Novice::DrawQuad(localQuad.LeftTop.x, localQuad.LeftTop.y, localQuad.RightTop.x, localQuad.RightTop.y, localQuad.LeftBottom.x, localQuad.LeftBottom.y, localQuad.RightBottom.x, localQuad.RightBottom.y, 0, 0, width, height, texture, color);
	bullet.Draw(scrollX);
}
