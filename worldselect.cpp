/*==============================================================================

   ゲーム処理 [game.cpp]
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
static WORLDSELECT g_WorldSelect;

static int	g_TextureNo = 0;	// テクスチャ情報
static int	g_BGMNo = 0;		// BGM識別子

int now_world_select_EffectArray = -1;
bool world_select_once = false;
int world_select_once_time = 0;

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitWorldSelect(void)
{
	//テクスチャ生成
	g_TextureNo = LoadTexture("data/TEXTURE/select/world_select.png");



	g_WorldSelect.select_x = 0;
	g_WorldSelect.select_y = 0;



	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)をループ指定すると無限ループ
	PlaySound(g_BGMNo, -1);

	g_WorldSelect.selecttime = 0;

	world_select_once = false;
	now_world_select_EffectArray = -1;
	world_select_once_time = 0;

	// ワールドセレクト画面の最初に描写される者たち
	StartWorldSelectScreen();

	return;
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitWorldSelect()
{
	UnloadTexture("data/TEXTURE/select/world_select.png");

}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateWorldSelect(void)
{
	//スペースキーが押されていて、フェード処理中ではないとき
	if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SetVolume(g_BGMNo, 0.1f);

		//STAGE_SELECTへ移行する
		SceneTransition(SCENE_STAGE_SELECT);
	}




	//ミッション
	/*SetEffect(8, D3DXVECTOR2(280.0f, 700.0f), D3DXVECTOR2(280.0f, 700.0f), 0,
		D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR2(500.0f, 200.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);*/

	//ロック
	/*SetEffect(10, D3DXVECTOR2(280.0f, 450.0f), D3DXVECTOR2(280.0f, 450.0f), 0,
		D3DXVECTOR2(450.0f, 100.0f), D3DXVECTOR2(450.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);*/


	// エンターキーが押された時の処理
	/*if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_STAGE_SELECT);
	}*/


	// キー入力による操作
	if (g_WorldSelect.selectcooltime <= 0)
	{
		bool use_key = false;		// キー入力されたかどうか
		// 右
		if (Keyboard_IsKeyDown(KK_RIGHT))
		{
			g_WorldSelect.select_x++;
			use_key = true;
		}
		// 左
		if (Keyboard_IsKeyDown(KK_LEFT))
		{
			g_WorldSelect.select_x--;
			use_key = true;
		}

		// 選択しているところが限界を超えないようにする処理
		if (g_WorldSelect.select_x >= WORLD_SELECT_MAX_X)
			g_WorldSelect.select_x = 0;
		if (g_WorldSelect.select_x < 0)
			g_WorldSelect.select_x = WORLD_SELECT_MAX_X - 1;

		if (use_key == true)
		{
			// 初期化と前回使われていたものの消去
			g_WorldSelect.selectcooltime = WORDL_SELECT_COOL;
			EffectBreak(now_world_select_EffectArray);
			world_select_once = false;
			world_select_once_time = 0;
		}
	}





	//　ワールド選択の選択しているところの処理
	if (world_select_once == false)
	{

		world_select_once = true;

		if (g_WorldSelect.select_y == 0)
		{

			// 選択されているときの表示
			if (g_WorldSelect.select_x == 0)
			{
				now_world_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						1.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// 選択されているときの表示
			if (g_WorldSelect.select_x == 1)
			{
				now_world_select_EffectArray =
					SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// 選択されているときの表示
			if (g_WorldSelect.select_x == 2)
			{
				now_world_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// 選択されているときの表示
			if (g_WorldSelect.select_x == 3)
			{
				now_world_select_EffectArray =
					SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 60,
						0.0f, 0.0f, 0);
			}

			// 選択されているときの表示
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


		// 選択されてからの時間が増えていく
		world_select_once_time++;
	}


	// クールタイムのカウントを減らす処理
	if (g_WorldSelect.selectcooltime > 0)
		g_WorldSelect.selectcooltime--;

	g_WorldSelect.selecttime++;

}

WORLDSELECT* GetWorldSelect()
{
	return &g_WorldSelect;
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawWorldSelect(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}


int GetNowWorld()
{
	return g_WorldSelect.select_x + 1;
}


void StartWorldSelectScreen()
{
	// 現在獲得している星の数の表示
	SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// 選ばれてないときの表示
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
