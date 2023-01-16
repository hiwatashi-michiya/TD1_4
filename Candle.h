#pragma once
#include "Map.h"
#include "Player2.h"
class Candle
{
public:
	//•Ï”
	bool isAlive;
	//ŠÖ”
	Candle();
	void Init();
	void Collision(Player2& player);
	void Move();
	void Update(Player2& player);
	void LoadMap();
};

