#pragma once
#include "Vec2.h"
#include "Circle.h"
#include "Player2.h"

class EnemyRRBullet
{
public:
	EnemyRRBullet();

	/*Vec2 mWorldPos;
	Vec2 mLocalPos;*/
	Circle mLocalCircle;
	Circle mWorldCircle;
	Vec2 mVector;
	Vec2 mVelocity;
	float mSpeed;

	unsigned int mColor;
	float mRadius;
	bool mIsAlive;//ê∂Ç´ÇƒÇÈÇ©Ç«Ç§Ç©éÂÇÍÇ≈Ç°ÇÒÇ™zÅ|ÇÃÇÀÇ±

	void Init();
	void Set(Vec2 pos, Player2& player);
	void Update(Player2& player, Vec2 pos, float* scrollX);
	void Move(Player2& player);
	void Collision(Player2& player, float* scrollX);
	void Draw(float* scrollX);
};

