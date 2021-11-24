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
#include "gameover.h"

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
static GAMEOVER g_Gameover;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGameover(void)
{
	//テクスチャ読み込み


	g_Gameover.gameovertime = 0;
	g_Gameover.selectpush = 0;


	//初期化


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameover(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameover(void)
{



	if (g_Gameover.gameovertime == 10)
	{
		//暗闇4 明かりなら48
		SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 100, 999, 0, 180,
			0.0f, 0.0f, 0);
		//横1440
		//縦810
		//ゲームオーバー
		SetEffect(55, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT / 2), 1,
			0.0f, 1.0f, 30, 120, 60, 90,
			0.0f, 0.0f, 0);

	}



	//if (g_Gameover.gameovertime == 240)
	//{
	//	
	//}

	//if (g_Gameover.gameovertime == 300)
	//{
	//	
	//}

	//if (g_Gameover.gameovertime == 400)
	//{
	//	
	//}

	//if (g_Gameover.gameovertime == 430)
	//{
	//	
	//}

	//if (g_Gameover.gameovertime == 460)
	//{
	//	
	//}

	//if (g_Gameover.gameovertime >= 560)
	//{
	//	if (g_Gameover.gameovertime <= 8000)
	//	{
	//		if (GetKeyboardPress(DIK_RETURN))
	//		{
	//			g_Gameover.gameovertime = 9000;
	//		}
	//	}
	//}

	if (g_Gameover.gameovertime >= 240)
	{
		////明るくする暗くするなら4
		//SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
		//	D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
		//	0.0f, 0.5f, 0, 1, 0, 1,
		//	0.0f, 0.0f, 0);

		//ステージ名
		SetEffect(57, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//リスタート
		SetEffect(56, D3DXVECTOR2(1200.0f, 700.0f), D3DXVECTOR2(1200.0f, 700.0f), 1,
			D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);
		//プレイヤー配置に戻る
		SetEffect(59, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
			D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//マップ？に戻る
		SetEffect(58, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
			D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		//横1440
		//縦810

		if (g_Gameover.selectpush == 0)
		{
			//next?次のステージへ的な
			SetEffect(56, D3DXVECTOR2(1200.0f, 700.0f), D3DXVECTOR2(1200.0f, 700.0f), 1,
				D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
			

		}

		if (g_Gameover.selectpush == 1)
		{
			//ワールド選択に戻る
			SetEffect(58, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
				D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}

		if (g_Gameover.selectpush == 2)
		{
			//プレイヤー配置に戻る
			SetEffect(59, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
				D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}

		/*if (g_Gameover.selectpush == 2)
		{
			SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), 1,
				D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(350.0f, 120.0f), 1,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		}*/


		if (g_Gameover.selecttime <= 0)
		{

			if (Keyboard_IsKeyDown(KK_RIGHT))
			{
				g_Gameover.selectpush++;
				g_Gameover.selecttime = 30;

			}
			if (g_Gameover.selectpush >= 3)
			{
				g_Gameover.selectpush = 0;
			}

			if (Keyboard_IsKeyDown(KK_LEFT))
			{
				g_Gameover.selectpush--;
				g_Gameover.selecttime = 30;

			}
			if (g_Gameover.selectpush < 0)
			{
				g_Gameover.selectpush = 2;
			}

			/*if (g_Gameover.gameovertime >= 9060)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_WORLD_SELECT);

				}
			}*/

			if (g_Gameover.selectpush == 0)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_GAME);

				}
			}

			if (g_Gameover.selectpush == 1)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_STAGE_SELECT);

				}
			}

			if (g_Gameover.selectpush == 2)
			{
				if (Keyboard_IsKeyDown(KK_ENTER))
				{
					SceneTransition(SCENE_PLACEMENT);

				}
			}

		}



		if (g_Gameover.selecttime >= 0)
			g_Gameover.selecttime--;

	}

	// 毎フレームカウントを増やす
	g_Gameover.gameovertime++;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGameover(void)
{

}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
GAMEOVER* GetGameover(void)
{
	return &g_Gameover;
}


void SetGameover(D3DXVECTOR2 pos)
{

}