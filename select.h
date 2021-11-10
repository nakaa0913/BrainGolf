#pragma once


//#define SELECT_MAX (5)

#define TIME (15)

#define SELECT_MAX_X (5)       // select_xのMAX
#define SELECT_MAX_Y (2)       // select_yのMAX

// プレイヤー構造体
struct SELECT
{
	bool					use;					// true:使っている  false:未使用
	float					w, h;					// 幅と高さ
	D3DXVECTOR2				pos;					// ポリゴンの座標
	float					rot;					// ポリゴンの回転量
	int						texNo;					// テクスチャ番号

	int						select_x;				//横選択
	int						select_y;			    //縦選択
	int						selectcooltime;			//選択クールタイム
	int						selecttime;				//セレクトフレーム

	float					origin_x;			    // xの原点(0,0を選択しているとき)
	float					origin_y;			    // yの原点(0,0を選択しているとき)


};

void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
