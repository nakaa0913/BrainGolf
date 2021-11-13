#pragma once


//#define SELECT_MAX (5)

#define TIME (15)

#define WORLD_SELECT_MAX_X (5)       // select_xのMAX
#define WORLD_SELECT_MAX_Y (1)       // select_yのMAX

#define WORDL_SELECT_COOL (10)       // ワールドセレクトの時のクールタイム

// プレイヤー構造体
struct WORLDSELECT
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

};

void InitWorldSelect(void);
void UninitWorldSelect(void);
void UpdateWorldSelect(void);
void DrawWorldSelect(void);

WORLDSELECT* GetWorldSelect();
int GetNowWorld();

void StartWorldSelectScreen();