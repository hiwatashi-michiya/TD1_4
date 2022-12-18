#include "Player2.h"
#include "ControllerInput.h"
#include <Novice.h>

Player2::Player2()
{
	position = { 64,600 };
	nextPosition = { 64,600 };
	moveVector = { 0,0 };
	size = { 32,32};
	playerColQuad = { position , int(size.x),int(size.y)};

	speed = 5.0f;
	
	

}

void Player2::Init()
{
}

void Player2::Update(Map map, float* scrollX)
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	moveVector.x = 0;
	//moveVector.y = 0;

	float minusSpeed = 0.5f;

	if (knockBackVelocity.x > 0) {
		knockBackVelocity.x -= minusSpeed;
	}
	if (knockBackVelocity.x < 0) {
		knockBackVelocity.x += minusSpeed;
	}

	if (knockBackVelocity.x <= minusSpeed && knockBackVelocity.x >= -minusSpeed) {
		knockBackVelocity.x = 0;
	}

	Novice::GetAnalogInputLeft(0, &stickPositionX, &stickPositionY);

	if ((keys[DIK_W] && preKeys[DIK_W] == 0) || Controller::IsTriggerButton(0, Controller::bA) == 1) {
		moveVector.y -= 13;
		//moveVector.y -= speed;
	}
	if (keys[DIK_A] || stickPositionX < 0) {
		moveVector.x -= speed;
	}
	/*if (keys[DIK_S]) {
		moveVector.y += speed;
	}*/
	if (keys[DIK_D] || stickPositionX > 0) {
		moveVector.x += speed;
	}

	if (BombRad > 0) {
		BombRad-= 3;
	}

	Novice::GetAnalogInputRight(0, &bombStickPositionX, &bombStickPositionY);
	
	
	if (fabs(bombStickPositionX) - fabs(preBombStickPositionX) > 10000 || fabs(bombStickPositionY) - fabs(preBombStickPositionY) > 10000) {
		bombVelocity.x = (cosf((bombStickPositionX - pow(2, 15)) * M_PI / powf(2, 16)) * 5.0f);
		bombVelocity.y = sinf(bombStickPositionY * M_PI / powf(2, 16)) * 5.0f;

		moveVector.y = 0;

		knockBackVelocity = { -bombVelocity.x * 3 ,  -bombVelocity.y * 3 };
	
		BombPos = { position.x + bombVelocity.x , position.y + bombVelocity.y };
		BombRad = 60;
	}

	preBombStickPositionX = bombStickPositionX;
	preBombStickPositionY = bombStickPositionY;

	moveVector.y += G * Weight;

	nextPosition.x = position.x + moveVector.x + knockBackVelocity.x;
	nextPosition.y = position.y + moveVector.y + knockBackVelocity.y;

	GridInit();
	
	if (position.y - nextPosition.y < 0) {
		if (map.map[UpGrid][RightGrid] == map.CANTBLOCK) {
			moveVector.x = 0;
			//スクロール値調整
			*scrollX -= knockBackVelocity.x;
			nextPosition.x = RightGrid * MAP_SIZE - size.x / 2;
			GridInit();
		}

		if (map.map[UpGrid][LeftGrid] == map.CANTBLOCK) {
			moveVector.x = 0;
			//スクロール値調整
			*scrollX -= knockBackVelocity.x;
			nextPosition.x = (LeftGrid + 1) * MAP_SIZE + size.x / 2;
			GridInit();
		}
	}
	else {
		if (map.map[DownGrid][RightGrid] == map.CANTBLOCK) {
			moveVector.x = 0;
			//スクロール値調整
			*scrollX -= knockBackVelocity.x;
			nextPosition.x = RightGrid * MAP_SIZE - size.x / 2;
			GridInit();
		}

		if (map.map[DownGrid][LeftGrid] == map.CANTBLOCK) {
			moveVector.x = 0;
			//スクロール値調整
			*scrollX -= knockBackVelocity.x;
			nextPosition.x = (LeftGrid + 1) * MAP_SIZE + size.x / 2;
			GridInit();
		}
	}

	

	if (map.map[UpGrid][RightGrid] == map.CANTBLOCK) {
		if (map.map[UpGrid][PosXGrid] != map.CANTBLOCK) {


			if (Right > RightGrid * MAP_SIZE && position.y - nextPosition.y < 0) {
				moveVector.x = 0;
				//スクロール値調整
				*scrollX -= knockBackVelocity.x;
				nextPosition.x = RightGrid * MAP_SIZE - size.x / 2;
				GridInit();


			}
			else {

				if (Up < (UpGrid + 1) * MAP_SIZE ) {
					moveVector.y = 0;
					knockBackVelocity.y = 0;
					nextPosition.y = (UpGrid + 2) * MAP_SIZE - size.y / 2;
					GridInit();
				}
			}
		}
	}

	if (map.map[UpGrid][LeftGrid] == map.CANTBLOCK) {
		if (map.map[UpGrid][PosXGrid] != map.CANTBLOCK) {


			if (Left < (LeftGrid + 1) * MAP_SIZE && position.y - nextPosition.y < 0) {
				moveVector.x = 0;
				//スクロール値調整
				*scrollX -= knockBackVelocity.x;
				nextPosition.x = (LeftGrid + 2) * MAP_SIZE - size.x / 2;
				GridInit();


			}
			else {

				if (Up < (UpGrid + 1) * MAP_SIZE) {
					moveVector.y = 0;
					knockBackVelocity.y = 0;
					nextPosition.y = (UpGrid + 2) * MAP_SIZE - size.y / 2;
					GridInit();
				}
			}
		}
	}

	if (map.map[DownGrid][RightGrid] == map.CANTBLOCK) {
		if (map.map[DownGrid][PosXGrid] != map.CANTBLOCK) {
			if (Right > RightGrid * MAP_SIZE && position.y - nextPosition.y > 0.0f) {
				moveVector.x = 0;
				//スクロール値調整
				*scrollX -= knockBackVelocity.x;
				nextPosition.x = RightGrid * MAP_SIZE - size.x / 2;
				GridInit();
			}
			else {
				if (Down >= DownGrid * MAP_SIZE && position.y + size.y / 2 <= (DownGrid)*MAP_SIZE) {
					moveVector.y = 0;
					knockBackVelocity.y = 0;
					nextPosition.y = DownGrid * MAP_SIZE - size.y / 2;
					GridInit();
				}
				else {
					moveVector.x = 0;
					//スクロール値調整
					*scrollX -= knockBackVelocity.x;
					nextPosition.x = RightGrid * MAP_SIZE - size.x / 2;
					GridInit();
				}
			}
		}
	}

	

	else if (map.map[DownGrid][LeftGrid] == map.CANTBLOCK) {
		if (map.map[DownGrid][PosXGrid] != map.CANTBLOCK) {
			if (Left < (LeftGrid + 1) * MAP_SIZE && position.y - nextPosition.y > 0.0f) {
				moveVector.x = 0;
				//スクロール値調整
				*scrollX -= knockBackVelocity.x;
				nextPosition.x = (LeftGrid + 1) * MAP_SIZE + size.x / 2;
				GridInit();
			}
			else {
				if (Down >= DownGrid * MAP_SIZE && position.y + size.y / 2 <= (DownGrid)*MAP_SIZE) {
					moveVector.y = 0;
					knockBackVelocity.y = 0;
					nextPosition.y = DownGrid * MAP_SIZE - size.y / 2;
					GridInit();
				}
				else {
					moveVector.x = 0;
					//スクロール値調整
					*scrollX -= knockBackVelocity.x;
					nextPosition.x = (LeftGrid + 1) * MAP_SIZE + size.x / 2;
					GridInit();
				}
			}
		}
	}

	Novice::ScreenPrintf(400, 420, "%0.2f", position.y + size.y / 2);
	Novice::ScreenPrintf(400, 440, "%d", (DownGrid)*MAP_SIZE);

	if (map.map[UpGrid][PosXGrid] == map.CANTBLOCK) {
		moveVector.y = 1;
		knockBackVelocity.y = 0;
		nextPosition.y = (UpGrid + 1) * MAP_SIZE + size.y / 2;
		GridInit();
	}

	if (map.map[DownGrid][PosXGrid] == map.CANTBLOCK) {
		moveVector.y = 0;
		knockBackVelocity.y = 0;
		nextPosition.y = DownGrid * MAP_SIZE - size.y / 2;
		GridInit();
	}

	Novice::ScreenPrintf(400, 400, "%0.2f", position.y - nextPosition.y);

	position.x = nextPosition.x;
	position.y = nextPosition.y;

	if (position.x > MAP_SIZE * 20 && position.x < MAP_SIZE * 30) {
		*scrollX += moveVector.x + knockBackVelocity.x;
	}
	else {

		if (position.x <= MAP_SIZE * 20) {
			*scrollX = 0;
		}

		if (position.x >= MAP_SIZE * 30) {
			*scrollX = MAP_SIZE * 10;
		}

	}

}

void Player2::Draw(float* scrollX)
{
	Novice::DrawQuad(
		position.x - size.x / 2 - *scrollX, position.y - size.y / 2,
		position.x + size.x / 2 - *scrollX, position.y - size.y / 2,
		position.x - size.x / 2 - *scrollX, position.y + size.y / 2,
		position.x + size.x / 2 - *scrollX, position.y + size.y / 2,
		0, 0,
		size.x, size.y,
		0, WHITE
	);
//	Novice::DrawEllipse(Left, nextPosition.y, 3, 3, 0, RED, kFillModeSolid);
//	Novice::DrawEllipse(Right, nextPosition.y, 3, 3, 0, RED, kFillModeSolid);
	//Novice::DrawEllipse(nextPosition.x, Up, 3, 3, 0, RErD, kFillModeSolid);
	//Novice::DrawEllipse(nextPosition.x, Down, 3, 3, 0, RED, kFillModeSolid);
	Novice::DrawEllipse(LeftGrid * MAP_SIZE + MAP_SIZE / 2 - *scrollX, (DownGrid + 1) * MAP_SIZE, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(RightGrid * MAP_SIZE + MAP_SIZE / 2 - *scrollX, nextPosition.y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(nextPosition.x - *scrollX, UpGrid * MAP_SIZE , 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(nextPosition.x - *scrollX, (DownGrid + 1) * MAP_SIZE , 3, 3, 0, BLUE, kFillModeSolid);

	Novice::DrawEllipse(BombPos.x - *scrollX, BombPos.y, BombRad, BombRad, 0, RED, kFillModeSolid);



	/*Novice::DrawEllipse(block[check[2]][check[0]].x, block[check[2]][check[0]].y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(block[check[2]][check[1]].x, block[check[2]][check[1]].y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(block[check[3]][check[0]].x, block[check[3]][check[0]].y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(block[check[3]][check[1]].x, block[check[3]][check[1]].y, 3, 3, 0, BLUE, kFillModeSolid);*/

}

void Player2::GridInit()
{

	Left = nextPosition.x - size.x / 2 ;
	Right = nextPosition.x + size.x / 2 - 1;
	Up = nextPosition.y - size.y / 2;
	Down = nextPosition.y + size.y / 2 ;

	LeftGrid = Left / MAP_SIZE;
	RightGrid = Right / MAP_SIZE;
	UpGrid = Up / MAP_SIZE;
	DownGrid = Down / MAP_SIZE;
	PosXGrid = nextPosition.x / MAP_SIZE;
	PosYGrid = nextPosition.y / MAP_SIZE;
}
