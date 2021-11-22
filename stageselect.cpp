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

/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static STAGESELECT g_StageSelect;

static int	g_TextureNo = 0;	// �e�N�X�`�����
static int	g_BGMNo = 0;		// BGM���ʎq

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

}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateStageSelect(void)
{
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

		//�X�y�[�X�L�[��������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
		//if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
		//{
		//	SetVolume(g_BGMNo, 0.1f);

		//	//RESULT�ֈڍs����
		//	SceneTransition(SCENE_GAME);
		//}


		//��
		SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
			D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);




		// �ړ��L�[�������ꂽ���̏���
		if (g_StageSelect.selectcooltime <= 0)
		{
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

			// �}�E�X�ł̑���
			//1 240 200
			if (mouse_pos_X > 165.0f && mouse_pos_X < 315.0f && mouse_pos_Y > 125.0f && mouse_pos_Y < 275.0f)
			{
				g_StageSelect.select_x = 0;
				g_StageSelect.select_y = 0;
				mouseuse = true;
			}

			//2 480 200
			else if (mouse_pos_X > 405.0f && mouse_pos_X < 555.0f && mouse_pos_Y > 125.0f && mouse_pos_Y < 275.0f)
			{
				g_StageSelect.select_x = 1;
				g_StageSelect.select_y = 0;
				mouseuse = true;
			}

			//3 720 200
			else if (mouse_pos_X > 645.0f && mouse_pos_X < 795.0f && mouse_pos_Y > 125.0f && mouse_pos_Y < 275.0f)
			{
				g_StageSelect.select_x = 2;
				g_StageSelect.select_y = 0;
				mouseuse = true;
			}

			//4 960 200
			else if (mouse_pos_X > 885.0f && mouse_pos_X < 1035.0f && mouse_pos_Y > 125.0f && mouse_pos_Y < 275.0f)
			{
				g_StageSelect.select_x = 3;
				g_StageSelect.select_y = 0;
				mouseuse = true;
			}

			//5 1200 200
			else if (mouse_pos_X > 1125.0f && mouse_pos_X < 1275.0f && mouse_pos_Y > 125.0f && mouse_pos_Y < 275.0f)
			{
				g_StageSelect.select_x = 4;
				g_StageSelect.select_y = 0;
				mouseuse = true;
			}

			//6 240 440
			if (mouse_pos_X > 165.0f && mouse_pos_X < 315.0f && mouse_pos_Y > 365.0f && mouse_pos_Y < 515.0f)
			{
				g_StageSelect.select_x = 0;
				g_StageSelect.select_y = 1;
				mouseuse = true;
			}

			//7 480 440
			else if (mouse_pos_X > 405.0f && mouse_pos_X < 555.0f && mouse_pos_Y > 365.0f && mouse_pos_Y < 515.0f)
			{
				g_StageSelect.select_x = 1;
				g_StageSelect.select_y = 1;
				mouseuse = true;
			}

			//8 720 440
			else if (mouse_pos_X > 645.0f && mouse_pos_X < 795.0f && mouse_pos_Y > 365.0f && mouse_pos_Y < 515.0f)
			{
				g_StageSelect.select_x = 2;
				g_StageSelect.select_y = 1;
				mouseuse = true;
			}

			//9 960 440
			else if (mouse_pos_X > 885.0f && mouse_pos_X < 1035.0f && mouse_pos_Y > 365.0f && mouse_pos_Y < 515.0f)
			{
				g_StageSelect.select_x = 3;
				g_StageSelect.select_y = 1;
				mouseuse = true;
			}

			//10 1200 440
			else if (mouse_pos_X > 1125.0f && mouse_pos_X < 1275.0f && mouse_pos_Y > 365.0f && mouse_pos_Y < 515.0f)
			{
				g_StageSelect.select_x = 4;
				g_StageSelect.select_y = 1;
				mouseuse = true;
			}

			// ���E�l�ɂ��C���̏���
			if (g_StageSelect.select_x >= SELECT_MAX_X)
				g_StageSelect.select_x = 0;
			if (g_StageSelect.select_x < 0)
				g_StageSelect.select_x = SELECT_MAX_X - 1;
			if (g_StageSelect.select_y >= SELECT_MAX_Y)
				g_StageSelect.select_y = 0;
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
		}

		// �}�E�X���\���ɂ����Ă����Ԃō��N���b�N��������
		if (mouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
		{
			StageDecision = true;
			// �ړ����͂̂Ƃ��ł��łɃX�e�[�W�f�[�^�͂�����Ă���̂ł��̂܂܂�����OK
			g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			// �v���C���[�z�u�t�F�[�Y�ɍs���O�ɑO��̔z�u�������Z�b�g����
			ResetPlacementArray();
			SceneTransition(SCENE_PLACEMENT);
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

		// �X�e�[�W�f�[�^���󂯎����(�X�V���ꂽ)�̂Ń~�b�V������\��������
		DrawMissionStageSelect();

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
	//�w�i�\��
	SetEffect(tex_NowWorld_background, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
		D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
		0.0f, 1.0f, 100, 999, 0, 180,
		0.0f, 0.0f, 0);

	////�~�b�V����
	//SetEffect(tex_NowWorld_mission, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
	//	D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
	//	0.0f, 1.0f, 100, 999, 0, 180,
	//	0.0f, 0.0f, 0);


	// �X�e�[�W�I���̎��̌��_�ƂȂ�ꏊ
	float	stage_origin_x = 240.0f;			    // x�̌��_(0,0��I�����Ă���Ƃ�)
	float	stage_origin_y = 200.0f;			    // y�̌��_(0,0��I�����Ă���Ƃ�)

	// �X�e�[�W�I���̎�1���ꂽ�炱�ꂾ����������Ă��
	float interval_x = 240.0f;
	float interval_y = 240.0f;

	//�X�e�[�W�I��
	for (int x = 0; x < SELECT_MAX_X; x++)
	{
		for (int y = 0; y < SELECT_MAX_Y; y++)
		{
			// ���݂̍��W�����߂�
			float now_x = stage_origin_x + interval_x * x;
			float now_y = stage_origin_y + interval_y * y;

			// �I������ĂȂ��Ƃ��̕\�����o��(�X�e�[�W���ׂ�)
			SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 999, 0, 0,
				0.0f, 0.0f, 0);
		}
	}

	return;
}