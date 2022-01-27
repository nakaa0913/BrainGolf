
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
static int number_46;		// 46

static int next_47;			// 47
static int white_48;		// 48
static int mapback_49;		// 49
//static int maparrow_50;	// 50 �g��Ȃ�
//static int maptext_51;	// 51 �g��Ȃ�

// placement�Ŏg�����
static int pickup_green_52; // 52
static int pickup_red_53;	// 53
static int batten_red_54;	// 54

// �Q�[���I�[�o�[
static int gameover_55;		 // 55
static int restart_56;		 // 56
static int stagename_57;	 // 57
static int gameover_back_58; // 58
static int gameover_place_59;// 59

static int titleback_60;	// 60
static int worldback_61;	// 61

//�@�|�[�Y���
static int pause_62;			// 62
static int commentary_63;		// 62
static int above_64;			// 64
static int retry_65;			// 65
static int pause_mission_66;	// 66
static int pause_stageselect_67;// 67

// �M�~�b�N�����`�b�v
static int GimmickDescriptionChip_68;// 68
static int pickup_GimmickDescription_69;// 69

static int batu_70;	// 70

//�N���u�̎��
static int rollball_71;
static int flyball_72;

//�|�[�Y��ʂ̊O�g
static int around_73;

//���U���g��ʒǉ�
static int note_74;
static int MAPButton1_75;
static int MAPButton2_76;
static int NEXTSTAGE1_77;
static int NEXTSTAGE2_78;
static int RETRY1_79;
static int RETRY2_80;
static int Ribon_81;
static int NoJewlry_82;
static int RedJewlry_83;
static int BlueJewlry_84;
static int YellowJewlry_85;

// �X�e�[�W�I�����
static int mission_waku_1_86;
static int pin_87;
static int botan_waku_1_88;

static int senntaku_haikei_1_89;
static int senntaku_haikei_2_90;
static int botan_1_91;
static int botan_2_92;

// �^�C�g��
static int title_click_93;
static int title_logo_94;
static int title_bokashi_95;

// ���U���g
static int result_go_96;
static int kekkahappyou_97;
static int kekkahappyou_2_98;
static int haiti_99;
static int haiti_2_100;
static int chara_101;

// �|�[�Y
static int migi_102;
static int hidari_103;

// ���U���g�̃N���A�^�C���̕\���̎��̐���
static int number_104;

// �|�[�Y�ƃ}�E�X����̂��
static int pozu_105;
static int pozu_2_106;
static int utu_107;
static int wejji_108;
static int doraiba_109;

// �z�u��ʂ̎��g������
static int play_botan_0_110;
static int play_botan_1_111;
static int home_botan_0_112;
static int home_botan1_113;
static int mob_placement_114;

//�|�[�Y��ʒǉ�
static int ue_115;
static int ue_2_116;
static int mission_117;
static int mission_2_118;

// number�ǉ�
static int number_2_119;
static int number_3_120;
static int nobasibou_121;

//�^�C�g���ɖ߂�{�^��
static int title_botan_122;
static int title_botan2_123;

void InitEffect(void)
{
	//�e�N�X�`���̖��O
	ao_0 = LoadTexture("data/TEXTURE/ao.png");
	aka_1 = LoadTexture("data/TEXTURE/result/advice.png");
	//tako_2 = LoadTexture("data/TEXTURE/result/tako.png");
	title_3 = LoadTexture("data/TEXTURE/title/title_effect.png");
	black_4 = LoadTexture("data/TEXTURE/other_effect/black.png");
	clear_5 = LoadTexture("data/TEXTURE/result/CLEAR.png");
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

	number_46 = LoadTexture("data/TEXTURE/result/number_02.png");
	next_47 = LoadTexture("data/TEXTURE/result/allnext.png");
	white_48 = LoadTexture("data/TEXTURE/result/fade_white.png");
	mapback_49 = LoadTexture("data/TEXTURE/result/map_back.png");
	//maparrow_50 = LoadTexture("data/TEXTURE/result/map_arrow.png");
	//maptext_51 = LoadTexture("data/TEXTURE/result/map_text.png");

	pickup_green_52 = LoadTexture("data/TEXTURE/placement/pickup_green.png");
	pickup_red_53 = LoadTexture("data/TEXTURE/placement/pickup_red.png");
	batten_red_54 = LoadTexture("data/TEXTURE/placement/batten_red.png");

	gameover_55 = LoadTexture("data/TEXTURE/result/gameover/OVER.png");
	restart_56 = LoadTexture("data/TEXTURE/result/gameover/restart.png");
	stagename_57 = LoadTexture("data/TEXTURE/result/gameover/stagename.png");
	gameover_back_58 = LoadTexture("data/TEXTURE/result/gameover/gameover_back.png");
	gameover_place_59 = LoadTexture("data/TEXTURE/result/gameover/gameover_place.png");

	titleback_60 = LoadTexture("data/TEXTURE/select/titleback.png");
	worldback_61 = LoadTexture("data/TEXTURE/select/worldback.png");

	pause_62 = LoadTexture("data/TEXTURE/pause/pause.png");
	commentary_63 = LoadTexture("data/TEXTURE/pause/commentary.png");
	above_64 = LoadTexture("data/TEXTURE/pause/above.png");
	retry_65 = LoadTexture("data/TEXTURE/pause/retry.png");
	pause_mission_66 = LoadTexture("data/TEXTURE/pause/mission.png");
	pause_stageselect_67 = LoadTexture("data/TEXTURE/pause/stageselect.png");

	GimmickDescriptionChip_68 = LoadTexture("data/TEXTURE/game/GimmickDescription/gimmick.png");
	pickup_GimmickDescription_69 = LoadTexture("data/TEXTURE/game/GimmickDescription/pickup_GimmickDescription.png");
	
	batu_70 = LoadTexture("data/TEXTURE/pause/batu.png");

	rollball_71 = LoadTexture("data/TEXTURE/select/2.png");
	flyball_72 = LoadTexture("data/TEXTURE/select/1.png");

	around_73 = LoadTexture("data/TEXTURE/pause/around.png");

	note_74 = LoadTexture("data/TEXTURE/result/note.png");
	MAPButton1_75 = LoadTexture("data/TEXTURE/result/1MAP_button.png");
	MAPButton2_76 = LoadTexture("data/TEXTURE/result/2MAP_button.png");
	NEXTSTAGE1_77 = LoadTexture("data/TEXTURE/result/1NEXTSTAGE_button.png");
	NEXTSTAGE2_78 = LoadTexture("data/TEXTURE/result/2NEXTSTAGE_button.png");
	RETRY1_79 = LoadTexture("data/TEXTURE/result/1RETRY_button.png");
	RETRY2_80 = LoadTexture("data/TEXTURE/result/2RETRY_button.png");
	Ribon_81 = LoadTexture("data/TEXTURE/result/ribon.png");
	NoJewlry_82 = LoadTexture("data/TEXTURE/result/jewelry_nasi.png");
	RedJewlry_83 = LoadTexture("data/TEXTURE/result/jewelry_Red.png");
	BlueJewlry_84 = LoadTexture("data/TEXTURE/result/jewelry_Blue.png");
	YellowJewlry_85 = LoadTexture("data/TEXTURE/result/jewelry_Yellow.png");

	mission_waku_1_86 = LoadTexture("data/TEXTURE/select/mission_waku_1.png");
	pin_87 = LoadTexture("data/TEXTURE/select/pin.png");
	botan_waku_1_88 = LoadTexture("data/TEXTURE/select/botan_waku_1.png");

	senntaku_haikei_1_89 = LoadTexture("data/TEXTURE/select/senntaku_haikei_1a.jpg");
	senntaku_haikei_2_90 = LoadTexture("data/TEXTURE/select/senntaku_haikei_2a.jpg");
	botan_1_91 = LoadTexture("data/TEXTURE/select/botan_1.png");
	botan_2_92 = LoadTexture("data/TEXTURE/select/botan_2.png");

	title_click_93 = LoadTexture("data/TEXTURE/title/title_click.png");
	title_logo_94 = LoadTexture("data/TEXTURE/title/titlerogo_4.png");
	title_bokashi_95 = LoadTexture("data/TEXTURE/select/senntaku_haikei_3a.jpg");

	result_go_96 = LoadTexture("data/TEXTURE/result/result.png");
	kekkahappyou_97 = LoadTexture("data/TEXTURE/result/kekkahappyou.png");
	kekkahappyou_2_98 = LoadTexture("data/TEXTURE/result/kekkahappyou_2.png");
	haiti_99 = LoadTexture("data/TEXTURE/result/haiti.png");
	haiti_2_100 = LoadTexture("data/TEXTURE/result/haiti_2.png");
	chara_101 = LoadTexture("data/TEXTURE/result/ribon_chara.png");

	migi_102 = LoadTexture("data/TEXTURE/pause/migi.png");
	hidari_103 = LoadTexture("data/TEXTURE/pause/hidari.png");

	number_104 = LoadTexture("data/TEXTURE/other_effect/number.png");

	pozu_105 = LoadTexture("data/TEXTURE/pause/pozu.png");
	pozu_2_106 = LoadTexture("data/TEXTURE/pause/pozu_2.png");
	utu_107 = LoadTexture("data/TEXTURE/pause/utu.png");
	wejji_108 = LoadTexture("data/TEXTURE/pause/wejji.png");
	doraiba_109 = LoadTexture("data/TEXTURE/pause/doraiba.png");

	play_botan_0_110 = LoadTexture("data/TEXTURE/placement/play_botan_0.png");
	play_botan_1_111 = LoadTexture("data/TEXTURE/placement/play_botan_1.png");
	home_botan_0_112 = LoadTexture("data/TEXTURE/placement/home_botan_0.png");
	home_botan1_113 = LoadTexture("data/TEXTURE/placement/home_botan_1.png");
	mob_placement_114 = LoadTexture("data/TEXTURE/placement/mob_placement.png");

	ue_115 = LoadTexture("data/TEXTURE/pause/ue.png");
	ue_2_116 = LoadTexture("data/TEXTURE/pause/ue_2.png");
	mission_117 = LoadTexture("data/TEXTURE/pause/mission.png");
	mission_2_118 = LoadTexture("data/TEXTURE/pause/mission_2.png");

	number_2_119 = LoadTexture("data/TEXTURE/other_effect/number_2.png");
	number_3_120 = LoadTexture("data/TEXTURE/other_effect/number_3.png");
	nobasibou_121 = LoadTexture("data/TEXTURE/other_effect/nobasibou.png");


	title_botan_122 = LoadTexture("data/TEXTURE/select/title_botan.png");
	title_botan2_123 = LoadTexture("data/TEXTURE/select/title_botan_2.png");

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

void ClearEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].isUse = false;
	}
}

void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].isUse = false;
	}
	// UninitScore();
	//UnloadTexture("data/TEXTURE/ao.png");
	//UnloadTexture("data/TEXTURE/result/advice.png");
	//UnloadTexture("data/TEXTURE/title/title_effect.png");
	//UnloadTexture("data/TEXTURE/other_effect/black.png");
	//UnloadTexture("data/TEXTURE/select/1.png");
	//UnloadTexture("data/TEXTURE/select/2.png");
	//UnloadTexture("data/TEXTURE/select/mission.png");
	//UnloadTexture("data/TEXTURE/select/selectstar.png");
	//UnloadTexture("data/TEXTURE/select/selectlock.png");
	//UnloadTexture("data/TEXTURE/result/clear_star_1.png");
	//UnloadTexture("data/TEXTURE/result/clear_star_2.png");
	//UnloadTexture("data/TEXTURE/result/clear_star_3.png");
	//UnloadTexture("data/TEXTURE/result/clear_star_black_1.png");
	//UnloadTexture("data/TEXTURE/other_effect/number.png");

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
	float rot_angle1, float rot_angle2, int rot_moving_pattern, float tx, float ty, float sx, float sy)
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

			g_Effect[i].tx = tx;					// �e�N�X�`��1�}�X�̕�
			g_Effect[i].ty = ty;					// �e�N�X�`��1�}�X�̍���
			g_Effect[i].sx = sx;					// �e�N�X�`���̃X�^�[�g�ʒux
			g_Effect[i].sy = sy;					// �e�N�X�`���̃X�^�[�g�ʒuy

			g_Effect[i].isUse = true;

			g_Effect[i].id = GetTextureData(id);

			if (fadeIn_count == 0)
			{
				g_Effect[i].Clarity = g_Effect[i].Clarity_max;
			}

			// �Ō��drawpos�ɒ���
			g_Effect[i].drawpos = g_Effect[i].pos;

			// �����x�̕ω��̏������s���B
			Fadeprocess(i);

			return i;
		}

	}

	// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
	exit(1);
}


// �z��̋t�������Ă���
int SetEffectInReverse(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, float tx, float ty, float sx, float sy)
{
	for (int i = MAX_EFFECT - 1; i > 0; i--)
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

			g_Effect[i].tx = tx;					// �e�N�X�`��1�}�X�̕�
			g_Effect[i].ty = ty;					// �e�N�X�`��1�}�X�̍���
			g_Effect[i].sx = sx;					// �e�N�X�`���̃X�^�[�g�ʒux
			g_Effect[i].sy = sy;					// �e�N�X�`���̃X�^�[�g�ʒuy

			g_Effect[i].isUse = true;

			g_Effect[i].id = GetTextureData(id);

			if (fadeIn_count == 0)
			{
				g_Effect[i].Clarity = g_Effect[i].Clarity_max;
			}

			// �Ō��drawpos�ɒ���
			g_Effect[i].drawpos = g_Effect[i].pos;

			// �����x�̕ω��̏������s���B
			Fadeprocess(i);

			return i;
		}

	}

	// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
	exit(1);
}

// ���̐����̂ݑΉ�
void SetEffectNumber(int num,int* back_array, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, bool vertical, float interval_magnification, int id)
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

	bool kakutei = false;

	for (int i = 0; i < MAX_EFFECT; i++)
	{

		if (g_Effect[i].isUse == false)
		{
			last_i = i;		// �J���Ă�Ƃ��̍ŏ�����������ۑ�����B

			for (int j = last_i; j < last_i + digit; j++)
			{
				// �g���Ă�����̂���������j��for���𔲂��ĒT���Ȃ���
				if (g_Effect[i].isUse == true)
					break;

				// �Ō�܂ōs������m�肷��B
				if (j == last_i + digit - 1)
				{
					kakutei = true;
					break;
				}
			}
		}

		if (kakutei == true)
		{
			break;
		}

		// �Ō�܂ł����ĊJ���ĂȂ�������G���[
		if (i == MAX_EFFECT - 1)
			exit(25);
	}

	int sn = last_i;
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

		//g_Effect[i + sn].id = GetTextureData(46);		// Number��46�Ԃɐݒ肳��Ă�
		//g_Effect[i + sn].id = GetTextureData(119);		// Number��46�Ԃɐݒ肳��Ă�

		g_Effect[i + sn].id = GetTextureData(id);		// �łӂ�����119�ɐݒ肳��Ă�



		// ����������������`����Ă����B�E���獶�Ɍ������ĕ`���Ă���
		// ����\�����錅�̐���
		int nownum = number % 10;

		// �����̊��o�̔{�� interval_magnification �łӂ�����0.7f

		// �c�����\���o�Ȃ��Ȃ�x��������B�c�����\���Ȃ�y��������
		if (!vertical)
		{
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
		}
		else
		{
			if (digit % 2 == 0)
			{
				// �����̏ꍇ			�^�񒆂̌����Ǝ��̐��̊Ԃɐ^�񒆂�����
				// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
				g_Effect[i + sn].pos.y = pos1.y + (middle_digit - i) * size1.y * interval_magnification - (size1.y * interval_magnification / 2);
				g_Effect[i + sn].pos1.y = pos1.y + (middle_digit - i) * size1.y * interval_magnification - (size1.y * interval_magnification / 2);
				g_Effect[i + sn].pos2.y = pos2.y + (middle_digit - i) * size2.y * interval_magnification - (size2.y * interval_magnification / 2);
			}
			else
			{
				// ��̏ꍇ		�w�肵�����W���^�񒆂̌����̒��S�ɗ���
				// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
				g_Effect[i + sn].pos.y = pos1.y + (middle_digit - i) * size1.y * interval_magnification;
				g_Effect[i + sn].pos1.y = pos1.y + (middle_digit - i) * size1.y * interval_magnification;
				g_Effect[i + sn].pos2.y = pos2.y + (middle_digit - i) * size2.y * interval_magnification;
			}
		}

		// �|�W�V�����̍Ē���(�|�W�V�������[�r���O�J�E���g��0�Ȃ瓮���Ȃ��̂ōŏ�����pos2�ɒ�������)
		if (pos_moving_pattern == 0)
		{
			g_Effect[i + sn].pos.x = g_Effect[i + sn].pos2.x;
			g_Effect[i + sn].pos1.x = g_Effect[i + sn].pos2.x;

			g_Effect[i + sn].pos.y = g_Effect[i + sn].pos2.y;
			g_Effect[i + sn].pos1.y = g_Effect[i + sn].pos2.y;
		}

		g_Effect[i + sn].tx = 1.0f / 10;						// �e�N�X�`��1�}�X�̕�
		g_Effect[i + sn].ty = 1.0f / 2;						// �e�N�X�`��1�}�X�̍���
		g_Effect[i + sn].sx = g_Effect[i + sn].tx * nownum;			// �e�N�X�`���̃X�^�[�g�ʒux
		g_Effect[i + sn].sy = 0.0f;							// �e�N�X�`���̃X�^�[�g�ʒuy

		if (fadeIn_count == 0)
		{
			g_Effect[i + sn].Clarity = g_Effect[i + sn].Clarity_max;
		}

		// �Ō��drawpos�ɒ���
		g_Effect[i + sn].drawpos = g_Effect[i + sn].pos;


		// �����x�̕ω��̏������s���B
		Fadeprocess(i + sn);

		// ���̌���
		number /= 10;
	}
	// �X�^�[�g�ʒu�ƘA�Ԃ�������Ԃ�
	back_array[0] = sn;
	back_array[1] = digit;
}

// �ݒu�G�t�F�N�g�i���o�[��00:00�̂悤�ɕ��ƕb�ŕ\������B�������ł͕b�ł��炤�B
void SetEffectTimeNumber(int num, int* back_array, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern)
{
	int min = num / 60;
	int second = num - min * 60;

	int num1 = min / 10;		// 00;00�̍�����1�Ԗ�
	int num2 = min % 10;
	int num3 = second / 10;
	int num4 = second % 10;

	int digit = 5;		// 5�ŌŒ�(00:00)

	// �����̐^�񒆂𒲂ׂ�B���������W�̒��S�ƂȂ�
	int middle_digit = digit / 2;

	int serial = 0;
	int nextnum = -1;

	int last_i = -1;
	bool kakutei = false;

	for (int i = 0; i < MAX_EFFECT; i++)
	{

		if (g_Effect[i].isUse == false)
		{
			last_i = i;		// �J���Ă�Ƃ��̍ŏ�����������ۑ�����B

			for (int j = last_i; j < last_i + digit; j++)
			{
				// �g���Ă�����̂���������j��for���𔲂��ĒT���Ȃ���
				if (g_Effect[i].isUse == true)
					break;

				// �Ō�܂ōs������m�肷��B
				if (j == last_i + digit - 1)
				{
					kakutei = true;
					break;
				}
			}
		}

		if (kakutei == true)
		{
			break;
		}

		// �Ō�܂ł����ĊJ���ĂȂ�������G���[
		if (i == MAX_EFFECT - 1)
			exit(25);
	}

	int sn = last_i;		// startnum

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

		//g_Effect[i + sn].id = GetTextureData(104);		// Number��46�Ԃɐݒ肳��Ă�
		g_Effect[i + sn].id = GetTextureData(119);		// Number��46�Ԃɐݒ肳��Ă�


		// ����������������`����Ă����B�E���獶�Ɍ������ĕ`���Ă���

		float interval_magnification = 0.8f;		// �����̊��o�̔{��

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
		int UVxNum = 0;
		int UVyNum = 0;
		switch (i)
		{
		case 0:
			UVxNum = num4;
			break;
		case 1:
			UVxNum = num3;
			break;
		case 2:
			UVxNum = 2;			// : �̕\��
			UVyNum = 1;
			break;
		case 3:
			UVxNum = num2;
			break;
		case 4:
			UVxNum = num1;
			break;
		default:
			break;
		}

		g_Effect[i + sn].tx = 1.0f / 10;						// �e�N�X�`��1�}�X�̕�
		g_Effect[i + sn].ty = 1.0f / 2;							// �e�N�X�`��1�}�X�̍���

		g_Effect[i + sn].sx = g_Effect[i + sn].tx * UVxNum;			// �e�N�X�`���̃X�^�[�g�ʒux(�����Ńe�N�X�`����UV�l�ݒ�)
		g_Effect[i + sn].sy = g_Effect[i + sn].ty * UVyNum;							// �e�N�X�`���̃X�^�[�g�ʒuy

		if (fadeIn_count == 0)
		{
			g_Effect[i + sn].Clarity = g_Effect[i + sn].Clarity_max;
		}

		// �Ō��drawpos�ɒ���
		g_Effect[i + sn].drawpos = g_Effect[i + sn].pos;

		// �����x�̕ω��̏������s���B
		Fadeprocess(i + sn);

		// ���̌���
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

			// �����x�̕ω��̏������s���B
			Fadeprocess(i);


			return i;
		}

	}

	// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
	exit(1);
}


void Fadeprocess(int i)
{
	////0�`fadeIn
	//if (g_Effect[i].now_count < 0 + g_Effect[i].fadeIn_count)
	//{
	//	float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeIn_count;
	//	g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * g_Effect[i].now_count;
	//}
	////fadeIn�`all
	//if (g_Effect[i].now_count >= 0 + g_Effect[i].fadeIn_count &&
	//	g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count)
	//{
	//	g_Effect[i].Clarity = g_Effect[i].Clarity_max;
	//}
	////all�`fadeOut
	//if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count + g_Effect[i].all_count &&
	//	g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count)
	//{
	//	float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeOut_count;
	//	g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * ((g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count) - g_Effect[i].now_count);
	//}

	int sadef = 0;
	//0�`fadeIn
	if (g_Effect[i].now_count < g_Effect[i].fadeIn_count && g_Effect[i].fadeIn_count != 0)
	{
		float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeIn_count;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * g_Effect[i].now_count;
		if (g_Effect[i].id == 84)
			sadef = 1;
	}
	//fadeIn�`all
	else if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count &&
		g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count)
	{
		g_Effect[i].Clarity = g_Effect[i].Clarity_max;
		if (g_Effect[i].id == 84)
			sadef = 2;
	}
	//all�`fadeOut
	else if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count + g_Effect[i].all_count &&
		g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count)
	{
		float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeOut_count;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * ((g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count) - g_Effect[i].now_count);
		if (g_Effect[i].id == 84)
			sadef = 3;
	}
	if (g_Effect[i].id == 84)
	{
		if (g_Effect[i].all_count != 999)
			int sdef = 3434;
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
	case 64:
		return above_64;
		break;
	case 65:
		return retry_65;
		break;
	case 66:
		return pause_mission_66;
		break;
	case 67:
		return pause_stageselect_67;
		break;
	case 68:
		return GimmickDescriptionChip_68;
		break;
	case 69:
		return pickup_GimmickDescription_69;
		break;
	case 70:
		return batu_70;
		break;
	case 71:
		return rollball_71;
		break;
	case 72:
		return flyball_72;
		break;
	case 73:
		return around_73;
		break;
	case 74:
		return note_74;
		break;
	case 75:
		return MAPButton1_75;
		break;
	case 76:
		return MAPButton2_76;
		break;
	case 77:
		return NEXTSTAGE1_77;
		break;
	case 78:
		return NEXTSTAGE2_78;
		break;
	case 79:
		return RETRY1_79;
		break;
	case 80:
		return RETRY2_80;
		break;
	case 81:
		return Ribon_81;
		break;
	case 82:
		return NoJewlry_82;
		break;
	case 83:
		return RedJewlry_83;
		break;
	case 84:
		return BlueJewlry_84;
		break;
	case 85:
		return YellowJewlry_85;
		break;
	case 86:
		return mission_waku_1_86;
		break;
	case 87:
		return pin_87;
		break;
	case 88:
		return botan_waku_1_88;
		break;
	case 89:
		return senntaku_haikei_1_89;
		break;
	case 90:
		return senntaku_haikei_2_90;
		break;
	case 91:
		return botan_1_91;
		break;
	case 92:
		return botan_2_92;
		break;
	case 93:
		return title_click_93;
		break;
	case 94:
		return title_logo_94;
		break;
	case 95:
		return title_bokashi_95;
		break;
	case 96:
		return result_go_96;
		break;
	case 97:
		return kekkahappyou_97;
		break;
	case 98:
		return kekkahappyou_2_98;
		break;
	case 99:
		return haiti_99;
		break;
	case 100:
		return haiti_2_100;
		break;
	case 101:
		return chara_101;
		break;
	case 102:
		return migi_102;
		break;
	case 103:
		return hidari_103;
		break;
	case 104:
		return number_104;
		break;
	case 105:
		return pozu_105;
		break;
	case 106:
		return pozu_2_106;
		break;
	case 107:
		return utu_107;
		break;
	case 108:
		return wejji_108;
		break;
	case 109:
		return doraiba_109;
		break;
	case 110:
		return play_botan_0_110;
		break;
	case 111:
		return play_botan_1_111;
		break;
	case 112:
		return home_botan_0_112;
		break;
	case 113:
		return home_botan1_113;
		break;
	case 114:
		return mob_placement_114;
		break;
	case 115:
		return ue_115;
		break;
	case 116:
		return ue_2_116;
		break;
	case 117:
		return mission_117;
		break;
	case 118:
		return mission_2_118;
		break;
	case 119:
		return number_2_119;
		break;
	case 120:
		return number_3_120;
		break;
	case 121:
		return nobasibou_121;
		break;
	case 122:
		return title_botan_122;
		break;
	case 123:
		return title_botan2_123;
		break;
	}
	
	// �ǂ��ɂ����ǂ蒅���Ȃ������ꍇ
	exit(21);
	return -1;
}

// id = -1 �Ńe�N�X�`�����̂܂܁B�ŏ���use_array_num���K�v�����A����use_array_num�̃G�t�F�N�g��r���ł��ύX�ł���,SerialNumber�̓f�t�H���g�֐��Ńf�t�H=1, ��������pos1��99999�Ȃ�΁A���̃G�t�F�N�g�̍��W����pos2�̕������ړ�����ݒ�B
void ChangeEffect(int use_array_num, int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, int SerialNumber)
{
	/*if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(29);*/
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return;


	int PlaySerial = 0;			// �A�Ԃ������Ɛ����Ă��邩�ǂ���

	for (int i = 0; i < SerialNumber; i++)
	{
		int new_array_num = use_array_num + i;
		//g_Effect[new_array_num].id = id;	���ň����œ��͂����l�ɂ���ăe�N�X�`����ύX���Ă���
		if (pos1.x >= 99998)			// ��������pos1��99999�Ȃ�΁A���̃G�t�F�N�g�̍��W����pos2�̕������ړ�����ݒ�B
		{
			//g_Effect[new_array_num].pos = g_Effect[new_array_num].pos;
			g_Effect[new_array_num].pos1 = g_Effect[new_array_num].pos;
			g_Effect[new_array_num].pos2 = g_Effect[new_array_num].pos + pos2;
		}
		else
		{
			g_Effect[new_array_num].pos = pos1;
			g_Effect[new_array_num].pos1 = pos1;
			g_Effect[new_array_num].pos2 = pos2;
		}
		g_Effect[new_array_num].pos_moving_pattern = pos_moving_pattern;
		if (size1.x >= 99998)			// ��������size1��99999�Ȃ�΁A���̃G�t�F�N�g�̃T�C�Y����size2�̃T�C�Y�������ݒ�B
		{
			//g_Effect[new_array_num].size = g_Effect[new_array_num].size;
			g_Effect[new_array_num].size1 = g_Effect[new_array_num].size;
			g_Effect[new_array_num].size2 = g_Effect[new_array_num].size + size2;
		}
		else
		{
			g_Effect[new_array_num].size = size1;
			g_Effect[new_array_num].size1 = size1;
			g_Effect[new_array_num].size2 = size2;
		}
		g_Effect[new_array_num].size_moving_pattern = size_moving_pattern;
		g_Effect[new_array_num].Clarity_min = Clarity_min;
		g_Effect[new_array_num].Clarity_max = Clarity_max;
		if(fadeIn_count == 0)									// �A�b�v�f�[�g�G�t�F�N�g�̒��̃t�F�[�h�v���Z�X�����̌���s�����΂悢���AEffectUpdata�̂��`�F���W�G�t�F�N�g���x�������肵���ꍇ�s���Ȃ��̂ŁB
			g_Effect[new_array_num].Clarity = g_Effect[new_array_num].Clarity_max;
		else
			g_Effect[new_array_num].Clarity = g_Effect[new_array_num].Clarity_min;
		g_Effect[new_array_num].fadeIn_count = fadeIn_count;
		g_Effect[new_array_num].all_count = all_count;
		g_Effect[new_array_num].fadeOut_count = fadeOut_count;
		g_Effect[new_array_num].now_count = 0;
		g_Effect[new_array_num].moving_count = moving_count;
		g_Effect[new_array_num].rot = AngleToRadian(rot_angle1);
		g_Effect[new_array_num].rot_angle = rot_angle1;
		g_Effect[new_array_num].rot_angle1 = rot_angle1;
		g_Effect[new_array_num].rot_angle2 = rot_angle2;
		g_Effect[new_array_num].rot_moving_pattern = rot_moving_pattern;
		g_Effect[new_array_num].rot_count = 0;

		g_Effect[new_array_num].drawpos = g_Effect[new_array_num].pos1;
		//g_Effect[new_array_num].new_array_num = 
		g_Effect[new_array_num].isUse = true;

		if (id == -1)
			g_Effect[new_array_num].id = g_Effect[new_array_num].id;
		else
			g_Effect[new_array_num].id = GetTextureData(id);

		// �����x�̕ω��̏������s���B
		Fadeprocess(new_array_num);

		PlaySerial++;

		// �A�Ԃ̕��I������烊�^�[���Ŋ֐��𔲂���
		if(PlaySerial == SerialNumber)
			return;


	}

	// MAX_EFFECT �𒴂������G�t�F�N�g���쐬���悤�Ƃ���ƃQ�[����������
	exit(1);
}


// use_array_num�̃G�t�F�N�g��now_count������ݒ�ł���,SerialNumber�̓f�t�H���g�֐��Ńf�t�H=1
void ChangeEffectCount(int use_array_num, int setcount, int SerialNumber)
{
	/*if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(30);*/
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return;

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].now_count = setcount;

		// �����x�̕ω��̏������s���B
		Fadeprocess(use_array_num);
	}
	return;
}


// ���W������ς����(������pos1,pos2�Ƃ��ɌŒ肳��Ă��܂�)
void ChangeEffectPos(int use_array_num, float setpos_x, float setpos_y, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(31);

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].pos = D3DXVECTOR2(setpos_x, setpos_y);
		g_Effect[use_array_num].pos1 = D3DXVECTOR2(setpos_x, setpos_y);
		g_Effect[use_array_num].pos2 = D3DXVECTOR2(setpos_x, setpos_y);
	}
	return;
}

// �e�N�X�`��������ς����
void ChangeEffectTexture(int use_array_num, int setTexid, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(32);

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
		exit(33);

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].color = D3DXCOLOR(r, g, b, g_Effect[use_array_num].Clarity);

		// �����x�̕ω��̏������s���B
		Fadeprocess(use_array_num);
	}
	return;
}

// �����x������ς����,min��max���ς��̂Œ���
void ChangeEffectClarity(int use_array_num, float clarity, int SerialNumber)
{
	/*if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(34);*/

	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return;

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].Clarity = clarity;
		g_Effect[use_array_num].Clarity_min = clarity;
		g_Effect[use_array_num].Clarity_max = clarity;

		// �����x�̕ω��̏������s���B
		Fadeprocess(use_array_num);
	}
	return;
}

// �z��̉��Ԗڂ����w�肵�ăG�t�F�N�g������,SerialNumber�̓f�t�H���g�֐��Ńf�t�H=1
void EffectBreak(int use_array_num, int SerialNumber)
{
	// �����l��G���[�ł���-1�������ꍇ�������̓}�b�N�X�G�t�F�N�g�𒴂����l�������ꍇ�Ȃɂ����Ȃ��B�G���[
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return;
		//exit(35);

	int PlaySerial = 0;			// �A�Ԃ������Ɛ����Ă��邩�ǂ���


	for (int i = 0; i < SerialNumber; i++)
	{
		int new_array_num = use_array_num + i;

		if (use_array_num + i == 25)
			int fdffef = 4;

		g_Effect[use_array_num + i].isUse = false;
		g_Effect[use_array_num + i].use_array_num = -1;

		PlaySerial++;

		// �A�Ԃ̕��I������烊�^�[���Ŋ֐��𔲂���
		if (PlaySerial == SerialNumber)
			return;
	}

	exit(35);
}

// �z��̉��Ԗڂ̃G�t�F�N�g�̍��̍��W��Ԃ�
D3DXVECTOR2 GetEffectPos(int use_array_num)
{
	/*if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(36);*/

	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return D3DXVECTOR2(300.f, 300.f);

	return g_Effect[use_array_num].pos;
}

// �z��̉��Ԗڂ̃G�t�F�N�g�̍��̃T�C�Y��Ԃ�
D3DXVECTOR2 GetEffectSize(int use_array_num)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(37);

	return g_Effect[use_array_num].size;
}

// �z��̉��Ԗڂ̃G�t�F�N�g�̍��̓����x��Ԃ�
float GetEffectClarity(int use_array_num)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(38);

	return g_Effect[use_array_num].Clarity;
}

// �z��̉��Ԗڂ̃G�t�F�N�g�̍���now_count��Ԃ�
int GetEffectnow_count(int use_array_num)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(39);

	return g_Effect[use_array_num].now_count;
}
