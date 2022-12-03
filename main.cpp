#define _USE_MATH_DEFINES
#include <Novice.h>
#include <math.h>
#include <stdio.h>
#include "Player.h"
#include "TestEnemy.h"
#include "TestEnemy2.h"
#include "Key.h"

const char kWindowTitle[] = "LC1A_21_ヒワタシミチヤ";

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

	int* pMouseX = 0;
	int* pMouseY = 0;

	int mouseX = 0;
	int mouseY = 0;

	int preMouseX = 0;
	int preMouseY = 0;

	int mouseSpeedX = 0;
	int mouseSpeedY = 0;

	int ellipseX = 300;
	int ellipseY = 300;
	int ellipseRadius = 50;

	int color = 0x000000FF;
	unsigned int backgroundColor = 0xFF88FFFF;
	

	bool isHit = false;

	int TILE = Novice::LoadTexture("./Resources/tile.png");

	int slowTime = 0;
	bool canSlow = true;
	bool slowFlag = false;

	DRAWTYPE drawType = MAKE;

	Map map;

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

	for (int y = 0; y < 50; y++) {

		for (int x = 0; x < 50; x++) {
			/*map.map[y][x] = map.NONE;

			if (y == 20) {
				map.map[y][x] = map.BLOCK;
			}*/

			map.tmpTime[y][x] = 0;

			map.blockColor[y][x] = 0xFFFFFFFF;
		}

	}

	map.blockCount = 25;

	Player player;

	const int kTestEnemy = 6;
	TestEnemy testEnemy[kTestEnemy];

	testEnemy[0].Set({ 928.0f,32.0f });
	testEnemy[1].Set({ 832.0f,32.0f });
	testEnemy[2].Set({ 736.0f,32.0f });
	testEnemy[3].Set({ 640.0f,32.0f });
	testEnemy[4].Set({ 1120.0f,32.0f });
	testEnemy[5].Set({ 1184.0f,32.0f });

	const int kTestEnemy2 = 2;
	TestEnemy2 testEnemy2[kTestEnemy2];
	testEnemy2[0].Set({ 32.0f,256.0f });
	testEnemy2[1].Set({ 32.0f,352.0f });
	float slow = 1.0f;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		Novice::GetMousePosition(pMouseX, pMouseY);

		Key::Update();

		///
		/// ↓更新処理ここから
		///
		///俺も食いたかった！！！！ゴメンネ; ;
		
		if (( Novice::IsPressMouse(0))) {
			slowFlag = true;
		}
		else {
			slowFlag = false;
		}

		if (slowFlag == true) {
			if (canSlow == true) {
				slowTime++;
				slow /= 1.1;
			}
			if (slowTime > 60) {
				canSlow = false;
			}
		}

		if (canSlow == false || slowFlag == false) {
			slow *= 1.1;
			if (slowTime > 0) {
				slowTime--;
			}
			else {
				canSlow = true;
			}
		}
		

		if (slow > 1.0) {
			slow = 1.0f;
		}

		if (slow < 0.2f) {
			slow = 0.2f;
		}

		isColorReverse = (slow - 0.2f) / 0.8f;


		if (Key::IsTrigger(DIK_R)) {
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
			map.blockCount = 25;
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

		//もの運び
		/*if ((sqrtf((ellipseX - mouseX) * (ellipseX - mouseX) + (ellipseY - mouseY) * (ellipseY - mouseY)) < ellipseRadius) && Novice::IsTriggerMouse(0) == true) {
			isHit = true;
		}

		if (isHit == true) {
			ellipseX += mouseSpeedX;
			ellipseY += mouseSpeedY;
		}*/
		//

		for (int y = 0; y < 50; y++) {

			for (int x = 0; x < 50; x++) {

				if (map.map[y][x] == map.NONE) {

					if (mouseY < y * MAP_SIZE + MAP_SIZE &&
						mouseY > y * MAP_SIZE &&
						mouseX < x * MAP_SIZE + MAP_SIZE &&
						mouseX > x * MAP_SIZE) {

						if (Novice::IsPressMouse(0) == true && map.blockCount > 0) {
							map.map[y][x] = map.TMPBLOCK;
							map.tmpTime[y][x] = 300;
							map.blockCount--;
							map.blockColor[y][x] = 0xFFFFFFFF;
						}

					}

				}

				if (map.map[y][x] == map.TMPNONE) {

					map.tmpTime[y][x]--;

					if (mouseY < y * MAP_SIZE + MAP_SIZE &&
						mouseY > y * MAP_SIZE &&
						mouseX < x * MAP_SIZE + MAP_SIZE &&
						mouseX > x * MAP_SIZE) {

					}

					if (map.tmpTime[y][x] == 0) {
						map.map[y][x] = map.BLOCK;
						map.blockCount++;
					}

				}

				if (map.map[y][x] == map.BLOCK) {

					if (mouseY < y * MAP_SIZE + MAP_SIZE &&
						mouseY > y * MAP_SIZE &&
						mouseX < x * MAP_SIZE + MAP_SIZE &&
						mouseX > x * MAP_SIZE) {

						if (Novice::IsPressMouse(1) == true && map.blockCount > 0) {
							map.map[y][x] = map.TMPNONE;
							map.tmpTime[y][x] = 300;

						}

					}

					map.blockColor[y][x] = 0xFF3399FF;

				}




				if (map.map[y][x] == map.TMPBLOCK) {

					map.tmpTime[y][x]--;

					if (mouseY < y * MAP_SIZE + MAP_SIZE &&
						mouseY > y * MAP_SIZE &&
						mouseX < x * MAP_SIZE + MAP_SIZE &&
						mouseX > x * MAP_SIZE) {

					}

					if (map.tmpTime[y][x] == 0) {
						map.map[y][x] = map.NONE;
						map.blockCount++;
					}

					map.blockColor[y][x] = (int(255 * (map.tmpTime[y][x] / 300.0f)) << 24) + (int(255 * (map.tmpTime[y][x] / 300.0f)) << 16) + (int(255 * (map.tmpTime[y][x] / 300.0f)) << 8) + 255;
					
				}

			}

		}

		/*if (Novice::IsPressMouse(1) || Novice::IsPressMouse(0)) {

			slowTime++;

			if (slowTime == 60) {
				slowTime = 0;
			}

			if (slowTime % 2 == 0) {
				player.Update(map, slow);
				testEnemy.Update(player,map, slow);
			}

		}
		else {

			slowTime = 0;

			player.Update(map, slow);
			testEnemy.Update(player, map, slow);

		}*/
		for (int i = 0; i < kTestEnemy; i++) {
			testEnemy[i].Update(player, map, slow);
		}
		for (int i = 0; i < kTestEnemy2; i++) {
			testEnemy2[i].Update(player, map, slow);
		}
		player.Update(map, slow);
		//testEnemy.Update(player, map, slow);

		preMouseX = mouseX;
		preMouseY = mouseY;
		if (Key::IsPress(DIK_R)) {
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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//もの運び
		/*Novice::DrawEllipse(ellipseX, ellipseY, ellipseRadius, ellipseRadius, 0.0f, 0xFFFFFFFF, kFillModeSolid);*/

		Novice::DrawBox(0, 0, 1280, 720,0, ColorReverse(backgroundColor), kFillModeSolid);

		for (int y = 0; y < 50; y++) {

			for (int x = 0; x < 50; x++) {

				if (map.map[y][x] == map.BLOCK || map.map[y][x] == map.CANTBLOCK || map.map[y][x] == map.TMPBLOCK) {

					Novice::DrawQuad(x * MAP_SIZE, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE,
						x * MAP_SIZE, y * MAP_SIZE + MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE + MAP_SIZE,
						0, 0, 32, 32, TILE, map.blockColor[y][x]);

				}

			}

		}

		Novice::DrawEllipse(mouseX, mouseY, 10, 10, 0.0f, ColorReverse(color), kFillModeSolid);

		player.Draw(isColorReverse);
		for (int i = 0; i < kTestEnemy2; i++) {
			testEnemy2[i].Draw();
		}
		for (int i = 0; i < kTestEnemy; i++) {
			testEnemy[i].Draw();
		}

		Novice::ScreenPrintf(60, 200, "%d", slowTime); 
		Novice::ScreenPrintf(10, 70, "ENERGY : %d", map.blockCount);
		Novice::ScreenPrintf(10, 50, "W or SPACE to Jump");
		Novice::ScreenPrintf(10, 30, "A : Left Move D : Right Move");
		Novice::ScreenPrintf(10, 10, "Left Click to Make Block");
		/*Novice::ScreenPrintf(10, 200, "slow:%f", slow);*/

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
