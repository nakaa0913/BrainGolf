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
#include "mouse.h"
#include "placement.h"

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
static STAGESELECT g_StageSelect;

static int	g_TextureNo = 0;	// テクスチャ情報
static int	g_BGMNo = 0;		// BGM識別子

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

int NowWorld = 0;				   //今選択してるやつ
int tex_NowWorld_background = -1;  //背景
int tex_NowWorld_stagechoice = -1; //ステージ選択の四角いやつ
int tex_NowWorld_mission = -1;     //ミッション

// 選択したときの処理で使う
int now_stage_select_EffectArray = -1;
bool stage_select_once = false;
int stage_select_once_time = 0;

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitStageSelect(void)
{

	g_StageSelect.select_x = 0;
	g_StageSelect.select_y = 0;



	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)をループ指定すると無限ループ
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

	StartStageSelectScreen();


	stage_select_once = false;
	now_stage_select_EffectArray = -1;
	stage_select_once_time = 0;

	return;
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitStageSelect()
{
	UnloadTexture("data/TEXTURE/select/stage_select.png");

}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateStageSelect(void)
{
	//スペースキーが押されていて、フェード処理中ではないとき
	//if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	//{
	//	SetVolume(g_BGMNo, 0.1f);

	//	//RESULTへ移行する
	//	SceneTransition(SCENE_GAME);
	//}


	//星
	SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);






	// エンターキーを押してゲームスタートをする処理
	/*if (GetKeyboardPress(DIK_RETURN))
	{
		// 移動入力のとこですでにステージデータはもらっているのでこのままいってOK
		g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
		SceneTransition(SCENE_GAME);
	}*/
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		// 移動入力のとこですでにステージデータはもらっているのでこのままいってOK
		g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
		// プレイヤー配置フェーズに行く前に前回の配置情報をリセットする
		ResetPlacementArray();
		SceneTransition(SCENE_PLACEMENT);
	}

	// 移動キーが押された時の処理
	if (g_StageSelect.selectcooltime <= 0)
	{
		bool use_key = false;		// キー入力されたかどうか
		// 上
		/*if (GetKeyboardPress(DIK_UP))
		{
			g_StageSelect.select_y--;
			use_key = true;
		}*/
		if (Keyboard_IsKeyDown(KK_UP))
		{
			g_StageSelect.select_y--;
			use_key = true;
		}
		// 下
		/*if (GetKeyboardPress(DIK_DOWN))
		{
			g_StageSelect.select_y++;
			use_key = true;
		}*/
		if (Keyboard_IsKeyDown(KK_DOWN))
		{
			g_StageSelect.select_y++;
			use_key = true;
		}
		// 右
		/*if (GetKeyboardPress(DIK_RIGHT))
		{
			g_StageSelect.select_x++;
			use_key = true;
		}*/
		if (Keyboard_IsKeyDown(KK_RIGHT))
		{
			g_StageSelect.select_x++;
			use_key = true;
		}
		// 左
		/*if (GetKeyboardPress(DIK_LEFT))
		{
			g_StageSelect.select_x--;
			use_key = true;
		}*/
		if (Keyboard_IsKeyDown(KK_LEFT))
		{
			g_StageSelect.select_x--;
			use_key = true;
		}

		// 限界値による修正の処理
		if (g_StageSelect.select_x >= SELECT_MAX_X)
			g_StageSelect.select_x = 0;
		if (g_StageSelect.select_x < 0)
			g_StageSelect.select_x = SELECT_MAX_X - 1;
		if (g_StageSelect.select_y >= SELECT_MAX_Y)
			g_StageSelect.select_y = 0;
		if (g_StageSelect.select_y < 0)
			g_StageSelect.select_y = SELECT_MAX_Y - 1;

		if (use_key == true)
		{
			// 初期化と前回使われていたものの消去
			g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			EffectBreak(now_stage_select_EffectArray);
			DeleteMissionStageSelect();
			stage_select_once = false;
			stage_select_once_time = 0;
		}
	}



	// ステージ選択の時の原点となる場所
	float	stage_origin_x = 240.0f;			    // xの原点(0,0を選択しているとき)
	float	stage_origin_y = 200.0f;			    // yの原点(0,0を選択しているとき)

	// ステージ選択の時1個離れたらこれだけ離れるよってやつ
	float interval_x = 240.0f;
	float interval_y = 240.0f;

	if (stage_select_once == false)
	{
		stage_select_once = true;

		// ステージデータを受け取る,ミッションやマップの表示で使うため。
		// xとyからマップの番号を計算する
		int stagenum = (SELECT_MAX_X * g_StageSelect.select_y) + (g_StageSelect.select_x + 1);
		SetStageData(stagenum);

		// ステージデータを受け取った(更新された)のでミッションを表示させる
		DrawMissionStageSelect();

		//ステージ選択
		for (int x = 0; x < SELECT_MAX_X; x++)
		{
			for (int y = 0; y < SELECT_MAX_Y; y++)
			{
				// 現在の座標を求める
				float now_x = stage_origin_x + interval_x * x;
				float now_y = stage_origin_y + interval_y * y;

				// 検索。選択しているとこを見つけて大きいサイズで表示。
				if (g_StageSelect.select_x == x)
				{
					if (g_StageSelect.select_y == y)
					{
						now_stage_select_EffectArray =
							SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
								D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
								1.0f, 1.0f, 0, 999, 0, 60,
								0.0f, 0.0f, 0);
					}
				}
			}
		}
	}


	// 選択した状態が続いてる場合trueなのでここをとおる
	if (stage_select_once == true)
	{
		if (stage_select_once_time % 60 == 0)
		{
			ChangeEffectCount(now_stage_select_EffectArray, 0);
		}


		// 選択されてからの時間が増えていく
		stage_select_once_time++;
	}




	if (g_StageSelect.selectcooltime > 0)
		g_StageSelect.selectcooltime--;


	g_StageSelect.selecttime++;

}

STAGESELECT* GetStageSelect()
{
	return &g_StageSelect;
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawStageSelect(void)
{



	//// １枚のポリゴンの頂点とテクスチャ座標を設定
	//DrawSpriteColorRotate(tex_NowWorld_background, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR (1.0f, 1.0f, 1.0f, 1.0f), 1.0f);

	/*static int world_1_background;
	static int world_2_stagechoice;
	static int world_3_mission;
	static int world_4_selectstar;*/

}

void StartStageSelectScreen()
{
	//背景表示
	SetEffect(tex_NowWorld_background, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
		D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
		0.0f, 1.0f, 100, 999, 0, 180,
		0.0f, 0.0f, 0);

	////ミッション
	//SetEffect(tex_NowWorld_mission, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
	//	D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
	//	0.0f, 1.0f, 100, 999, 0, 180,
	//	0.0f, 0.0f, 0);


	// ステージ選択の時の原点となる場所
	float	stage_origin_x = 240.0f;			    // xの原点(0,0を選択しているとき)
	float	stage_origin_y = 200.0f;			    // yの原点(0,0を選択しているとき)

	// ステージ選択の時1個離れたらこれだけ離れるよってやつ
	float interval_x = 240.0f;
	float interval_y = 240.0f;

	//ステージ選択
	for (int x = 0; x < SELECT_MAX_X; x++)
	{
		for (int y = 0; y < SELECT_MAX_Y; y++)
		{
			// 現在の座標を求める
			float now_x = stage_origin_x + interval_x * x;
			float now_y = stage_origin_y + interval_y * y;

			// 選択されてないときの表示を出す(ステージすべて)
			SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 999, 0, 0,
				0.0f, 0.0f, 0);
		}
	}

	return;
}