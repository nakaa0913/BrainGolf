/*==============================================================================

   ゲーム処理 [game.cpp]
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

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;
bool goal = false;
bool gameover = false;

int game_frame_time = 0;
int sound_once = 0;

RESULT* p_GetResult = GetResult();

/*------------------------------------------------------------------------------
   初期化関数
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

	InitGimmickDescription();

	g_BGMNo = LoadSound("data/BGM/ユキノイロドリ.wav");

	//SetVolume(g_BGMNo, 0.5f);
	//PlaySound(g_BGMNo, -1);
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

	g_BGMNo = LoadSound("data/BGM/ユキノイロドリ.wav");

	SetVolume(g_BGMNo, 0.5f);
	PlaySound(g_BGMNo, -1);
	sound_once = 0;
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	StopSoundAll();
	//初期化とは逆順に終了処理を行う
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
   更新処理をする関数
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

			UpdateGimmickDescription_Game();
			// ゲームスタートしてからのフレーム時間を+1する
			game_frame_time++;

			// ゲームスタートしてからの時間(秒)を+1する,60フレームごとに+1
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
		if (sound_once == 0)
		{
			StopSoundAll();
			g_BGMNo = LoadSound("data/SE/funnyelectrosingle.wav");
			PlaySound(g_BGMNo, 0);
			sound_once = 1;
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



	////スペースキーが押されていて、フェード処理中ではないとき
	//if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE) 
	//{
	//	SetVolume(g_BGMNo, 0.1f);

	//	//RESULTへ移行する
	//	SceneTransition(SCENE_RESULT);
	//}
}

/*------------------------------------------------------------------------------
   描画処理をする関数
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