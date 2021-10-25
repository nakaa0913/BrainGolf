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

#define PLAYER_H (50)
#define PLAYER_W (50)
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static PLAYER g_Player[PLAYER_MAX];
static int g_ShotSENo = 0;

static int tex_yazirushi = 0;

static float g_CharaUV = 0.0f;
static int g_AnimePtn = 0;
static int g_AnimeWaitFrame = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	//テクスチャ読み込み
	

	//
	g_ShotSENo = LoadSound("data/SE/shot000.wav");
	tex_yazirushi = LoadTexture("data/TEXTURE/yazirusi.png");

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_Player[i].texNo = LoadTexture("data/TEXTURE/majo.png");

		g_Player[i].pos.x = SCREEN_WIDTH / 2;
		g_Player[i].pos.y = 440;
		g_Player[i].w = PLAYER_W;
		g_Player[i].h = PLAYER_H;
		g_Player[i].use = false;

		g_Player[i].act = 0;
		g_Player[i].direction = 0;
		g_Player[i].have = false;
		g_Player[i].catchwait = 0;
		g_Player[i].angle = 0.0f;
		g_Player[i].ShotPower = 0;
	}

	g_Player[0].have = true;


	//初期化

	SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 100));
	SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 300));
	SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 500));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	BULLET bullet = *GetBullet();

	for (int i = 0; i < PLAYER_MAX; i++)
	{


		if (GetKeyboardPress(DIK_UP))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x, g_Player[i].pos.y - 3.0f)) != 1)
				g_Player[i].pos.y -= 3.0f;

			g_Player[i].direction = 3;
			//g_CharaUV = 0.75f;

			//歩きアニメーション
			if (g_AnimeWaitFrame > 10)
			{
				g_AnimePtn++;
				if (g_AnimePtn > 2)
					g_AnimePtn = 0;

				g_AnimeWaitFrame = 0;
			}
			g_AnimeWaitFrame++;
		}

		if (GetKeyboardPress(DIK_DOWN))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x, g_Player[i].pos.y + 3.0f)) != 1)
				g_Player[i].pos.y += 3.0f;

			g_Player[i].direction = 0;
			//g_CharaUV = 0.0f;

			//歩きアニメーション
			if (g_AnimeWaitFrame > 10)
			{
				g_AnimePtn++;
				if (g_AnimePtn > 2)
					g_AnimePtn = 0;

				g_AnimeWaitFrame = 0;
			}
			g_AnimeWaitFrame++;
		}

		if (GetKeyboardPress(DIK_LEFT))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x - 3.0f, g_Player[i].pos.y)) != 1)
				g_Player[i].pos.x -= 3.0f;

			g_Player[i].direction = 1;
			//g_CharaUV = 0.25f;

			//歩きアニメーション
			if (g_AnimeWaitFrame > 10)
			{
				g_AnimePtn++;
				if (g_AnimePtn > 2)
					g_AnimePtn = 0;

				g_AnimeWaitFrame = 0;
			}
			g_AnimeWaitFrame++;
		}

		if (GetKeyboardPress(DIK_RIGHT))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x + 3.0f, g_Player[i].pos.y)) != 1)
				g_Player[i].pos.x += 3.0f;

			g_Player[i].direction = 2;
			//g_CharaUV = 0.5f;

			//歩きアニメーション
			if (g_AnimeWaitFrame > 10)
			{
				g_AnimePtn++;
				if (g_AnimePtn > 2)
					g_AnimePtn = 0;

				g_AnimeWaitFrame = 0;
			}
			g_AnimeWaitFrame++;
		}

		//マップ1へ切り替える
		if (GetKeyboardTrigger(DIK_L))
		{
			SetCurrentMap(1);
		}
		//マップ0へ切り替える
		if (GetKeyboardTrigger(DIK_K))
		{
			SetCurrentMap(0);
		}


		// 弾発射
		if (g_Player[i].have == true)
		{
			// プレイヤーの角度を変える処理,回転させる処理
			g_Player[i].angle += 6.0f;
			if (g_Player[i].angle > 360.0f)
				g_Player[i].angle = 0.0f;
			g_Player[i].direction = 2;

			g_Player[i].ShotPower++;
			if (g_Player[i].ShotPower > 100)
				g_Player[i].ShotPower = 0;

			SetShotPower(g_Player[i].ShotPower);

			if (GetKeyboardTrigger(DIK_SPACE))
			{
				g_Player[i].catchwait = 60;
				g_Player[i].have = false;

				PlaySound(g_ShotSENo, 0);

				SetVolume(g_ShotSENo, 0.1f);

				D3DXVECTOR2 pos = g_Player[i].pos;
				SetBullet(pos , g_Player[i].angle, g_Player[i].ShotPower);		// ここで飛ばす角度帰れるよ
				AddScore(123);
			}
		}

		if(g_Player[i].catchwait > 0)
			g_Player[i].catchwait--;

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == true)
		{
			float directionUV = 0.0f + 0.25f * g_Player[i].direction;

			float rot = AngleToRot(g_Player[i].angle);

			// 矢印の描写
			if (g_Player[i].have == true)
			{
				DrawSpriteColorRotate(tex_yazirushi, g_Player[i].pos.x, g_Player[i].pos.y, 700.0f, 700.0f,
					0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
			}

			DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
				g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
		}
	}
}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player[0];
}


void SetPlayer(D3DXVECTOR2 pos)
{
	// もし未使用の弾が無かったら発射しない( =これ以上撃てないって事 )
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == false)		// 未使用状態のバレットを見つける
		{
			g_Player[i].use = true;			// 使用状態へ変更する
			g_Player[i].pos = pos;			// 座標をセット
			g_Player[i].h = PLAYER_H;
			g_Player[i].w = PLAYER_W;

			return;							// 1発セットしたので終了する
		}
	}
}