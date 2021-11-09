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
#include "FileDataManagement.h"

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
static int g_AnimeSpd = 0;
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
		g_Player[i].nextpos = g_Player[i].pos;
		g_Player[i].w = PLAYER_W;
		g_Player[i].h = PLAYER_H;
		g_Player[i].use = false;


		g_Player[i].drawpos = g_Player[i].pos;
		g_Player[i].drawsize = D3DXVECTOR2(g_Player[i].w, g_Player[i].h);


		g_Player[i].act = 0;
		g_Player[i].direction = 0;
		g_Player[i].have = false;
		g_Player[i].catchwait = 0;
		g_Player[i].angle = 0.0f;
		g_Player[i].ShotPower = 0;
		g_Player[i].ConfirmAngle = false;
		g_Player[i].ConfirmCooltime = 10;

		for (int num = 0; num < ORDER_MAX; num++)
		{
			g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[num] = -1;
			g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[num] = -1;
		}
		g_Player[i].move_around = false;
		g_Player[i].move_speed = PLAYER_MOVE_SPEED;
		g_Player[i].now_array_num = 0;
		g_Player[i].order_max_num = 0;




	}

	g_Player[0].have = true;


	//初期化

	// 今は、ファイルから読み込んで設定している。SetPlayerUseFile関数
	//////////SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 100));
	//////////SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 300));
	//////////SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 500));

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
		// 前回の座標の保存
		g_Player[i].nextpos = g_Player[i].pos;

		if (GetKeyboardPress(DIK_UP))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x, g_Player[i].pos.y - 3.0f)) != 1)
				g_Player[i].nextpos.y -= 3.0f;

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
				g_Player[i].nextpos.y += 3.0f;

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
				g_Player[i].nextpos.x -= 3.0f;

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
				g_Player[i].nextpos.x += 3.0f;

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
		


		// ボールを持っていなくて、往復移動をする場合の処理。
		if (g_Player[i].have == false && g_Player[i].move_around == true)
		{
			for (int array_num = 0; array_num < g_Player[i].order_max_num; array_num++)
			{
				// 今配列の何番目の移動をしているかを検索している(例：配列の0番目の移動をしているよ)
				if (g_Player[i].now_array_num == array_num)
				{
					// 次の配列の番号を分かりやすくしておく
					int next_array = g_Player[i].now_array_num + 1;
					if (next_array >= g_Player[i].order_max_num)
						next_array = 0;

					// どっちもtureになったら次の配列の移動へ
					bool	move_end_x = false;
					bool	move_end_y = false;

					// 実際の移動処理
					// 下向きに進むか上向きに進むか
					if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[array_num] < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array])
					{
						// 下向きに進む処理(+)
						g_Player[i].nextpos.y += g_Player[i].move_speed;
						// 移動制限の処理。
						if (g_Player[i].nextpos.y > g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2))
						{
							g_Player[i].nextpos.y = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);
							move_end_y = true;
						}
					}
					else if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[array_num] > g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array])
					{
						// 上向きに進む処理(-)
						g_Player[i].nextpos.y -= g_Player[i].move_speed;
						// 移動制限の処理。
						if (g_Player[i].nextpos.y < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2))
						{
							g_Player[i].nextpos.y = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);
							move_end_y = true;
						}
					}
					else
					{
						// == の場合
						move_end_y = true;
					}
					// 右向きに進むか左向きに進むか
					if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[array_num] < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array])
					{
						// 右向きに進む処理(+)
						g_Player[i].nextpos.x += g_Player[i].move_speed;
						//移動制限の処理。
						if (g_Player[i].nextpos.x > g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2))
						{
							g_Player[i].nextpos.x = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
							move_end_x = true;
						}
					}
					else if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[array_num] > g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array])
					{
						// 左向きに進む処理(-)
						g_Player[i].nextpos.x -= g_Player[i].move_speed;
						// 移動制限の処理。
						if (g_Player[i].nextpos.x < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2))
						{
							g_Player[i].nextpos.x = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
							move_end_x = true;
						}
					}
					else
					{
						// == の場合
						move_end_x = true;
					}

					if (move_end_x && move_end_y)
					{
						g_Player[i].now_array_num = next_array;
					}
					
					break;

				}
			}
		}

		 // nextpos(計算用のポジション)をpos(ちゃんとしたポジション)に適用
		g_Player[i].pos = g_Player[i].nextpos;

		// pos を drawpos に変換
		g_Player[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Player[i].pos.x - DRAW_GAP) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Player[i].pos.y - DRAW_GAP) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2);
		g_Player[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Player[i].pos.y - DRAW_GAP) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Player[i].pos.x - DRAW_GAP) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2);


		int dffs = 5;



		//if (g_Player[i].have == false && g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[1] != -1) {

		//	//歩きアニメーション
		//	if (g_Player[i].animewaitframe2 > 10)
		//	{
		//		if (g_Player[i].animeptn2 > 2)
		//			g_Player[i].animeptn2 = 0;

		//		g_Player[i].animewaitframe2 = 0;
		//	}
		//	g_Player[i].animewaitframe2++;

		//	if (g_Player[i].roundtrip_x == 0) {
		//		if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[1] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) < g_Player[i].pos.x) {
		//			g_Player[i].pos.x -= 1.0f;
		//			g_Player[i].direction = 1;

		//			if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[1] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) >= g_Player[i].pos.x) {
		//				g_Player[i].roundtrip_x = 1;
		//			}
		//		}
		//	}

		//	if (g_Player[i].roundtrip_y == 0) {
		//		if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[1] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) < g_Player[i].pos.y) {
		//			g_Player[i].pos.y -= 1.0f;
		//			g_Player[i].direction = 1;

		//			if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[1] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) >= g_Player[i].pos.y) {
		//				g_Player[i].roundtrip_y = 1;
		//			}
		//		}
		//	}

		//	if (g_Player[i].roundtrip_x == 1) {
		//		if (g_Player[i].pos.x < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2)) {
		//			g_Player[i].pos.x += 1.0f;
		//			g_Player[i].direction = 2;

		//			if (g_Player[i].pos.x >= g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2)) {
		//				g_Player[i].roundtrip_x = 0;
		//			}
		//		}
		//	}

		//	if (g_Player[i].roundtrip_y == 1) {
		//		if (g_Player[i].pos.y < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2)) {
		//			g_Player[i].pos.y += 1.0f;
		//			g_Player[i].direction = 2;

		//			if (g_Player[i].pos.y >= g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2)) {
		//				g_Player[i].roundtrip_y = 0;
		//			}
		//		}
		//	}
		//}
		

			////マップ1へ切り替える
			//if (GetKeyboardTrigger(DIK_L))
			//{
			//	SetCurrentMap(1);
			//}
			////マップ0へ切り替える
			//if (GetKeyboardTrigger(DIK_K))
			//{
			//	SetCurrentMap(0);
			//}


			// 弾発射
			if (g_Player[i].have == true)
			{
				if (g_Player[i].ConfirmAngle == false)
				{
					// プレイヤーの角度を変える処理,回転させる処理
					g_Player[i].angle += 6.0f;
					if (g_Player[i].angle > 360.0f)
						g_Player[i].angle = 0.0f;
					g_Player[i].direction = 0;
					if (GetKeyboardTrigger(DIK_SPACE))
					{
						g_Player[i].ConfirmAngle = true;
					}
				}

				if (g_Player[i].ConfirmAngle == true)
				{
					// クールタイムの減少
					if (g_Player[i].ConfirmCooltime >= 0)
						g_Player[i].ConfirmCooltime--;

					g_Player[i].direction = 0;
					// ShotPowerの変動の設定
					g_Player[i].ShotPower++;
					if (g_Player[i].ShotPower > 100)
						g_Player[i].ShotPower = 0;

					// 表示だけ↓scoreと同じもの
					SetShotPower(g_Player[i].ShotPower);

					if (GetKeyboardTrigger(DIK_SPACE) && g_Player[i].ConfirmCooltime < 0)
					{
						g_Player[i].catchwait = 60;
						g_Player[i].have = false;

						PlaySound(g_ShotSENo, 0);

						SetVolume(g_ShotSENo, 0.1f);

						D3DXVECTOR2 pos = g_Player[i].pos;
						SetBullet(pos, g_Player[i].angle, g_Player[i].ShotPower);
					}

				}
			}

			if (g_Player[i].catchwait > 0)
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
					// ShotPowerによる倍率
					float ShotBairitu = 0.5f + (g_Player[i].ShotPower / 100.0f);

					DrawSpriteColorRotate(tex_yazirushi, g_Player[i].drawpos.x, g_Player[i].drawpos.y, 500.0f * ShotBairitu, 500.0f * ShotBairitu,
						0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
				}

				//DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].w, g_Player[i].h,
				//	g_Player[i].animeptn2 * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

				DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].w, g_Player[i].h,
					g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

				// 上から見た時の表示
				// 矢印の描写
				if (g_Player[i].have == true)
				{
					// ShotPowerによる倍率
					float ShotBairitu = 0.5f + (g_Player[i].ShotPower / 100.0f);

					DrawSpriteColorRotate(tex_yazirushi, g_Player[i].pos.x, g_Player[i].pos.y, 500.0f * ShotBairitu, 500.0f * ShotBairitu,
						0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
				}

				//DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
				//	g_Player[i].animeptn2 * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

				DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
					g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			}
		}
	}

	//=============================================================================
	// プレイヤー構造体の先頭アドレスを取得
	//=============================================================================
	PLAYER* GetPlayer(void)
	{
		return &g_Player[0];
	}


	void SetPlayer(D3DXVECTOR2 pos)
	{
		// もし未使用のプレイヤーがいなかったら追加できない。
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			if (g_Player[i].use == false)		// 未使用状態のプレイヤーを見つける
			{
				g_Player[i].use = true;			// 使用状態へ変更する
				g_Player[i].pos = pos;			// 座標をセット
				g_Player[i].h = PLAYER_H;
				g_Player[i].w = PLAYER_W;

				return;							// 1発セットしたので終了する
			}
		}
	}

	// 構造体をポインタではなく普通に受け取ると中身は上書きできない。参照はできる。
	void SetPlayerUseFile(MAPCHIP_POS_STRUCT Receive_Mapchip_Pos_Struct, float movespeed)
	{
		// もし未使用のプレイヤーがいなかったら追加できない。
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			if (g_Player[i].use == false)		// 未使用状態のプレイヤーを見つける
			{
				// 受け取ったマップチップでの座標と往復する順番を渡す
				// 同じ構造体のものだからこうやって受け取れる
				g_Player[i].Mapchip_Pos_Struct = Receive_Mapchip_Pos_Struct;

				// 座標をセット		マップチップでの座標からちゃんとした座標へ変換
				g_Player[i].pos.x = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
				g_Player[i].pos.y = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[0] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

				// 移動する用であったら移動するかどうかをtrueへ
				if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[1] != -1)
					g_Player[i].move_around = true;

				// 初期の設定
				g_Player[i].order_max_num = 0;

				for (int order_num = 0; order_num < ORDER_MAX; order_num++)
				{
					if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[order_num] != -1)
						g_Player[i].order_max_num++;
					else
						break;
				}

				g_Player[i].move_speed = movespeed;

				g_Player[i].use = true;			// 使用状態へ変更する
				g_Player[i].h = PLAYER_H;
				g_Player[i].w = PLAYER_W;

				return;							// 1発セットしたので終了する
			}
		}
	}