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
static WORLDSELECT g_WorldSelect;

static int	g_TextureNo = 0;	// �e�N�X�`�����
static int	g_BGMNo = 0;		// BGM���ʎq

int now_world_select_EffectArray = -1;
bool world_select_once = false;
int world_select_once_time = 0;

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitWorldSelect(void)
{
	//�e�N�X�`������
	g_TextureNo = LoadTexture("data/TEXTURE/select/world_select.png");



	g_WorldSelect.select_x = 0;
	g_WorldSelect.select_y = 0;



	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)�����[�v�w�肷��Ɩ������[�v
	PlaySound(g_BGMNo, -1);

	g_WorldSelect.selecttime = 0;

	world_select_once = false;
	now_world_select_EffectArray = -1;
	world_select_once_time = 0;

	// ���[���h�Z���N�g��ʂ̍ŏ��ɕ`�ʂ����҂���
	StartWorldSelectScreen();

	return;
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitWorldSelect()
{
	UnloadTexture("data/TEXTURE/select/world_select.png");

}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateWorldSelect(void)
{
	//�X�y�[�X�L�[��������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
	if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SetVolume(g_BGMNo, 0.1f);

		//STAGE_SELECT�ֈڍs����
		SceneTransition(SCENE_STAGE_SELECT);
	}




	//�~�b�V����
	/*SetEffect(8, D3DXVECTOR2(280.0f, 700.0f), D3DXVECTOR2(280.0f, 700.0f), 0,
		D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR2(500.0f, 200.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);*/

	//���b�N
	/*SetEffect(10, D3DXVECTOR2(280.0f, 450.0f), D3DXVECTOR2(280.0f, 450.0f), 0,
		D3DXVECTOR2(450.0f, 100.0f), D3DXVECTOR2(450.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);*/


	// �G���^�[�L�[�������ꂽ���̏���
	/*if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_STAGE_SELECT);
	}*/


	// �L�[���͂ɂ�鑀��
	if (g_WorldSelect.selectcooltime <= 0)
	{
		bool use_key = false;		// �L�[���͂��ꂽ���ǂ���
		// �E
		if (Keyboard_IsKeyDown(KK_RIGHT))
		{
			g_WorldSelect.select_x++;
			use_key = true;
		}
		// ��
		if (Keyboard_IsKeyDown(KK_LEFT))
		{
			g_WorldSelect.select_x--;
			use_key = true;
		}

		// �I�����Ă���Ƃ��낪���E�𒴂��Ȃ��悤�ɂ��鏈��
		if (g_WorldSelect.select_x >= WORLD_SELECT_MAX_X)
			g_WorldSelect.select_x = 0;
		if (g_WorldSelect.select_x < 0)
			g_WorldSelect.select_x = WORLD_SELECT_MAX_X - 1;

		if (use_key == true)
		{
			// �������ƑO��g���Ă������̂̏���
			g_WorldSelect.selectcooltime = WORDL_SELECT_COOL;
			EffectBreak(now_world_select_EffectArray);
			world_select_once = false;
			world_select_once_time = 0;
		}
	}





	//�@���[���h�I���̑I�����Ă���Ƃ���̏���
	if (world_select_once == false)
	{

		world_select_once = true;

		if (g_WorldSelect.select_y == 0)
		{

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 0)
			{
				now_world_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						1.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 1)
			{
				now_world_select_EffectArray =
					SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 2)
			{
				now_world_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 3)
			{
				now_world_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 4)
			{
				now_world_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}
		}
	}

	if (world_select_once == true)
	{
		if (world_select_once_time % 60 == 0)
		{
			ChangeEffectCount(now_world_select_EffectArray, 0);
		}


		// �I������Ă���̎��Ԃ������Ă���
		world_select_once_time++;
	}


	// �N�[���^�C���̃J�E���g�����炷����
	if (g_WorldSelect.selectcooltime > 0)
		g_WorldSelect.selectcooltime--;

	g_WorldSelect.selecttime++;

}

WORLDSELECT* GetWorldSelect()
{
	return &g_WorldSelect;
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawWorldSelect(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}


int GetNowWorld()
{
	return g_WorldSelect.select_x + 1;
}


void StartWorldSelectScreen()
{
	// ���݊l�����Ă��鐯�̐��̕\��
	SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// �I�΂�ĂȂ��Ƃ��̕\��
	SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	return;
}
