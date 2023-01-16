#pragma once
#include "Vec2.h"
#include "Map.h"
#include "Quad.h"
#include "Circle.h"
#include "Player2.h"

class TestEnemy06
{
public:
	TestEnemy06(Vec2 position);
	~TestEnemy06();

	void Update(Player2& player, Map& map);
	void Draw(float* scrollX);
	void Spawn(Vec2 position);
	void Init(Vec2 position);

private:

	void Collision(Player2& player, Map& map);
	void Move();
	
	//ステータス
	Vec2 mPosition;
	Vec2 mSpeed;
	int mRadius;
	//当たり判定
	Quad mColQuad;


	bool mIsAlive;

	//スポーンタイマーの設定
	int mRespawnTime;

	//四点の当たり判定
	int left;
	int top;
	int right;
	int bottom;

	//速度の設定
	bool mSetTarget;

	//動く時間
	int mMoveTime;
	//動く時間の設定
	int mRandMoveTime;

	//止まる時間
	int mStopTime;

	//SE
	int mKnockSE;

};


