#include "Player2.h"
#include <Novice.h>

Player2::Player2()
{
	position = { 64,600 };
	nextPosition = { 64,600 };
	moveVector = { 0,0 };
	size = { 32,32};
	playerColQuad = { position , int(size.x),int(size.y)};

	speed = 8;
	
	

}

void Player2::Init()
{
}

void Player2::Update(Map map)
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	moveVector.x = 0;
	moveVector.y = 0;

	if (keys[DIK_W]/* && preKeys[DIK_W] == 0*/) {
		//moveVector.y -= 14;
		moveVector.y -= speed;
	}
	if (keys[DIK_A]) {
		moveVector.x -= speed;
	}
	if (keys[DIK_S]) {
		moveVector.y += speed;
	}
	if (keys[DIK_D]) {
		moveVector.x += speed;
	}

	//moveVector.y += G * Weight;

	nextPosition.x = position.x + moveVector.x;
	nextPosition.y = position.y + moveVector.y;

	GridInit();
	
	
	if (map.map[PosYGrid][RightGrid] == map.CANTBLOCK) {
		moveVector.x = 0;
		nextPosition.x = RightGrid * MAP_SIZE;
		GridInit();
	}

	if (map.map[PosYGrid][LeftGrid] == map.CANTBLOCK) {
		moveVector.x = 0;
		nextPosition.x = LeftGrid * MAP_SIZE;
		GridInit();
	}

	if (map.map[UpGrid][PosXGrid] == map.CANTBLOCK) {
		moveVector.y = 0;
		nextPosition.y = UpGrid * MAP_SIZE;
		GridInit();
	}

	Down = nextPosition.y + size.y / 2 - 1;
	if (map.map[DownGrid][PosXGrid] == map.CANTBLOCK) {
		moveVector.y = 0;
		nextPosition.y = DownGrid * MAP_SIZE;
		GridInit();
	}

	position.x += moveVector.x;
	position.y += moveVector.y;

}

void Player2::Draw()
{
	Novice::DrawQuad(
		position.x - size.x / 2, position.y - size.y / 2,
		position.x + size.x / 2, position.y - size.y / 2,
		position.x - size.x / 2, position.y + size.y / 2,
		position.x + size.x / 2, position.y + size.y / 2,
		0, 0,
		size.x, size.y,
		0, WHITE
	);

	Novice::DrawEllipse(Left, nextPosition.y, 3, 3, 0, RED, kFillModeSolid);
	Novice::DrawEllipse(Right, nextPosition.y, 3, 3, 0, RED, kFillModeSolid);
	Novice::DrawEllipse(nextPosition.x, Up, 3, 3, 0, RED, kFillModeSolid);
	Novice::DrawEllipse(nextPosition.x, Down, 3, 3, 0, RED, kFillModeSolid);
	Novice::DrawEllipse(LeftGrid * MAP_SIZE, nextPosition.y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(RightGrid * MAP_SIZE , nextPosition.y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(nextPosition.x, UpGrid * MAP_SIZE , 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(nextPosition.x, DownGrid * MAP_SIZE , 3, 3, 0, BLUE, kFillModeSolid);

	/*Novice::DrawEllipse(block[check[2]][check[0]].x, block[check[2]][check[0]].y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(block[check[2]][check[1]].x, block[check[2]][check[1]].y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(block[check[3]][check[0]].x, block[check[3]][check[0]].y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(block[check[3]][check[1]].x, block[check[3]][check[1]].y, 3, 3, 0, BLUE, kFillModeSolid);*/

}

void Player2::GridInit()
{

	Left = nextPosition.x - size.x / 2;
	Right = nextPosition.x + size.x / 2 - 1;
	Up = nextPosition.y - size.y / 2;
	Down = nextPosition.y + size.y / 2 - 1;

	LeftGrid = Left / MAP_SIZE;
	RightGrid = Right / MAP_SIZE;
	UpGrid = Up / MAP_SIZE;
	DownGrid = Down / MAP_SIZE;
	PosXGrid = nextPosition.x / MAP_SIZE;
	PosYGrid = nextPosition.y / MAP_SIZE;
}
