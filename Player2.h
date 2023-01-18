#pragma once
#include "Vec2.h"
#include "Map.h"
#include"Quad.h"
#include"Circle.h"

class Player2
{
private:

	Vec2 position;
	Vec2 nextPosition;
	Vec2 moveVector;
	Vec2 size;
	Quad playerColQuad;
	Quad nextPlayerColQuad;

	int bombStickPositionX;
	int bombStickPositionY;

	int preBombStickPositionX;
	int preBombStickPositionY;

	int stickPositionX;
	int stickPositionY;

	int prestickPositionX;
	int prestickPositionY;

	int bombCount;
	int bombCountMax;

	Vec2 bombVelocity;

	Vec2 knockBackVelocity;

	float BombPosMisal;
	
	Circle BombCircle;

	float speed;
	
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	float G = 9.8;
	float Weight = 0.05;
	
	int Left;
	int Right;
	int Up;
	int Down;
	int LeftGrid;
	int RightGrid;
	int UpGrid;
	int DownGrid;
	int PosXGrid;
	int PosYGrid;

	bool canJump;

	bool onGround = false;

	int overHeatGage;
	int maxOverHeatGage;
	int coolTimeGage;

	//壁すれ
	bool wallFlag;
	int wallCount;
	int wallCountMax;
	//チャージ
	bool isCharge;
	int chargeTime;
	float chargeMag;
	bool isBigExp;

	float BombPow;
	bool StickStetting = false;

	void Charge();

	//爆発した直後かどうか
	int isHeat;

	//プレイヤーの色
	int color;

	//減速カウント
	int decelCount;

public:

	Vec2 BombPos = { 9999,9999 };
	float BombRad = 0;

	Player2();
	void Init();

	void GridInit();

	void Update(float slow,Map& map, float* scrollX, Quad GateQuad);

	void HitTE4(Circle TargetQuad);

	void Draw(float* scrollX);

	//最大半径
	int MAXEXPSIZE = 96;

	//チャージタイムの取得
	int GetChargeTime() { return chargeTime; }

	//半径が大きいかどうかの取得
	bool GetIsBig() { return isBigExp; }

	Quad GetPlayerQuad() { return playerColQuad; };
	Vec2 GetPlayerPos() { return position;};
	Vec2 GetPlayerKnockbackVelocity() { return knockBackVelocity; };
	Circle GetBombCircle() { return BombCircle; };
};



