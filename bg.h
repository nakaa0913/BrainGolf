//=============================================================================
//
// 背景処理 [bg.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"




//// 背景構造体
//struct BACKGROUND
//{
//	bool					use;					// true:使っている  false:未使用
//	D3DXVECTOR2				size;					// 幅と高さ
//	D3DXVECTOR2				pos;					// ポリゴンの座標
//	D3DXVECTOR2				nextpos;				// 次の予定の座標
//	D3DXVECTOR2				drawpos;				// 次の予定の座標
//	float					rot;					// ポリゴンの回転量
//	int						texNo;					// テクスチャ番号
//
//};






//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_CHIP_SIZE_X (40)
#define MAP_CHIP_SIZE_Y (40)

#define DRAW_MAP_CHIP_SIZE_X (80)
#define DRAW_MAP_CHIP_SIZE_Y (40)

#define GAME_ORIGIN_POINT_X		(SCREEN_WIDTH / 2 + 120.0f)					// ゲーム内の原点をこれとする。
#define GAME_ORIGIN_POINT_Y		(0.0f + 40.0f)							// ゲーム内の原点をこれとする。

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);

int GetMapEnter(D3DXVECTOR2 pos);
void SetCurrentMap(int next);

int CheckBlockdata(int BlockX, int BlockY);


