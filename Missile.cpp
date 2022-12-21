#include "Missile.h"
#include <Novice.h>

Missile::Missile()
{
	Init();
}

void Missile::Init()
{
	//敵本体
	enemyWidth = 0.0f;
	enemyHeight = 0.0f;
	enemyPosition = { 0.0f,0.0f };
	enemyQuad = {enemyPosition,enemyWidth,enemyHeight };
	enemyVelocity = 0.0f;
	enemyVector = {0.0f,0.0f};
	enmyIsAliveFlag = false;

	//ミサイル
	missileWidth = 0.0f;
	missileHeight = 0.0f;
	missilePosition = { 0.0f,0.0f };
	missileQuad = { missilePosition ,missileWidth ,missileHeight };
	missileVelocity = 5.0f;
	missileVector = { 0.0f,0.0f };
	missileIsAliveFlag = false;

	setFlag = false;
}

void Missile::Set(Vec2 EnemyPosition, float EnemyWidth, float EnemyHeight, float EnemyVelocity, Vec2 MissilePosition, float MissileWidth, float MissileHeight, float MissileVelocity)
{
	if (!setFlag) {
		//敵本体
		enemyWidth = EnemyWidth;
		enemyHeight = EnemyHeight;
		enemyPosition = EnemyPosition;
		enemyQuad = { enemyPosition,enemyWidth,enemyHeight };
		enemyVelocity = EnemyVelocity;
		enemyVector = { 0.0f,0.0f };
		enemyColor=WHITE;
		enmyIsAliveFlag = true;

		//ミサイル
		missileWidth = MissileWidth;
		missileHeight = MissileHeight;
		missilePosition = MissilePosition;
		missileQuad = { missilePosition ,missileWidth ,missileHeight };
		missileVelocity = MissileVelocity;
		missileVector = { 0.0f,0.0f };
		missileColor = WHITE;
		missileIsAliveFlag = true;


		setFlag = true;
	}
}

void Missile::Update()
{
	if (enmyIsAliveFlag) {
		EnemyCollision();
		EnemyMove();
	}
	if (missileIsAliveFlag) {
		MissileCollision();
		MissileMove();
	}
}

void Missile::EnemyCollision()
{
}

void Missile::EnemyMove()
{
}

void Missile::MissileCollision()
{
}

void Missile::MissileMove()
{
}

void Missile::EnemyDraw()
{
	Novice::DrawQuad(enemyQuad.LeftTop.x, enemyQuad.LeftTop.y, enemyQuad.RightTop.x, enemyQuad.RightTop.y, enemyQuad.LeftBottom.x, enemyQuad.LeftBottom.y, enemyQuad.RightBottom.x, enemyQuad.RightBottom.y,0,0, enemyWidth, enemyHeight, 0,enemyColor);
}

void Missile::MissileDraw()
{
	Novice::DrawQuad(missileQuad.LeftTop.x, missileQuad.LeftTop.y, missileQuad.RightTop.x, missileQuad.RightTop.y, missileQuad.LeftBottom.x, missileQuad.LeftBottom.y, missileQuad.RightBottom.x, missileQuad.RightBottom.y, 0, 0, missileWidth, missileHeight, 0, missileColor);
}
