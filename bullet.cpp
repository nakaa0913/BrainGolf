//=============================================================================
//
// バレット処理 [bullet.cpp]
//  Author : 
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
#include "collision.h"
#include "camera.h"
#include "gamedata.h"
#include "savedata.h"
#include "stagedata.h"
#include "sound.h"
#include "FileDataManagement.h"
#include "keyboard.h"
#include "pause.h"

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
static SHADOWBULLET g_ShadowBullet[BULLET_MAX];		// バレットの影構造体

static int g_SENo = 0;								//SE識別

int needletime = 0;									//針の当たり判定の時間
int hole_changetime = 0;							//踏んだら消える床の画像の変わる時間時間
//double angle = 00.0;								//向かせたい角度
//
//#define BULLET_ANGLE		(angle*D3DX_PI/180)		//バレットの角度(向かせたい角度*π/180)
#define COLLISIONTIME (60)							//当たっている時間

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	int texNo = LoadTexture("data/TEXTURE/bullet/ao.png");
	int tex_bullet_shadow = LoadTexture("data/TEXTURE/bullet/bullet_shadow.png");

	g_SENo = 0;

	// バレット構造体の初期化 でも実際はSetBulletで呼ぶときにそっちで値が代入される
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use = false;
		g_Bullet[i].w = 20.0f;
		g_Bullet[i].h = 20.0f;
		g_Bullet[i].pos = D3DXVECTOR2(300, 300.0f);
		g_Bullet[i].nextpos = g_Bullet[i].pos;
		g_Bullet[i].oldpos = g_Bullet[i].pos;

		g_Bullet[i].flying_height = 0.0f;
		g_Bullet[i].on_the_ground = true;

		g_Bullet[i].drawpos = g_Bullet[i].pos;
		g_Bullet[i].drawsize = D3DXVECTOR2(g_Bullet[i].w, g_Bullet[i].h);

		g_Bullet[i].rot = 0.0f;
		g_Bullet[i].texNo = texNo;

		g_Bullet[i].friction = 1.0f;
		g_Bullet[i].angle = 0.0f;
		g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);	// 移動量を初期化
		g_Bullet[i].vector = D3DXVECTOR2(1.0f, 1.0f);

		g_Bullet[i].CollicionCool = 0;

		g_Bullet[i].shottime = 0;
		g_Bullet[i].collisiontime = 0;

		g_Bullet[i].onswitch = false;
		g_Bullet[i].switchcool = 0;
		g_Bullet[i].holecool = 0;
		g_Bullet[i].hole_changetime = 0;
		// バレットの影構造体の初期化
		g_ShadowBullet[i].w = g_Bullet[i].w;
		g_ShadowBullet[i].h = g_Bullet[i].h;
		g_ShadowBullet[i].pos = g_Bullet[i].pos;

		g_ShadowBullet[i].drawpos = g_Bullet[i].pos;
		g_ShadowBullet[i].drawsize = D3DXVECTOR2(g_Bullet[i].w, g_Bullet[i].h);

		g_ShadowBullet[i].tex = tex_bullet_shadow;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	UnloadTexture("data/TEXTURE/bullet/ao.png");
	UnloadTexture("data/TEXTURE/bullet/bullet_shadow.png");
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	CAMERA* p_Camera = GetCamera();
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();
	GAMEDATA* p_Gamedata = GetGamedata();

	int axis_x;
	int axis_y;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		//画像入れ替え処理
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				// そのブロックが当たり判定があるブロックかどうか調べるa
				int BlockData = CheckBlockdata(x, y);

				////////針の画像入れ替え処理////////
				if (p_Stagedata->maparray[y][x] == 16)
				{
					//240以下の時に当たるとボールを止める
					if (needletime <= 240)
					{
						p_Stagedata->maparray[y][x] = 17;
					}
				}
				if (p_Stagedata->maparray[y][x] == 17)
				{
					//241以上の時に当たるとボールを止める
					if (needletime > 240)
					{
						p_Stagedata->maparray[y][x] = 16;
					}
				}
				if (p_Stagedata->maparray[y][x] == 37)
				{
					//241以上の時に当たるとボールを止める
					if (hole_changetime > 120)
					{
						p_Stagedata->maparray[y][x] = 22;
					}
				}

			}
		}

		//480以上になったらneedletimeを0にしてループさせる
		if (needletime >= 480)
		{
			needletime = 0;
		}

		if (g_Bullet[i].use == true)	// このバレットが使われている？
		{
			// 前回の座標の保存
			g_Bullet[i].oldpos = g_Bullet[i].pos;


			// 摩擦とか抵抗力の計算
			// 最初の15フレームは摩擦なし
			if (g_Bullet[i].shottime < 15)
				g_Bullet[i].friction = 1.0f;
			else
				g_Bullet[i].friction = 0.9815f;

			if (g_Bullet[i].shotpower < 0.14f)
			{
				g_Bullet[i].shotpower = 0;
			}
			// ショットパワーに抵抗力をかけて力を弱くする
			g_Bullet[i].shotpower = g_Bullet[i].shotpower * g_Bullet[i].friction;

			// 移動量moveの更新
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.x,
				-BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.y);	// ベクトルからmoveを設定


			//// デバッグ用にキー入力でもボール移動できるようにした(加速版みたいな)
			//if (Keyboard_IsKeyDown(KK_UP))
			//{
			//	g_Bullet[i].shotpower = 0.3f;								// ショットパワーを設定
			//	g_Bullet[i].angle = 90.0f;									// 角度を設定
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定
			//}
			//if (Keyboard_IsKeyDown(KK_DOWN))
			//{
			//	g_Bullet[i].shotpower = 0.3f;								// ショットパワーを設定
			//	g_Bullet[i].angle = 270.0f;									// 角度を設定
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定
			//}
			//if (Keyboard_IsKeyDown(KK_RIGHT))
			//{
			//	g_Bullet[i].shotpower = 0.3f;								// ショットパワーを設定
			//	g_Bullet[i].angle = 0.0f;									// 角度を設定
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定
			//}
			//if (Keyboard_IsKeyDown(KK_LEFT))
			//{
			//	g_Bullet[i].shotpower = 0.3f;								// ショットパワーを設定
			//	g_Bullet[i].angle = 180.0f;									// 角度を設定
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定
			//}




			// oldposにmove等の移動を反映させてnextposとする
			g_Bullet[i].nextpos = g_Bullet[i].oldpos + g_Bullet[i].move;




			// マップとの当たり判定の計算の下準備
			int hitcount = 0;			// 四角形で当たり判定を計算したときに当たっているブロックの数
			int hitcountCorner = 0;		// 当たっているブロックの角の数
			D3DXVECTOR2 block_min = D3DXVECTOR2(999, 999);
			D3DXVECTOR2 block_max = D3DXVECTOR2(-1, -1);
			D3DXVECTOR2 block_last = D3DXVECTOR2(-1, -1);

			// HitBlockData構造体のHitBlockDatasを初期化,今回は4個くらいしか当たらない想定。
			HitBlockData2D HitBlockDatas2D[HitBlockData2DMax]{};		// 箱だけ宣言
			for (int k = 0; k < HitBlockData2DMax; k++)					// 中身入れる
			{
				HitBlockDatas2D[k].BlockPosX = -1;
				HitBlockDatas2D[k].BlockPosY = -1;
				HitBlockDatas2D[k].CornerNum = -1;
				HitBlockDatas2D[k].isUse = false;
			}

			// CollicionCool中なら当たり判定の判定を行わない
			if (g_Bullet[i].CollicionCool <= 0)
			{


				// マップとの当たり判定処理
				for (int y = 0 - 1; y < MAP_Y + 1; y++)
				{
					for (int x = 0 - 1; x < MAP_X + 1; x++)
					{
						// そのブロックが当たり判定があるブロックかどうか調べる
						int BlockData;
						// 外周のブロックの場合は壁ブロックを設定する。-1の部分はここで描写、+1の部分は透明の設定もあるので後で描写
						if (x == -1 || y == -1 || x == MAP_X || y == MAP_Y)
						{
							BlockData = 1;
						}
						else
						{
							BlockData = CheckBlockdata(x, y);
						}

						// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
						if (BlockData == 1)
						{
							// ブロックの4隅の座標の保存
							D3DXVECTOR2 LU_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X - (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y - (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 RU_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y - (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 LD_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X - (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 RD_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));

							// 最初は四角で当たり判定を調べる、必須。そこから当たってるであろうことを調べる。
							if (CheckHit(D3DXVECTOR2(g_Bullet[i].nextpos.x - (g_Bullet[i].w / 2), g_Bullet[i].nextpos.y - (g_Bullet[i].h / 2)), D3DXVECTOR2(g_Bullet[i].w, g_Bullet[i].h),
								D3DXVECTOR2(x * MAP_CHIP_SIZE_X, y * MAP_CHIP_SIZE_Y), D3DXVECTOR2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y)) == true
								)
							{
								// ヒットカウントを増やし、当たっているブロックの最大値と最低値を保存する
								hitcount++;
								block_last.x = x;
								block_last.y = y;

								if (x > block_max.x) block_max.x = x;
								if (x < block_min.x) block_min.x = x;
								if (y > block_max.y) block_max.y = y;
								if (y < block_min.y) block_min.y = y;

								// 四隅はまだわからないけど当たっているので入れておく
								for (int k = 0; k < HitBlockData2DMax; k++)			// 使われていないものにいれていく
								{
									if (HitBlockDatas2D[k].isUse == false)
									{
										HitBlockDatas2D[k].BlockPosX = x;
										HitBlockDatas2D[k].BlockPosY = y;
										// HitBlockDatas2D[k].CornerNum = corner;
										// HitBlockDatas2D[k].isUse = true;		// 使われてる状態にはまだしない。
										break;									// 登録したので抜ける
									}
								}

								// 円の当たり判定と、四つ角のどこに当たっているかを調べる
								for (int corner = 0; corner < 4; corner++)
								{
									D3DXVECTOR2 point_pos = D3DXVECTOR2(0.0f, 0.0f);
									if (corner == 0)
									{
										point_pos = LU_block;
									}
									if (corner == 1)
									{
										point_pos = RU_block;
									}
									if (corner == 2)
									{
										point_pos = LD_block;
									}
									if (corner == 3)
									{
										point_pos = RD_block;
									}

									// 円の情報の整理(Bullet)
									Circle2D BulletCircle = {
										g_Bullet[i].nextpos.x,
										g_Bullet[i].nextpos.y,
										g_Bullet[i].w / 2,		// 半径だから横幅の半分
									};
									// 点の情報の整理(ブロックの角)
									Float2 CornerPoint = {
										point_pos.x,
										point_pos.y,
									};
									// 円と４つ角のどこが当たっているか調べる
									if (OnCollisionPointAndCircle(CornerPoint, BulletCircle) == true)
									{
										// ChangeMapdata(2, x, y);

										// 円の当たり判定で当たっている場合
										// 当たっているブロックの保存
										hitcountCorner++;

										for (int k = 0; k < HitBlockData2DMax; k++)			// 使われていないものにいれていく
										{
											if (HitBlockDatas2D[k].isUse == false)
											{
												HitBlockDatas2D[k].BlockPosX = x;
												HitBlockDatas2D[k].BlockPosY = y;
												HitBlockDatas2D[k].CornerNum = corner;
												HitBlockDatas2D[k].isUse = true;			// 使われてる状態にする
												break;									// 登録したので抜ける
											}
										}







									}
								}

							}

						}
						//赤いブロック
						if (BlockData == 19)
						{
							// ブロックの4隅の座標の保存
							D3DXVECTOR2 LU_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X - (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y - (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 RU_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y - (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 LD_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X - (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 RD_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));

							// 最初は四角で当たり判定を調べる、必須。そこから当たってるであろうことを調べる。
							if (CheckHit(D3DXVECTOR2(g_Bullet[i].nextpos.x - (g_Bullet[i].w / 2), g_Bullet[i].nextpos.y - (g_Bullet[i].h / 2)), D3DXVECTOR2(g_Bullet[i].w, g_Bullet[i].h),
								D3DXVECTOR2(x * MAP_CHIP_SIZE_X, y * MAP_CHIP_SIZE_Y), D3DXVECTOR2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y)) == true
								)
							{
								// ヒットカウントを増やし、当たっているブロックの最大値と最低値を保存する
								hitcount++;
								block_last.x = x;
								block_last.y = y;

								if (x > block_max.x) block_max.x = x;
								if (x < block_min.x) block_min.x = x;
								if (y > block_max.y) block_max.y = y;
								if (y < block_min.y) block_min.y = y;

								// 四隅はまだわからないけど当たっているので入れておく
								for (int k = 0; k < HitBlockData2DMax; k++)			// 使われていないものにいれていく
								{
									if (HitBlockDatas2D[k].isUse == false)
									{
										HitBlockDatas2D[k].BlockPosX = x;
										HitBlockDatas2D[k].BlockPosY = y;
										// HitBlockDatas2D[k].CornerNum = corner;
										// HitBlockDatas2D[k].isUse = true;		// 使われてる状態にはまだしない。
										break;									// 登録したので抜ける
									}
								}

								// 円の当たり判定と、四つ角のどこに当たっているかを調べる
								for (int corner = 0; corner < 4; corner++)
								{
									D3DXVECTOR2 point_pos = D3DXVECTOR2(0.0f, 0.0f);
									if (corner == 0)
									{
										point_pos = LU_block;
									}
									if (corner == 1)
									{
										point_pos = RU_block;
									}
									if (corner == 2)
									{
										point_pos = LD_block;
									}
									if (corner == 3)
									{
										point_pos = RD_block;
									}

									// 円の情報の整理(Bullet)
									Circle2D BulletCircle = {
										g_Bullet[i].nextpos.x,
										g_Bullet[i].nextpos.y,
										g_Bullet[i].w / 2,		// 半径だから横幅の半分
									};
									// 点の情報の整理(ブロックの角)
									Float2 CornerPoint = {
										point_pos.x,
										point_pos.y,
									};
									// 円と４つ角のどこが当たっているか調べる
									if (OnCollisionPointAndCircle(CornerPoint, BulletCircle) == true)
									{
										// ChangeMapdata(2, x, y);

										// 円の当たり判定で当たっている場合
										// 当たっているブロックの保存
										hitcountCorner++;

										for (int k = 0; k < HitBlockData2DMax; k++)			// 使われていないものにいれていく
										{
											if (HitBlockDatas2D[k].isUse == false)
											{
												HitBlockDatas2D[k].BlockPosX = x;
												HitBlockDatas2D[k].BlockPosY = y;
												HitBlockDatas2D[k].CornerNum = corner;
												HitBlockDatas2D[k].isUse = true;			// 使われてる状態にする
												break;									// 登録したので抜ける
											}
										}







									}
								}

							}

						}
						//青いブロック
						if (BlockData == 35)
						{
							// ブロックの4隅の座標の保存
							D3DXVECTOR2 LU_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X - (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y - (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 RU_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y - (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 LD_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X - (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));
							D3DXVECTOR2 RD_block = D3DXVECTOR2(x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) + (MAP_CHIP_SIZE_X / 2), y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) + (MAP_CHIP_SIZE_Y / 2));

							// 最初は四角で当たり判定を調べる、必須。そこから当たってるであろうことを調べる。
							if (CheckHit(D3DXVECTOR2(g_Bullet[i].nextpos.x - (g_Bullet[i].w / 2), g_Bullet[i].nextpos.y - (g_Bullet[i].h / 2)), D3DXVECTOR2(g_Bullet[i].w, g_Bullet[i].h),
								D3DXVECTOR2(x * MAP_CHIP_SIZE_X, y * MAP_CHIP_SIZE_Y), D3DXVECTOR2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y)) == true
								)
							{
								// ヒットカウントを増やし、当たっているブロックの最大値と最低値を保存する
								hitcount++;
								block_last.x = x;
								block_last.y = y;

								if (x > block_max.x) block_max.x = x;
								if (x < block_min.x) block_min.x = x;
								if (y > block_max.y) block_max.y = y;
								if (y < block_min.y) block_min.y = y;

								// 四隅はまだわからないけど当たっているので入れておく
								for (int k = 0; k < HitBlockData2DMax; k++)			// 使われていないものにいれていく
								{
									if (HitBlockDatas2D[k].isUse == false)
									{
										HitBlockDatas2D[k].BlockPosX = x;
										HitBlockDatas2D[k].BlockPosY = y;
										// HitBlockDatas2D[k].CornerNum = corner;
										// HitBlockDatas2D[k].isUse = true;		// 使われてる状態にはまだしない。
										break;									// 登録したので抜ける
									}
								}

								// 円の当たり判定と、四つ角のどこに当たっているかを調べる
								for (int corner = 0; corner < 4; corner++)
								{
									D3DXVECTOR2 point_pos = D3DXVECTOR2(0.0f, 0.0f);
									if (corner == 0)
									{
										point_pos = LU_block;
									}
									if (corner == 1)
									{
										point_pos = RU_block;
									}
									if (corner == 2)
									{
										point_pos = LD_block;
									}
									if (corner == 3)
									{
										point_pos = RD_block;
									}

									// 円の情報の整理(Bullet)
									Circle2D BulletCircle = {
										g_Bullet[i].nextpos.x,
										g_Bullet[i].nextpos.y,
										g_Bullet[i].w / 2,		// 半径だから横幅の半分
									};
									// 点の情報の整理(ブロックの角)
									Float2 CornerPoint = {
										point_pos.x,
										point_pos.y,
									};
									// 円と４つ角のどこが当たっているか調べる
									if (OnCollisionPointAndCircle(CornerPoint, BulletCircle) == true)
									{
										// ChangeMapdata(2, x, y);

										// 円の当たり判定で当たっている場合
										// 当たっているブロックの保存
										hitcountCorner++;

										for (int k = 0; k < HitBlockData2DMax; k++)			// 使われていないものにいれていく
										{
											if (HitBlockDatas2D[k].isUse == false)
											{
												HitBlockDatas2D[k].BlockPosX = x;
												HitBlockDatas2D[k].BlockPosY = y;
												HitBlockDatas2D[k].CornerNum = corner;
												HitBlockDatas2D[k].isUse = true;			// 使われてる状態にする
												break;									// 登録したので抜ける
											}
										}







									}
								}

							}

						}
					}
				}
			}

			// 円の情報の整理計算用(Bullet)
			Circle2D BulletCircle = {
				g_Bullet[i].nextpos.x,
				g_Bullet[i].nextpos.y,
				g_Bullet[i].w / 2,		// 半径だから横幅の半分
			};

			// 当たっているブロックが0以上かつ1こ単体の場合の処理
			if (hitcount == 1)
			{
				int OriginLengthAndWidthPos = -1;					// -1:Nohit,:0:左,1:右,2:上,3:下,円の原点が縦横4方向のどこに位置するか
				int OriginCornerPos = -1;							// -1:Nohit,:0:左上,1:右上,2:左下,3:右下,円の原点が斜め4方向のどこに位置するか
				// 円の原点の場所によって処理を変える
				// ①円の原点がブロックの縦横4方向のどこに位置するかの処理
				if (BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f)
				{
					if (BulletCircle.y > HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f && BulletCircle.y < HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginLengthAndWidthPos = 0;
				}
				if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y > HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f && BulletCircle.y < HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginLengthAndWidthPos = 1;
				}
				if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y < HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f)
						OriginLengthAndWidthPos = 2;
				}
				if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y > HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginLengthAndWidthPos = 3;
				}
				// ②円の原点がブロックの斜め4方向のどこに位置するかの処理
				if (BulletCircle.x <= HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f)
				{
					if (BulletCircle.y <= HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f)
						OriginCornerPos = 0;
				}
				if (BulletCircle.x >= HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y <= HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f)
						OriginCornerPos = 1;
				}
				if (BulletCircle.x <= HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f)
				{
					if (BulletCircle.y >= HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginCornerPos = 2;
				}
				if (BulletCircle.x >= HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
				{
					if (BulletCircle.y >= HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
						OriginCornerPos = 3;
				}

				// 計算でnextposを変える
				if (OriginLengthAndWidthPos != -1)
				{
					if (OriginLengthAndWidthPos == 0)
					{
						g_Bullet[i].nextpos.x = HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f - (g_Bullet[i].w / 2);
						////g_Bullet[i].move.x *= -1;
						//g_Bullet[i].vector.x *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, HitBlockDatas2D[0].BlockPosX* MAP_CHIP_SIZE_X + 0.0f, g_Bullet[i].nextpos.y);
						InversionVecAng(i, 0);
						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}
					if (OriginLengthAndWidthPos == 1)
					{
						g_Bullet[i].nextpos.x = HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X + (g_Bullet[i].w / 2);
						////g_Bullet[i].move.x *= -1;
						//g_Bullet[i].vector.x *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, HitBlockDatas2D[0].BlockPosX* MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X, g_Bullet[i].nextpos.y);
						InversionVecAng(i, 0);

						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}
					if (OriginLengthAndWidthPos == 2)
					{
						g_Bullet[i].nextpos.y = HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f - (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, HitBlockDatas2D[0].BlockPosY* MAP_CHIP_SIZE_Y + 0.0f);
						InversionVecAng(i, 1);

						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}
					if (OriginLengthAndWidthPos == 3)
					{
						g_Bullet[i].nextpos.y = HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y + (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, HitBlockDatas2D[0].BlockPosY* MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y);
						InversionVecAng(i, 1);

						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}
				}

				// ブロックの斜め４方向に位置する場合の処理。ここではブロック１個の時なので必ず角が当たっている。から円での計算をする
				if (OriginCornerPos != -1)
				{
					bool hit = false;
					float distance;
					Float2 finpos;
					Float2 movedistance;
					float ratio;

					int BigMagnification = 10000;		// 誤差を減らすための倍率

					// 誤差を減らすために大きくした円の情報の整理計算用(Bullet)
					Circle2D BigBulletCircle = {
						BulletCircle.x * BigMagnification,
						BulletCircle.y * BigMagnification,
						BulletCircle.r * BigMagnification,
					};

					Point2D BigCornerPoint;

					// ブロックでの座標からちゃんとした座標に変換する
					if (HitBlockDatas2D[0].CornerNum == 0)
					{
						BigCornerPoint.x = (HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f) * BigMagnification;
						BigCornerPoint.y = (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f) * BigMagnification;
						BigCornerPoint.corner = 0;
					}
					if (HitBlockDatas2D[0].CornerNum == 1)
					{
						BigCornerPoint.x = (HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X) * BigMagnification;
						BigCornerPoint.y = (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f) * BigMagnification;
						BigCornerPoint.corner = 1;
					}
					if (HitBlockDatas2D[0].CornerNum == 2)
					{
						BigCornerPoint.x = (HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f) * BigMagnification;
						BigCornerPoint.y = (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y) * BigMagnification;
						BigCornerPoint.corner = 2;
					}
					if (HitBlockDatas2D[0].CornerNum == 3)
					{
						BigCornerPoint.x = (HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X) * BigMagnification;
						BigCornerPoint.y = (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y) * BigMagnification;
						BigCornerPoint.corner = 3;
					}


					// ここから計算
					distance = CalculationDistance(BigBulletCircle.x, BigBulletCircle.y, BigCornerPoint.x, BigCornerPoint.y);
					if (distance <= BigBulletCircle.r)
						hit = true;

					ratio = CalculationRatio(distance, BigBulletCircle.r, BigMagnification);
					finpos = { BigCornerPoint.x * BigMagnification / ratio, BigCornerPoint.y * BigMagnification / ratio };
					movedistance = { finpos.x - BigCornerPoint.x, finpos.y - BigCornerPoint.y };
					movedistance = { fabsf(movedistance.x), fabsf(movedistance.y) };

					if (hit)
					{
						int divnum = 10;		// 分割数
						Float2 onemove{ -1, -1 };
						if (OriginCornerPos == 0)
						{
							onemove = { -movedistance.x / divnum, -movedistance.y / divnum };	// 下のMoreAccuratePos関数は10分割にしたものを

						}
						if (OriginCornerPos == 1)
						{
							onemove = { movedistance.x / divnum, -movedistance.y / divnum };
						}
						if (OriginCornerPos == 2)
						{
							onemove = { -movedistance.x / divnum, movedistance.y / divnum };
						}
						if (OriginCornerPos == 3)
						{
							onemove = { movedistance.x / divnum, movedistance.y / divnum };
						}
						// より正確にするために分割数で割った数の中から最も正確なposに移動させる。そして誤差計算のための10000で割る
						Float2 newpos = MoreAccurateCircleCollision(BigBulletCircle.x, BigBulletCircle.y, BigBulletCircle.r, BigCornerPoint.x, BigCornerPoint.y, onemove, divnum);
						g_Bullet[i].nextpos.x = newpos.x / BigMagnification;
						g_Bullet[i].nextpos.y = newpos.y / BigMagnification;

						// 当たっているブロックの真ん中の座標を求める
						float HitBlockCenterPosX = HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
						float HitBlockCenterPosY = HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);
						// 当たっているブロックの角までの差を出す
						float difference_CornerPosX = CalculateCornerDistanceX(HitBlockDatas2D[0].CornerNum, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y);
						float difference_CornerPosY = CalculateCornerDistanceY(HitBlockDatas2D[0].CornerNum, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y);
						// 当たっているブロックの角の座標を出す
						float CornerPosX = HitBlockCenterPosX + difference_CornerPosX;
						float CornerPosY = HitBlockCenterPosY + difference_CornerPosY;

						// 値の更新をさせる。
						CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, CornerPosX, CornerPosY);

					}


				}



			}
			else if (hitcount > 0 && hitcount <= 4)
			{
				// ブロックに当たっており、かつ2個以上かつ4個以下の場合の場合
				// x座標のブロックに完全に左右どちらかからあたっている場合
				if (block_min.x == block_max.x)
				{
					int LeftorRight = -1;
					// 左右どちらからあたっているのかを調べる
					// ①円の原点がブロックの縦横4方向のどこに位置するかの処理
					if (BulletCircle.x < block_min.x * MAP_CHIP_SIZE_X + 0.0f)
					{
						// バレットはブロックの左側から右側に向かって進んでいて衝突したのでブロックの左側にnextposを固定し、左に向かって反射させる
						LeftorRight = 0;
						g_Bullet[i].nextpos.x = block_min.x * MAP_CHIP_SIZE_X + 0.0f - (g_Bullet[i].w / 2);
						////g_Bullet[i].move.x *= -1;
						//g_Bullet[i].vector.x *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, block_min.x* MAP_CHIP_SIZE_X + 0.0f, g_Bullet[i].nextpos.y);
						InversionVecAng(i, 0);

						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}
					if (BulletCircle.x > block_min.x * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
					{
						// バレットはブロックの右側から左側に向かって進んでいて衝突したのでブロックの右側にnextposを固定し、右に向かって反射させる
						LeftorRight = 1;
						g_Bullet[i].nextpos.x = block_min.x * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X + (g_Bullet[i].w / 2);
						////g_Bullet[i].move.x *= -1;
						//g_Bullet[i].vector.x *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, block_min.x* MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X, g_Bullet[i].nextpos.y);
						InversionVecAng(i, 0);

						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}

					if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
					{
						if (BulletCircle.y < HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f)
							LeftorRight = 2;

						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}
					if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
					{
						if (BulletCircle.y > HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
							LeftorRight = 3;

						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}

				}
				// x座標のブロックに完全に上下どちらかからあたっている場合
				if (block_min.y == block_max.y)
				{
					if (BulletCircle.y < block_min.y * MAP_CHIP_SIZE_Y + 0.0f)
					{
						// バレットはブロックの上側から下側に向かって進んでいて衝突したのでブロックの上側にnextposを固定し、上に向かって反射させる
						g_Bullet[i].nextpos.y = block_min.y * MAP_CHIP_SIZE_Y + 0.0 - (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, block_min.y* MAP_CHIP_SIZE_Y + 0.0);
						InversionVecAng(i, 1);
						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}
					if (BulletCircle.y > block_min.y * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
					{
						// バレットはブロックの下側から上側に向かって進んでいて衝突したのでブロックの下側にnextposを固定し、下に向かって反射させる
						g_Bullet[i].nextpos.y = block_min.y * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y + (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, block_min.y* MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y);
						InversionVecAng(i, 1);
						g_SENo = LoadSound("data/SE/Accent44-1.wav");
						PlaySound(g_SENo, 0);
					}
				}

			}

			//ゲームオーバー処理
			if (g_Bullet[i].shotpower <= 0)
			{
				if (g_Bullet[i].shottime >= 120)
				{
					StopSoundAll();
					GameoverTrue();
					GameoverTrue_Pause();
				}

			}


			//ボールが地面にいるときだけ当たり判定（2回のバウンドと3回目のバウンドからは常に当たり判定がある）
			bool ground = false;	// ボールが地面についているかどうか
			if (g_Bullet[i].club_pattern == 0 ||
				g_Bullet[i].shottime == 28 || g_Bullet[i].shottime == 57 || g_Bullet[i].shottime >= 81)
				ground = true;

			// 地面に当たっているときにしか続行されない者たち
			if (ground == true)
			{
				// マップとの当たり判定処理

				// ゴールに入った時の処理
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y)) == 2)
				{
					// ゴールに入った時の処理
					GoalTrue();
					GoalTrue_Pause();
					bool updata_savedata = false;

					// ミッションをクリアしているかどうかの処理。新たにクリアしていた場合のみ更新する
					for (int missionnum = 0; missionnum < MAX_MISSION; missionnum++)
					{
						if (JudgeClearMission(missionnum) == true)
						{
							// クリアしていて更新があった場合セーブデータ構造体を変更する
							p_Savedata[p_Stagedata->stagenum].mission_clear[missionnum] = 1;
							updata_savedata = true;
						}
					}
					// クリアタイムが更新されたら
					if (p_Gamedata->game_time < p_Savedata[p_Stagedata->stagenum].clear_time)
					{
						// クリアしていて更新があった場合セーブデータ構造体を変更する
						p_Savedata[p_Stagedata->stagenum].clear_time = p_Gamedata->game_time;
						updata_savedata = true;
					}
					// セーブデータの更新があったならば、テキストも更新する
					if (updata_savedata == true)
					{
						// テキストファイルを書き換える
						WriteSavedata(SAVEDATA_FILE);
					}
				}

				//砂
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 13)
				{
					// パワーを減衰させる
					if (g_Bullet[i].shotpower > 0.3f)
						g_Bullet[i].shotpower = 0.3f;

				}

				//当たってる間trueになる
				bool collision_accboard = false;
				//どの番号に当たっているか
				int collision_num = -1;

				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 3)
				{
					collision_accboard = true;
					collision_num = 3;
				}
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 4)
				{
					collision_accboard = true;
					collision_num = 4;
				}
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 5)
				{
					collision_accboard = true;
					collision_num = 5;
				}
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 6)
				{
					collision_accboard = true;
					collision_num = 6;
				}
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 7)
				{
					collision_accboard = true;
					collision_num = 7;
				}
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 8)
				{
					collision_accboard = true;
					collision_num = 8;
				}
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 9)
				{
					collision_accboard = true;
					collision_num = 9;
				}
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 10)
				{
					collision_accboard = true;
					collision_num = 10;
				}

				//連続して当たってたらtrueになる
				if (collision_accboard == true)
				{
					g_Bullet[i].collisiontime++;
				}
				else
				{
					//当たってなかったら0にする
					g_Bullet[i].collisiontime = 0;
				}




				if (collision_num == 3)
				{
					// 加速板（上）に乗った時の処理
					if (g_Bullet[i].accboardcool <= 0)
					{
						g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
						g_Bullet[i].angle = 90.0f;									// 角度を設定
						g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

						g_Bullet[i].accboardcool = 10;

						g_SENo = LoadSound("data/SE/Shortbridge29-4.wav");
						PlaySound(g_SENo, 0);
					}
				}
				if (collision_num == 4)
				{
					// 加速板（下）に乗った時の処理
					if (g_Bullet[i].accboardcool <= 0)
					{
						g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
						g_Bullet[i].angle = 270.0f;									// 角度を設定
						g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定


						g_Bullet[i].accboardcool = 10;
						g_SENo = LoadSound("data/SE/Shortbridge29-4.wav");
						PlaySound(g_SENo, 0);
					}
				}
				if (collision_num == 5)
				{
					// 加速板（右）に乗った時の処理
					if (g_Bullet[i].accboardcool <= 0)
					{
						g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
						g_Bullet[i].angle = 0.0f;									// 角度を設定
						g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

						g_Bullet[i].accboardcool = 10;
						g_SENo = LoadSound("data/SE/Shortbridge29-4.wav");
						PlaySound(g_SENo, 0);
					}
				}
				if (collision_num == 6)
				{
					// 加速板（左）に乗った時の処理
					if (g_Bullet[i].accboardcool <= 0)
					{
						g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
						g_Bullet[i].angle = 180.0f;									// 角度を設定
						g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

						g_Bullet[i].accboardcool = 10;
						g_SENo = LoadSound("data/SE/Shortbridge29-4.wav");
						PlaySound(g_SENo, 0);
					}
				}
				if (collision_num == 7)
				{
					// 加速板（右上）に乗った時の処理
					if (g_Bullet[i].accboardcool <= 0)
					{
						g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
						g_Bullet[i].angle = 45.0f;									// 角度を設定
						g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

						g_Bullet[i].accboardcool = 10;
						g_SENo = LoadSound("data/SE/Shortbridge29-4.wav");
						PlaySound(g_SENo, 0);
					}
				}
				if (collision_num == 8)
				{
					// 加速板（右下）に乗った時の処理
					if (g_Bullet[i].accboardcool <= 0)
					{
						g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
						g_Bullet[i].angle = 315.0f;									// 角度を設定
						g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

						g_Bullet[i].accboardcool = 10;
						g_SENo = LoadSound("data/SE/Shortbridge29-4.wav");
						PlaySound(g_SENo, 0);
					}
				}
				if (collision_num == 9)
				{
					// 加速板（左下）に乗った時の処理
					if (g_Bullet[i].accboardcool <= 0)
					{
						g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
						g_Bullet[i].angle = 225.0f;									// 角度を設定
						g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

						g_Bullet[i].accboardcool = 10;
						g_SENo = LoadSound("data/SE/Shortbridge29-4.wav");
						PlaySound(g_SENo, 0);
					}
				}
				if (collision_num == 10)
				{
					// 加速板（左上）に乗った時の処理
					if (g_Bullet[i].accboardcool <= 0)
					{
						g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
						g_Bullet[i].angle = 135.0f;									// 角度を設定
						g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

						g_Bullet[i].accboardcool = 10;
						g_SENo = LoadSound("data/SE/Shortbridge29-4.wav");
						PlaySound(g_SENo, 0);
					}
				}



				//スイッチ
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 14)
				{
					if (g_Bullet[i].switchcool <= 0)
					{
						g_Bullet[i].onswitch = !g_Bullet[i].onswitch;
						g_Bullet[i].switchcool = 120.0f;
					}
				}
				//スイッチ押された後
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 18)
				{
					if (g_Bullet[i].switchcool <= 0)
					{
						g_Bullet[i].onswitch = !g_Bullet[i].onswitch;
						g_Bullet[i].switchcool = 120.0f;
					}
				}

				for (int y = 0; y < MAP_Y; y++)
				{
					for (int x = 0; x < MAP_X; x++)
					{
						if (p_Stagedata->maparray[y][x] == 14)
						{

							//スイッチ押すだけの処理
							if (g_Bullet[i].onswitch == true)
							{
								p_Stagedata->maparray[y][x] = 18;
								g_Bullet[i].switchcool = 25.0f;
							}
						}

						if (p_Stagedata->maparray[y][x] == 18)
						{
							//スイッチ押すだけの処理
							if (g_Bullet[i].onswitch == false)
							{
								p_Stagedata->maparray[y][x] = 14;
								g_Bullet[i].switchcool = 25.0f;
							}
						}

						// スイッチ押したら現れる赤ブロック
						if (p_Stagedata->maparray[y][x] == 19)
						{
							if (g_Bullet[i].onswitch == true)
							{
								p_Stagedata->maparray[y][x] = 20;
							}
						}

						// 赤ブロックの消えた後の床
						if (p_Stagedata->maparray[y][x] == 20)
						{
							if (g_Bullet[i].onswitch == false)
							{
								p_Stagedata->maparray[y][x] = 19;
							}
						}

						//スイッチ押したら消える青ブロック
						if (p_Stagedata->maparray[y][x] == 36)
						{
							if (g_Bullet[i].onswitch == true)
							{
								p_Stagedata->maparray[y][x] = 35;
							}
						}

						//消えるブロックの消えた後の床
						if (p_Stagedata->maparray[y][x] == 35)
						{
							if (g_Bullet[i].onswitch == false)
							{
								p_Stagedata->maparray[y][x] = 36;
							}
						}
					}
				}


				axis_x = (int)(g_Bullet[i].pos.x / MAP_CHIP_SIZE_X);//座標をマップチップ一つの大きさで割る
				axis_y = (int)(g_Bullet[i].pos.y / MAP_CHIP_SIZE_Y);
				// 踏んだら消えるブロック
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 21)
				{
					if (p_Stagedata->maparray[axis_y][axis_x] == 21)
					{
						p_Stagedata->maparray[axis_y][axis_x] = 37;
						hole_changetime = 0;
					}

				}


				//崩れた穴の処理
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 22)
				{
					if (g_Bullet[i].holecool <= 0)
					{
						g_Bullet[i].shotpower = 0.0f;
					}
				}

				//池
				if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 34)
				{
					// パワーを減衰させる
					if (g_Bullet[i].shotpower > 0.0f)
						g_Bullet[i].shotpower = 0.0f;

				}

			}////////地面にある時だけの処理の終わり///////////
			/////////////////////////////////////////////////
			//////////////////////////////////////////////////

			

			for (int y = 0; y < MAP_Y; y++)
			{
				for (int x = 0; x < MAP_X; x++)
				{
					//ワープ1
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 11)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 12)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 12)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 11)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
					//ワープ2
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 24)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 25)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 25)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 24)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}

					//ワープ3
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 26)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 27)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 27)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 26)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}

					//ワープ4
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 28)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 29)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 29)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 28)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}

					//ワープ5
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 30)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 31)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 31)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 30)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}

					//ワープ6
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 32)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 33)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 33)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 32)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}

					//ワープ7
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 38)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 39)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 39)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 38)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}

					//ワープ8
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 40)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 41)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
					if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 41)
					{
						if (g_Bullet[i].warpcool <= 0)
						{
							// そのブロックが当たり判定があるブロックかどうか調べるa
							int BlockData = CheckBlockdata(x, y);
							// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
							if (BlockData == 40)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 20;
								g_SENo = LoadSound("data/SE/Shortbridge30-3.wav");
								PlaySound(g_SENo, 0);
							}

						}
					}
				}
			}





			//bool changeblock;


			//////////針の処理////////
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 16)
			{
				g_Bullet[i].shotpower = 0.0f;
			}



			//反射板
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 15)
			{
				// 反射板（右に行く）に乗った時の処理
				g_Bullet[i].angle = 0.0f;									// 角度を設定
				g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

			}



			// 最期にposにnextposを反映させる
			g_Bullet[i].pos = g_Bullet[i].nextpos;

			// 影にもポジションデータを渡す
			g_ShadowBullet[i].pos = g_Bullet[i].nextpos;



			// ボールが跳ねて見える処理,クラブが1(とぶやつ)の時のみ飛んでるように見せる
			if (g_Bullet[i].club_pattern == 1)
				g_Bullet[i].flying_height = Bounce(30.0f, g_Bullet[i].shottime, 28, 57, 81, 120);



			// pos を drawpos に変換		DRAW_GAP は、上から見た時の描写でのマップの描写はレフトトップで、プレイヤーはど真ん中でやってるから、そのずれ。
			g_Bullet[i].drawpos.x = GAME_ORIGIN_POINT_X + DRAW_GAP_BALL_X + ((g_Bullet[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Bullet[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			g_Bullet[i].drawpos.y = -g_Bullet[i].flying_height + GAME_ORIGIN_POINT_Y + DRAW_GAP_BALL_Y + ((g_Bullet[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Bullet[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
			g_Bullet[i].drawsize.x = g_Bullet[i].w * p_Camera->magnification;
			g_Bullet[i].drawsize.y = g_Bullet[i].h * p_Camera->magnification;

			// 影の描写座標も変換する,高さは含めずに計算する
			g_ShadowBullet[i].drawpos.x = GAME_ORIGIN_POINT_X + DRAW_GAP_BALL_X + ((g_Bullet[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Bullet[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			g_ShadowBullet[i].drawpos.y = GAME_ORIGIN_POINT_Y + DRAW_GAP_BALL_Y + ((g_Bullet[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Bullet[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
			g_ShadowBullet[i].drawsize.x = g_Bullet[i].w * p_Camera->magnification;
			g_ShadowBullet[i].drawsize.y = g_Bullet[i].h * p_Camera->magnification;

		}
		
		// クールタイムを減らす処理一覧
		// 球がブロックに当たった時の判定のクールタイムを減らしていく
		if (g_Bullet[i].CollicionCool > 0)
			g_Bullet[i].CollicionCool--;
		// ワープのクールタイムを減らしていく
		if (g_Bullet[i].warpcool > 0)
			g_Bullet[i].warpcool--;
		// 加速版のクールタイムを減らしていく
		if (g_Bullet[i].accboardcool > 0)
			g_Bullet[i].accboardcool--;

		// 弾が発射されてからのカウントを増やす
		g_Bullet[i].shottime++;

		// 針の時間を増やす（ずっとループする）
		needletime++;

		// スイッチのクールタイムを減らしていく
		if (g_Bullet[i].switchcool > 0)
		{
			g_Bullet[i].switchcool--;
		}

		// 崩れる穴のクールタイムを減らしていく
		if (g_Bullet[i].holecool > 0)
		{
			g_Bullet[i].holecool--;
		}

		// 崩れる穴の変わるタイム
			hole_changetime++;

		// パワー100で打ち出した場合(ShotPowor1.5f)球が止まるまで
		// g_Bullet[i].shottimeは　143カウント

	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	//CAMERA* p_Camera = GetCamera();

	//for (int i = 0; i < BULLET_MAX; i++)
	//{
	//	if (g_Bullet[i].use == true)	// このバレットが使われている？
	//	{								// Yes
	//		//バレットの位置やテクスチャー座標を反映
	//		float px = g_Bullet[i].pos.x;	// バレットの表示位置X
	//		float py = g_Bullet[i].pos.y;	// バレットの表示位置Y
	//		float pw = g_Bullet[i].w;		// バレットの表示幅
	//		float ph = g_Bullet[i].h;		// バレットの表示高さ
	//		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



	//		// １枚のポリゴンの頂点とテクスチャ座標を設定
	//		DrawSpriteColorRotate(g_Bullet[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Bullet[i].rot);
	//	}
	//}
}


void DrawBulletSpecifyNum(int i)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)	// このバレットが使われている？
		{								// Yes
			//バレットの位置やテクスチャー座標を反映
			float pxB = g_Bullet[i].drawpos.x;	// バレットの表示位置X
			float pyB = g_Bullet[i].drawpos.y;	// バレットの表示位置Y
			float pwB = g_Bullet[i].drawsize.x;		// バレットの表示幅
			float phB = g_Bullet[i].drawsize.y;		// バレットの表示高さ
			D3DXCOLOR colB = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//バレットの影位置やテクスチャー座標を反映
			float pxSB = g_ShadowBullet[i].drawpos.x;	// バレットの表示位置X
			float pySB = g_ShadowBullet[i].drawpos.y;	// バレットの表示位置Y
			float pwSB = g_ShadowBullet[i].drawsize.x;		// バレットの表示幅
			float phSB = g_ShadowBullet[i].drawsize.y;		// バレットの表示高さ
			D3DXCOLOR colSB = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



			// １枚のポリゴンの頂点とテクスチャ座標を設定, 先に影を描写する
			DrawSpriteColorRotate(g_ShadowBullet[i].tex, pxSB, pySB, pwSB, phSB, 0.0f, 0.0f, 1.0f, 1.0f, colSB, 0.0f);
			DrawSpriteColorRotate(g_Bullet[i].texNo, pxB, pyB, pwB, phB, 0.0f, 0.0f, 1.0f, 1.0f, colB, g_Bullet[i].rot);
		}
	}
}

//=============================================================================
// バレット構造体の先頭アドレスを取得
//=============================================================================
BULLET* GetBullet(void)
{
	return &g_Bullet[0];
}


//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBullet(D3DXVECTOR2 pos, float angle, int ShotPower, int club_pattern)
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

			g_Bullet[i].shotpower = 1.12f;			// デバッグ用にパワーマックス(100の状態)で発射
			//g_Bullet[i].shotpower = ShotBairitu;			// shotpowerの設定
			g_Bullet[i].shottime = 0;						// 弾が発射されてからの時間の初期化
			g_Bullet[i].angle = angle;						// 角度を設定
			g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);	// 角度からベクトルを設定
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.x,
				-BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.y);	// ベクトルからmoveを設定

			g_Bullet[i].flying_height = 0.0f;
			g_Bullet[i].club_pattern = club_pattern;

			return;							// 1発セットしたので終了する
		}
	}
}

D3DXVECTOR2 AngleToVector2(float angle)
{
	float radian = angle * (D3DX_PI / 180);
	return  D3DXVECTOR2(cos(radian), sin(radian));
}


// -1:NoHit,0,左上,1:右上,2:左下,3:右下,四隅のどれに当たっているか。またはどれにも当たっていないか。
// ブロックの中心からの角までの座標の計算。今どこの角に当たっているかをもらうと計算できる。こっちはXだけ。
float CalculateCornerDistanceX(int CornerNum, float size_x, float size_y)
{
	float distance_x = 0;

	if (CornerNum == 0 || CornerNum == 2)
		distance_x = -size_x / 2;
	if (CornerNum == 1 || CornerNum == 3)
		distance_x = size_x / 2;

	return distance_x;
}

// ブロックの中心からの角までの座標の計算。今どこの角に当たっているかをもらうと計算できる。こっちはYだけ。
float CalculateCornerDistanceY(int CornerNum, float size_x, float size_y)
{
	float distance_y = 0;

	if (CornerNum == 2 || CornerNum == 3)
		distance_y = -size_y / 2;
	if (CornerNum == 0 || CornerNum == 1)
		distance_y = size_y / 2;

	return distance_y;
}

// 衝突した2点の座標から計算して新しく設定する角度とベクトルを求める。void型で最期に値の更新をこの関数内で直接行っている。
void CalculateNewVecAng(int i, float bulletposX, float bulletposY, float CornerPosX, float CornerPosY)
{

	// ボールベクトルの角度
	// g_Bullet[i].angle
	// 壁のベクトルの角度
	//float wall_radian = CalculateRadianFrom2Points(CornerPosX, CornerPosY, g_Bullet[i].oldpos.x, g_Bullet[i].oldpos.y);
	float wall_radian = CalculateRadianFrom2Points(CornerPosX, CornerPosY, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y);
	wall_radian = InversionYRadian(wall_radian);
	//float wall_radian = atan2(g_Bullet[i].nextpos.y - (HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2) / BigMagnification), HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) - (BigCornerPoint.x / BigMagnification));
	float wall_angle = RadianToDegree(wall_radian);
	// 壁ベクトルの角度の真逆の角度
	float wall_angle_reverse = ReverseDegree(wall_angle);

	// 壁の真逆の角度からボールの角度を引いて差を出す
	float difference_angle = wall_angle_reverse - g_Bullet[i].angle;
	float adjustAngle = 55.0f;
	// カスあたりでも壁ベクトルの角度から adjustangle 以上の角度はつかないよっていうゲームっぽく見せるための調整。リアルすぎないように。
	if (difference_angle > adjustAngle)
		difference_angle = adjustAngle;
	if (difference_angle < -adjustAngle)
		difference_angle = -adjustAngle;
	// 壁の角度に差の角度を足す
	float new_bullet_angle = wall_angle + difference_angle;
	if (new_bullet_angle >= 360.0)
		new_bullet_angle -= 360.0;
	if (new_bullet_angle < 0)
		new_bullet_angle += 360.0;

	// 角度とベクトルの更新
	g_Bullet[i].angle = new_bullet_angle;							// 角度を設定
	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

	g_Bullet[i].CollicionCool = COL_COOL;

	// 壁に当たった回数を+1回する
	GAMEDATA* p_Gamedata = GetGamedata();
	p_Gamedata->hit_wall_count++;

	return;
}

// 反転させたいものが、Xなら0,Yなら1
void InversionVecAng(int i, int XorY)
{
	// 角度はx,y関係なくこれで反転
	float newang = g_Bullet[i].angle + 180.0;
	if (newang >= 360)
		newang -= 360;

	D3DXVECTOR2 newvec = D3DXVECTOR2(g_Bullet[i].vector.x, g_Bullet[i].vector.y);
	if (XorY == 0)
		newvec.x *= -1;
	else
		newvec.y *= -1;

	// 角度とベクトルの更新
	g_Bullet[i].angle = newang;									// 角度を設定
	g_Bullet[i].vector = newvec;		// 角度からベクトルを設定

	g_Bullet[i].CollicionCool = COL_COOL;

	// 壁に当たった回数を+1回する
	GAMEDATA* p_Gamedata = GetGamedata();
	p_Gamedata->hit_wall_count++;

	return;
}

// ボールをはねて見せる関数、まじで見た目だけ。タイミングとかはパワーの話決まってからみんなにあわせてもらう
float Bounce(float maxhight, int nowframe, int bounce1frame, int bounce2frame, int bounce3frame, int bounce4frame)
{
	float bounceframe = bounce1frame;	// 今何バウンド目かを識別
	float now_maxhight = maxhight;		// バウンドするたびに跳ねる高さを低くするため
	int now_count = nowframe;
	if (nowframe >= bounce1frame)
	{
		bounceframe = bounce2frame - bounce1frame;
		now_maxhight = maxhight * 0.68f;
		now_count = nowframe - bounce1frame;
	}
	if (nowframe >= bounce2frame)
	{
		bounceframe = bounce3frame - bounce2frame;
		now_maxhight = maxhight * 0.30f;
		now_count = nowframe - bounce2frame;
	}
	if (nowframe >= bounce3frame)
	{
		bounceframe = bounce4frame - bounce3frame;
		now_maxhight = maxhight * 0.12f;
		now_count = nowframe - bounce3frame;
	}
	// 貰った時のフレームがすでに終わっている時間だったら0を返す
	if (nowframe > bounce4frame)
		return 0.0f;



	// 半円を描く時間を180で割って、1フレームで何度ずつ上がっていくのかを計算する,それに今のフレームをかける
	float now_degree = 180.0f / bounceframe * now_count;
	// それをラジアンに変換
	float now_radian = DegreeToRadian(now_degree);
	// 最大高さにサインをかけてあげることで今の高さを出す
	float sindata = sin(now_radian);
	float nowhight = now_maxhight * sindata;

	return nowhight;
}

