//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_MAX		(3)		// �o���b�g��Max��
#define BULLET_SPEED	(4.0f)		// �o���b�g�̈ړ��X�s�[�h
#define COL_COOL		(3)			// CollicionCool�̒���


// �o���b�g�\����
struct BULLET
{
	bool					use;					// true:�g���Ă���  false:���g�p
	float					w, h;					// ���ƍ���
	D3DXVECTOR2				pos;					// �o���b�g�̍��W
	D3DXVECTOR2				nextpos;				// �o���b�g�̍��W
	D3DXVECTOR2				oldpos;					// �o���b�g�̍��W

	float					flying_height;			// ���̔��ł��鍂���B(3�����ł�����y���̍���)
	bool					on_the_ground;			// �n�ʂɃ{�[�������Ă����Ԃ��ǂ���

	D3DXVECTOR2				drawpos;				// �\������ۂ̍��W
	D3DXVECTOR2				drawsize;				// �\������ۂ̃T�C�Y

	float					rot;					// �o���b�g�̉�]��
	D3DXVECTOR2				move;					// �o���b�g�̈ړ���
	int						texNo;					// ���Ԗڂ̃e�N�X�`���[���g�p����̂�
	float					friction;				// ��������
	float					angle;					// �p�x
	D3DXVECTOR2				vector;					// �x�N�g��
	float					shotpower;				// ���̗͂̔{��
	int						CollicionCool;			// �����u���b�N�ɓ����������̃N�[���^�C��
	int						accboardcool;			// �����̃N�[���^�C��
	int						warpcool;				// ���[�v�̃N�[���^�C��
	int						shottime;				// �e�����˂���Ă���̎���
	int						collisiontime;			// �e���������Ă��鎞��

	int						club_pattern;			// ���̔�ѕ�

};

struct SHADOWBULLET
{
	float					w, h;					// ���ƍ���
	D3DXVECTOR2				pos;					// �o���b�g�̍��W

	D3DXVECTOR2				drawpos;				// �\������ۂ̍��W
	D3DXVECTOR2				drawsize;				// �\������ۂ̃T�C�Y

	int						tex;					// ���Ԗڂ̃e�N�X�`���[���g�p����̂�
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET* GetBullet(void);

D3DXVECTOR2 AngleToVector2(float angle);
void SetBullet(D3DXVECTOR2 pos, float angle, int ShotPower, int club_pattern);
float CalculateCornerDistanceX(int CornerNum, float size_x, float size_y);
float CalculateCornerDistanceY(int CornerNum, float size_x, float size_y);
void CalculateNewVecAng(int i, float bulletposX, float bulletposY, float CornerPosX, float CornerPosY);
void InversionVecAng(int i, int XorY);
void DrawBulletSpecifyNum(int i);
float Bounce(float maxhight, int nowframe, int bounce1frame, int bounce2frame, int bounce3frame, int bounce4frame);