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
#include "pause.h"
#include "scene.h"
#include "fade.h"
#include "effect.h"
#include "mission.h"
#include "savedata.h"
#include "stagedata.h"
#include "keyboard.h"
#include "sound.h"
#include "mouse.h"
#include "pause.h"
#include "game.h"
#include "placement.h"

//#define GOAL_H (50)
//#define GOAL_W (50)
#define CLICK_COOLTIME	(20)			// �N���b�N�̃N�[���^�C��
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

bool pause;			// �����|�[�Y�����ǂ���
int pause_cool;		// �|�[�Y�؂�ւ��̃N�[���^�C��

int now_pause_select_EffectArray = -1;
bool pause_select_once = false;
int pause_select_once_time = 0;
//bool onlyOnce = true;
bool pausemouseuse = false;

bool pauseclickuse = false;
bool pauseopen = false;
bool Above = false;
int ClickCool = CLICK_COOLTIME;



//=============================================================================
// ����������
//=============================================================================
HRESULT InitPause(void)
{
	//�e�N�X�`���ǂݍ���

	STAGEDATA* p_Stagedata = GetStagedata();
	pause = false;


	//������
	pause_select_once = false;
	now_pause_select_EffectArray = -1;
	pause_select_once_time = 0;



	//�|�[�Y�{�^���̕\��
	SetEffect(62, D3DXVECTOR2(50, 50), D3DXVECTOR2(50, 50), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
		0.0f, 1.0f, 30, 999, 0, 90,
		0.0f, 0.0f, 0);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPause(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePause(void)
{

	//�}�E�X�̍��W���擾
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();

	// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
	/*int OldPauseSelect = g_Pause.selectpush;*/



	//// �����|�[�Y��ԂȂ�
	//if (pause == true)
	//{

	//	// �Ƃ肠�����͂����肾��
	//	SetEffect(62, D3DXVECTOR2(400, 400), D3DXVECTOR2(400, 400), 0,
	//		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
	//		0.0f, 1.0f, 0, 1, 0, 30,
	//		0.0f, 0.0f, 0);



	//}



	////�@P�L�[��������ă|�[�Y��Ԃ�؂�ւ��鏈��
	//if (pause_cool <= 0)
	//{
	//	if (Keyboard_IsKeyDown(KK_P))
	//	{
	//		pause = !pause;

	//		pause_cool = PUSHKEY_COOLTIME;

	//	}
	//}



	// �}�E�X�̍��W���g���Ă̓��͏���

		//1 1200 700	300 300
	if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 15.0f && mouse_pos_Y < 85.0f)
	{
		//g_Pause.selectpush = 0;
		pausemouseuse = true;

		// �}�E�X���\���ɂ����Ă����Ԃō��N���b�N��������
		if (pausemouseuse && mouse_Lclick)
		{
			//�|�[�Y��ʂ��J��
			pauseclickuse = true;
		}
	}
	//�|�[�Y��ʂ��J���Ă�����
	if (pauseclickuse)
	{


		//���邭����Ȃ�48�Â�����Ȃ�4
		SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 1,
			D3DXVECTOR2(0, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		// �ォ��̃}�b�v
		SetEffect(64, D3DXVECTOR2(50, 150), D3DXVECTOR2(50, 150), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);

		// �z�u�����蒼��
		SetEffect(65, D3DXVECTOR2(50, 250), D3DXVECTOR2(50, 250), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);

		// �~�b�V����
		SetEffect(66, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);

		// �X�e�[�W�I��
		SetEffect(67, D3DXVECTOR2(50, 450), D3DXVECTOR2(50, 450), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);

		if (ClickCool <= 0)
		{
			//�|�[�Y��ʂ̃{�^���������Ă��Ȃ�������i�|�[�Y��ʂ͊J���Ă����ԁj
			if (pauseopen == false)
			{
				///////�ォ��̃}�b�v/////////////
				if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 112.0f && mouse_pos_Y < 180.0f)
				{
					pausemouseuse = true;
					if (Above == false)
					{
						if (pausemouseuse && mouse_Lclick)
						{
							Above = true;
							ClickCool = CLICK_COOLTIME;
							pauseopen = true;
						}
					}
					if (ClickCool <= 0)
					{
						if (Above == true && pauseopen == true)
						{
							if (mouse_Lclick)
							{
								Above = false;
								ClickCool = CLICK_COOLTIME;
								pauseclickuse = false;

							}
						}
					}
				}

				/////////////�z�u�����蒼��//////////////////
				if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 212.0f && mouse_pos_Y < 280.0f)
				{
					pausemouseuse = true;
					if (pausemouseuse && mouse_Lclick)
					{
						SceneTransition(SCENE_PLACEMENT);
						pauseclickuse = false;
						//pauseopen = true;
					}

				}

				////////�~�b�V����/////////
				if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 312.0f && mouse_pos_Y < 380.0f)
				{
					pausemouseuse = true;
					if (pauseopen == false)
					{
						if (pausemouseuse && mouse_Lclick)
						{
							pauseopen = true;
							DrawMissionPause();
							ClickCool = CLICK_COOLTIME;
						}
					}
					if (pauseopen == true)
					{
						if (pausemouseuse && mouse_Lclick)
						{
							pauseopen = false;
							//DeleteMissionPause();
							ClickCool = CLICK_COOLTIME;
						}
					}
				}

				////////�X�e�[�W�I��/////////
				if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 412.0f && mouse_pos_Y < 480.0f)
				{
					pausemouseuse = true;
					if (pausemouseuse && mouse_Lclick)
					{
						SceneTransition(SCENE_STAGE_SELECT);
						pauseclickuse = false;
						//pauseopen = true;
					}
				}

			}
		}/////////////////


		if (mouse_pos_X > 360.0f)
		{
			if (mouse_Lclick)
			{
				pauseclickuse = false;
			}
		}
		//}
	}

	//bool Change = false;
	//if (pauseopen && pauseclickuse && mouse_Lclick)
	//	Change = true;
	//// �ύX���������ꍇ�A�������ƐV�������̂̃Z�b�g
	//if (Change == true)
	//{
	//	ClickCool = CLICK_COOLTIME;
	//	EffectBreak(now_pause_select_EffectArray);
	//	DeleteMissionPause();
	//	pause_select_once = false;
	//	pause_select_once_time = 0;


	//}

	if (pause_cool > 0)
		pause_cool--;

	if (ClickCool > 0)
		ClickCool--;
	//// ���t���[���J�E���g�𑝂₷
	//g_Pause.goaltime++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPause(void)
{
	 //�ォ�王�_�̕\��
	if (Above)
	{
		DrawBGaboveForPlacement();
		DrawPlayerForPlacement();
	}
}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
//PAUSE* GetPause(void)
//{
//	return &g_Pause;
//}


void SetPause(D3DXVECTOR2 pos)
{

}