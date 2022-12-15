#pragma once
#include "Vec2.h"

const int MAP_SIZE = 32;

const int kMaxBlock = 12;

struct Map{
	enum TILE {
		NONE = 10,
		CANTBLOCK,
		BLOCK,
		TMPNONE,
		TMPBLOCK,
		NEEDLE,
		REDNONE,
		GREENNONE,
		BLUENONE,
		REDBLOCK,
		GREENBLOCK,
		BLUEBLOCK
		
	};

	int map[50][50];

	//�����蔻��̂Ȃ��u���b�N���ǂ����𒲂ׂ�
	bool AnyNone(int map) {

		if (map == NONE || map == TMPNONE || map == REDNONE || map == GREENNONE || map == BLUENONE) {
			return true;
		}

		return false;

	}

	float tmpTime[50][50];

	unsigned int blockColor[50][50];

	int blockCount;
	int blockNum[50][50];

	struct BlockStruct {
		Vec2 pos;
	};
	
	BlockStruct Block[50][50];

};

