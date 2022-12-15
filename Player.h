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

	//十字キーの動き
	int stickPositionX;
	int stickPositionY;

	//ボムを投げる方向
	int bombStickPositionX;
	int bombStickPositionY;

	int preBombStickPositionX;
	int preBombStickPositionY;

	//爆弾の情報
	Vec2 bombPosition;
	Vec2 bombVelocity;
	float bombLength;

	//ボムの当たり判定
	Circle bombCollision;

	//ブロックの当たり判定(ボム専用)
	Vec2 blockLeftTop;
	Vec2 blockRightTop;
	Vec2 blockLeftBottom;
	Vec2 blockRightBottom;
	Quad blockCollision;

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
	Vec2 knockBackVelocity;

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

