/*==============================================================================

   �Q�[������ [game.cpp]
														 Author :
														 Date   :a
--------------------------------------------------------------------------------

==============================================================================*/

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
#include "Goal.h"
#include"stageselect.h"
#include "Texture.h"
#include "sprite.h"
#include "effect.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "worldselect.h"
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

int now_select_EffectArray = -1;
bool select_once = false;
int select_once_time = 0;

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
	select_once = false;
	now_select_EffectArray = -1;
	select_once_time = 0;

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
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SetVolume(g_BGMNo, 0.1f);

		//RESULT�ֈڍs����
		SceneTransition(SCENE_STAGE_SELECT);
	}


	/////////////

	//// �X�e�[�W�I���̎��̌��_�ƂȂ�ꏊ
	//float	stage_origin_x = 240.0f;			    // x�̌��_(0,0��I�����Ă���Ƃ�)
	//float	stage_origin_y = 200.0f;			    // y�̌��_(0,0��I�����Ă���Ƃ�)

	//// �X�e�[�W�I���̎�1���ꂽ�炱�ꂾ����������Ă��
	//float distance_x = 240.0f;
	//float distance_y = 240.0f;

	////�X�e�[�W�I�����o�[�W����
	//for (int x = 0; x < SELECT_MAX_X; x++)
	//{
	//	for (int y = 0; y < SELECT_MAX_Y; y++)
	//	{
	//		// ���݂̍��W�����߂�
	//		float now_x = stage_origin_x + distance_x * x;
	//		float now_y = stage_origin_y + distance_y * y;

	//		// �I������ĂȂ��Ƃ��̕\�����o��(�X�e�[�W���ׂ�)
	//		SetEffect(6, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
	//			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
	//			0.0f, 1.0f, 0, 1, 0, 0,
	//			0.0f, 0.0f, 0);

	//		// �����B�I�����Ă���Ƃ��������đ傫���T�C�Y�ŕ\���B
	//		if (g_WorldSelect.select_x == x)
	//		{
	//			if (g_WorldSelect.select_y == y)
	//			{
	//				SetEffect(6, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
	//					D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
	//					1.0f, 1.0f, 0, 1, 0, 0,
	//					0.0f, 0.0f, 0);
	//			}
	//		}
	//	}
	//}




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

	//�Z���N�g��ԏ�
	if (select_once == false)
	{

		select_once = true;

		if (g_WorldSelect.select_y == 0)
		{

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 0)
			{
				now_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						1.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 1)
			{
				now_select_EffectArray =
					SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 2)
			{
				now_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 3)
			{
				now_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// �I������Ă���Ƃ��̕\��
			if (g_WorldSelect.select_x == 4)
			{
				now_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}
		}
	}

	if (select_once == true)
	{
		if (select_once_time % 60 == 0)
		{
			ChangeEffectCount(now_select_EffectArray, 0);
		}


		// �I������Ă���̎��Ԃ������Ă���
		select_once_time++;
	}


	// �L�[��������āA�N�[���^�C���ȉ��Ȃ�
	// �I�����Ă���Ƃ����ς��āA
	// �g���Ă����G�t�F�N�g������
	if (g_WorldSelect.selectcooltime <= 0)
	{
		if (GetKeyboardPress(DIK_RIGHT))
		{
			g_WorldSelect.select_x++;
			g_WorldSelect.selectcooltime = TIME;

			EffectBreak(now_select_EffectArray);
			select_once = false;
			select_once_time = 0;
		}


		if (GetKeyboardPress(DIK_LEFT))
		{
			g_WorldSelect.select_x--;
			g_WorldSelect.selectcooltime = TIME;
			EffectBreak(now_select_EffectArray);
			select_once = false;
			select_once_time = 0;
		}

		// �I�����Ă���Ƃ��낪���E�𒴂��Ȃ��悤�ɂ��鏈��
		if (g_WorldSelect.select_x >= 5)
		{
			g_WorldSelect.select_x = 0;
		}
		if (g_WorldSelect.select_x < 0)
		{
			g_WorldSelect.select_x = 4;
		}

		// �I������Ă���Ƃ��ɃG���^�[�L�[�������ꂽ�ꍇ�̏���
		if (g_WorldSelect.select_x == 0)
		{
			/*if (GetKeyboardPress(DIK_DOWN))
			{
				g_WorldSelect.select_y++;
				g_WorldSelect.selectcooltime = 10;
			}*/

			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}
		if (g_WorldSelect.select_x == 1)
		{

			//if (GetKeyboardPress(DIK_DOWN))
			//{
			//	g_WorldSelect.select_y++;
			//	g_WorldSelect.selectcooltime = TIME;
			//}
			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}
		if (g_WorldSelect.select_x == 2)
		{
			//if (GetKeyboardPress(DIK_DOWN))
			//{
			//	g_WorldSelect.select_y++;
			//	g_WorldSelect.selectcooltime = TIME;
			//}
			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}
		if (g_WorldSelect.select_x == 3)
		{
			//if (GetKeyboardPress(DIK_DOWN))
			//{
			//	g_WorldSelect.select_y++;
			//	g_WorldSelect.selectcooltime = TIME;
			//}
			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}
		if (g_WorldSelect.select_x == 4)
		{
			//if (GetKeyboardPress(DIK_DOWN))
			//{
			//	g_WorldSelect.select_y++;
			//	g_WorldSelect.selectcooltime = TIME;
			//}
			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}



	}



	// �N�[���^�C���̃J�E���g�����炷����
	if (g_WorldSelect.selectcooltime >= 0)
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
