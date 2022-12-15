#pragma once

#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")

// X�{�b�N�X�R���g���[���[�ł�����̂ŃR�����g�A�E�g�̐����͂���
// �ق��̃R���g���[���[�͕�����Ȃ��̂Ō��ؕK�{
// steam�Ȃǂ�pad�̐ݒ���s���Ă���ꍇ���̐ݒ�̂ق����D�悳��Ă��܂��̂ŃA�v���𗎂Ƃ��Ďg�p���Ă���������

class Gamepad {
public:
	// �������݂̃{�^��
	enum class Button {
		UP = 0, // �\���L�[��
		DOWN, // �\���L�[��
		LEFT, // �\���L�[��
		RIGHT, // �\���L�[�E
		START, // �����̎O�݂����Ȃ��
		BACK, // �l�p���d�Ȃ����悤�Ȃ��
		LEFT_THUMB, // ���X�e�B�b�N��������
		RIGHT_THUMB, // �E�X�e�B�b�N�������� 
		LEFT_SHOULDER, // LB
		RIGHT_SHOULDER, // RB
		A = 12, // A
		B, // B
		X, // X
		Y, // Y
	};

	// RT,LT
	enum class Triger {
		LEFT,
		RIGHT,
	};

	// �X�e�B�b�N
	enum class Stick {
		LEFT_X,
		LEFT_Y,
		RIGHT_X,
		RIGHT_Y
	};

private:
	inline Gamepad(){}
	inline ~Gamepad() {}

public:
	// ���͊֐�
	static void Input();

	// �������݂̃{�^���̏�Ԃ��擾
	static bool getButton(Button type);

	// �������݂̃{�^���̑O�t���[���̏�Ԃ��擾
	static bool getPreButton(Button type);

	// �������݂̃{�^�����������u��
	static bool Pushed(Button type);

	// �������݂̃{�^���𒷉���
	static bool LongPush(Button type);

	// �������݂̃{�^���𗣂����u��
	static bool Released(Button type);

	// �g���K�[�̃{�^���̏�Ԃ��擾
	static unsigned char getTriger(Triger type);

	// �X�e�B�b�N�̃{�^��
	static short getStick(Stick type);

	// �o�C�u���[�V����
	static void isVibration(const int& flag);

	// �f�o�b�O�p
	static void Draw();

private:
	static short preButton;
	static XINPUT_STATE state;
	static XINPUT_VIBRATION vibration;
};