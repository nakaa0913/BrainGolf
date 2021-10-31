
#include "effect.h"
#include "Texture.h"
#include "sprite.h"

EFFECT g_Effect[MAX_EFFECT];

//�e�N�X�`���̖��O��`
static int ao_0;		// 0
static int aka_1;		// 1
static int tako_2;		// 2
static int title_3;		// 3
static int black_4;		// 4
void InitEffect(void)
{
	//�e�N�X�`���̖��O
	ao_0 = LoadTexture("data/TEXTURE/ao.png");
	aka_1 = LoadTexture("data/TEXTURE/aka.png");
	tako_2 = LoadTexture("data/TEXTURE/tako.png");
	title_3 = LoadTexture("data/TEXTURE/title.png");
	black_4 = LoadTexture("data/TEXTURE/black.png");

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
		g_Effect[i].Clarity = g_Effect[i].Clarity_max;
		g_Effect[i].fadeIn_count = 100;
		g_Effect[i].all_count = 100;
		g_Effect[i].fadeOut_count = 100;
		g_Effect[i].now_count = 300;
		g_Effect[i].moving_count = 0;
		g_Effect[i].rot_angle = 0;
		g_Effect[i].rot_angle1 = 0;
		g_Effect[i].rot_angle2 = 90;
		g_Effect[i].rot_moving_pattern = 0;

		g_Effect[i].drawpos = g_Effect[i].pos1;
		g_Effect[i].isUse = false;

	}
}

void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].isUse = false;
	}
}

void UpdateEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse)
		{
			

			//0�`fadeIn
			if (g_Effect[i].now_count < 0 + g_Effect[i].fadeIn_count)
			{
				float oneframe = 1.0f / g_Effect[i].fadeIn_count;
				g_Effect[i].Clarity = oneframe * g_Effect[i].now_count;
			}
			//fadeIn�`all
			if(g_Effect[i].now_count >= 0 + g_Effect[i].fadeIn_count && 
				g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count)
			{
				g_Effect[i].Clarity = 1.0f;
			}
			//all�`fadeOut
			if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count + g_Effect[i].all_count && 
				g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count)
			{
				float oneframe = 1.0f / g_Effect[i].fadeOut_count;
				g_Effect[i].Clarity = oneframe * ((g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count) - g_Effect[i].now_count);
			}

			// pos_moveing�̏���
			PosMovingPattern(i);

			// size_moveing�̏���
			SizeMovingPattern(i);








			// ���Ԍo�߂ɂ��j�󏈗�
			if (g_Effect[i].now_count > g_Effect[i].fadeIn_count
				+ g_Effect[i].all_count + g_Effect[i].fadeOut_count)
			{
				// �������ɕ\�����������ꍇ�̏���.all_count == 999�������疳�����ɕ\��
				if (g_Effect[i].all_count == 999)
				{
					g_Effect[i].now_count = g_Effect[i].fadeIn_count + g_Effect[i].all_count;
				}
				else
					g_Effect[i].isUse = false;
			}

			// ���t���[�����ƂɃJ�E���g��i�߂�
			g_Effect[i].now_count++;
			
			// Draw�p�ɒ���
			/*g_Effect[i].drawpos.x = g_Effect[i].pos1.x;
			g_Effect[i].drawpos.y = g_Effect[i].pos1.y;*/
		}
	}
}

void DrawEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse == true)
		{
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Effect[i].Clarity);
			// D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			DrawSpriteColorRotate(g_Effect[i].id, g_Effect[i].pos.x, g_Effect[i].pos.y, g_Effect[i].size.x, g_Effect[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f, col, 0.0f);
			int aaaa = 0;
		}
	}
}

EFFECT* GetEffect(void)
{
	return &g_Effect[0];
}


// all_count == 999�������疳�����ɕ\��
void SetEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
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
		g_Effect[i].Clarity_min = 0.0f;
		g_Effect[i].Clarity_max = 0.0f;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min;
		g_Effect[i].fadeIn_count = fadeIn_count;
		g_Effect[i].all_count = all_count;
		g_Effect[i].fadeOut_count = fadeOut_count;
		g_Effect[i].now_count = 0;
		g_Effect[i].moving_count = moving_count;
		g_Effect[i].rot_angle = rot_angle1;
		g_Effect[i].rot_angle1 = rot_angle1;
		g_Effect[i].rot_angle2 = rot_angle2;
		g_Effect[i].rot_moving_pattern = rot_moving_pattern;

		g_Effect[i].drawpos = g_Effect[i].pos1;
		g_Effect[i].isUse = true;
		
		if(id == 0)
			g_Effect[i].id = ao_0;
		if (id == 1)
			g_Effect[i].id = aka_1;
		if (id == 2)
			g_Effect[i].id = tako_2;
		if (id == 3)
			g_Effect[i].id = title_3;
		if (id == 4)
			g_Effect[i].id = black_4;


		return;
		}

	}

	// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
	exit(1);
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

float AngleToRadian(float angle)
{
	float radian = angle * (D3DX_PI / 180);
	return  radian;
}