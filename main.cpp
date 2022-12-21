#define _USE_MATH_DEFINES
#include <Novice.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "Player.h"
#include "Player2.h"
#include "TestEnemy.h"
#include "TestEnemy2.h"
#include "Key.h"
#include "Collision.h"
#include "Circle.h"
#include "Quad.h"
#include "ControllerInput.h"
#include "Candle.h"
#include "WindMill.h"
#include "Gate.h"
#include "TestEnemy04.h"

const char kWindowTitle[] = "map";

int ColorReverse(int basecolor);

float isColorReverse = 0;

enum DRAWTYPE {
	MAKE,
	ERASE
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	clock_t offset;
	offset = clock();
	int FPS = 0;

	int* pMouseX = 0;
	int* pMouseY = 0;

	int mouseX = 0;
	int mouseY = 0;

	int preMouseX = 0;
	int preMouseY = 0;
	bool preMousePush = false;

	int mouseSpeedX = 0;
	int mouseSpeedY = 0;

	int ellipseX = 300;
	int ellipseY = 300;
	int ellipseRadius = 50;

	int color = 0x000000FF;
	unsigned int backgroundColor = 0x9977AAFF;
	
	bool isHit = false;

	//スクロール値
	float scrollX = 0;

	int TILE = Novice::LoadTexture("./Resources/tile.png");
	int COLORTILE = Novice::LoadTexture("./Resources/colortile.png");
	int COLORNONE = Novice::LoadTexture("./Resources/colornone.png");
	int FRAMEBORDER = Novice::LoadTexture("./Resources/frameborder.png");

	bool isShowBorder = false;

	int slowTime = 0;
	const int kslowTimeMax = 120;
	bool canSlow = true;
	bool slowFlag = false;

	Vec2 expPos = { 640,360};
	float expRad = 128;
	Circle expCir = { expPos  , expRad };
	bool expFlag = false;

	DRAWTYPE drawType = MAKE;

	Map map;
	int Map = 0;

	enum {
		putBlockMode, // ブロック設置
		explodeMode,  // 爆破
		handMode //つかむとかたたくとか
	};

	int mouseActionMode = putBlockMode;


	FILE* fp = NULL;
	fopen_s(&fp, "./Resources/test.csv", "rt");
	if (fp == NULL) {
		return 0;
	}
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			fscanf_s(fp, "%d,", &map.map[y][x]);
		}
	}
	fclose(fp);

	fp = NULL;
	fopen_s(&fp, "./Resources/mapEasy.csv", "rt");
	if (fp == NULL) {
		return 0;
	}
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			fscanf_s(fp, "%d,", &map.map[y][x]);
		}
	}
	fclose(fp);

	for (int y = 0; y < 50; y++) {

		for (int x = 0; x < 50; x++) {

			map.blockColor[y][x] = 0xFFFFFFFF;

			//mapEasy.tmpTime[y][x] = 0;

			//mapEasy.blockColor[y][x] = 0xFFFFFFFF;
		}

	}

	bool isEdit = false;

	int setNumber = 0;

	//書き込み時の文字列、最大数はブロックの種類に依存。
	char string[kMaxBlock][4] = { 
		"10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
		"20", "21", "22", "23", "24"/*, "25", "26", "27", "28", "29"*/
	};

	
	map.blockCount = 25;
	//mapEasy.blockCount = 25;
	Player player;
	Player2 player2;

	//ギミック
	Candle candle(map);

	//const int kTestEnemy = 6;
	//TestEnemy testEnemy[kTestEnemy];
	////
	//testEnemy[0].Set({ 928.0f,32.0f });
	//testEnemy[1].Set({ 832.0f,32.0f });
	//testEnemy[2].Set({ 736.0f,32.0f });
	//testEnemy[3].Set({ 640.0f,32.0f });
	//testEnemy[4].Set({ 1120.0f,32.0f });
	//testEnemy[5].Set({ 1184.0f,32.0f });

	/*const int kTestEnemy2 = 2;
	TestEnemy2 testEnemy2[kTestEnemy2];
	testEnemy2[0].Set({ 32.0f,256.0f });
	testEnemy2[1].Set({ 32.0f,352.0f });*/
	float slow = 1.0f;

	Novice::SetMouseCursorVisibility(0);

	WindMill windMill;

	windMill.Set({ 1000,300 }, scrollX);

	Gate gate;

	gate.Set({ 1168,288}, { 32, 160 } , scrollX);

	TestEnemy04 TE4;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		Novice::GetMousePosition(pMouseX, pMouseY);

		//キー入力の受付
		Key::Update();

		//コントローラー入力の受付
		Controller::SetState();

		///
		/// ↓更新処理ここから
		///
		///俺も食いたかった！！！！ゴメンネ; ;
		///疲れた
		///学校だとふとんがいないから集中できないし、仮にこの世にふとんがいなかったら精神が崩壊してる。
		///ふとんがいてくれるから俺はがんばれる。

		if (Novice::GetWheel() < 0) {
			if (mouseActionMode < handMode) {
				mouseActionMode++;
			}
		}
		else if (Novice::GetWheel() > 0) {
			if (mouseActionMode > putBlockMode) {
				mouseActionMode--;
			}
		}

		expPos = { float(mouseX),float(mouseY) };
		expCir = { expPos  , expRad };

		if (expFlag == true) {

			float pow = 0.5;

			float expPowDistance = sqrtf((player.GetPlayerQuad().LeftTop.x + 32 - expPos.x) * (player.GetPlayerQuad().LeftTop.x + 32 - expPos.x) + (player.GetPlayerQuad().LeftTop.y + 32 - expPos.y) * (player.GetPlayerQuad().LeftTop.y + 32 - expPos.y));

			float ecpPowF = 1 - (expPowDistance / expRad);

			Vec2 PlayerPos = { player.GetPlayerQuad().LeftTop.x + 32 - expPos.x,
				player.GetPlayerQuad().LeftTop.y + 32 - expPos.y };

			Vec2 expPowVec =
			{ PlayerPos.x * ecpPowF * pow,
				PlayerPos.y * ecpPowF * pow };

			/*if (expPowVec.y < 0) {
				expPowVec.y = -pow - expPowVec.y;
			}
			else {
				expPowVec.y = pow - expPowVec.y;
			}

			if (expPowVec.x < 0) {
				expPowVec.x = -pow - expPowVec.x;
			}
			else {
				expPowVec.x = pow - expPowVec.x;
			}*/

			player.hitCircle(expCir, expPowVec, 0);
			Novice::ScreenPrintf(600, 200, "%0.2f", ecpPowF);
		}

		//if (keys[DIK_SPACE] != 0) {
		//	slowFlag = true;
		//}
		//else {
		//	slowFlag = false;
		//	/*if (preMousePush) {
		//		canSlow = false;
		//	}*/
		//}

		//if (slowFlag == true) {
		//	if (canSlow == true) {
		//		slowTime++;
		//		slow /= 1.1;
		//	}
		//	if (slowTime > kslowTimeMax) {
		//		canSlow = false;
		//	}
		//}

		//if (canSlow == false || slowFlag == false) {
		//	slow *= 1.1;
		//	if (slowTime > 0) {
		//		slowTime--;
		//	}
		//	else {
		//		canSlow = true;
		//	}
		//}
		
		if (keys[DIK_SPACE] != 0) {
			slow /= 1.1;
		}
		else {
			slow *= 1.1;
		}

		if (slow > 1.0) {
			slow = 1.0f;
		}

		if (slow < 0.2f) {
			slow = 0.2f;
		}

		isColorReverse = (slow - 0.2f) / 0.8f;

		if (Key::IsTrigger(DIK_Q)) {

			if (isShowBorder == false) {
				isShowBorder = true;
			}
			else {
				isShowBorder = false;
			}

		}

		
		/// 
		///マップ書き込み機能のフラグをオンにする
		///Eキーを押すと青のラインが出現する。出現している間はエディタ機能を使える
		///再度Eキーを押すと通常のゲームプレイに戻る
		/// 
		///デバッグ中の操作
		///矢印キーで配置するブロックの変更。数字毎のブロックの割り振りはMap.hのTILE参照
		///上キー...数字を一つ上げる
		///下キー...数字を一つ下げる
		///右キー...数字を十個上げる
		///左キー...数字を十個下げる
		///配置はマウスでなぞって配置できる
		/// 
		if (Key::IsTrigger(DIK_E)) {
			
			if (isEdit == false) {
				isEdit = true;
			}
			else {
				isEdit = false;
			}

		}

		Novice::ScreenPrintf(300,300,"%d", Map);

		if (Key::IsTrigger(DIK_R)) {

			player.Init();
			FILE* fp = NULL;

			switch (Map)
			{
			case 0:
				
				fopen_s(&fp, "./Resources/mapEasy.csv", "rt");
				
				break;
			case 1:

				fopen_s(&fp, "./Resources/test.csv", "rt");

				break;
			}

			if (fp == NULL) {
				return 0;
			}

			for (int y = 0; y < 50; y++) {
				for (int x = 0; x < 50; x++) {
					fscanf_s(fp, "%d,", &map.map[y][x]);
				}
			}

			fclose(fp);
			map.blockCount = 25;


			
		}


		if (isEdit == true) {

			//書き込む数字の設定
			if (setNumber < kMaxBlock - 1) {

				//一単位での切り替え
				if (Key::IsTrigger(DIK_UP)) {
					setNumber++;
				}

				//十単位での切り替え
				if (Key::IsTrigger(DIK_RIGHT)) {
					
					//最大数を超えなければそのまま加算
					if (setNumber + 10 < kMaxBlock - 1) {
						setNumber += 10;
					}
					//最大数を超えたら最大値に変換
					else {
						setNumber = kMaxBlock - 1;
					}

				}

			}

			if (setNumber > 0) {

				if (Key::IsTrigger(DIK_DOWN)) {
					setNumber--;
				}

				//十単位での切り替え
				if (Key::IsTrigger(DIK_LEFT)) {

					//最小値を超えなければそのまま減算
					if (setNumber - 10 > 0) {
						setNumber -= 10;
					}
					//最小値を超えたら最小値に変換
					else {
						setNumber = 0;
					}

				}

			}

		}

		pMouseX = &mouseX;
		pMouseY = &mouseY;

		mouseSpeedX = mouseX - preMouseX;
		mouseSpeedY = mouseY - preMouseY;

		if (Novice::IsPressMouse(0) == true) {
			color = 0xFF0000FF;
		}
		else {
			color = 0x000000FF;
			isHit = false;
		}

		int mouseYGrid = mouseY / MAP_SIZE;
		int mouseXGrid = (mouseX + scrollX) / MAP_SIZE;
		int premouseYGrid = preMouseY / MAP_SIZE;
		int premouseXGrid = (preMouseX + scrollX) / MAP_SIZE;
		int setMouseYGrid = premouseYGrid;
		int setMouseXGrid = premouseXGrid;

		if (isEdit == true) {

			if (Novice::IsPressMouse(0) == true) {

				FILE* fp = NULL;

				switch (Map)
				{
				case 0:

					fopen_s(&fp, "./Resources/mapEasy.csv", "r+b");

					break;
				case 1:

					fopen_s(&fp, "./Resources/test.csv", "r+b");

					break;
				}

				if (fp == NULL) {
					return 0;
				}

				fseek(fp, (setMouseYGrid * 152) + (setMouseXGrid * 3), SEEK_SET);

				fputs(string[setNumber], fp);

				fclose(fp);

				switch (Map)
				{
				case 0:

					fopen_s(&fp, "./Resources/mapEasy.csv", "rt");

					break;
				case 1:

					fopen_s(&fp, "./Resources/test.csv", "rt");

					break;
				}

				if (fp == NULL) {
					return 0;
				}

				for (int y = 0; y < 50; y++) {
					for (int x = 0; x < 50; x++) {
						fscanf_s(fp, "%d,", &map.map[y][x]);
					}
				}

				fclose(fp);
				map.blockCount = 25;

			}

		}


		//着色
		for (int y = 0; y < kMapBlockHeight; y++) {

			for (int x = 0; x < kMapBlockWidth; x++) {

				if (map.map[y][x] == map.REDNONE || map.map[y][x] == map.REDBLOCK) {
					map.blockColor[y][x] = 0xFF0000FF;
				}

				if (map.map[y][x] == map.GREENNONE || map.map[y][x] == map.GREENBLOCK) {
					map.blockColor[y][x] = 0x00FF00FF;
				}

				if (map.map[y][x] == map.BLUENONE || map.map[y][x] == map.BLUEBLOCK) {
					map.blockColor[y][x] = 0x0000FFFF;
				}

				if (map.map[y][x] == map.ICEBLOCK) {

					map.blockColor[y][x] = 0xAAAAFFFF;

					Circle a = { { static_cast<float>(player2.BombPos.x),static_cast<float>(player2.BombPos.y) }, static_cast<float>(player2.BombRad) };
					Quad b = { {static_cast<float>(x * MAP_SIZE),static_cast<float>(y * MAP_SIZE)},{static_cast<float>((x + 1) * MAP_SIZE - 1),static_cast<float>(y * MAP_SIZE)},{static_cast<float>(x * MAP_SIZE),static_cast<float>((y + 1) * MAP_SIZE - 1)},{static_cast<float>((x + 1) * MAP_SIZE - 1),static_cast<float>((y + 1) * MAP_SIZE - 1)} };
					///爆弾の範囲がスイッチと接触しているか
					if (Collision::CircleToQuad(a, b)) {
						map.map[y][x] = map.NONE;
					}

				}

			}

		}

		//エディット中邪魔なので動けないようにした
		if (isEdit == false) {
			player2.Update(slow,map, &scrollX, gate.GetGateQuad());
		}
	

		windMill.Hit(player2.GetBombCircle());
		windMill.Update(scrollX);

		gate.Update(scrollX, windMill.GetisCharged());
		
		TE4.HitBomb(player2.GetBombCircle());
		TE4.HitPlayer(player2.GetPlayerQuad(), player2.GetPlayerKnockbackVelocity());
		player2.HitTE4(TE4.GetCircle());
		TE4.Update(slow,scrollX, player2.GetPlayerPos());

		if (Key::IsTrigger(DIK_C)) {
			candle.isAlive = false;
		}
		candle.Update(map, player2);
		//testEnemy.Update(player, map, slow);

		preMouseX = mouseX;
		preMouseY = mouseY;
		preMousePush = Novice::IsPressMouse(0);

		if (Key::IsPress(DIK_R)) {
			/*if (Map == 1) {
				player.Init();
				FILE* fp = NULL;
				fopen_s(&fp, "./Resources/test.csv", "rt");
				if (fp == NULL) {
					return 0;
				}
				for (int y = 0; y < 50; y++) {
					for (int x = 0; x < 50; x++) {
						fscanf_s(fp, "%d,", &map.map[y][x]);
					}
				}
				fclose(fp);
			}
			else {
				player.Init();
				FILE* fp = NULL;
				fopen_s(&fp, "./Resources/mapEasy.csv", "rt");
				if (fp == NULL) {
					return 0;
				}
				for (int y = 0; y < 50; y++) {
					for (int x = 0; x < 50; x++) {
						fscanf_s(fp, "%d,", &map.map[y][x]);
					}
				}
				fclose(fp);
			}*/
		}

		if (Key::IsTrigger(DIK_M)) {
			for (int y = 0; y < 50; y++) {
				for (int x = 0; x < 50; x++) {
					map.blockNum[y][x] = 0;
					map.map[y][x] == map.NONE;
					map.blockCount = 25;
				}
			}
			//俺が変えたぜ
			player2.Init();
			FILE* fp = NULL;

			Map++;

			switch (Map)
			{
			case 0:

				fopen_s(&fp, "./Resources/mapEasy.csv", "rt");

				break;
			case 1:

				fopen_s(&fp, "./Resources/test.csv", "rt");

				TE4.Set({ 1000,100},scrollX);
				windMill.Delete();
				gate.Delete();
				break;
			
			default:

				fopen_s(&fp, "./Resources/mapEasy.csv", "rt");
				
				TE4.Delete();
				windMill.Set({ 1000,300 }, scrollX);
				gate.Set({ 1168,288 }, { 32, 160 }, scrollX);

				Map = 0;
				break;
			}

			if (fp == NULL) {
				return 0;
			}

			for (int y = 0; y < 50; y++) {
				for (int x = 0; x < 50; x++) {
					fscanf_s(fp, "%d,", &map.map[y][x]);
				}
			}

			fclose(fp);
			map.blockCount = 25;

			//if (Map == 0) {
			//	player.Init();
			//	FILE* fp = NULL;
			//	fopen_s(&fp, "./Resources/test.csv", "rt");
			//	if (fp == NULL) {
			//		return 0;
			//	}
			//	for (int y = 0; y < 50; y++) {
			//		for (int x = 0; x < 50; x++) {
			//			fscanf_s(fp, "%d,", &map.map[y][x]);
			//		}
			//	}
			//	fclose(fp);
			///*	testEnemy[0].Set({ 928.0f,32.0f });
			//	testEnemy[1].Set({ 832.0f,32.0f });
			//	testEnemy[2].Set({ 736.0f,32.0f });
			//	testEnemy[3].Set({ 640.0f,32.0f });
			//	testEnemy[4].Set({ 1120.0f,32.0f });
			//	testEnemy[5].Set({ 1184.0f,32.0f });
			//	testEnemy2[0].Set({ 32.0f,256.0f });
			//	testEnemy2[1].Set({ 32.0f,352.0f });*/
			//	Map = 1;
			//}
			//else {
			//	player.Init();
			//	FILE* fp = NULL;
			//	fopen_s(&fp, "./Resources/mapEasy.csv", "rt");
			//	if (fp == NULL) {
			//		return 0;
			//	}
			//	for (int y = 0; y < 50; y++) {
			//		for (int x = 0; x < 50; x++) {
			//			fscanf_s(fp, "%d,", &map.map[y][x]);
			//		}
			//	}
			//	fclose(fp);
			//	Map = 0;
			//}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//もの運び
		/*Novice::DrawEllipse(ellipseX, ellipseY, ellipseRadius, ellipseRadius, 0.0f, 0xFFFFFFFF, kFillModeSolid);*/

		
		//if (Map == 1) {

		//背景
		//Novice::DrawQuad(0, 0, 1280, 0, 0, 720, 1280, 720, 0, 0, 1, 1, 0, 0x9977AAFF);
		Novice::DrawBox(0, 0, 1280, 720, 0, ColorReverse(backgroundColor), kFillModeSolid);

			for (int y = 0; y < 50; y++) {

				for (int x = 0; x < 50; x++) {

					if (map.map[y][x] == map.BREAKBLOCK || map.map[y][x] == map.CANTBLOCK || map.map[y][x] == map.TMPBLOCK || map.map[y][x] == map.NEEDLE) {

						Novice::DrawQuad(x * MAP_SIZE - scrollX, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE - scrollX, y * MAP_SIZE,
							x * MAP_SIZE - scrollX, y * MAP_SIZE + MAP_SIZE, x * MAP_SIZE + MAP_SIZE - scrollX, y * MAP_SIZE + MAP_SIZE,
							0, 0, 32, 32, TILE, map.blockColor[y][x]);

					}

					if (map.map[y][x] == map.REDNONE || map.map[y][x] == map.GREENNONE || map.map[y][x] == map.BLUENONE) {

						Novice::DrawQuad(x* MAP_SIZE - scrollX, y* MAP_SIZE, x* MAP_SIZE + MAP_SIZE - scrollX, y* MAP_SIZE,
							x* MAP_SIZE - scrollX, y* MAP_SIZE + MAP_SIZE, x* MAP_SIZE + MAP_SIZE - scrollX, y* MAP_SIZE + MAP_SIZE,
							0, 0, 32, 32, COLORNONE, map.blockColor[y][x]);

					}

					if (map.map[y][x] == map.REDBLOCK || map.map[y][x] == map.GREENBLOCK || map.map[y][x] == map.BLUEBLOCK ||
						map.map[y][x] == map.CANDLE_SWHITCH || map.map[y][x] == map.CANDLE_BLOCK || map.map[y][x] == map.ICEBLOCK) {

						Novice::DrawQuad(x* MAP_SIZE - scrollX, y* MAP_SIZE, x* MAP_SIZE + MAP_SIZE - scrollX, y* MAP_SIZE,
							x* MAP_SIZE - scrollX, y* MAP_SIZE + MAP_SIZE, x* MAP_SIZE + MAP_SIZE - scrollX, y* MAP_SIZE + MAP_SIZE,
							0, 0, 32, 32, COLORTILE, map.blockColor[y][x]);

					}

				}

			}

			if (isShowBorder == true) {
				Novice::DrawQuad(0 - scrollX, 0, 1280 - scrollX, 0, 0 - scrollX, 720, 1280 - scrollX, 720, 0, 0, 1280, 720, FRAMEBORDER, 0x00AA0088);
				Novice::DrawQuad(1280 - scrollX, 0, 2560 - scrollX, 0, 1280 - scrollX, 720, 2560 - scrollX, 720, 0, 0, 1280, 720, FRAMEBORDER, 0x00AA0088);
			}

			if (isEdit == true) {
				Novice::DrawQuad(0 - scrollX, 0, 1280 - scrollX, 0, 0 - scrollX, 720, 1280 - scrollX, 720, 0, 0, 1280, 720, FRAMEBORDER, 0x0000FF88);
				Novice::DrawQuad(1280 - scrollX, 0, 2560 - scrollX, 0, 1280 - scrollX, 720, 2560 - scrollX, 720, 0, 0, 1280, 720, FRAMEBORDER, 0x0000FF88);
			}

		//}
		/*else {
			for (int y = 0; y < 50; y++) {

				for (int x = 0; x < 50; x++) {

					if (mapEasy.map[y][x] == mapEasy.BLOCK || mapEasy.map[y][x] == mapEasy.CANTBLOCK || mapEasy.map[y][x] == mapEasy.TMPBLOCK) {

						Novice::DrawQuad(x * MAP_SIZE, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE,
							x * MAP_SIZE, y * MAP_SIZE + MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE + MAP_SIZE,
							0, 0, 32, 32, TILE, mapEasy.blockColor[y][x]);

					}

				}

			}
		}*/

	
		

		

		//Novice::DrawBox(20, 700, 10 * (kslowTimeMax - slowTime), 10, 0, GREEN, kFillModeSolid);
		//Novice::DrawBox(20, 680, 40 * map.blockCount, 10, 0, GREEN, kFillModeSolid);

		//player.Draw(isColorReverse);
		if (Map == 1) {
			/*for (int i = 0; i < kTestEnemy2; i++) {
				testEnemy2[i].Draw();
			}
			for (int i = 0; i < kTestEnemy; i++) {
				testEnemy[i].Draw();
			}*/
		}

		switch (mouseActionMode)
		{
		case putBlockMode:
			Novice::DrawBox(1280, 0, -64, 64, 0, RED, kFillModeSolid);
			Novice::DrawBox(mouseX - 10, mouseY - 10, 20, 20, 0.0f, color, kFillModeSolid);
			break;
		case explodeMode:
			Novice::DrawBox(1280, 0, -64, 64, 0, GREEN, kFillModeSolid);
			
			for (int y = 0; y < 50; y++) {
				for (int x = 0; x < 50; x++) {
					if (y == mouseYGrid && x == mouseXGrid) {
							for (int i = -1; i < 2; i++) {
								for (int j = -1; j < 2; j++) {
									Novice::DrawBox((x - j) * 32, (y - i) * 32, 32, 32, 0, 0xFF0000EE, kFillModeWireFrame);
								}
							}

							for (int i = -2; i < 3; i += 4) {
								Novice::DrawBox((x - i) * 32, (y) * 32, 32, 32, 0, 0xFF0000EE, kFillModeWireFrame);
							}

							for (int i = -2; i < 3; i += 4) {
								Novice::DrawBox((x) * 32, (y - i) * 32, 32, 32, 0, 0xFF0000EE, kFillModeWireFrame);
							}
					}
				}
			}
			
			Novice::DrawEllipse(expPos.x, expPos.y, expRad, expRad, 0, GREEN, kFillModeWireFrame);
			Novice::DrawEllipse(mouseX, mouseY, 20, 20, 0.0f, color, kFillModeSolid);
			
			break;
		case handMode:
			Novice::DrawBox(1280, 0, -64, 64, 0, 0xFFFF00FF, kFillModeSolid);
			break;
		}

		windMill.Draw();

		gate.Draw();

		TE4.Draw();

		player2.Draw(&scrollX);

		Novice::ScreenPrintf(60, 200, "%d", slowTime); 
		Novice::ScreenPrintf(10, 70, "ENERGY : %d", map.blockCount);
		Novice::ScreenPrintf(10, 50, "W or SPACE to Jump");
		Novice::ScreenPrintf(10, 30, "A : Left Move D : Right Move");
		Novice::ScreenPrintf(10, 10, "Left Click to Make Block");

		//デバッグ機能、現在置こうとしているマップチップのナンバー表示
		if (isEdit == true) {

			Novice::DrawBox(990, 690, 200, 30, 0.0f, 0x000000AA, kFillModeSolid);
			Novice::ScreenPrintf(1000, 700, "setNumber : %d", setNumber + 10);

		}

		/*Novice::ScreenPrintf(10, 200, "slow:%f", slow);*/

		
		if (expFlag == true) {
			//Novice::DrawBox(0, 0, 1280, 64, 0, 0xFFFF00FF, kFillModeSolid);
			Novice::DrawEllipse(expPos.x, expPos.y, expRad, expRad, 0, GREEN, kFillModeSolid);
		}

		Novice::DrawBox(0, 480, 100, 40, 0, BLACK, kFillModeSolid);
		Novice::ScreenPrintf(0, 500, "FPS:%0.1f", 1.0f / ((double)(clock() - offset) / CLOCKS_PER_SEC));
		offset = clock();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

int ColorReverse(int basecolor)
{
	int BaseColorR = (basecolor & 0xFF000000) >> 24;
	int BaseColorG = (basecolor & 0x00FF0000) >> 16;
	int BaseColorB = (basecolor & 0x0000FF00) >> 8;

	BaseColorR = BaseColorR * isColorReverse + (255 - BaseColorR) * (1.0f - isColorReverse);
	BaseColorG = BaseColorG * isColorReverse + (255 - BaseColorG) * (1.0f - isColorReverse);
	BaseColorB = BaseColorB * isColorReverse + (255 - BaseColorB) * (1.0f - isColorReverse);

	return (BaseColorR << 24) + (BaseColorG << 16) + (BaseColorB << 8) + 255;
}
