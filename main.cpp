#define _USE_MATH_DEFINES
#include <Novice.h>
#include <math.h>
#include "Player.h"
#include "Key.h"

const char kWindowTitle[] = "LC1A_21_ヒワタシミチヤ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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

	bool isHit = false;

	int TILE = Novice::LoadTexture("./Resources/tile.png");

	Map map;

	for (int y = 0; y < 50; y++) {

		for (int x = 0; x < 50; x++) {
			map.map[y][x] = map.NONE;

			if (y == 20) {
				map.map[y][x] = map.BLOCK;
			}

			map.tmpTime[y][x] = 0;
		}

	}
	
	map.blockCount = 50;

	Player player;

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

		player.Update(map);

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
							map.tmpTime[y][x] = 180;
							map.blockCount--;
						}

					}

				}

				if (map.map[y][x] == map.BLOCK) {

					if (mouseY < y * MAP_SIZE + MAP_SIZE &&
						mouseY > y * MAP_SIZE &&
						mouseX < x * MAP_SIZE + MAP_SIZE &&
						mouseX > x * MAP_SIZE) {

					}

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

				}

			}

		}

		preMouseX = mouseX;
		preMouseY = mouseY;


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//もの運び
		/*Novice::DrawEllipse(ellipseX, ellipseY, ellipseRadius, ellipseRadius, 0.0f, 0xFFFFFFFF, kFillModeSolid);*/

		for (int y = 0; y < 50; y++) {

			for (int x = 0; x < 50; x++) {

				if (map.map[y][x] == map.BLOCK || map.map[y][x] == map.TMPBLOCK) {

					Novice::DrawQuad(x * MAP_SIZE, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE,
						x * MAP_SIZE, y * MAP_SIZE + MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE + MAP_SIZE,
						0, 0, 32, 32, TILE, 0xFFFFFFFF);

				}

			}

		}

		Novice::DrawEllipse(mouseX, mouseY, 10, 10, 0.0f, color, kFillModeSolid);

		player.Draw();

		Novice::ScreenPrintf(10, 10, "%d", 20*MAP_SIZE);

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
