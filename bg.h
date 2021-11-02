//=============================================================================
//
// 背景処理 [bg.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_CHIP_SIZE_X (40)
#define MAP_CHIP_SIZE_Y (40)

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


void DrawBG2(void);
int GetMapEnter2(D3DXVECTOR2 pos);
int CheckBlockdata2(int BlockX, int BlockY);