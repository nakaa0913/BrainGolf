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

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPause(void)
{
	//�e�N�X�`���ǂݍ���


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



	// �����|�[�Y��ԂȂ�
	if (pause == true)
	{

		// �Ƃ肠�����͂����肾��
		SetEffect(62, D3DXVECTOR2(400, 400), D3DXVECTOR2(400, 400), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);



	}



	//�@P�L�[��������ă|�[�Y��Ԃ�؂�ւ��鏈��
	if (pause_cool <= 0)
	{
		if (Keyboard_IsKeyDown(KK_P))
		{
			pause = !pause;

			pause_cool = PUSHKEY_COOLTIME;

		}
	}


	////�L�[����
	//if (g_Pause.selecttime <= 0)
	//{
	//	//�|�[�Y�{�^���̕\��
	//	if (Keyboard_IsKeyDown(KK_P))
	//	{
	//		//��1440
	//		//�c810
	//		g_Pause.selectpush++;

	//		//PauseTrue();
	//	}


	//	//�|�[�Y�{�^���̕\��
	//	if (g_Pause.selectpush == 1)
	//	{
	//		//�Q�[���N���A
	//		SetEffect(62, D3DXVECTOR2(50, 50), D3DXVECTOR2(50, 50), 0,
	//			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
	//			0.0f, 1.0f, 30, 999, 60, 30,
	//			0.0f, 0.0f, 0);
	//	}


	//	if (g_Pause.selectpush >= 2)
	//	{
	//		g_Pause.selectpush = 1;
	//	}


	//	if (g_Pause.selectpush < 0)
	//	{
	//		g_Pause.selectpush = 1;
	//	}

	//}

	//// �}�E�X�̍��W���g���Ă̓��͏���
	////1 1200 700	300 300
	//if (mouse_pos_X > 1050.0f && mouse_pos_X < 1350.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
	//{
	//	g_Pause.selectpush = 0;
	//	pausemouseuse = true;
	//}
	////2 100 700		200 200
	//else if (mouse_pos_X > 60.0f && mouse_pos_X < 140.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
	//{
	//	g_Pause.selectpush = 1;
	//	pausemouseuse = true;
	//}

	//// �}�E�X���������ʒu�ɂ����āA���N���b�N������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
	//if (pausemouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
	//{
	//	//SetVolume(g_BGMNo, 0.1f);

	//	//STAGE_SELECT�ֈڍs����
	//	SceneTransition(SCENE_STAGE_SELECT);
	//}


	//// �����O�̃t���[������ω����������ꍇ�̂݃G�t�F�N�g�Ȃǂ�ω�������
	//bool Change = false;
	//if (OldPauseSelect != g_Pause.selectpush)
	//	Change = true;

	//// �ύX���������ꍇ�A�������ƐV�������̂̃Z�b�g
	//if (Change == true)
	//{
	//	// �������ƑO��g���Ă������̂̏���
	//	g_Pause.selecttime = 30;
	//	//EffectBreak(now_pause_select_EffectArray);		// �O�̕`�ʂ�����
	//	pause_select_once = false;						// 1����`�ʂ��ĂȂ���ɂ���
	//	pause_select_once_time = 0;						// �`�ʂ��Ă���̎��Ԃ̃��Z�b�g
	//}

	//
	//if (g_Pause.selecttime >= 0)
	//	g_Pause.selecttime--;

	if (pause_cool > 0)
		pause_cool--;



	//// ���t���[���J�E���g�𑝂₷
	//g_Pause.goaltime++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPause(void)
{

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