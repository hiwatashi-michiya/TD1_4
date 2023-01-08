#pragma once
#include "Vec2.h"

const int MAP_SIZE = 32;

//ブロックの種類
const int kMaxBlock = 18;

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
		RED_NONE,
		GREEN_NONE,
		BLUE_NONE,
		RED_BLOCK,
		GREEN_BLOCK,
		BLUE_BLOCK,
		CANDLE_SWHITCH,
		CANDLE_BLOCK,
		ICE_BLOCK,
		RED_SWITCH,
		GREEN_SWITCH,
		BLUE_SWITCH
	};

	int map[kMapBlockHeight][kMapBlockWidth];

	//当たり判定のないブロックかどうかを調べる。trueならNONE、falseならBLOCK
	bool AnyNone(int map) {

		if (map == NONE || map == TMPNONE || map == RED_NONE || map == GREEN_NONE || map == BLUE_NONE || map == CANDLE_SWHITCH ||
			map == RED_SWITCH || map == GREEN_SWITCH || map == BLUE_SWITCH) {
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

