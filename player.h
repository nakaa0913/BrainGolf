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

#define CLUB_CHANGECOOL	(12)			// クラブを持ち替えのクールタイム


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
	D3DXVECTOR2				nextpos;				// 次の予定の座標
	D3DXVECTOR2				drawpos;				// 表示する際の座標
	D3DXVECTOR2				drawsize;				// 表示する際のサイズ
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
	int						now_array_num;			// 現在配列の何番の動作中か
	int						order_max_num;			// ちゃんと中身が入っている状態がどこまでか


	int						now_count;				////一時的なもの
	int						moving_count;			////
	int						pos_moving_pattern;		// 初期位置から終了位置に移動するときの動き方 0:pos1から動かない
	float					move_speed;				// プレイヤーの移動速度

	int						roundtrip_x;			// プレイヤーを往復させる処理X
	int						roundtrip_y;			// プレイヤーを往復させる処理Y
	float					animeptn2;				// プレイヤーの歩行アニメーション
	int						animewaitframe2;		// プレイヤーの歩行アニメーション待ち時間
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DrawPlayerSpecifyNum(int i);
void DrawPlayerForPlacement(void);
void DrawPlayerSpecifyNumForPlacement(int i);
void SetPlayer(D3DXVECTOR2 pos);
void SetPlayerUseMapPos(int mappos_x, int mappos_y);
PLAYER *GetPlayer(void);
int GetClubPattern(void);

void SetPlayerUseFile(MAPCHIP_POS_STRUCT Receive_Mapchip_Pos_Struct, float movespeed);
int SetPlayerForPlacement(int mappos_x, int mappos_y);
int returnHavePlayer();
void DeletePlayer(int num);
void DeletePlacementPlayer();