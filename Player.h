#pragma once
#include "Vec2.h"
#include "Map.h"

class Player
{
public:
	Player();
	void Init();
	void SetLeft();
	void SetRight();

	Vec2 position;
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;
	Vec2 vector;
	Vec2 velocity;
	
	float speed;
	
	bool jumpFlag;
	float jumpSpeed;

	Vec2 gravityVector;
	Vec2 gravityVelocity;
	float gravitySpeed;

	int key;
	int prekey;

	int texture;

	void Update(Map map, float slow);
	void Draw(float isColorReverse);

	
};

