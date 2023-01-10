#include "Lift.h"
#include "Matrix33 .h"
#include "Collision.h"
#include <Novice.h>

Lift::Lift()
{
	Init();
}

void Lift::Init()
{
	texture = 0;
	quad = { worldPosition, width, height };
	width = 0;
	height = 0;
	color = WHITE;
	worldPosition = { 0,0 };
	localPosition = { 0,0 };
	velocity = 0;
}

void Lift::Set(Vec2 Position,int Width,int Height)
{
	texture = 0;
	width = Width;
	height = Height;
	color = WHITE;
	worldPosition = Position;
	localPosition = Position;
	localQuad;
	velocity = 0;
	quad = { worldPosition, width, height };
}

void Lift::Move(Player2& player)
{
}

void Lift::Update(Player2& player)
{
	Collision(player);
	Move(player);
}

void Lift::Collision(Player2& player)
{
	if (Collision::QuadToQuad(player.GetPlayerQuad(), quad)) {
		//è„
		if (quad.LeftTop.x < player.GetPlayerQuad().RightTop.x && quad.RightTop.x < player.GetPlayerQuad().RightTop.x && quad.LeftBottom.y > player.GetPlayerQuad().LeftBottom.y) {
			int i;
		}
	}
}

void Lift::Draw(float* scrollX)
{
	localPosition = { worldPosition.x - *scrollX,worldPosition.y};
	Matrix33 tmp = Matrix33::MakeAffine({1,1}, 0, {localPosition});
	localQuad = quad * tmp;
	Novice::DrawQuad(localQuad.LeftTop.x, localQuad.LeftTop.y, localQuad.RightTop.x, localQuad.RightTop.y, localQuad.LeftBottom.x, localQuad.LeftBottom.y, localQuad.RightBottom.x, localQuad.RightBottom.y,0,0,width,height,texture,color);
}
