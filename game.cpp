/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :
														 Date   :
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


/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitGame(void)
{
	InitPlayer();
	InitEnemy();
	InitEnemyEmitter();
	InitBullet();
	InitScore();
	InitBG();

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
	UninitBG();
	UninitScore();
	UninitBullet();
	UninitEnemy();
	UninitPlayer();
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	UpdateBG();
	UpdatePlayer();
	UpdateEnemy();
	UpdateBullet();
	UpdateScore();

	UpdateEnemyEmitter();

	UpdateCollision();

	//スペースキーが押されていて、フェード処理中ではないとき
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE) 
	{
		SetVolume(g_BGMNo, 0.1f);

		//RESULTへ移行する
		SceneTransition(SCENE_RESULT);
	}
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	DrawBG();
	DrawBullet();
	DrawEnemy();
	DrawPlayer();

	DrawScore();
}

