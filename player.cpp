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
#include "camera.h"
#include "predictionbullet.h"
#include "gamedata.h"
#include "keyboard.h"
#include "placement.h"
#include "primitive.h"
#include "effect.h"
#include "gimmick_description.h"

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

int	club_pattern;			// 使うクラブ(打ち方)0が転がる、1がとぶ
int club_ChangeCool;		// クラブを持ち替えた時のクールタイム

bool mouseuse = false;

bool pausemouseuse2 = false;

bool pauseclickuse2 = false;	//ポーズ画面を開いたかどうか

int pause_cool2;		// ポーズ切り替えのクールタイム
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	//テクスチャ読み込み

	pause_cool2 = 0;
	//
	g_ShotSENo = LoadSound("data/SE/shot000.wav");
	tex_yazirushi = LoadTexture("data/TEXTURE/game/player/yazirusi.png");

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_Player[i].texNo = LoadTexture("data/TEXTURE/game/player/majo.png");

		if(i == 0)
			g_Player[i].texNo = LoadTexture("data/TEXTURE/game/player/majo2.png");

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

	club_pattern = 1;		// 使うクラブの初期設定(初期はとぶやつをもっておくことにする)



	// プレイヤー配置フェーズで配置したものを読み込んで配置する
	PLACEMENT* p_Placement = GetPlacement();

	for (int i = 0; i < PLACEMENT_MAX; i++)
	{
		if (p_Placement[i].isUse)
		{
			SetPlayerUseMapPos(p_Placement[i].placement_x, p_Placement[i].placement_y);
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	UnloadTexture("data/TEXTURE/game/player/yazirusi.png");
	UnloadTexture("data/TEXTURE/game/player/majo.png");
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//マウスの座標を取得
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();

	// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
	//int OldStageSelectX = g_StageSelect.select_x;
	//int OldStageSelectY = g_StageSelect.select_y;

	BULLET* bullet = GetBullet();
	CAMERA* p_Camera = GetCamera();
	GAMEDATA* p_Gamedata = GetGamedata();

	// 誰か一人でも持っている状態かどうか
	bool now_have = false;

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		// 前回の座標の保存
		g_Player[i].nextpos = g_Player[i].pos;

		//上
		if (Keyboard_IsKeyDown(KK_W))
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

		//下
		if (Keyboard_IsKeyDown(KK_S))
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

		//左
		if (Keyboard_IsKeyDown(KK_A))
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
		
		//右
		if (Keyboard_IsKeyDown(KK_D))
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

		// pos を drawpos に変換		DRAW_GAP は、上から見た時の描写でのマップの描写はレフトトップで、プレイヤーはど真ん中でやってるから、そのずれ。
		g_Player[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Player[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Player[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
		g_Player[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Player[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Player[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

		g_Player[i].drawsize.x = g_Player[i].w * p_Camera->magnification;
		g_Player[i].drawsize.y = g_Player[i].h * p_Camera->magnification;

		//float drawmosuepos_x = GAME_ORIGIN_POINT_X + ((mouse_pos_X + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((mouse_pos_X - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
		//float drawmosuepos_y = GAME_ORIGIN_POINT_Y + ((mouse_pos_Y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((mouse_pos_Y + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;


		//ポーズボタン 1200 700	300 300
		if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 15.0f && mouse_pos_Y < 85.0f)
		{
			//g_Pause.selectpush = 0;
			pausemouseuse2 = true;

			// マウスが表示にあっている状態で左クリックをしたら
			if (pausemouseuse2 && mouse_Lclick)
			{
				//ポーズ画面を開く
				pauseclickuse2 = true;
			}
		}

		if (pausemouseuse2 || pauseclickuse2)
		{
			//画面の360より右を押したらポーズ画面をすべて閉じる
			if (mouse_pos_X > 360.0f)
			{
				if (mouse_Lclick)
				{
					pauseclickuse2 = false;
					pausemouseuse2 = false;
					pause_cool2 = 30;
				}
			}
		}

		
			// 弾発射
			if (g_Player[i].have == true)
			{
				now_have = true;
				if (g_Player[i].ConfirmAngle == false)
				{


					// プレイヤーの角度を変える処理,回転させる処理撃つ方向を決める
					if (Keyboard_IsKeyDown(KK_LEFT))
					{
						g_Player[i].angle += 3.0f;

						if (g_Player[i].angle > 360.0f)
							g_Player[i].angle = 0.0f;
						g_Player[i].direction = 0;
						mouseuse = false;
					}

					if (Keyboard_IsKeyDown(KK_RIGHT))
					{
						g_Player[i].angle -= 3.0f;

						if (g_Player[i].angle <= 0.0f)
							g_Player[i].angle = 360.0f;
						g_Player[i].direction = 0;
						mouseuse = false;
					}

					// マウスカーソルの場所でとばす方向を決める処理
					// mouse_pos_X  mouse_pos_Y
					// マウスの座標から上から見た時の座標を出す
					// その座標とボールを持ってるプレイヤーの座標の2点間から角度を出す

					// 2分探索で徐々に検索していく








						if (mouse_Rclick)
						{
							mouseuse = true;
						}

						if (mouseuse)
						{
							Float2 more_mousepos = Getmoremousepos();

							// ①の点から②を見た時のラジアンを計算する
							float mouse_rad = CalculateRadianFrom2Points(g_Player[i].pos.x / MAP_CHIP_SIZE_X, g_Player[i].pos.y / MAP_CHIP_SIZE_Y, more_mousepos.x, more_mousepos.y);
							mouse_rad = InversionYRadian(mouse_rad);
							float mouse_angle = RadianToDegree(mouse_rad);

							g_Player[i].angle = mouse_angle;

							if (g_Player[i].angle <= 0.0f)
								g_Player[i].angle = 360.0f;
							g_Player[i].direction = 0;
						}

						// クラブを持ち変える処理
						if (club_ChangeCool <= 0)
						{
							if (Keyboard_IsKeyDown(KK_UP))
							{
								club_pattern--;
								club_ChangeCool = CLUB_CHANGECOOL;
							}
							if (Keyboard_IsKeyDown(KK_DOWN))
							{
								club_pattern++;
								club_ChangeCool = CLUB_CHANGECOOL;
							}
						}

						// クラブ持ち替えの限界処理
						if (club_pattern < 0)
							club_pattern = 1;
						if (club_pattern > 1)
							club_pattern = 0;

						//クラブの種類の表示
						if (club_pattern == 0)
						{
							SetEffect(71, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 0,
								D3DXVECTOR2(200.0f, 150.0f), D3DXVECTOR2(200.0f, 150.0f), 0,
								0.0f, 1.0f, 0, 1, 0, 0,
								0.0f, 0.0f, 0);
						}
						if (club_pattern == 1)
						{
							SetEffect(72, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 0,
								D3DXVECTOR2(200.0f, 150.0f), D3DXVECTOR2(200.0f, 150.0f), 0,
								0.0f, 1.0f, 0, 1, 0, 0,
								0.0f, 0.0f, 0);
						}
						if (pauseclickuse2 == false && pausemouseuse2 == false)
						{
						if (pause_cool2 <= 0)
						{
							//ENTERで弾だす
							if (Keyboard_IsKeyDown(KK_ENTER) || mouse_Lclick && mouseuse)
							{
								// パスした回数を増やす
								p_Gamedata->pass_count++;

								g_Player[i].catchwait = 60;
								g_Player[i].have = false;

								PlaySound(g_ShotSENo, 0);

								SetVolume(g_ShotSENo, 0.1f);

								D3DXVECTOR2 pos = g_Player[i].pos;
								SetBullet(pos, g_Player[i].angle, g_Player[i].ShotPower, club_pattern);
							}
						}
				}
			}


		}

		// クールタイムを減らす処理
		if (g_Player[i].catchwait > 0)
			g_Player[i].catchwait--;

	
	}

	if (now_have == true)
	{
		PredictionUseTrue();
	}
	else
	{
		PredictionUseFalse();
	}

	// クールタイムを減らす処理(それぞれのぷれいやーじゃないやつ(for文の外に書かないといけないやつ)
	if (club_ChangeCool > 0)
		club_ChangeCool--;

	//ポーズ画面のクールタイム
	if (pause_cool2 > 0)
		pause_cool2--;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		
	}
}


void DrawPlayerSpecifyNum(int i)
{
	CAMERA* p_Camera = GetCamera();

	float directionUV = 0.0f + 0.25f * g_Player[i].direction;

	float rot = AngleToRot(g_Player[i].angle);


	////////// とうかくずでの矢印の描写
	////////if (g_Player[i].have == true)
	////////{
	////////	// ShotPowerによる倍率
	////////	float ShotBairitu = 0.5f + (g_Player[i].ShotPower / 100.0f);

	////////	DrawSpriteColorRotate(tex_yazirushi, g_Player[i].drawpos.x, g_Player[i].drawpos.y, 500.0f * ShotBairitu * p_Camera->magnification, 500.0f * ShotBairitu * p_Camera->magnification,
	////////		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
	////////}




	// とうかくずでのプレイヤーの表示
	DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].drawsize.x, g_Player[i].drawsize.y,
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

	DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
		g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

}


// プレイヤー配置の時の描写
void DrawPlayerForPlacement(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if(g_Player[i].use == true)
		{
			float directionUV = 0.0f;		// 下向きの状態で表示

			DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x + TO_CENTER, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
				g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		}
	}
}


void DrawPlayerSpecifyNumForPlacement(int i)
{
	CAMERA* p_Camera = GetCamera();

	float directionUV = 0.0f + 0.25f * g_Player[i].direction;

	float rot = AngleToRot(g_Player[i].angle);

	// pos を drawpos に変換		DRAW_GAP は、上から見た時の描写でのマップの描写はレフトトップで、プレイヤーはど真ん中でやってるから、そのずれ。
	g_Player[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Player[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Player[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
	g_Player[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Player[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Player[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
	g_Player[i].drawsize.x = g_Player[i].w * p_Camera->magnification;
	g_Player[i].drawsize.y = g_Player[i].h * p_Camera->magnification;

	// とうかくずでのプレイヤーの表示
	DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].drawsize.x, g_Player[i].drawsize.y,
		g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

	//DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
	//	g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

}


// 引数のnum番のプレイヤーを消す
void DeletePlayer(int num)
{
	g_Player[num].use = false;

}

// 配置したプレイヤーを消す(主人公以外)
void DeletePlacementPlayer()
{
	for (int i = 1; i < PLAYER_MAX; i++)
	{
		g_Player[i].use = false;
	}
}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
PLAYER* GetPlayer(void)
{
	return &g_Player[0];
}

int GetClubPattern(void)
{
	return club_pattern;
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

void SetPlayerUseMapPos(int mappos_x, int mappos_y)
{
	// もし未使用のプレイヤーがいなかったら追加できない。主人公は除くのでi=1から
	for (int i = 1; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == false)		// 未使用状態のプレイヤーを見つける
		{
			// 座標をセット		マップチップでの座標からちゃんとした座標へ変換
			g_Player[i].pos.x = mappos_x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
			g_Player[i].pos.y = mappos_y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

			g_Player[i].use = true;			// 使用状態へ変更する

			return;							// 1発セットしたので終了する
		}
	}
	return;
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

// プレイヤー配置フェーズでのセットプレイヤー処理,戻り値でどこにプレイヤーをセットしたかを返す
int SetPlayerForPlacement(int mappos_x, int mappos_y)
{
	// もし未使用のプレイヤーがいなかったら追加できない。主人公は除くのでi=1から
	for (int i = 1; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == false)		// 未使用状態のプレイヤーを見つける
		{

			// 座標をセット		マップチップでの座標からちゃんとした座標へ変換
			g_Player[i].pos.x = mappos_x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
			g_Player[i].pos.y = mappos_y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);



			g_Player[i].h = PLAYER_H;
			g_Player[i].w = PLAYER_W;

			g_Player[i].use = true;			// 使用状態へ変更する

			return i;							// 1発セットしたので終了する
		}
	}
	return -1;
}


// 現在弾を持っているプレイヤーを返す。持っていなければ0
int returnHavePlayer()
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == true)
		{
			if (g_Player[i].have == true)
				return i;
		}
	}

	return 0;
}