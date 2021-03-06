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
#define MAP_CHIP_MAGNIFICATION (0.9f)
#define CAMERA_MAGNIFICATION (0.95f)

#define MAP_CHIP_SIZE_X (40 * MAP_CHIP_MAGNIFICATION)
#define MAP_CHIP_SIZE_Y (40 * MAP_CHIP_MAGNIFICATION)

//#define DRAW_GAP	 (0 * CAMERA_MAGNIFICATION)			// 上画面をレフトトップでやってたせいで出たずれ
#define DRAW_GAP_X	 (20 * CAMERA_MAGNIFICATION)			// 上画面をレフトトップでやってたせいで出たずれ
#define DRAW_GAP_Y	 (40 * CAMERA_MAGNIFICATION)			// 上画面をレフトトップでやってたせいで出たずれ？

#define DRAW_GAP_FINAL_Y	 (-18.0f)			// 最終調整


									// ここいじって表示を足元に当たり判定が来るようにする。
#define DRAW_GAP_BALL_X	 (-5 * CAMERA_MAGNIFICATION)			// 上のDRAW_GAPにさらにプラスする
#define DRAW_GAP_BALL_Y	 (-5 * CAMERA_MAGNIFICATION)			// 当確図で見た時に、ボールが綺麗に見えるためのもの


//#define DRAW_MAP_CHIP_SIZE_X (80.0f)
//#define DRAW_MAP_CHIP_SIZE_Y (40.0f)
#define DRAW_MAP_CHIP_SIZE_X (80.0f * CAMERA_MAGNIFICATION)	// カメラのズーム倍率使わなくなったので。
#define DRAW_MAP_CHIP_SIZE_Y (40.0f * CAMERA_MAGNIFICATION)

//#define MAP_CHIP3D_SIZE_X (240.0f - (80.0f - DRAW_MAP_CHIP_SIZE_X))
//#define MAP_CHIP3D_SIZE_Y (400.0f - (40.0f - DRAW_MAP_CHIP_SIZE_Y))
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
void SetBackground();

int CheckBlockdata(int BlockX, int BlockY);

D3DXVECTOR2 PosToMappos(D3DXVECTOR2 pos);
D3DXVECTOR2 MapposToPos(D3DXVECTOR2 mappos);

int LimitRange(int num, int min, int max);
bool toumei(int mapchipdata);