//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_TextureNo = 0;	// テクスチャ情報
static int	g_BGMNo = 0;		// BGM識別子

								//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	//テクスチャ生成
	g_TextureNo = LoadTexture("data/TEXTURE/title/title.png");

	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)をループ指定すると無限ループ
	PlaySound(g_BGMNo, -1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	StopSoundAll();
	UnloadTexture("data/TEXTURE/title/title.png");
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	bool mouse_Lclick = GetMouseLClick();

	if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_WORLD_SELECT);
	}
	if (mouse_Lclick && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_WORLD_SELECT);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}

