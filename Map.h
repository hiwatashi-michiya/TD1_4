#pragma once

const int MAP_SIZE = 32;

struct Map{
	enum TILE {
		NONE,
		BLOCK,
		TMPNONE,
		TMPBLOCK
		
	};
	int map[50][50];

	float tmpTime[50][50];

	unsigned int blockColor[50][50];

	int blockCount;

	
};

