//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "score.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
int have_count = 0;
int haveplayer = -1;

//=============================================================================
// 当たり判定処理
//=============================================================================
void UpdateCollision(void)
{
	PLAYER *player = GetPlayer();		// プレイヤーのポインターを初期化
	ENEMY  *enemy = GetEnemy();		// エネミーのポインターを初期化
	BULLET *bullet = GetBullet();		// バレットのポインターを初期化

//	// 敵と操作キャラ(BB)
//	if (player[0].use == true)
//	{
//		for (int i = 0; i < ENEMY_MAX; i++)
//		{
//			if (enemy[i].use == false)
//				continue;
//
////			if (CollisionBB(player->pos, enemy[i].pos, D3DXVECTOR2(player->w, player->h), D3DXVECTOR2(enemy[i].w, enemy[i].h)))
//			if (CollisionBC(player->pos, enemy[i].pos, player->h/2, enemy[i].h/2))
//			{
//				// 操作キャラクターは死に
//
//				// 敵キャラクターは倒される
//				enemy[i].use = false;
//
//				// HP減少処理
//
//			}
//		}
//	}

	//// 弾と敵(BB)
	//for (int i = 0; i < BULLET_MAX; i++)
	//{
	//	if (bullet[i].use == false)
	//		continue;

	//	for (int j = 0; j < ENEMY_MAX; j++)
	//	{
	//		if (enemy[j].use == false)
	//			continue;
	//			
	//		if (CollisionBB(bullet[i].pos, enemy[j].pos, D3DXVECTOR2(bullet[i].w, bullet[i].h), D3DXVECTOR2(enemy[j].w, enemy[j].h)))
	//		{
	//			bullet[i].use = false;		// 弾の消滅処理を行い
	//			enemy[j].use = false;		// 敵は倒される

	//			// スコア計算

	//			//break;					// １回当たって終わりの時はここでbreakする。１フレーム内の間有効ならbreakをコメントにする。
	//		}
	//	}
	//}

	

	// プレイヤーと弾の判定
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullet[i].use == false)
			continue;

		for (int j = 0; j < PLAYER_MAX; j++)
		{
			if (player[j].use == false)
				continue;

			if (CollisionBB(bullet[i].pos, player[j].pos, D3DXVECTOR2(bullet[i].w, bullet[i].h), D3DXVECTOR2(player[j].w, player[j].h)))
			{

				if (player[j].catchwait <= 0)
				{
					bullet[i].use = false;		// 弾の消滅処理を行い
					bullet[i].friction = 1.0f;
					player[j].have = true;		// プレイヤーは弾を持つ
					Truenow_have();
					haveplayer = j;

					have_count = 1;


					SetShotPower(0);			// ショットパワーの表示を0にしておく

					// 全てのプレイヤーの必要な要素を初期化
					for (int n = 0; n < PLAYER_MAX; n++)
					{
						player[n].angle = 0.0f;
						player[n].ShotPower = 0;
						player[n].ConfirmAngle = false;
						player[n].ConfirmCooltime = 10;
					}
					
				}

				// スコア計算

				//break;					// １回当たって終わりの時はここでbreakする。１フレーム内の間有効ならbreakをコメントにする。
			}
		}
	}

	//if (have_count >= 1)
	//{
	//	if (have_count >= 2)
	//	{
	//		have_count = 0;
	//		player[haveplayer].have = true;		// プレイヤーは弾を持つ
	//		Truenow_have();
	//	}
	//	else
	//		have_count++;
	//}

	// ボスと弾(BC)

	// 自分と敵の弾(BC)

	// 死亡したら状態遷移

	////跳ね返り
	//for (int i = 0; i < BULLET_MAX; i++)
	//{
	//	//右
	//	if (bullet[i].pos.x > 480.0f)
	//	{
	//		bullet[i].move.x *= -1;
	//	}
	//	//左
	//	if (bullet[i].pos.x < 80.0f)
	//	{
	//		bullet[i].move.x *= -1;
	//	}
	//	//上
	//	if (bullet[i].pos.y < 80.0f)
	//	{
	//		bullet[i].move.y *= -1;
	//	}
	//	//下
	//	if (bullet[i].pos.y > 720.0f)
	//	{
	//		bullet[i].move.y *= -1;
	//	}
	//}
}

//=============================================================================
// BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X軸の判定
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y軸の判定
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}

	return false;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistanceのベクトル長を得る
	float length;
//	length = D3DXVec2Length(&vDistance);
	length = D3DXVec2LengthSq(&vDistance);

//	float size = size1 + size2;
	float size = (size1 + size2) * (size1 + size2);

	//1と2の半径を足して判定する
	//差分のベクトル長の方が小さければ
	//ヒットしている
	if (length < size)
	{
		return true;
	}

	return false;
}

bool CheckHit(D3DXVECTOR2 pos1, D3DXVECTOR2 size1, D3DXVECTOR2 pos2, D3DXVECTOR2 size2)
{
	float L1 = pos1.x;      // 左
	float R1 = pos1.x + size1.x; // 右(左+横幅)
	float L2 = pos2.x;      // 左
	float R2 = pos2.x + size2.x; // 右(左+横幅)

	if (R1 < L2) return false; //< 線上も当たってることにする
	if (R2 < L1) return false; //< 線上も当たってることにする

	float U1 = pos1.y;			 // 上
	float D1 = pos1.y + size1.y; // 下(上+縦幅)
	float U2 = pos2.y;			// 上
	float D2 = pos2.y + size2.y; // 下(上+縦幅)

	if (D1 < U2) return false; //< 線上も当たってることにする
	if (D2 < U1) return false; //< 線上も当たってることにする

	// それ以外の場合は当たっている
	return true;
}