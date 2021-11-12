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
#include "Goal.h"
#include"stageselect.h"
#include "Texture.h"
#include "sprite.h"
#include "effect.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "worldselect.h"
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
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SetVolume(g_BGMNo, 0.1f);

		//RESULTへ移行する
		SceneTransition(SCENE_STAGE_SELECT);
	}


	/////////////

	//// ステージ選択の時の原点となる場所
	//float	stage_origin_x = 240.0f;			    // xの原点(0,0を選択しているとき)
	//float	stage_origin_y = 200.0f;			    // yの原点(0,0を選択しているとき)

	//// ステージ選択の時1個離れたらこれだけ離れるよってやつ
	//float distance_x = 240.0f;
	//float distance_y = 240.0f;

	////ステージ選択横バージョン
	//for (int x = 0; x < SELECT_MAX_X; x++)
	//{
	//	for (int y = 0; y < SELECT_MAX_Y; y++)
	//	{
	//		// 現在の座標を求める
	//		float now_x = stage_origin_x + distance_x * x;
	//		float now_y = stage_origin_y + distance_y * y;

	//		// 選択されてないときの表示を出す(ステージすべて)
	//		SetEffect(6, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
	//			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
	//			0.0f, 1.0f, 0, 1, 0, 0,
	//			0.0f, 0.0f, 0);

	//		// 検索。選択しているとこを見つけて大きいサイズで表示。
	//		if (g_WorldSelect.select_x == x)
	//		{
	//			if (g_WorldSelect.select_y == y)
	//			{
	//				SetEffect(6, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
	//					D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
	//					1.0f, 1.0f, 0, 1, 0, 0,
	//					0.0f, 0.0f, 0);
	//			}
	//		}
	//	}
	//}




	//ミッション
	/*SetEffect(8, D3DXVECTOR2(280.0f, 700.0f), D3DXVECTOR2(280.0f, 700.0f), 0,
		D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR2(500.0f, 200.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);*/

		//星
	SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	//ロック
	/*SetEffect(10, D3DXVECTOR2(280.0f, 450.0f), D3DXVECTOR2(280.0f, 450.0f), 0,
		D3DXVECTOR2(450.0f, 100.0f), D3DXVECTOR2(450.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);*/


		// ワールド選択の時
	SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	//セレクト一番上

	if (g_WorldSelect.select_y == 0)
	{
		if (g_WorldSelect.select_x == 0)
		{
			SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
				D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
				1.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}

		if (g_WorldSelect.select_x == 1)
		{
			SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
				D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}

		if (g_WorldSelect.select_x == 2)
		{
			SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
				D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}

		if (g_WorldSelect.select_x == 3)
		{
			SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
				D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}

		if (g_WorldSelect.select_x == 4)
		{
			SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
				D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}
	}

	//セレクト二段目
	/*if (g_WorldSelect.select_y == 1)
	{
		if (g_WorldSelect.select_x == 0)
		{
			SetEffect(6, D3DXVECTOR2(60.0f, 300.0f), D3DXVECTOR2(60.0f, 300.0f), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}

		if (g_WorldSelect.select_x == 1)
		{
			SetEffect(7, D3DXVECTOR2(170.0f, 300.0f), D3DXVECTOR2(170.0f, 300.0f), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}

		if (g_WorldSelect.select_x == 2)
		{
			SetEffect(6, D3DXVECTOR2(280.0f, 300.0f), D3DXVECTOR2(280.0f, 300.0f), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}

		if (g_WorldSelect.select_x == 3)
		{
			SetEffect(6, D3DXVECTOR2(390.0f, 300.0f), D3DXVECTOR2(390.0f, 300.0f), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}

		if (g_WorldSelect.select_x == 4)
		{
			SetEffect(6, D3DXVECTOR2(500.0f, 300.0f), D3DXVECTOR2(500.0f, 300.0f), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 0,
				0.0f, 0.0f, 0);
		}
	}*/





	if (g_WorldSelect.selectcooltime <= 0)
	{

		/*if (g_WorldSelect.select_y >= 2)
		{
			g_WorldSelect.select_y = 0;
		}

		if (g_WorldSelect.select_y < 0)
		{
			g_WorldSelect.select_y = 1;
		}*/


		/*if (GetKeyboardPress(DIK_UP))
		{
			g_WorldSelect.select_y--;
			g_WorldSelect.selectcooltime = 10;

		}
*/


		if (GetKeyboardPress(DIK_RIGHT))
		{
			g_WorldSelect.select_x++;
			g_WorldSelect.selectcooltime = TIME;
		}
		if (g_WorldSelect.select_x >= 5)
		{
			g_WorldSelect.select_x = 0;
		}

		if (GetKeyboardPress(DIK_LEFT))
		{
			g_WorldSelect.select_x--;
			g_WorldSelect.selectcooltime = TIME;

		}
		if (g_WorldSelect.select_x < 0)
		{
			g_WorldSelect.select_x = 4;
		}


		if (g_WorldSelect.select_x == 0)
		{
			/*if (GetKeyboardPress(DIK_DOWN))
			{
				g_WorldSelect.select_y++;
				g_WorldSelect.selectcooltime = 10;
			}*/

			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}


		if (g_WorldSelect.select_x == 1)
		{

			//if (GetKeyboardPress(DIK_DOWN))
			//{
			//	g_WorldSelect.select_y++;
			//	g_WorldSelect.selectcooltime = TIME;
			//}
			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}

		if (g_WorldSelect.select_x == 2)
		{
			//if (GetKeyboardPress(DIK_DOWN))
			//{
			//	g_WorldSelect.select_y++;
			//	g_WorldSelect.selectcooltime = TIME;
			//}
			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}

		if (g_WorldSelect.select_x == 3)
		{
			//if (GetKeyboardPress(DIK_DOWN))
			//{
			//	g_WorldSelect.select_y++;
			//	g_WorldSelect.selectcooltime = TIME;
			//}
			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}

		if (g_WorldSelect.select_x == 4)
		{
			//if (GetKeyboardPress(DIK_DOWN))
			//{
			//	g_WorldSelect.select_y++;
			//	g_WorldSelect.selectcooltime = TIME;
			//}
			if (GetKeyboardPress(DIK_RETURN))
			{
				SceneTransition(SCENE_STAGE_SELECT);
			}
		}



	}



	if (g_WorldSelect.selectcooltime >= 0)
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