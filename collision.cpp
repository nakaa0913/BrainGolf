//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "score.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int have_count = 0;
int haveplayer = -1;

//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(void)
{
	PLAYER *player = GetPlayer();		// �v���C���[�̃|�C���^�[��������
	ENEMY  *enemy = GetEnemy();		// �G�l�~�[�̃|�C���^�[��������
	BULLET *bullet = GetBullet();		// �o���b�g�̃|�C���^�[��������

//	// �G�Ƒ���L����(BB)
//	if (player[0].use == true)
//	{
//		for (int i = 0; i < ENEMY_MAX; i++)
//		{
//			if (enemy[i].use == false)
//				continue;
//
////			if (CollisionBB(player->pos, enemy[i].pos, D3DXVECTOR2(player->w, player->h), D3DXVECTOR2(enemy[i].w, enemy[i].h)))
//			if (CollisionBC(player->pos, enemy[i].pos, player->h/2, enemy[i].h/2))
//			{
//				// ����L�����N�^�[�͎���
//
//				// �G�L�����N�^�[�͓|�����
//				enemy[i].use = false;
//
//				// HP��������
//
//			}
//		}
//	}

	//// �e�ƓG(BB)
	//for (int i = 0; i < BULLET_MAX; i++)
	//{
	//	if (bullet[i].use == false)
	//		continue;

	//	for (int j = 0; j < ENEMY_MAX; j++)
	//	{
	//		if (enemy[j].use == false)
	//			continue;
	//			
	//		if (CollisionBB(bullet[i].pos, enemy[j].pos, D3DXVECTOR2(bullet[i].w, bullet[i].h), D3DXVECTOR2(enemy[j].w, enemy[j].h)))
	//		{
	//			bullet[i].use = false;		// �e�̏��ŏ������s��
	//			enemy[j].use = false;		// �G�͓|�����

	//			// �X�R�A�v�Z

	//			//break;					// �P�񓖂����ďI���̎��͂�����break����B�P�t���[�����̊ԗL���Ȃ�break���R�����g�ɂ���B
	//		}
	//	}
	//}

	

	// �v���C���[�ƒe�̔���
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == false)
			continue;

		for (int j = 0; j < PLAYER_MAX; j++)
		{
			if (player[j].use == false)
				continue;

			if (CollisionBB(bullet[i].pos, player[j].pos, D3DXVECTOR2(bullet[i].w, bullet[i].h), D3DXVECTOR2(player[j].w, player[j].h)))
			{

				if (player[j].catchwait <= 0)
				{
					bullet[i].use = false;		// �e�̏��ŏ������s��
					bullet[i].friction = 1.0f;
					player[j].have = true;		// �v���C���[�͒e������
					Truenow_have();
					haveplayer = j;

					have_count = 1;


					SetShotPower(0);			// �V���b�g�p���[�̕\����0�ɂ��Ă���

					// �S�Ẵv���C���[�̕K�v�ȗv�f��������
					for (int n = 0; n < PLAYER_MAX; n++)
					{
						player[n].angle = 0.0f;
						player[n].ShotPower = 0;
						player[n].ConfirmAngle = false;
						player[n].ConfirmCooltime = 10;
					}
					
				}

				// �X�R�A�v�Z

				//break;					// �P�񓖂����ďI���̎��͂�����break����B�P�t���[�����̊ԗL���Ȃ�break���R�����g�ɂ���B
			}
		}
	}

	//if (have_count >= 1)
	//{
	//	if (have_count >= 2)
	//	{
	//		have_count = 0;
	//		player[haveplayer].have = true;		// �v���C���[�͒e������
	//		Truenow_have();
	//	}
	//	else
	//		have_count++;
	//}

	// �{�X�ƒe(BC)

	// �����ƓG�̒e(BC)

	// ���S�������ԑJ��

	////���˕Ԃ�
	//for (int i = 0; i < BULLET_MAX; i++)
	//{
	//	//�E
	//	if (bullet[i].pos.x > 480.0f)
	//	{
	//		bullet[i].move.x *= -1;
	//	}
	//	//��
	//	if (bullet[i].pos.x < 80.0f)
	//	{
	//		bullet[i].move.x *= -1;
	//	}
	//	//��
	//	if (bullet[i].pos.y < 80.0f)
	//	{
	//		bullet[i].move.y *= -1;
	//	}
	//	//��
	//	if (bullet[i].pos.y > 720.0f)
	//	{
	//		bullet[i].move.y *= -1;
	//	}
	//}
}

//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X���̔���
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y���̔���
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//�S�Ă̏�����TRUE�Ȃ�q�b�g����
			return true;
		}
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistance�̃x�N�g�����𓾂�
	float length;
//	length = D3DXVec2Length(&vDistance);
	length = D3DXVec2LengthSq(&vDistance);

//	float size = size1 + size2;
	float size = (size1 + size2) * (size1 + size2);

	//1��2�̔��a�𑫂��Ĕ��肷��
	//�����̃x�N�g�����̕������������
	//�q�b�g���Ă���
	if (length < size)
	{
		return true;
	}

	return false;
}

bool CheckHit(D3DXVECTOR2 pos1, D3DXVECTOR2 size1, D3DXVECTOR2 pos2, D3DXVECTOR2 size2)
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