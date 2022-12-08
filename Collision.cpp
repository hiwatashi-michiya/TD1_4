#include "Collision.h"


bool Collision::QuadToQuad(float x, float y, float quadw, float quadh, float x2, float y2, float quadw2, float quadh2) {
	if (x <= x2 + quadw2 && x + quadw >= x2 && y >= y2 - quadh2 && y - quadh <= y2) {
		return true;
	}

	return false;
}

bool Collision::QuadToQuad(Vec2 pos, float quadw, float quadh, Vec2 pos2, float quadw2, float quadh2) {
	if (pos.x <= pos2.x + quadw2 && pos.x + quadw >= pos2.x && pos.y >= pos2.y - quadh2 && pos.y - quadh <= pos2.y) {
		return true;
	}

	return false;
}

bool Collision::QuadToQuad(Quad pos, Quad pos2) {
	if (pos.LeftTop.x <= pos2.RightTop.x && pos.RightTop.x >= pos2.LeftTop.x && pos.LeftTop.y >= pos2.LeftBottom.y && pos.LeftBottom.y <= pos2.LeftTop.y) {
		return true;
	}

	return false;
}

bool Collision::DiagonalQuadToQuad(Quad pos, Quad diagonalPos) {

	//矩形の辺に沿るベクトル
	Vec2 StartLeftBottom = diagonalPos.LeftBottom - diagonalPos.LeftTop;
	Vec2 StartLeftTop = diagonalPos.LeftTop - diagonalPos.RightTop;
	Vec2 StartRightTop = diagonalPos.RightTop - diagonalPos.RightBottom;
	Vec2 StartRightBottom = diagonalPos.RightBottom - diagonalPos.LeftBottom;
	//細かく当たり判定を取るための間の点のベクトル
	Vec2 MiddleTop = { pos.LeftTop.x + pos.GetWidth() / 2, pos.LeftTop.y };
	Vec2 MiddleRight = { pos.RightTop.x , pos.LeftTop.y - pos.GetHeight() / 2 };
	Vec2 MiddleBottom = { pos.LeftTop.x + pos.GetWidth() / 2, pos.LeftBottom.y };
	Vec2 MiddleLeft = { pos.LeftTop.x , pos.LeftTop.y - pos.GetHeight() / 2 };
	//角からとりたい当たり判定の点までのベクトル
	Vec2 LeftTopToPoint = diagonalPos.LeftTop - pos.LeftTop;
	Vec2 RightTopToPoint = diagonalPos.RightTop - pos.LeftTop;
	Vec2 LeftBottomToPoint = diagonalPos.LeftBottom - pos.LeftTop;
	Vec2 RightBottomToPoint = diagonalPos.RightBottom - pos.LeftTop;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - pos.RightTop;
	RightTopToPoint = diagonalPos.RightTop - pos.RightTop;
	LeftBottomToPoint = diagonalPos.LeftBottom - pos.RightTop;
	RightBottomToPoint = diagonalPos.RightBottom - pos.RightTop;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - pos.LeftBottom;
	RightTopToPoint = diagonalPos.RightTop - pos.LeftBottom;
	LeftBottomToPoint = diagonalPos.LeftBottom - pos.LeftBottom;
	RightBottomToPoint = diagonalPos.RightBottom - pos.LeftBottom;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - pos.RightBottom;
	RightTopToPoint = diagonalPos.RightTop - pos.RightBottom;
	LeftBottomToPoint = diagonalPos.LeftBottom - pos.RightBottom;
	RightBottomToPoint = diagonalPos.RightBottom - pos.RightBottom;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - MiddleTop;
	RightTopToPoint = diagonalPos.RightTop - MiddleTop;
	LeftBottomToPoint = diagonalPos.LeftBottom - MiddleTop;
	RightBottomToPoint = diagonalPos.RightBottom - MiddleTop;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - MiddleRight;
	RightTopToPoint = diagonalPos.RightTop - MiddleRight;
	LeftBottomToPoint = diagonalPos.LeftBottom - MiddleRight;
	RightBottomToPoint = diagonalPos.RightBottom - MiddleRight;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - MiddleBottom;
	RightTopToPoint = diagonalPos.RightTop - MiddleBottom;
	LeftBottomToPoint = diagonalPos.LeftBottom - MiddleBottom;
	RightBottomToPoint = diagonalPos.RightBottom - MiddleBottom;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}

	LeftTopToPoint = diagonalPos.LeftTop - MiddleLeft;
	RightTopToPoint = diagonalPos.RightTop - MiddleLeft;
	LeftBottomToPoint = diagonalPos.LeftBottom - MiddleLeft;
	RightBottomToPoint = diagonalPos.RightBottom - MiddleLeft;

	if (StartLeftTop.Cross(LeftTopToPoint) <= 0 &&
		StartRightTop.Cross(RightTopToPoint) <= 0 &&
		StartRightBottom.Cross(RightBottomToPoint) <= 0 &&
		StartLeftBottom.Cross(LeftBottomToPoint) <= 0) {
		return true;
	}
	

	return false;
}

bool Collision::CircleToCirlce(Circle a, Circle b) {
	float distance = a.pos.DistanceFrom(b.pos);
	if (a.radius + b.radius >= distance) {
		return true;
	}
	return false;
}

bool Collision::CircleToQuad(Circle a, Quad b) {
	if (Collision::QuadToQuad({ b.LeftTop.x ,b.LeftTop.y + a.radius }, b.GetWidth(), b.GetHeight() + a.radius * 2, a.pos, 1, 1) ||
		Collision::QuadToQuad({ b.LeftTop.x - a.radius,b.LeftTop.y }, b.GetWidth() + a.radius * 2, b.GetHeight(), a.pos, 1, 1) ||
		Collision::CircleToCirlce({ a.pos,1 }, { b.LeftTop,a.radius }) ||
		Collision::CircleToCirlce({ a.pos,1 }, { b.RightTop,a.radius }) ||
		Collision::CircleToCirlce({ a.pos,1 }, { b.LeftBottom,a.radius }) ||
		Collision::CircleToCirlce({ a.pos,1 }, { b.RightBottom,a.radius })
		) {

		return true;
	}
	return false;
}

Quad Collision::GetCollisionQuad(Quad a, Quad b) {
	Quad tmp;
	if (a.LeftTop.x <= b.LeftTop.x) {
		tmp.LeftTop.x = b.LeftTop.x;
		tmp.LeftBottom.x = b.LeftBottom.x;
	}
	else {
		tmp.LeftTop.x = a.LeftTop.x;
		tmp.LeftBottom.x = a.LeftBottom.x;
	}

	if (a.RightTop.x >= b.RightTop.x) {
		tmp.RightTop.x = b.RightTop.x;
		tmp.RightBottom.x = b.RightBottom.x;
	}
	else {
		tmp.RightTop.x = a.RightTop.x;
		tmp.RightBottom.x = a.RightBottom.x;
	}

	if (a.LeftTop.y <= b.LeftTop.y) {
		tmp.LeftTop.y = a.LeftTop.y;
		tmp.RightTop.y = a.RightTop.y;
	}
	else {
		tmp.LeftTop.y = b.LeftTop.y;
		tmp.RightTop.y = b.RightTop.y;
	}
	 
	if (a.LeftBottom.y >= b.LeftBottom.y) {
		tmp.LeftBottom.y = a.LeftBottom.y;
		tmp.RightBottom.y = a.RightBottom.y;
	}
	else {
		tmp.LeftBottom.y = b.LeftBottom.y;
		tmp.RightBottom.y = b.RightBottom.y;
	}

	return{ tmp };
}