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
#include "collision.h"

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
	int texNo = LoadTexture("data/TEXTURE/bullet/ao.png");
	// �o���b�g�\���̂̏����� �ł����ۂ�SetBullet�ŌĂԂƂ��ɂ������Œl����������
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use = false;
		g_Bullet[i].w = 20.0f;
		g_Bullet[i].h = 20.0f;
		g_Bullet[i].pos = D3DXVECTOR2(300, 300.0f);
		g_Bullet[i].nextpos = g_Bullet[i].pos;
		g_Bullet[i].oldpos = g_Bullet[i].pos;

		g_Bullet[i].drawpos = g_Bullet[i].pos;
		g_Bullet[i].drawsize = D3DXVECTOR2(g_Bullet[i].w, g_Bullet[i].h);

		g_Bullet[i].rot = 0.0f;
		g_Bullet[i].texNo = texNo;

		g_Bullet[i].friction = 1.0f;
		g_Bullet[i].angle = 0.0f;
		g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);	// �ړ��ʂ�������
		g_Bullet[i].vector = D3DXVECTOR2(1.0f, 1.0f);

		g_Bullet[i].CollicionCool = 0;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	UnloadTexture("data/TEXTURE/bullet/ao.png");
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
			g_Bullet[i].friction = 0.9815;

			if (g_Bullet[i].shotpower < 0.14f)
			{
				g_Bullet[i].shotpower = 0;
			}
			// �V���b�g�p���[�ɒ�R�͂������ė͂��キ����
			g_Bullet[i].shotpower = g_Bullet[i].shotpower * g_Bullet[i].friction;

			// �ړ���move�̍X�V
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.x,
				-BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.y);	// �x�N�g������move��ݒ�



			// oldpos��move���̈ړ��𔽉f������nextpos�Ƃ���
			g_Bullet[i].nextpos = g_Bullet[i].oldpos + g_Bullet[i].move;


			

			// �}�b�v�Ƃ̓����蔻��̌v�Z�̉�����
			int hitcount = 0;			// �l�p�`�œ����蔻����v�Z�����Ƃ��ɓ������Ă���u���b�N�̐�
			int hitcountCorner = 0;		// �������Ă���u���b�N�̊p�̐�
			D3DXVECTOR2 block_min = D3DXVECTOR2(999, 999);
			D3DXVECTOR2 block_max = D3DXVECTOR2(-1, -1);
			D3DXVECTOR2 block_last = D3DXVECTOR2(-1, -1);

			// HitBlockData�\���̂�HitBlockDatas��������,�����4���炢����������Ȃ��z��B
			HitBlockData2D HitBlockDatas2D[HitBlockData2DMax]{};		// �������錾
			for (int k = 0; k < HitBlockData2DMax; k++)					// ���g�����
			{
				HitBlockDatas2D[k].BlockPosX = -1;
				HitBlockDatas2D[k].BlockPosY = -1;
				HitBlockDatas2D[k].CornerNum = -1;
				HitBlockDatas2D[k].isUse = false;
			}

			// CollicionCool���Ȃ瓖���蔻��̔�����s��Ȃ�
			if (g_Bullet[i].CollicionCool <= 0)
			{


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
							// �u���b�N��4���̍��W�̕ۑ�
							D3DXVECTOR2 LU_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X - (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y - (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 RU_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y - (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 LD_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X - (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 RD_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));

							// �ŏ��͎l�p�œ����蔻��𒲂ׂ�A�K�{�B�������瓖�����Ă�ł��낤���Ƃ𒲂ׂ�B
							if (CheckHit(D3DXVECTOR2(g_Bullet[i].nextpos.x - (g_Bullet[i].w / 2), g_Bullet[i].nextpos.y - (g_Bullet[i].h / 2)), D3DXVECTOR2(g_Bullet[i].w, g_Bullet[i].h),
								D3DXVECTOR2(x * MAP_CHIP_SIZE_X, y * MAP_CHIP_SIZE_Y), D3DXVECTOR2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y)) == true
								)
							{
								// �q�b�g�J�E���g�𑝂₵�A�������Ă���u���b�N�̍ő�l�ƍŒ�l��ۑ�����
								hitcount++;
								block_last.x = x;
								block_last.y = y;

								if (x > block_max.x) block_max.x = x;
								if (x < block_min.x) block_min.x = x;
								if (y > block_max.y) block_max.y = y;
								if (y < block_min.y) block_min.y = y;

								// �l���͂܂��킩��Ȃ����Ǔ������Ă���̂œ���Ă���
								for (int k = 0; k < HitBlockData2DMax; k++)			// �g���Ă��Ȃ����̂ɂ���Ă���
								{
									if (HitBlockDatas2D[k].isUse == false)
									{
										HitBlockDatas2D[k].BlockPosX = x;
										HitBlockDatas2D[k].BlockPosY = y;
										// HitBlockDatas2D[k].CornerNum = corner;
										// HitBlockDatas2D[k].isUse = true;		// �g���Ă��Ԃɂ͂܂����Ȃ��B
										break;									// �o�^�����̂Ŕ�����
									}
								}

								// �~�̓����蔻��ƁA�l�p�̂ǂ��ɓ������Ă��邩�𒲂ׂ�
								for (int corner = 0; corner < 4; corner++)
								{
									D3DXVECTOR2 point_pos = D3DXVECTOR2(0.0f, 0.0f);
									if (corner == 0)
									{
										point_pos = LU_block;
									}
									if (corner == 1)
									{
										point_pos = RU_block;
									}
									if (corner == 2)
									{
										point_pos = LD_block;
									}
									if (corner == 3)
									{
										point_pos = RD_block;
									}

									// �~�̏��̐���(Bullet)
									Circle2D BulletCircle = {
										g_Bullet[i].nextpos.x,
										g_Bullet[i].nextpos.y,
										g_Bullet[i].w / 2,		// ���a�����牡���̔���
									};
									// �_�̏��̐���(�u���b�N�̊p)
									Float2 CornerPoint = {
										point_pos.x,
										point_pos.y,
									};
									// �~�ƂS�p�̂ǂ����������Ă��邩���ׂ�
									if (OnCollisionPointAndCircle(CornerPoint, BulletCircle) == true)
									{
										// ChangeMapdata(2, x, y);

										// �~�̓����蔻��œ������Ă���ꍇ
										// �������Ă���u���b�N�̕ۑ�
										hitcountCorner++;

										for (int k = 0; k < HitBlockData2DMax; k++)			// �g���Ă��Ȃ����̂ɂ���Ă���
										{
											if (HitBlockDatas2D[k].isUse == false)
											{
												HitBlockDatas2D[k].BlockPosX = x;
												HitBlockDatas2D[k].BlockPosY = y;
												HitBlockDatas2D[k].CornerNum = corner;
												HitBlockDatas2D[k].isUse = true;			// �g���Ă��Ԃɂ���
												break;									// �o�^�����̂Ŕ�����
											}
										}







									}
								}

							}

						}

					}
				}
			}

			// �~�̏��̐����v�Z�p(Bullet)
			Circle2D BulletCircle = {
				g_Bullet[i].nextpos.x,
				g_Bullet[i].nextpos.y,
				g_Bullet[i].w / 2,		// ���a�����牡���̔���
			};

			// �������Ă���u���b�N��0�ȏォ��1���P�̂̏ꍇ�̏���
			if (hitcount == 1)
			{
				int OriginLengthAndWidthPos = -1;					// -1:Nohit,:0:��,1:�E,2:��,3:��,�~�̌��_���c��4�����̂ǂ��Ɉʒu���邩
				int OriginCornerPos = -1;							// -1:Nohit,:0:����,1:�E��,2:����,3:�E��,�~�̌��_���΂�4�����̂ǂ��Ɉʒu���邩
				// �~�̌��_�̏ꏊ�ɂ���ď�����ς���
				// �@�~�̌��_���u���b�N�̏c��4�����̂ǂ��Ɉʒu���邩�̏���
				if (BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f)
				{
					if (BulletCircle.y > HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f && BulletCircle.y < HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginLengthAndWidthPos = 0;
				}
				if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y > HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f && BulletCircle.y < HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginLengthAndWidthPos = 1;
				}
				if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y < HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f)
						OriginLengthAndWidthPos = 2;
				}
				if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y > HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginLengthAndWidthPos = 3;
				}
				// �A�~�̌��_���u���b�N�̎΂�4�����̂ǂ��Ɉʒu���邩�̏���
				if (BulletCircle.x <= HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f)
				{
					if (BulletCircle.y <= HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f)
						OriginCornerPos = 0;
				}
				if (BulletCircle.x >= HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y <= HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f)
						OriginCornerPos = 1;
				}
				if (BulletCircle.x <= HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f)
				{
					if (BulletCircle.y >= HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginCornerPos = 2;
				}
				if (BulletCircle.x >= HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y >= HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginCornerPos = 3;
				}

				// �v�Z��nextpos��ς���
				if (OriginLengthAndWidthPos != -1)
				{
					if (OriginLengthAndWidthPos == 0)
					{
						g_Bullet[i].nextpos.x = HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f - (g_Bullet[i].w / 2);
						////g_Bullet[i].move.x *= -1;
						//g_Bullet[i].vector.x *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, HitBlockDatas2D[0].BlockPosX* MAP_CHIP_SIZE_X + 0.0f, g_Bullet[i].nextpos.y);
						InversionVecAng(i, 0);

					}
					if (OriginLengthAndWidthPos == 1)
					{
						g_Bullet[i].nextpos.x = HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X + (g_Bullet[i].w / 2);
						////g_Bullet[i].move.x *= -1;
						//g_Bullet[i].vector.x *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, HitBlockDatas2D[0].BlockPosX* MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X, g_Bullet[i].nextpos.y);
						InversionVecAng(i, 0);

					}
					if (OriginLengthAndWidthPos == 2)
					{
						g_Bullet[i].nextpos.y = HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f - (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, HitBlockDatas2D[0].BlockPosY* MAP_CHIP_SIZE_Y + 0.0f);
						InversionVecAng(i, 1);

					}
					if (OriginLengthAndWidthPos == 3)
					{
						g_Bullet[i].nextpos.y = HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y + (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, HitBlockDatas2D[0].BlockPosY* MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y);
						InversionVecAng(i, 1);

					}
				}

				// �u���b�N�̎΂߂S�����Ɉʒu����ꍇ�̏����B�����ł̓u���b�N�P�̎��Ȃ̂ŕK���p���������Ă���B����~�ł̌v�Z������
				if (OriginCornerPos != -1)
				{
					bool hit = false;
					float distance;
					Float2 finpos;
					Float2 movedistance;
					float ratio;

					int BigMagnification = 10000;		// �덷�����炷���߂̔{��

					// �덷�����炷���߂ɑ傫�������~�̏��̐����v�Z�p(Bullet)
					Circle2D BigBulletCircle = {
						BulletCircle.x * BigMagnification,
						BulletCircle.y * BigMagnification,
						BulletCircle.r * BigMagnification,
					};

					Point2D BigCornerPoint;

					// �u���b�N�ł̍��W���炿���Ƃ������W�ɕϊ�����
					if (HitBlockDatas2D[0].CornerNum == 0)
					{
						BigCornerPoint.x = (HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f) * BigMagnification;
						BigCornerPoint.y = (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f) * BigMagnification;
						BigCornerPoint.corner = 0;
					}
					if (HitBlockDatas2D[0].CornerNum == 1)
					{
						BigCornerPoint.x = (HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X) * BigMagnification;
						BigCornerPoint.y = (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f) * BigMagnification;
						BigCornerPoint.corner = 1;
					}
					if (HitBlockDatas2D[0].CornerNum == 2)
					{
						BigCornerPoint.x = (HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f) * BigMagnification;
						BigCornerPoint.y = (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y) * BigMagnification;
						BigCornerPoint.corner = 2;
					}
					if (HitBlockDatas2D[0].CornerNum == 3)
					{
						BigCornerPoint.x = (HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X) * BigMagnification;
						BigCornerPoint.y = (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y) * BigMagnification;
						BigCornerPoint.corner = 3;
					}


					// ��������v�Z
					distance = CalculationDistance(BigBulletCircle.x, BigBulletCircle.y, BigCornerPoint.x, BigCornerPoint.y);
					if (distance <= BigBulletCircle.r)
						hit = true;

					ratio = CalculationRatio(distance, BigBulletCircle.r, BigMagnification);
					finpos = { BigCornerPoint.x * BigMagnification / ratio, BigCornerPoint.y * BigMagnification / ratio };
					movedistance = { finpos.x - BigCornerPoint.x, finpos.y - BigCornerPoint.y };
					movedistance = { fabsf(movedistance.x), fabsf(movedistance.y) };

					if (hit)
					{
						int divnum = 10;		// ������
						Float2 onemove{ -1, -1 };
						if (OriginCornerPos == 0)
						{
							onemove = { -movedistance.x / divnum, -movedistance.y / divnum };	// ����MoreAccuratePos�֐���10�����ɂ������̂�

						}
						if (OriginCornerPos == 1)
						{
							onemove = { movedistance.x / divnum, -movedistance.y / divnum };
						}
						if (OriginCornerPos == 2)
						{
							onemove = { -movedistance.x / divnum, movedistance.y / divnum };
						}
						if (OriginCornerPos == 3)
						{
							onemove = { movedistance.x / divnum, movedistance.y / divnum };
						}
						// ��萳�m�ɂ��邽�߂ɕ������Ŋ��������̒�����ł����m��pos�Ɉړ�������B�����Č덷�v�Z�̂��߂�10000�Ŋ���
						Float2 newpos = MoreAccurateCircleCollision(BigBulletCircle.x, BigBulletCircle.y, BigBulletCircle.r, BigCornerPoint.x, BigCornerPoint.y, onemove, divnum);
						g_Bullet[i].nextpos.x = newpos.x / BigMagnification;
						g_Bullet[i].nextpos.y = newpos.y / BigMagnification;

						// �������Ă���u���b�N�̐^�񒆂̍��W�����߂�
						float HitBlockCenterPosX = HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
						float HitBlockCenterPosY = HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);
						// �������Ă���u���b�N�̊p�܂ł̍����o��
						float difference_CornerPosX = CalculateCornerDistanceX(HitBlockDatas2D[0].CornerNum, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y);
						float difference_CornerPosY = CalculateCornerDistanceY(HitBlockDatas2D[0].CornerNum, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y);
						// �������Ă���u���b�N�̊p�̍��W���o��
						float CornerPosX = HitBlockCenterPosX + difference_CornerPosX;
						float CornerPosY = HitBlockCenterPosY + difference_CornerPosY;

						// �l�̍X�V��������B
						CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, CornerPosX, CornerPosY);

					}


				}



			}
			else if (hitcount > 0 && hitcount <= 4)
			{
				// �u���b�N�ɓ������Ă���A����2�ȏォ��4�ȉ��̏ꍇ�̏ꍇ
				// x���W�̃u���b�N�Ɋ��S�ɍ��E�ǂ��炩���炠�����Ă���ꍇ
				if (block_min.x == block_max.x)
				{
					int LeftorRight = -1;
					// ���E�ǂ��炩�炠�����Ă���̂��𒲂ׂ�
					// �@�~�̌��_���u���b�N�̏c��4�����̂ǂ��Ɉʒu���邩�̏���
					if (BulletCircle.x < block_min.x * MAP_CHIP_SIZE_X + 0.0f)
					{
						// �o���b�g�̓u���b�N�̍�������E���Ɍ������Đi��ł��ďՓ˂����̂Ńu���b�N�̍�����nextpos���Œ肵�A���Ɍ������Ĕ��˂�����
						LeftorRight = 0;
						g_Bullet[i].nextpos.x = block_min.x * MAP_CHIP_SIZE_X + 0.0f - (g_Bullet[i].w / 2);
						////g_Bullet[i].move.x *= -1;
						//g_Bullet[i].vector.x *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, block_min.x* MAP_CHIP_SIZE_X + 0.0f, g_Bullet[i].nextpos.y);
						InversionVecAng(i, 0);

					}
					if (BulletCircle.x > block_min.x * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
					{
						// �o���b�g�̓u���b�N�̉E�����獶���Ɍ������Đi��ł��ďՓ˂����̂Ńu���b�N�̉E����nextpos���Œ肵�A�E�Ɍ������Ĕ��˂�����
						LeftorRight = 1;
						g_Bullet[i].nextpos.x = block_min.x * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X + (g_Bullet[i].w / 2);
						////g_Bullet[i].move.x *= -1;
						//g_Bullet[i].vector.x *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, block_min.x* MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X, g_Bullet[i].nextpos.y);
						InversionVecAng(i, 0);

					}

					if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
					{
						if (BulletCircle.y < HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f)
							LeftorRight = 2;
					}
					if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
					{
						if (BulletCircle.y > HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
							LeftorRight = 3;
					}

				}
				// x���W�̃u���b�N�Ɋ��S�ɏ㉺�ǂ��炩���炠�����Ă���ꍇ
				if (block_min.y == block_max.y)
				{
					if (BulletCircle.y < block_min.y * MAP_CHIP_SIZE_Y + 0.0f)
					{
						// �o���b�g�̓u���b�N�̏㑤���牺���Ɍ������Đi��ł��ďՓ˂����̂Ńu���b�N�̏㑤��nextpos���Œ肵�A��Ɍ������Ĕ��˂�����
						g_Bullet[i].nextpos.y = block_min.y * MAP_CHIP_SIZE_Y + 0.0 - (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, block_min.y* MAP_CHIP_SIZE_Y + 0.0);
						InversionVecAng(i, 1);

					}
					if (BulletCircle.y > block_min.y * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
					{
						// �o���b�g�̓u���b�N�̉�������㑤�Ɍ������Đi��ł��ďՓ˂����̂Ńu���b�N�̉�����nextpos���Œ肵�A���Ɍ������Ĕ��˂�����
						g_Bullet[i].nextpos.y = block_min.y * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y + (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, block_min.y* MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y);
						InversionVecAng(i, 1);

					}
				}

			}






			// �}�b�v�Ƃ̓����蔻�菈��

			// �S�[���ɓ��������̏���
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y)) == 2)
			{
				// �S�[���ɓ��������̏���
				GoalTrue();
				// g_Bullet[i].use = false;
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 3)
			{
				// �����i��j�ɏ�������̏���
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// �V���b�g�p���[��ݒ�
					g_Bullet[i].angle = 90.0f;									// �p�x��ݒ�
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�
					
					g_Bullet[i].accboardcool = 60;
				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 4)
			{
				// �����i���j�ɏ�������̏���
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// �V���b�g�p���[��ݒ�
					g_Bullet[i].angle = 270.0f;									// �p�x��ݒ�
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�


					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 5)
			{
				// �����i�E�j�ɏ�������̏���
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// �V���b�g�p���[��ݒ�
					g_Bullet[i].angle = 0.0f;									// �p�x��ݒ�
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 6)
			{
				// �����i���j�ɏ�������̏���
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// �V���b�g�p���[��ݒ�
					g_Bullet[i].angle = 180.0f;									// �p�x��ݒ�
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 7)
			{
				// �����i�E��j�ɏ�������̏���
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// �V���b�g�p���[��ݒ�
					g_Bullet[i].angle = 45.0f;									// �p�x��ݒ�
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 8)
			{
				// �����i�E���j�ɏ�������̏���
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// �V���b�g�p���[��ݒ�
					g_Bullet[i].angle = 315.0f;									// �p�x��ݒ�
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 9)
			{
				// �����i�����j�ɏ�������̏���
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// �V���b�g�p���[��ݒ�
					g_Bullet[i].angle = 225.0f;									// �p�x��ݒ�
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 10)
			{
				// �����i����j�ɏ�������̏���
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// �V���b�g�p���[��ݒ�
					g_Bullet[i].angle = 135.0f;									// �p�x��ݒ�
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

					g_Bullet[i].accboardcool = 60;

				}
			}

			//���[�v
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 11)
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
							if (BlockData == 12)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 60;

							}

						}
					}
				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 12)
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
							if (BlockData == 11)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 60;
							}

						}
					}
				}
			}

			//��
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 13)
			{
				// �p���[������������
				if (g_Bullet[i].shotpower > 0.3f)
					g_Bullet[i].shotpower = 0.3f;

			}

			//���˔�
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 15)
			{
				// ���˔i�E�ɍs���j�ɏ�������̏���
					g_Bullet[i].angle = 0.0f;									// �p�x��ݒ�
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

			}

			//if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 15)
			//{
			//	// ���˔i���ɍs���j�ɏ�������̏���
			//	g_Bullet[i].angle = 180.0f;									// �p�x��ݒ�
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

			//}

			//if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 15)
			//{
			//	// ���˔i��ɍs���j�ɏ�������̏���
			//	g_Bullet[i].angle = 90.0f;									// �p�x��ݒ�
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

			//}

			//if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 15)
			//{
			//	// ���˔i���ɍs���j�ɏ�������̏���
			//	g_Bullet[i].angle = 270.0f;									// �p�x��ݒ�
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

			//}





			//// �N�[���^�C�������炷�����ꗗ
			//// �����u���b�N�ɓ����������̔���̃N�[���^�C�������炵�Ă���
			//if (g_Bullet[i].CollicionCool > 0)
			//	g_Bullet[i].CollicionCool--;
			//// ���[�v�̃N�[���^�C�������炵�Ă���
			//if (g_Bullet[i].warpcool > 0)
			//	g_Bullet[i].warpcool--;
			//// �����ł̃N�[���^�C�������炵�Ă���
			//if (g_Bullet[i].accboardcool > 0)
			//	g_Bullet[i].accboardcool--;


			// �Ŋ���pos��nextpos�𔽉f������
			g_Bullet[i].pos = g_Bullet[i].nextpos;

			// pos �� drawpos �ɕϊ�		DRAW_GAP �́A�ォ�猩�����̕`�ʂł̃}�b�v�̕`�ʂ̓��t�g�g�b�v�ŁA�v���C���[�͂ǐ^�񒆂ł���Ă邩��A���̂���B
			g_Bullet[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Bullet[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Bullet[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2);
			g_Bullet[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Bullet[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Bullet[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2);

		}

		// �N�[���^�C�������炷�����ꗗ
		// �����u���b�N�ɓ����������̔���̃N�[���^�C�������炵�Ă���
		if (g_Bullet[i].CollicionCool > 0)
			g_Bullet[i].CollicionCool--;
		// ���[�v�̃N�[���^�C�������炵�Ă���
		if (g_Bullet[i].warpcool > 0)
			g_Bullet[i].warpcool--;
		// �����ł̃N�[���^�C�������炵�Ă���
		if (g_Bullet[i].accboardcool > 0)
			g_Bullet[i].accboardcool--;

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


void DrawBulletSpecifyNum(int i)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)	// ���̃o���b�g���g���Ă���H
		{								// Yes
			//�o���b�g�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Bullet[i].drawpos.x;	// �o���b�g�̕\���ʒuX
			float py = g_Bullet[i].drawpos.y;	// �o���b�g�̕\���ʒuY
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
BULLET* GetBullet(void)
{
	return &g_Bullet[0];
}


//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBullet(D3DXVECTOR2 pos, float angle, int ShotPower)
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

			g_Bullet[i].shotpower = ShotBairitu;			// shotpower�̐ݒ�
			g_Bullet[i].angle = angle;						// �p�x��ݒ�
			g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);	// �p�x����x�N�g����ݒ�
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.x,
				-BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.y);	// �x�N�g������move��ݒ�

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

D3DXVECTOR2 AngleToVector2(float angle)
{
	float radian = angle * (D3DX_PI / 180);
	return  D3DXVECTOR2(cos(radian), sin(radian));
}


// -1:NoHit,0,����,1:�E��,2:����,3:�E��,�l���̂ǂ�ɓ������Ă��邩�B�܂��͂ǂ�ɂ��������Ă��Ȃ����B
// �u���b�N�̒��S����̊p�܂ł̍��W�̌v�Z�B���ǂ��̊p�ɓ������Ă��邩�����炤�ƌv�Z�ł���B��������X�����B
float CalculateCornerDistanceX(int CornerNum, float size_x, float size_y)
{
	float distance_x = 0;

	if (CornerNum == 0 || CornerNum == 2)
		distance_x = -size_x / 2;
	if (CornerNum == 1 || CornerNum == 3)
		distance_x = size_x / 2;

	return distance_x;
}

// �u���b�N�̒��S����̊p�܂ł̍��W�̌v�Z�B���ǂ��̊p�ɓ������Ă��邩�����炤�ƌv�Z�ł���B��������Y�����B
float CalculateCornerDistanceY(int CornerNum, float size_x, float size_y)
{
	float distance_y = 0;

	if (CornerNum == 2 || CornerNum == 3)
		distance_y = -size_y / 2;
	if (CornerNum == 0 || CornerNum == 1)
		distance_y = size_y / 2;

	return distance_y;
}

// �Փ˂���2�_�̍��W����v�Z���ĐV�����ݒ肷��p�x�ƃx�N�g�������߂�Bvoid�^�ōŊ��ɒl�̍X�V�����̊֐����Œ��ڍs���Ă���B
void CalculateNewVecAng(int i, float bulletposX, float bulletposY, float CornerPosX, float CornerPosY)
{

	// �{�[���x�N�g���̊p�x
	// g_Bullet[i].angle
	// �ǂ̃x�N�g���̊p�x
	//float wall_radian = CalculateRadianFrom2Points(CornerPosX, CornerPosY, g_Bullet[i].oldpos.x, g_Bullet[i].oldpos.y);
	float wall_radian = CalculateRadianFrom2Points(CornerPosX, CornerPosY, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y);
	wall_radian = InversionYRadian(wall_radian);
	//float wall_radian = atan2(g_Bullet[i].nextpos.y - (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) / BigMagnification), HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) - (BigCornerPoint.x / BigMagnification));
	float wall_angle = RadianToDegree(wall_radian);
	// �ǃx�N�g���̊p�x�̐^�t�̊p�x
	float wall_angle_reverse = ReverseDegree(wall_angle);

	// �ǂ̐^�t�̊p�x����{�[���̊p�x�������č����o��
	float difference_angle = wall_angle_reverse - g_Bullet[i].angle;
	float adjustAngle = 55.0f;
	// �J�X������ł��ǃx�N�g���̊p�x���� adjustangle �ȏ�̊p�x�͂��Ȃ�����Ă����Q�[�����ۂ������邽�߂̒����B���A�������Ȃ��悤�ɁB
	if (difference_angle > adjustAngle)
		difference_angle = adjustAngle;
	if (difference_angle < -adjustAngle)
		difference_angle = -adjustAngle;
	// �ǂ̊p�x�ɍ��̊p�x�𑫂�
	float new_bullet_angle = wall_angle + difference_angle;
	if (new_bullet_angle >= 360.0)
		new_bullet_angle -= 360.0;
	if (new_bullet_angle < 0)
		new_bullet_angle += 360.0;

	// �p�x�ƃx�N�g���̍X�V
	g_Bullet[i].angle = new_bullet_angle;							// �p�x��ݒ�
	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// �p�x����x�N�g����ݒ�

	g_Bullet[i].CollicionCool = COL_COOL;

	return;
}

// ���]�����������̂��AX�Ȃ�0,Y�Ȃ�1
void InversionVecAng(int i, int XorY)
{
	// �p�x��x,y�֌W�Ȃ�����Ŕ��]
	float newang = g_Bullet[i].angle + 180.0;
	if (newang >= 360)
		newang -= 360;

	D3DXVECTOR2 newvec = D3DXVECTOR2(g_Bullet[i].vector.x, g_Bullet[i].vector.y);
	if (XorY == 0)
		newvec.x *= -1;
	else
		newvec.y *= -1;

	// �p�x�ƃx�N�g���̍X�V
	g_Bullet[i].angle = newang;									// �p�x��ݒ�
	g_Bullet[i].vector = newvec;		// �p�x����x�N�g����ݒ�

	g_Bullet[i].CollicionCool = COL_COOL;

	return;
}

