#include "Candle.h"
#include"Circle.h"
#include "Collision.h"
#include <Novice.h>
Candle::Candle(Map& map) {
	Init(map);
}


void Candle::Init(Map& map)
{
	isAlive = false;
	for (int y = 0; y < kMapBlockHeight; y++) {
		for (int x = 0; x < kMapBlockWidth; x++) {
			candleMap[y][x] = map.map[y][x];
		}
	}
}

void Candle::Update(Map& map, Player2& player)
{
	Collision(map,player);
	Move(map);
}
void Candle::Collision(Map& map, Player2& player)
{
	//ボムの半径がリセットされたとき
	if (player.BombRad == player.MAXEXPSIZE) {
		for (int y = 0; y < kMapBlockHeight; y++) {
			for (int x = 0; x < kMapBlockWidth; x++) {
				///スイッチ捜索
				if (candleMap[y][x] == Map::CANDLE_SWHITCH) {
					Circle a = { { static_cast<float>(player.BombPos.x),static_cast<float>(player.BombPos.y) }, static_cast<float>(player.BombRad) };
					Quad b = { {static_cast<float>(x * MAP_SIZE),static_cast<float>(y * MAP_SIZE)},{static_cast<float>((x + 1) * MAP_SIZE - 1),static_cast<float>(y * MAP_SIZE)},{static_cast<float>(x * MAP_SIZE),static_cast<float>((y + 1) * MAP_SIZE - 1)},{static_cast<float>((x + 1) * MAP_SIZE - 1),static_cast<float>((y + 1) * MAP_SIZE - 1)} };
					///爆弾の範囲がスイッチと接触しているか
					if (Collision::CircleToQuad(a, b) && !isAlive) {
						isAlive = true;
					}
					else if(Collision::CircleToQuad(a, b) && isAlive) {
						isAlive = false;
					}
				}
			}
		}
	}
}

void Candle::Move(Map& map)
{
	if (isAlive) {
		for (int y = 0; y < kMapBlockHeight; y++) {
			for (int x = 0; x < kMapBlockWidth; x++) {
				if (candleMap[y][x] == Map::CANDLE_BLOCK) {
					map.map[y][x] = Map::NONE;
				}
			}
		}
	}
	else {
		for (int y = 0; y < kMapBlockHeight; y++) {
			for (int x = 0; x < kMapBlockWidth; x++) {
				if (candleMap[y][x] == Map::CANDLE_BLOCK) {
					map.map[y][x] = Map::CANTBLOCK;
				}
			}
		}
	}
	Novice::ScreenPrintf(800,400,"isAlive:%d", isAlive);
}

void Candle::LoadMap(Map& map) {
	for (int y = 0; y < kMapBlockHeight; y++) {
		for (int x = 0; x < kMapBlockWidth; x++) {
			candleMap[y][x] = map.map[y][x];
		}
	}
}