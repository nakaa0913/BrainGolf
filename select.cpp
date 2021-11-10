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
#include"select.h"
#include "Texture.h"
#include "sprite.h"
#include "effect.h"
#include "stagedata.h"
#include "FileDataManagement.h"
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
static SELECT g_Select;

static int	g_TextureNo = 0;	// テクスチャ情報
static int	g_BGMNo = 0;		// BGM識別子

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitSelect(void)
{
	//テクスチャ生成
	g_TextureNo = LoadTexture("data/TEXTURE/select.png");


	for (int i = 0; i < SELECT_MAX; i++)
	{
		g_Select.selectpush = 0;
		g_Select.selectvertical = 0;
	}


	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)をループ指定すると無限ループ
	PlaySound(g_BGMNo, -1);

	g_Select.selecttime = 0;

	return ;
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitSelect()
{
	
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateSelect(void)
{
	//スペースキーが押されていて、フェード処理中ではないとき
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SetVolume(g_BGMNo, 0.1f);

		//RESULTへ移行する
		SceneTransition(SCENE_GAME);
	}


	/////////////

	
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

		
		//1段目
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

		//二段目
		/*SetEffect(6, D3DXVECTOR2(60.0f, 300.0f), D3DXVECTOR2(60.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(7, D3DXVECTOR2(170.0f, 300.0f), D3DXVECTOR2(170.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(280.0f, 300.0f), D3DXVECTOR2(280.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(390.0f, 300.0f), D3DXVECTOR2(390.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(500.0f, 300.0f), D3DXVECTOR2(500.0f, 300.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		//三段目
		SetEffect(6, D3DXVECTOR2(60.0f, 400.0f), D3DXVECTOR2(60.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(7, D3DXVECTOR2(170.0f, 400.0f), D3DXVECTOR2(170.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(280.0f, 400.0f), D3DXVECTOR2(280.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(390.0f, 400.0f), D3DXVECTOR2(390.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(500.0f, 400.0f), D3DXVECTOR2(500.0f, 400.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		//四段目
		SetEffect(6, D3DXVECTOR2(60.0f, 500.0f), D3DXVECTOR2(60.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(7, D3DXVECTOR2(170.0f, 500.0f), D3DXVECTOR2(170.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(280.0f, 500.0f), D3DXVECTOR2(280.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(390.0f, 500.0f), D3DXVECTOR2(390.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);

		SetEffect(6, D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 0,
			D3DXVECTOR2(50.0f, 50.0f), D3DXVECTOR2(50.0f, 50.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 0,
			0.0f, 0.0f, 0);*/

		//セレクト一番上

		if (g_Select.selectvertical == 0)
		{
			if (g_Select.selectpush == 0)
			{
					SetEffect(6, D3DXVECTOR2(240.0f, 200.0f), D3DXVECTOR2(240.0f, 200.0f), 0,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
						1.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
			}

			if (g_Select.selectpush == 1)
			{
				SetEffect(7, D3DXVECTOR2(480.0f, 500.0f), D3DXVECTOR2(480.0f, 500.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}

			if (g_Select.selectpush == 2)
			{
				SetEffect(6, D3DXVECTOR2(720.0f, 250.0f), D3DXVECTOR2(720.0f, 250.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}

			if (g_Select.selectpush == 3)
			{
				SetEffect(6, D3DXVECTOR2(960.0f, 550.0f), D3DXVECTOR2(960.0f, 550.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}

			if (g_Select.selectpush == 4)
			{
				SetEffect(6, D3DXVECTOR2(1200.0f, 400.0f), D3DXVECTOR2(1200.0f, 400.0f), 0,
					D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 0,
					0.0f, 0.0f, 0);
			}
		}

			//セレクト二段目
			/*if (g_Select.selectvertical == 1)
			{
				if (g_Select.selectpush == 0)
				{
					SetEffect(6, D3DXVECTOR2(60.0f, 300.0f), D3DXVECTOR2(60.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_Select.selectpush == 1)
				{
					SetEffect(7, D3DXVECTOR2(170.0f, 300.0f), D3DXVECTOR2(170.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_Select.selectpush == 2)
				{
					SetEffect(6, D3DXVECTOR2(280.0f, 300.0f), D3DXVECTOR2(280.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_Select.selectpush == 3)
				{
					SetEffect(6, D3DXVECTOR2(390.0f, 300.0f), D3DXVECTOR2(390.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}

				if (g_Select.selectpush == 4)
				{
					SetEffect(6, D3DXVECTOR2(500.0f, 300.0f), D3DXVECTOR2(500.0f, 300.0f), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 0,
						0.0f, 0.0f, 0);
				}
			}*/

			



			if (g_Select.selectcooltime <= 0)
			{

				if (g_Select.selectvertical >= 2)
				{
					g_Select.selectvertical = 0;
				}

				if (g_Select.selectvertical < 0)
				{
					g_Select.selectvertical = 1;
				}
			

				if (GetKeyboardPress(DIK_UP))
				{
					g_Select.selectvertical--;
					g_Select.selectcooltime = 10;

				}

				

				if (GetKeyboardPress(DIK_RIGHT))
				{
					g_Select.selectpush++;
					g_Select.selectcooltime = TIME;
				}
				if (g_Select.selectpush >= 5)
				{
					g_Select.selectpush = 0;
				}

				if (GetKeyboardPress(DIK_LEFT))
				{
					g_Select.selectpush--;
					g_Select.selectcooltime = TIME;

				}
				if (g_Select.selectpush < 0)
				{
					g_Select.selectpush = 4;
				}


				if (g_Select.selectpush == 0)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = 10;
					}

					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}


				if (g_Select.selectpush == 1)
				{

					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				if (g_Select.selectpush == 2)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				if (g_Select.selectpush == 3)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				if (g_Select.selectpush == 4)
				{
					if (GetKeyboardPress(DIK_DOWN))
					{
						g_Select.selectvertical++;
						g_Select.selectcooltime = TIME;
					}
					if (GetKeyboardPress(DIK_RETURN))
					{
						SceneTransition(SCENE_GAME);
					}
				}

				

			}



			if (g_Select.selectcooltime >= 0)
				g_Select.selectcooltime--;

	


		


			g_Select.selecttime++;
	
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawSelect(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}

