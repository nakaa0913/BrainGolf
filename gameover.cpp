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

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGameover(void)
{
	//�e�N�X�`���ǂݍ���


	g_Gameover.gameovertime = 0;
	g_Gameover.selectpush = 0;


	//������
	g_GameoverSENo = LoadSound("data/SE/Phrase04-1.wav");
	onceSE = 0;

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
	//�}�E�X�̍��W���擾
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouseuse = false;

	// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
	//int OldnowchoiceX = nowchoice.x;
	//int OldnowchoiceY = nowchoice.y;


	if (g_Gameover.gameovertime == 1)
	{
		//�È�4 ������Ȃ�48
		SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 100, 999, 0, 180,
			0.0f, 0.0f, 0);
		//��1440
		//�c810
		//�Q�[���I�[�o�[
		SetEffect(55, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT / 2), 1,
			0.0f, 1.0f, 10, 70, 10, 90,
			0.0f, 0.0f, 0);

	}


	if (g_Gameover.gameovertime >= 90)
	{
		////���邭����Â�����Ȃ�4
		//SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
		//	D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
		//	0.0f, 0.5f, 0, 1, 0, 1,
		//	0.0f, 0.0f, 0);

		//�X�e�[�W��
		SetEffect(57, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//���X�^�[�g
		SetEffect(56, D3DXVECTOR2(1200.0f, 700.0f), D3DXVECTOR2(1200.0f, 700.0f), 1,
			D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);
		//�v���C���[�z�u�ɖ߂�
		SetEffect(59, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
			D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//�}�b�v�H�ɖ߂�
		SetEffect(58, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
			D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//��1440
		//�c810

		if (g_Gameover.selectpush == 0)
		{
			//next?���̃X�e�[�W�֓I��
			SetEffect(56, D3DXVECTOR2(1200.0f, 700.0f), D3DXVECTOR2(1200.0f, 700.0f), 1,
				D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
			

		}

		if (g_Gameover.selectpush == 1)
		{
			//���[���h�I���ɖ߂�
			SetEffect(58, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
				D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}

		if (g_Gameover.selectpush == 2)
		{
			//�v���C���[�z�u�ɖ߂�
			SetEffect(59, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
				D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 1,
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


		if (g_Gameover.selecttime <= 0)
		{

			if (Keyboard_IsKeyDown(KK_RIGHT))
			{
				g_Gameover.selectpush++;
				g_Gameover.selecttime = 30;

			}
			if (g_Gameover.selectpush >= 3)
			{
				g_Gameover.selectpush = 0;
			}

			if (Keyboard_IsKeyDown(KK_LEFT))
			{
				g_Gameover.selectpush--;
				g_Gameover.selecttime = 30;

			}
			if (g_Gameover.selectpush < 0)
			{
				g_Gameover.selectpush = 2;
			}

			/*if (g_Gameover.gameovertime >= 9060)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_WORLD_SELECT);

				}
			}*/

			if (g_Gameover.selectpush == 0)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_GAME);

				}
			}

			if (g_Gameover.selectpush == 1)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_STAGE_SELECT);

				}
			}

			if (g_Gameover.selectpush == 2)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_PLACEMENT);

				}
			}

		}

		//�}�E�X����
		//next				1200, 700
		if (mouse_pos_X > 1100.0f && mouse_pos_X < 1300.0f && mouse_pos_Y > 670.0f && mouse_pos_Y < 710.0f)
		{
			g_Gameover.selectpush = 0;
			mouseuse = true;
		}
		//���[���h�I��		100, 700
		if (mouse_pos_X > 70.0f && mouse_pos_X < 130.0f && mouse_pos_Y > 670.0f && mouse_pos_Y < 710.0f)
		{
			g_Gameover.selectpush = 1;
			mouseuse = true;
		}
		//�v���C���[�z�u	600, 700
		if (mouse_pos_X > 500.0f && mouse_pos_X < 700.0f && mouse_pos_Y > 670.0f && mouse_pos_Y < 710.0f)
		{
			g_Gameover.selectpush = 2;
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

		if (g_Gameover.selecttime >= 0)
			g_Gameover.selecttime--;

	}

	// ���t���[���J�E���g�𑝂₷
	g_Gameover.gameovertime++;
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