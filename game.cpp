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
int game_frame_time = 0;

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitGame(void)
{
	goal = false;
	game_frame_time = 0;

	InitPlayer();
	InitEnemy();
	InitEnemyEmitter();
	InitBullet();
	InitScore();
	InitBG();
	InitResult();
	InitCamera();
	InitPrediction();
	InitGamedata();
	g_BGMNo = LoadSound("data/BGM/sample001.wav");

	SetVolume(g_BGMNo, 1.0f);
	PlaySound(g_BGMNo, -1);
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	//初期化とは逆順に終了処理を行う
	UninitGamedata();
	UninitPrediction();
	UninitCamera();
	UninitBG();
	UninitScore();
	UninitBullet();
	UninitEnemy();
	UninitPlayer();
	UninitResult();
	goal = false;
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	if (goal == false)
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

		// ゲームスタートしてからのフレーム時間を+1する
		game_frame_time++;

		// ゲームスタートしてからの時間(秒)を+1する,60フレームごとに+1
		if (game_frame_time % 60 == 0)
		{
			GAMEDATA* p_Gamedata = GetGamedata();
			p_Gamedata->game_time++;
		}

	}
	else {
		UpdateResult();
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

}

void GoalTrue()
{
	goal = true;

	return;
}