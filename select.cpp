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
#include"select.h"
#include "Texture.h"
#include "sprite.h"
#include "effect.h"
#include "stagedata.h"
#include "FileDataManagement.h"
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
static SELECT g_Select;

static int	g_TextureNo = 0;	// �e�N�X�`�����
static int	g_BGMNo = 0;		// BGM���ʎq

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitSelect(void)
{
	//�e�N�X�`������
	g_TextureNo = LoadTexture("data/TEXTURE/select.png");


	for (int i = 0; i < SELECT_MAX; i++)
	{
		g_Select.selectpush = 0;
		g_Select.selectvertical = 0;
	}


	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)�����[�v�w�肷��Ɩ������[�v
	PlaySound(g_BGMNo, -1);

	g_Select.selecttime = 0;

	return ;
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitSelect()
{
	
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateSelect(void)
{
	//�X�y�[�X�L�[��������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SetVolume(g_BGMNo, 0.1f);

		//RESULT�ֈڍs����
		SceneTransition(SCENE_GAME);
	}


	/////////////

	
		//�~�b�V����
		/*SetEffect(8, D3DXVECTOR2(280.0f, 700.0f), D3DXVECTOR2(280.0f, 700.0f), 0,
			D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR2(500.0f, 200.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);*/

		//��
		SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
			D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		//���b�N
		/*SetEffect(10, D3DXVECTOR2(280.0f, 450.0f), D3DXVECTOR2(280.0f, 450.0f), 0,
			D3DXVECTOR2(450.0f, 100.0f), D3DXVECTOR2(450.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);*/

		
		//1�i��
		SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		//��i��
		/*SetEffect(6, D3DXVECTOR2(60.0f, 300.0f), D3DXVECTOR2(60.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(7, D3DXVECTOR2(170.0f, 300.0f), D3DXVECTOR2(170.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(280.0f, 300.0f), D3DXVECTOR2(280.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(390.0f, 300.0f), D3DXVECTOR2(390.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(500.0f, 300.0f), D3DXVECTOR2(500.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		//�O�i��
		SetEffect(6, D3DXVECTOR2(60.0f, 400.0f), D3DXVECTOR2(60.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(7, D3DXVECTOR2(170.0f, 400.0f), D3DXVECTOR2(170.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(280.0f, 400.0f), D3DXVECTOR2(280.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(390.0f, 400.0f), D3DXVECTOR2(390.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(500.0f, 400.0f), D3DXVECTOR2(500.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		//�l�i��
		SetEffect(6, D3DXVECTOR2(60.0f, 500.0f), D3DXVECTOR2(60.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(7, D3DXVECTOR2(170.0f, 500.0f), D3DXVECTOR2(170.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(280.0f, 500.0f), D3DXVECTOR2(280.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(390.0f, 500.0f), D3DXVECTOR2(390.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);*/

		//�Z���N�g��ԏ�

		if (g_Select.selectvertical == 0)
		{
			if (g_Select.selectpush == 0)
			{
					SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
						1.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
			}

			if (g_Select.selectpush == 1)
			{
				SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}

			if (g_Select.selectpush == 2)
			{
				SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}

			if (g_Select.selectpush == 3)
			{
				SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}

			if (g_Select.selectpush == 4)
			{
				SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}
		}

			//�Z���N�g��i��
			/*if (g_Select.selectvertical == 1)
			{
				if (g_Select.selectpush == 0)
				{
					SetEffect(6, D3DXVECTOR2(60.0f, 300.0f), D3DXVECTOR2(60.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_Select.selectpush == 1)
				{
					SetEffect(7, D3DXVECTOR2(170.0f, 300.0f), D3DXVECTOR2(170.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_Select.selectpush == 2)
				{
					SetEffect(6, D3DXVECTOR2(280.0f, 300.0f), D3DXVECTOR2(280.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_Select.selectpush == 3)
				{
					SetEffect(6, D3DXVECTOR2(390.0f, 300.0f), D3DXVECTOR2(390.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_Select.selectpush == 4)
				{
					SetEffect(6, D3DXVECTOR2(500.0f, 300.0f), D3DXVECTOR2(500.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}
			}*/

			



			if (g_Select.selectcooltime <= 0)
			{

				if (g_Select.selectvertical >= 2)
				{
					g_Select.selectvertical = 0;
				}

				if (g_Select.selectvertical < 0)
				{
					g_Select.selectvertical = 1;
				}
			

				if (GetKeyboardPress(DIK_UP))
				{
					g_Select.selectvertical--;
					g_Select.selectcooltime = 10;

				}

				

				if (GetKeyboardPress(DIK_RIGHT))
				{
					g_Select.selectpush++;
					g_Select.selectcooltime = TIME;
				}
				if (g_Select.selectpush >= 5)
				{
					g_Select.selectpush = 0;
				}

				if (GetKeyboardPress(DIK_LEFT))
				{
					g_Select.selectpush--;
					g_Select.selectcooltime = TIME;

				}
				if (g_Select.selectpush < 0)
				{
					g_Select.selectpush = 4;
				}


				if (g_Select.selectpush == 0)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = 10;
					}

					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}


				if (g_Select.selectpush == 1)
				{

					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				if (g_Select.selectpush == 2)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				if (g_Select.selectpush == 3)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				if (g_Select.selectpush == 4)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				

			}



			if (g_Select.selectcooltime >= 0)
				g_Select.selectcooltime--;

	


		


			g_Select.selecttime++;
	
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawSelect(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}

