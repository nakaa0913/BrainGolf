//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
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
#include "logo.h"
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

static int logo_count = 0;

//=============================================================================
// 初期化処理
//=============================================================================
void InitLogo(void)
{
	//テクスチャ生成
	g_TextureNo = LoadTexture("data/TEXTURE/logo/HEW2.png");

	g_BGMNo = LoadSound("data/SE/catvoice01.wav");

	//255(-1)をループ指定すると無限ループ
	PlaySound(g_BGMNo, 0);

	logo_count = 0;

	return ;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLogo(void)
{
	StopSoundAll();
	UnloadTexture("data/TEXTURE/logo/HEW2.png");

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLogo(void)
{
	bool mouse_Lclick = GetMouseLClick();

	/*if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_Prologue);
	}*/

	//if (mouse_Lclick && GetFadeState() == FADE_NONE)
	//{
	//	SceneTransition(SCENE_STAGE_SELECT);
	//}
	//
	/*if (Keyboard_IsKeyDown(KK_G) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_GAME);
	}*/

	// 180フレームしたらタイトルが始まる
	if (logo_count == 180)
	{
		if (GetFadeState() == FADE_NONE)
		{
			SceneTransition(SCENE_STAGE_SELECT);
		}
	}

	logo_count++;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLogo(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}

