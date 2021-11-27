//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "texture.h"
#include "sprite.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(16)	// キャラサイズ
#define TEXTURE_HEIGHT				(32)	// 


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static bool						g_Use;						// true:使っている  false:未使用
static float					g_w, g_h;					// 幅と高さ
static D3DXVECTOR3				g_Pos;						// ポリゴンの座標
static int						g_TexNo;					// テクスチャ番号

static int						g_Score;					// スコア
static int						g_Score2;					// スコア
static int						g_Score3;					// スコア

static int						g_ShotPower;				// 弾を打ち出すときの力0~100

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{
	//テクスチャ生成
	g_TexNo = LoadTexture("data/TEXTURE/other_effect/number.png");

	//初期化
	g_Use   = true;
	g_w     = TEXTURE_WIDTH;
	g_h     = TEXTURE_HEIGHT;
	g_Pos   = D3DXVECTOR3(500.0f, 20.0f, 0.0f);

	g_Score = 0;	// スコアの初期化
	g_Score2 = 0;	// スコアの初期化
	g_Score3 = 0;	// スコアの初期化

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	UnloadTexture("data/TEXTURE/other_effect/number.png");

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	//有効化フラグがONなら描画する
	if (g_Use)
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));

		// 桁数分処理する
		int number = g_Score;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// 今回表示する桁の数字
			float x = (float)(number % 10);

			// スコアの位置やテクスチャー座標を反映
			float px = g_Pos.x - g_w * i;	// プレイヤーの表示位置X
			float py = g_Pos.y;			// プレイヤーの表示位置Y
			float pw = g_w;				// プレイヤーの表示幅
			float ph = g_h;				// プレイヤーの表示高さ

			float tw = 1.0f / 10;		// テクスチャの幅
			float th = 1.0f / 1;		// テクスチャの高さ
			float tx = x * tw;			// テクスチャの左上X座標
			float ty = 0.0f;			// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSprite(g_TexNo, px, py, pw, ph, tx, ty, tw, th);

			// 次の桁へ
			number /= 10;
		}

		// 桁数分処理する
		int number2 = g_Score2;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// 今回表示する桁の数字
			float x = (float)(number2 % 10);

			// スコアの位置やテクスチャー座標を反映
			float px = g_Pos.x - g_w * i;	// プレイヤーの表示位置X
			float py = g_Pos.y + 40.0f * 2;			// プレイヤーの表示位置Y
			float pw = g_w;				// プレイヤーの表示幅
			float ph = g_h;				// プレイヤーの表示高さ

			float tw = 1.0f / 10;		// テクスチャの幅
			float th = 1.0f / 1;		// テクスチャの高さ
			float tx = x * tw;			// テクスチャの左上X座標
			float ty = 0.0f;			// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSprite(g_TexNo, px, py, pw, ph, tx, ty, tw, th);

			// 次の桁へ
			number2 /= 10;
		}


		// 桁数分処理する
		int number3 = g_Score3;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// 今回表示する桁の数字
			float x = (float)(number3 % 10);

			// スコアの位置やテクスチャー座標を反映
			float px = g_Pos.x - g_w * i;	// プレイヤーの表示位置X
			float py = g_Pos.y + 40.0f * 3;			// プレイヤーの表示位置Y
			float pw = g_w;				// プレイヤーの表示幅
			float ph = g_h;				// プレイヤーの表示高さ

			float tw = 1.0f / 10;		// テクスチャの幅
			float th = 1.0f / 1;		// テクスチャの高さ
			float tx = x * tw;			// テクスチャの左上X座標
			float ty = 0.0f;			// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSprite(g_TexNo, px, py, pw, ph, tx, ty, tw, th);

			// 次の桁へ
			number3 /= 10;
		}


		// 打ち出すパワーの表示
		// 桁数分処理する
		int ShotPowerNumber = g_ShotPower;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// 今回表示する桁の数字
			float x = (float)(ShotPowerNumber % 10);

			// スコアの位置やテクスチャー座標を反映
			float px = g_Pos.x - g_w * i + 40.0f;	// プレイヤーの表示位置X
			float py = g_Pos.y + 40.0f;			// プレイヤーの表示位置Y
			float pw = g_w;				// プレイヤーの表示幅
			float ph = g_h;				// プレイヤーの表示高さ

			float tw = 1.0f / 10;		// テクスチャの幅
			float th = 1.0f / 1;		// テクスチャの高さ
			float tx = x * tw;			// テクスチャの左上X座標
			float ty = 0.0f;			// テクスチャの左上Y座標

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSprite(g_TexNo, px, py, pw, ph, tx, ty, tw, th);

			// 次の桁へ
			ShotPowerNumber /= 10;
		}
	}
}

//=============================================================================
// スコアを加算する
// 引数:add :追加する点数。マイナスも可能
//=============================================================================
void AddScore(int add)
{
	g_Score += add;

	if (g_Score > SCORE_MAX)
	{
		g_Score = SCORE_MAX;
	}
}

void SetScore(int score)
{
	g_Score = score;

	if (g_Score > SCORE_MAX)
	{
		g_Score = SCORE_MAX;
	}
}

void SetScore2(int score)
{
	g_Score2 = score;

	if (g_Score2 > SCORE_MAX)
	{
		g_Score2 = SCORE_MAX;
	}
}

void SetScore3(int score)
{
	g_Score3 = score;

	if (g_Score3 > SCORE_MAX)
	{
		g_Score3 = SCORE_MAX;
	}
}

void SetShotPower(int ShotPower)
{
	g_ShotPower = ShotPower;

	if (g_ShotPower > SCORE_MAX)
	{
		g_ShotPower = SCORE_MAX;
	}
}