#pragma once
#include "Vec2.h"
#include "Map.h"
#include"Quad.h"
#include"Circle.h"

class Player
{
public:
	Player();
	void Init();
	void SetLeft();
	void SetRight();

	//�{���̏�����
	void BombInit();

	//�{���𓊂������
	int stickPositionX;
	int stickPositionY;

	//���e�̏��
	Vec2 bombPosition;
	Vec2 bombVelocity;
	float bombLength;

	//�{���̓����蔻��
	Circle bombCollision;

	//�u���b�N�̓����蔻��(�{����p)
	Vec2 blockLeftTop;
	Vec2 blockRightTop;
	Vec2 blockLeftBottom;
	Vec2 blockRightBottom;
	Quad blockCollision;

	//���j�������ǂ���
	bool isExplosion;

	//�����郂�[�V�����ɓ����Ă��邩�ǂ���
	bool isThrowMotion;

	//���������ǂ���
	bool isAfterThrow;

	//�{���̉摜
	int bombTexture;

	Vec2 position;
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;
	Vec2 vector;
	Vec2 velocity;
	Vec2 knockBackVelocity= {0,0};

	Quad playerColQuad = { LeftTop ,RightTop ,LeftBottom ,RightBottom };
	
	float speed;
	
	bool jumpFlag;
	float jumpSpeed;

	Vec2 gravityVector;
	Vec2 gravityVelocity;
	float gravitySpeed;

	bool expflag = false;

	int key;
	int prekey;

	int texture;

	void Update(Map map, float slow);
	void Draw(float isColorReverse);

	Quad GetPlayerQuad() { return playerColQuad;};

	void hitCircle(Circle targetCircle, Vec2 knockBack,int Damage);
};

