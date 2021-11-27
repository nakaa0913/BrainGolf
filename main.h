/*==============================================================================

   テクスチャの描画 [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#define MAP_X (14)
#define MAP_Y (20)

#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1440)				// ウインドウの幅
#define SCREEN_HEIGHT	(810)				// ウインドウの高さ

#define SCREEN_WIDTH_MOUSEGAP	(SCREEN_WIDTH / (SCREEN_WIDTH - 10.0f))				    // ウインドウの幅のマウスでのずれの倍率
#define SCREEN_HEIGHT_MOUSEGAP	(SCREEN_HEIGHT / (SCREEN_HEIGHT - 10.0f))				// ウインドウの高さのマウスでのずれの倍率


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float frand();

long GetMousePosX(void);
long GetMousePosY(void);
bool GetMouseLClick(void);
int GetMouseLClickNum(void);
bool GetMouseRClick(void);
int GetMouseRClickNum(void);
bool GetMouseScroll(void);
int  GetMouseScrollNum(void);