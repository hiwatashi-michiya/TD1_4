#include "Lift.h"
#include "Matrix33 .h"
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
	velocity = 0;
	quad = { worldPosition, width, height };
}

void Lift::Move()
{
}

void Lift::Collision()
{

}

void Lift::Update(float Scroll)
{
	localPosition = { worldPosition.x - Scroll,worldPosition.y - Scroll };
	Move();
	Collision();
}

void Lift::Draw()
{
	Matrix33 tmp = Matrix33::MakeAffine({1,1}, 0, {localPosition});
	quad = quad * tmp;
	Novice::DrawQuad(quad.LeftTop.x, quad.LeftTop.y, quad.RightTop.x, quad.RightTop.y, quad.LeftBottom.x, quad.LeftBottom.y, quad.RightBottom.x, quad.RightBottom.y,0,0,width,height,texture,color);
}
