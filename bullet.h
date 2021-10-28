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
#define BULLET_MAX		(50)		// �o���b�g��Max��
#define BULLET_SPEED	(4.0f)		// �o���b�g�̈ړ��X�s�[�h


// �o���b�g�\����a
struct BULLET
{
	bool					use;					// true:�g���Ă���  false:���g�p
	float					w, h;					// ���ƍ���
	D3DXVECTOR2				pos;					// �o���b�g�̍��W
	D3DXVECTOR2				nextpos;				// �o���b�g�̍��W
	D3DXVECTOR2				oldpos;					// �o���b�g�̍��W
	float					rot;					// �o���b�g�̉�]��
	D3DXVECTOR2				move;					// �o���b�g�̈ړ���
	int						texNo;					// ���Ԗڂ̃e�N�X�`���[���g�p����̂�
	float					friction;				// ��������
	float					angle;					// �p�x
	D3DXVECTOR2				vector;					// �x�N�g��
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(void);

D3DXVECTOR2 AngleToVector2(float angle);
void SetBullet(D3DXVECTOR2 pos, float angle, int ShotPower);