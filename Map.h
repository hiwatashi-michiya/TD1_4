#pragma once
#include "Vec2.h"

const int MAP_SIZE = 32;

//ブロックの種類
const int kMaxBlock = 19;

//マップチップの横最大数
const int kMapBlockWidth = 500;

//マップチップの縦最大数
const int kMapBlockHeight = 50;

struct Map{
	enum TILE {
		NONE = 10,
		CANTBLOCK,//11
		BREAKBLOCK,//12
		TMPNONE,//13
		TMPBLOCK,//14
		NEEDLE,//15
		RED_NONE,//16
		GREEN_NONE,//17
		BLUE_NONE,//18
		RED_BLOCK,//19
		GREEN_BLOCK,//20
		BLUE_BLOCK,//21
		CANDLE_SWITCH,//22
		CANDLE_NONE,//23
		CANDLE_BLOCK,//24
		ICE_BLOCK,//25
		RED_SWITCH,//26
		GREEN_SWITCH,//27
		BLUE_SWITCH//28
	};

	int map[kMapBlockHeight][kMapBlockWidth];

	//当たり判定のないブロックかどうかを調べる。trueならNONE、falseならBLOCK
	bool AnyNone(int map) {

		if (map == NONE || map == TMPNONE || map == RED_NONE || map == GREEN_NONE || map == BLUE_NONE || map == CANDLE_NONE || map == CANDLE_SWITCH ||
			map == RED_SWITCH || map == GREEN_SWITCH || map == BLUE_SWITCH) {
			return true;
		}

		return false;

	}

	unsigned int blockColor[kMapBlockHeight][kMapBlockWidth];

	//針に当たったかどうか
	bool isHitNeedle;

};

