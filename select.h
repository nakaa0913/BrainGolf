#pragma once


#define SELECT_MAX (5)

#define TIME (15)
// プレイヤー構造体
struct SELECT
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
	int						goaltime;				//ゴールしてからの時間
	int						selectpush;				//選択してるやつ
	int						selectvertical;			//縦選択
	int						selectcooltime;			//選択クールタイム
	int						selecttime;				//セレクトフレーム
};

void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
