#pragma once
#include "Vec2.h"

const int MAP_SIZE = 32;

//�u���b�N�̎��
const int kMaxBlock = 18;

//�}�b�v�`�b�v�̉��ő吔
const int kMapBlockWidth = 500;

//�}�b�v�`�b�v�̏c�ő吔
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

	//�����蔻��̂Ȃ��u���b�N���ǂ����𒲂ׂ�Btrue�Ȃ�NONE�Afalse�Ȃ�BLOCK
	bool AnyNone(int map) {

		if (map == NONE || map == TMPNONE || map == RED_NONE || map == GREEN_NONE || map == BLUE_NONE || map == CANDLE_SWHITCH ||
			map == RED_SWITCH || map == GREEN_SWITCH || map == BLUE_SWITCH) {
			return true;
		}

		return false;

	}

	unsigned int blockColor[kMapBlockHeight][kMapBlockWidth];

};

