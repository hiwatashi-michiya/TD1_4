#pragma once
#include "Map.h"
#include "Player2.h"
class Candle
{
public:
	//�ϐ�
	bool isAlive;
	int candleMap[50][50];
	//�֐�
	Candle(Map& map);
	void Init(Map& map);
	void Collision(Map& map,Player2& player);
	void Move(Map& map);
	void Update(Map& map, Player2& player);
	void LoadMap(Map& map);
};

