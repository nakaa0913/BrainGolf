#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "bg.h"
#include "scene.h"
#include "fade.h"
#include <math.h>
#include "game.h"
#include "primitive.h"
#include "collision.h"
#include "camera.h"
#include "predictionbullet.h"
#include "player.h"
#include "bullet.h"


static PREDICTION g_Prediction[PREDICTION_MAX];					// 予測弾構造体


HRESULT InitPrediction(void)
{
	int texNo = LoadTexture("data/TEXTURE/bullet/ao.png");

	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		g_Prediction[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Prediction[i].size = D3DXVECTOR2(100.0f, 100.0f);
		g_Prediction[i].drawpos = g_Prediction[i].pos;
		g_Prediction[i].drawsize = g_Prediction[i].size;
		g_Prediction[i].angle = 0.0f;
		g_Prediction[i].vector = D3DXVECTOR2(100.0f, 100.0f);
		g_Prediction[i].shotpower = 1.0f;
		g_Prediction[i].texNo = texNo;
		g_Prediction[i].isUse = false;



	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPrediction(void)
{
	// UnloadTexture("data/TEXTURE/bullet/ao.png");
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePrediction(void)
{

	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		if (g_Prediction[i].isUse == true)	// この予測弾が使われている？
		{
			CAMERA* p_Camera = GetCamera();
			BULLET* p_Bullet = GetBullet();
			PLAYER* p_Player = GetPlayer();

			int havenum = 0;

			// 情報をもらう
			g_Prediction[i].angle = p_Player[havenum].angle;
			g_Prediction[i].pos = p_Player[havenum].pos;
			g_Prediction[i].size.x = p_Bullet[0].w;
			g_Prediction[i].size.y = p_Bullet[0].h;

			// pos を drawpos に変換		DRAW_GAP は、上から見た時の描写でのマップの描写はレフトトップで、プレイヤーはど真ん中でやってるから、そのずれ。
			g_Prediction[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Prediction[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Prediction[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) - p_Camera->pos.x;
			g_Prediction[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Prediction[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Prediction[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) - p_Camera->pos.y;
			g_Prediction[i].drawsize.x = g_Prediction[i].size.x * p_Camera->magnification;
			g_Prediction[i].drawsize.y = g_Prediction[i].size.y * p_Camera->magnification;

		}

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPrediction(void)
{
	CAMERA* p_Camera = GetCamera();

	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		if (g_Prediction[i].isUse == true)	// この予測弾が使われている？
		{									// Yes
			// 予測弾の位置やテクスチャー座標を反映
			float px = g_Prediction[i].pos.x;		// バレットの表示位置X
			float py = g_Prediction[i].pos.y;		// バレットの表示位置Y
			float pw = g_Prediction[i].size.x;		// バレットの表示幅
			float ph = g_Prediction[i].size.y;		// バレットの表示高さ
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColorRotate(g_Prediction[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, 0.0f);
		}
	}
}


void DrawPredictionSpecifyNum(int i)
{
	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		if (g_Prediction[i].isUse == true)	// この予測弾が使われている？
		{									// Yes
			//バレットの位置やテクスチャー座標を反映
			float px = g_Prediction[i].drawpos.x;	// バレットの表示位置X
			float py = g_Prediction[i].drawpos.y;	// バレットの表示位置Y
			float pw = g_Prediction[i].drawsize.x;		// バレットの表示幅
			float ph = g_Prediction[i].drawsize.y;		// バレットの表示高さ
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColorRotate(g_Prediction[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, 0.0f);
		}
	}
}


PREDICTION* GetPrediction(void)
{
	return &g_Prediction[0];
}
