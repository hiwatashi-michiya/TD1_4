#pragma once
#include "Vec2.h"
#include "Quad.h"
#include "Circle.h"
namespace Collision {
	bool QuadToQuad(float x, float y, float quadw, float quadh, float x2, float y2, float quadw2, float quadh2);


	bool QuadToQuad(Vec2 pos, float quadw, float quadh, Vec2 pos2, float quadw2, float quadh2);


	bool QuadToQuad(Quad pos, Quad pos2);

	bool DiagonalQuadToQuad(Quad pos, Quad diagonalPos);

	bool CircleToCirlce(Circle a, Circle b);

	bool CircleToQuad(Circle a, Quad b);

	Quad GetCollisionQuad(Quad a, Quad b);
}
