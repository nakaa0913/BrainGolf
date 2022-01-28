/*==============================================================================

   シーン管理 [scene.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "stageselect.h"
#include "effect.h"
#include "logo.h"
#include "player.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "worldselect.h"
#include "savedata.h"
#include "placement.h"
#include "mission.h"
#include "Prologue.h"
#include "pause.h"
#include "stageselect.h"
#include "sprite.h"
#include "Texture.h"

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static SCENE g_SceneIndex = SCENE_NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;

bool	change_once = false;		// シーン変えてってお願い

int gas = 0;

static int g_Tex_cursorS;	// マウスカーソルのテクスチャ用
bool cursor_isUseS = true;	// マウスカーソルの表示用
int cursor_fade_stateS = 0;	// マウスカーソルのフェードイン中がどうか,0:フェード中じゃない,1:フェードイン中,2フェードアウト中
int cursor_fade_countS = 0;	// マウスカーソルのフェード中の場合のカウント
int cursor_fadetimeS = 0;	// フェードする場合これだけかけてフェードする
float cursor_ClarityS = 1.0f;		// カーソルの透明度


/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitScene(SCENE index)
{
	g_SceneIndex = g_SceneNextIndex = index;

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		InitSavedata();
		InitMission();			// ステージセレクトでミッションの情報使うから先に読んでおく
		InitEffect();
		InitLogo();
		//InitStagedata();
		break;

	case SCENE_Prologue:
		InitEffect();
		InitPrologue();
		break;

	case SCENE_TITLE:
		InitEffect();
		InitTitle();
		break;

	case SCENE_WORLD_SELECT:
		InitEffect();
		InitWorldSelect();
		break;


	case SCENE_STAGE_SELECT:
		InitEffect(); 
		//InitStageSelect();
		InitStageSelect2();
		break;

	case SCENE_PLACEMENT:
		InitEffect();
		InitGameForPlacement();
		InitStagedata();
		SetStageData(GetNowChoiceStageNum());
		InitPlacement(); 
		break;

	case SCENE_GAME:
		InitEffect();
		InitGame();
		InitStagedata();
		SetStageData(GetNowChoiceStageNum());
		InitPause();
		break;

		//case SCENE_RESULT:
		//	InitEffect();
		//	InitResult();
		//	break;
	}

	// マウスの初期化
	g_Tex_cursorS = LoadTexture("data/TEXTURE/other_effect/cursor.png");

	cursor_isUseS = true;	// マウスカーソルの表示用
	cursor_fade_stateS = 0;	// マウスカーソルのフェードイン中がどうか,0:フェード中じゃない,1:フェードイン中,2フェードアウト中
	cursor_fade_countS = 0;	// マウスカーソルのフェード中の場合のカウント
	cursor_fadetimeS = 0;	// フェードする場合これだけかけてフェードする
	cursor_ClarityS = 1.0f;

	// 初期設定
	//SetCursorState(true, 2, 180);	// いきなり透明にしておく

}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitScene(void)
{

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		UninitEffect();
		UninitLogo();
		break;

	case SCENE_Prologue:
		UninitEffect();
		UninitPrologue();
		break;

	case SCENE_TITLE:
		UninitEffect();
		UninitTitle();
		break;

	case SCENE_WORLD_SELECT:
		UninitEffect();
		UninitWorldSelect();
		break;

	case SCENE_STAGE_SELECT:
		UninitEffect();
		UninitStageSelect();
		break;

	case SCENE_PLACEMENT:
		UninitEffect();
		UninitPlacement();
		break;

	case SCENE_GAME:
		UninitEffect();
		UninitGame();
		UninitPause();
		break;

		//case SCENE_RESULT:
		//	UninitEffect();
		//	UninitResult();
		//	break;
	}
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		UpdateEffect();
		UpdateLogo();
		break;

	case SCENE_Prologue:
		UpdateEffect();
		UpdatePrologue();
		break;

	case SCENE_TITLE:
		UpdateEffect();
		UpdateTitle();
		break;

	case SCENE_WORLD_SELECT:
		UpdateEffect();
		UpdateWorldSelect();
		break;

	case SCENE_STAGE_SELECT:
		UpdateEffect();
		//UpdateStageSelect();
		UpdateStageSelect2();
		
		break;

	case SCENE_PLACEMENT:
		UpdateEffect();
		UpdatePlacement();
		break;

	case SCENE_GAME:
		UpdateEffect();
		UpdateGame();
		UpdatePause();
		break;

		//case SCENE_RESULT:
		//	UpdateSavedata();
		//	UpdateEffect();
		//	UpdateResult();
		//	UpdateStagedata();
		//	break;
	}

	UpdateFade();
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		DrawLogo();
		DrawEffect();
		break;

	case SCENE_Prologue:
		DrawEffect();
		DrawPrologue();
		break;

	case SCENE_TITLE:
		DrawTitle();
		DrawEffect();
		break;

	case SCENE_WORLD_SELECT:
		DrawWorldSelect();
		DrawEffect();
		break;

	case SCENE_STAGE_SELECT:
		DrawStageSelect();
		DrawEffect();
		break;

	case SCENE_PLACEMENT:
		DrawPlacement();
		DrawEffect();
		break;

	case SCENE_GAME:
		DrawGame();
		DrawEffect();
		DrawPause();
		break;

		//case SCENE_RESULT:
		//	DrawResult();
		//	DrawEffect();
		//	break;
	}

	//// カーソルの処理
	//if (cursor_isUseS == true)
	//{
	//	float mouse_pos_X = GetMousePosX();
	//	float mouse_pos_Y = GetMousePosY();

	//	//D3DXCOLOR Ccolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, cursor_Clarity);
	//	D3DXCOLOR Ccolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	float sizeX = 120.0f;
	//	float sizeY = 120.0f;
	//	float posX = mouse_pos_X;
	//	float posY = mouse_pos_Y;
	//	DrawSpriteLeftTopColor(g_Tex_cursorS, posX, posY, sizeX, sizeY, 0.0f, 0.0f, 0.0f, 1.0f, Ccolor);
	//}

	DrawFade();
}

/*------------------------------------------------------------------------------
   シーン遷移を要求する関数
------------------------------------------------------------------------------*/
void SetScene(SCENE index)
{
	change_once = true;

	//遷移先シーンを設定する
	g_SceneNextIndex = index;
}

/*------------------------------------------------------------------------------
   遷移を要求がある場合にシーンを切り替える関数
------------------------------------------------------------------------------*/
void CheckScene(void)
{
	//////////現在のシーンと遷移先シーンが違っていたら
	////////if (g_SceneIndex != g_SceneNextIndex)
	////////{
	////////	//現在のシーンを終了させる
	////////	UninitScene();

	////////	//遷移先シーンの初期化処理を行う
	////////	InitScene(g_SceneNextIndex);
	////////}


	// シーン変えてってお願いが来てたら1回だけ変更する
	if (change_once == true)
	{
		change_once = false;

		//現在のシーンを終了させる
		UninitScene();

		//遷移先シーンの初期化処理を行う
		InitScene(g_SceneNextIndex);
	}

}


SCENE* GetScene(void)
{
	return &g_SceneIndex;
}