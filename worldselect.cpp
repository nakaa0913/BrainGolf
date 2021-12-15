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
#include "mouse.h"
#include "savedata.h"
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

bool WorldDecision = false;				// �G���^�[�����N���b�N�Ń��[���h���m�肳�����瑼�̂Ƃ��Ɉړ��ł��Ȃ�����
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
	WorldDecision = false;

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
	// �m�肳��ĂȂ��ꍇ�̂ݓ�������
	if (WorldDecision == false)
	{

		//�}�E�X�̍��W���擾
		float mouse_pos_X = GetMousePosX();
		float mouse_pos_Y = GetMousePosY();
		bool mouse_Lclick = GetMouseLClick();
		bool mouse_Rclick = GetMouseRClick();
		bool mouseuse = false;

		// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
		int OldWorldSelectX = g_WorldSelect.select_x;
		int OldWorldSelectY = g_WorldSelect.select_y;

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
			//-2�ȊO�͍��E�Ɉړ��ł���
			if (g_WorldSelect.select_x != -2)
			{
				// �E
				if (Keyboard_IsKeyDown(KK_RIGHT))
					g_WorldSelect.select_x++;
				// ��
				if (Keyboard_IsKeyDown(KK_LEFT))
					g_WorldSelect.select_x--;
			}
			// �I�����Ă���Ƃ��낪���E�𒴂��Ȃ��悤�ɂ��鏈��
			if (g_WorldSelect.select_x >= WORLD_SELECT_MAX_X)
				g_WorldSelect.select_x = 0;

			//x��-1�Ȃ�4�ɂ���i������E�j
			if (g_WorldSelect.select_x < 0 && g_WorldSelect.select_x >= -1)
			{
				g_WorldSelect.select_x = WORLD_SELECT_MAX_X - 1;
			}

			//�^�C�g���ɖ߂鏈��
			if(g_WorldSelect.select_x == 0)
			{
				if (Keyboard_IsKeyDown(KK_DOWN))
					g_WorldSelect.select_x = -2 ;
			}
			if (g_WorldSelect.select_x == -2)
			{
				if (Keyboard_IsKeyDown(KK_UP))
					g_WorldSelect.select_x = 0;

				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SetVolume(g_BGMNo, 0.1f);
					WorldDecision = true;

					//STAGE_SELECT�ֈڍs����
					SceneTransition(SCENE_TITLE);
				}

				//if(mouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
				//{
				//	SetVolume(g_BGMNo, 0.1f);
				//	WorldDecision = true;

				//	//STAGE_SELECT�ֈڍs����
				//	SceneTransition(SCENE_TITLE);
				//}
			}

		}

		// �}�E�X�̍��W���g���Ă̓��͏���
		//1 240 200
		if (mouse_pos_X > 165.0f && mouse_pos_X < 315.0f && mouse_pos_Y > 125.0f && mouse_pos_Y < 275.0f)
		{
			g_WorldSelect.select_x = 0;
			mouseuse = true;
		}
		//2 480 500
		else if (mouse_pos_X > 405.0f && mouse_pos_X < 555.0f && mouse_pos_Y > 425.0f && mouse_pos_Y < 575.0f)
		{
			g_WorldSelect.select_x = 1;
			mouseuse = true;
		}
		//3 720 250
		else if (mouse_pos_X > 645.0f && mouse_pos_X < 795.0f && mouse_pos_Y > 175.0f && mouse_pos_Y < 325.0f)
		{
			g_WorldSelect.select_x = 2;
			mouseuse = true;
		}
		//4 960 550
		else if (mouse_pos_X > 885.0f && mouse_pos_X < 1035.0f && mouse_pos_Y > 475.0f && mouse_pos_Y < 625.0f)
		{
			g_WorldSelect.select_x = 3;
			mouseuse = true;
		}
		//5 1200 400
		else if (mouse_pos_X > 1125.0f && mouse_pos_X < 1275.0f && mouse_pos_Y > 325.0f && mouse_pos_Y < 475.0f)
		{
			g_WorldSelect.select_x = 4;
			mouseuse = true;
		}
		//�^�C�g�� 240 700
		else if (mouse_pos_X > 165.0f && mouse_pos_X < 315.0f && mouse_pos_Y > 625.0f && mouse_pos_Y < 775.0f)
		{
			g_WorldSelect.select_x = -2;
			mouseuse = true;
		}









		// �����O�̃t���[������ω����������ꍇ�̂݃G�t�F�N�g�Ȃǂ�ω�������
		bool Change = false;
		if (OldWorldSelectX != g_WorldSelect.select_x ||
			OldWorldSelectY != g_WorldSelect.select_y)
			Change = true;


		// �ύX���������ꍇ�A�������ƐV�������̂̃Z�b�g
		if (Change == true)
		{
			// �������ƑO��g���Ă������̂̏���
			g_WorldSelect.selectcooltime = WORDL_SELECT_COOL;
			EffectBreak(now_world_select_EffectArray);		// �O�̕`�ʂ�����
			world_select_once = false;						// 1����`�ʂ��ĂȂ���ɂ���
			world_select_once_time = 0;						// �`�ʂ��Ă���̎��Ԃ̃��Z�b�g
		}






	//	// ����SCENE_STAGE_SELECT�֍s������

	//�X�y�[�X�L�[��������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
		if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
		{
			SetVolume(g_BGMNo, 0.1f);

			WorldDecision = true;

			//STAGE_SELECT�ֈڍs����
			SceneTransition(SCENE_STAGE_SELECT);
		}

		// �}�E�X���������ʒu�ɂ����āA���N���b�N������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
		if (mouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
		{
			SetVolume(g_BGMNo, 0.1f);

			WorldDecision = true;

			//STAGE_SELECT�ֈڍs����
			if (g_WorldSelect.select_x == -2)
			{
				SceneTransition(SCENE_TITLE);
			}
			else
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}





		//�@���[���h�I���̑I�����Ă���Ƃ���̕`�ʂ̏���
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

				// �I������Ă���Ƃ��̕\��
				if (g_WorldSelect.select_x == -2)
				{
					now_world_select_EffectArray =
						// �^�C�g���ɖ߂鏈��
						SetEffect(60, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
							D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
							0.0f, 1.0f, 0, 999, 0, 0,
							0.0f, 0.0f, 0);

				
				}
	
		
				
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

	// �Z�[�u�f�[�^����Q�b�g���Ă鐯�̐���ǂݍ���
	int AllWorldStar = GetStar(0);//���ׂẴX�e�[�W�̌��݊l�����Ă��鐯�̐�

	int World1Star = GetStar(1);  //�X�e�[�W1�̌��݊l�����Ă��鐯�̐�

	int World2Star = GetStar(2);  //�X�e�[�W2�̌��݊l�����Ă��鐯�̐�

	int World3Star = GetStar(3);  //�X�e�[�W3�̌��݊l�����Ă��鐯�̐�

	int World4Star = GetStar(4);  //�X�e�[�W4�̌��݊l�����Ă��鐯�̐�

	int World5Star = GetStar(5);  //�X�e�[�W5�̌��݊l�����Ă��鐯�̐�

	int Number_EffectArray[2] = { 0,0 };
	int* p_Number_EffectArray = Number_EffectArray;
	// �Z�[�u�f�[�^����ǂݍ��񂾑S�Ă̐��̐��̕\��
	SetEffectNumber(AllWorldStar, p_Number_EffectArray, D3DXVECTOR2(250.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// �S�Ă̐��̐�(150)�̕\��
	SetEffectNumber(150, p_Number_EffectArray, D3DXVECTOR2(400.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// �X�e�[�W1�̌��݊l�����Ă��鐯�̐��̕\��
	SetEffectNumber(World1Star, p_Number_EffectArray, D3DXVECTOR2(200.0f, 320.0f), D3DXVECTOR2(200.0f, 320.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);
	// �X�e�[�W2�̌��݊l�����Ă��鐯�̐��̕\��
	SetEffectNumber(World2Star, p_Number_EffectArray, D3DXVECTOR2(480.0f, 600.0f), D3DXVECTOR2(480.0f, 600.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);
	// �X�e�[�W3�̌��݊l�����Ă��鐯�̐��̕\��
	SetEffectNumber(World3Star, p_Number_EffectArray, D3DXVECTOR2(720.0f, 350.0f), D3DXVECTOR2(720.0f, 350.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);
	// �X�e�[�W4�̌��݊l�����Ă��鐯�̐��̕\��
	SetEffectNumber(World4Star, p_Number_EffectArray, D3DXVECTOR2(970.0f, 660.0f), D3DXVECTOR2(970.0f, 660.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);
	// �X�e�[�W5�̌��݊l�����Ă��鐯�̐��̕\��
	SetEffectNumber(World5Star, p_Number_EffectArray, D3DXVECTOR2(1200.0f, 500.0f), D3DXVECTOR2(1200.0f, 500.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);


	// �X�e�[�W1�̑S�Ă̐��̐�(30)�̕\�� ///(���k)///
	SetEffectNumber(30, p_Number_EffectArray, D3DXVECTOR2(300.0f, 320.0f), D3DXVECTOR2(300.0f, 320.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
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

	// �^�C�g���ɖ߂鏈��
	SetEffect(60, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	return;
}
