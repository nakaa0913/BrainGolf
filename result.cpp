/*==============================================================================

   ���_�Ǘ� [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include "result.h"
#include "scene.h"
#include "fade.h"
#include "effect.h"
#include "mission.h"
#include "savedata.h"
#include "stagedata.h"
#include "keyboard.h"
#include "sound.h"
#include "mouse.h"

#define GOAL_H (50)
#define GOAL_W (50)
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static RESULT g_Result;

int now_result_select_EffectArray = -1;
bool result_select_once = false;
int result_select_once_time = 0;
//bool onlyOnce = true;
bool resultmouseuse = false;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
{
	//�e�N�X�`���ǂݍ���


	g_Result.goaltime = 0;
	g_Result.selectpush = 0;


	//������
	result_select_once = false;
	now_result_select_EffectArray = -1;
	result_select_once_time = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	//�}�E�X�̍��W���擾
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();

	// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
	int OldResultSelect = g_Result.selectpush;

	if (g_Result.goaltime == 10)
	{
		//�È�4 ������Ȃ�48
		SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 100, 999, 0, 180,
			0.0f, 0.0f, 0);
		//��1440
		//�c810
		//�Q�[���N���A
		SetEffect(5, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT / 2), 1,
			0.0f, 1.0f, 30, 120, 60, 90,
			0.0f, 0.0f, 0);

	}



	if (g_Result.goaltime == 240)
	{
		//�i�A�h�o�C�X�H�j
		SetEffect(1, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
			D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
			0.0f, 1.0f, 100, 999, 0, 180,
			0.0f, 0.0f, 0);
		DrawMissionResult();
	}

	if (g_Result.goaltime == 300)
	{
		//��(�e)
		SetEffect(14, D3DXVECTOR2(550.0f, 68.0f), D3DXVECTOR2(550.0f, 68.0f), 0,
			D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
			0.0f, 1.0f, 60, 999, 0, 60,
			0.0f, 0.0f, 0);
		//��(�e)
		SetEffect(14, D3DXVECTOR2(550.0f, 163.0f), D3DXVECTOR2(550.0f, 163.0f), 0,
			D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
			0.0f, 1.0f, 60, 999, 0, 60,
			0.0f, 0.0f, 0);
		//��(�e)
		SetEffect(14, D3DXVECTOR2(550.0f, 250.0f), D3DXVECTOR2(550.0f, 250.0f), 0,
			D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
			0.0f, 1.0f, 60, 999, 0, 60,
			0.0f, 0.0f, 0);
	}

	if (g_Result.goaltime == 400)
	{
		// �~�b�V�������N���A���Ă���Ȃ�\������
		if (p_Savedata[p_Stagedata->stagenum].mission_clear[0] == 1)
		{
			////��
			SetEffect(11, D3DXVECTOR2(550.0f, 68.0f), D3DXVECTOR2(550.0f, 68.0f), 0,
				D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				0.0f, 1.0f, 120, 999, 0, 60,
				0.0f, 0.0f, 0);
		}
		//��1440
		//�c810
	}

	if (g_Result.goaltime == 430)
	{
		// �~�b�V�������N���A���Ă���Ȃ�\������
		if (p_Savedata[p_Stagedata->stagenum].mission_clear[1] == 1)
		{
			//��
			SetEffect(11, D3DXVECTOR2(550.0f, 163.0f), D3DXVECTOR2(550.0f, 163.0f), 0,
				D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				0.0f, 1.0f, 120, 999, 0, 60,
				0.0f, 0.0f, 0);
		}
	}

	if (g_Result.goaltime == 460)
	{
		// �~�b�V�������N���A���Ă���Ȃ�\������
		if (p_Savedata[p_Stagedata->stagenum].mission_clear[2] == 1)
		{
			//��
			SetEffect(11, D3DXVECTOR2(550.0f, 250.0f), D3DXVECTOR2(550.0f, 250.0f), 0,
				D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				0.0f, 1.0f, 120, 999, 0, 60,
				0.0f, 0.0f, 0);
		}
	}

	if (g_Result.goaltime >= 560)
	{
		if (g_Result.goaltime <= 8000)
		{
			if (GetKeyboardPress(DIK_RETURN))
			{
				g_Result.goaltime = 9000;
			}
			if (mouse_Lclick)
			{
				g_Result.goaltime = 9000;
			}
		}
	}

	if (g_Result.goaltime >= 9000)
	{
		//���邭����Â�����Ȃ�4
		SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//next?���̃X�e�[�W�֓I��
		SetEffect(47, D3DXVECTOR2(1200.0f, 700.0f), D3DXVECTOR2(1200.0f, 700.0f), 1,
			D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);
		
		//���[���h�I���ɖ߂�
		SetEffect(49, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
			D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//��1440
		//�c810

		if (g_Result.selectpush == 0)
		{
			//next?���̃X�e�[�W�֓I��
			SetEffect(47, D3DXVECTOR2(1200.0f, 700.0f), D3DXVECTOR2(1200.0f, 700.0f), 1,
				D3DXVECTOR2(400.0f, 400.0f), D3DXVECTOR2(400.0f, 400.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);

		}

		if (g_Result.selectpush == 1)
		{
			//���[���h�I���ɖ߂�
			SetEffect(49, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
				D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}

		/*if (g_Result.selectpush == 2)
		{
			SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), 1,
				D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(350.0f, 120.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}*/

		//�L�[����
		if (g_Result.selecttime <= 0)
		{

			if (Keyboard_IsKeyDown(KK_RIGHT))
			{
				g_Result.selectpush++;
				g_Result.selecttime = 30;

			}
			if (g_Result.selectpush >= 2)
			{
				g_Result.selectpush = 0;
			}

			if (Keyboard_IsKeyDown(KK_LEFT))
			{
				g_Result.selectpush--;
				g_Result.selecttime = 30;

			}
			if (g_Result.selectpush < 0)
			{
				g_Result.selectpush = 1;
			}

			if (g_Result.goaltime >= 9060)
			{
				if (g_Result.selectpush == 0)
				{
					if (Keyboard_IsKeyDown(KK_ENTER))
					{
						SceneTransition(SCENE_WORLD_SELECT);

					}
				}

			}


			if (g_Result.selectpush == 1)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_STAGE_SELECT);

				}
			}
		}

		// �}�E�X�̍��W���g���Ă̓��͏���
		//1 1200 700	300 300
		if (mouse_pos_X > 1050.0f && mouse_pos_X < 1350.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
		{
			g_Result.selectpush = 0;
			resultmouseuse = true;
		}
		//2 100 700		200 200
		else if (mouse_pos_X > 60.0f && mouse_pos_X < 140.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
		{
			g_Result.selectpush = 1;
			resultmouseuse = true;
		}

		// �}�E�X���������ʒu�ɂ����āA���N���b�N������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
		if (resultmouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
		{
			//SetVolume(g_BGMNo, 0.1f);

			//STAGE_SELECT�ֈڍs����
			SceneTransition(SCENE_STAGE_SELECT);
		}


		// �����O�̃t���[������ω����������ꍇ�̂݃G�t�F�N�g�Ȃǂ�ω�������
		bool Change = false;
		if (OldResultSelect != g_Result.selectpush)
			Change = true;

		// �ύX���������ꍇ�A�������ƐV�������̂̃Z�b�g
		if (Change == true)
		{
			// �������ƑO��g���Ă������̂̏���
			g_Result.selecttime = 30;
			//EffectBreak(now_result_select_EffectArray);		// �O�̕`�ʂ�����
			result_select_once = false;						// 1����`�ʂ��ĂȂ���ɂ���
			result_select_once_time = 0;						// �`�ʂ��Ă���̎��Ԃ̃��Z�b�g
		}


		if (g_Result.selecttime >= 0)
			g_Result.selecttime--;

	}

	// ���t���[���J�E���g�𑝂₷
	g_Result.goaltime++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{

}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
RESULT* GetResult(void)
{
	return &g_Result;
}


void SetResult(D3DXVECTOR2 pos)
{

}