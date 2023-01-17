#pragma once
#include "Vec2.h"

const int MAP_SIZE = 32;

//�u���b�N�̎��
const int kMaxBlock = 20;

//�}�b�v�`�b�v�̉��ő吔
const int kMapBlockWidth = 500;

//�}�b�v�`�b�v�̏c�ő吔
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
		BLUE_SWITCH,//28
		SPEEDDOWN,//29
	};

	int map[kMapBlockHeight][kMapBlockWidth];

	//�����蔻��̂Ȃ��u���b�N���ǂ����𒲂ׂ�Btrue�Ȃ�NONE�Afalse�Ȃ�BLOCK
	bool AnyNone(int map) {

		if (map == NONE || map == TMPNONE || map == RED_NONE || map == GREEN_NONE || map == BLUE_NONE || map == CANDLE_NONE || map == CANDLE_SWITCH ||
			map == RED_SWITCH || map == GREEN_SWITCH || map == BLUE_SWITCH) {
			return true;
		}

		return false;

	}

	int blockColor;

	//�j�ɓ����������ǂ���
	bool isHitNeedle;

};

