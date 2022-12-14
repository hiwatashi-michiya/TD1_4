#define USE_MATH_DEFINES_
#include <math.h>
#include "Player.h"
#include <Novice.h>
#include"Key.h"
#include"Collision.h"
#include"Circle.h"

Player::Player() {
	Init();
}

void Player::Init() {
	position = { 32.0f,640.0f };
	LeftTop = { position.x+0,position.y + 0 };
	RightTop = { position.x + 32,position.y + 0 };
	LeftBottom = { position.x+0,position.y + 32 };
	RightBottom = { position.x + 32,position.y + 32 };

	playerColQuad = { LeftTop ,RightTop ,LeftBottom ,RightBottom };
	vector = { 0,0 };
	velocity = { 0,0 };
	speed = 5.0f;

	gravityVector = { 0,0 };
	gravityVelocity = { 0,0 };
	gravitySpeed = 0.5;

	jumpFlag = false;
	jumpSpeed = 15.0f;

	stickPositionX = 0;
	stickPositionY = 0;

	BombInit();

	texture = Novice::LoadTexture("white1x1.png");
	bombTexture = Novice::LoadTexture("./Resources/bomb.png");
}

//ボムの位置の初期化
void Player::BombInit() {

	//ボムのステータス
	bombPosition = { -10000,10000 };
	bombVelocity = { 0,0 };
	bombLength = 16.0f;

	isThrowMotion = false;
	isAfterThrow = false;

}

void Player::SetLeft() {
	LeftTop.x = 32;
	RightTop.x = 64;
	LeftBottom.x = 32;
	RightBottom.x = 64;
}

void Player::SetRight() {
	LeftTop.x = 1280;
	RightTop.x = 1312;
	LeftBottom.x = 1280;
	RightBottom.x = 1312;
}

void Player::Update(Map map,float slow) {
	vector = { 0,0 };
	gravityVector = { 0,0 };

	//パッドのスティック入力受付
	Novice::GetAnalogInputLeft(0, &stickPositionX, &stickPositionY);

	//爆弾を投げようとしている状態か
	if (isThrowMotion == true) {

		//R2で爆弾を投げる
		if (Novice::IsTriggerButton(0, kPadButton11) && isAfterThrow == false) {
			isAfterThrow = true;
			bombVelocity.x = cosf((stickPositionX - pow(2, 15)) * M_PI / powf(2, 16)) * 5.0f;
			bombVelocity.y = sinf(stickPositionY * M_PI / powf(2, 16)) * 5.0f;
			bombPosition.x = LeftTop.x + bombLength;
			bombPosition.y = LeftTop.y + bombLength;
			isThrowMotion = false;
		}

	}

	//ボムが投げられた状態の時にボムを動かす
	if (isAfterThrow == true) {

		bombVelocity.y += 0.1f;
		bombPosition.x += bombVelocity.x;
		bombPosition.y += bombVelocity.y;

		//画面外に出たら消滅
		if (bombPosition.x - bombLength > 1280 || bombPosition.x + bombLength < 0) {
			BombInit();
		}

		if (bombPosition.y - bombLength > 720 || bombPosition.y + bombLength < 0) {
			BombInit();
		}

	}

	if (isThrowMotion == false) {

		//R2で爆弾を投げる状態に遷移
		if (Novice::IsTriggerButton(0, kPadButton11) && isAfterThrow == false) {
			isThrowMotion = true;
		}

		//スティックの入力追加
		if (Key::IsPress(DIK_A) || stickPositionX < 0) {
			vector = { -1,0 };
			velocity = vector * speed /** slow*/;

			////////////////////////当たり判定/////////////////////////
			Vec2 tmpLeftTop, tmpLeftBottom;
			int LeftTopX, LeftBottomX;
			int LeftTopY, LeftBottomY;
			tmpLeftTop = LeftTop + velocity;
			tmpLeftBottom.x = LeftBottom.x + velocity.x;
			tmpLeftBottom.y = (LeftBottom.y - 1) + velocity.y;

			LeftTopX = (int)(tmpLeftTop.x / (MAP_SIZE));
			LeftTopY = (int)(tmpLeftTop.y / (MAP_SIZE));

			LeftBottomX = (int)(tmpLeftBottom.x / (MAP_SIZE));
			LeftBottomY = (int)(tmpLeftBottom.y / (MAP_SIZE));

			if ((map.map[LeftTopY][LeftTopX] == map.NEEDLE /*|| map.map[LeftTopY][LeftTopX] == map.NEEDLE*/) &&
				(map.map[LeftBottomY][LeftBottomX] == map.NEEDLE/* || map.map[LeftBottomY][LeftBottomX] == map.NEEDLE)*/)) {
				Init();
				/*LeftTop += velocity * slow;
				RightTop += velocity * slow;
				LeftBottom += velocity * slow;
				RightBottom += velocity * slow;*/
			}
			/*else {
				float num = (LeftBottomX + 1) * MAP_SIZE;
				LeftTop.x = num;
				RightTop.x = num + MAP_SIZE;
				LeftBottom.x = num;
				RightBottom.x = num + MAP_SIZE;
			}*/

			if ((map.map[LeftTopY][LeftTopX] == map.NONE || map.map[LeftTopY][LeftTopX] == map.TMPNONE ||
				map.map[LeftTopY][LeftTopX] == map.REDNONE || map.map[LeftTopY][LeftTopX] == map.GREENNONE ||
				map.map[LeftTopY][LeftTopX] == map.BLUENONE) &&
				(map.map[LeftBottomY][LeftBottomX] == map.NONE || map.map[LeftBottomY][LeftBottomX] == map.TMPNONE ||
					map.map[LeftBottomY][LeftBottomX] == map.REDNONE || map.map[LeftBottomY][LeftBottomX] == map.GREENNONE ||
					map.map[LeftBottomY][LeftBottomX] == map.BLUENONE)) {
				LeftTop += velocity * slow;
				RightTop += velocity * slow;
				LeftBottom += velocity * slow;
				RightBottom += velocity * slow;
			}
			else {
				float num = (LeftBottomX + 1) * MAP_SIZE;
				LeftTop.x = num;
				RightTop.x = num + MAP_SIZE;
				LeftBottom.x = num;
				RightBottom.x = num + MAP_SIZE;
			}
		}
		//スティックの入力追加
		if (Key::IsPress(DIK_D) || stickPositionX > 0) {
			vector = { 1,0 };
			velocity = vector * speed /** slow*/;

			////////////////////////当たり判定/////////////////////////
			Vec2 tmpRightTop, tmpRightBottom;
			int RightTopX, RightBottomX;
			int RightTopY, RightBottomY;
			tmpRightTop.x = (RightTop.x - 1) + velocity.x;
			tmpRightTop.y = (RightTop.y) + velocity.y;
			tmpRightBottom.x = RightBottom.x - 1 + velocity.x;
			tmpRightBottom.y = RightBottom.y - 1 + velocity.y;

			RightTopX = (int)(tmpRightTop.x / (MAP_SIZE));
			RightTopY = (int)(tmpRightTop.y / (MAP_SIZE));

			RightBottomX = (int)(tmpRightBottom.x / (MAP_SIZE));
			RightBottomY = (int)(tmpRightBottom.y / (MAP_SIZE));

			if ((map.map[RightTopY][RightTopX] == map.NEEDLE /*|| map.map[LeftTopY][LeftTopX] == map.NEEDLE*/) &&
				(map.map[RightBottomY][RightBottomX] == map.NEEDLE/* || map.map[LeftBottomY][LeftBottomX] == map.NEEDLE)*/)) {
				Init();
				/*LeftTop += velocity * slow;
				RightTop += velocity * slow;
				LeftBottom += velocity * slow;
				RightBottom += velocity * slow;*/
			}
			/*else {
				float num = (LeftBottomX + 1) * MAP_SIZE;
				LeftTop.x = num;
				RightTop.x = num + MAP_SIZE;
				LeftBottom.x = num;
				RightBottom.x = num + MAP_SIZE;
			}*/


			if ((map.map[RightTopY][RightTopX] == map.NONE || map.map[RightTopY][RightTopX] == map.TMPNONE ||
				map.map[RightTopY][RightTopX] == map.REDNONE || map.map[RightTopY][RightTopX] == map.GREENNONE ||
				map.map[RightTopY][RightTopX] == map.BLUENONE) &&
				(map.map[RightBottomY][RightBottomX] == map.NONE || map.map[RightBottomY][RightBottomX] == map.TMPNONE ||
					map.map[RightBottomY][RightBottomX] == map.REDNONE || map.map[RightBottomY][RightBottomX] == map.GREENNONE ||
					map.map[RightBottomY][RightBottomX] == map.BLUENONE)) {
				LeftTop += velocity * slow;
				RightTop += velocity * slow;
				LeftBottom += velocity * slow;
				RightBottom += velocity * slow;
			}
			else {
				float num = (RightBottomX - 1) * MAP_SIZE;
				LeftTop.x = num;
				RightTop.x = num + MAP_SIZE;
				LeftBottom.x = num;
				RightBottom.x = num + MAP_SIZE;
			}
		}
		if ((Key::IsPress(DIK_W) || Key::IsPress(DIK_SPACE)) && jumpFlag) {
			jumpFlag = false;
			gravityVector = { 0,-1 };
			gravityVelocity.y = gravityVector.y * jumpSpeed;
			////////////////////////当たり判定/////////////////////////
			Vec2 tmpLeftTop, tmpRightTop;
			int LeftTopX, RightTopX;
			int LeftTopY, RightTopY;
			tmpLeftTop = LeftTop + gravityVelocity;
			tmpRightTop.x = (RightTop.x - 1) + gravityVelocity.x;
			tmpRightTop.y = (RightTop.y) + gravityVelocity.y;

			LeftTopX = (int)(tmpLeftTop.x / (MAP_SIZE));
			LeftTopY = (int)(tmpLeftTop.y / (MAP_SIZE));

			RightTopX = (int)(tmpRightTop.x / (MAP_SIZE));
			RightTopY = (int)(tmpRightTop.y / (MAP_SIZE));

			if ((map.map[LeftTopY][LeftTopX] == map.NEEDLE /*|| map.map[LeftTopY][LeftTopX] == map.NEEDLE*/) &&
				(map.map[RightTopY][RightTopX] == map.NEEDLE/* || map.map[LeftBottomY][LeftBottomX] == map.NEEDLE)*/)) {
				Init();
				/*LeftTop += velocity * slow;
				RightTop += velocity * slow;
				LeftBottom += velocity * slow;
				RightBottom += velocity * slow;*/
			}
			/*else {
				float num = (LeftBottomX + 1) * MAP_SIZE;
				LeftTop.x = num;
				RightTop.x = num + MAP_SIZE;
				LeftBottom.x = num;
				RightBottom.x = num + MAP_SIZE;
			}*/

			if ((map.map[LeftTopY][LeftTopX] == map.NONE || map.map[LeftTopY][LeftTopX] == map.TMPNONE ||
				map.map[LeftTopY][LeftTopX] == map.REDNONE || map.map[LeftTopY][LeftTopX] == map.GREENNONE ||
				map.map[LeftTopY][LeftTopX] == map.BLUENONE) &&
				(map.map[RightTopY][RightTopX] == map.NONE || map.map[RightTopY][RightTopX] == map.TMPNONE ||
					map.map[RightTopY][RightTopX] == map.REDNONE || map.map[RightTopY][RightTopX] == map.GREENNONE ||
					map.map[RightTopY][RightTopX] == map.BLUENONE)) {
				LeftTop += gravityVelocity;
				RightTop += gravityVelocity;
				LeftBottom += gravityVelocity;
				RightBottom += gravityVelocity;
			}
			else {
				float num = (LeftTopY + 1) * MAP_SIZE;
				LeftTop.y = num;
				RightTop.y = num;
				LeftBottom.y = num + MAP_SIZE;
				RightBottom.y = num + MAP_SIZE;
			}

		}

	}

	{
		///*if (knockBackVelocity.x > 0) {
		//	knockBackVelocity.x -= 1;
		//}
		//if (knockBackVelocity.x < 0) {
		//	knockBackVelocity.x += 1;
		//}*/
		//knockBackVelocity.y += 1;


		//LeftTop += knockBackVelocity;
		//RightTop += knockBackVelocity;
		//LeftBottom += knockBackVelocity;
		//RightBottom += knockBackVelocity;
	}


	
	//重力
	{


		gravityVector = { 0,1 * slow };
		gravityVelocity += gravityVector * gravitySpeed ;
		

		////////////////////////当たり判定/////////////////////////
		Vec2 tmpLeftTop, tmpRightTop,tmpLeftBottom, tmpRightBottom;
		int LeftTopX, RightTopX,LeftBottomX, RightBottomX;
		int LeftTopY, RightTopY,LeftBottomY, RightBottomY;

		tmpLeftTop = LeftTop + gravityVelocity;
		tmpRightTop.x = (RightTop.x - 1) + gravityVelocity.x;
		tmpRightTop.y = (RightTop.y) + gravityVelocity.y;
		tmpLeftBottom.x = LeftBottom.x + gravityVelocity.x;
		tmpLeftBottom.y = (LeftBottom.y) + gravityVelocity.y;
		tmpRightBottom.x = RightBottom.x - 1 + gravityVelocity.x;
		tmpRightBottom.y = RightBottom.y  + gravityVelocity.y;

		LeftTopX = (int)(tmpLeftTop.x / (MAP_SIZE));
		LeftTopY = (int)(tmpLeftTop.y / (MAP_SIZE));

		RightTopX = (int)(tmpRightTop.x / (MAP_SIZE));
		RightTopY = (int)(tmpRightTop.y / (MAP_SIZE));

		LeftBottomX = (int)(tmpLeftBottom.x / (MAP_SIZE));
		LeftBottomY = (int)(tmpLeftBottom.y / (MAP_SIZE));

		RightBottomX = (int)(tmpRightBottom.x / (MAP_SIZE));
		RightBottomY = (int)(tmpRightBottom.y / (MAP_SIZE));

		if ((map.map[LeftTopY][LeftTopX] == map.NEEDLE /*|| map.map[LeftTopY][LeftTopX] == map.NEEDLE*/) &&
			(map.map[RightTopY][RightTopX] == map.NEEDLE/* || map.map[LeftBottomY][LeftBottomX] == map.NEEDLE)*/)) {
			Init();
			tmpLeftTop = LeftTop + gravityVelocity;
			tmpRightTop.x = (RightTop.x - 1) + gravityVelocity.x;
			tmpRightTop.y = (RightTop.y) + gravityVelocity.y;
			tmpLeftBottom.x = LeftBottom.x + gravityVelocity.x;
			tmpLeftBottom.y = (LeftBottom.y) + gravityVelocity.y;
			tmpRightBottom.x = RightBottom.x - 1 + gravityVelocity.x;
			tmpRightBottom.y = RightBottom.y + gravityVelocity.y;

			LeftTopX = (int)(tmpLeftTop.x / (MAP_SIZE));
			LeftTopY = (int)(tmpLeftTop.y / (MAP_SIZE));

			RightTopX = (int)(tmpRightTop.x / (MAP_SIZE));
			RightTopY = (int)(tmpRightTop.y / (MAP_SIZE));

			LeftBottomX = (int)(tmpLeftBottom.x / (MAP_SIZE));
			LeftBottomY = (int)(tmpLeftBottom.y / (MAP_SIZE));

			RightBottomX = (int)(tmpRightBottom.x / (MAP_SIZE));
			RightBottomY = (int)(tmpRightBottom.y / (MAP_SIZE));
			/*LeftTop += velocity * slow;
			RightTop += velocity * slow;
			LeftBottom += velocity * slow;
			RightBottom += velocity * slow;*/
		}
		if ((map.map[LeftBottomY][LeftBottomX] == map.NEEDLE /*|| map.map[LeftBottomY][LeftBottomX] == map.TMPNONE*/) &&
			(map.map[RightBottomY][RightBottomX] == map.NEEDLE /*|| map.map[RightBottomY][RightBottomX] == map.TMPNONE*/)) {
			Init();
			tmpLeftTop = LeftTop + gravityVelocity;
			tmpRightTop.x = (RightTop.x - 1) + gravityVelocity.x;
			tmpRightTop.y = (RightTop.y) + gravityVelocity.y;
			tmpLeftBottom.x = LeftBottom.x + gravityVelocity.x;
			tmpLeftBottom.y = (LeftBottom.y) + gravityVelocity.y;
			tmpRightBottom.x = RightBottom.x - 1 + gravityVelocity.x;
			tmpRightBottom.y = RightBottom.y + gravityVelocity.y;

			LeftTopX = (int)(tmpLeftTop.x / (MAP_SIZE));
			LeftTopY = (int)(tmpLeftTop.y / (MAP_SIZE));

			RightTopX = (int)(tmpRightTop.x / (MAP_SIZE));
			RightTopY = (int)(tmpRightTop.y / (MAP_SIZE));

			LeftBottomX = (int)(tmpLeftBottom.x / (MAP_SIZE));
			LeftBottomY = (int)(tmpLeftBottom.y / (MAP_SIZE));

			RightBottomX = (int)(tmpRightBottom.x / (MAP_SIZE));
			RightBottomY = (int)(tmpRightBottom.y / (MAP_SIZE));
		}
		/*else {
			float num = (LeftBottomX + 1) * MAP_SIZE;
			LeftTop.x = num;
			RightTop.x = num + MAP_SIZE;
			LeftBottom.x = num;
			RightBottom.x = num + MAP_SIZE;
		}*/


		if (!(map.map[LeftTopY][LeftTopX] == map.NONE || map.map[LeftTopY][LeftTopX] == map.TMPNONE ||
			map.map[LeftTopY][LeftTopX] == map.REDNONE || map.map[LeftTopY][LeftTopX] == map.GREENNONE ||
			map.map[LeftTopY][LeftTopX] == map.BLUENONE) ||
			!(map.map[RightTopY][RightTopX] == map.NONE || map.map[RightTopY][RightTopX] == map.TMPNONE ||
				map.map[RightTopY][RightTopX] == map.REDNONE || map.map[RightTopY][RightTopX] == map.GREENNONE ||
				map.map[RightTopY][RightTopX] == map.BLUENONE)) {
			float num = (LeftTopY+1) * MAP_SIZE;
			LeftTop.y = num;
			RightTop.y = num;
			LeftBottom.y = num + MAP_SIZE;
			RightBottom.y = num + MAP_SIZE;
			gravityVelocity = { 0,0 };
		}
		if ((map.map[LeftBottomY][LeftBottomX] == map.NONE || map.map[LeftBottomY][LeftBottomX] == map.TMPNONE ||
			map.map[LeftBottomY][LeftBottomX] == map.REDNONE || map.map[LeftBottomY][LeftBottomX] == map.GREENNONE ||
			map.map[LeftBottomY][LeftBottomX] == map.BLUENONE) &&
			(map.map[RightBottomY][RightBottomX] == map.NONE || map.map[RightBottomY][RightBottomX] == map.TMPNONE ||
				map.map[RightBottomY][RightBottomX] == map.REDNONE || map.map[RightBottomY][RightBottomX] == map.GREENNONE ||
				map.map[RightBottomY][RightBottomX] == map.BLUENONE)) {
			jumpFlag=false;
			LeftTop += gravityVelocity * slow;
			RightTop += gravityVelocity * slow;
			LeftBottom += gravityVelocity * slow;
			RightBottom += gravityVelocity * slow;
		}
		else {
			float num = (LeftTopY) * MAP_SIZE;
			LeftTop.y = num;
			RightTop.y = num;
			LeftBottom.y = num + MAP_SIZE;
			RightBottom.y = num + MAP_SIZE;
			gravityVelocity = { 0,0 };
			jumpFlag = true;
		}
	}

	

	prekey = key;
	key = 0;

	playerColQuad = { LeftTop ,RightTop ,LeftBottom ,RightBottom };

	Novice::ScreenPrintf(0, 400, "slow:%0.2f", slow);
}


void Player::Draw(float isColorReverse) {

	int BaseColorR = (RED & 0xFF000000) >> 24;
	int BaseColorG = (RED & 0x00FF0000) >> 16;
	int BaseColorB = (RED & 0x0000FF00) >> 8;

	BaseColorR = BaseColorR * isColorReverse + (255 - BaseColorR) * (1.0f - isColorReverse);
	BaseColorG = BaseColorG * isColorReverse + (255 - BaseColorG) * (1.0f - isColorReverse);
	BaseColorB = BaseColorB * isColorReverse + (255 - BaseColorB) * (1.0f - isColorReverse);

	int PlayerColor = (BaseColorR << 24) + (BaseColorG << 16) + (BaseColorB << 8) + 255;

	Novice::ScreenPrintf(200, 40, "gravityVelocity:%f", gravityVelocity.y);

	//ボムを投げている状態の時ボムを表示
	if (isAfterThrow == true) {
		Novice::DrawQuad(bombPosition.x - bombLength, bombPosition.y - bombLength,
			bombPosition.x + bombLength, bombPosition.y - bombLength,
			bombPosition.x - bombLength, bombPosition.y + bombLength,
			bombPosition.x + bombLength, bombPosition.y + bombLength,
			0, 0, 32, 32, bombTexture, 0xFFFFFFFF);
	}

	Novice::DrawQuad(LeftTop.x, LeftTop.y /**-1 + Mapchip::kWindowHeight*/, RightTop.x, RightTop.y /** -1 + Mapchip::kWindowHeight*/,LeftBottom.x, LeftBottom.y  /** -1 + Mapchip::kWindowHeight*/,RightBottom.x, RightBottom.y  /** -1 + Mapchip::kWindowHeight*/,0, 0, MAP_SIZE, MAP_SIZE, texture, PlayerColor);
}

void Player::hitCircle(Circle targetCircle,Vec2 knockBack, int Damage)
{
	if (Collision::CircleToQuad(targetCircle, playerColQuad)) {

		gravityVelocity = { 0,0 };

		gravityVelocity = knockBack;
	}
}
