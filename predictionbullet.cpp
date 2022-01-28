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

static int predictionbullet_ao;
static int predictionbullet_aka;

int drawcount = 0;


HRESULT InitPrediction(void)
{
	predictionbullet_ao = LoadTexture("data/TEXTURE/bullet/predictionbullet/ao.png");
	predictionbullet_aka = LoadTexture("data/TEXTURE/bullet/predictionbullet/aka.png");

	drawcount = 0;

	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		g_Prediction[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Prediction[i].size = D3DXVECTOR2(100.0f, 100.0f);
		g_Prediction[i].drawpos = g_Prediction[i].pos;
		g_Prediction[i].drawsize = g_Prediction[i].size;
		g_Prediction[i].angle = 0.0f;
		g_Prediction[i].vector = D3DXVECTOR2(100.0f, 100.0f);
		g_Prediction[i].shotpower = 1.0f;
		g_Prediction[i].tex = predictionbullet_ao;
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

			// 情報をもらう
			int havenum = returnHavePlayer();
			g_Prediction[i].angle = 360 - p_Player[havenum].angle;
			g_Prediction[i].pos = p_Player[havenum].pos;
			g_Prediction[i].size.x = PREDICTION_SIZE;
			g_Prediction[i].size.y = PREDICTION_SIZE;

			int ClubPattern = GetClubPattern();

			// ベクトルの計算
			g_Prediction[i].vector = AngleToVector2(g_Prediction[i].angle);	// 角度からベクトルを設定

			float sizebairitu = 0.0f;		// この分だけ毎回小さくなっていく
			
			// 値の更新		iの分だけ離れて表示される
			if (ClubPattern == 0)		// 地面を転がる場合の予測
			{
				g_Prediction[i].pos += g_Prediction[i].vector * (i + 1) * 40;
				g_Prediction[i].size *= 1.0f - i * sizebairitu;

				g_Prediction[i].tex = predictionbullet_ao;			// テクスチャの設定、転がる場合全部青

				if (i == 6)
				{
					g_Prediction[i].pos.x = 99999;
					g_Prediction[i].pos.y = 99999;
				}
			}
			if (ClubPattern == 1)		// とぶ場合の予測
			{
				//g_Prediction[i].pos += g_Prediction[i].vector * (i + 1) * 40;
				//g_Prediction[i].size *= 1.0f - i * 0.1f;

				
				switch (i)
				{
				case 0:
					g_Prediction[i].pos += g_Prediction[i].vector * 82;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 1:		// わんばんa
					g_Prediction[i].pos += g_Prediction[i].vector * 122;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 2:
					g_Prediction[i].pos += g_Prediction[i].vector * 161;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 3:		// つーばん
					g_Prediction[i].pos += g_Prediction[i].vector * 200;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 4:
					g_Prediction[i].pos += g_Prediction[i].vector * 220;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 5:		// すりーばん
					g_Prediction[i].pos += g_Prediction[i].vector * 240;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				case 6:		// 一番手前
					g_Prediction[i].pos += g_Prediction[i].vector * 41;
					g_Prediction[i].size *= 1.0f - i * sizebairitu;
					break;
				default:
					break;
				}
				// バウンドするところだけテクスチャを変える
				if (i == 1 || i == 3 || i == 5)
				{
					g_Prediction[i].tex = predictionbullet_aka;		// テクスチャの設定、飛ぶやつの場合着地する場所は赤くする
				}
				else
					g_Prediction[i].tex = predictionbullet_ao;
			}



			static int finalgapy = DRAW_GAP_FINAL_Y / 2;

			// pos を drawpos に変換		DRAW_GAP は、上から見た時の描写でのマップの描写はレフトトップで、プレイヤーはど真ん中でやってるから、そのずれ。
			g_Prediction[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Prediction[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Prediction[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			g_Prediction[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Prediction[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Prediction[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y + finalgapy;
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
	//CAMERA* p_Camera = GetCamera();

	//for (int i = 0; i < PREDICTION_MAX; i++)
	//{
	//	if (g_Prediction[i].isUse == true)	// この予測弾が使われている？
	//	{									// Yes
	//		// 予測弾の位置やテクスチャー座標を反映
	//		float px = g_Prediction[i].pos.x;		// バレットの表示位置X
	//		float py = g_Prediction[i].pos.y;		// バレットの表示位置Y
	//		float pw = g_Prediction[i].size.x;		// バレットの表示幅
	//		float ph = g_Prediction[i].size.y;		// バレットの表示高さ
	//		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



	//		// １枚のポリゴンの頂点とテクスチャ座標を設定
	//		DrawSpriteColorRotate(g_Prediction[i].tex, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, 0.0f);
	//	}
	//}
}


void DrawPredictionSpecifyNum(int i)
{

	// 球を発射していたら表示しない
	if (hassyazyunbi())
		PredictionUseTrue();
	else
		PredictionUseFalse();

	if (g_Prediction[0].isUse == true)
	{
		if(drawcount == 0)
			drawcount = 1;
	}
	else
		drawcount = 0;

	if (drawcount >= 1)
	{
		if (drawcount >= 7)
		{
			if (g_Prediction[i].isUse == true)	// この予測弾が使われている？
			{

				//バレットの位置やテクスチャー座標を反映
				float px = g_Prediction[i].drawpos.x;	// バレットの表示位置X
				float py = g_Prediction[i].drawpos.y;	// バレットの表示位置Y
				float pw = g_Prediction[i].drawsize.x;		// バレットの表示幅
				float ph = g_Prediction[i].drawsize.y;		// バレットの表示高さ
				D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



				// １枚のポリゴンの頂点とテクスチャ座標を設定
				DrawSpriteColorRotate(g_Prediction[i].tex, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, 0.0f);
			}
		}
		else
			drawcount++;
	}
}


PREDICTION* GetPrediction(void)
{
	return &g_Prediction[0];
}

void PredictionUseTrue()
{
	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		g_Prediction[i].isUse = true;
	}
	return;
}

void PredictionUseFalse()
{
	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		g_Prediction[i].isUse = false;
	}
	return;
}