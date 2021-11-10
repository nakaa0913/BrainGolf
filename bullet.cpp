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
#include "collision.h"

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
	int texNo = LoadTexture("data/TEXTURE/bullet/ao.png");
	// バレット構造体の初期化 でも実際はSetBulletで呼ぶときにそっちで値が代入される
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use = false;
		g_Bullet[i].w = 20.0f;
		g_Bullet[i].h = 20.0f;
		g_Bullet[i].pos = D3DXVECTOR2(300, 300.0f);
		g_Bullet[i].nextpos = g_Bullet[i].pos;
		g_Bullet[i].oldpos = g_Bullet[i].pos;

		g_Bullet[i].drawpos = g_Bullet[i].pos;
		g_Bullet[i].drawsize = D3DXVECTOR2(g_Bullet[i].w, g_Bullet[i].h);

		g_Bullet[i].rot = 0.0f;
		g_Bullet[i].texNo = texNo;

		g_Bullet[i].friction = 1.0f;
		g_Bullet[i].angle = 0.0f;
		g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED, -BULLET_SPEED);	// 移動量を初期化
		g_Bullet[i].vector = D3DXVECTOR2(1.0f, 1.0f);

		g_Bullet[i].CollicionCool = 0;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	UnloadTexture("data/TEXTURE/bullet/ao.png");
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
			g_Bullet[i].friction = 0.9815;

			if (g_Bullet[i].shotpower < 0.14f)
			{
				g_Bullet[i].shotpower = 0;
			}
			// ショットパワーに抵抗力をかけて力を弱くする
			g_Bullet[i].shotpower = g_Bullet[i].shotpower * g_Bullet[i].friction;

			// 移動量moveの更新
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.x,
				-BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.y);	// ベクトルからmoveを設定



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
				for (int y = 0; y < MAP_Y; y++)
				{
					for (int x = 0; x < MAP_X; x++)
					{
						// そのブロックが当たり判定があるブロックかどうか調べるa
						int BlockData = CheckBlockdata(x, y);
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

					}
					if (OriginLengthAndWidthPos == 1)
					{
						g_Bullet[i].nextpos.x = HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X + (g_Bullet[i].w / 2);
						////g_Bullet[i].move.x *= -1;
						//g_Bullet[i].vector.x *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, HitBlockDatas2D[0].BlockPosX* MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X, g_Bullet[i].nextpos.y);
						InversionVecAng(i, 0);

					}
					if (OriginLengthAndWidthPos == 2)
					{
						g_Bullet[i].nextpos.y = HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f - (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, HitBlockDatas2D[0].BlockPosY* MAP_CHIP_SIZE_Y + 0.0f);
						InversionVecAng(i, 1);

					}
					if (OriginLengthAndWidthPos == 3)
					{
						g_Bullet[i].nextpos.y = HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y + (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, HitBlockDatas2D[0].BlockPosY* MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y);
						InversionVecAng(i, 1);

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

					}

					if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
					{
						if (BulletCircle.y < HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + 0.0f)
							LeftorRight = 2;
					}
					if (BulletCircle.x > HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + 0.0f && BulletCircle.x < HitBlockDatas2D[0].BlockPosX * MAP_CHIP_SIZE_X + MAP_CHIP_SIZE_X)
					{
						if (BulletCircle.y > HitBlockDatas2D[0].BlockPosY * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
							LeftorRight = 3;
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

					}
					if (BulletCircle.y > block_min.y * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y)
					{
						// バレットはブロックの下側から上側に向かって進んでいて衝突したのでブロックの下側にnextposを固定し、下に向かって反射させる
						g_Bullet[i].nextpos.y = block_min.y * MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y + (g_Bullet[i].h / 2);
						////g_Bullet[i].move.y *= -1;
						//g_Bullet[i].vector.y *= -1;
						//CalculateNewVecAng(i, g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y, g_Bullet[i].nextpos.x, block_min.y* MAP_CHIP_SIZE_Y + MAP_CHIP_SIZE_Y);
						InversionVecAng(i, 1);

					}
				}

			}






			// マップとの当たり判定処理

			// ゴールに入った時の処理
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].nextpos.x, g_Bullet[i].nextpos.y)) == 2)
			{
				// ゴールに入った時の処理
				GoalTrue();
				// g_Bullet[i].use = false;
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 3)
			{
				// 加速板（上）に乗った時の処理
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
					g_Bullet[i].angle = 90.0f;									// 角度を設定
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定
					
					g_Bullet[i].accboardcool = 60;
				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 4)
			{
				// 加速板（下）に乗った時の処理
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
					g_Bullet[i].angle = 270.0f;									// 角度を設定
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定


					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 5)
			{
				// 加速板（右）に乗った時の処理
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
					g_Bullet[i].angle = 0.0f;									// 角度を設定
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 6)
			{
				// 加速板（左）に乗った時の処理
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
					g_Bullet[i].angle = 180.0f;									// 角度を設定
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 7)
			{
				// 加速板（右上）に乗った時の処理
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
					g_Bullet[i].angle = 45.0f;									// 角度を設定
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 8)
			{
				// 加速板（右下）に乗った時の処理
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
					g_Bullet[i].angle = 315.0f;									// 角度を設定
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 9)
			{
				// 加速板（左下）に乗った時の処理
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
					g_Bullet[i].angle = 225.0f;									// 角度を設定
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

					g_Bullet[i].accboardcool = 60;

				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 10)
			{
				// 加速板（左上）に乗った時の処理
				if (g_Bullet[i].accboardcool <= 0)
				{
					g_Bullet[i].shotpower = 2.0f;								// ショットパワーを設定
					g_Bullet[i].angle = 135.0f;									// 角度を設定
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

					g_Bullet[i].accboardcool = 60;

				}
			}

			//ワープ
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 11)
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
							if (BlockData == 12)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 60;

							}

						}
					}
				}
			}

			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 12)
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
							if (BlockData == 11)
							{
								g_Bullet[i].nextpos.x = x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
								g_Bullet[i].nextpos.y = y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

								g_Bullet[i].warpcool = 60;
							}

						}
					}
				}
			}

			//砂
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 13)
			{
				// パワーを減衰させる
				if (g_Bullet[i].shotpower > 0.3f)
					g_Bullet[i].shotpower = 0.3f;

			}

			//反射板
			if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 15)
			{
				// 反射板（右に行く）に乗った時の処理
					g_Bullet[i].angle = 0.0f;									// 角度を設定
					g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

			}

			//if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 15)
			//{
			//	// 反射板（左に行く）に乗った時の処理
			//	g_Bullet[i].angle = 180.0f;									// 角度を設定
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

			//}

			//if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 15)
			//{
			//	// 反射板（上に行く）に乗った時の処理
			//	g_Bullet[i].angle = 90.0f;									// 角度を設定
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

			//}

			//if (GetMapEnter(D3DXVECTOR2(g_Bullet[i].pos.x, g_Bullet[i].pos.y)) == 15)
			//{
			//	// 反射板（下に行く）に乗った時の処理
			//	g_Bullet[i].angle = 270.0f;									// 角度を設定
			//	g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);		// 角度からベクトルを設定

			//}





			//// クールタイムを減らす処理一覧
			//// 球がブロックに当たった時の判定のクールタイムを減らしていく
			//if (g_Bullet[i].CollicionCool > 0)
			//	g_Bullet[i].CollicionCool--;
			//// ワープのクールタイムを減らしていく
			//if (g_Bullet[i].warpcool > 0)
			//	g_Bullet[i].warpcool--;
			//// 加速版のクールタイムを減らしていく
			//if (g_Bullet[i].accboardcool > 0)
			//	g_Bullet[i].accboardcool--;


			// 最期にposにnextposを反映させる
			g_Bullet[i].pos = g_Bullet[i].nextpos;

			// pos を drawpos に変換		DRAW_GAP は、上から見た時の描写でのマップの描写はレフトトップで、プレイヤーはど真ん中でやってるから、そのずれ。
			g_Bullet[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Bullet[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Bullet[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2);
			g_Bullet[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Bullet[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Bullet[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2);

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


void DrawBulletSpecifyNum(int i)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)	// このバレットが使われている？
		{								// Yes
			//バレットの位置やテクスチャー座標を反映
			float px = g_Bullet[i].drawpos.x;	// バレットの表示位置X
			float py = g_Bullet[i].drawpos.y;	// バレットの表示位置Y
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
BULLET* GetBullet(void)
{
	return &g_Bullet[0];
}


//=============================================================================
// バレットの発射設定
//=============================================================================
void SetBullet(D3DXVECTOR2 pos, float angle, int ShotPower)
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

			g_Bullet[i].shotpower = ShotBairitu;			// shotpowerの設定
			g_Bullet[i].angle = angle;						// 角度を設定
			g_Bullet[i].vector = AngleToVector2(g_Bullet[i].angle);	// 角度からベクトルを設定
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.x,
				-BULLET_SPEED * g_Bullet[i].shotpower * g_Bullet[i].vector.y);	// ベクトルからmoveを設定

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

	return;
}

