#pragma once
#include "Vec2.h"
#include "Circle.h"
class WindMill
{
private:

	Vec2 WorldPos;
	Vec2 LocalPos;
	float Radius;
	Circle circle;

	bool isExpHit;

	float Charge;
	bool isCharged;

	const int MAXCHARGE = 200;

public:

	WindMill();

	void Set(Vec2 pos,float ScrollX);

	void Update(float ScrollX);

	void Hit(Circle TargetCircle);

	bool GetisCharged() { return isCharged; };

	void Draw();
};

