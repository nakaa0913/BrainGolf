#pragma once


//#define SELECT_MAX (5)

#define TIME (15)

#define SELECT_MAX_X (5)       // select_xのMAX
#define SELECT_MAX_Y (2)       // select_yのMAX

// プレイヤー構造体
struct STAGESELECT
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

void InitStageSelect(void);
void UninitStageSelect(void);
void UpdateStageSelect(void);
void DrawStageSelect(void);

STAGESELECT* GetStageSelect();
//void SetStageSelect(int stagenum);