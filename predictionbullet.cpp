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
#include "camera.h"
#include "predictionbullet.h"
#include "player.h"
#include "bullet.h"


static PREDICTION g_Prediction[PREDICTION_MAX];					// �\���e�\����

static int predictionbullet_ao;
static int predictionbullet_aka;

int drawcount = 0;


HRESULT InitPrediction(void)
{
	predictionbullet_ao = LoadTexture("data/TEXTURE/bullet/predictionbullet/ao.png");
	predictionbullet_aka = LoadTexture("data/TEXTURE/bullet/predictionbullet/aka.png");

	drawcount = 0;

	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		g_Prediction[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Prediction[i].size = D3DXVECTOR2(100.0f, 100.0f);
		g_Prediction[i].drawpos = g_Prediction[i].pos;
		g_Prediction[i].drawsize = g_Prediction[i].size;
		g_Prediction[i].angle = 0.0f;
		g_Prediction[i].vector = D3DXVECTOR2(100.0f, 100.0f);
		g_Prediction[i].shotpower = 1.0f;
		g_Prediction[i].tex = predictionbullet_ao;
		g_Prediction[i].isUse = false;



	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPrediction(void)
{
	// UnloadTexture("data/TEXTURE/bullet/ao.png");
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePrediction(void)
{

	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		if (g_Prediction[i].isUse == true)	// ���̗\���e���g���Ă���H
		{
			CAMERA* p_Camera = GetCamera();
			BULLET* p_Bullet = GetBullet();
			PLAYER* p_Player = GetPlayer();

			// �������炤
			int havenum = returnHavePlayer();
			g_Prediction[i].angle = 360 - p_Player[havenum].angle;
			g_Prediction[i].pos = p_Player[havenum].pos;
			g_Prediction[i].size.x = PREDICTION_SIZE;
			g_Prediction[i].size.y = PREDICTION_SIZE;

			int ClubPattern = GetClubPattern();

			// �x�N�g���̌v�Z
			g_Prediction[i].vector = AngleToVector2(g_Prediction[i].angle);	// �p�x����x�N�g����ݒ�

			float sizebairitu = 0.0f;		// ���̕��������񏬂����Ȃ��Ă���
			
			// �l�̍X�V		i�̕���������ĕ\�������
			if (ClubPattern == 0)		// �n�ʂ�]����ꍇ�̗\��
			{
				g_Prediction[i].pos += g_Prediction[i].vector * (i + 1) * 40;
				g_Prediction[i].size *= 1.0f - i * sizebairitu;

				g_Prediction[i].tex = predictionbullet_ao;			// �e�N�X�`���̐ݒ�A�]����ꍇ�S����

				if (i == 6)
				{
					g_Prediction[i].pos.x = 99999;
					g_Prediction[i].pos.y = 99999;
				}
			}
			if (ClubPattern == 1)		// �Ƃԏꍇ�̗\��
			{
				//g_Prediction[i].pos += g_Prediction[i].vector * (i + 1) * 40;
				//g_Prediction[i].size *= 1.0f - i * 0.1f;

				
				switch (i)
				{
				case 0:
					g_Prediction[i].pos += g_Prediction[i].vector * 82;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 1:		// ���΂�a
					g_Prediction[i].pos += g_Prediction[i].vector * 122;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 2:
					g_Prediction[i].pos += g_Prediction[i].vector * 161;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 3:		// �[�΂�
					g_Prediction[i].pos += g_Prediction[i].vector * 200;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 4:
					g_Prediction[i].pos += g_Prediction[i].vector * 220;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 5:		// ����[�΂�
					g_Prediction[i].pos += g_Prediction[i].vector * 240;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 6:		// ��Ԏ�O
					g_Prediction[i].pos += g_Prediction[i].vector * 41;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				default:
					break;
				}
				// �o�E���h����Ƃ��낾���e�N�X�`����ς���
				if (i == 1 || i == 3 || i == 5)
				{
					g_Prediction[i].tex = predictionbullet_aka;		// �e�N�X�`���̐ݒ�A��Ԃ�̏ꍇ���n����ꏊ�͐Ԃ�����
				}
				else
					g_Prediction[i].tex = predictionbullet_ao;
			}



			static int finalgapy = DRAW_GAP_FINAL_Y / 2;

			// pos �� drawpos �ɕϊ�		DRAW_GAP �́A�ォ�猩�����̕`�ʂł̃}�b�v�̕`�ʂ̓��t�g�g�b�v�ŁA�v���C���[�͂ǐ^�񒆂ł���Ă邩��A���̂���B
			g_Prediction[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Prediction[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Prediction[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			g_Prediction[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Prediction[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Prediction[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y + finalgapy;
			g_Prediction[i].drawsize.x = g_Prediction[i].size.x * p_Camera->magnification;
			g_Prediction[i].drawsize.y = g_Prediction[i].size.y * p_Camera->magnification;

		}

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPrediction(void)
{
	//CAMERA* p_Camera = GetCamera();

	//for (int i = 0; i < PREDICTION_MAX; i++)
	//{
	//	if (g_Prediction[i].isUse == true)	// ���̗\���e���g���Ă���H
	//	{									// Yes
	//		// �\���e�̈ʒu��e�N�X�`���[���W�𔽉f
	//		float px = g_Prediction[i].pos.x;		// �o���b�g�̕\���ʒuX
	//		float py = g_Prediction[i].pos.y;		// �o���b�g�̕\���ʒuY
	//		float pw = g_Prediction[i].size.x;		// �o���b�g�̕\����
	//		float ph = g_Prediction[i].size.y;		// �o���b�g�̕\������
	//		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



	//		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	//		DrawSpriteColorRotate(g_Prediction[i].tex, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, 0.0f);
	//	}
	//}
}


void DrawPredictionSpecifyNum(int i)
{

	// ���𔭎˂��Ă�����\�����Ȃ�
	if (hassyazyunbi())
		PredictionUseTrue();
	else
		PredictionUseFalse();

	if (g_Prediction[0].isUse == true)
	{
		if(drawcount == 0)
			drawcount = 1;
	}
	else
		drawcount = 0;

	if (drawcount >= 1)
	{
		if (drawcount >= 7)
		{
			if (g_Prediction[i].isUse == true)	// ���̗\���e���g���Ă���H
			{

				//�o���b�g�̈ʒu��e�N�X�`���[���W�𔽉f
				float px = g_Prediction[i].drawpos.x;	// �o���b�g�̕\���ʒuX
				float py = g_Prediction[i].drawpos.y;	// �o���b�g�̕\���ʒuY
				float pw = g_Prediction[i].drawsize.x;		// �o���b�g�̕\����
				float ph = g_Prediction[i].drawsize.y;		// �o���b�g�̕\������
				D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				DrawSpriteColorRotate(g_Prediction[i].tex, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, 0.0f);
			}
		}
		else
			drawcount++;
	}
}


PREDICTION* GetPrediction(void)
{
	return &g_Prediction[0];
}

void PredictionUseTrue()
{
	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		g_Prediction[i].isUse = true;
	}
	return;
}

void PredictionUseFalse()
{
	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		g_Prediction[i].isUse = false;
	}
	return;
}