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
#define PLAYER_MAX (10)

#define ORDER_MAX			 (5)
#define INPUT_DIGIT_X_MAX	 (4)
#define INPUT_DIGIT_Y_MAX	 (4)

#define PLAYER_MOVE_SPEED	 (3.0f)


// ファイル読み込みからマップチップでの座標と往復する順番を取りやすくするためだけの構造体
// PLAYER構造体で使用しているので、それより上に書かないとダメ。ネスト構造
struct MAPCHIP_POS_STRUCT
{			
	int						mapchip_pos_x[ORDER_MAX];
	int						mapchip_pos_y[ORDER_MAX];
};


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
	bool					ConfirmAngle;			// 角度を確定したかどうか
	int						ConfirmCooltime;		// 確定してからのクールタイム

	struct					MAPCHIP_POS_STRUCT Mapchip_Pos_Struct;
	bool					move_around;			// プレイヤーが初期位置から動き回るかどうか。
	float					move_speed;				// プレイヤーの移動速度
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

void SetPlayerUseFile(MAPCHIP_POS_STRUCT Receive_Mapchip_Pos_Struct, float movespeed);