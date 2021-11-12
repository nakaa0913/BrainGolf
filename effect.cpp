
#include "effect.h"
#include "Texture.h"
#include "sprite.h"
#include "score.h"
#include "scene.h"
#include "bg.h"
#include "camera.h"

EFFECT g_Effect[MAX_EFFECT];

//�e�N�X�`���̖��O��`
static int ao_0;		 // 0
static int aka_1;		 // 1
//static int tako_2;	 // 2
static int title_3;		 // 3
static int black_4;		 // 4
static int clear_5;		 // 5
static int select_6;	 // 6
static int select2_7;    // 7
static int mission_8;    // 8
static int selectstar_9; // 9
static int selectlock_10;// 10
static int clear_star1_11;// 11
static int clear_star2_12;// 12
static int clear_star3_13;// 13
static int clear_star4_14;// 14

void InitEffect(void)
{
	//�e�N�X�`���̖��O
	ao_0 = LoadTexture("data/TEXTURE/ao.png");
	aka_1 = LoadTexture("data/TEXTURE/result/advice.png");
	//tako_2 = LoadTexture("data/TEXTURE/result/tako.png");
	title_3 = LoadTexture("data/TEXTURE/title/title_effect.png");
	black_4 = LoadTexture("data/TEXTURE/other_effect/black.png");
	clear_5 = LoadTexture("data/TEXTURE/result/clear.png");
	select_6 = LoadTexture("data/TEXTURE/select/1.png");
	select2_7 = LoadTexture("data/TEXTURE/select/2.png");
	mission_8 = LoadTexture("data/TEXTURE/select/mission.png");
	selectstar_9 = LoadTexture("data/TEXTURE/select/selectstar.png");
	selectlock_10 = LoadTexture("data/TEXTURE/select/selectlock.png");
	clear_star1_11 = LoadTexture("data/TEXTURE/result/clear_star_1.png");
	clear_star2_12 = LoadTexture("data/TEXTURE/result/clear_star_2.png");
	clear_star3_13 = LoadTexture("data/TEXTURE/result/clear_star_3.png");
	clear_star4_14 = LoadTexture("data/TEXTURE/result/clear_star_black_1.png");



	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].id = ao_0;
		g_Effect[i].pos = D3DXVECTOR2(0, 0);
		g_Effect[i].pos1 = D3DXVECTOR2(0, 0);
		g_Effect[i].pos2 = D3DXVECTOR2(0, 0);
		g_Effect[i].pos_moving_pattern = 0;
		g_Effect[i].size = D3DXVECTOR2(100, 100);
		g_Effect[i].size1 = D3DXVECTOR2(100, 100);
		g_Effect[i].size2 = D3DXVECTOR2(100, 100);
		g_Effect[i].size_moving_pattern = 0;
		g_Effect[i].Clarity_min = 0.0f;
		g_Effect[i].Clarity_max = 1.0f;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min;
		g_Effect[i].fadeIn_count = 100;
		g_Effect[i].all_count = 100;
		g_Effect[i].fadeOut_count = 100;
		g_Effect[i].now_count = 300;
		g_Effect[i].moving_count = 0;
		g_Effect[i].rot = 0.0f;
		g_Effect[i].rot_angle = 0;
		g_Effect[i].rot_angle1 = 0;
		g_Effect[i].rot_angle2 = 90;
		g_Effect[i].rot_moving_pattern = 0;
		g_Effect[i].rot_count = 0;

		g_Effect[i].drawpos = g_Effect[i].pos;
		g_Effect[i].drawsize = g_Effect[i].size;

		g_Effect[i].drawpos = g_Effect[i].pos1;
		g_Effect[i].isUse = false;

	}
	InitScore();
}

void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].isUse = false;
	}
	// UninitScore();
	UnloadTexture("data/TEXTURE/ao.png");
	UnloadTexture("data/TEXTURE/result/advice.png");
	UnloadTexture("data/TEXTURE/title/title_effect.png");
	UnloadTexture("data/TEXTURE/other_effect/black.png");
	UnloadTexture("data/TEXTURE/select/1.png");
	UnloadTexture("data/TEXTURE/select/2.png");
	UnloadTexture("data/TEXTURE/select/mission.png");
	UnloadTexture("data/TEXTURE/select/selectstar.png");
	UnloadTexture("data/TEXTURE/select/selectlock.png");
	UnloadTexture("data/TEXTURE/result/clear_star_1.png");
	UnloadTexture("data/TEXTURE/result/clear_star_2.png");
	UnloadTexture("data/TEXTURE/result/clear_star_3.png");
	UnloadTexture("data/TEXTURE/result/clear_star_black_1.png");

}

void UpdateEffect(void)
{
	CAMERA* p_Camera = GetCamera();

	int effectnum = 0;
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse)
		{
			// FadeIn����A�E�g�܂ł̏���
			Fadeprocess(i);

			// pos_moveing�̏���
			PosMovingPattern(i);

			// size_moveing�̏���
			SizeMovingPattern(i);

			// rot_moveing�̏���
			RotMovingPattern(i);






			

			// ���Ԍo�߂ɂ��j�󏈗�
			if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count
				+ g_Effect[i].all_count + g_Effect[i].fadeOut_count)
			{
				// �������ɕ\�����������ꍇ�̏���.all_count == 999�������疳�����ɕ\��
				if (g_Effect[i].all_count == 999)
				{
					g_Effect[i].now_count = g_Effect[i].fadeIn_count + g_Effect[i].all_count - 998;
				}
				else
				{
					g_Effect[i].isUse = false;
				}
					
			}

			// ���t���[�����ƂɃJ�E���g��i�߂�
			g_Effect[i].now_count++;
			effectnum++;


			// pos �� drawpos �ɕϊ�	�G�t�F�N�g�̏ꍇ�Adrawpos����
			g_Effect[i].drawpos = g_Effect[i].pos;
			// g_Effect[i].drawsize = g_Effect[i].size * p_Camera->magnification;






		}
	}
	SetScore(effectnum);
	UpdateScore();
}

void DrawEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse == true)
		{
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Effect[i].Clarity);
			DrawSpriteColorRotate(g_Effect[i].id, g_Effect[i].drawpos.x, g_Effect[i].drawpos.y, g_Effect[i].size.x, g_Effect[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Effect[i].rot);
		}
	}
	DrawScore();
}

EFFECT* GetEffect(void)
{
	return &g_Effect[0];
}


// all_count == 999�������疳�����ɕ\��
int SetEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
			   float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
			   float rot_angle1, float rot_angle2, int rot_moving_pattern)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse == false)
		{
		//g_Effect[i].id = id;	���ň����œ��͂����l�ɂ���ăe�N�X�`����ύX���Ă���
		g_Effect[i].pos = pos1;
		g_Effect[i].pos1 = pos1;
		g_Effect[i].pos2 = pos2;
		g_Effect[i].pos_moving_pattern = pos_moving_pattern;
		g_Effect[i].size = size1;
		g_Effect[i].size1 = size1;
		g_Effect[i].size2 = size2;
		g_Effect[i].size_moving_pattern = size_moving_pattern;
		g_Effect[i].Clarity_min = Clarity_min;
		g_Effect[i].Clarity_max = Clarity_max;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min;
		g_Effect[i].fadeIn_count = fadeIn_count;
		g_Effect[i].all_count = all_count;
		g_Effect[i].fadeOut_count = fadeOut_count;
		g_Effect[i].now_count = 0;
		g_Effect[i].moving_count = moving_count;
		g_Effect[i].rot = AngleToRadian(rot_angle1);
		g_Effect[i].rot_angle = rot_angle1;
		g_Effect[i].rot_angle1 = rot_angle1;
		g_Effect[i].rot_angle2 = rot_angle2;
		g_Effect[i].rot_moving_pattern = rot_moving_pattern;
		g_Effect[i].rot_count = 0;

		g_Effect[i].drawpos = g_Effect[i].pos1;
		g_Effect[i].use_array_num = i;
		g_Effect[i].isUse = true;
		
		g_Effect[i].id = GetTextureData(id);

		return i;
		}

	}

	// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
	 exit(1);
}

// �Q�[�����ł̃G�t�F�N�g���g���ꍇ�͂������B���W�������I�Ɏ΂߂ɏC�����Ă����B�Ⴆ�΃Q�[�����̃{�[���ɒǏ]����Ƃ��̎��֗�
// all_count == 999�������疳�����ɕ\��
int SetGameEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern)
{
	CAMERA* p_Camera = GetCamera();

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse == false)
		{
			//g_Effect[i].id = id;	���ň����œ��͂����l�ɂ���ăe�N�X�`����ύX���Ă���
			
			// pos �� drawpos �ɕϊ� ���Ă��邯�ǁA�G�t�F�N�g�̏ꍇpos�̂܂܂��B


			g_Effect[i].pos.x = GAME_ORIGIN_POINT_Y + ((pos1.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((pos1.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2);
			g_Effect[i].pos.y = GAME_ORIGIN_POINT_Y + ((pos1.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((pos1.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2);
			g_Effect[i].pos1 = g_Effect[i].pos;

			g_Effect[i].pos2.x = GAME_ORIGIN_POINT_X + ((pos2.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((pos2.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2);
			g_Effect[i].pos2.y = GAME_ORIGIN_POINT_Y + ((pos2.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((pos2.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2);

			g_Effect[i].pos_moving_pattern = pos_moving_pattern;
			g_Effect[i].size = size1 * p_Camera->magnification;
			g_Effect[i].size1 = size1 * p_Camera->magnification;
			g_Effect[i].size2 = size2 * p_Camera->magnification;
			g_Effect[i].size_moving_pattern = size_moving_pattern;
			g_Effect[i].Clarity_min = Clarity_min;
			g_Effect[i].Clarity_max = Clarity_max;
			g_Effect[i].Clarity = g_Effect[i].Clarity_min;
			g_Effect[i].fadeIn_count = fadeIn_count;
			g_Effect[i].all_count = all_count;
			g_Effect[i].fadeOut_count = fadeOut_count;
			g_Effect[i].now_count = 0;
			g_Effect[i].moving_count = moving_count;
			g_Effect[i].rot = AngleToRadian(rot_angle1);
			g_Effect[i].rot_angle = rot_angle1;
			g_Effect[i].rot_angle1 = rot_angle1;
			g_Effect[i].rot_angle2 = rot_angle2;
			g_Effect[i].rot_moving_pattern = rot_moving_pattern;
			g_Effect[i].rot_count = 0;

			g_Effect[i].drawpos = g_Effect[i].pos1;
			g_Effect[i].use_array_num = i;
			g_Effect[i].isUse = true;

			g_Effect[i].id = GetTextureData(id);


			return i;
		}

	}

	// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
	exit(1);
}


void Fadeprocess(int i)
{
	//0�`fadeIn
	if (g_Effect[i].now_count < 0 + g_Effect[i].fadeIn_count)
	{
		float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeIn_count;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * g_Effect[i].now_count;
	}
	//fadeIn�`all
	if (g_Effect[i].now_count >= 0 + g_Effect[i].fadeIn_count &&
		g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count)
	{
		g_Effect[i].Clarity = g_Effect[i].Clarity_max;
	}
	//all�`fadeOut
	if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count + g_Effect[i].all_count &&
		g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count)
	{
		float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeOut_count;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * ((g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count) - g_Effect[i].now_count);
	}
}


void PosMovingPattern(int i)
{
	// ���̊֐���isUse��true�̏ꍇ�����Ă΂�Ȃ��ꏊ�ŌĂ�

	// ���݂̃J�E���g�� moving_count ��菬�����Ԃ������s�����
	if (g_Effect[i].now_count < g_Effect[i].moving_count)
	{
		// 0	pos1����ړ����Ȃ��B
		if (g_Effect[i].pos_moving_pattern == 0)
		{
			g_Effect[i].pos = g_Effect[i].pos1;
		}

		// 1	pos1����pos2�܂Œ����I�Ȉړ�������
		if (g_Effect[i].pos_moving_pattern == 1)
		{
			D3DXVECTOR2 onemove = (g_Effect[i].pos2 - g_Effect[i].pos1) / g_Effect[i].moving_count;
			D3DXVECTOR2 newpos = g_Effect[i].pos + onemove * g_Effect[i].now_count;
			g_Effect[i].pos = g_Effect[i].pos1 + onemove * g_Effect[i].now_count;
			// g_Effect[i].pos = g_Effect[i].pos2;

			// �덷���o��̂œ����Ō�̃t���[����pos2���x�ɂȂ�悤�ɒ���
			if (g_Effect[i].now_count == g_Effect[i].moving_count - 1)
				g_Effect[i].pos = g_Effect[i].pos2;
		}
		// �����Ƀp�^�[�������������Ă���




	}
	
	return;
}

void SizeMovingPattern(int i)
{
	// ���̊֐���isUse��true�̏ꍇ�����Ă΂�Ȃ��ꏊ�ŌĂ�

	// ���݂̃J�E���g�� moving_count ��菬�����Ԃ������s�����
	if (g_Effect[i].now_count < g_Effect[i].moving_count)
	{
		// 0	pos1����ړ����Ȃ��B
		if (g_Effect[i].size_moving_pattern == 0)
		{
			g_Effect[i].size = g_Effect[i].size1;
		}

		// 1	size1����size2�܂Œ����I�Ȉړ�������
		if (g_Effect[i].size_moving_pattern == 1)
		{
			D3DXVECTOR2 onemove = (g_Effect[i].size2 - g_Effect[i].size1) / g_Effect[i].moving_count;
			D3DXVECTOR2 newpos = g_Effect[i].size + onemove * g_Effect[i].now_count;
			g_Effect[i].size = g_Effect[i].size1 + onemove * g_Effect[i].now_count;
			// g_Effect[i].size = g_Effect[i].size2;

			// �덷���o��̂œ����Ō�̃t���[����size2���x�ɂȂ�悤�ɒ���
			if (g_Effect[i].now_count == g_Effect[i].moving_count - 1)
				g_Effect[i].size = g_Effect[i].size2;
		}
		// �����Ƀp�^�[�������������Ă���




	}

	return;
}

void RotMovingPattern(int i)
{
	// ���̊֐���isUse��true�̏ꍇ�����Ă΂�Ȃ��ꏊ�ŌĂ�

	// ���݂̃J�E���g�� moving_count ��菬�����Ԃ������s�����
	// ��������rot_moving_pattern �� 2 �̎��͎��Ԃ��؂�Ă������ɉ�]����̂Ŏ��s�����
	if (g_Effect[i].now_count < g_Effect[i].moving_count || g_Effect[i].rot_moving_pattern == 2)
	{
		// �܂��p�xangle���烉�W�A��rot�ɕϊ�����
		float rot = AngleToRadian(g_Effect[i].rot_angle);
		float rot1 = AngleToRadian(g_Effect[i].rot_angle1);
		float rot2 = AngleToRadian(g_Effect[i].rot_angle2);


		// 0	rot_angle1����ړ����Ȃ��B
		if (g_Effect[i].rot_moving_pattern == 0)
		{
			g_Effect[i].rot = AngleToRadian(g_Effect[i].rot_angle);
		}

		// 1	rot_angle1����rot_angle2�܂Œ����I�Ȉړ�������
		if (g_Effect[i].rot_moving_pattern == 1)
		{
			float onemove = (g_Effect[i].rot_angle2 - g_Effect[i].rot_angle1) / g_Effect[i].moving_count;
			g_Effect[i].rot_angle = g_Effect[i].rot_angle1 + onemove * g_Effect[i].now_count;
			g_Effect[i].rot		  = AngleToRadian(g_Effect[i].rot_angle);

			// �덷���o��̂œ����Ō�̃t���[����rot_angle2�ɒ��x�ɂȂ�悤�ɒ���
			if (g_Effect[i].now_count == g_Effect[i].moving_count - 1)
			{
				g_Effect[i].rot_angle = g_Effect[i].rot_angle2;
				g_Effect[i].rot		  = AngleToRadian(g_Effect[i].rot_angle);
			}
		}

		// 2	rot_angle1����rot_angle2 �܂Œ����I�ȉ�]������B 1�Ƃ͈Ⴂ�Amoving_count���I����Ă���]��������B
		if (g_Effect[i].rot_moving_pattern == 2)
		{
			float onemove = (g_Effect[i].rot_angle2 - g_Effect[i].rot_angle1) / g_Effect[i].moving_count;
			g_Effect[i].rot_angle = g_Effect[i].rot_angle1 + onemove * g_Effect[i].rot_count;
			g_Effect[i].rot		  = AngleToRadian(g_Effect[i].rot_angle);
		}
		// �����Ƀp�^�[�������������Ă���




	}

	g_Effect[i].rot_count++;

	return;
}

float AngleToRadian(float angle)
{
	float radian = angle * (D3DX_PI / 180);
	return  radian;
}

int GetTextureData(int id)
{

	switch (id)
	{
	case 0:
		return ao_0;
		break;
	case 1:
		return aka_1;
		break;
	//case 2:
	//	return tako_2;
	//	break;
	case 3:
		return title_3;
		break;
	case 4:
		return black_4;
		break;
	case 5:
		return clear_5;
		break;
	case 6:
		return select_6;
		break;
	case 7:
		return select2_7;
		break;
	case 8:
		return mission_8;
		break;
	case 9:
		return selectstar_9;
		break;
	case 10:
		return selectlock_10;
		break;
	case 11:
		return clear_star1_11;
		break;
	case 12:
		return clear_star2_12;
		break;
	case 13:
		return clear_star3_13;
		break;
	case 14:
		return clear_star4_14;
		break;
	}

	// �ǂ��ɂ����ǂ蒅���Ȃ������ꍇ
	exit(21);
	return -1;
}


// �ŏ���use_array_num���K�v�����A����use_array_num�̃G�t�F�N�g��r���ł��ύX�ł���
void ChangeEffect(int use_array_num, int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern)
{
	if (g_Effect[use_array_num].isUse)
	{
		//g_Effect[use_array_num].id = id;	���ň����œ��͂����l�ɂ���ăe�N�X�`����ύX���Ă���
		g_Effect[use_array_num].pos = pos1;
		g_Effect[use_array_num].pos1 = pos1;
		g_Effect[use_array_num].pos2 = pos2;
		g_Effect[use_array_num].pos_moving_pattern = pos_moving_pattern;
		g_Effect[use_array_num].size = size1;
		g_Effect[use_array_num].size1 = size1;
		g_Effect[use_array_num].size2 = size2;
		g_Effect[use_array_num].size_moving_pattern = size_moving_pattern;
		g_Effect[use_array_num].Clarity_min = Clarity_min;
		g_Effect[use_array_num].Clarity_max = Clarity_max;
		g_Effect[use_array_num].Clarity = g_Effect[use_array_num].Clarity_min;
		g_Effect[use_array_num].fadeIn_count = fadeIn_count;
		g_Effect[use_array_num].all_count = all_count;
		g_Effect[use_array_num].fadeOut_count = fadeOut_count;
		g_Effect[use_array_num].now_count = 0;
		g_Effect[use_array_num].moving_count = moving_count;
		g_Effect[use_array_num].rot = AngleToRadian(rot_angle1);
		g_Effect[use_array_num].rot_angle = rot_angle1;
		g_Effect[use_array_num].rot_angle1 = rot_angle1;
		g_Effect[use_array_num].rot_angle2 = rot_angle2;
		g_Effect[use_array_num].rot_moving_pattern = rot_moving_pattern;
		g_Effect[use_array_num].rot_count = 0;

		g_Effect[use_array_num].drawpos = g_Effect[use_array_num].pos1;
		//g_Effect[use_array_num].use_array_num = 
		g_Effect[use_array_num].isUse = true;

		g_Effect[use_array_num].id = GetTextureData(id);

		return;


	}

	// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
	exit(1);
}


// use_array_num�̃G�t�F�N�g��now_count������ݒ�ł���
void ChangeEffectCount(int use_array_num, int setcount)
{
	g_Effect[use_array_num].now_count = setcount;

	return;
}

// �z��̉��Ԗڂ����w�肵�ăG�t�F�N�g������
void EffectBreak(int use_array_num)
{
	g_Effect[use_array_num].isUse = false;
	g_Effect[use_array_num].use_array_num = -1;

	return;
}