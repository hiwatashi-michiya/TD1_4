#include "TestEnemy06.h"
#include <Novice.h>
#include "Collision.h"

TestEnemy06::TestEnemy06(Vec2 position)
{

	Init(position);

	//���\�[�X
	mKnockSE = Novice::LoadAudio("./Resources/SE/knock.wav");

}

TestEnemy06::~TestEnemy06()
{
}

void TestEnemy06::Init(Vec2 position) {

	mPosition = position;
	mSpeed = { 3,3 };
	mRadius = MAP_SIZE;
	mIsAlive = true;
	mRespawnTime = 0;
	mColQuad = { mPosition, mRadius, mRadius };
	left = (mPosition.x - mRadius / 2) / MAP_SIZE;
	top = (mPosition.y - mRadius / 2) / MAP_SIZE;
	right = (mPosition.x + mRadius / 2 - 1) / MAP_SIZE;
	bottom = (mPosition.y + mRadius / 2 - 1) / MAP_SIZE;
	mSetTarget = false;
	mMoveTime = 0;
	mStopTime = 0;
	mRandMoveTime = 60;

}

void TestEnemy06::Update(Player2& player,Map& map) {

	if (mIsAlive == true) {

		if (mSetTarget == false) {

			//�ڕW�ƍs�����Ԃ�ݒ�
			if (mStopTime == 0) {
				mRandMoveTime = rand() % 40 + 40;
				mSpeed.x = (player.GetPlayerPos().x - mPosition.x) / (mRandMoveTime * 2);
				mSpeed.y = (player.GetPlayerPos().y - mPosition.y) / (mRandMoveTime * 2);
			}

			mStopTime++;

			if (mStopTime == 60) {
				mSetTarget = true;
				mMoveTime = 0;
			}

		}

		Move();

		Collision(player, map);

	}

}

void TestEnemy06::Draw(float* scrollX) {

	if (mIsAlive == true) {
		Novice::DrawQuad(mPosition.x - mRadius / 2 - *scrollX, mPosition.y - mRadius / 2,
			mPosition.x + mRadius / 2 - *scrollX, mPosition.y - mRadius / 2,
			mPosition.x - mRadius / 2 - *scrollX, mPosition.y + mRadius / 2,
			mPosition.x + mRadius / 2 - *scrollX, mPosition.y + mRadius / 2,
			0, 0, 1, 1, 0, 0x0000FFFF);
	}

}

void TestEnemy06::Spawn(Vec2 position) {

	if (mIsAlive == false) {

		if (mRespawnTime == 0) {
			mRespawnTime = 300;
		}
		else {
			mRespawnTime--;
		}

		if (mRespawnTime == 0) {
			Init(position);
		}

	}

}

void TestEnemy06::Collision(Player2& player, Map& map) {

	mColQuad = { mPosition,mRadius,mRadius };

	//�ˌ����ē��������ꍇ
	if (Collision::QuadToQuad(mColQuad, player.GetPlayerQuad()) == true && player.GetIsHeat() == true) {
		Novice::PlayAudio(mKnockSE, 0, 0.5f);
		//���ł���
		mIsAlive = false;
	}
	
	//���e�̉~�ɓ��������ꍇ
	if (Collision::CircleToQuad(player.GetBombCircle(), mColQuad) == true) {
		Novice::PlayAudio(mKnockSE, 0, 0.5f);
		//���ł���
		mIsAlive = false;
	}

	//�ʏ�̏�Ԃœ��������ꍇ
	if (Collision::QuadToQuad(mColQuad, player.GetPlayerQuad()) == true && player.GetIsHeat() == false) {
		//�q�b�g�t���O�𗧂Ă�
		player.SetIsHitTE6();
	}

}

void TestEnemy06::Move() {

	if (mSetTarget == true && mMoveTime != mRandMoveTime) {

		mMoveTime++;
		mPosition.x += mSpeed.x;
		mPosition.y += mSpeed.y;

		if (mMoveTime == mRandMoveTime) {
			mSetTarget = false;
			mStopTime = 0;
		}

	}

	

}
