#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vec2.h"
#include "Matrix33 .h"

class Quad {
public:
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;

public:

	Quad();
	Quad(Vec2 Pos, int width, int height);
	Quad(Vec2 Pos, int width, int height, int center);
	Quad(Vec2 LeftTop, Vec2 RightTop, Vec2 LeftBottom, Vec2 RightBottom);
	Quad Scaling(Quad quad, float scale);
	Quad XScaling(Quad quad, float scale);
	Quad YScaling(Quad quad, float scale);
	Quad Rotate(Quad quad, float theta);
	Quad Rotate(Quad quad, float theta, float radius);
	Quad CenterRotate(Quad quad, float theta);
	Quad Translation(Quad quad, Vec2 position);
	void WidthAdd(Quad& quad, float add);

	float GetWidth() const { return RightTop.DistanceFrom(LeftTop); }
	float GetHeight() const { return LeftTop.DistanceFrom(LeftBottom); }
	Vec2 GetCenter() const { return { ((RightTop - LeftTop).Normalized() * LeftTop.DistanceFrom(RightTop) / 2) + ((LeftBottom - LeftTop).Normalized() * LeftTop.DistanceFrom(LeftBottom) / 2) + LeftTop }; }

	Quad operator + (Vec2 s) const;
	Quad operator - (Vec2 s) const;
	Quad operator + (float s)const;
	Quad operator * (Matrix33 mat)const;
};

