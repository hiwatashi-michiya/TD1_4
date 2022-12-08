#pragma once

const int MAP_SIZE = 32;

struct Map{
	enum TILE {
		NONE,
		CANTBLOCK,
		BLOCK,
		TMPNONE,
		TMPBLOCK,
		NEEDLE
		
	};
	int map[50][50];

	float tmpTime[50][50];

	unsigned int blockColor[50][50];

	int blockCount;
	int blockNum[50][50];
	
};

