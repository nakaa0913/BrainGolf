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
int tex_NowWorld_stagechoice = -1; //�X�e�[�W�I���̎l�p�����
int tex_NowWorld_mission = -1;     //�~�b�V����

// �I�������Ƃ��̏����Ŏg��
int now_stage_select_EffectArray = -1;
int stage_EffectArray[USE_STAGE_MAX];
int stage_star_EffectArray[USE_STAGE_MAX][MAX_MISSION];
bool stage_select_once = false;
int stage_select_once_time = 0;

bool StageDecision = false;				// �G���^�[�����N���b�N�ŃX�e�[�W���m�肳�����瑼�̂Ƃ��Ɉړ��ł��Ȃ�����

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitStageSelect(void)
{

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



	g_BGMNo = LoadSound("data/BGM/sample000.wav");

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


	StartStageSelectScreen();

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
	stage_select_once_time = 0;

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
	if (Keyboard_IsKeyDown(KK_Q))
		ChangePage();
	
	if (StageDecision == false)
	{
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

			if (g_StageSelect.select_x == 0) {
				
				if (g_StageSelect.select_y == 0)
				{
					//(0,0)�̏���
					if (Keyboard_IsKeyDown(KK_UP))
					{
						g_StageSelect.select_y = 3;
					}

					if (Keyboard_IsKeyDown(KK_DOWN))
					{
						g_StageSelect.select_y = 1;
					}
				}
				//(0,1)�̏���
				else if (g_StageSelect.select_y == 1)
				{
					if (Keyboard_IsKeyDown(KK_UP))
					{
						g_StageSelect.select_y = 0;
					}
					//����������u���[���h�I���ɖ߂�{�^���v�ɂ���
					if (Keyboard_IsKeyDown(KK_DOWN))
					{
						g_StageSelect.select_y = 3;
					}
				}

				//(0,3)�̏���
				else if (g_StageSelect.select_y == 3)
				{
					if (Keyboard_IsKeyDown(KK_UP))
					{
						g_StageSelect.select_y = 1;
					}

					if (Keyboard_IsKeyDown(KK_DOWN))
					{
						g_StageSelect.select_y = 0;
					}
					//ENTER�Ń^�C�g���֖߂�
					if (Keyboard_IsKeyDown(KK_ENTER))
					{
						SceneTransition(SCENE_TITLE);

						if (UseEnter == 0)
						{
							g_SENo = LoadSound("data/SE/Accent03-1.wav");
							PlaySound(g_SENo, 0);
							UseEnter = 1;
						}
					}
					////ENTER�ŃV�[�����[���h�I���ɂ���
					//if (Keyboard_IsKeyDown(KK_ENTER))
					//{
					//	SceneTransition(SCENE_WORLD_SELECT);
					//}
				}
				//y = 3�ȊO�̎��ɍ��E�ړ����ł���i3�́u���[���h�I���ɖ߂�{�^���v�j
				if (g_StageSelect.select_y != 3)
				{
					// �E
					if (Keyboard_IsKeyDown(KK_RIGHT))
					{
						g_StageSelect.select_x++;
					}
					// ��
					if (Keyboard_IsKeyDown(KK_LEFT))
					{
						g_StageSelect.select_x--;
					}
				}
			}
			//x = 0����Ȃ��Ƃ��̏���
			else {
				// ��
				if (Keyboard_IsKeyDown(KK_UP))
				{
					g_StageSelect.select_y--;
				}
				// ��
				if (Keyboard_IsKeyDown(KK_DOWN))
				{
					g_StageSelect.select_y++;
				}
				// �E
				if (Keyboard_IsKeyDown(KK_RIGHT))
				{
					g_StageSelect.select_x++;
				}
				// ��
				if (Keyboard_IsKeyDown(KK_LEFT))
				{
					g_StageSelect.select_x--;
				}
			}

			if (g_StageSelect.selecttime >= 1)
			{
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
						// ���݂̍��W�����߂�
						float effectnow_x = effectpos_x + while_x * x;
						float effectnow_y = effectpos_y + while_y * y;

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
					g_StageSelect.select_y = 3;
					mouseuse = true;
				}
			}


			// ���E�l�ɂ��C���̏���

			//x��5�ȏ�Ȃ�0�ɂ���i�E���獶�j
			if (g_StageSelect.select_x >= SELECT_MAX_X)
				g_StageSelect.select_x = 0;

			//x��-1�Ȃ�4�ɂ���i������E�j
			if (g_StageSelect.select_x < 0 && g_StageSelect.select_x >= -1)
				g_StageSelect.select_x = SELECT_MAX_X - 1;

			//y��2�Ȃ�0�ɂ���i�������j
			if (g_StageSelect.select_y > 1 && g_StageSelect.select_y <= SELECT_MAX_Y)
			{
				g_StageSelect.select_y = 0;
			}

			//y��4�Ȃ�3�ɂ���i�������j
			if (g_StageSelect.select_y < 5 && g_StageSelect.select_y >= 4)
			{
				g_StageSelect.select_y = 0;
			}
			//y��0�����Ȃ�1�ɂ���i�ォ�牺�j
			if (g_StageSelect.select_y < 0)
				g_StageSelect.select_y = SELECT_MAX_Y - 1;

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
			DeleteMissionStageSelect();
			stage_select_once = false;
			stage_select_once_time = 0;
		}


		// ���肵�ăV�[�����ς�鏈��

		// �G���^�[�L�[�������ăQ�[���X�^�[�g�����鏈��
		if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
		{
			StageDecision = true;
			// �ړ����͂̂Ƃ��ł��łɃX�e�[�W�f�[�^�͂�����Ă���̂ł��̂܂܂�����OK
			g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			// �v���C���[�z�u�t�F�[�Y�ɍs���O�ɑO��̔z�u�������Z�b�g����
			ResetPlacementArray();
			SceneTransition(SCENE_PLACEMENT);

			g_SENo = LoadSound("data/SE/Accent03-1.wav");
			PlaySound(g_SENo, 0);
		}

		// �}�E�X���\���ɂ����Ă����Ԃō��N���b�N��������
		if (mouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
		{
			g_SENo = LoadSound("data/SE/Accent03-1.wav");
			PlaySound(g_SENo, 0);

			StageDecision = true;
			// �ړ����͂̂Ƃ��ł��łɃX�e�[�W�f�[�^�͂�����Ă���̂ł��̂܂܂�����OK
			g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			// �v���C���[�z�u�t�F�[�Y�ɍs���O�ɑO��̔z�u�������Z�b�g����
			ResetPlacementArray();
			if (g_StageSelect.select_x == 0 && g_StageSelect.select_y == 3)
			{
				SceneTransition(SCENE_TITLE);
			}
			else
			{
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

		// �X�e�[�W�f�[�^���󂯎��,�~�b�V������}�b�v�̕\���Ŏg�����߁B
		// x��y����}�b�v�̔ԍ����v�Z����
		int stagenum = (SELECT_MAX_X * g_StageSelect.select_y) + (g_StageSelect.select_x + 1);
		SetStageData(stagenum);

		if (g_StageSelect.select_y != 3)
		{
			// �X�e�[�W�f�[�^���󂯎����(�X�V���ꂽ)�̂Ń~�b�V������\��������
			DrawMissionStageSelect();
		}


		

		//�X�e�[�W�I��
		for (int x = 0; x < SELECT_MAX_X; x++)
		{
			for (int y = 0; y < SELECT_MAX_Y; y++)
			{
				// ���݂̍��W�����߂�
				float now_x = stage_origin_x + interval_x * x;
				float now_y = stage_origin_y + interval_y * y;

				// �����B�I�����Ă���Ƃ��������đ傫���T�C�Y�ŕ\���B
				if (g_StageSelect.select_x == x)
				{
					if (g_StageSelect.select_y == y)
					{
						now_stage_select_EffectArray =
							SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
								D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
								1.0f, 1.0f, 0, 999, 0, 60,
								0.0f, 0.0f, 0);

						g_SENo = LoadSound("data/SE/Accent03-1.wav");
						PlaySound(g_SENo, 0);
					}
				}

				
			}


		}

		// �^�C�g���ɖ߂鏈�� (���[���h�I���ɖ߂�{�^���̕\��)
		if (g_StageSelect.select_x == 0 && g_StageSelect.select_y == 3)
		{
			SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
				D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
				0.0f, 1.0f, 0, 999, 0, 60,
				0.0f, 0.0f, 0);
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
	SetEffect(tex_NowWorld_background, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
		D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
		0.0f, 1.0f, 100, 999, 0, 180,
		0.0f, 0.0f, 0);

	// �X�e�[�W�I���̎��̌��_�ƂȂ�ꏊ
	float	stage_origin_x = 240.0f;			    // x�̌��_(0,0��I�����Ă���Ƃ�)
	float	stage_origin_y = 200.0f;			    // y�̌��_(0,0��I�����Ă���Ƃ�)

	// �X�e�[�W�I���̎�1���ꂽ�炱�ꂾ����������Ă��
	float interval_x = 240.0f;
	float interval_y = 240.0f;


	float page_interval_x = 300.0f;



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
				stage_EffectArray[NowWorld_stagenum] =
					SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 999, 0, 0,
						0.0f, 0.0f, 0);

				// �~�b�V�������N���A���Ă���Ȃ�\������
				if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
				{
					//��
					stage_star_EffectArray[NowWorld_stagenum][0] =
					SetEffect(83, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}

				// �~�b�V�������N���A���Ă���Ȃ�\������
				if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
				{
					//��
					stage_star_EffectArray[NowWorld_stagenum][1] =
					SetEffect(84, D3DXVECTOR2(now_x - 50, now_y), D3DXVECTOR2(now_x - 50, now_y), 0,
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

	return;
}

void ChangePage()
{
	{
		SAVEDATA* p_Savedata = GetSavedata();
		STAGEDATA* p_Stagedata = GetStagedata();

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


		float page_interval_x = 300.0f;
		float change_page_interval_x = interval_x * SELECT_MAX_X + page_interval_x;

		float change_page_interval = -change_page_interval_x;

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

					D3DXVECTOR2 now_stagePos	= GetEffectPos(stage_EffectArray[NowWorld_stagenum]);
					D3DXVECTOR2 now_stage_starPos[3];
					now_stage_starPos[0]= GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][0]);
					now_stage_starPos[1]= GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][1]);
					now_stage_starPos[2]= GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][2]);

					// �I������ĂȂ��Ƃ��̕\�����o��(�X�e�[�W���ׂ�)
						ChangeEffect(stage_EffectArray[NowWorld_stagenum], tex_NowWorld_stagechoice, now_stagePos, D3DXVECTOR2(now_stagePos.x + change_page_interval, now_stagePos.y), 1,
							D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 999, 0, 0,
							0.0f, 0.0f, 0);

					// �~�b�V�������N���A���Ă���Ȃ�\������
					if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
					{
						//��
						ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][0], 83, now_stage_starPos[0], D3DXVECTOR2(now_stage_starPos[0].x + change_page_interval, now_stage_starPos[0].y), 1,
								D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
								0.0f, 1.0f, 120, 999, 0, 60,
								0.0f, 0.0f, 0);
					}

					// �~�b�V�������N���A���Ă���Ȃ�\������
					if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
					{
						//��
						ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][1], 84, now_stage_starPos[1], D3DXVECTOR2(now_stage_starPos[1].x + change_page_interval, now_stage_starPos[1].y), 1,
								D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
								0.0f, 1.0f, 120, 999, 0, 60,
								0.0f, 0.0f, 0);
					}

					// �~�b�V�������N���A���Ă���Ȃ�\������
					if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
					{
						//��
						ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][2], 85, now_stage_starPos[2], D3DXVECTOR2(now_stage_starPos[2].x + change_page_interval, now_stage_starPos[2].y), 1,
								D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
								0.0f, 1.0f, 120, 999, 0, 60,
								0.0f, 0.0f, 0);
					}
				}
			}
		}

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

		return;
	}
}