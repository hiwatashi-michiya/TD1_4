#pragma once
#include <Windows.h>
#include <Xinput.h>

#pragma comment (lib, "xinput.lib")

// �R���g���[���̍ő�ڑ��� 1�`4
#define MAX_CONTROLLER_NUM 1

// Xinput�R���g���[���[
class Controller
{

public:
	// �{�^���R�[�h
	enum Button {
		bUP			= 0x0001,		// ��
		bDOWN		= 0x0002,		// ��
		bLEFT		= 0x0004,		// ��
		bRIGHT		= 0x0008,		// �E
		bSTART		= 0x0010,		// ���j���[
		bBACK		= 0x0020,		// �r���[
		lTHUMB		= 0x0040,		// L3
		rTHUMB		= 0x0080,		// R3
		lSHOULDER	= 0x0100,		// L1
		rSHOULDER	= 0x0200,		// R1
		bA			= 0x1000,		// A
		bB			= 0x2000,		// B
		bX			= 0x4000,		// X
		bY			= 0x8000,		// Y
		lTrigger	= 0x000F0000,	// L2
		rTrigger	= 0x00FF0000,	// R2
	};

	// �X�e�B�b�N�̌���
	enum StickDirection {
		lsdUP,		// LEFT STICK DIRECTION UP
		lsdDOWN,	// LEFT STICK DIRECTION DOWN
		lsdRIGHT,	// LEFT STICK DIRECTION RIGHT
		lsdLEFT,	// LEFT STICK DIRECTION LEFT
		rsdUP,		// RIGHT STICK DIRECTION UP
		rsdDOWN,	// RIGHT STICK DIRECTION DOWN
		rsdRIGHT,	// RIGHT STICK DIRECTION RIGHT
		rsdLEFT		// RIGHT STICK DIRECTION LEFT
	};

	struct StickMagnitude
	{
		int x;
		int y;
	};

private:

	static XINPUT_STATE state[MAX_CONTROLLER_NUM];			// ���݂̓��͏��
	static XINPUT_STATE previousState[MAX_CONTROLLER_NUM];	// �O��̓��͏��

	static BYTE triggerDeadZone[MAX_CONTROLLER_NUM];		// �g���K�[�̃f�b�h�]�[��

	static SHORT leftStickDeadZone[MAX_CONTROLLER_NUM];		// ���X�e�B�b�N�̃f�b�h�]�[��
	static SHORT rightStickDeadZone[MAX_CONTROLLER_NUM];	// �E�X�e�B�b�N�̃f�b�h�]�[��

	static int number; // �R���g���[���[�̐�

public:

	/// <summary>
	/// ���ׂẴR���g���[���[�̏�Ԃ��Z�b�g����
	/// </summary>
	/// <returns>�ڑ���</returns>
	static void SetState();

	/// <summary>
	/// ���ݎg���Ă��邩
	/// </summary>
	static bool IsUse();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// �g���K�[�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="deadzone">�f�b�h�]�[���@�F�@0�`255</param>
	/// <returns>�����@or�@���s</returns>
	static bool SetTriggerDeadZone(int number, int deadzone);

	/// <summary>
	/// �E�X�e�B�b�N�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="deadzone">�f�b�h�]�[���@�F�@0�`32768</param>
	/// <returns>�����@or�@���s</returns>
	static bool SetRightStickDeadZone(int number, int deadzone);

	/// <summary>
	/// ���X�e�B�b�N�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="deadzone">�f�b�h�]�[���@�F�@0�`32768</param>
	/// <returns>�����@or�@���s</returns>
	static bool SetLeftStickDeadZone(int number, int deadzone);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// �{�^���������ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="button">�{�^���ԍ�</param>
	/// <returns></returns>
	static bool IsTriggerButton(int number, Button button);

	/// <summary>
	/// �{�^����������Ă��鎞
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="button">�{�^���ԍ�</param>
	/// <returns></returns>
	static bool IsPressedButton(int number, Button button);

	/// <summary>
	/// �{�^���������ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="button">�{�^���ԍ�</param>
	/// <returns></returns>
	static bool IsReleaseButton(int number, Button button);

	/// <summary>
	/// �X�e�B�b�N���w��̌����ɓ|���ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="direction">�X�e�B�b�N����</param>
	/// <returns></returns>
	static bool IsStickDirection(int number, StickDirection direction);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// �E�g���K�[
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="out">0�`255</param>
	/// <returns>�����@or�@���s</returns>
	static bool GetRightTrigger(int number, int& out);

	/// <summary>
	/// ���g���K�[
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="out">0�`255</param>
	/// <returns>�����@or�@���s</returns>
	static bool GetLeftTrigger(int number, int& out);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// �E�X�e�B�b�N
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="outx">X��</param>
	/// <param name="outy">Y��</param>
	/// <returns>�����@or�@���s</returns>
	static bool GetRightStick(int number, int& outx, int& outy);

	static bool GetRightStick(int number, StickMagnitude& out);

	/// <summary>
	/// ���X�e�B�b�N
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="outx">X��</param>
	/// <param name="outy">Y��</param>
	/// <returns>�����@or�@���s</returns>
	static bool GetLeftStick(int number, int& outx, int& outy);

	static bool GetLeftStick(int number, StickMagnitude& out);

	static int GetConnectionNumber() { return number; }

	static bool IsUseController();

private:

	Controller() = delete;
	Controller(const Controller&) = delete;
	void operator =(const Controller&) = delete;

};