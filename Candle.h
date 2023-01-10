#pragma once
#include "Map.h"
#include "Player2.h"
class Candle
{
public:
	//•Ï”
	bool isAlive;
	int candleMap[kMapBlockHeight][kMapBlockWidth];
	//ŠÖ”
	Candle(Map& map);
	void Init(Map& map);
	void Collision(Map& map,Player2& player);
	void Move(Map& map);
	void Update(Map& map, Player2& player);
	void LoadMap(Map& map);
};

