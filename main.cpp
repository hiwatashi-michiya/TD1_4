#define _USE_MATH_DEFINES
#include <Novice.h>
#include <math.h>
#include <stdio.h>
#include "Player.h"
#include "TestEnemy.h"
#include "TestEnemy2.h"
#include "Key.h"

const char kWindowTitle[] = "map";

const int kMaxBlock = 5;

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
	bool preMousePush = false;

	int mouseSpeedX = 0;
	int mouseSpeedY = 0;

	int ellipseX = 300;
	int ellipseY = 300;
	int ellipseRadius = 50;

	int color = 0x000000FF;
	unsigned int backgroundColor = 0xFF88FFFF;
	

	bool isHit = false;

	int TILE = Novice::LoadTexture("./Resources/tile.png");
	int FRAMEBORDER = Novice::LoadTexture("./Resources/frameborder.png");

	bool isShowBorder = false;

	int slowTime = 0;
	bool canSlow = true;
	bool slowFlag = false;

	DRAWTYPE drawType = MAKE;

	Map map;
	int Map = 0;

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

			map.tmpTime[y][x] = 0;

			map.blockColor[y][x] = 0xFFFFFFFF;

			//mapEasy.tmpTime[y][x] = 0;

			//mapEasy.blockColor[y][x] = 0xFFFFFFFF;
		}

	}

	bool isEdit = false;

	int setNumber = 0;

	char string[kMaxBlock][2] = { "0", "1", "2", "3", "4" };

	
	map.blockCount = 25;
	//mapEasy.blockCount = 25;
	Player player;

	const int kTestEnemy = 6;
	TestEnemy testEnemy[kTestEnemy];
	//
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

	Novice::SetMouseCursorVisibility(0);

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
		///疲れた

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
		///数字キーを押すと設置するブロックを変えることができる
		///0:NONE(ブロックなし)
		///1:CANTBLOCK(壊せないブロック)
		///2:BLOCK(消せるブロック)
		///配置は通常プレイと同じでなぞって配置できる
		/// 
		if (Key::IsTrigger(DIK_E)) {
			
			if (isEdit == false) {
				isEdit = true;
			}
			else {
				isEdit = false;
			}

		}

		if (Key::IsTrigger(DIK_R)) {
			if (Map == 1) {
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
				map.blockCount = 25;
			}
		}

		if (player.LeftBottom.x < 32) {

			player.SetRight();

			Map--;

			for (int y = 0; y < 50; y++) {
				for (int x = 0; x < 50; x++) {
					map.blockNum[y][x] = 0;
					map.map[y][x] == map.NONE;
					map.blockCount = 25;
				}
			}

			if (Map == 1) {
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
			else {
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
				map.blockCount = 25;
			}

		}

		if (player.LeftBottom.x > 1280) {

			player.SetLeft();

			Map++;

			for (int y = 0; y < 50; y++) {
				for (int x = 0; x < 50; x++) {
					map.blockNum[y][x] = 0;
					map.map[y][x] == map.NONE;
					map.blockCount = 25;
				}
			}

			if (Map == 1) {
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
			else {
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
				map.blockCount = 25;
			}

		}

		if (isEdit == true) {

			//書き込む数字の設定
			if (Key::IsTrigger(DIK_0)) {
				setNumber = 0;
			}

			if (Key::IsTrigger(DIK_1)) {
				setNumber = 1;
			}

			if (Key::IsTrigger(DIK_2)) {
				setNumber = 2;
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

		//もの運び
		/*if ((sqrtf((ellipseX - mouseX) * (ellipseX - mouseX) + (ellipseY - mouseY) * (ellipseY - mouseY)) < ellipseRadius) && Novice::IsTriggerMouse(0) == true) {
			isHit = true;
		}

		if (isHit == true) {
			ellipseX += mouseSpeedX;
			ellipseY += mouseSpeedY;
		}*/
		//
		//if (Map == 1) {
		int mouseYGrid = mouseY / MAP_SIZE;
		int mouseXGrid = mouseX / MAP_SIZE;
		int premouseYGrid = preMouseY / MAP_SIZE;
		int premouseXGrid = preMouseX / MAP_SIZE;
		int setMouseYGrid = premouseYGrid;
		int setMouseXGrid = premouseXGrid;

		if (isEdit == true) {

			if (Novice::IsPressMouse(0) == true) {

				FILE* fp = NULL;

				if (Map == 0) {
					fopen_s(&fp, "./Resources/mapEasy.csv", "r+b");
					if (fp == NULL) {
						return 0;
					}
				}
				else {
					fopen_s(&fp, "./Resources/test.csv", "r+b");
					if (fp == NULL) {
						return 0;
					}
				}

				fseek(fp, (setMouseYGrid * 102) + (setMouseXGrid * 2), SEEK_SET);

				fputs(string[setNumber], fp);

				fclose(fp);

				if (Map == 1) {
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
				}

			}

		}
		else {

			for (int y = 0; y < 50; y++) {

				for (int x = 0; x < 50; x++) {

					if (map.map[y][x] == map.NONE) {

						if (y == mouseYGrid && x == mouseXGrid) {

							if (Novice::IsPressMouse(0) == true) {


								if (preMousePush == true) {

									while (1) {


										if (setMouseYGrid < mouseYGrid) {
											setMouseYGrid++;
										}
										if (setMouseYGrid > mouseYGrid) {
											setMouseYGrid--;
										}
										if (setMouseXGrid < mouseXGrid) {
											setMouseXGrid++;
										}
										if (setMouseXGrid > mouseXGrid) {
											setMouseXGrid--;
										}

										if (setMouseYGrid == mouseYGrid && setMouseXGrid == mouseXGrid) {
											//Novice::DrawBox(0, 0, 600, 600, 0, RED,kFillModeSolid);
											break;
										}

										if (map.map[setMouseYGrid][setMouseXGrid] == map.NONE) {
											if (map.blockCount > 0) {
												map.map[setMouseYGrid][setMouseXGrid] = map.TMPBLOCK;
												map.tmpTime[setMouseYGrid][setMouseXGrid] = 300;
												map.blockCount--;
												map.blockColor[setMouseYGrid][setMouseXGrid] = 0xFFFFFFFF;

												for (int y = 0; y < 50; y++) {
													for (int x = 0; x < 50; x++) {
														map.blockNum[y][x]++;
													}
												}
												map.blockNum[setMouseYGrid][setMouseXGrid] = 0;
											}
											else {

												/*int MinTmpTime = 300;
												for (int y = 0; y < 50; y++) {
													for (int x = 0; x < 50; x++) {
														if (MinTmpTime > int(map.tmpTime[y][x]) && int(map.tmpTime[y][x] != 0)) {
															MinTmpTime = int(map.tmpTime[y][x]);
														}
													}
												}*/

												for (int y = 0; y < 50; y++) {
													for (int x = 0; x < 50; x++) {
														if (int(map.blockNum[y][x]) == 24) {
															map.map[y][x] = map.NONE;
															map.blockCount++;
															map.tmpTime[y][x] = 0;

															//map.blockNum[y][x]++;
														}
													}
												}

												map.map[setMouseYGrid][setMouseXGrid] = map.TMPBLOCK;
												map.blockCount--;
												map.tmpTime[setMouseYGrid][setMouseXGrid] = 300;
												map.blockColor[setMouseYGrid][setMouseXGrid] = 0xFFFFFFFF;

												for (int y = 0; y < 50; y++) {
													for (int x = 0; x < 50; x++) {
														map.blockNum[y][x]++;
													}
												}
												map.blockNum[setMouseYGrid][setMouseXGrid] = 0;
											}
										}


										/*map.map[setMouseYGrid][setMouseXGrid] = map.TMPBLOCK;
										map.blockCount--;
										map.tmpTime[setMouseYGrid][setMouseXGrid] = 300;
										map.blockColor[setMouseYGrid][setMouseXGrid] = 0xFFFFFFFF;*/




									}


								}

								if (map.blockCount > 0) {
									map.map[y][x] = map.TMPBLOCK;
									map.tmpTime[y][x] = 300;
									map.blockCount--;
									map.blockColor[y][x] = 0xFFFFFFFF;

									for (int y = 0; y < 50; y++) {
										for (int x = 0; x < 50; x++) {
											map.blockNum[y][x]++;
										}
									}
									map.blockNum[y][x] = 0;
								}
								else {

									/*int MinTmpTime = 300;
									for (int y = 0; y < 50; y++) {
										for (int x = 0; x < 50; x++) {
											if (MinTmpTime > int(map.tmpTime[y][x]) && int(map.tmpTime[y][x] != 0)) {
												MinTmpTime = int(map.tmpTime[y][x]);
											}
										}
									}*/

									for (int y = 0; y < 50; y++) {
										for (int x = 0; x < 50; x++) {
											if (int(map.blockNum[y][x]) == 24) {
												map.map[y][x] = map.NONE;
												map.blockCount++;
												map.tmpTime[y][x] = 0;

												//map.blockNum[y][x]++;
											}
										}
									}


									map.map[y][x] = map.TMPBLOCK;
									map.blockCount--;
									map.tmpTime[y][x] = 300;
									map.blockColor[y][x] = 0xFFFFFFFF;


									for (int y = 0; y < 50; y++) {
										for (int x = 0; x < 50; x++) {
											map.blockNum[y][x]++;
										}
									}
									map.blockNum[y][x] = 0;
								}

							}

						}

					}

					//Novice::ScreenPrintf(60, 200, "%d", map.blockCount);

					if (map.map[y][x] == map.TMPNONE) {

						map.tmpTime[y][x]--;

						if (y == mouseYGrid && x == mouseXGrid) {

						}

						if (map.tmpTime[y][x] == 0) {
							map.map[y][x] = map.BLOCK;
							//map.blockCount++;
						}

					}

					if (map.map[y][x] == map.BLOCK) {

						if (y == mouseYGrid && x == mouseXGrid) {

							if (Novice::IsPressMouse(1) == true) {
								map.map[y][x] = map.TMPNONE;
								map.tmpTime[y][x] = 300;

							}

						}

						map.blockColor[y][x] = 0xFF3399FF;

					}




					if (map.map[y][x] == map.TMPBLOCK) {

						map.tmpTime[y][x]--;

						if (y == mouseYGrid && x == mouseXGrid) {

						}

						if (map.tmpTime[y][x] == 0) {
							map.map[y][x] = map.NONE;
							map.blockCount++;
						}

						map.blockColor[y][x] = (int(255 * (map.tmpTime[y][x] / 300.0f)) << 24) + (int(255 * (map.tmpTime[y][x] / 300.0f)) << 16) + (int(255 * (map.tmpTime[y][x] / 300.0f)) << 8) + 255;
						if (map.blockNum[y][x] == 24) {
							map.blockColor[y][x] = RED;
						}
					}

					if (map.map[y][x] == map.CANTBLOCK) {
						map.blockColor[y][x] = 0xFFEEFFFF;
					}

				}

			}

		}

		
		//}
		/*else {
			for (int y = 0; y < 50; y++) {

				for (int x = 0; x < 50; x++) {

					if (mapEasy.map[y][x] == mapEasy.NONE) {

						if (mouseY < y * MAP_SIZE + MAP_SIZE &&
							mouseY > y * MAP_SIZE &&
							mouseX < x * MAP_SIZE + MAP_SIZE &&
							mouseX > x * MAP_SIZE) {

							if (Novice::IsPressMouse(0) == true) {
								if (mapEasy.blockCount > 0) {
									mapEasy.map[y][x] = mapEasy.TMPBLOCK;
									mapEasy.tmpTime[y][x] = 300;
									mapEasy.blockCount--;
									mapEasy.blockColor[y][x] = 0xFFFFFFFF;
								}
								else {

									int MinTmpTime = 300;
									int DelX = x;
									int DelY = y;
									for (int y = 0; y < 50; y++) {
										for (int x = 0; x < 50; x++) {
											if (MinTmpTime > int(mapEasy.tmpTime[y][x]) && int(mapEasy.tmpTime[y][x] != 0)) {
												MinTmpTime = int(mapEasy.tmpTime[y][x]);
												DelX = x;
												DelY = y;
											}
										}
									}

								

									mapEasy.map[DelY][DelX] = mapEasy.NONE;
									mapEasy.tmpTime[DelY][DelX] = 0;
									mapEasy.map[y][x] = mapEasy.TMPBLOCK;
									mapEasy.tmpTime[y][x] = 300;
									mapEasy.blockColor[y][x] = 0xFFFFFFFF;

									
								}
							}
						}

					}
					Novice::ScreenPrintf(200, 200, "%d", mapEasy.blockCount);
					if (mapEasy.map[y][x] == mapEasy.TMPNONE) {

						mapEasy.tmpTime[y][x]--;

						if (mouseY < y * MAP_SIZE + MAP_SIZE &&
							mouseY > y * MAP_SIZE &&
							mouseX < x * MAP_SIZE + MAP_SIZE &&
							mouseX > x * MAP_SIZE) {

						}

						if (mapEasy.tmpTime[y][x] == 0) {
							mapEasy.map[y][x] = mapEasy.BLOCK;
							mapEasy.blockCount++;
						}

					}

					if (mapEasy.map[y][x] == mapEasy.BLOCK) {

						if (mouseY < y * MAP_SIZE + MAP_SIZE &&
							mouseY > y * MAP_SIZE &&
							mouseX < x * MAP_SIZE + MAP_SIZE &&
							mouseX > x * MAP_SIZE) {

							if (Novice::IsPressMouse(1) == true && mapEasy.blockCount > 0) {
								mapEasy.map[y][x] = mapEasy.TMPNONE;
								mapEasy.tmpTime[y][x] = 300;
								mapEasy.blockCount--;

							}

						}

						mapEasy.blockColor[y][x] = 0xFF3399FF;

					}




					if (mapEasy.map[y][x] == mapEasy.TMPBLOCK) {

						mapEasy.tmpTime[y][x]--;

						if (mouseY < y * MAP_SIZE + MAP_SIZE &&
							mouseY > y * MAP_SIZE &&
							mouseX < x * MAP_SIZE + MAP_SIZE &&
							mouseX > x * MAP_SIZE) {

						}

						if (mapEasy.tmpTime[y][x] == 0) {
							mapEasy.map[y][x] = map.NONE;
							mapEasy.blockCount++;
						}

						mapEasy.blockColor[y][x] = (int(255 * (mapEasy.tmpTime[y][x] / 300.0f)) << 24) + (int(255 * (mapEasy.tmpTime[y][x] / 300.0f)) << 16) + (int(255 * (mapEasy.tmpTime[y][x] / 300.0f)) << 8) + 255;
						Novice::ScreenPrintf(60, 200, "%d");
					}

				}

			}
		}*/

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
		if (Map == 1) {
			for (int i = 0; i < kTestEnemy; i++) {
				testEnemy[i].Update(player, map, slow);
			}
			for (int i = 0; i < kTestEnemy2; i++) {
				testEnemy2[i].Update(player, map, slow);
			}
			player.Update(map, slow);
		}
		else {
			player.Update(map, slow);
		}
		
		//testEnemy.Update(player, map, slow);

		preMouseX = mouseX;
		preMouseY = mouseY;
		preMousePush = Novice::IsPressMouse(0);

		if (Key::IsPress(DIK_R)) {
			if (Map == 1) {
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
			}
		}

		if (Key::IsTrigger(DIK_M)) {
			for (int y = 0; y < 50; y++) {
				for (int x = 0; x < 50; x++) {
					map.blockNum[y][x] = 0;
					map.map[y][x] == map.NONE;
					map.blockCount = 25;
				}
			}
			if (Map == 0) {
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
				testEnemy[0].Set({ 928.0f,32.0f });
				testEnemy[1].Set({ 832.0f,32.0f });
				testEnemy[2].Set({ 736.0f,32.0f });
				testEnemy[3].Set({ 640.0f,32.0f });
				testEnemy[4].Set({ 1120.0f,32.0f });
				testEnemy[5].Set({ 1184.0f,32.0f });
				testEnemy2[0].Set({ 32.0f,256.0f });
				testEnemy2[1].Set({ 32.0f,352.0f });
				Map = 1;
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
				Map = 0;
			}
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
		//if (Map == 1) {
			for (int y = 0; y < 50; y++) {

				for (int x = 0; x < 50; x++) {

					if (map.map[y][x] == map.BLOCK || map.map[y][x] == map.CANTBLOCK || map.map[y][x] == map.TMPBLOCK) {

						Novice::DrawQuad(x * MAP_SIZE, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE,
							x * MAP_SIZE, y * MAP_SIZE + MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE + MAP_SIZE,
							0, 0, 32, 32, TILE, map.blockColor[y][x]);

					}

				}

			}

			if (isShowBorder == true) {
				Novice::DrawQuad(0, 0, 1280, 0, 0, 720, 1280, 720, 0, 0, 1280, 720, FRAMEBORDER, 0x00000088);
			}

			if (isEdit == true) {
				Novice::DrawQuad(0, 0, 1280, 0, 0, 720, 1280, 720, 0, 0, 1280, 720, FRAMEBORDER, 0x0000FF88);
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

		Novice::DrawEllipse(mouseX, mouseY, 10, 10, 0.0f, ColorReverse(color), kFillModeSolid);
		

		

		Novice::DrawBox(20, 700, 20 * ( 60 - slowTime), 10, 0, 0xFFFF00FF, kFillModeSolid);
		Novice::DrawBox(20, 680, 40 * map.blockCount, 10, 0, GREEN, kFillModeSolid);

		player.Draw(isColorReverse);
		if (Map == 1) {
			for (int i = 0; i < kTestEnemy2; i++) {
				testEnemy2[i].Draw();
			}
			for (int i = 0; i < kTestEnemy; i++) {
				testEnemy[i].Draw();
			}
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
