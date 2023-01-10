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

void Lift::Update()
{
	Move();
	Collision();
}

void Lift::Draw(float* scrollX)
{
	localPosition = { worldPosition.x - *scrollX,worldPosition.y};
	Matrix33 tmp = Matrix33::MakeAffine({1,1}, 0, {localPosition});
	localQuad = quad * tmp;
	Novice::DrawQuad(localQuad.LeftTop.x, localQuad.LeftTop.y, localQuad.RightTop.x, localQuad.RightTop.y, localQuad.LeftBottom.x, localQuad.LeftBottom.y, localQuad.RightBottom.x, localQuad.RightBottom.y,0,0,width,height,texture,color);
}
