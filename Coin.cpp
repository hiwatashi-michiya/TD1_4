#include "Coin.h"
#include "Collision.h"
#include <Novice.h>
Coin::Coin()
{
	Init();
}

void Coin::Init()
{
	pos = {0.0f,0.0f};
	quad = { {0.0f,0.0f },0,0};
	width = 50.0f;
	height = 50.0f;
	isAlive = false;
}

void Coin::Set(Vec2 pos)
{
	this->pos = pos;
	isAlive = true;
}

void Coin::Update(Player2& player, float* scroll)
{
	Collision(player, scroll);
}

void Coin::Collision(Player2& player, float* scroll)
{
	if (isAlive) {
		quad = { {pos.x /*- *scroll*/,pos.y},(int)width,(int)height };
		if (Collision::QuadToQuad(player.GetPlayerQuad(), quad)) {
			isAlive = false;
		}
	}
	
}

void Coin::Draw(float* scroll)
{
	if (isAlive) {
		quad = { {pos.x - *scroll,pos.y},(int)width,(int)height };
		Novice::DrawQuad(quad.LeftTop.x, quad.LeftTop.y, quad.RightTop.x, quad.RightTop.y, quad.LeftBottom.x, quad.LeftBottom.y, quad.RightBottom.x, quad.RightBottom.y, 0, 0, width, height, 0, 0xFFFF00FF);
	}
}
