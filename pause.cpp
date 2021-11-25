/*==============================================================================

   頂点管理 [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include "pause.h"
#include "scene.h"
#include "fade.h"
#include "effect.h"
#include "mission.h"
#include "savedata.h"
#include "stagedata.h"
#include "keyboard.h"
#include "sound.h"
#include "mouse.h"
#include "pause.h"
#include "game.h"
#include "placement.h"

//#define GOAL_H (50)
//#define GOAL_W (50)
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

bool pause;			// 今がポーズ中かどうか
int pause_cool;		// ポーズ切り替えのクールタイム

int now_pause_select_EffectArray = -1;
bool pause_select_once = false;
int pause_select_once_time = 0;
//bool onlyOnce = true;
bool pausemouseuse = false;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPause(void)
{
	//テクスチャ読み込み


	pause = false;


	//初期化
	pause_select_once = false;
	now_pause_select_EffectArray = -1;
	pause_select_once_time = 0;



	//ポーズボタンの表示
	SetEffect(62, D3DXVECTOR2(50, 50), D3DXVECTOR2(50, 50), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
		0.0f, 1.0f, 30, 999, 0, 90,
		0.0f, 0.0f, 0);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPause(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePause(void)
{

	//マウスの座標を取得
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();

	// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
	/*int OldPauseSelect = g_Pause.selectpush;*/



	// 今がポーズ状態なら
	if (pause == true)
	{

		// とりあえずはったりだけ
		SetEffect(62, D3DXVECTOR2(400, 400), D3DXVECTOR2(400, 400), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);



	}



	//　Pキーが押されてポーズ状態を切り替える処理
	if (pause_cool <= 0)
	{
		if (Keyboard_IsKeyDown(KK_P))
		{
			pause = !pause;

			pause_cool = PUSHKEY_COOLTIME;

		}
	}


	////キー入力
	//if (g_Pause.selecttime <= 0)
	//{
	//	//ポーズボタンの表示
	//	if (Keyboard_IsKeyDown(KK_P))
	//	{
	//		//横1440
	//		//縦810
	//		g_Pause.selectpush++;

	//		//PauseTrue();
	//	}


	//	//ポーズボタンの表示
	//	if (g_Pause.selectpush == 1)
	//	{
	//		//ゲームクリア
	//		SetEffect(62, D3DXVECTOR2(50, 50), D3DXVECTOR2(50, 50), 0,
	//			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
	//			0.0f, 1.0f, 30, 999, 60, 30,
	//			0.0f, 0.0f, 0);
	//	}


	//	if (g_Pause.selectpush >= 2)
	//	{
	//		g_Pause.selectpush = 1;
	//	}


	//	if (g_Pause.selectpush < 0)
	//	{
	//		g_Pause.selectpush = 1;
	//	}

	//}

	//// マウスの座標を使っての入力処理
	////1 1200 700	300 300
	//if (mouse_pos_X > 1050.0f && mouse_pos_X < 1350.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
	//{
	//	g_Pause.selectpush = 0;
	//	pausemouseuse = true;
	//}
	////2 100 700		200 200
	//else if (mouse_pos_X > 60.0f && mouse_pos_X < 140.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
	//{
	//	g_Pause.selectpush = 1;
	//	pausemouseuse = true;
	//}

	//// マウスが押される位置にあって、左クリック押されていて、フェード処理中ではないとき
	//if (pausemouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
	//{
	//	//SetVolume(g_BGMNo, 0.1f);

	//	//STAGE_SELECTへ移行する
	//	SceneTransition(SCENE_STAGE_SELECT);
	//}


	//// もし前のフレームから変化があった場合のみエフェクトなどを変化させる
	//bool Change = false;
	//if (OldPauseSelect != g_Pause.selectpush)
	//	Change = true;

	//// 変更があった場合、初期化と新しいもののセット
	//if (Change == true)
	//{
	//	// 初期化と前回使われていたものの消去
	//	g_Pause.selecttime = 30;
	//	//EffectBreak(now_pause_select_EffectArray);		// 前の描写を消す
	//	pause_select_once = false;						// 1回も描写してないよにする
	//	pause_select_once_time = 0;						// 描写してからの時間のリセット
	//}

	//
	//if (g_Pause.selecttime >= 0)
	//	g_Pause.selecttime--;

	if (pause_cool > 0)
		pause_cool--;



	//// 毎フレームカウントを増やす
	//g_Pause.goaltime++;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPause(void)
{

}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
//PAUSE* GetPause(void)
//{
//	return &g_Pause;
//}


void SetPause(D3DXVECTOR2 pos)
{

}