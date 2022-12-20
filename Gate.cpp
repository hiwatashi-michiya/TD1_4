#include "Gate.h"
#include <Novice.h>

Gate::Gate()
{
	WorldPos = { 9999,9999 };
	LocalPos = { 9999,9999 };

	Size = { 1,1 };

	OpenPos = 0;

	isExist = false;
}

void Gate::Set(Vec2 pos, Vec2 size, float ScrollX)
{
	WorldPos = pos;

	LocalPos.x = WorldPos.x - ScrollX;
	LocalPos.y = WorldPos.y;

	Size = size;

	quad = { {LocalPos.x - ScrollX,LocalPos.y + Size.y / 2 }, int(Size.x),int(Size.y) };

	isExist = true;
}

void Gate::Update(float ScrollX, bool isOpen)

{

	if (isOpen == true) {
		if (OpenPos < Size.y) {
			OpenPos += 2;
		}
	}
	else {
		if (OpenPos > 0) {
			OpenPos -= 4;
		}
	}


	if (OpenPos >= Size.y) {
		OpenPos = Size.y;
	}
	if (OpenPos <= 0) {
		OpenPos = 0;
	}

	LocalPos.x = WorldPos.x - ScrollX;
	LocalPos.y = WorldPos.y ;

	quad = { {WorldPos.x,WorldPos.y + Size.y / 2 - OpenPos}, int(Size.x),int(Size.y) };
}

void Gate::Hit(Quad TargetQuad)
{
}

void Gate::Delete()
{

	WorldPos = { 9999,9999 };
	LocalPos = { 9999,9999 };

	Size = { 1,1 };

	OpenPos = 0;

	isExist = false;
}

void Gate::Draw()
{
	if (isExist == true) {
		Novice::DrawQuad(
			LocalPos.x - Size.x / 2, LocalPos.y - OpenPos,
			LocalPos.x + Size.x / 2, LocalPos.y - OpenPos,
			LocalPos.x - Size.x / 2, LocalPos.y + Size.y - OpenPos,
			LocalPos.x + Size.x / 2, LocalPos.y + Size.y - OpenPos,
			0, 0,
			1, 1,
			0, RED);
	}
}
