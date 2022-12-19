#pragma once
#include "Vec2.h"

const int MAP_SIZE = 32;

const int kMaxBlock = 14;

//�}�b�v�`�b�v�̉��ő吔
const int kMapBlockWidth = 50;

//�}�b�v�`�b�v�̏c�ő吔
const int kMapBlockHeight = 50;

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
		BLUEBLOCK,
		CANDLE_SWHITCH,
		CANDLE_BLOCK,
	};

	int map[kMapBlockHeight][kMapBlockWidth];

	//�����蔻��̂Ȃ��u���b�N���ǂ����𒲂ׂ�
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

