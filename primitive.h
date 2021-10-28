///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////����̃v���~�e�B�u�B.h
////2021/10/28	�ēc���m
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __IKD_OX_PRIMITIVE_H__
#define __IKD_OX_PRIMITIVE_H__


#include <math.h>

#define _OX_EPSILON_	0.000001f	// �덷

// ======================================  2D�n =======================================
// 2����float
struct Float2 {
	float x, y;

	//Float2() {}
	//Float2(float x, float y) : x(x), y(y) {}
	//~Float2() {}

	//Float2 operator +(const Float2& r) const {
	//	return Float2(x + r.x, y + r.y);
	//}

	//Float2 operator -(const Float2& r) const {
	//	return Float2(x - r.x, y - r.y);
	//}

	//Float2 operator -() const {
	//	return Float2(x * -1.0f, y * -1.0f);
	//}

	//Float2 operator *(const Float2& r) const {
	//	return Float2(x * r.x, y * r.y);
	//}

	//Float2 operator /(const Float2& r) const {
	//	return Float2(x / r.x, y / r.y);
	//}

	//Float2 operator *(float r) const {
	//	return Float2(x * r, y * r);
	//}

	//Float2 operator /(float r) const {
	//	return Float2(x / r, y / r);
	//}

	//friend Float2 operator *(float l, const Float2& r) {
	//	return Float2(r.x * l, r.y * l);
	//}

	//friend Float2 operator /(float l, const Float2& r) {
	//	return Float2(r.x / l, r.y / l);
	//}

	//float dot(const Float2& r) const {
	//	return x * r.x + y * r.y;
	//}

	//float cross(const Float2& r) const {
	//	return x * r.y - y * r.x;
	//}

	//float length() const {
	//	return sqrtf(lengthSq());
	//}

	//float lengthSq() const {
	//	return x * x + y * y;
	//}

	//void norm() {
	//	const float len = length();
	//	if (len > 0.0f) {
	//		x /= len;
	//		y /= len;
	//	}
	//}

	//Float2 getNorm() const {
	//	const float len = length();
	//	if (len > 0.0f) {
	//		return Float2(x / len, y / len);
	//	}
	//	return Float2(0.0f, 0.0f);
	//}
};


// �_�f�[�^ corner= -1:Nohit,0:����,1:�E��,2:����,3:�E��  Float2 �ƈႢ�A�ǂ��̊p���̏������邽�߂�int corner�����݂���
typedef struct Point2D
{
	Float2 pos;
	//Pos pos;
	// float x, y;
    
    // ���ŏ�����l��n�����Ƃɂ���āA�ȗ��\�����ƂȂ�B�ȗ������ꍇ����-1���n�����
    int corner = -1;

	//Point2D() {}
	//Point2D(const Float2& pos, int corner = -1) {}
	//~Point2D() {}
} ;

// �~�f�[�^ Float2�Ɖ~�̔��a
typedef struct Circle2D
{
	Float2 pos;
	float r;	// ���a

	//Circle2D() {}
	//Circle2D(const Float2& pos, float r) {}
	//~Circle2D() {}
};

// ======================================  3D�n =======================================

// 3����float
struct Float3 {
	float x, y, z;

	//Float3() {}
	//Float3(float x, float y, float z) : x(x), y(y), z(z) {}
	//~Float3() {}

	//Float3 operator +(const Float3& r) const {
	//	return Float3(x + r.x, y + r.y, z + r.z);
	//}

	//Float3 operator -(const Float3& r) const {
	//	return Float3(x - r.x, y - r.y, z - r.z);
	//}

	//Float3 operator -() const {
	//	return Float3(x * -1.0f, y * -1.0f, z * -1.0f);
	//}

	//Float3 operator *(const Float3& r) const {
	//	return Float3(x * r.x, y * r.y, z * r.z);
	//}

	//Float3 operator /(const Float3& r) const {
	//	return Float3(x / r.x, y / r.y, z / r.z);
	//}

	//Float3 operator *(float r) const {
	//	return Float3(x * r, y * r, z * r);
	//}

	//Float3 operator /(float r) const {
	//	return Float3(x / r, y / r, z / r);
	//}

	//friend Float3 operator *(float l, const Float3& r) {
	//	return Float3(r.x * l, r.y * l, r.z * l);
	//}

	//friend Float3 operator /(float l, const Float3& r) {
	//	return Float3(r.x / l, r.y / l, r.z / l);
	//}

	//float dot(const Float3& r) const {
	//	return x * r.x + y * r.y + z * r.z;
	//}

	//Float3 cross(const Float3& r) const {
	//	return Float3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
	//}

	//float length() const {
	//	return sqrtf(lengthSq());
	//}

	//float lengthSq() const {
	//	return x * x + y * y + z * z;
	//}

	//void norm() {
	//	const float len = length();
	//	if (len > 0.0f) {
	//		x /= len;
	//		y /= len;
	//		z /= len;
	//	}
	//}

	//Float3 getNorm() const {
	//	const float len = length();
	//	if (len > 0.0f) {
	//		return Float3(x / len, y / len, z / len);
	//	}
	//	return Float3(0.0f, 0.0f, 0.0f);
	//}
};

// �_�f�[�^ corner= -1:Nohit,0:����,1:�E��,2:����,3:�E��  Float3 �ƈႢ�A�ǂ��̊p���̏������邽�߂�int corner�����݂���
typedef struct Point3D
{
	Float3 pos;

	// ���ŏ�����l��n�����Ƃɂ���āA�ȗ��\�����ƂȂ�B�ȗ������ꍇ����-1���n�����
	int corner = -1;

	//Point3D() {}
	//Point3D(const Float3& pos, int corner = -1) {}
	//~Point3D() {}
} ;

// �� �f�[�^ Float3�Ƌ��̔��a
typedef struct Sphere {
	Float3 pos;	// ���_�̍��W
	float r;	// ���a

	//Sphere() {}
	//Sphere(const Float3& pos, float r) {}
	//~Sphere() {}
} ;

// ======================================================�֐���`=============================================
float CalculationRatio(float peace, float all, int magnification);
bool OnCollisionPointAndCircle(Float2 point, Circle2D circle);
float CalculationDistance(float point1pos1, float point1pos2, float point2pos1, float point2pos2);
Float2 MoreAccurateCircleCollision(float OriginX, float OriginY, float radius, float pointposX, float pointposY, Float2 onemove, int divnum);

#endif