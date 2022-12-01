#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
struct Vec2
{
	/// �����o�ϐ�

	float x; //����x
	float y; //����y



/// �����o�֐�

	/// <summary>
	/// �f�t�H���g�R���X�g���N�^
	/// </summary>
	Vec2();


	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="nx"> x����</param>
	/// <param name="ny"> y����</param>
	 Vec2(float nx, float ny);

	/// <summary>
	/// ���������߂�֐�
	/// </summary>
	/// <returns>float�^</returns>
	float Length() const;

	/// <summary>
	/// ������2������߂�֐�
	/// </summary>
	/// <returns>float�^</returns>
	float LengthSquare() const;

	/// <summary>
	/// �����̃x�N�g���Ƃ̓���
	/// </summary>
	/// <param name="other"> Vec2</param>
	/// <returns>float�^</returns>
	 float Dot(const Vec2& other) const;

	/// <summary>
	/// �����̃x�N�g���Ƃ̊O��
	/// </summary>
	/// <param name="other"> Vec2</param>
	/// <returns>float�^</returns>
	 float Cross(const Vec2& other) const;

	/// <summary>
	/// �����̃x�N�g���Ƃ̋���
	/// </summary>
	/// <param name="other"> Vec2</param>
	/// <returns>float�^</returns>
	float DistanceFrom(const Vec2& other) const;

	/// <summary>
	/// ���K��
	/// </summary>
	/// <returns>Vec2�^</returns>
	Vec2 Normalized() const;

	/// <summary>
	/// �[���x�N�g���ł��邩
	/// </summary>
	/// <returns>true: 0�ł���   false: 0�łȂ�</returns>
	 bool isZero() const;

	/// <summary>
	/// �[���x�N�g���ɂ���
	/// </summary>
	void setZero();

	/// <summary>
	/// �x�N�g���̉�]
	/// </summary>
	/// <param name="t"> ��]�p�x���W�A��</param>
	/// <returns>Vec2�^</returns>
	Vec2 Rotation(float t) const;


	/// <summary>
	/// �P�� + 
	/// </summary>
	/// <returns>Vec2�^</returns>
	Vec2 operator +() const;

	/// <summary>
	/// �P�� - 
	/// </summary>
	/// <returns>Vec2�^</returns>
	 Vec2 operator -() const;

	/// <summary>
	/// 2�� + 
	/// </summary>
	/// <param name="other"> Vec2</param>
	/// <returns>Vec2�^</returns>
	 Vec2 operator +(const Vec2& other) const;

	/// <summary>
	/// 2�� - 
	/// </summary>
	/// <param name="other"> Vec2</param>
	/// <returns>Vec2�^</returns>
	 Vec2 operator -(const Vec2& other) const;

	/// <summary>
	/// 2�� * 
	/// </summary>
	/// <param name="s"> s�{</param>
	/// <returns>Vec2�^</returns>
	Vec2 operator *(float s) const;

	/// <summary>
	/// 2�� / 
	/// </summary>
	/// <param name="s">  1 / s�{</param>
	/// <returns>Vec2�^</returns>
	 Vec2 operator /(float s) const;

	/// <summary>
	/// ����������Z +=
	/// </summary>
	/// <param name="other"> Vec2</param>
	/// <returns>Vec2�^</returns>
	Vec2& operator +=(const Vec2& other);

	/// <summary>
	/// ����������Z -=
	/// </summary>
	/// <param name="other"> Vec2</param>
	/// <returns>Vec2�^</returns>
	Vec2& operator -=(const Vec2& other);

	/// <summary>
	/// ����������Z *= 
	/// </summary>
	/// <param name="s"> s�{</param>
	/// <returns>Vec2�^</returns>
	Vec2& operator *=(float s);

	/// <summary>
	/// ����������Z /= 
	/// </summary>
	/// <param name="s"> 1 / s�{</param>
	/// <returns>Vec2�^</returns>
	Vec2& operator /=(float s);

};

/// <summary>
/// Vec2 ����ɂ��� 2�� * 
/// </summary>
/// <param name="s"> s�{</param>
/// <param name="v"> Vec2</param>
/// <returns>Vec2�^</returns>
 Vec2 operator *(float s, const Vec2& v);

