#pragma once

enum TILE {
	NONE,
	BLOCK,
	TMPBLOCK
};

const int MAP_SIZE = 32;

static int map[50][50] = { 0 };

static int tmpTime[50][50] = { 0 };

static int blockCount = 50;
