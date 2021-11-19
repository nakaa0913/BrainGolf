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

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitGame(void)
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
	g_BGMNo = LoadSound("data/BGM/sample001.wav");

	SetVolume(g_BGMNo, 1.0f);
	PlaySound(g_BGMNo, -1);
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitGame()
{
	//�������Ƃ͋t���ɏI���������s��
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
}

void GoalTrue()
{
	goal = true;

	return;
}


void GameoverTrue()
{
	gameover = true;

	return;
}