
#include<iostream>
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

//�X�e�[�W�I���̔w�i
static int stage_select1_15;// 15
static int stage_select2_16;// 16
static int stage_select3_17;// 17
static int stage_select4_18;// 18
static int stage_select5_19;// 19
//�X�e�[�W�I���̎l�p�����
static int stage_choice1_20;// 20
static int stage_choice2_21;// 21
static int stage_choice3_22;// 22
static int stage_choice4_23;// 23
static int stage_choice5_24;// 24
//�X�e�[�W�I���̃~�b�V����
static int stage_mission_background_25;// 25
static int stage_mission0_26;// 26
static int stage_mission1_27;// 27
static int stage_mission2_28;// 28
static int stage_mission3_29;// 29
static int stage_mission4_30;// 30
static int stage_mission5_31;// 31
static int stage_mission6_32;// 32
static int stage_mission7_33;// 33
static int stage_mission8_34;// 34
static int stage_mission9_35;// 35
static int stage_mission10_36;// 36
static int stage_mission11_37;// 37
static int stage_mission12_38;// 38
static int stage_mission13_39;// 39
static int stage_mission14_40;// 40 
static int stage_mission15_41;// 41
static int stage_mission16_42;// 42
static int stage_mission17_43;// 43
static int stage_mission18_44;// 44
static int stage_mission19_45;// 45

// �����̕\��
static int number_46;// 46

static int next_47;	    // 47
static int white_48;    // 48
static int mapback_49;  // 49
//static int maparrow_50; // 50 �g��Ȃ�
//static int maptext_51;  // 51 �g��Ȃ�

// placement�Ŏg�����
static int pickup_green_52;  // 52
static int pickup_red_53;  // 53
static int batten_red_54;  // 54

// �Q�[���I�[�o�[
static int gameover_55;  // 55
static int restart_56;  // 56
static int stagename_57;  // 57
static int gameover_back_58;  // 58
static int gameover_place_59; // 59

static int titleback_60; //60
static int worldback_61; //61

//�@�|�[�Y���
static int pause_62; //62
static int commentary_63; //62



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

	stage_select1_15 = LoadTexture("data/TEXTURE/select/1aka.png");
	stage_select2_16 = LoadTexture("data/TEXTURE/select/2yellow.png");
	stage_select3_17 = LoadTexture("data/TEXTURE/select/3green.png");
	stage_select4_18 = LoadTexture("data/TEXTURE/select/4orange.png");
	stage_select5_19 = LoadTexture("data/TEXTURE/select/5blue.png");

	stage_choice1_20 = LoadTexture("data/TEXTURE/select/1.png");
	stage_choice2_21 = LoadTexture("data/TEXTURE/select/1.png");
	stage_choice3_22 = LoadTexture("data/TEXTURE/select/1.png");
	stage_choice4_23 = LoadTexture("data/TEXTURE/select/1.png");
	stage_choice5_24 = LoadTexture("data/TEXTURE/select/1.png");

	stage_mission_background_25 = LoadTexture("data/TEXTURE/select/mission/mission_background.png");
	stage_mission0_26 = LoadTexture("data/TEXTURE/select/mission/mission_0.png");
	stage_mission1_27 = LoadTexture("data/TEXTURE/select/mission/mission_1.png");
	stage_mission2_28 = LoadTexture("data/TEXTURE/select/mission/mission_2.png");
	stage_mission3_29 = LoadTexture("data/TEXTURE/select/mission/mission_3.png");
	stage_mission4_30 = LoadTexture("data/TEXTURE/select/mission/mission_4.png");
	stage_mission5_31 = LoadTexture("data/TEXTURE/select/mission/mission_5.png");
	stage_mission6_32 = LoadTexture("data/TEXTURE/select/mission/mission_6.png");
	stage_mission7_33 = LoadTexture("data/TEXTURE/select/mission/mission_7.png");
	stage_mission8_34 = LoadTexture("data/TEXTURE/select/mission/mission_8.png");
	stage_mission9_35 = LoadTexture("data/TEXTURE/select/mission/mission_9.png");
	stage_mission10_36 = LoadTexture("data/TEXTURE/select/mission/mission_10.png");
	stage_mission11_37 = LoadTexture("data/TEXTURE/select/mission/mission_11.png");
	stage_mission12_38 = LoadTexture("data/TEXTURE/select/mission/mission_12.png");
	stage_mission13_39 = LoadTexture("data/TEXTURE/select/mission/mission_13.png");
	stage_mission14_40 = LoadTexture("data/TEXTURE/select/mission/mission_14.png");
	stage_mission15_41 = LoadTexture("data/TEXTURE/select/mission/mission_15.png");
	stage_mission16_42 = LoadTexture("data/TEXTURE/select/mission/mission_16.png");
	stage_mission17_43 = LoadTexture("data/TEXTURE/select/mission/mission_17.png");
	stage_mission18_44 = LoadTexture("data/TEXTURE/select/mission/mission_18.png");
	stage_mission19_45 = LoadTexture("data/TEXTURE/select/mission/mission_19.png");

	number_46 = LoadTexture("data/TEXTURE/other_effect/number.png");
	next_47 = LoadTexture("data/TEXTURE/result/allnext.png");
	white_48 = LoadTexture("data/TEXTURE/result/fade_white.png");
	mapback_49 = LoadTexture("data/TEXTURE/result/map_back.png");
	//maparrow_50 = LoadTexture("data/TEXTURE/result/map_arrow.png");
	//maptext_51 = LoadTexture("data/TEXTURE/result/map_text.png");

	pickup_green_52 = LoadTexture("data/TEXTURE/placement/pickup_green.png");
	pickup_red_53 = LoadTexture("data/TEXTURE/placement/pickup_red.png");
	batten_red_54 = LoadTexture("data/TEXTURE/placement/batten_red.png");

	gameover_55 = LoadTexture("data/TEXTURE/result/gameover/gameover.png");
	restart_56 = LoadTexture("data/TEXTURE/result/gameover/restart.png");
	stagename_57 = LoadTexture("data/TEXTURE/result/gameover/stagename.png");
	gameover_back_58 = LoadTexture("data/TEXTURE/result/gameover/gameover_back.png");
	gameover_place_59 = LoadTexture("data/TEXTURE/result/gameover/gameover_place.png");

	titleback_60 = LoadTexture("data/TEXTURE/select/titleback.png");
	worldback_61 = LoadTexture("data/TEXTURE/select/worldback.png");

	pause_62 = LoadTexture("data/TEXTURE/other_effect/pause.png");
	commentary_63 = LoadTexture("data/TEXTURE/other_effect/commentary.png");


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

		g_Effect[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Effect[i].Clarity);

		// UV�l�̐ݒ�B�f�t�H���ƑS�ĕ\��
		g_Effect[i].tx = 1.0f;
		g_Effect[i].ty = 1.0f;
		g_Effect[i].sx = 0.0f;
		g_Effect[i].sy = 0.0f;

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
	UnloadTexture("data/TEXTURE/other_effect/number.png");

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






			

			// ���Ԍo�߂ɂ��j�󏈗�		== �ɂ��邱�Ƃ�999�̏������y�ɂȂ�
			if (g_Effect[i].now_count == g_Effect[i].fadeIn_count
				+ g_Effect[i].all_count + g_Effect[i].fadeOut_count)
			{
				// �������ɕ\�����������ꍇ�̏���.all_count == 999�������疳�����ɕ\��
				if (g_Effect[i].all_count == 999)
				{
					// g_Effect[i].now_count = g_Effect[i].fadeIn_count + 998;�@����Ȃ��Ƃ��Ȃ��Ă���
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
			g_Effect[i].color = D3DXCOLOR(g_Effect[i].color.r, g_Effect[i].color.g, g_Effect[i].color.b, g_Effect[i].Clarity);
			DrawSpriteColorRotate(g_Effect[i].id, g_Effect[i].drawpos.x, g_Effect[i].drawpos.y, g_Effect[i].size.x, g_Effect[i].size.y, g_Effect[i].sx, g_Effect[i].sy, g_Effect[i].tx, g_Effect[i].ty, g_Effect[i].color, g_Effect[i].rot);
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

		g_Effect[i].tx = 1.0f;					// �e�N�X�`��1�}�X�̕�
		g_Effect[i].ty = 1.0f;					// �e�N�X�`��1�}�X�̍���
		g_Effect[i].sx = 0.0f;					// �e�N�X�`���̃X�^�[�g�ʒux
		g_Effect[i].sy = 0.0f;					// �e�N�X�`���̃X�^�[�g�ʒuy

		g_Effect[i].isUse = true;
		
		g_Effect[i].id = GetTextureData(id);

		return i;
		}

	}

	// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
	 exit(1);
}

// ���̐����̂ݑΉ�
void SetEffectNumber(int num,int* back_array, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern)
{

	// ����������͎��ۂɂ͎g�킸�ɃN���[�����g���Čv�Z
	int number = num;

	// ��������������������̌v�Z
	int digit = 0;
	while (number != 0)
	{
		number = number / 10;
		digit++;
	}
	// 0�P�̂̏ꍇ��̃��C�������ƌ���0�ɂȂ�̂ŁA���Ƃ�digit��1�ɂ��Ă�����
	if (num == 0)
		digit = 1;

	// �����̐^�񒆂𒲂ׂ�B���������W�̒��S�ƂȂ�
	int middle_digit = digit / 2;

	int serial = 0;
	int nextnum = -1;

	int last_i = -1;

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse == false)
		{
			if (i == nextnum)
			{
				// �A�Ԃ������ꍇ
				serial++;
			}
			else
			{
				// �A�ԂłȂ������ꍇ
				serial = 0;
			}

			nextnum = i + 1;

			// serial���������A�����Ă�����break���Ĕ�����B
			if (serial == digit - 1)
			{
				last_i = i;
				break;
			}
		}
		// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
		//exit(25);
	}

	int sn = last_i - (digit - 1);		// startnum
	// ������num�����߂ē���Ă���
	number = num;

	// �Z�b�g�G�t�F�N�g���鏈��
	for (int i = 0; i < digit; i++)
	{
		//g_Effect[i + sn].id = id;	���ň����œ��͂����l�ɂ���ăe�N�X�`����ύX���Ă���
		g_Effect[i + sn].pos = pos1;
		g_Effect[i + sn].pos1 = pos1;
		g_Effect[i + sn].pos2 = pos2;
		g_Effect[i + sn].pos_moving_pattern = pos_moving_pattern;
		g_Effect[i + sn].size = size1;
		g_Effect[i + sn].size1 = size1;
		g_Effect[i + sn].size2 = size2;
		g_Effect[i + sn].size_moving_pattern = size_moving_pattern;
		g_Effect[i + sn].Clarity_min = Clarity_min;
		g_Effect[i + sn].Clarity_max = Clarity_max;
		g_Effect[i + sn].Clarity = g_Effect[i + sn].Clarity_min;
		g_Effect[i + sn].fadeIn_count = fadeIn_count;
		g_Effect[i + sn].all_count = all_count;
		g_Effect[i + sn].fadeOut_count = fadeOut_count;
		g_Effect[i + sn].now_count = 0;
		g_Effect[i + sn].moving_count = moving_count;
		g_Effect[i + sn].rot = AngleToRadian(rot_angle1);
		g_Effect[i + sn].rot_angle = rot_angle1;
		g_Effect[i + sn].rot_angle1 = rot_angle1;
		g_Effect[i + sn].rot_angle2 = rot_angle2;
		g_Effect[i + sn].rot_moving_pattern = rot_moving_pattern;
		g_Effect[i + sn].rot_count = 0;

		g_Effect[i + sn].drawpos = g_Effect[i + sn].pos1;
		g_Effect[i + sn].use_array_num = i + sn;
		g_Effect[i + sn].isUse = true;

		g_Effect[i + sn].id = GetTextureData(46);		// Number��46�Ԃɐݒ肳��Ă�


		// ����������������`����Ă����B�E���獶�Ɍ������ĕ`���Ă���
		// ����\�����錅�̐���
		int nownum = number % 10;

		float interval_magnification = 0.7f;		// �����̊��o�̔{��

		// ��������̏ꍇ�Ƌ����̏ꍇ�ŕ\�����@���ꍇ��������
		if (digit % 2 == 0)
		{
			// �����̏ꍇ			�^�񒆂̌����Ǝ��̐��̊Ԃɐ^�񒆂�����
			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			g_Effect[i + sn].pos.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification - (size1.x * interval_magnification / 2);
			g_Effect[i + sn].pos1.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification - (size1.x * interval_magnification / 2);
			g_Effect[i + sn].pos2.x = pos2.x + (middle_digit - i) * size2.x * interval_magnification - (size2.x * interval_magnification / 2);
		}
		else
		{
			// ��̏ꍇ		�w�肵�����W���^�񒆂̌����̒��S�ɗ���
			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			g_Effect[i + sn].pos.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification;
			g_Effect[i + sn].pos1.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification;
			g_Effect[i + sn].pos2.x = pos2.x + (middle_digit - i) * size2.x * interval_magnification;
		}

		g_Effect[i + sn].tx = 1.0f / 10;						// �e�N�X�`��1�}�X�̕�
		g_Effect[i + sn].ty = 1.0f / 2;						// �e�N�X�`��1�}�X�̍���
		g_Effect[i + sn].sx = g_Effect[i + sn].tx * nownum;			// �e�N�X�`���̃X�^�[�g�ʒux
		g_Effect[i + sn].sy = 0.0f;							// �e�N�X�`���̃X�^�[�g�ʒuy

		// ���̌���
		number /= 10;
	}
	// �X�^�[�g�ʒu�ƘA�Ԃ�������Ԃ�
	back_array[0] = sn;
	back_array[1] = digit;
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
	case 15:
		return stage_select1_15;
		break;
	case 16:
		return stage_select2_16;
		break;
	case 17:
		return stage_select3_17;
		break;
	case 18:
		return stage_select4_18;
		break;
	case 19:
		return stage_select5_19;
		break;
	case 20:
		return stage_choice1_20;
		break;
	case 21:
		return stage_choice2_21;
		break;
	case 22:
		return stage_choice3_22;
		break;
	case 23:
		return stage_choice4_23;
		break;
	case 24:
		return stage_choice5_24;
		break;
	case 25:
		return stage_mission_background_25;
		break;
	case 26:
		return stage_mission0_26;
		break;
	case 27:
		return stage_mission1_27;
		break;
	case 28:
		return stage_mission2_28;
		break;
	case 29:
		return stage_mission3_29;
		break;
	case 30:
		return stage_mission4_30;
		break;
	case 31:
		return stage_mission5_31;
		break;
	case 32:
		return stage_mission6_32;
		break;
	case 33:
		return stage_mission7_33;
		break;
	case 34:
		return stage_mission8_34;
		break;
	case 35:
		return stage_mission9_35;
		break;
	case 36:
		return stage_mission10_36;
		break;
	case 37:
		return stage_mission11_37;
		break;
	case 38:
		return stage_mission12_38;
		break;
	case 39:
		return stage_mission13_39;
		break;
	case 40:
		return stage_mission14_40;
		break;
	case 41:
		return stage_mission15_41;
		break;
	case 42:
		return stage_mission16_42;
		break;
	case 43:
		return stage_mission17_43;
		break;
	case 44:
		return stage_mission18_44;
		break;
	case 45:
		return stage_mission19_45;
		break;
	case 46:
		return number_46;
		break;
	case 47:
		return next_47;
		break;
	case 48:
		return white_48;
		break;
	case 49:
		return mapback_49;
		break;
	//case 50:
	//	return maparrow_50;
	//	break;
	//case 51:
	//	return maptext_51;
	//	break;
	case 52:
		return pickup_green_52;
		break;
	case 53:
		return pickup_red_53;
		break;
	case 54:
		return batten_red_54; 
			break;
	case 55:
		return gameover_55;
		break;		
	case 56:
		return restart_56;
		break;
	case 57:
		return stagename_57;
		break;
	case 58:
		return gameover_back_58;
		break;
	case 59:
		return gameover_place_59;
		break;
	case 60:
		return titleback_60;
		break;
	case 61:
		return worldback_61;
		break;
	case 62:
		return pause_62;
		break;
	case 63:
		return commentary_63;
		break;
	
	}

	// �ǂ��ɂ����ǂ蒅���Ȃ������ꍇ
	exit(21);
	return -1;
}


// �ŏ���use_array_num���K�v�����A����use_array_num�̃G�t�F�N�g��r���ł��ύX�ł���,SerialNumber�̓f�t�H���g�֐��Ńf�t�H=1
void ChangeEffect(int use_array_num, int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(29);

	for (int i = 0; i < SerialNumber; i++)
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


// use_array_num�̃G�t�F�N�g��now_count������ݒ�ł���,SerialNumber�̓f�t�H���g�֐��Ńf�t�H=1
void ChangeEffectCount(int use_array_num, int setcount, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(30);

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].now_count = setcount;
	}
	return;
}

// �e�N�X�`��������ς����
void ChangeEffectTexture(int use_array_num, int setTexid, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(31);

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].id = GetTextureData(setTexid);
	}
	return;
}

// �F������ς����
void ChangeEffectColor(int use_array_num, float r, float g, float b, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(32);

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].color = D3DXCOLOR(r, g, b, g_Effect[use_array_num].Clarity);
	}
	return;
}

// �����x������ς����,min��max���ς��̂Œ���
void ChangeEffectClarity(int use_array_num, float clarity, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(33);

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].Clarity = clarity;
		g_Effect[use_array_num].Clarity_min = clarity;
		g_Effect[use_array_num].Clarity_max = clarity;
	}
	return;
}

// �z��̉��Ԗڂ����w�肵�ăG�t�F�N�g������,SerialNumber�̓f�t�H���g�֐��Ńf�t�H=1
void EffectBreak(int use_array_num, int SerialNumber)
{
	// �����l��G���[�ł���-1�������ꍇ�������̓}�b�N�X�G�t�F�N�g�𒴂����l�������ꍇ�Ȃɂ����Ȃ��B�G���[
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return;
		//exit(34);


	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num + i].isUse = false;
		g_Effect[use_array_num + i].use_array_num = -1;
	}

	return;
}

// �z��̉��Ԗڂ̃G�t�F�N�g�̍��̍��W��Ԃ�
D3DXVECTOR2 GetEffectPos(int use_array_num)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(35);

	return g_Effect[use_array_num].pos;
}

// �z��̉��Ԗڂ̃G�t�F�N�g�̍��̃T�C�Y��Ԃ�
D3DXVECTOR2 GetEffectSize(int use_array_num)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(36);

	return g_Effect[use_array_num].size;
}
