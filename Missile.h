#pragma once
#include "Quad.h"
class Missile
{
public:
	//変数
	//敵本体
	float enemyWidth;
	float enemyHeight;
	Quad enemyQuad;
	Vec2 enemyPosition;
	int enemyVelocity;
	Vec2 enemyVector;
	unsigned int enemyColor;
	bool enmyIsAliveFlag;

	//ミサイル
	float missileWidth;
	float missileHeight;
	Quad missileQuad;
	Vec2 missilePosition;
	int missileVelocity;
	Vec2 missileVector;
	unsigned int missileColor;
	bool missileIsAliveFlag;

	bool setFlag;
	
	//関数
	Missile();
	void Init();
	void Set(Vec2 EnemyPosition, float EnemyWidth, float EnemyHeight, float EnemyVelocity, Vec2 MissilePosition, float MissileWidth, float MissileHeight, float MissileVelocity);
	void Update();
	//敵本体
	void EnemyCollision();
	void EnemyMove();
	void EnemyDraw();
	//ミサイル
	void MissileCollision();
	void MissileMove();
	void MissileDraw();
};

