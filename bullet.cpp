//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "bullet.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "bg.h"
#include "scene.h"
#include "fade.h"
#include <math.h>
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static BULLET g_Bullet[BULLET_MAX];					// バレット構造体



//double angle = 00.0;								//向かせたい角度
//
//#define BULLET_ANGLE		(angle*D3DX_PI/180)		//バレットの角度(向かせたい角度*π/180)


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	int texNo = LoadTexture("data/TEXTURE/bullet00.png");
	// バレット構造体の初期化
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use   = false;
		g_Bullet[i].w     = 50.0f;
		g_Bullet[i].h     = 50.0f;
		g_Bullet[i].pos   = D3DXVECTOR2(300, 300.0f);
		g_Bullet[i].rot   = 0.0f;
		g_Bullet[i].texNo = texNo;

		g_Bullet[i].friction = 1.0f;
		g_Bullet[i].angle = 0.0f;
		g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);	// 移動量を初期化
		g_Bullet[i].vector = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{


	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)	// このバレットが使われている？
		{								// Yes
			
			g_Bullet[i].friction *= 0.992;

			if (g_Bullet[i].friction < 0.2)
			{
				g_Bullet[i].friction = 0;
			}
			// バレットの移動処理
			g_Bullet[i].pos += g_Bullet[i].move * g_Bullet[i].friction;

			// 画面外まで進んだ？
			if (g_Bullet[i].pos.y < (0.0f - g_Bullet[i].h/2))	// 自分の大きさを考慮して画面外か判定している
			{
				g_Bullet[i].use = false;
				g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);
			}

			//
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 2)
			{
				GoalTrue();
				g_Bullet[i].use = false;
				g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);


				/*SceneTransition(SCENE_RESULT);*/
			}

			//
			if (GetKeyboardTrigger(DIK_R))
			{
				g_Bullet[i].use = false;
				g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)	// このバレットが使われている？
		{								// Yes
			//バレットの位置やテクスチャー座標を反映
			float px = g_Bullet[i].pos.x;	// バレットの表示位置X
			float py = g_Bullet[i].pos.y;	// バレットの表示位置Y
			float pw = g_Bullet[i].w;		// バレットの表示幅
			float ph = g_Bullet[i].h;		// バレットの表示高さ
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			DrawSpriteColorRotate(g_Bullet[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Bullet[i].rot);
		}
	}

}


//=============================================================================
// バレット構造体の先頭アドレスを取得
//=============================================================================
BULLET *GetBullet(void)
{
	return &g_Bullet[0];
}


//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBullet(D3DXVECTOR2 pos , float angle , int ShotPower)
{
	// ShotPowerによる倍率
	float ShotBairitu = 0.5f + (ShotPower / 100.0f);


	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == false)		// 未使用状態のバレットを見つける
		{
			g_Bullet[i].use = true;			// 使用状態へ変更する
			g_Bullet[i].pos = pos;			// 座標をセット
			// g_Bullet[i].rot = BULLET_ANGLE;	// 角度をセット

			g_Bullet[i].vector = AngleToVector2(angle);	// 角度からベクトルを設定
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * ShotBairitu * g_Bullet[i].vector.x, -BULLET_SPEED * ShotBairitu * g_Bullet[i].vector.y);	// ベクトルからmoveを設定

			return;							// 1発セットしたので終了する
		}
	}
}

D3DXVECTOR2 AngleToVector2(float angle)
{
	float radian = angle * (D3DX_PI / 180);
	return  D3DXVECTOR2(cos(radian), sin(radian));
}