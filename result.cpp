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
#include "gamedata.h"
#include "game.h"
#include "stageselect.h"
#include "placement.h"

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
bool result_click = false; //���U���g��ʂɍs�����ǂ�����

//�G�t�F�N�g�֘A
int map_back = -1;			// �}�b�v�߂�
int clear = -1;				// �Q�[���N���A
int next = -1;				//	����
int result = -1;			//	���U���g
int placement = -1;			//	�z�u����
int retry = -1;

bool resultfin = false;		// �S�ďI������牽�����Ȃ��悤��

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
{
	resultfin = false;

	//�e�N�X�`���ǂݍ���


	g_Result.goaltime = 0;
	g_Result.selectpush = 0;
	g_Result.resulttime = 0;

	//������
	result_select_once = false;
	now_result_select_EffectArray = -1;
	result_select_once_time = 0;
	result_click = false;
	map_back = -1;
	clear = -1;
	next = -1;				//	����
	result = -1;			//	���U���g
	placement = -1;			//	�z�u����
	retry = -1;
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
	GAMEDATA* p_Gamedata = GetGamedata();

	//�}�E�X�̍��W���擾
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();
	bool mouseuse = false;

	// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
	int OldResultSelect = g_Result.selectpush;

	if (resultfin == false)
	{
		if (result_click == false)
		{
			if (g_Result.goaltime == 10)
			{
				//�È�4 ������Ȃ�48
				SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
					D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
					0.0f, 0.5f, 100, 999, 0, 180,
					0.0f, 0.0f, 0);
				clear =
					//�Q�[���N���A
					SetEffect(5, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
						D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1300, 700), 1,
						0.0f, 1.0f, 30, 999, 0, 90,
						0.0f, 0.0f, 0);
			}
			if (g_Result.goaltime == 90)
			{
				retry =
					//���g���C
					SetEffect(79, D3DXVECTOR2(800.0f, 700.0f), D3DXVECTOR2(800.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);

				placement =
					//�v���C���[�z�u�ɖ߂�
					SetEffect(99, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);

				map_back =
					//�}�b�v�ɖ߂�
					SetEffect(75, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);

				result =
					//���U���g�ɍs��
					SetEffect(97, D3DXVECTOR2(700.0f, 550.0f), D3DXVECTOR2(700.0f, 550.0f), 1,
						D3DXVECTOR2(700.0f, 80.0f), D3DXVECTOR2(700.0f, 80.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);

				next =
					//���̃X�e�[�W
					SetEffect(77, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 1,
						D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);
			}

			if (g_Result.goaltime >= 90)
			{

				if (g_Result.selectpush == 0)
				{
					//next?���̃X�e�[�W�֓I��
					SetEffect(80, D3DXVECTOR2(800.0f, 700.0f), D3DXVECTOR2(800.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);

				}

				if (g_Result.selectpush == 1)
				{
					//���[���h�I���ɖ߂�
					SetEffect(76, D3DXVECTOR2(90.0f, 700.0f), D3DXVECTOR2(90.0f, 700.0f), 1,
						D3DXVECTOR2(227.0f, 202.0f), D3DXVECTOR2(227.0f, 202.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 2)
				{
					//�v���C���[�z�u�ɖ߂�
					SetEffect(100, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 109.0f), D3DXVECTOR2(200.0f, 109.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 3)
				{
					//���U���g�ɍs��
					SetEffect(98, D3DXVECTOR2(700.0f, 545.0f), D3DXVECTOR2(700.0f, 545.0f), 1,
						D3DXVECTOR2(725.0f, 85.0f), D3DXVECTOR2(725.0f, 85.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 4)
				{
					//���̃X�e�[�W
					SetEffect(78, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 1,
						D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				//if (g_Result.selectpush == 3)
				//{
				//	//���U���g�ɍs��
				//	SetEffect(98, D3DXVECTOR2(700.0f, 545.0f), D3DXVECTOR2(700.0f, 545.0f), 1,
				//		D3DXVECTOR2(725.0f, 85.0f), D3DXVECTOR2(725.0f, 85.0f), 1,
				//		0.0f, 1.0f, 0, 1, 0, 1,
				//		0.0f, 0.0f, 0);
				//}

				//�}�E�X����
				if (mouse_pos_X > 715.0f && mouse_pos_X < 870.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Result.selectpush = 0;
					mouseuse = true;
				}
				//���[���h�I��		100, 700
				if (mouse_pos_X > 22.0f && mouse_pos_X < 150.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Result.selectpush = 1;
					mouseuse = true;
				}
				//�v���C���[�z�u	600, 700
				if (mouse_pos_X > 520.0f && mouse_pos_X < 675.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Result.selectpush = 2;
					mouseuse = true;
				}
				//���U���g�ɂ���
				if (mouse_pos_X > 550.0f && mouse_pos_X < 840.0f && mouse_pos_Y > 500.0f && mouse_pos_Y < 600.0f)
				{
					g_Result.selectpush = 3;
					mouseuse = true;
				}
				//���̃X�e�[�W
				if (mouse_pos_X > 1170.0f && mouse_pos_X < 1420.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Result.selectpush = 4;
					mouseuse = true;
				}

				if (mouseuse && mouse_Lclick)
				{
					if (g_Result.selectpush == 0)
					{
						// Init�Q�[����BGM�𗬂�����true�ɂ��Ă���
						BGMonceTrue();
						SceneTransition(SCENE_GAME);
					}

					if (g_Result.selectpush == 1)
					{
						SceneTransition(SCENE_STAGE_SELECT);
					}

					if (g_Result.selectpush == 2)
					{
						SceneTransition(SCENE_PLACEMENT);
					}

					if (g_Result.selectpush == 4)
					{
						// ���̃X�e�[�W��
						resultfin = true;
						//GoalFalse();
						NextstageTrue();
						PushNextstage();
						NextNowChoiceStageNum();
						ResetPlacementArray();
						SceneTransition(SCENE_PLACEMENT);
					}
				}

				if (g_Result.selectpush == 3)
				{
					if (mouseuse && mouse_Lclick)
					{
						result_click = true;
						g_Result.goaltime = 0;
						EffectBreak(map_back);
						EffectBreak(clear);
						EffectBreak(next);
						EffectBreak(placement);
						EffectBreak(result);
						EffectBreak(retry);
					}
				}
			}
		}

		g_Result.goaltime++;

		//���U���g��ʂɂ��������
		if (result_click == true)
		{

			if (g_Result.resulttime == 10)
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



			if (g_Result.resulttime == 30)
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

				SetEffect(101, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
					D3DXVECTOR2(1400, 750), D3DXVECTOR2(1400, 750), 1,
					0.0f, 1.0f, 100, 999, 0, 180,
					0.0f, 0.0f, 0);

				// �~�b�V����(����)��\������
				//DrawMissionResult();���ƂȂ����\������Ȃ��������Ə����Ă�̂ɁB�B�B
				SAVEDATA* p_Savedata = GetSavedata();

				// �X�e�[�W�f�[�^����~�b�V�������e�Ȃǂ�ǂݎ��
				STAGEDATA* p_Stagedata = GetStagedata();

				float sizebairitu = 0.7f;		// �X�e�[�W�Z���N�g�̎��̊k�̔{��

				float size_x = 768.0f * sizebairitu;
				float size_y = 128.0f * sizebairitu;

				float interval_y = size_y;

				float base_pos1_x = 1110.0f;
				float base_pos1_y = 265.0f;

				float base_pos2_x = base_pos1_x;
				float base_pos2_y = base_pos1_y;

				// �����̐ݒ�
				float interval_magnification = 0.35f;	// �����\���̊Ԋu�̔{��

				float num_size_x = 60.0f;
				float num_size_y = 60.0f;

				int move_frame = 12;

				for (int i = 0; i < MAX_MISSION; i++)
				{
					// �R���e���c��id��`�ʗp�ɁA�G�t�F�N�g�Őݒ肳��Ă���id�ɕϊ�
					int Content_Texid = ContentsNumToTexid(p_Stagedata->mission_ContentsNum[i]);
					// �Z�b�g�G�t�F�N�g�ŕ����̕`��
					int Content_EffectArray =
						SetEffect(Content_Texid, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
							D3DXVECTOR2(size_x, size_y), D3DXVECTOR2(size_x, size_y), 0,
							0.0f, 1.0f, 100, 999, 0, 1,
							0.0f, 0.0f, 0);

					// �~�b�V�����̃e�N�X�`��ID���琔���̍��W���ǂꂾ���^�񒆂��炸��Ă邩���Ƃ��Ă���(x�̂�)
					float number_gap_x = MissionTexIdToNumXGAP(Content_Texid) * sizebairitu;

					// �����̕`��		�~�b�V�����̔ԍ����Ƃɐ�����`���ꏊ�͌��܂��Ă�Ǝv���̂ŁA�����switch���Ŕ��ʂł���Ɗy
					int Number_EffectArray[2] = { 0,0 };
					int* p_Number_EffectArray = Number_EffectArray;
					SetEffectNumber(p_Stagedata->mission_JudgeNum[i], p_Number_EffectArray, D3DXVECTOR2(base_pos1_x - number_gap_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - number_gap_x, base_pos2_y + interval_y * i), 1,
						D3DXVECTOR2(num_size_x * sizebairitu, num_size_y * sizebairitu), D3DXVECTOR2(num_size_x, num_size_y), 0,
						0.0f, 1.0f, 100, 999, 0, 1,
						0.0f, 0.0f, 0, interval_magnification);
				}






			}

			if (g_Result.resulttime == 30)
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

				// �N���A�^�C���̕\�� p_Gamedata  SetEffectTimeNumber
				int Number_EffectArray[2] = { 0,0 };
				int* p_Number_EffectArray = Number_EffectArray;
				SetEffectTimeNumber(p_Gamedata->game_time, p_Number_EffectArray, D3DXVECTOR2(850.0f, 600.0f), D3DXVECTOR2(800.0f, 540.0f), 0,
					D3DXVECTOR2(48.0f, 48.0f), D3DXVECTOR2(30.0f, 30.0f), 0,
					0.0f, 1.0f, 60, 999, 0, 60,
					0.0f, 0.0f, 0);

				// �ő��^�C���̕\�� p_Gamedata  SetEffectTimeNumber
				SetEffectTimeNumber(p_Savedata[p_Stagedata->stagenum].clear_time, p_Number_EffectArray, D3DXVECTOR2(1112.0f, 600.0f), D3DXVECTOR2(1050.0f, 540.0f), 0,
					D3DXVECTOR2(48.0f, 48.0f), D3DXVECTOR2(30.0f, 30.0f), 0,
					0.0f, 1.0f, 60, 999, 0, 60,
					0.0f, 0.0f, 0);
			}

			if (g_Result.resulttime == 80)
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

			if (g_Result.resulttime == 100)
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

			if (g_Result.resulttime == 120)
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


			if (g_Result.resulttime == 160)
			{


				//next?���̃X�e�[�W�֓I��
				SetEffect(77, D3DXVECTOR2(1080.0f, 700.0f), D3DXVECTOR2(1080.0f, 700.0f), 1,
					D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
					0.0f, 1.0f, 0, 999, 0, 1,
					0.0f, 0.0f, 0);

				//���[���h�I���ɖ߂�
				SetEffect(75, D3DXVECTOR2(400.0f, 700.0f), D3DXVECTOR2(400.0f, 700.0f), 1,
					D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
					0.0f, 1.0f, 0, 999, 0, 1,
					0.0f, 0.0f, 0);

				//���g���C
				SetEffect(79, D3DXVECTOR2(800.0f, 700.0f), D3DXVECTOR2(800.0f, 700.0f), 1,
					D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
					0.0f, 1.0f, 0, 999, 0, 1,
					0.0f, 0.0f, 0);

				//�v���C���[�z�u�ɖ߂�
				SetEffect(99, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
					D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
					0.0f, 1.0f, 0, 999, 0, 1,
					0.0f, 0.0f, 0);
			}
			//��1440
			//�c810

			if (g_Result.resulttime >= 160)
			{
				if (g_Result.selectpush == 0)
				{
					//next?���̃X�e�[�W�֓I��
					SetEffect(78, D3DXVECTOR2(1080.0f, 700.0f), D3DXVECTOR2(1080.0f, 700.0f), 1,
						D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);

				}

				if (g_Result.selectpush == 1)
				{
					//���[���h�I���ɖ߂�
					SetEffect(76, D3DXVECTOR2(393.0f, 702.0f), D3DXVECTOR2(393.0f, 702.0f), 1,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 2)
				{
					//���g���C
					SetEffect(80, D3DXVECTOR2(800.0f, 700.0f), D3DXVECTOR2(800.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 3)
				{
					//�v���C���[�z�u�ɖ߂�
					SetEffect(100, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 109.0f), D3DXVECTOR2(200.0f, 109.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				// �}�E�X�̍��W���g���Ă̓��͏���
				//1 1200 700	300 300
				if (mouse_pos_X > 950.0f && mouse_pos_X < 1200.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
				{
					g_Result.selectpush = 0;
					resultmouseuse = true;
				}
				//2 100 700		200 200
				if (mouse_pos_X > 340.0f && mouse_pos_X < 460.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
				{
					g_Result.selectpush = 1;
					resultmouseuse = true;
				}
				if (mouse_pos_X > 770.0f && mouse_pos_X < 930.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
				{
					g_Result.selectpush = 2;
					resultmouseuse = true;
				}
				if (mouse_pos_X > 480.0f && mouse_pos_X < 690.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
				{
					g_Result.selectpush = 3;
					resultmouseuse = true;
				}

				if (resultmouseuse && mouse_Lclick)
				{
					if (g_Result.selectpush == 0)
					{
						// ���̃X�e�[�W��
						resultfin = true;
						//GoalFalse();
						NextstageTrue();
						PushNextstage();
						NextNowChoiceStageNum();
						ResetPlacementArray();
						SceneTransition(SCENE_PLACEMENT);
					}

					if (g_Result.selectpush == 1)
					{
						SceneTransition(SCENE_STAGE_SELECT);
					}

					if (g_Result.selectpush == 2)
					{
						// Init�Q�[����BGM�𗬂�����true�ɂ��Ă���
						BGMonceTrue();
						SceneTransition(SCENE_GAME);
					}
					if (g_Result.selectpush == 3)
					{
						SceneTransition(SCENE_PLACEMENT);
					}
				}

				//// �}�E�X���������ʒu�ɂ����āA���N���b�N������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
				//if (resultmouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
				//{
				//	//SetVolume(g_BGMNo, 0.1f);

				//	//STAGE_SELECT�ֈڍs����
				//	SceneTransition(SCENE_STAGE_SELECT);
				//}


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
			g_Result.resulttime++;
		}
	}

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

bool checkresult()
{
	return resultfin;
}