/*==============================================================================

   �Q�[������ [game.cpp]
														 Author :
														 Date   :a
--------------------------------------------------------------------------------

==============================================================================*/

#include<iostream>
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "enemy_emitter.h"
#include "bullet.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "bg.h"
#include "result.h"
#include"stageselect.h"
#include "Texture.h"
#include "sprite.h"
#include "effect.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "worldselect.h"
#include "keyboard.h"
#include "mouse.h"
#include "placement.h"
#include "savedata.h"

/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/
#define USE_STAGE_MAX	(20)	// ���ۂɎ�������Ďg���X�e�[�W�̐�
#define PAGE_MAX		(2)		// �y�[�W��

/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static STAGESELECT g_StageSelect;

static int	g_TextureNo = 0;	// �e�N�X�`�����
static int	g_BGMNo = 0;		// BGM���ʎq
static int g_SENo = 0;

int			UseArrow;
int			UseEnter;


//static int world_1_background;
//static int world_2_background;
//static int world_3_background;
//static int world_4_background;
//static int world_5_background;
//
//static int world_1_stagechoice;
//static int world_2_stagechoice;
//static int world_3_stagechoice;
//static int world_4_stagechoice;
//static int world_5_stagechoice;
//
//static int world_1_mission;

int NowWorld = 0;				   //���I�����Ă���
int tex_NowWorld_background = -1;  //�w�i
int tex_Page_background_EffectArray[2] = { -1, -1 };  //�y�[�W�w�i�̂��߂̔z��
int tex_StageNum_background_EffectArray[2] = { -1, -1 };  //�X�e�[�W�ԍ�(1���G�ň���)�̂��߂̔z��
int tex_Pin_EffectArray = -1;			// �s���̃G�t�F�N�g�z��
int tex_Waku_EffectArray = -1;			// ���g�̃G�t�F�N�g�z��
int tex_NowWorld_stagechoice = -1; //�X�e�[�W�I���̎l�p�����
int tex_NowWorld_mission = -1;     //�~�b�V����

// �I�������Ƃ��̏����Ŏg��
int now_stage_select_EffectArray = -1;			// �s��
int now_stage_selectWaku_EffectArray = -1;			// ���g
int now_stagenum_select_EffectArray[2] = { -1, -1 };
int* p_now_stagenum_select_EffectArray = now_stagenum_select_EffectArray;
int stage_EffectArray[USE_STAGE_MAX];
int Arrow_EffectArray[2];				// �����E���̂��߂̔z��
int stage_star_EffectArray[USE_STAGE_MAX][MAX_MISSION];
bool stage_select_once = false;
int stage_select_once_time = 0;

bool StageDecision = false;				// �G���^�[�����N���b�N�ŃX�e�[�W���m�肳�����瑼�̂Ƃ��Ɉړ��ł��Ȃ�����

int change_cool = 30;

int change_count = 0;

static int cahngetime = 1;		// 60�t���[�������ăy�[�W���ς��

static bool changing = false;			// �y�[�W�`�F���W�����ǂ���

static int now_page = 0;		// ���݊J���Ă���y�[�W

int now_stagenum = -1;			// 1~20�ł̌��݂̃X�e�[�W�ԍ�

float change_page_interval = 0.0f;


//int stageNumber_EffectArray[2] = { 0, 0 };
//int* p_stageNumber_EffectArray[20];				// 20�X�e�[�W���̔z����|�C���^�[�ŗp�ӂ���


int stageNumber_EffectArray[20][2];
//int* p_stageNumber_EffectArray;				// 20�X�e�[�W���̔z����|�C���^�[�ŗp�ӂ���

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitStageSelect(void)
{
	for (int i = 0; i < 20; i++)
	{
		stageNumber_EffectArray[i][0] = 0;
		stageNumber_EffectArray[i][1] = 0;
	}
	now_stagenum_select_EffectArray[0] = -1;
	now_stagenum_select_EffectArray[1] = -1;

	// �z�u�V�[������߂��Ă����Ƃ��ɉ��y����d�ɂȂ�Ȃ��悤�ɁB
	StopSoundAll();

	now_page = 0;
	change_page_interval = 0.0f;

	change_count = 0;

	changing = false;

	g_StageSelect.select_x = 0;
	g_StageSelect.select_y = 0;

	StageDecision = false;

	UseArrow = 0;
	UseEnter = 0;

	// ���ׂ��X�e�[�W��\������Ƃ��̃G�t�F�N�g�z��̏�����
	for (int i = 0; i < USE_STAGE_MAX; i++)
	{
		stage_EffectArray[i] = -1;
		for (int j = 0; j < MAX_MISSION; j++)
		{
			stage_star_EffectArray[i][j] = -1;
		}
	}



	g_BGMNo = LoadSound("data/BGM/���Ńo�^�t���C.wav");
	SetVolume(g_BGMNo, 0.8f);
	//255(-1)�����[�v�w�肷��Ɩ������[�v
	PlaySound(g_BGMNo, -1);

	g_StageSelect.selecttime = 0;

	NowWorld = GetNowWorld();


	//
	if (NowWorld == 1)
	{
		tex_NowWorld_background = 15;
		tex_NowWorld_stagechoice = 20;
		tex_NowWorld_mission = 25;
	}

	if (NowWorld == 2)
	{
		tex_NowWorld_background = 16;
		tex_NowWorld_stagechoice = 21;
		tex_NowWorld_mission = 26;
	}

	if (NowWorld == 3)
	{
		tex_NowWorld_background = 17;
		tex_NowWorld_stagechoice = 22;
		tex_NowWorld_mission = 27;
	}

	if (NowWorld == 4)
	{
		tex_NowWorld_background = 18;
		tex_NowWorld_stagechoice = 23;
		tex_NowWorld_mission = 28;
	}

	if (NowWorld == 5)
	{
		tex_NowWorld_background = 19;
		tex_NowWorld_stagechoice = 24;
		tex_NowWorld_mission = 29;
	}

	// �Z�[�u�f�[�^����Q�b�g���Ă鐯�̐���ǂݍ���
	int StageStar = GetStar(NowWorld);

	int Number_EffectArray[2] = { 0,0 };
	int* p_Number_EffectArray = Number_EffectArray;
	// �Z�[�u�f�[�^����ǂݍ��񂾑S�Ă̐��̐��̕\��
	SetEffectNumber(StageStar, p_Number_EffectArray, D3DXVECTOR2(250.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// �S�Ă̐��̐�(30)�̕\��
	SetEffectNumber(30, p_Number_EffectArray, D3DXVECTOR2(400.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	stage_select_once = false;
	now_stage_select_EffectArray = -1;
	now_stage_selectWaku_EffectArray = -1;
	stage_select_once_time = 0;

	Arrow_EffectArray[0] = -1;
	Arrow_EffectArray[1] = -1;

	change_cool = 30;

	StartStageSelectScreen();

	return;
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitStageSelect()
{
	UnloadTexture("data/TEXTURE/select/stage_select.png");
	StopSoundAll();
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateStageSelect(void)
{
	if (change_cool <= 0)
		changing = false;
	else
		changing = true;

	if (change_cool > 0)
		change_cool--;


	// �y�[�W�`�F���W���ł͂Ȃ��Ƃ��ɕ��ʂɓ���
	if (changing == false)
	{
		change_count = 0;		// �`�F���W���̎��̂ݑ�����B�����Ń��Z�b�g���Ă���

		if (Keyboard_IsKeyDown(KK_E))
		{
			if (change_cool <= 0)
			{
				change_cool = 60;
				ChangePage(1);
				return;
			}
		}
		if (Keyboard_IsKeyDown(KK_Q))
		{
			if (change_cool <= 0)
			{
				change_cool = 60;
				ChangePage(-1);
				return;
			}
		}

		//�}�E�X�̍��W���擾
		float mouse_pos_X = GetMousePosX();
		float mouse_pos_Y = GetMousePosY();
		bool mouse_Lclick = GetMouseLClick();
		bool mouseuse = false;

		// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
		int OldStageSelectX = g_StageSelect.select_x;
		int OldStageSelectY = g_StageSelect.select_y;


		// �ړ��L�[�������ꂽ���̏���
		if (g_StageSelect.selectcooltime <= 0)
		{
			if (Keyboard_IsKeyDown(KK_UP) && g_StageSelect.select_x != 5 && g_StageSelect.select_x != 6)
			{
				if (g_StageSelect.select_y == 0 && g_StageSelect.select_x == 0)		// 0,0�̎���������ƃ^�C�g���֍s���ɂȂ�
					g_StageSelect.select_y = 2;
				else if (g_StageSelect.select_y == 0)								// �ŏ�i�̎���������ƍŉ��w�ɍs��
					g_StageSelect.select_y = 1;
				else
					g_StageSelect.select_y--;										// �ʏ�
				g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			}
			if (Keyboard_IsKeyDown(KK_DOWN) && g_StageSelect.select_x != 5 && g_StageSelect.select_x != 6)
			{
				if (g_StageSelect.select_y == 2 && g_StageSelect.select_x == 0)		// �^�C�g���̎�������0,0�ɂȂ�
					g_StageSelect.select_y = 0;
				else if (g_StageSelect.select_y == 1 && g_StageSelect.select_x == 0)								// 0,1�̎��^�C�g���ɍs��
					g_StageSelect.select_y = 2;
				else if (g_StageSelect.select_y == 1)								// �ŉ��w����������ƍŏ�i�s��
					g_StageSelect.select_y = 1;
				else
					g_StageSelect.select_y++;										// �ʏ�
				g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			}
			if (Keyboard_IsKeyDown(KK_RIGHT) && g_StageSelect.select_y != 2)
			{
				if (g_StageSelect.select_x == 4)				// �[�̎������Ɩ��ɍs��
				{
					if (now_page == 0)
					{
						g_StageSelect.select_x = 6;
						g_StageSelect.select_y = 0;
					}
				}
				else if (g_StageSelect.select_x == 6)			// ���̎������ƃy�[�W�`�F���W����
				{
					change_cool = 60;
					g_StageSelect.select_x = 0;
					g_StageSelect.select_y = 0;
					ChangePage(1);
					return;
				}
				else if (g_StageSelect.select_x == 5)				// �����̎�������0�ɂ���
					g_StageSelect.select_x = 0;
				else
					g_StageSelect.select_x++;					// �ʏ�
				g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			}
			if (Keyboard_IsKeyDown(KK_LEFT) && g_StageSelect.select_y != 2)
			{
				if (g_StageSelect.select_x == 0)				// �[�̎������Ɩ��ɍs��
				{
					if (now_page == 1)
					{
						g_StageSelect.select_x = 5;
						g_StageSelect.select_y = 0;
					}
				}
				else if (g_StageSelect.select_x == 5)			// ���̎������ƃy�[�W�`�F���W����
				{
					change_cool = 60;
					g_StageSelect.select_x = 4;
					g_StageSelect.select_y = 0;
					ChangePage(-1);
					return;
				}
				else if (g_StageSelect.select_x == 6)				// �E���̎�������4�ɂ���
					g_StageSelect.select_x = 4;
				else
					g_StageSelect.select_x--;					// �ʏ�
				g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			}







			// �}�E�X�ł̑���
			// �X�e�[�W�I���̎��̌��_�ƂȂ�ꏊ
			float	effectpos_x = 240.0f;			    // x�̌��_(0,0��I�����Ă���Ƃ�)
			float	effectpos_y = 200.0f;			    // y�̌��_(0,0��I�����Ă���Ƃ�)

			// �X�e�[�W�I���̎�1���ꂽ�炱�ꂾ����������Ă��
			float while_x = 240.0f;
			float while_y = 240.0f;

			//�X�e�[�W�I��
			for (int x = 0; x < SELECT_MAX_X; x++)
			{
				for (int y = 0; y < SELECT_MAX_Y; y++)
				{
					// �X�e�[�W�̍��W�����߂�
					int now_stage = x + y * SELECT_MAX_X + (now_page * 10);	// 0~19
					D3DXVECTOR2 Stage_Pos = GetStagePos(now_stage + 1);
					// ���݂̍��W�����߂�
					/*float effectnow_x = effectpos_x + while_x * x;
					float effectnow_y = effectpos_y + while_y * y;*/
					float effectnow_x = Stage_Pos.x;
					float effectnow_y = Stage_Pos.y;

					if (mouse_pos_X > effectnow_x - 50.0f && mouse_pos_X < effectnow_x + 50.0f && mouse_pos_Y > effectnow_y - 50.0f && mouse_pos_Y < effectnow_y + 50.0f)
					{
						g_StageSelect.select_x = x;
						g_StageSelect.select_y = y;
						mouseuse = true;
					}

				}
			}
			//���[���h�I���֖߂� 240 700
			if (mouse_pos_X > 180.0f && mouse_pos_X < 280.0f && mouse_pos_Y > 650.0f && mouse_pos_Y < 750.0f)
			{
				g_StageSelect.select_x = 0;
				g_StageSelect.select_y = 2;
				mouseuse = true;
			}
			//�����
			D3DXVECTOR2 yazipos = D3DXVECTOR2(120.0f, 320.0f);
			D3DXVECTOR2 yazisize = D3DXVECTOR2(50.0f, 50.0f);
			if (now_page == 1)
			{
				if (mouse_pos_X > yazipos.x - yazisize.x && mouse_pos_X < yazipos.x + yazisize.x && mouse_pos_Y > yazipos.y - yazisize.y && mouse_pos_Y < yazipos.y + yazisize.y)
				{
					g_StageSelect.select_x = 5;
					if (g_StageSelect.select_y == 2)
						g_StageSelect.select_y = 0;
					mouseuse = true;
				}
			}
			//�E���
			yazipos = D3DXVECTOR2(1320.0f, 320.0f);
			if (now_page == 0)
			{
				if (mouse_pos_X > yazipos.x - yazisize.x && mouse_pos_X < yazipos.x + yazisize.x && mouse_pos_Y > yazipos.y - yazisize.y && mouse_pos_Y < yazipos.y + yazisize.y)
				{
					g_StageSelect.select_x = 6;
					if (g_StageSelect.select_y == 2)
						g_StageSelect.select_y = 0;
					mouseuse = true;
				}
			}
		}

		// �ύX���m�F���鏈��

			// �����O�̃t���[������ω����������ꍇ�̂݃G�t�F�N�g�Ȃǂ�ω�������
		bool Change = false;
		if (OldStageSelectX != g_StageSelect.select_x ||
			OldStageSelectY != g_StageSelect.select_y)
			Change = true;

		// �ύX���������ꍇ�A�������ƐV�������̂̃Z�b�g
		if (Change == true)
		{
			g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			EffectBreak(now_stage_select_EffectArray);
			EffectBreak(now_stage_selectWaku_EffectArray);
			EffectBreak(now_stagenum_select_EffectArray[0], now_stagenum_select_EffectArray[1]);
			DeleteMissionStageSelect();
			stage_select_once = false;
			stage_select_once_time = 0;
		}

		bool mouseclick = false;
		if (mouseuse && mouse_Lclick)
			mouseclick = true;

		// �}�E�X���\���ɂ����Ă����Ԃō��N���b�N�������̓G���^�[�L�[��������
		if (GetFadeState() == FADE_NONE)
		{
			if (Keyboard_IsKeyDown(KK_ENTER) || mouseclick)
			{
				g_SENo = LoadSound("data/SE/�u�s�����v����̃{�^�����E�A�N�Z���g��.wav");
				PlaySound(g_SENo, 0);

				StageDecision = true;
				// �ړ����͂̂Ƃ��ł��łɃX�e�[�W�f�[�^�͂�����Ă���̂ł��̂܂܂�����OK
				g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
				// �v���C���[�z�u�t�F�[�Y�ɍs���O�ɑO��̔z�u�������Z�b�g����
				ResetPlacementArray();
				if (g_StageSelect.select_y == 2)
				{
					change_cool = 999;				// ���肵���̂ŐG��Ȃ�����
					SceneTransition(SCENE_TITLE);
				}
				else if (g_StageSelect.select_x == 5)
				{
					g_StageSelect.select_x = 4;
					ChangePage(-1);
					return;
				}
				else if (g_StageSelect.select_x == 6)
				{
					g_StageSelect.select_x = 0;
					ChangePage(1);
					return;
				}
				else
				{
					change_cool = 999;				// ���肵���̂ŐG��Ȃ�����
					SceneTransition(SCENE_PLACEMENT);
				}
			}
		}






		// �X�e�[�W�I���̎��̌��_�ƂȂ�ꏊ
		float	stage_origin_x = 240.0f;			    // x�̌��_(0,0��I�����Ă���Ƃ�)
		float	stage_origin_y = 200.0f;			    // y�̌��_(0,0��I�����Ă���Ƃ�)

		// �X�e�[�W�I���̎�1���ꂽ�炱�ꂾ����������Ă��
		float interval_x = 240.0f;
		float interval_y = 240.0f;

		if (stage_select_once == false)
		{
			stage_select_once = true;

			// �X�e�[�W�̂Ƃ������X�e�[�W�f�[�^���󂯎��B
			if (g_StageSelect.select_x < SELECT_MAX_X && g_StageSelect.select_y < SELECT_MAX_Y)
			{
				// �X�e�[�W�f�[�^���󂯎��,�~�b�V������}�b�v�̕\���Ŏg�����߁B
				// x��y����}�b�v�̔ԍ����v�Z����
				int stagenum = (now_page * 10) + (SELECT_MAX_X * g_StageSelect.select_y) + (g_StageSelect.select_x + 1);
				now_stagenum = stagenum;
				SetStageData(stagenum);		// 1~20�̒l������

				// �X�e�[�W�f�[�^���󂯎����(�X�V���ꂽ)�̂Ń~�b�V������\��������
				DrawMissionStageSelect();
			}



			//�X�e�[�W�I��
			for (int x = 0; x < SELECT_MAX_X + 2; x++)
			{
				for (int y = 0; y < SELECT_MAX_Y + 1; y++)
				{
					// �X�e�[�W�̍��W�����߂�
					int now_stage = x + y * SELECT_MAX_X + (now_page * 10);	// 0~19
					D3DXVECTOR2 Stage_Pos = GetStagePos(now_stage + 1);

					// ���݂̍��W�����߂�
					/*float now_x = stage_origin_x + interval_x * x;
					float now_y = stage_origin_y + interval_y * y;*/
					float now_x = Stage_Pos.x;
					float now_y = Stage_Pos.y;

					// �����B�I�����Ă���Ƃ��������đ傫���T�C�Y�ŕ\���B
					if (g_StageSelect.select_x == x)
					{
						if (g_StageSelect.select_y == y)
						{
							if (x < SELECT_MAX_X && y < SELECT_MAX_Y)
							{
								int now_select_stage = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (now_page * 10);	// 0~19

								// �s��
								now_stage_select_EffectArray =
									SetEffect(87, D3DXVECTOR2(now_x, now_y - 120), D3DXVECTOR2(now_x, now_y - 40), 1,
										D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
										0.0f, 1.0f, 30, 999, 0, 30,
										0.0f, 0.0f, 0);
								// ���g
								now_stage_selectWaku_EffectArray =
									SetEffect(88, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
										D3DXVECTOR2(220.0f, 220.0f), D3DXVECTOR2(220.0f, 220.0f), 0,
										0.0f, 1.0f, 30, 999, 0, 30,
										0.0f, 0.0f, 0);

								// �X�e�[�W�̐���
								SetEffectNumber(now_select_stage + 1, p_now_stagenum_select_EffectArray, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
									D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
									1.0f, 1.0f, 0, 999, 0, 60,
									0.0f, 0.0f, 0);

							}
							else if (y == 2)		// �^�C�g���ɖ߂鏈�� (���[���h�I���ɖ߂�{�^���̕\��)
							{
								now_stage_select_EffectArray = 
								SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
									D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
									0.0f, 1.0f, 0, 999, 0, 60,
									0.0f, 0.0f, 0);
								now_stage_selectWaku_EffectArray =
									SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
										D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
										0.0f, 0.0f, 0, 999, 0, 60,
										0.0f, 0.0f, 0);			// ���������Ǐo���Ă���
							}
							else if (x == 5)		// �y�[�W�ύX�̖��̍�
							{
								now_stage_select_EffectArray = 
								SetEffect(61, D3DXVECTOR2(120.0f, 320.0f), D3DXVECTOR2(120.0f, 320.0f), 0,
									D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
									0.0f, 1.0f, 0, 999, 0, 60,
									0.0f, 0.0f, 0);
								now_stage_selectWaku_EffectArray =
									SetEffect(61, D3DXVECTOR2(120.0f, 320.0f), D3DXVECTOR2(120.0f, 320.0f), 0,
										D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
										0.0f, 0.0f, 0, 999, 0, 60,
										0.0f, 0.0f, 0);
							}
							else if (x == 6)		// �y�[�W�ύX�̖��̉E
							{
								now_stage_select_EffectArray = 
								SetEffect(61, D3DXVECTOR2(1320.0f, 320.0f), D3DXVECTOR2(1320.0f, 320.0f), 0,
									D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
									0.0f, 1.0f, 0, 999, 0, 60,
									0.0f, 0.0f, 0);
								now_stage_selectWaku_EffectArray =
									SetEffect(61, D3DXVECTOR2(1320.0f, 320.0f), D3DXVECTOR2(1320.0f, 320.0f), 0,
										D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
										0.0f, 0.0f, 0, 999, 0, 60,
										0.0f, 0.0f, 0);
							}

							g_SENo = LoadSound("data/SE/Accent03-1.wav");
							PlaySound(g_SENo, 0);
						}
					}
				}
			}
		}


		// �I��������Ԃ������Ă�ꍇtrue�Ȃ̂ł������Ƃ���
		if (stage_select_once == true)
		{
			if (stage_select_once_time % 60 == 0)
			{
				ChangeEffectCount(now_stage_select_EffectArray, 0);
			}


			// �I������Ă���̎��Ԃ������Ă���
			stage_select_once_time++;
		}





		if (g_StageSelect.selectcooltime > 0)
			g_StageSelect.selectcooltime--;


		g_StageSelect.selecttime++;


	}
	else
	{
		// �`�F���W���̏ꍇ

		SAVEDATA* p_Savedata = GetSavedata();
		STAGEDATA* p_Stagedata = GetStagedata();

		// �^���Â̎��ɉ摜��ς���
		if (change_count == 24)
		{
			//�X�e�[�W�I��
			for (int page = 0; page < PAGE_MAX; page++)
			{

				// �y�[�W�̔w�i
				ChangeEffect(tex_Page_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
					D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
					0.0f, 1.0f, 0, 999, 0, cahngetime,
					0.0f, 0.0f, 0);

				// �X�e�[�W�ԍ�
				ChangeEffect(tex_StageNum_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
					D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
					0.0f, 1.0f, 0, 999, 0, cahngetime,
					0.0f, 0.0f, 0);

				// tex_Page_background_EffectArray[page]
				// tex_StageNum_background_EffectArray


				for (int x = 0; x < SELECT_MAX_X; x++)
				{
					for (int y = 0; y < SELECT_MAX_Y; y++)
					{
						//int now_num = x + y * SELECT_MAX_X + (page * 10);
						int NowWorld_stagenum = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (page * 10);	// 0~19

						D3DXVECTOR2 now_stagePos = GetEffectPos(stage_EffectArray[NowWorld_stagenum]);
						D3DXVECTOR2 now_stage_starPos[3];
						now_stage_starPos[0] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][0]);
						now_stage_starPos[1] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][1]);
						now_stage_starPos[2] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][2]);

						// �I������ĂȂ��Ƃ��̕\�����o��(�X�e�[�W���ׂ�)
						//////////ChangeEffect(stage_EffectArray[NowWorld_stagenum], tex_NowWorld_stagechoice, now_stagePos, D3DXVECTOR2(now_stagePos.x + change_page_interval, now_stagePos.y), 1,
						//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
						//////////	0.0f, 0.0f, 0);

						//////////// ����
						//////////// ���݂̍��W�����߂�
						//////////
						//////////ChangeEffect(stageNumber_EffectArray[NowWorld_stagenum][0], -1, D3DXVECTOR2(99999,99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
						//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
						//////////	0.0f, 0.0f, 0, stageNumber_EffectArray[NowWorld_stagenum][1]);

						// �~�b�V�������N���A���Ă���Ȃ�\������ p_stageNumber_EffectArray[NowWorld_stagenum]
						if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
						{
							//��
							ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][0], 83, now_stage_starPos[0], D3DXVECTOR2(now_stage_starPos[0].x + change_page_interval, now_stage_starPos[0].y), 1,
								D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
								0.0f, 1.0f, 120, 999, 0, cahngetime,
								0.0f, 0.0f, 0);
						}

						// �~�b�V�������N���A���Ă���Ȃ�\������
						if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
						{
							//��
							ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][1], 84, now_stage_starPos[1], D3DXVECTOR2(now_stage_starPos[1].x + change_page_interval, now_stage_starPos[1].y), 1,
								D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
								0.0f, 1.0f, 120, 999, 0, cahngetime,
								0.0f, 0.0f, 0);
						}

						// �~�b�V�������N���A���Ă���Ȃ�\������
						if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
						{
							//��
							ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][2], 85, now_stage_starPos[2], D3DXVECTOR2(now_stage_starPos[2].x + change_page_interval, now_stage_starPos[2].y), 1,
								D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
								0.0f, 1.0f, 120, 999, 0, cahngetime,
								0.0f, 0.0f, 0);
						}
					}
				}
			}
			// ���̏���
			ChangeEffectClarity(Arrow_EffectArray[0], 1.0f);
			ChangeEffectClarity(Arrow_EffectArray[1], 1.0f);

			if (now_page == 0)
				ChangeEffectClarity(Arrow_EffectArray[0], 0.3f);

			if (now_page == 1)
				ChangeEffectClarity(Arrow_EffectArray[1], 0.3f);

		}

		change_count++;
	}

	SetScore2(now_page);
}

STAGESELECT* GetStageSelect()
{
	return &g_StageSelect;
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawStageSelect(void)
{



	//// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	//DrawSpriteColorRotate(tex_NowWorld_background, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR (1.0f, 1.0f, 1.0f, 1.0f), 1.0f);

	/*static int world_1_background;
	static int world_2_stagechoice;
	static int world_3_mission;
	static int world_4_selectstar;*/

}

void StartStageSelectScreen()
{
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	//�w�i�\��
	// 1�y�[�W��
	tex_Page_background_EffectArray[0] =
	SetEffect(89, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, 1.0f, 100, 999, 0, 60,
		0.0f, 0.0f, 0);
	// 2�y�[�W��
	tex_Page_background_EffectArray[1] =
		SetEffect(90, D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
			0.0f, 1.0f, 100, 999, 0, 60,
			0.0f, 0.0f, 0);

	// 1�y�[�W��
	tex_StageNum_background_EffectArray[0] = 
		SetEffect(91, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
			0.0f, 1.0f, 100, 999, 0, 60,
			0.0f, 0.0f, 0);

	// 2�y�[�W��
	tex_StageNum_background_EffectArray[1] =
		SetEffect(92, D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
			0.0f, 1.0f, 100, 999, 0, 60,
			0.0f, 0.0f, 0);

	// �X�e�[�W�I���̎��̌��_�ƂȂ�ꏊ
	float	stage_origin_x = 240.0f;			    // x�̌��_(0,0��I�����Ă���Ƃ�)
	float	stage_origin_y = 200.0f;			    // y�̌��_(0,0��I�����Ă���Ƃ�)

	// �X�e�[�W�I���̎�1���ꂽ�炱�ꂾ����������Ă��
	float interval_x = 240.0f;
	float interval_y = 240.0f;


	float page_interval_x = SCREEN_WIDTH;



	//�X�e�[�W�I��
	for (int page = 0; page < PAGE_MAX; page++)
	{
		for (int x = 0; x < SELECT_MAX_X; x++)
		{
			for (int y = 0; y < SELECT_MAX_Y; y++)
			{
				//int now_num = x + y * SELECT_MAX_X + (page * 10);
				int NowWorld_stagenum = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (page * 10);	// 0~19

				// ���݂̍��W�����߂�
				float now_x = stage_origin_x + interval_x * x + page * page_interval_x;
				float now_y = stage_origin_y + interval_y * y;

				// �I������ĂȂ��Ƃ��̕\�����o��(�X�e�[�W���ׂ�)
				//////////stage_EffectArray[NowWorld_stagenum] =
				//////////	SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
				//////////		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				//////////		0.0f, 1.0f, 0, 999, 0, 0,
				//////////		0.0f, 0.0f, 0); 

				//////////int* p_stageNumber_EffectArray;				// 20�X�e�[�W���̔z����|�C���^�[�ŗp�ӂ���
				//////////p_stageNumber_EffectArray = &stageNumber_EffectArray[NowWorld_stagenum][0];


				//////////SetEffectNumber(NowWorld_stagenum + 1, p_stageNumber_EffectArray, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
				//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				//////////	0.0f, 1.0f, 0, 999, 0, 0,
				//////////	0.0f, 0.0f, 0);

				/*stageNumber_EffectArray[NowWorld_stagenum][0] = 1;
				stageNumber_EffectArray[NowWorld_stagenum][1] = 1;*/

				// �~�b�V�������N���A���Ă���Ȃ�\������
				if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
				{
					//��
					stage_star_EffectArray[NowWorld_stagenum][0] =
					SetEffect(83, D3DXVECTOR2(now_x - 40, now_y), D3DXVECTOR2(now_x - 40, now_y), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}

				// �~�b�V�������N���A���Ă���Ȃ�\������
				if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
				{
					//��
					stage_star_EffectArray[NowWorld_stagenum][1] =
					SetEffect(84, D3DXVECTOR2(now_x - 0, now_y), D3DXVECTOR2(now_x - 0, now_y), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}

				// �~�b�V�������N���A���Ă���Ȃ�\������
				if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
				{
					//��
					stage_star_EffectArray[NowWorld_stagenum][2] =
					SetEffect(85, D3DXVECTOR2(now_x + 50, now_y), D3DXVECTOR2(now_x + 50, now_y), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}
			}
		}
	}

	// �^�C�g���ɖ߂鏈��
	SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// �y�[�W�ύX�̖��̍�
	Arrow_EffectArray[0] = 
	SetEffect(61, D3DXVECTOR2(120.0f, 320.0f), D3DXVECTOR2(120.0f, 320.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 60,
		0.0f, 0.0f, 0);

	// �y�[�W�ύX�̖��̉E
	Arrow_EffectArray[1] = 
	SetEffect(61, D3DXVECTOR2(1320.0f, 320.0f), D3DXVECTOR2(1320.0f, 320.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 60,
		0.0f, 0.0f, 0);

	//�ǂ̂��̐��H
	SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	// �Z�[�u�f�[�^����Q�b�g���Ă鐯�̐���ǂݍ���
	// ��������̂��H
	int StageStar = GetStar(NowWorld);

	int Number_EffectArray[2] = { 0,0 };
	int* p_Number_EffectArray = Number_EffectArray;
	// �Z�[�u�f�[�^����ǂݍ��񂾑S�Ă̐��̐��̕\��
	SetEffectNumber(StageStar, p_Number_EffectArray, D3DXVECTOR2(250.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// �S�Ă̐��̐�(30)�̕\��
	SetEffectNumber(30, p_Number_EffectArray, D3DXVECTOR2(400.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// ���̓����x�������鏈��
	if (now_page == 0)
		ChangeEffectClarity(Arrow_EffectArray[0], 0.3f);

	if (now_page == 1)
		ChangeEffectClarity(Arrow_EffectArray[1], 0.3f);

	// �s���̃G�t�F�N�g������Ă���
	tex_Pin_EffectArray = 
	SetEffect(87, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	// ���g�̃G�t�F�N�g������Ă���
	tex_Waku_EffectArray = 
	SetEffect(88, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	return;
}

void ChangePage(int ToGoPage)
{
	// �y�[�W�`�F���W���ɂ���
	changing = true;

	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	// �t�F�[�h������(�����w�i���o��)SetEffectInReverse
	SetEffectInReverse(4, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, 1.0f, 22, 4, 22, 48,
		0.0f, 0.0f, 0);


	////�w�i�\��
	//SetEffect(tex_NowWorld_background, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
	//	D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
	//	0.0f, 1.0f, 100, 999, 0, 180,
	//	0.0f, 0.0f, 0);

	// �X�e�[�W�I���̎��̌��_�ƂȂ�ꏊ
	float	stage_origin_x = 240.0f;			    // x�̌��_(0,0��I�����Ă���Ƃ�)
	float	stage_origin_y = 200.0f;			    // y�̌��_(0,0��I�����Ă���Ƃ�)

	// �X�e�[�W�I���̎�1���ꂽ�炱�ꂾ����������Ă��
	float interval_x = 240.0f;
	float interval_y = 240.0f;

	float page_interval = SCREEN_WIDTH;
	change_page_interval = -ToGoPage * SCREEN_WIDTH;		// �ړ�����

	////�X�e�[�W�I��
	//for (int page = 0; page < PAGE_MAX; page++)
	//{
	//	// �y�[�W�̔w�i
	//	ChangeEffect(tex_Page_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
	//		D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
	//		0.0f, 1.0f, 0, 999, 0, cahngetime,
	//		0.0f, 0.0f, 0);

	//	// �X�e�[�W�ԍ�
	//	ChangeEffect(tex_StageNum_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
	//		D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
	//		0.0f, 1.0f, 0, 999, 0, cahngetime,
	//		0.0f, 0.0f, 0);

	//	// tex_Page_background_EffectArray[page]
	//	// tex_StageNum_background_EffectArray


	//	for (int x = 0; x < SELECT_MAX_X; x++)
	//	{
	//		for (int y = 0; y < SELECT_MAX_Y; y++)
	//		{
	//			//int now_num = x + y * SELECT_MAX_X + (page * 10);
	//			int NowWorld_stagenum = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (page * 10);	// 0~19

	//			// ���݂̍��W�����߂�
	//			float now_x = stage_origin_x + interval_x * x + page * page_interval;
	//			float now_y = stage_origin_y + interval_y * y;

	//			D3DXVECTOR2 now_stagePos = GetEffectPos(stage_EffectArray[NowWorld_stagenum]);
	//			D3DXVECTOR2 now_stage_starPos[3];
	//			now_stage_starPos[0] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][0]);
	//			now_stage_starPos[1] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][1]);
	//			now_stage_starPos[2] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][2]);

	//			// �I������ĂȂ��Ƃ��̕\�����o��(�X�e�[�W���ׂ�)
	//			//////////ChangeEffect(stage_EffectArray[NowWorld_stagenum], tex_NowWorld_stagechoice, now_stagePos, D3DXVECTOR2(now_stagePos.x + change_page_interval, now_stagePos.y), 1,
	//			//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
	//			//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
	//			//////////	0.0f, 0.0f, 0);

	//			//////////// ����
	//			//////////// ���݂̍��W�����߂�
	//			//////////
	//			//////////ChangeEffect(stageNumber_EffectArray[NowWorld_stagenum][0], -1, D3DXVECTOR2(99999,99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
	//			//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
	//			//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
	//			//////////	0.0f, 0.0f, 0, stageNumber_EffectArray[NowWorld_stagenum][1]);

	//			// �~�b�V�������N���A���Ă���Ȃ�\������ p_stageNumber_EffectArray[NowWorld_stagenum]
	//			if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
	//			{
	//				//��
	//				ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][0], 83, now_stage_starPos[0], D3DXVECTOR2(now_stage_starPos[0].x + change_page_interval, now_stage_starPos[0].y), 1,
	//					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
	//					0.0f, 1.0f, 120, 999, 0, cahngetime,
	//					0.0f, 0.0f, 0);
	//			}

	//			// �~�b�V�������N���A���Ă���Ȃ�\������
	//			if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
	//			{
	//				//��
	//				ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][1], 84, now_stage_starPos[1], D3DXVECTOR2(now_stage_starPos[1].x + change_page_interval, now_stage_starPos[1].y), 1,
	//					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
	//					0.0f, 1.0f, 120, 999, 0, cahngetime,
	//					0.0f, 0.0f, 0);
	//			}

	//			// �~�b�V�������N���A���Ă���Ȃ�\������
	//			if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
	//			{
	//				//��
	//				ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][2], 85, now_stage_starPos[2], D3DXVECTOR2(now_stage_starPos[2].x + change_page_interval, now_stage_starPos[2].y), 1,
	//					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
	//					0.0f, 1.0f, 120, 999, 0, cahngetime,
	//					0.0f, 0.0f, 0);
	//			}
	//		}
	//	}
	//}

	//// �^�C�g���ɖ߂鏈��
	//SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
	//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
	//	0.0f, 1.0f, 0, 999, 0, 0,
	//	0.0f, 0.0f, 0);

	////�ǂ̂��̐��H
	//SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
	//	D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
	//	0.0f, 1.0f, 0, 1, 0, 0,
	//	0.0f, 0.0f, 0);

	//// �Z�[�u�f�[�^����Q�b�g���Ă鐯�̐���ǂݍ���
	//// ��������̂��H
	//int StageStar = GetStar(NowWorld);

	//int Number_EffectArray[2] = { 0,0 };
	//int* p_Number_EffectArray = Number_EffectArray;
	//// �Z�[�u�f�[�^����ǂݍ��񂾑S�Ă̐��̐��̕\��
	//SetEffectNumber(StageStar, p_Number_EffectArray, D3DXVECTOR2(250.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
	//	D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
	//	0.0f, 1.0f, 0, 999, 0, 0,
	//	0.0f, 0.0f, 0);

	//// �S�Ă̐��̐�(30)�̕\��
	//SetEffectNumber(30, p_Number_EffectArray, D3DXVECTOR2(400.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
	//	D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
	//	0.0f, 1.0f, 0, 999, 0, 0,
	//	0.0f, 0.0f, 0);

	// �ύX���������ꍇ�̂ŁA�������ƐV�������̂̃Z�b�g
	g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
	EffectBreak(now_stage_select_EffectArray);
	EffectBreak(now_stage_selectWaku_EffectArray);
	EffectBreak(now_stagenum_select_EffectArray[0], now_stagenum_select_EffectArray[1]);
	DeleteMissionStageSelect();
	stage_select_once = false;
	stage_select_once_time = 0;

	change_cool = 48;
	now_page += ToGoPage;

	/*ChangeEffectClarity(Arrow_EffectArray[0], 1.0f);
	ChangeEffectClarity(Arrow_EffectArray[1], 1.0f);

	if(now_page == 0)
		ChangeEffectClarity(Arrow_EffectArray[0], 0.3f);

	if (now_page == 1)
		ChangeEffectClarity(Arrow_EffectArray[1], 0.3f);*/

	return;

}

int GetNowChoiceStageNum()
{
	return now_stagenum;
}


D3DXVECTOR2 GetStagePos(int num)
{
	switch (num)
	{
	case 1:
		return D3DXVECTOR2(200.0f, 180.0f);
		break;
	case 2:
		return D3DXVECTOR2(475.0f, 310.0f);
		break;
	case 3:
		return D3DXVECTOR2(680.0f, 210.0f);
		break;
	case 4:
		return D3DXVECTOR2(980.0f, 120.0f);
		break;
	case 5:
		return D3DXVECTOR2(1230.0f, 300.0f);
		break;
	case 6:
		return D3DXVECTOR2(140.0f, 550.0f);
		break;
	case 7:
		return D3DXVECTOR2(550.0f, 660.0f);
		break;
	case 8:
		return D3DXVECTOR2(850.0f, 490.0f);
		break;
	case 9:
		return D3DXVECTOR2(1030.0f, 530.0f);
		break;
	case 10:
		return D3DXVECTOR2(1300.0f, 620.0f);
		break;

	case 11:
		return D3DXVECTOR2(150.0f, 450.0f);
		break;
	case 12:
		return D3DXVECTOR2(240.0f, 210.0f);
		break;
	case 13:
		return D3DXVECTOR2(590.0f, 180.0f);
		break;
	case 14:
		return D3DXVECTOR2(970.0f, 90.0f);
		break;
	case 15:
		return D3DXVECTOR2(1240.0f, 120.0f);
		break;
	case 16:
		return D3DXVECTOR2(1300.0f, 300.0f);
		break;
	case 17:
		return D3DXVECTOR2(1230.0f, 510.0f);
		break;
	case 18:
		return D3DXVECTOR2(900.0f, 380.0f);
		break;
	case 19:
		return D3DXVECTOR2(780.0f, 610.0f);
		break;
	case 20:
		return D3DXVECTOR2(480.0f, 640.0f);
		break;
	}
}