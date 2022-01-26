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
#define RESULT_MAX (5)

// プレイヤー構造体
struct RESULT
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
	int						goaltime;				// ゴールしてからの時間
	int						selectpush;				// 選択してるやつ
	int						selecttime;				// 選択クールタイム
	int						resulttime;				// リザルト表示してからの時間
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(D3DXVECTOR2 pos);
RESULT* GetResult(void);

//#define MAX_RESULT (3)			// ミッション数の最大(最後尾)3つ固定
//#define SAVEDATA_ELEMENTS	(4)			// ミッション数+クリアタイム
//#define MAX_DIGIT	(3)			// 最大3桁まで
//
//typedef struct {
//
//	// セットエフェクトで使われる配列の番号を保管する
//	int mission_background_EffectArray;					// 背景は1個なので1
//	int mission_ContentsNum_EffectArray[MAX_RESULT];
//	int mission_JudgeNum_EffectArray[MAX_RESULT][MAX_DIGIT];
//
//}RESULT;

//void DrawMissionResult();
//void DeleteMissionResult();
bool checkresult();