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
#include "effect.h"

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
	//g_TextureNo = LoadTexture("data/TEXTURE/title/titlerogo_4.png");

	g_BGMNo = LoadSound("data/BGM/morningroutine(title).wav");

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
	//UnloadTexture("data/TEXTURE/title/titlerogo_4.png");
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	bool mouse_Lclick = GetMouseLClick();

	// ステージセレクトへ飛ぶ。この時ワールド１を選択されていることにする
	if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_STAGE_SELECT);
	}
	if (mouse_Lclick && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_STAGE_SELECT);
	}
	// タイトルぼかし
	SetEffect(95, D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, 1.0f, 0, 1, 0, 1,
		0.0f, 0.0f, 0);

	//明るくするなら48暗くするなら4
	SetEffect(4, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, 0.5f, 0, 1, 0, 1,
		0.0f, 0.0f, 0);

	// タイトルクリック指示
	SetEffect(93, D3DXVECTOR2(720, 300), D3DXVECTOR2(720, 300), 0,
		D3DXVECTOR2(1200.0f, 1200.0f), D3DXVECTOR2(1200.0f, 1200.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 1,
		0.0f, 0.0f, 0);
	
	// タイトルロゴ
	SetEffect(94, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(1000.0f, 500.0f), D3DXVECTOR2(1000.0f, 500.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 1,
		0.0f, 0.0f, 0);



	/*if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_WORLD_SELECT);
	}
	if (mouse_Lclick && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_WORLD_SELECT);
	}*/
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}

