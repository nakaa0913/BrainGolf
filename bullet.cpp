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
#include "primitive.h"

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
	// バレット構造体の初期化 でも実際はSetBulletで呼ぶときにそっちで値が代入される
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use   = false;
		g_Bullet[i].w     = 50.0f;
		g_Bullet[i].h     = 50.0f;
		g_Bullet[i].pos   = D3DXVECTOR2(300, 300.0f);
		g_Bullet[i].nextpos = g_Bullet[i].pos;
		g_Bullet[i].oldpos = g_Bullet[i].pos;
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
		{								
			// 前回の座標の保存
			g_Bullet[i].oldpos = g_Bullet[i].pos;


			// 摩擦とか抵抗力の計算
			//g_Bullet[i].friction *= 0.992;
			g_Bullet[i].friction *= 0.9995;

			if (g_Bullet[i].friction < 0.2)
			{
				g_Bullet[i].friction = 0;
			}
			// 移動量moveの変動の計算
			g_Bullet[i].move = g_Bullet[i].move * g_Bullet[i].friction;

			// oldposにmove等の移動を反映させてnextposとする
			g_Bullet[i].nextpos = g_Bullet[i].oldpos + g_Bullet[i].move;

			// マップとの当たり判定の計算の下準備
			int hitcount = 0;			// 四角形で当たり判定を計算したときに当たっているブロックの数
			int hitcountCorner = 0;		// 当たっているブロックの角の数
			Float2 block_min  = { 999, 999 } ;
			Float2 block_max  = { -1, -1 };
			Float2 block_last = { -1, -1 };

			// HitBlockData構造体のHitBlockDatasを初期化,今回は4個くらいしか当たらない想定。
			HitBlockData2D HitBlockDatas2D[HitBlockData2DMax]{};		// 箱だけ宣言
			for (int k = 0; k < HitBlockData2DMax; k++)					// 中身入れる
			{
				HitBlockDatas2D[k].BlockPosX = -1;
				HitBlockDatas2D[k].BlockPosY = -1;
				HitBlockDatas2D[k].CornerNum = -1;
				HitBlockDatas2D[k].isUse = false;
			}


			// マップとの当たり判定処理
			for (int y = 0; y < MAP_Y; y++)
			{
				for (int x = 0; x < MAP_X; x++)
				{
					// そのブロックが当たり判定があるブロックかどうか調べるa
					int BlockData = CheckBlockdata(x, y);
					// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
					if (BlockData == 1)
					{

					}
					
				}
			}

			





						// マップとの当たり判定処理
			//if (g_Bullet[i].pos.y < (0.0f - g_Bullet[i].h/2))	// 自分の大きさを考慮して画面外か判定している
			//{
			//	g_Bullet[i].use = false;
			//	g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);
			//}

			// ゴールに入った時の処理
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 2)
			{
				// ゴールに入った時の処理
				GoalTrue();
				g_Bullet[i].use = false;


				/*SceneTransition(SCENE_RESULT);*/
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 3)
			{
				// 加速板に乗った時の処理
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].friction = 0.999;
					/*g_Bullet[i].vector = AngleToVector2();*/
					g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * 2 * g_Bullet[i].vector.x,
						-BULLET_SPEED * 2 * g_Bullet[i].vector.y);

					g_Bullet[i].accboardcool = 60;

				}
			}
			if (g_Bullet[i].accboardcool > 0)
				g_Bullet[i].accboardcool--;

			//ワープ
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 4)
			{
				if (g_Bullet[i].warpcool <= 0)
				{
					for (int y = 0; y < MAP_Y; y++)
					{
						for (int x = 0; x < MAP_X; x++)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 5)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 60;

							}

						}
					}
				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 5)
			{
				if (g_Bullet[i].warpcool <= 0)
				{
					for (int y = 0; y < MAP_Y; y++)
					{
						for (int x = 0; x < MAP_X; x++)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 4)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 60;
							}

						}
					}
				}
			}
			if (g_Bullet[i].warpcool > 0)
				g_Bullet[i].warpcool--;

			// 最期にposにnextposを反映させる
			g_Bullet[i].pos = g_Bullet[i].nextpos;

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

			g_Bullet[i].vector = AngleToVector2(angle);	// 角度からベクトルを設定
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * ShotBairitu * g_Bullet[i].vector.x,
										  -BULLET_SPEED * ShotBairitu * g_Bullet[i].vector.y);	// ベクトルからmoveを設定

			return;							// 1発セットしたので終了する
		}
	}
}

D3DXVECTOR2 AngleToVector2(float angle)
{
	float radian = angle * (D3DX_PI / 180);
	return  D3DXVECTOR2(cos(radian), sin(radian));
}