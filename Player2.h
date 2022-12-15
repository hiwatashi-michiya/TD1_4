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

	Vec2 bombVelocity;

	Vec2 knockBackVelocity;

	Vec2 BombPos;
	int BombRad = 0;

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

	bool onGround = false;

public:

	Player2();
	void Init();

	void GridInit();

	void Update(Map map);

	void Draw();

	Quad GetPlayerQuad() { return playerColQuad; };
};



