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

//#define DRAW_GAP	 (0 * p_Camera->magnification)			// 上画面をレフトトップでやってたせいで出たずれ
#define DRAW_GAP_X	 (20 * p_Camera->magnification)			// 上画面をレフトトップでやってたせいで出たずれ
#define DRAW_GAP_Y	 (20 * p_Camera->magnification)			// 上画面をレフトトップでやってたせいで出たずれ？
									// ここいじって表示を足元に当たり判定が来るようにする。
#define DRAW_GAP_BALL_X	 (-5 * p_Camera->magnification)			// 上のDRAW_GAPにさらにプラスする
#define DRAW_GAP_BALL_Y	 (-5 * p_Camera->magnification)			// 当確図で見た時に、ボールが綺麗に見えるためのもの


#define DRAW_MAP_CHIP_SIZE_X (80.0f)
#define DRAW_MAP_CHIP_SIZE_Y (40.0f)
//#define DRAW_MAP_CHIP_SIZE_X (80.0f * p_Camera->magnification)	// カメラのズーム倍率使わなくなったので。
//#define DRAW_MAP_CHIP_SIZE_Y (40.0f * p_Camera->magnification)

#define MAP_CHIP3D_SIZE_X (240.0f)
#define MAP_CHIP3D_SIZE_Y (400.0f)

#define MAP_CHIP3D_GAP_X (80.0f)
#define MAP_CHIP3D_GAP_Y (360.0f)

#define GAME_ORIGIN_POINT_X		(720.0f + 40.0f * 2 + 0.0f)					// ゲーム内の原点をこれとする。
#define GAME_ORIGIN_POINT_Y		(0.0f	+ 40.0f * 2 + 0.0f)					// ゲーム内の原点をこれとする。

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
void DrawBGaboveForPlacement(void);
void DrawBGsideForPlacement(void);

int GetMapEnter(D3DXVECTOR2 pos);
void SetCurrentMap(int next);

int CheckBlockdata(int BlockX, int BlockY);

D3DXVECTOR2 PosToMappos(D3DXVECTOR2 pos);
D3DXVECTOR2 MapposToPos(D3DXVECTOR2 mappos);

int LimitRange(int num, int min, int max);