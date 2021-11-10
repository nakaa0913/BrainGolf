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
			InitEffect();
			InitLogo();
			//InitStagedata();
			break;

	case SCENE_TITLE:
		InitEffect();
		InitTitle();
		break;

	case SCENE_SELECT:
		InitEffect();
		InitStageSelect();
		break;

	case SCENE_GAME:
		InitEffect();
		InitGame();
		InitStagedata();
		break;

	case SCENE_RESULT:
		InitEffect();
		InitResult();
		break;
	}
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

	case SCENE_TITLE:
		UninitEffect();
		UninitTitle();
		break;

	case SCENE_SELECT:
		UninitEffect();
		UninitStageSelect();
		break;

	case SCENE_GAME:
		UninitEffect();
		UninitGame();
		break;

	case SCENE_RESULT:
		UninitEffect();
		UninitResult();
		break;
	}
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateScene(void)
{
	switch( g_SceneIndex ) 
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		UpdateEffect();
		UpdateLogo();
		UpdateStagedata();
		break;

	case SCENE_TITLE:
		UpdateEffect();
		UpdateTitle();
		UpdateStagedata();
		break;

	case SCENE_SELECT:
		UpdateEffect();
		UpdateStageSelect();
		UpdateStagedata();
		break;

	case SCENE_GAME:
		UpdateEffect();
		UpdateGame();
		UpdateStagedata();
		break;

	case SCENE_RESULT:
		UpdateEffect();
		UpdateResult();
		UpdateStagedata();
		break;
	}

	UpdateFade();
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawScene(void)
{
	switch( g_SceneIndex )
	{
	case SCENE_NONE:
		break;

	case SCENE_LOGO:
		DrawLogo();
		DrawEffect();
		break;

	case SCENE_TITLE:
		DrawTitle();
		DrawEffect();
		break;

	case SCENE_SELECT:
		DrawStageSelect();
		DrawEffect();
		break;

	case SCENE_GAME:
		DrawGame();
		DrawEffect();
		break;

	case SCENE_RESULT:
		DrawResult();
		DrawEffect();
		break;
	}

	DrawFade();
}

/*------------------------------------------------------------------------------
   シーン遷移を要求する関数
------------------------------------------------------------------------------*/
void SetScene(SCENE index)
{
	//遷移先シーンを設定する
	g_SceneNextIndex = index;
}

/*------------------------------------------------------------------------------
   遷移を要求がある場合にシーンを切り替える関数
------------------------------------------------------------------------------*/
void CheckScene(void)
{
	//現在のシーンと遷移先シーンが違っていたら
	if( g_SceneIndex != g_SceneNextIndex )
	{
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