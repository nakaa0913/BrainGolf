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

bool pauseclickuse = false;	//�|�[�Y��ʂ��J�������ǂ���
bool Abovemap = false;			//�ォ�王�_�̃{�^��
bool pausemission = false;	//�~�b�V�����̃{�^��

bool pauseonce = false;
bool stretching = false;

bool gameover_pause = false;
bool goal2_pause = false;
bool deleteonce = false;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPause(void)
{
	deleteonce = false;

	//�e�N�X�`���ǂݍ���

	STAGEDATA* p_Stagedata = GetStagedata();
	pause = false;

	gameover_pause = false;
	goal2_pause = false;
	
	//������
	pause_select_once = false;
	now_pause_select_EffectArray = -1;
	pause_select_once_time = 0;



	//�|�[�Y�{�^���̕\��
	SetEffect(102, D3DXVECTOR2(50, 50), D3DXVECTOR2(50, 50), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
		0.0f, 1.0f, 30, 999, 0, 90,
		0.0f, 0.0f, 0);


	pauseclickuse = false;	//�|�[�Y��ʂ��J�������ǂ���
	Abovemap = false;			//�ォ�王�_�̃{�^��
	pausemission = false;	//�~�b�V�����̃{�^��
	pause_cool = CLICK_COOLTIME;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPause(void)
{
	gameover_pause = false;
	goal2_pause = false;
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

	// �}�E�X�̍��W���g���Ă̓��͏���
	if (goal2_pause == false)
	{
		if (gameover_pause == false)
		{
			if (pauseclickuse == false)
			{
				if (pause_cool <= 0)
				{
					//�|�[�Y�{�^�� 1200 700	300 300
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 15.0f && mouse_pos_Y < 85.0f)
					{
						//g_Pause.selectpush = 0;

						pausemouseuse = true;

						// �}�E�X���\���ɂ����Ă����Ԃō��N���b�N��������
						if (pausemouseuse && mouse_Lclick)
						{
							//�|�[�Y��ʂ��J��
							pauseclickuse = true;
							pause_cool = CLICK_COOLTIME;
						}
					}
				}
			}
			//�|�[�Y��ʂ��J���Ă�����
			if (pauseclickuse)
			{
				if (stretching == false) {
					//���邭����Ȃ�48�Â�����Ȃ�4
					now_pause_select_EffectArray =
						SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
							D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2), 0,
							0.0f, 0.25f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);
				}

				//�|�[�Y�{�^���̕\��
				SetEffect(103, D3DXVECTOR2(50, 50), D3DXVECTOR2(50, 50), 0,
					D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

				// �ォ��̃}�b�v
				SetEffect(64, D3DXVECTOR2(50, 150), D3DXVECTOR2(50, 150), 0,
					D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

				// ���g���C
				SetEffect(65, D3DXVECTOR2(50, 250), D3DXVECTOR2(50, 250), 0,
					D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

				// �~�b�V����
				SetEffect(66, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
					D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

				// �X�e�[�W�I��
				SetEffect(67, D3DXVECTOR2(50, 450), D3DXVECTOR2(50, 450), 0,
					D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

				//�v���C���[�z�u�ɖ߂�
				SetEffect(99, D3DXVECTOR2(100.0f, 550.0f), D3DXVECTOR2(100.0f, 550.0f), 1,
					D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

				if (pause_cool <= 0)
				{
					//�|�[�Y��ʂ̒��̃{�^��(�ォ�王�_�A���g���C�A�~�b�V�����A�X�e�[�W�I��)

						///////�ォ��̃}�b�v/////////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 112.0f && mouse_pos_Y < 180.0f)
					{
						pausemouseuse = true;

						// �I�����܂����}�[�N
						SetEffect(73, D3DXVECTOR2(50, 150), D3DXVECTOR2(50, 150), 0,
							D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);

						if (pausemouseuse && mouse_Lclick)
						{
							//Abovemap = !Abovemap;
							pause_cool = CLICK_COOLTIME;
							if (Abovemap)
							{
								pausemission = false;
								DeleteMissionPause();


								/*DrawBGaboveForPlacement();
								DrawPlayerForPlacement();*/
							}
							else
							{
								Abovemap = true;
							}
						}
					}

					/////////////���g���C//////////////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 212.0f && mouse_pos_Y < 280.0f)
					{

						pausemouseuse = true;

						// �I�����܂����}�[�N
						SetEffect(73, D3DXVECTOR2(50, 250), D3DXVECTOR2(50, 250), 0,
							D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);

						if (pausemouseuse && mouse_Lclick)
						{
							SceneTransition(SCENE_GAME);
							//pauseclickuse = false;
							////�ォ�王�_���~�b�V�������J���Ă��������
							//Abovemap = false;
							//pausemission = false;
							//DeleteMissionPause();
						}


					}

					////////�~�b�V����/////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 312.0f && mouse_pos_Y < 380.0f)
					{
						pausemouseuse = true;
						if (pausemission == false)
						{
							// �I�����܂����}�[�N
							SetEffect(73, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
								D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
								0.0f, 1.0f, 0, 1, 0, 1,
								0.0f, 0.0f, 0);
						}
						//�~�b�V������\������
						if (pausemouseuse && mouse_Lclick)
						{
							//above���J���Ă������
							Abovemap = false;
							stretching = !stretching;

							pausemission = !pausemission;
							pause_cool = CLICK_COOLTIME;

							if (pausemission)
							{
								/*SetEffect(70, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
									D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
									0.0f, 1.0f, 0, 1, 0, 1,
									0.0f, 0.0f, 0);*/
								DrawMissionPause();
							}
							else
							{
								pausemission = false;
								stretching = false;
								DeleteMissionPause();
							}

						}

					}

					////////�X�e�[�W�I��/////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 412.0f && mouse_pos_Y < 480.0f)
					{
						pausemouseuse = true;

						// �I�����܂����}�[�N
						SetEffect(73, D3DXVECTOR2(50, 450), D3DXVECTOR2(50, 450), 0,
							D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);

						if (pausemouseuse && mouse_Lclick && (Abovemap || pausemission))
						{
							SceneTransition(SCENE_STAGE_SELECT);
							/*pauseclickuse = false;
							Abovemap = false;
							pausemission = false;
							DeleteMissionPause();*/

						}
						if (pausemouseuse && mouse_Lclick)
						{
							SceneTransition(SCENE_STAGE_SELECT);
							pauseclickuse = false;
						}

					}

					////////�z�u����/////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 175.0f && mouse_pos_Y > 500.0f && mouse_pos_Y < 600.0f)
					{
						pausemouseuse = true;

						// �I�����܂����}�[�N
						SetEffect(73, D3DXVECTOR2(100, 550), D3DXVECTOR2(100, 550), 0,
							D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);

						if (pausemouseuse && mouse_Lclick)
						{
							SceneTransition(SCENE_PLACEMENT);
							//pauseclickuse = false;
							////�ォ�王�_���~�b�V�������J���Ă��������
							//Abovemap = false;
							//pausemission = false;
							//DeleteMissionPause();
						}

					}

					//�|�[�Y�{�^������ 1200 700	300 300
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 15.0f && mouse_pos_Y < 85.0f)
					{
						//g_Pause.selectpush = 0;
						pausemouseuse = true;

						// �}�E�X���\���ɂ����Ă����Ԃō��N���b�N��������
						if (pausemouseuse && mouse_Lclick)
						{
							//�|�[�Y��ʂ����
							pauseclickuse = false;
							pausemission = false;
							Abovemap = false;
							DeleteMissionPause();
							stretching = false;
							pause_cool = CLICK_COOLTIME;
						}
					}

					
				}
				//�o�c��̕\��
				if (pausemission)
				{
					SetEffect(70, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				
					//��ʂ�360���E����������|�[�Y��ʂ����ׂĕ���
					if (mouse_pos_X > 360.0f)
					{
						
						if (mouse_Lclick)
						{
							pauseclickuse = false;
							pausemission = false;
							Abovemap = false;
							DeleteMissionPause();
							stretching = false;
							//pause_cool = CLICK_COOLTIME;
						}
					}
				

			}
		}
	}
	
	if (deleteonce == false)
	{
		if (gameover_pause == true || goal2_pause == true)
		{
			deleteonce = true;

			pauseclickuse = false;
			pausemission = false;
			Abovemap = false;
			DeleteMissionPause();
		}
	}



	if (pause_cool > 0)
		pause_cool--;
	
	/*if (ClickCool > 0)
		ClickCool--;*/
		//// ���t���[���J�E���g�𑝂₷
		//g_Pause.goaltime++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPause(void)
{
	//�ォ�王�_�̕\��
	if (Abovemap)
	{
		//���邭����Ȃ�48�Â�����Ȃ�4
		ChangeEffect(now_pause_select_EffectArray, 4, D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
			0.0f, 0.5f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

			//�o�c��̕\��
			SetEffect(70, D3DXVECTOR2(50, 150), D3DXVECTOR2(50, 150), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);

			DrawBGaboveForPlacement();
			DrawPlayerForPlacement();
	}

	//�~�b�V����
	if (pausemission)
	{
		if (stretching == true) {
			//���邭����Ȃ�48�Â�����Ȃ�4
			ChangeEffect(now_pause_select_EffectArray, 4, D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), 0,
				D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
				0.0f, 0.5f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		
		}

		////�o�c��̕\��
		//SetEffect(70, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
		//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		//	0.0f, 1.0f, 0, 1, 0, 1,
		//	0.0f, 0.0f, 0);
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

void GoalTrue_Pause()
{
	goal2_pause = true;

	return;
}

void GameoverTrue_Pause()
{
	gameover_pause = true;

	return;
}
