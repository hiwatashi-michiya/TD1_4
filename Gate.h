#pragma once
#include "Vec2.h"
#include "Quad.h"

class Gate
{

private:
	
	Vec2 WorldPos;//è„ê^ÇÒíÜ
	Vec2 LocalPos;

	Vec2 Size;

	Quad quad;

	float OpenPos;

public:
	Gate();

	void Set(Vec2 pos, Vec2 size,float ScrollX);

	void Update(float ScrollX,bool isOpen);

	void Hit(Quad TargetQuad);

	Quad GetGateQuad() { return quad; };

	void Draw();
};

