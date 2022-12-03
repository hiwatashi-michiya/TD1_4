#include "TestEnemy.h"
#include <Novice.h>

TestEnemy::TestEnemy()
{
	Init();
}

void TestEnemy::Init()
{
	position = { 128.0f,32.0f };
	LeftTop = { position.x + 0.0f,position.y + 0.0f };
	RightTop = { position.x + 64.0f,position.y + 0.0f };
	LeftBottom = { position.x + 0.0f,position.y + 64.0f };
	RightBottom = { position.x + 64.0f,position.y + 64.0f };

	isAlive = false;
	fallFlag = false;



	texture = Novice::LoadTexture("white1x1.png");
	velocity = {0.0f, 0.0f};
	vector = {0.0f,0.0f};
	speed = 0.5f;
}

void TestEnemy::Update(Player player,Map map, float slow)
{
	if ((player.RightBottom.x >= LeftBottom.x && player.RightBottom.x <= RightBottom.x) || (player.LeftBottom.x <= LeftBottom.x && player.LeftBottom.x >= RightBottom.x) && !isAlive) {
		isAlive = true;
		/*fallFlag = true;*/
	}

	if (isAlive) {
		vector = { 0.0f,1.0f };
		velocity += vector * speed;
		Vec2 tmpLeftTop, tmpRightTop, tmpLeftBottom, tmpRightBottom;
		int LeftTopX, RightTopX, LeftBottomX, RightBottomX;
		int LeftTopY, RightTopY, LeftBottomY, RightBottomY;

		tmpLeftTop = LeftTop + velocity;
		tmpRightTop.x = (RightTop.x - 1) + velocity.x;
		tmpRightTop.y = (RightTop.y) + velocity.y;
		tmpLeftBottom.x = LeftBottom.x + velocity.x;
		tmpLeftBottom.y = (LeftBottom.y) + velocity.y;
		tmpRightBottom.x = RightBottom.x - 1 + velocity.x;
		tmpRightBottom.y = RightBottom.y + velocity.y;

		LeftTopX = (int)(tmpLeftTop.x / (MAP_SIZE));
		LeftTopY = (int)(tmpLeftTop.y / (MAP_SIZE));

		RightTopX = (int)(tmpRightTop.x / (MAP_SIZE));
		RightTopY = (int)(tmpRightTop.y / (MAP_SIZE));

		LeftBottomX = (int)(tmpLeftBottom.x / (MAP_SIZE));
		LeftBottomY = (int)(tmpLeftBottom.y / (MAP_SIZE));

		RightBottomX = (int)(tmpRightBottom.x / (MAP_SIZE));
		RightBottomY = (int)(tmpRightBottom.y / (MAP_SIZE));
		if (!(map.map[LeftTopY][LeftTopX] == map.NONE || map.map[LeftTopY][LeftTopX] == map.TMPNONE) ||
			!(map.map[RightTopY][RightTopX] == map.NONE || map.map[RightTopY][RightTopX] == map.TMPNONE)) {
			float num = (LeftTopY + 1) * MAP_SIZE;
			LeftTop.y = num;
			RightTop.y = num;
			LeftBottom.y = num + MAP_SIZE;
			RightBottom.y = num + MAP_SIZE;
			velocity = { 0,0 };
		}
		if ((map.map[LeftBottomY][LeftBottomX] == map.NONE || map.map[LeftBottomY][LeftBottomX] == map.TMPNONE) &&
			(map.map[RightBottomY][RightBottomX] == map.NONE || map.map[RightBottomY][RightBottomX] == map.TMPNONE)) {
			LeftTop += velocity;
			RightTop += velocity;
			LeftBottom += velocity;
			RightBottom += velocity;
		}
		else {
			float num = (LeftTopY)*MAP_SIZE;
			LeftTop.y = num;
			RightTop.y = num;
			LeftBottom.y = num + MAP_SIZE;
			RightBottom.y = num + MAP_SIZE;
			velocity = { 0,0 };
			/*isAlive = false;*/
			Init();
		}
		
	}
}

void TestEnemy::Draw()
{
	Novice::DrawQuad(LeftTop.x, LeftTop.y, RightTop.x, RightTop.y, LeftBottom.x, LeftBottom.y, RightBottom.x, RightBottom.y,0,0,64,64, texture,WHITE);
}
