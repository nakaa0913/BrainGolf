/*==============================================================================

   頂点管理[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_MAX (3)

// プレイヤー構造体
struct PLAYER
{
	bool					use;					// true:使っている  false:未使用
	float					w, h;					// 幅と高さ
	D3DXVECTOR2				pos;					// ポリゴンの座標
	float					rot;					// ポリゴンの回転量
	int						texNo;					// テクスチャ番号

	int						act;					// テクスチャの状態管理
	int						direction;				// プレイヤーの向いてる向き 0:下,1:左,2:右,3:上
	bool					have;					// ボールを持っているかどうか
	int						catchwait;				// ボールを打ってから次にキャッチできるまでのクールタイム管理
	float					angle;					// どの角度を向いているか
	int						ShotPower;				// 弾を打ち出す強さ

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetPlayer(D3DXVECTOR2 pos);
PLAYER *GetPlayer(void);
