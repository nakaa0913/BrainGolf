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
static STAGESELECT g_StageSelect;

static int	g_TextureNo = 0;	// �e�N�X�`�����
static int	g_BGMNo = 0;		// BGM���ʎq

//static int world_1_background;
//static int world_2_background;
//static int world_3_background;
//static int world_4_background;
//static int world_5_background;
//
//static int world_1_stagechoice;
//static int world_2_stagechoice;
//static int world_3_stagechoice;
//static int world_4_stagechoice;
//static int world_5_stagechoice;
//
//static int world_1_mission;

int NowWorld = 0;				   //���I�����Ă���
int tex_NowWorld_background = -1;  //�w�i
int tex_NowWorld_stagechoice = -1; //�X�e�[�W�I���̎l�p�����
int tex_NowWorld_mission = -1;     //�~�b�V����
/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitStageSelect(void)
{
	//�e�N�X�`������
	/*g_TextureNo = LoadTexture("data/TEXTURE/select/stage_select.png");*/


	//�e�N�X�`���̖��O
	//world_1_background = LoadTexture("data/TEXTURE/select/stage_select.png");
	//world_2_background = LoadTexture("data/TEXTURE/select/stage_select.png");
	//world_3_background = LoadTexture("data/TEXTURE/select/stage_select.png");
	//world_4_background = LoadTexture("data/TEXTURE/select/stage_select.png");
	//world_5_background = LoadTexture("data/TEXTURE/select/stage_select.png");

	//world_1_stagechoice = LoadTexture("data/TEXTURE/select/1.png");



		g_StageSelect.select_x = 0;
		g_StageSelect.select_y = 0;
	


	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)�����[�v�w�肷��Ɩ������[�v
	PlaySound(g_BGMNo, -1);

	g_StageSelect.selecttime = 0;

	NowWorld = GetNowWorld();

	
	//
	if (NowWorld == 1)
	{
		tex_NowWorld_background = 15;
		tex_NowWorld_stagechoice = 20;
		tex_NowWorld_mission = 25;
	}

	if (NowWorld == 2)
	{
		tex_NowWorld_background = 16;
		tex_NowWorld_stagechoice = 21;
		tex_NowWorld_mission = 26;
	}

	if (NowWorld == 3)
	{
		tex_NowWorld_background = 17;
		tex_NowWorld_stagechoice = 22;
		tex_NowWorld_mission = 27;
	}

	if (NowWorld == 4)
	{
		tex_NowWorld_background = 18;
		tex_NowWorld_stagechoice = 23;
		tex_NowWorld_mission = 28;
	}

	if (NowWorld == 5)
	{
		tex_NowWorld_background = 19;
		tex_NowWorld_stagechoice = 24;
		tex_NowWorld_mission = 29;
	}

	
	// ���Ԃ񂱂ꂾ��I�I�I�I�I�I
	
	//�w�i�\��
	SetEffect(tex_NowWorld_background, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
		D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
		0.0f, 1.0f, 100, 999, 0, 180,
		0.0f, 0.0f, 0);

	//�~�b�V����
	SetEffect(tex_NowWorld_mission, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
		D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
		0.0f, 1.0f, 100, 999, 0, 180,
		0.0f, 0.0f, 0);

	return ;
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitStageSelect()
{
	UnloadTexture("data/TEXTURE/select/stage_select.png");

}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateStageSelect(void)
{
	//�X�y�[�X�L�[��������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SetVolume(g_BGMNo, 0.1f);

		//RESULT�ֈڍs����
		SceneTransition(SCENE_GAME);
	}


	/////////////

	// �X�e�[�W�I���̎��̌��_�ƂȂ�ꏊ
	float	stage_origin_x = 240.0f;			    // x�̌��_(0,0��I�����Ă���Ƃ�)
	float	stage_origin_y = 200.0f;			    // y�̌��_(0,0��I�����Ă���Ƃ�)

	// �X�e�[�W�I���̎�1���ꂽ�炱�ꂾ����������Ă��
	float distance_x = 240.0f;
	float distance_y = 240.0f;

	//�X�e�[�W�I�����o�[�W����
	for (int x = 0; x < SELECT_MAX_X; x++)
	{
		for (int y = 0; y < SELECT_MAX_Y; y++)
		{
			// ���݂̍��W�����߂�
			float now_x = stage_origin_x + distance_x * x;
			float now_y = stage_origin_y + distance_y * y;

			// �I������ĂȂ��Ƃ��̕\�����o��(�X�e�[�W���ׂ�)
			SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);

			// �����B�I�����Ă���Ƃ��������đ傫���T�C�Y�ŕ\���B
			if (g_StageSelect.select_x == x)
			{
				if (g_StageSelect.select_y == y)
				{
					SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
						1.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}
			}
		}
	}


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

		//
		//// ���[���h�I���̎�
		//SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
		//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		//	0.0f, 1.0f, 0, 1, 0, 0,
		//	0.0f, 0.0f, 0);

		//SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
		//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		//	0.0f, 1.0f, 0, 1, 0, 0,
		//	0.0f, 0.0f, 0);

		//SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
		//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		//	0.0f, 1.0f, 0, 1, 0, 0,
		//	0.0f, 0.0f, 0);

		//SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
		//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		//	0.0f, 1.0f, 0, 1, 0, 0,
		//	0.0f, 0.0f, 0);

		//SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
		//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		//	0.0f, 1.0f, 0, 1, 0, 0,
		//	0.0f, 0.0f, 0);

		//�Z���N�g��ԏ�

		/*if (g_StageSelect.select_y == 0)
		{
			if (g_StageSelect.select_x == 0)
			{
					SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
						1.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
			}

			if (g_StageSelect.select_x == 1)
			{
				SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}

			if (g_StageSelect.select_x == 2)
			{
				SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}

			if (g_StageSelect.select_x == 3)
			{
				SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}

			if (g_StageSelect.select_x == 4)
			{
				SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}
		}*/

			//�Z���N�g��i��
			/*if (g_StageSelect.select_y == 1)
			{
				if (g_StageSelect.select_x == 0)
				{
					SetEffect(6, D3DXVECTOR2(60.0f, 300.0f), D3DXVECTOR2(60.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_StageSelect.select_x == 1)
				{
					SetEffect(7, D3DXVECTOR2(170.0f, 300.0f), D3DXVECTOR2(170.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_StageSelect.select_x == 2)
				{
					SetEffect(6, D3DXVECTOR2(280.0f, 300.0f), D3DXVECTOR2(280.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_StageSelect.select_x == 3)
				{
					SetEffect(6, D3DXVECTOR2(390.0f, 300.0f), D3DXVECTOR2(390.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_StageSelect.select_x == 4)
				{
					SetEffect(6, D3DXVECTOR2(500.0f, 300.0f), D3DXVECTOR2(500.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}
			}*/

			



			if (g_StageSelect.selectcooltime <= 0)
			{

				if (g_StageSelect.select_y >= 2)
				{
					g_StageSelect.select_y = 0;
				}

				if (g_StageSelect.select_y < 0)
				{
					g_StageSelect.select_y = 1;
				}
			

				if (GetKeyboardPress(DIK_UP))
				{
					g_StageSelect.select_y--;
					g_StageSelect.selectcooltime = 10;

				}

				

				if (GetKeyboardPress(DIK_RIGHT))
				{
					g_StageSelect.select_x++;
					g_StageSelect.selectcooltime = TIME;
				}
				if (g_StageSelect.select_x >= 5)
				{
					g_StageSelect.select_x = 0;
				}

				if (GetKeyboardPress(DIK_LEFT))
				{
					g_StageSelect.select_x--;
					g_StageSelect.selectcooltime = TIME;

				}
				if (g_StageSelect.select_x < 0)
				{
					g_StageSelect.select_x = 4;
				}


				if (g_StageSelect.select_x == 0)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_StageSelect.select_y++;
						g_StageSelect.selectcooltime = 10;
					}

					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}


				if (g_StageSelect.select_x == 1)
				{

					if (GetKeyboardPress(DIK_DOWN))
					{
						g_StageSelect.select_y++;
						g_StageSelect.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				if (g_StageSelect.select_x == 2)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_StageSelect.select_y++;
						g_StageSelect.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				if (g_StageSelect.select_x == 3)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_StageSelect.select_y++;
						g_StageSelect.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				if (g_StageSelect.select_x == 4)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_StageSelect.select_y++;
						g_StageSelect.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				

			}



			if (g_StageSelect.selectcooltime >= 0)
				g_StageSelect.selectcooltime--;

	


		


			g_StageSelect.selecttime++;
	
}

STAGESELECT* GetStageSelect()
{
	return &g_StageSelect;
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawStageSelect(void)
{
	


	//// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	//DrawSpriteColorRotate(tex_NowWorld_background, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR (1.0f, 1.0f, 1.0f, 1.0f), 1.0f);

	/*static int world_1_background;
	static int world_2_stagechoice;
	static int world_3_mission;
	static int world_4_selectstar;*/

}

