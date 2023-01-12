#include "Player2.h"
#include "ControllerInput.h"
#include "Collision.h"
#include <Novice.h>

Player2::Player2()
{
	position = { 64,600 };
	nextPosition = { 64,600 };
	moveVector = { 0,0 };
	size = { 32,32};
	playerColQuad = { position , int(size.x),int(size.y)};
	nextPlayerColQuad = playerColQuad;
	speed = 5.0f;
	
	BombPos = { 9999,9999 };
	BombRad = 0;
	BombCircle = {BombPos,BombRad};

	BombPosMisal = 16;

	overHeatGage = 0;
	maxOverHeatGage = 300;
	coolTimeGage = 0;

	canJump = true;

	isCharge = false;
	chargeTime = 0;
	chargeMag = 1;
	isBigExp = false;
	isHeat = 0;
	color = 0xFFFFFFFF;

}

void Player2::Init()
{
	position = { 64,600 };
	nextPosition = { 64,600 };
	moveVector = { 0,0 };
	size = { 32,32 };
	playerColQuad = { position , int(size.x),int(size.y) };
	nextPlayerColQuad = playerColQuad;
	speed = 5.0f;

	BombPos = { 9999,9999 };
	BombRad = 0;
	BombCircle = { BombPos,BombRad };

	BombPosMisal = 16;

	overHeatGage = 0;
	maxOverHeatGage = 300;
	coolTimeGage = 0;

	canJump = true;

	isCharge = false;
	chargeTime = 0;
	chargeMag = 1;
	isBigExp = false;
	isHeat = 0;
	color = 0xFFFFFFFF;

}

void Player2::Charge() {

	if (Controller::IsTriggerButton(0, Controller::rTrigger) || (keys[DIK_G] && preKeys[DIK_G] == 0)) {

		//チャージしていないとき且つチャージ後でないとき
		if (isCharge == false && chargeTime != 120) {
			isCharge = true;
		}

	}

	//チャージフラグが立ったらカウント開始
	if (isCharge == true) {

		chargeTime++;

		if (chargeTime == 120) {
			isCharge = false;
		}

	}

}

void Player2::Update(float slow, Map& map, float* scrollX, Quad GateQuad)
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	moveVector.x = 0;
	//moveVector.y = 0;

	float minusSpeed = 0.5f;

	if (knockBackVelocity.x > 0) {
		knockBackVelocity.x -= minusSpeed * slow;
	}
	if (knockBackVelocity.x < 0) {
		knockBackVelocity.x += minusSpeed * slow;
	}

	if (knockBackVelocity.x <= minusSpeed * slow && knockBackVelocity.x >= -minusSpeed * slow) {
		knockBackVelocity.x = 0;
	}

	if (isHeat > 0) {
		isHeat--;
		color = 0xFF0000FF;
	}
	else {
		color = 0xFFFFFFFF;
	}

	Novice::GetAnalogInputLeft(0, &stickPositionX, &stickPositionY);

	if (((keys[DIK_W] && preKeys[DIK_W] == 0) || Controller::IsTriggerButton(0, Controller::bA) == 1) && canJump == true) {
		moveVector.y -= 13;
		canJump = false;
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
	else {
		BombPos = { 9999,9999};
	}

	Novice::GetAnalogInputRight(0, &bombStickPositionX, &bombStickPositionY);
	
	Charge();

	//クールタイム
	if (coolTimeGage > 0) {
		coolTimeGage--;

		//ゼロになったらオーバーヒートゲージをリセット
		if (coolTimeGage == 0) {
			overHeatGage = 0;
		}

	}

	//クールタイムに入っていなければ少しずつオーバーヒートゲージを下げる
	if (coolTimeGage == 0) {

		if (overHeatGage > 0) {
			overHeatGage--;
		}

	}
	
	//オーバーヒートゲージが満タンでない時爆発可能
	if (overHeatGage < maxOverHeatGage) {

		if ((fabs(bombStickPositionX) - fabs(preBombStickPositionX) > 10000 ||
			fabs(bombStickPositionY) - fabs(preBombStickPositionY) > 10000) &&
			isCharge == false) {
			bombVelocity.x = (cosf((bombStickPositionX - pow(2, 15)) * M_PI / powf(2, 16)) * 5.0f);
			bombVelocity.y = sinf(bombStickPositionY * M_PI / powf(2, 16)) * 5.0f;

			moveVector.y = 0;
			isHeat = 30;

			//チャージされていたら飛距離を伸ばし、チャージリセット
			if (chargeTime == 120) {
				chargeMag = 1.5f;
				MAXEXPSIZE = 128;
				chargeTime = 0;
				isBigExp = true;
			}
			else {
				chargeMag = 1;
				MAXEXPSIZE = 96;
				isBigExp = false;
			}

			//爆発ゲージを加算
			overHeatGage += 20;

			//ゲージが最大値に収まるよう調整
			if (overHeatGage > maxOverHeatGage) {
				overHeatGage = maxOverHeatGage;
			}

			knockBackVelocity = { -bombVelocity.x * 3 * chargeMag ,  -bombVelocity.y * 3 * chargeMag };

			BombPos = { position.x + bombVelocity.x * BombPosMisal , position.y + bombVelocity.y * BombPosMisal };
			BombRad = MAXEXPSIZE;
			canJump = false;
		}

		//上下左右キーでばくはつ(コントローラー繋ぐのめんどい時よう)
		{
			if (keys[DIK_RIGHT] != 0 && preKeys[DIK_RIGHT] == 0 && isCharge == false) {
				bombVelocity.x = (cosf((32768 - pow(2, 15)) * M_PI / powf(2, 16)) * 5.0f);
				bombVelocity.y = sinf(0 * M_PI / powf(2, 16)) * 5.0f;

				moveVector.y = 0;
				isHeat = 30;

				//チャージされていたら飛距離を伸ばす
				if (chargeTime == 120) {
					chargeMag = 1.5f;
					chargeTime = 0;
					MAXEXPSIZE = 128;
					isBigExp = true;
				}
				else {
					chargeMag = 1;
					MAXEXPSIZE = 96;
					isBigExp = false;
				}

				//爆発ゲージを加算
				overHeatGage += 30;

				//ゲージが最大値に収まるよう調整
				if (overHeatGage > maxOverHeatGage) {
					overHeatGage = maxOverHeatGage;
				}

				knockBackVelocity = { -bombVelocity.x * 3 * chargeMag ,  -bombVelocity.y * 3 * chargeMag };

			BombPos = { position.x + bombVelocity.x * BombPosMisal , position.y + bombVelocity.y * BombPosMisal };
			BombRad = MAXEXPSIZE;
			canJump = false;
		}

			if (keys[DIK_LEFT] != 0 && preKeys[DIK_LEFT] == 0 && isCharge == false) {
				bombVelocity.x = (cosf((-32768 - pow(2, 15)) * M_PI / powf(2, 16)) * 5.0f);
				bombVelocity.y = sinf(0 * M_PI / powf(2, 16)) * 5.0f;

				moveVector.y = 0;
				isHeat = 30;

				//チャージされていたら飛距離を伸ばす
				if (chargeTime == 120) {
					chargeMag = 1.5f;
					chargeTime = 0;
					MAXEXPSIZE = 128;
					isBigExp = true;
				}
				else {
					chargeMag = 1;
					MAXEXPSIZE = 96;
					isBigExp = false;
				}

				//爆発ゲージを加算
				overHeatGage += 30;

				//ゲージが最大値に収まるよう調整
				if (overHeatGage > maxOverHeatGage) {
					overHeatGage = maxOverHeatGage;
				}

				knockBackVelocity = { -bombVelocity.x * 3 * chargeMag ,  -bombVelocity.y * 3 * chargeMag };

			BombPos = { position.x + bombVelocity.x * BombPosMisal, position.y + bombVelocity.y * BombPosMisal };
			BombRad = MAXEXPSIZE;
			canJump = false;
		}

			if (keys[DIK_UP] != 0 && preKeys[DIK_UP] == 0 && isCharge == false) {
				bombVelocity.x = (cosf((0 - pow(2, 15)) * M_PI / powf(2, 16)) * 5.0f);
				bombVelocity.y = sinf(-32768 * M_PI / powf(2, 16)) * 5.0f;

				moveVector.y = 0;
				isHeat = 30;

				//チャージされていたら飛距離を伸ばす
				if (chargeTime == 120) {
					chargeMag = 1.5f;
					chargeTime = 0;
					MAXEXPSIZE = 128;
					isBigExp = true;
				}
				else {
					chargeMag = 1;
					MAXEXPSIZE = 96;
					isBigExp = false;
				}

				//爆発ゲージを加算
				overHeatGage += 30;

				//ゲージが最大値に収まるよう調整
				if (overHeatGage > maxOverHeatGage) {
					overHeatGage = maxOverHeatGage;
				}

				knockBackVelocity = { -bombVelocity.x * 3 * chargeMag ,  -bombVelocity.y * 3 * chargeMag };

			BombPos = { position.x + bombVelocity.x * BombPosMisal, position.y + bombVelocity.y * BombPosMisal };
			BombRad = MAXEXPSIZE;
			canJump = false;
		}

			if (keys[DIK_DOWN] != 0 && preKeys[DIK_DOWN] == 0 && isCharge == false) {
				bombVelocity.x = (cosf((0 - pow(2, 15)) * M_PI / powf(2, 16)) * 5.0f);
				bombVelocity.y = sinf(32768 * M_PI / powf(2, 16)) * 5.0f;

				moveVector.y = 0;
				isHeat = 30;

				//チャージされていたら飛距離を伸ばす
				if (chargeTime == 120) {
					chargeMag = 1.5f;
					chargeTime = 0;
					MAXEXPSIZE = 128;
					isBigExp = true;
				}
				else {
					chargeMag = 1;
					MAXEXPSIZE = 96;
					isBigExp = false;
				}

				//爆発ゲージを加算
				overHeatGage += 30;

				//ゲージが最大値に収まるよう調整
				if (overHeatGage > maxOverHeatGage) {
					overHeatGage = maxOverHeatGage;
				}

				knockBackVelocity = { -bombVelocity.x * 3 * chargeMag ,  -bombVelocity.y * 3 * chargeMag };

			BombPos = { position.x + bombVelocity.x * BombPosMisal, position.y + bombVelocity.y * BombPosMisal };
			BombRad = MAXEXPSIZE;
			canJump = false;
		}

		}

	}

	//クールタイムが0でオーバーヒートした場合、クールタイムを設定
	if (overHeatGage == maxOverHeatGage && coolTimeGage == 0) {

		//クールタイムを設定
		coolTimeGage = 180;

	}

	//チャージ中なら速度を下げる
	if (isCharge == true) {
		moveVector.x /= 2;

	}

	BombCircle = { BombPos,BombRad };

	preBombStickPositionX = bombStickPositionX;
	preBombStickPositionY = bombStickPositionY;

	moveVector.y += G * Weight * slow;

	nextPosition.x = position.x + (moveVector.x + knockBackVelocity.x) * slow;
	nextPosition.y = position.y + (moveVector.y + knockBackVelocity.y) * slow;

	nextPlayerColQuad = { {nextPosition.x ,nextPosition.y}, int(size.x), int(size.y) };

	if (Collision::QuadToQuad(nextPlayerColQuad, GateQuad)) {
		moveVector.x = 0;
		*scrollX -= knockBackVelocity.x;

		if (position.x < GateQuad.GetCenter().x) {
			nextPosition.x = GateQuad.LeftTop.x - size.x / 2;
		}
		else {
			nextPosition.x = GateQuad.RightTop.x + size.x / 2;
		}

	}

	//当たり判定
	{
		GridInit();


		if (map.map[UpGrid][LeftGrid] == map.NEEDLE ||
			map.map[UpGrid][RightGrid] == map.NEEDLE ||
			map.map[DownGrid][LeftGrid] == map.NEEDLE ||
			map.map[DownGrid][RightGrid] == map.NEEDLE) {
			Init();
			GridInit();
			map.isHitNeedle = true;
		}

		if (map.map[UpGrid][LeftGrid] == map.ICE_BLOCK ||
			map.map[UpGrid][RightGrid] == map.ICE_BLOCK ||
			map.map[DownGrid][LeftGrid] == map.ICE_BLOCK ||
			map.map[DownGrid][RightGrid] == map.ICE_BLOCK) {
			
			if (isHeat > 0) {
				
				if (map.map[UpGrid][LeftGrid] == map.ICE_BLOCK) {
					map.map[UpGrid][LeftGrid] = map.NONE;
				}

				if (map.map[UpGrid][RightGrid] == map.ICE_BLOCK) {
					map.map[UpGrid][RightGrid] = map.NONE;
				}

				if (map.map[DownGrid][LeftGrid] == map.ICE_BLOCK) {
					map.map[DownGrid][LeftGrid] = map.NONE;
				}

				if (map.map[DownGrid][RightGrid] == map.ICE_BLOCK) {
					map.map[DownGrid][RightGrid] = map.NONE;
				}

			}

		}

		if (position.y - nextPosition.y < 0) {
			if (map.AnyNone(map.map[UpGrid][RightGrid]) == false) {
				moveVector.x = 0;
				//スクロール値調整
				*scrollX -= knockBackVelocity.x;
				nextPosition.x = RightGrid * MAP_SIZE - size.x / 2;
				GridInit();
			}

			if (map.AnyNone(map.map[UpGrid][LeftGrid]) == false) {
				moveVector.x = 0;
				//スクロール値調整
				*scrollX -= knockBackVelocity.x;
				nextPosition.x = (LeftGrid + 1) * MAP_SIZE + size.x / 2;
				GridInit();
			}
		}
		else {
			if (map.AnyNone(map.map[DownGrid][RightGrid]) == false) {
				moveVector.x = 0;
				//スクロール値調整
				*scrollX -= knockBackVelocity.x;
				nextPosition.x = RightGrid * MAP_SIZE - size.x / 2;
				GridInit();
			}

			if (map.AnyNone(map.map[DownGrid][LeftGrid]) == false) {
				moveVector.x = 0;
				//スクロール値調整
				*scrollX -= knockBackVelocity.x;
				nextPosition.x = (LeftGrid + 1) * MAP_SIZE + size.x / 2;
				GridInit();
			}
		}



		if (map.AnyNone(map.map[UpGrid][RightGrid]) == false) {
			if (map.AnyNone(map.map[UpGrid][PosXGrid]) == true) {


				if (Right > RightGrid * MAP_SIZE && position.y - nextPosition.y < 0) {
					moveVector.x = 0;
					//スクロール値調整
					*scrollX -= knockBackVelocity.x;
					nextPosition.x = RightGrid * MAP_SIZE - size.x / 2;
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

		if (map.AnyNone(map.map[UpGrid][LeftGrid]) == false) {
			if (map.AnyNone(map.map[UpGrid][PosXGrid]) == true) {


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

		if (map.AnyNone(map.map[DownGrid][RightGrid]) == false) {
			if (map.AnyNone(map.map[DownGrid][PosXGrid]) == true) {
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
						canJump = true;
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



		else if (map.AnyNone(map.map[DownGrid][LeftGrid]) == false) {
			if (map.AnyNone(map.map[DownGrid][PosXGrid]) == true) {
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
						canJump = true;
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

		//Novice::ScreenPrintf(400, 420, "%0.2f", position.y + size.y / 2);
		//Novice::ScreenPrintf(400, 440, "%d", (DownGrid)*MAP_SIZE);

		if (map.AnyNone(map.map[UpGrid][PosXGrid]) == false) {
			moveVector.y = 1;
			knockBackVelocity.y = 0;
			nextPosition.y = (UpGrid + 1) * MAP_SIZE + size.y / 2;
			GridInit();
		}

		if (map.AnyNone(map.map[DownGrid][PosXGrid]) == false) {
			moveVector.y = 0;
			knockBackVelocity.y = 0;
			canJump = true;
			nextPosition.y = DownGrid * MAP_SIZE - size.y / 2;
			GridInit();
		}

	}

	

	position.x = nextPosition.x;
	position.y = nextPosition.y;

	//スクロール
	if (position.x > MAP_SIZE * 20 && position.x < MAP_SIZE * (kMapBlockWidth - 20)) {
		*scrollX +=( moveVector.x + knockBackVelocity.x) * slow;
	}
	else {

		if (position.x <= MAP_SIZE * 20) {
			*scrollX = 0;
		}

		if (position.x >= MAP_SIZE * (kMapBlockWidth - 20)) {
			*scrollX = MAP_SIZE * (kMapBlockWidth - 40);
		}

	}

	playerColQuad = { position , int(size.x),int(size.y) };

}

void Player2::HitTE4(Circle TargetCirle)
{
	if (Collision::CircleToQuad(TargetCirle,playerColQuad)) {
		knockBackVelocity.x *= -1;
		knockBackVelocity.y *= -1;
	}
}

void Player2::Draw(float* scrollX)
{

	//オーバーヒートゲージ
	Novice::DrawQuad(
		position.x - size.x / 2 - *scrollX, position.y - size.y / 2 - 20,
		position.x - size.x / 2 + (overHeatGage * 32 / maxOverHeatGage) - *scrollX, position.y - size.y / 2 - 20,
		position.x - size.x / 2 - *scrollX, position.y + size.y / 2 - 47,
		position.x - size.x / 2 + (overHeatGage * 32 / maxOverHeatGage) - *scrollX, position.y + size.y / 2 - 47,
		0, 0,
		size.x, size.y,
		0, RED
	);

	Novice::DrawBox(position.x - size.x / 2 - *scrollX, position.y - size.y / 2 - 20, 32, 5, 0.0f, RED, kFillModeWireFrame);

	//クールタイムゲージ

	Novice::DrawQuad(
		position.x - size.x / 2 - *scrollX, position.y - size.y / 2 - 10,
		position.x - size.x / 2 + (coolTimeGage * 32 / 180) - *scrollX, position.y - size.y / 2 - 10,
		position.x - size.x / 2 - *scrollX, position.y + size.y / 2 - 37,
		position.x - size.x / 2 + (coolTimeGage * 32 / 180) - *scrollX, position.y + size.y / 2 - 37,
		0, 0,
		size.x, size.y,
		0, BLUE
	);

	Novice::DrawBox(position.x - size.x / 2 - *scrollX, position.y - size.y / 2 - 10, 32, 5, 0.0f, BLUE, kFillModeWireFrame);

	Novice::DrawQuad(
		position.x - size.x / 2 - *scrollX, position.y - size.y / 2,
		position.x + size.x / 2 - *scrollX, position.y - size.y / 2,
		position.x - size.x / 2 - *scrollX, position.y + size.y / 2,
		position.x + size.x / 2 - *scrollX, position.y + size.y / 2,
		0, 0,
		size.x, size.y,
		0, color
	);
//	Novice::DrawEllipse(Left, nextPosition.y, 3, 3, 0, RED, kFillModeSolid);
//	Novice::DrawEllipse(Right, nextPosition.y, 3, 3, 0, RED, kFillModeSolid);
	//Novice::DrawEllipse(nextPosition.x, Up, 3, 3, 0, RErD, kFillModeSolid);
	//Novice::DrawEllipse(nextPosition.x, Down, 3, 3, 0, RED, kFillModeSolid);
	/*Novice::DrawEllipse(LeftGrid * MAP_SIZE + MAP_SIZE / 2 - *scrollX, (DownGrid + 1) * MAP_SIZE, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(RightGrid * MAP_SIZE + MAP_SIZE / 2 - *scrollX, nextPosition.y, 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(nextPosition.x - *scrollX, UpGrid * MAP_SIZE , 3, 3, 0, BLUE, kFillModeSolid);
	Novice::DrawEllipse(nextPosition.x - *scrollX, (DownGrid + 1) * MAP_SIZE , 3, 3, 0, BLUE, kFillModeSolid);*/

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
