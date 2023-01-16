#pragma once
#include "Vec2.h"
#include "Map.h"
#include "Quad.h"
#include "Circle.h"
#include "Player2.h"

class TestEnemy06
{
public:
	TestEnemy06(Vec2 position);
	~TestEnemy06();

	void Update(Player2& player, Map& map);
	void Draw(float* scrollX);
	void Spawn(Vec2 position);
	void Init(Vec2 position);

private:

	void Collision(Player2& player, Map& map);
	void Move();
	
	//�X�e�[�^�X
	Vec2 mPosition;
	Vec2 mSpeed;
	int mRadius;
	//�����蔻��
	Quad mColQuad;


	bool mIsAlive;

	//�X�|�[���^�C�}�[�̐ݒ�
	int mRespawnTime;

	//�l�_�̓����蔻��
	int left;
	int top;
	int right;
	int bottom;

	//���x�̐ݒ�
	bool mSetTarget;

	//��������
	int mMoveTime;
	//�������Ԃ̐ݒ�
	int mRandMoveTime;

	//�~�܂鎞��
	int mStopTime;

	//SE
	int mKnockSE;

};


