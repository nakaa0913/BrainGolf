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
#include "result.h"
#include "camera.h"
#include "predictionbullet.h"
#include "gamedata.h"
#include "gameover.h"
#include "pause.h"
#include "gimmick_description.h"
#include "stageselect.h"

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
static int g_BGMNo = 0;

bool goal = false;
bool gameover = false;

int game_frame_time = 0;
int sound_once = 0;

RESULT* p_GetResult = GetResult();

bool BGMonce = false;

bool pushnextstage = false;

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitGame(void)
{
	pushnextstage = false;
	goal = false;
	gameover = false;

	game_frame_time = 0;

	InitPlayer();
	InitEnemy();
	InitEnemyEmitter();
	InitBullet();
	InitScore();
	InitBG();
	InitResult();
	InitGameover();
	InitCamera();
	InitPrediction();
	InitGamedata();

	InitGimmickDescription();

	g_BGMNo = LoadSound("data/BGM/���ɗh����.wav");
	

	if (BGMonce)
	{
		SetVolume(g_BGMNo, 0.5f);
		PlaySound(g_BGMNo, -1);
	}

	BGMonce = false;
	sound_once = 0;
}

void InitGameForPlacement(void)
{
	goal = false;
	gameover = false;

	game_frame_time = 0;

	InitPlayer();
	InitEnemy();
	InitEnemyEmitter();
	InitBullet();
	InitScore();
	InitBG();
	InitResult();
	InitGameover();
	InitCamera();
	InitPrediction();
	InitGamedata();

	InitGimmickDescription();

	if (GetNowChoiceStageNum() <= 10)
	{
		// ���a�w�i�̕\��
		g_BGMNo = LoadSound("data/BGM/���ɗh����.wav");
		SetVolume(g_BGMNo, 1.0f);
	}
	else if (GetNowChoiceStageNum() <= 15)
	{
		// �ጴ�w�i�̕\��
		g_BGMNo = LoadSound("data/BGM/���L�m�C���h��.wav");
		SetVolume(g_BGMNo, 0.5f);
	}
	else if (GetNowChoiceStageNum() <= 20)
	{
		// �n���w�i�̕\��
		g_BGMNo = LoadSound("data/BGM/������.wav");
		SetVolume(g_BGMNo, 0.6f);
	}

	PlaySound(g_BGMNo, -1);

	sound_once = 0;
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitGame()
{
	StopSoundAll();
	//�������Ƃ͋t���ɏI���������s��
	UninitGimmickDescription();
	UninitGamedata();
	UninitPrediction();
	UninitCamera();
	UninitBG();
	UninitScore();
	UninitBullet();
	UninitEnemy();
	UninitPlayer();
	UninitResult();
	UninitGameover();

	gameover = false;
	goal = false;
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	if (pushnextstage == false)
	{
		if (goal == false)
		{
			if (gameover == false)
			{
				UpdateCamera();
				UpdateBG();
				UpdatePlayer();
				UpdateEnemy();
				UpdateBullet();
				UpdateScore();

				UpdateEnemyEmitter();

				UpdateCollision();
				UpdatePrediction();
				UpdateGamedata();

				UpdateGimmickDescription_Game();
				// �Q�[���X�^�[�g���Ă���̃t���[�����Ԃ�+1����
				game_frame_time++;

				// �Q�[���X�^�[�g���Ă���̎���(�b)��+1����,60�t���[�����Ƃ�+1
				if (game_frame_time % 60 == 0)
				{
					GAMEDATA* p_Gamedata = GetGamedata();
					p_Gamedata->game_time++;
				}
			}
			else
			{
				UpdateGameover();
			}

		}
		else {
			UpdateResult();
			if (pushnextstage == false)
			{
				if (sound_once == 0)
				{
					if (p_GetResult->goaltime == 1)
					{
						StopSoundAll();
						g_BGMNo = LoadSound("data/SE/funnyelectrosingle.wav");
						PlaySound(g_BGMNo, 0);
						sound_once = 1;
					}
					
				}
				if (sound_once == 1)
				{
					if (p_GetResult->goaltime == 200)
					{
						StopSoundAll();
						g_BGMNo = LoadSound("data/BGM/wish_m329.wav");
						PlaySound(g_BGMNo, -1);
						sound_once = 2;
					}
				}
			}
		}
	}



	////�X�y�[�X�L�[��������Ă��āA�t�F�[�h�������ł͂Ȃ��Ƃ�
	//if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE) 
	//{
	//	SetVolume(g_BGMNo, 0.1f);

	//	//RESULT�ֈڍs����
	//	SceneTransition(SCENE_RESULT);
	//}
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawGame(void)
{

	DrawBG();
	DrawBullet();
	DrawPrediction();
	DrawEnemy();
	DrawPlayer();

	DrawScore();
	if (goal == true)
	{
		DrawResult();
	}
	if (gameover == true)
	{
		DrawGameover();
	}
	//if (pause = true)
	//{
		//DrawPause();
	//}
}

void GoalTrue()
{
	goal = true;

	return;
}

void GoalFalse()
{
	goal = false;

	return;
}


void GameoverTrue()
{
	gameover = true;

	return;
}

//void PauseTrue()
//{
//	pause = true;
//
//	return;
//}

// BGMonce��true�ɂ��邾��
void BGMonceTrue()
{
	BGMonce = true;
	return;
}

// pushnextstage��true�ɂ��邾��
void NextstageTrue()
{
	pushnextstage = true;
	return;
}

// sound_once��-60�ɂ��ĉ���炳�Ȃ��悤�ɂ���ɂ��邾��
void PushNextstage()
{
	sound_once = -60;
	return;
}