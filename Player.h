#pragma once
#include "Vec2.h"
#include "Map.h"
#include"Quad.h"
#include"Circle.h"

class Player
{
public:
	Player();
	void Init();
	void SetLeft();
	void SetRight();

	//ボムの初期化
	void BombInit();

	//ボムを投げる向き
	int stickPositionX;
	int stickPositionY;

	//爆弾の情報
	Vec2 bombPosition;
	Vec2 bombVelocity;
	float bombLength;

	//爆破したかどうか
	bool isExplosion;

	//投げるモーションに入っているかどうか
	bool isThrowMotion;

	//投げたかどうか
	bool isAfterThrow;

	//ボムの画像
	int bombTexture;

	Vec2 position;
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;
	Vec2 vector;
	Vec2 velocity;
	Vec2 knockBackVelocity= {0,0};

	Quad playerColQuad = { LeftTop ,RightTop ,LeftBottom ,RightBottom };
	
	float speed;
	
	bool jumpFlag;
	float jumpSpeed;

	Vec2 gravityVector;
	Vec2 gravityVelocity;
	float gravitySpeed;

	bool expflag = false;

	int key;
	int prekey;

	int texture;

	void Update(Map map, float slow);
	void Draw(float isColorReverse);

	Quad GetPlayerQuad() { return playerColQuad;};

	void hitCircle(Circle targetCircle, Vec2 knockBack,int Damage);
};

