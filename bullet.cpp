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
#include "primitive.h"

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
	// �o���b�g�\���̂̏����� �ł����ۂ�SetBullet�ŌĂԂƂ��ɂ������Œl����������
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use   = false;
		g_Bullet[i].w     = 50.0f;
		g_Bullet[i].h     = 50.0f;
		g_Bullet[i].pos   = D3DXVECTOR2(300, 300.0f);
		g_Bullet[i].nextpos = g_Bullet[i].pos;
		g_Bullet[i].oldpos = g_Bullet[i].pos;
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
		{								
			// �O��̍��W�̕ۑ�
			g_Bullet[i].oldpos = g_Bullet[i].pos;


			// ���C�Ƃ���R�͂̌v�Z
			//g_Bullet[i].friction *= 0.992;
			g_Bullet[i].friction *= 0.9995;

			if (g_Bullet[i].friction < 0.2)
			{
				g_Bullet[i].friction = 0;
			}
			// �ړ���move�̕ϓ��̌v�Z
			g_Bullet[i].move = g_Bullet[i].move * g_Bullet[i].friction;

			// oldpos��move���̈ړ��𔽉f������nextpos�Ƃ���
			g_Bullet[i].nextpos = g_Bullet[i].oldpos + g_Bullet[i].move;

			// �}�b�v�Ƃ̓����蔻��̌v�Z�̉�����
			int hitcount = 0;			// �l�p�`�œ����蔻����v�Z�����Ƃ��ɓ������Ă���u���b�N�̐�
			int hitcountCorner = 0;		// �������Ă���u���b�N�̊p�̐�
			Float2 block_min  = { 999, 999 } ;
			Float2 block_max  = { -1, -1 };
			Float2 block_last = { -1, -1 };

			// HitBlockData�\���̂�HitBlockDatas��������,�����4���炢����������Ȃ��z��B
			HitBlockData2D HitBlockDatas2D[HitBlockData2DMax]{};		// �������錾
			for (int k = 0; k < HitBlockData2DMax; k++)					// ���g�����
			{
				HitBlockDatas2D[k].BlockPosX = -1;
				HitBlockDatas2D[k].BlockPosY = -1;
				HitBlockDatas2D[k].CornerNum = -1;
				HitBlockDatas2D[k].isUse = false;
			}


			// �}�b�v�Ƃ̓����蔻�菈��
			for (int y = 0; y < MAP_Y; y++)
			{
				for (int x = 0; x < MAP_X; x++)
				{
					// ���̃u���b�N�������蔻�肪����u���b�N���ǂ������ׂ�a
					int BlockData = CheckBlockdata(x, y);
					// ���̃u���b�N�f�[�^�� 1 �������瓖���蔻�肪����̂Œ��œ����蔻��̌v�Z���A�������Ă���ʂ�1�ʂɌ��߂�
					if (BlockData == 1)
					{

					}
					
				}
			}

			





						// �}�b�v�Ƃ̓����蔻�菈��
			//if (g_Bullet[i].pos.y < (0.0f - g_Bullet[i].h/2))	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			//{
			//	g_Bullet[i].use = false;
			//	g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);
			//}

			// �S�[���ɓ��������̏���
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 2)
			{
				// �S�[���ɓ��������̏���
				GoalTrue();
				g_Bullet[i].use = false;


				/*SceneTransition(SCENE_RESULT);*/
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 3)
			{
				// �����ɏ�������̏���
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].friction = 0.999;
					/*g_Bullet[i].vector = AngleToVector2();*/
					g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * 2 * g_Bullet[i].vector.x,
						-BULLET_SPEED * 2 * g_Bullet[i].vector.y);

					g_Bullet[i].accboardcool = 60;

				}
			}
			if (g_Bullet[i].accboardcool > 0)
				g_Bullet[i].accboardcool--;

			//���[�v
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 4)
			{
				if (g_Bullet[i].warpcool <= 0)
				{
					for (int y = 0; y < MAP_Y; y++)
					{
						for (int x = 0; x < MAP_X; x++)
						{
							// ���̃u���b�N�������蔻�肪����u���b�N���ǂ������ׂ�a
							int BlockData = CheckBlockdata(x, y);
							// ���̃u���b�N�f�[�^�� 1 �������瓖���蔻�肪����̂Œ��œ����蔻��̌v�Z���A�������Ă���ʂ�1�ʂɌ��߂�
							if (BlockData == 5)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 60;

							}

						}
					}
				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 5)
			{
				if (g_Bullet[i].warpcool <= 0)
				{
					for (int y = 0; y < MAP_Y; y++)
					{
						for (int x = 0; x < MAP_X; x++)
						{
							// ���̃u���b�N�������蔻�肪����u���b�N���ǂ������ׂ�a
							int BlockData = CheckBlockdata(x, y);
							// ���̃u���b�N�f�[�^�� 1 �������瓖���蔻�肪����̂Œ��œ����蔻��̌v�Z���A�������Ă���ʂ�1�ʂɌ��߂�
							if (BlockData == 4)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 60;
							}

						}
					}
				}
			}
			if (g_Bullet[i].warpcool > 0)
				g_Bullet[i].warpcool--;

			// �Ŋ���pos��nextpos�𔽉f������
			g_Bullet[i].pos = g_Bullet[i].nextpos;

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

			g_Bullet[i].vector = AngleToVector2(angle);	// �p�x����x�N�g����ݒ�
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * ShotBairitu * g_Bullet[i].vector.x,
										  -BULLET_SPEED * ShotBairitu * g_Bullet[i].vector.y);	// �x�N�g������move��ݒ�

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

D3DXVECTOR2 AngleToVector2(float angle)
{
	float radian = angle * (D3DX_PI / 180);
	return  D3DXVECTOR2(cos(radian), sin(radian));
}