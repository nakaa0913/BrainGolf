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
#include "result.h"
#include "scene.h"
#include "fade.h"
#include "effect.h"
#include "mission.h"
#include "savedata.h"
#include "stagedata.h"
#include "keyboard.h"
#include "sound.h"
#include "mouse.h"

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
static RESULT g_Result;

int now_result_select_EffectArray = -1;
bool result_select_once = false;
int result_select_once_time = 0;
//bool onlyOnce = true;
bool resultmouseuse = false;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	//テクスチャ読み込み


	g_Result.goaltime = 0;
	g_Result.selectpush = 0;


	//初期化
	result_select_once = false;
	now_result_select_EffectArray = -1;
	result_select_once_time = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	//マウスの座標を取得
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();

	// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
	int OldResultSelect = g_Result.selectpush;

	if (g_Result.goaltime == 10)
	{
		//暗闇4 明かりなら48
		SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
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



	if (g_Result.goaltime == 240)
	{
		//（アドバイス？）
		SetEffect(1, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
			D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
			0.0f, 1.0f, 100, 999, 0, 180,
			0.0f, 0.0f, 0);
		DrawMissionResult();
	}

	if (g_Result.goaltime == 300)
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

	if (g_Result.goaltime == 400)
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

	if (g_Result.goaltime == 430)
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

	if (g_Result.goaltime == 460)
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

	if (g_Result.goaltime >= 560)
	{
		if (g_Result.goaltime <= 8000)
		{
			if (GetKeyboardPress(DIK_RETURN))
			{
				g_Result.goaltime = 9000;
			}
			if (mouse_Lclick)
			{
				g_Result.goaltime = 9000;
			}
		}
	}

	if (g_Result.goaltime >= 9000)
	{
		//明るくする暗くするなら4
		SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//next?次のステージへ的な
		SetEffect(47, D3DXVECTOR2(1200.0f, 700.0f), D3DXVECTOR2(1200.0f, 700.0f), 1,
			D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);
		
		//ワールド選択に戻る
		SetEffect(49, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
			D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//横1440
		//縦810

		if (g_Result.selectpush == 0)
		{
			//next?次のステージへ的な
			SetEffect(47, D3DXVECTOR2(1200.0f, 700.0f), D3DXVECTOR2(1200.0f, 700.0f), 1,
				D3DXVECTOR2(400.0f, 400.0f), D3DXVECTOR2(400.0f, 400.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);

		}

		if (g_Result.selectpush == 1)
		{
			//ワールド選択に戻る
			SetEffect(49, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
				D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}

		/*if (g_Result.selectpush == 2)
		{
			SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), 1,
				D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(350.0f, 120.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}*/

		//キー入力
		if (g_Result.selecttime <= 0)
		{

			if (Keyboard_IsKeyDown(KK_RIGHT))
			{
				g_Result.selectpush++;
				g_Result.selecttime = 30;

			}
			if (g_Result.selectpush >= 2)
			{
				g_Result.selectpush = 0;
			}

			if (Keyboard_IsKeyDown(KK_LEFT))
			{
				g_Result.selectpush--;
				g_Result.selecttime = 30;

			}
			if (g_Result.selectpush < 0)
			{
				g_Result.selectpush = 1;
			}

			if (g_Result.goaltime >= 9060)
			{
				if (g_Result.selectpush == 0)
				{
					if (Keyboard_IsKeyDown(KK_ENTER))
					{
						SceneTransition(SCENE_WORLD_SELECT);

					}
				}

			}


			if (g_Result.selectpush == 1)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_STAGE_SELECT);

				}
			}
		}

		// マウスの座標を使っての入力処理
		//1 1200 700	300 300
		if (mouse_pos_X > 1050.0f && mouse_pos_X < 1350.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
		{
			g_Result.selectpush = 0;
			resultmouseuse = true;
		}
		//2 100 700		200 200
		else if (mouse_pos_X > 60.0f && mouse_pos_X < 140.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
		{
			g_Result.selectpush = 1;
			resultmouseuse = true;
		}

		// マウスが押される位置にあって、左クリック押されていて、フェード処理中ではないとき
		if (resultmouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
		{
			//SetVolume(g_BGMNo, 0.1f);

			//STAGE_SELECTへ移行する
			SceneTransition(SCENE_STAGE_SELECT);
		}


		// もし前のフレームから変化があった場合のみエフェクトなどを変化させる
		bool Change = false;
		if (OldResultSelect != g_Result.selectpush)
			Change = true;

		// 変更があった場合、初期化と新しいもののセット
		if (Change == true)
		{
			// 初期化と前回使われていたものの消去
			g_Result.selecttime = 30;
			//EffectBreak(now_result_select_EffectArray);		// 前の描写を消す
			result_select_once = false;						// 1回も描写してないよにする
			result_select_once_time = 0;						// 描写してからの時間のリセット
		}


		if (g_Result.selecttime >= 0)
			g_Result.selecttime--;

	}

	// 毎フレームカウントを増やす
	g_Result.goaltime++;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{

}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
RESULT* GetResult(void)
{
	return &g_Result;
}


void SetResult(D3DXVECTOR2 pos)
{

}