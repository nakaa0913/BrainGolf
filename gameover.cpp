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
#include "sound.h"
#include "fade.h"
#include "effect.h"
#include "mission.h"
#include "savedata.h"
#include "stagedata.h"
#include "keyboard.h"
#include "gameover.h"
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
static GAMEOVER g_Gameover;
static int g_GameoverSENo = 0;

int			onceSE;
bool result_click2 = false; //���U���g��ʂɍs�����ǂ�����

//�G�t�F�N�g�֘A
int map_back2 = -1;			// �}�b�v�߂�
int gameover = -1;				// �Q�[���N���A
int next2 = -1;				//	����
int result2 = -1;			//	���U���g
int placement2 = -1;			//	�z�u����
bool result_over_once = false;
int result_over_once_time = 0;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitGameover(void)
{
	//�e�N�X�`���ǂݍ���

	result_over_once = false;
	g_Gameover.gameovertime = 0;
	g_Gameover.selectpush = 0;
	g_Gameover.resulttime2 = 0;

	//������
	g_GameoverSENo = LoadSound("data/SE/Phrase04-1.wav");
	onceSE = 0;
	result_click2 = false;
	map_back2 = -1;
	gameover = -1;
	next2 = -1;				//	����
	result2 = -1;			//	���U���g
	placement2 = -1;			//	�z�u����
	result_over_once_time = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameover(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameover(void)
{
	if (onceSE == 0)
	{
		PlaySound(g_GameoverSENo, 0);
		onceSE = 1;
	}
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();
	//�}�E�X�̍��W���擾
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouseuse = false;

	// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
	int OldResultSelect = g_Gameover.selectpush;

	// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
	//int OldnowchoiceX = nowchoice.x;
	//int OldnowchoiceY = nowchoice.y;

	if (result_click2 == false)
	{
		if (g_Gameover.gameovertime == 1)
		{
			//�È�4 ������Ȃ�48
			SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
				D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
				0.0f, 0.5f, 100, 999, 0, 180,
				0.0f, 0.0f, 0);
			//��1440
			//�c810

			gameover =
			//�Q�[���I�[�o�[
			SetEffect(55, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1300, 700), 1,
				0.0f, 1.0f, 30, 999, 0, 90,
				0.0f, 0.0f, 0);

		}
	

		if (g_Gameover.gameovertime == 90)
		{
			////���邭����Â�����Ȃ�4
			//SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			//	D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			//	0.0f, 0.5f, 0, 1, 0, 1,
			//	0.0f, 0.0f, 0);

			////�X�e�[�W��
			//SetEffect(57, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			//	D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 1,
			//	0.0f, 1.0f, 0, 999, 0, 1,
			//	0.0f, 0.0f, 0);

	

			next2 =
			//���X�^�[�g
			SetEffect(79, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 1,
				D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
				0.0f, 1.0f, 0, 999, 0, 1,
				0.0f, 0.0f, 0);

			placement2 =
			//�v���C���[�z�u�ɖ߂�
			SetEffect(99, D3DXVECTOR2(1100.0f, 700.0f), D3DXVECTOR2(1100.0f, 700.0f), 1,
				D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
				0.0f, 1.0f, 0, 999, 0, 1,
				0.0f, 0.0f, 0);

			map_back2 =
			//�}�b�v�H�ɖ߂�
			SetEffect(75, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
				D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
				0.0f, 1.0f, 0, 999, 0, 1,
				0.0f, 0.0f, 0);

			result2 =
			//���U���g�ɍs��
			SetEffect(97, D3DXVECTOR2(700.0f, 550.0f), D3DXVECTOR2(700.0f, 550.0f), 1,
				D3DXVECTOR2(700.0f, 80.0f), D3DXVECTOR2(700.0f, 80.0f), 1,
				0.0f, 1.0f, 0, 999, 0, 1,
				0.0f, 0.0f, 0);
		}
			//��1440
			//�c810

			if (g_Gameover.gameovertime >= 90)
			{
				if (g_Gameover.selectpush == 0)
				{
					//next?���̃X�e�[�W�֓I��
					SetEffect(80, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);


				}

				if (g_Gameover.selectpush == 1)
				{
					//���[���h�I���ɖ߂�
					SetEffect(76, D3DXVECTOR2(90.0f, 700.0f), D3DXVECTOR2(90.0f, 700.0f), 1,
						D3DXVECTOR2(227.0f, 202.0f), D3DXVECTOR2(227.0f, 202.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Gameover.selectpush == 2)
				{
					//�v���C���[�z�u�ɖ߂�
					SetEffect(100, D3DXVECTOR2(1100.0f, 700.0f), D3DXVECTOR2(1100.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 109.0f), D3DXVECTOR2(200.0f, 109.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Gameover.selectpush == 3)
				{
					//���U���g�ɍs��
					SetEffect(98, D3DXVECTOR2(700.0f, 545.0f), D3DXVECTOR2(700.0f, 545.0f), 1,
						D3DXVECTOR2(725.0f, 85.0f), D3DXVECTOR2(725.0f, 85.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				/*if (g_Gameover.selectpush == 2)
				{
					SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), 1,
						D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(350.0f, 120.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}*/


				//if (g_Gameover.selecttime <= 0)
				//{

				//	if (Keyboard_IsKeyDown(KK_RIGHT))
				//	{
				//		g_Gameover.selectpush++;
				//		g_Gameover.selecttime = 30;

				//	}
				//	if (g_Gameover.selectpush >= 3)
				//	{
				//		g_Gameover.selectpush = 0;
				//	}

				//	if (Keyboard_IsKeyDown(KK_LEFT))
				//	{
				//		g_Gameover.selectpush--;
				//		g_Gameover.selecttime = 30;

				//	}
				//	if (g_Gameover.selectpush < 0)
				//	{
				//		g_Gameover.selectpush = 2;
				//	}

				//	/*if (g_Gameover.gameovertime >= 9060)
				//	{
				//		if (Keyboard_IsKeyDown(KK_ENTER))
				//		{
				//			SceneTransition(SCENE_WORLD_SELECT);

				//		}
				//	}*/

				//	if (g_Gameover.selectpush == 0)
				//	{
				//		if (Keyboard_IsKeyDown(KK_ENTER))
				//		{
				//			SceneTransition(SCENE_GAME);

				//		}
				//	}

				//	if (g_Gameover.selectpush == 1)
				//	{
				//		if (Keyboard_IsKeyDown(KK_ENTER))
				//		{
				//			SceneTransition(SCENE_STAGE_SELECT);

				//		}
				//	}

				//	if (g_Gameover.selectpush == 2)
				//	{
				//		if (Keyboard_IsKeyDown(KK_ENTER))
				//		{
				//			SceneTransition(SCENE_PLACEMENT);

				//		}
				//	}

				//}

				//�}�E�X����
				//next				1200, 700
				if (mouse_pos_X > 1215.0f && mouse_pos_X < 1370.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Gameover.selectpush = 0;
					mouseuse = true;
				}
				//���[���h�I��		100, 700
				if (mouse_pos_X > 22.0f && mouse_pos_X < 150.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Gameover.selectpush = 1;
					mouseuse = true;
				}
				//�v���C���[�z�u	600, 700
				if (mouse_pos_X > 1025.0f && mouse_pos_X < 1175.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Gameover.selectpush = 2;
					mouseuse = true;
				}

				//���U���g�ɂ���
				if (mouse_pos_X > 550.0f && mouse_pos_X < 840.0f && mouse_pos_Y > 500.0f && mouse_pos_Y < 600.0f)
				{
					g_Gameover.selectpush = 3;
					mouseuse = true;
				}

				if (mouseuse && mouse_Lclick)
				{
					if (g_Gameover.selectpush == 0)
					{
						SceneTransition(SCENE_GAME);
					}

					if (g_Gameover.selectpush == 1)
					{
						SceneTransition(SCENE_STAGE_SELECT);
					}

					if (g_Gameover.selectpush == 2)
					{
						SceneTransition(SCENE_PLACEMENT);
					}
				}

				if (g_Gameover.selectpush == 3)
				{
					if (mouseuse && mouse_Lclick)
					{
						result_click2 = true;
						g_Gameover.gameovertime = 0;
						EffectBreak(map_back2);
						EffectBreak(gameover);
						EffectBreak(next2);
						EffectBreak(placement2);
						EffectBreak(result2);
					}
				}
			}
			if (g_Gameover.selecttime >= 0)
				g_Gameover.selecttime--;

	
		// ���t���[���J�E���g�𑝂₷
		g_Gameover.gameovertime++;
	}

	if (result_click2 == true)
	{

		if (g_Gameover.resulttime2 == 10)
		{
			////�È�4 ������Ȃ�48
			//SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			//	D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			//	0.0f, 0.5f, 100, 999, 0, 180,
			//	0.0f, 0.0f, 0);
			//��1440
			//�c810
			//�Q�[���N���A
			/*SetEffect(5, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT / 2), 1,
				0.0f, 1.0f, 30, 120, 60, 90,
				0.0f, 0.0f, 0);*/

		}



		if (g_Gameover.resulttime2 == 30)
		{
			//�i�A�h�o�C�X�H�j
			/*SetEffect(1, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
				D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
				0.0f, 1.0f, 100, 999, 0, 180,
				0.0f, 0.0f, 0);*/
			SetEffect(74, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				D3DXVECTOR2(1400, 800), D3DXVECTOR2(1400, 800), 1,
				0.0f, 1.0f, 100, 999, 0, 180,
				0.0f, 0.0f, 0);
			//DrawMissionResult();
		}

		if (g_Gameover.resulttime2 == 30)
		{
			//��(�e)
			SetEffect(82, D3DXVECTOR2(800.0f, 280.0f), D3DXVECTOR2(800.0f, 280.0f), 0,
				D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
				0.0f, 1.0f, 60, 999, 0, 60,
				0.0f, 0.0f, 0);
			//��(�e)
			SetEffect(82, D3DXVECTOR2(800.0f, 360.0f), D3DXVECTOR2(800.0f, 360.0f), 0,
				D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
				0.0f, 1.0f, 60, 999, 0, 60,
				0.0f, 0.0f, 0);
			//��(�e)
			SetEffect(82, D3DXVECTOR2(800.0f, 440.0f), D3DXVECTOR2(800.0f, 440.0f), 0,
				D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
				0.0f, 1.0f, 60, 999, 0, 60,
				0.0f, 0.0f, 0);
		}

		if (g_Gameover.resulttime2 == 80)
		{
			// �~�b�V�������N���A���Ă���Ȃ�\������
			if (p_Savedata[p_Stagedata->stagenum].mission_clear[0] == 1)
			{
				////��
				SetEffect(83, D3DXVECTOR2(800.0f, 280.0f), D3DXVECTOR2(800.0f, 280.0f), 0,
					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
					0.0f, 1.0f, 120, 999, 0, 60,
					0.0f, 0.0f, 0);
			}
			//��1440
			//�c810
		}

		if (g_Gameover.resulttime2 == 100)
		{
			// �~�b�V�������N���A���Ă���Ȃ�\������
			if (p_Savedata[p_Stagedata->stagenum].mission_clear[1] == 1)
			{
				//��
				SetEffect(84, D3DXVECTOR2(800.0f, 360.0f), D3DXVECTOR2(800.0f, 360.0f), 0,
					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
					0.0f, 1.0f, 120, 999, 0, 60,
					0.0f, 0.0f, 0);
			}
		}

		if (g_Gameover.resulttime2 == 120)
		{
			// �~�b�V�������N���A���Ă���Ȃ�\������
			if (p_Savedata[p_Stagedata->stagenum].mission_clear[2] == 1)
			{
				//��
				SetEffect(85, D3DXVECTOR2(800.0f, 440.0f), D3DXVECTOR2(800.0f, 440.0f), 0,
					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
					0.0f, 1.0f, 120, 999, 0, 60,
					0.0f, 0.0f, 0);
			}
		}

		/*if (g_Result.resulttime >= 120)
		{
			if (g_Result.resulttime <= 200)
			{
				if (GetKeyboardPress(DIK_RETURN))
				{
					g_Result.resulttime = 210;
				}
				if (mouse_Lclick)
				{
					g_Result.resulttime = 210;
				}
			}
		}*/

		if (g_Gameover.resulttime2 >= 160)
		{
			//���邭����Â�����Ȃ�4
			/*SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
				D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
				0.0f, 0.5f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);*/

				//next?���̃X�e�[�W�֓I��
			SetEffect(77, D3DXVECTOR2(1080.0f, 700.0f), D3DXVECTOR2(1080.0f, 700.0f), 1,
				D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);

			//���[���h�I���ɖ߂�
			SetEffect(75, D3DXVECTOR2(400.0f, 700.0f), D3DXVECTOR2(400.0f, 700.0f), 1,
				D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);

			//��1440
			//�c810

			if (g_Gameover.selectpush == 0)
			{
				//next?���̃X�e�[�W�֓I��
				SetEffect(78, D3DXVECTOR2(1080.0f, 700.0f), D3DXVECTOR2(1080.0f, 700.0f), 1,
					D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

			}

			if (g_Gameover.selectpush == 1)
			{
				//���[���h�I���ɖ߂�
				SetEffect(76, D3DXVECTOR2(393.0f, 702.0f), D3DXVECTOR2(393.0f, 702.0f), 1,
					D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
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

		
			// �}�E�X�̍��W���g���Ă̓��͏���
			//1 1200 700	300 300
			if (mouse_pos_X > 930.0f && mouse_pos_X < 1230.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
			{
				g_Gameover.selectpush = 0;
				mouseuse = true;
			}
			//2 100 700		200 200
			else if (mouse_pos_X > 340.0f && mouse_pos_X < 460.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
			{
				g_Gameover.selectpush = 1;
				mouseuse = true;
			}

			// �}�E�X���������ʒu�ɂ����āA���N���b�N������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
			if (mouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
			{
				//SetVolume(g_BGMNo, 0.1f);

				//STAGE_SELECT�ֈڍs����
				SceneTransition(SCENE_GAME);
			}


			// �����O�̃t���[������ω����������ꍇ�̂݃G�t�F�N�g�Ȃǂ�ω�������
			bool Change = false;
			if (OldResultSelect != g_Gameover.selectpush)
				Change = true;

			// �ύX���������ꍇ�A�������ƐV�������̂̃Z�b�g
			if (Change == true)
			{
				// �������ƑO��g���Ă������̂̏���
				g_Gameover.selecttime = 30;
				//EffectBreak(now_result_select_EffectArray);		// �O�̕`�ʂ�����
				result_over_once = false;						// 1����`�ʂ��ĂȂ���ɂ���
				result_over_once_time = 0;						// �`�ʂ��Ă���̎��Ԃ̃��Z�b�g
			}


			if (g_Gameover.selecttime >= 0)
				g_Gameover.selecttime--;

		}

		// ���t���[���J�E���g�𑝂₷
		g_Gameover.resulttime2++;
	
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameover(void)
{

}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
GAMEOVER* GetGameover(void)
{
	return &g_Gameover;
}


void SetGameover(D3DXVECTOR2 pos)
{

}