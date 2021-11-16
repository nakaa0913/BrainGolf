/*==============================================================================

   頂点管理 [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include "Goal.h"
#include "scene.h"
#include "fade.h"
#include "effect.h"
#include "mission.h"
#include "savedata.h"
#include "stagedata.h"
#include "keyboard.h"

#define GOAL_H (50)
#define GOAL_W (50)
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static GOAL g_Goal;

//static int aa;//画面（鳥）
//static int bb;//星（たこ）
//static int cc;//リザルト
//static int dd;//選択画面（タイトル）
//static int ee;//タイトル
//static int ff;//クリア〜（タイトル）
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGoal(void)
{
	//テクスチャ読み込み



	g_Goal.goaltime = 0;
	g_Goal.selectpush = 0;



	//初期化


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGoal(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGoal(void)
{
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	if (g_Goal.goaltime == 10)
	{
		//暗闇
		SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 100, 999, 0, 180,
			0.0f, 0.0f, 0);
		//横1440
		//縦810
		//ゲームクリア
		SetEffect(5, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT / 2), 1,
			0.0f, 1.0f, 30, 120, 60, 90,
			0.0f, 0.0f, 0);

		
	}


	if (g_Goal.goaltime == 240)
	{
		//赤丸（アドバイス？）
		SetEffect(1, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
			D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
			0.0f, 1.0f, 100, 999, 0, 180,
			0.0f, 0.0f, 0);

	}

	if (g_Goal.goaltime == 300)
	{
		//星(影)
		SetEffect(14, D3DXVECTOR2(550.0f, 68.0f), D3DXVECTOR2(550.0f, 68.0f), 0,
			D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
			0.0f, 1.0f, 60, 999, 0, 60,
			0.0f, 0.0f, 0);
		//星(影)
		SetEffect(14, D3DXVECTOR2(550.0f, 163.0f), D3DXVECTOR2(550.0f, 163.0f), 0,
			D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
			0.0f, 1.0f, 60, 999, 0, 60,
			0.0f, 0.0f, 0);
		//星(影)
		SetEffect(14, D3DXVECTOR2(550.0f, 250.0f), D3DXVECTOR2(550.0f, 250.0f), 0,
			D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
			0.0f, 1.0f, 60, 999, 0, 60,
			0.0f, 0.0f, 0);
	}

	if (g_Goal.goaltime == 400)
	{
		// ミッションをクリアしているなら表示する
		if (p_Savedata[p_Stagedata->stagenum].mission_clear[0] == 1)
		{
			////星
			SetEffect(11, D3DXVECTOR2(550.0f, 68.0f), D3DXVECTOR2(550.0f, 68.0f), 0,
				D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				0.0f, 1.0f, 120, 999, 0, 60,
				0.0f, 0.0f, 0);
		}
		//横1440
		//縦810
	}

	if (g_Goal.goaltime == 430)
	{
		// ミッションをクリアしているなら表示する
		if (p_Savedata[p_Stagedata->stagenum].mission_clear[1] == 1)
		{
			//星
			SetEffect(11, D3DXVECTOR2(550.0f, 163.0f), D3DXVECTOR2(550.0f, 163.0f), 0,
				D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				0.0f, 1.0f, 120, 999, 0, 60,
				0.0f, 0.0f, 0);
		}
	}

	if (g_Goal.goaltime == 460)
	{
		// ミッションをクリアしているなら表示する
		if (p_Savedata[p_Stagedata->stagenum].mission_clear[2] == 1)
		{
			//星
			SetEffect(11, D3DXVECTOR2(550.0f, 250.0f), D3DXVECTOR2(550.0f, 250.0f), 0,
				D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				0.0f, 1.0f, 120, 999, 0, 60,
				0.0f, 0.0f, 0);
		}
	}

	if (g_Goal.goaltime >= 500)
	{
		if (g_Goal.goaltime <= 8000)
		{
			if (Keyboard_IsKeyDown(KK_ENTER))
			{
				g_Goal.goaltime = 9000;
			}
		}
	}

	if (g_Goal.goaltime >= 9000)
	{
	

		//暗闇
		SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);
		//
		SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f), 1,
			D3DXVECTOR2(300.0f, 80.0f), D3DXVECTOR2(300.0f, 80.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);
		//ステージ選択
		SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 550.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 550.0f), 1,
			D3DXVECTOR2(300.0f, 80.0f), D3DXVECTOR2(300.0f, 80.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);
		//タイトル
		SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), 1,
			D3DXVECTOR2(300.0f, 80.0f), D3DXVECTOR2(300.0f, 80.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);


		if (g_Goal.selectpush == 0)
		{
			SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f), 1,
				D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(350.0f, 120.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);

			
		}

		if (g_Goal.selectpush == 1)
		{
			SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 550.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 550.0f), 1,
				D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(350.0f, 120.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}

		if (g_Goal.selectpush == 2)
		{
			SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), 1,
				D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(350.0f, 120.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}


		if (g_Goal.selecttime <= 0)
		{

			if (Keyboard_IsKeyDown(KK_DOWN))
			{
				g_Goal.selectpush++;
				g_Goal.selecttime = 30;

			}
			if (g_Goal.selectpush >= 3)
			{
				g_Goal.selectpush = 0;
			}

			if (Keyboard_IsKeyDown(KK_UP))
			{
				g_Goal.selectpush--;
				g_Goal.selecttime = 30;

			}
			if (g_Goal.selectpush < 0)
			{
				g_Goal.selectpush = 2;
			}

			if (g_Goal.goaltime >= 9060)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_WORLD_SELECT);

				}
			}

			if (g_Goal.selectpush == 1)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_STAGE_SELECT);

				}
			}

			if (g_Goal.selectpush == 2)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_TITLE);

				}
			}

		}



		if (g_Goal.selecttime >= 0)
			g_Goal.selecttime--;

	}

	// 毎フレームカウントを増やす
	g_Goal.goaltime++;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGoal(void)
{

}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
GOAL* GetGoal(void)
{
	return &g_Goal;
}


void SetGoal(D3DXVECTOR2 pos)
{

}