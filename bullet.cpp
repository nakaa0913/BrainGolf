//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "bullet.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "bg.h"
#include "scene.h"
#include "fade.h"
#include <math.h>
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static BULLET g_Bullet[BULLET_MAX];					// �o���b�g�\����



//double angle = 00.0;								//�����������p�x
//
//#define BULLET_ANGLE		(angle*D3DX_PI/180)		//�o���b�g�̊p�x(�����������p�x*��/180)


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(void)
{
	int texNo = LoadTexture("data/TEXTURE/bullet00.png");
	// �o���b�g�\���̂̏�����
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use   = false;
		g_Bullet[i].w     = 50.0f;
		g_Bullet[i].h     = 50.0f;
		g_Bullet[i].pos   = D3DXVECTOR2(300, 300.0f);
		g_Bullet[i].rot   = 0.0f;
		g_Bullet[i].texNo = texNo;

		g_Bullet[i].friction = 1.0f;
		g_Bullet[i].angle = 0.0f;
		g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);	// �ړ��ʂ�������
		g_Bullet[i].vector = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{


	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)	// ���̃o���b�g���g���Ă���H
		{								// Yes
			
			g_Bullet[i].friction *= 0.992;

			if (g_Bullet[i].friction < 0.2)
			{
				g_Bullet[i].friction = 0;
			}
			// �o���b�g�̈ړ�����
			g_Bullet[i].pos += g_Bullet[i].move * g_Bullet[i].friction;

			// ��ʊO�܂Ői�񂾁H
			if (g_Bullet[i].pos.y < (0.0f - g_Bullet[i].h/2))	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				g_Bullet[i].use = false;
				g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);
			}

			//
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 2)
			{
				GoalTrue();
				g_Bullet[i].use = false;
				g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);


				/*SceneTransition(SCENE_RESULT);*/
			}

			//
			if (GetKeyboardTrigger(DIK_R))
			{
				g_Bullet[i].use = false;
				g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)	// ���̃o���b�g���g���Ă���H
		{								// Yes
			//�o���b�g�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Bullet[i].pos.x;	// �o���b�g�̕\���ʒuX
			float py = g_Bullet[i].pos.y;	// �o���b�g�̕\���ʒuY
			float pw = g_Bullet[i].w;		// �o���b�g�̕\����
			float ph = g_Bullet[i].h;		// �o���b�g�̕\������
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			DrawSpriteColorRotate(g_Bullet[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Bullet[i].rot);
		}
	}

}


//=============================================================================
// �o���b�g�\���̂̐擪�A�h���X���擾
//=============================================================================
BULLET *GetBullet(void)
{
	return &g_Bullet[0];
}


//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBullet(D3DXVECTOR2 pos , float angle , int ShotPower)
{
	// ShotPower�ɂ��{��
	float ShotBairitu = 0.5f + (ShotPower / 100.0f);


	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == false)		// ���g�p��Ԃ̃o���b�g��������
		{
			g_Bullet[i].use = true;			// �g�p��Ԃ֕ύX����
			g_Bullet[i].pos = pos;			// ���W���Z�b�g
			// g_Bullet[i].rot = BULLET_ANGLE;	// �p�x���Z�b�g

			g_Bullet[i].vector = AngleToVector2(angle);	// �p�x����x�N�g����ݒ�
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * ShotBairitu * g_Bullet[i].vector.x, -BULLET_SPEED * ShotBairitu * g_Bullet[i].vector.y);	// �x�N�g������move��ݒ�

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

D3DXVECTOR2 AngleToVector2(float angle)
{
	float radian = angle * (D3DX_PI / 180);
	return  D3DXVECTOR2(cos(radian), sin(radian));
}