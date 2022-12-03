#include "TestEnemy2.h"
#include <Novice.h>

TestEnemy2::TestEnemy2()
{
	position = { 0.0f,0.0f };
	Init();
}

void TestEnemy2::Init()
{
	LeftTop = { position.x + 0.0f,position.y + 0.0f };
	RightTop = { position.x + 64.0f,position.y + 0.0f };
	LeftBottom = { position.x + 0.0f,position.y + 64.0f };
	RightBottom = { position.x + 64.0f,position.y + 64.0f };

	isAlive = false;
	fallFlag = false;



	texture = Novice::LoadTexture("white1x1.png");
	velocity = { 0.0f, 0.0f };
	vector = { 0.0f,0.0f };
	speed = 0.5f;
}

void TestEnemy2::Set(Vec2 pos)
{
	position = pos;
	LeftTop = { position.x + 0.0f,position.y + 0.0f };
	RightTop = { position.x + 64.0f,position.y + 0.0f };
	LeftBottom = { position.x + 0.0f,position.y + 64.0f };
	RightBottom = { position.x + 64.0f,position.y + 64.0f };
}



void TestEnemy2::Update(Player player, Map map, float slow)
{
	if ((player.LeftTop.y >= LeftTop.y && player.LeftTop.y <= LeftBottom.y) || (player.LeftBottom.y <= LeftTop.y && player.LeftBottom.y >= LeftBottom.y) && !isAlive) {
		isAlive = true;
	}

	if (isAlive) {
		vector = { 1.0f,0.0f };
		velocity += vector * speed;
		Vec2 tmpLeftTop, tmpRightTop, tmpLeftBottom, tmpRightBottom;
		int LeftTopX, RightTopX, LeftBottomX, RightBottomX;
		int LeftTopY, RightTopY, LeftBottomY, RightBottomY;

		tmpLeftTop = LeftTop + velocity;
		tmpRightTop.x = (RightTop.x - 1) + velocity.x;
		tmpRightTop.y = (RightTop.y) + velocity.y;
		tmpLeftBottom.x = LeftBottom.x + velocity.x;
		tmpLeftBottom.y = (LeftBottom.y - 1) + velocity.y;
		tmpRightBottom.x = RightBottom.x - 1 + velocity.x;
		tmpRightBottom.y = RightBottom.y - 1 + velocity.y;

		LeftTopX = (int)(tmpLeftTop.x / (MAP_SIZE));
		LeftTopY = (int)(tmpLeftTop.y / (MAP_SIZE));

		RightTopX = (int)(tmpRightTop.x / (MAP_SIZE));
		RightTopY = (int)(tmpRightTop.y / (MAP_SIZE));

		LeftBottomX = (int)(tmpLeftBottom.x / (MAP_SIZE));
		LeftBottomY = (int)(tmpLeftBottom.y / (MAP_SIZE));

		RightBottomX = (int)(tmpRightBottom.x / (MAP_SIZE));
		RightBottomY = (int)(tmpRightBottom.y / (MAP_SIZE));
		if (!(map.map[RightTopY][RightTopX] == map.NONE || map.map[RightTopY][RightTopX] == map.TMPNONE) ||
			!(map.map[RightBottomY][RightBottomX] == map.NONE || map.map[RightBottomY][RightBottomX] == map.TMPNONE)) {
			float num = (LeftTopX + 1) * MAP_SIZE;
			LeftTop.x = num;
			RightTop.x = num;
			LeftBottom.x = num + MAP_SIZE * 2;
			RightBottom.x = num + MAP_SIZE * 2;
			velocity = { 0,0 };
		}
		if ((map.map[RightTopY][RightTopX] == map.NONE || map.map[RightTopY][RightTopX] == map.TMPNONE) &&
			(map.map[RightBottomY][RightBottomX] == map.NONE || map.map[RightBottomY][RightBottomX] == map.TMPNONE)) {
			LeftTop += velocity * slow;
			RightTop += velocity * slow;
			LeftBottom += velocity * slow;
			RightBottom += velocity * slow;
		}
		else {
			float num = (RightTopX)*MAP_SIZE;
			LeftTop.x = num;
			RightTop.x = num;
			LeftBottom.x = num + MAP_SIZE * 2;
			RightBottom.x = num + MAP_SIZE * 2;
			velocity = { 0,0 };
			Init();
		}

	}
}

void TestEnemy2::Draw()
{
	Novice::DrawQuad(LeftTop.x, LeftTop.y, RightTop.x, RightTop.y, LeftBottom.x, LeftBottom.y, RightBottom.x, RightBottom.y, 0, 0, 64, 64, texture, WHITE);
}