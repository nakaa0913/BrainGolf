///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////����̃v���~�e�B�u�B.cpp	�֗��Ȏ���֐������Ă��
////2021/10/28	�ēc���m
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <math.h>
#include "primitive.h"




// 2�_�Ԃ̋��������߂�float�^�ŕԂ��֐�
float CalculationDistance(float point1pos1, float point1pos2, float point2pos1, float point2pos2)
{

	float a = point1pos1 - point2pos1;
	float b = point1pos2 - point2pos2;
	float c = sqrt(a * a + b * b);

	return c;
}
// 2�_�Ԃ̋��������߂�    �ǂ����ł���������g���Ă�B
//float CalculationDistance(float obj1pos1, float obj1pos2, float obj2pos1, float obj2pos2)
//{
//	float distance = sqrt(pow(obj1pos1 - obj2pos1, 2) +
//						  pow(obj1pos2 - obj2pos2, 2));
//	return distance;
//}


// 1�̓_��1�̉~�̓����蔻��B�_�Ɖ~�̌��_�̋���<=�~�̔��a�Ȃ瓖�����Ă���B
bool OnCollisionPointAndCircle(Float2 point, Circle2D circle)
{
	float a = point.x - circle.x;
	float b = point.y - circle.y;
	float c = sqrt(a * a + b * b);

	if (c <= circle.r)
	{
		return true;
	}
	return false;
}

// peace��all�̂ǂꂾ���̊������Ԃ��B��{peace�̕����������̂�0~0.999���Ԃ�B1�œ����傫���Bmagnification�͌v�Z���ʂ����̕��{�ɂ��邱�Ƃ��ł���B�덷�̌v�Z�r����10000�{�Ƃ����Ă���g�B�g��Ȃ��ꍇ��1
float CalculationRatio(float peace, float all, int magnification)
{
	float ratio;

	if (magnification != 1)
		ratio = magnification * peace / all;
	else
		ratio = peace / all;

	return ratio;
}

//// ��萳�m�ȉ~�̓����蔻������߂�֐��B�~�̌��_�̍��W�Ɠ������Ă���_�̍��W���狗�����v�Z���āA10��������move�̒�����ł��߂��������W��Ԃ�
//Float2 MoreAccurateCircleCollision(float OriginX, float OriginY, float radius, float pointposX, float pointposY, Float2 onemove, int divnum)
//{
//	Float2 BestPos = { OriginX, OriginY };
//
//	// move��divnum�ɕ����čl����B�����قǐ��m���������͏d���Ȃ邩�瑽���Ă�10���炢����������
//	for (int i = 0; i < divnum; i++)
//	{
//		BestPos.x = BestPos.x + onemove.x;
//		BestPos.y = BestPos.y + onemove.y;
//
//		float distance = CalculationDistance(BestPos.x, BestPos.y, pointposX, pointposY);
//		if (distance >= radius)
//			return BestPos;
//	}
//
//	Float2 BudPos = { -1.0f, -1.0f };
//
//	return BudPos;
//}

// ��萳�m�ȉ~�̓����蔻������߂�֐��B�~�̌��_�̍��W�Ɠ������Ă���_�̍��W���狗�����v�Z���āA10��������move�̒�����ł��߂��������W��Ԃ�
Float2 MoreAccurateCircleCollision(float OriginX, float OriginY, float radius, float pointposX, float pointposY, Float2 onemove, int divnum)
{
	// ��̊֐��̓񕪊򌟍��o�[�W�����I�����̑������������̂������B100�Ƃ��ŕ������Ă�����Ȃɏd���Ȃ��I

	Float2 BestPos = { OriginX, OriginY };

	int min = 0;
	int max = divnum;
	int middle;

	while (min <= max) 
	{
		middle = (min + max) / 2;

		if (CalculationDistance(OriginX + onemove.x * middle, OriginY + onemove.y * middle, pointposX, pointposY) >= radius)
		{
			if (CalculationDistance(OriginX + onemove.x * (middle - 1), OriginY + onemove.y * (middle - 1), pointposX, pointposY) < radius)
			{
				BestPos.x = BestPos.x + onemove.x * middle;
				BestPos.y = BestPos.y + onemove.y * middle;
				return BestPos;
			}
			else
			{
				max = middle - 1;
			}
		}
		else
		{
			min = middle + 1;
		}
	}

	Float2 BudPos = { -1.0f, -1.0f };

	return BudPos;
}

// �^�񒆂ł͂Ȃ��A���[�A��[�̍��W�������ŌĂԁB
bool CheckHit2DBoxBox(Float2 pos1, Float2 size1, Float2 pos2, Float2 size2)
{
	float L1 = pos1.x;      // ��
	float R1 = pos1.x + size1.x; // �E(��+����)
	float L2 = pos2.x;      // ��
	float R2 = pos2.x + size2.x; // �E(��+����)

	if (R1 < L2) return false; //< ������������Ă邱�Ƃɂ���
	if (R2 < L1) return false; //< ������������Ă邱�Ƃɂ���

	float U1 = pos1.y;			 // ��
	float D1 = pos1.y + size1.y; // ��(��+�c��)
	float U2 = pos2.y;			// ��
	float D2 = pos2.y + size2.y; // ��(��+�c��)

	if (D1 < U2) return false; //< ������������Ă邱�Ƃɂ���
	if (D2 < U1) return false; //< ������������Ă邱�Ƃɂ���

	// ����ȊO�̏ꍇ�͓������Ă���
	return true;
}

double DegreeToRadian(double degree)
{
	// �p�x��360�x�ȏ�̏ꍇ�A0~360�x�ɂȂ�悤�ɒ���
	if (degree >= 360)
	{
		while (degree >= 360)
		{
			degree -= 360.0;
		}
	}
	// �p�x��0�x�����̏ꍇ�A0~360�x�ɂȂ�悤�ɒ���
	if (degree < 0)
	{
		while (degree < 0)
		{
			degree += 360.0;
		}
	}

	// �p�x * 3.14 / 180.0 �Ŋp�x���烉�W�A���ɕϊ��ł���
	return  degree * PI / 180.0;
}

double RadianToDegree(double radian)
{
	// atan2�̏ꍇ�B0�x�̃X�^�[�g�ʒu���甽���v����0~3.14~-3.14~0�ƂȂ�B
	// �܂����W�A�����}�C�i�X�������ꍇ�̒���
	if (radian < 0)
		radian += PI * 2;

	// ���W�A�� * 180.0 / 3.14 �Ń��W�A������p�x�ɕϊ��ł���
	return  radian * 180.0 / PI;
}

// ���͂����p�x�̐^�t�̊p�x��Ԃ�(270�x��������90�x)
double ReverseDegree(double degree)
{

	double new_degree = degree + 180.0;


	// �p�x��360�x�ȏ�̏ꍇ�A0~360�x�ɂȂ�悤�ɒ���
	if (new_degree >= 360)
	{
		while (new_degree >= 360)
		{
			new_degree -= 360.0;
		}
	}
	// �p�x��0�x�����̏ꍇ�A0~360�x�ɂȂ�悤�ɒ���
	if (new_degree < 0)
	{
		while (new_degree < 0)
		{
			new_degree += 360.0;
		}
	}

	return  new_degree;
}

// 2�̓_����@�̓_����A���������̃��W�A�����v�Z����
double CalculateRadianFrom2Points(double point1x, double point1y, double point2x, double point2y)
{
	double distance_x = point2x - point1x;
	double distance_y = point2y - point1y;

	double radian = atan2(distance_y, distance_x);

	if (radian < 0)
		radian += PI * 2;

	int asdasd = 5;

	return radian;
}

// ���W�A����Y�������]������(X���Ŕ��])
double InversionYRadian(double radian)
{
	double newradian = -radian;

	if (newradian < 0)
		newradian += PI * 2;

	int asdads = 5;

	return newradian;
}