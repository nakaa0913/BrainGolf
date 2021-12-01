//=============================================================================
//
// タイトル画面処理 [Prologue.cpp]
// Author : 
//
//=============================================================================
#include "Prologue.h"
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "enemy_emitter.h"
#include "bullet.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "bg.h"
#include "result.h"
#include"stageselect.h"
#include "Texture.h"
#include "sprite.h"
#include "effect.h"
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
void InitPrologue(void)
{
	//テクスチャ生成
	g_TextureNo = LoadTexture("data/TEXTURE/logo/HEW2.png");

	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)をループ指定すると無限ループ
	PlaySound(g_BGMNo, -1);

	return;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPrologue(void)
{
	StopSoundAll();
	UnloadTexture("data/TEXTURE/logo/HEW2.png");
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePrologue(void)
{
	bool mouse_Lclick = GetMouseLClick();

	if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_TITLE);
	}
	if (mouse_Lclick && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPrologue(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
}
