#pragma once
#include "Vec2.h"

const int MAP_SIZE = 32;

//ブロックの種類
const int kMaxBlock = 15;

//マップチップの横最大数
const int kMapBlockWidth = 50;

//マップチップの縦最大数
const int kMapBlockHeight = 50;

struct Map{
	enum TILE {
		NONE = 10,
		CANTBLOCK,
		BREAKBLOCK,
		TMPNONE,
		TMPBLOCK,
		NEEDLE,
		REDNONE,
		GREENNONE,
		BLUENONE,
		REDBLOCK,
		GREENBLOCK,
		BLUEBLOCK,
		CANDLE_SWHITCH,
		CANDLE_BLOCK,
		ICEBLOCK,
	};

	int map[kMapBlockHeight][kMapBlockWidth];

	//当たり判定のないブロックかどうかを調べる。trueならNONE、falseならBLOCK
	bool AnyNone(int map) {

		if (map == NONE || map == TMPNONE || map == REDNONE || map == GREENNONE || map == BLUENONE || map == CANDLE_SWHITCH) {
			return true;
		}

		return false;

	}

	unsigned int blockColor[50][50];

	int blockCount;
	int blockNum[50][50];

	struct BlockStruct {
		Vec2 pos;
	};
	
	BlockStruct Block[50][50];

};

