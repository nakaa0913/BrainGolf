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
#define CLICK_COOLTIME	(20)			// クリックのクールタイム
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

bool pauseclickuse = false;
bool pauseopen = false;
bool Above = false;
int ClickCool = CLICK_COOLTIME;



//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPause(void)
{
	//テクスチャ読み込み

	STAGEDATA* p_Stagedata = GetStagedata();
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



	//// 今がポーズ状態なら
	//if (pause == true)
	//{

	//	// とりあえずはったりだけ
	//	SetEffect(62, D3DXVECTOR2(400, 400), D3DXVECTOR2(400, 400), 0,
	//		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
	//		0.0f, 1.0f, 0, 1, 0, 30,
	//		0.0f, 0.0f, 0);



	//}



	////　Pキーが押されてポーズ状態を切り替える処理
	//if (pause_cool <= 0)
	//{
	//	if (Keyboard_IsKeyDown(KK_P))
	//	{
	//		pause = !pause;

	//		pause_cool = PUSHKEY_COOLTIME;

	//	}
	//}



	// マウスの座標を使っての入力処理

		//1 1200 700	300 300
	if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 15.0f && mouse_pos_Y < 85.0f)
	{
		//g_Pause.selectpush = 0;
		pausemouseuse = true;

		// マウスが表示にあっている状態で左クリックをしたら
		if (pausemouseuse && mouse_Lclick)
		{
			//ポーズ画面を開く
			pauseclickuse = true;
		}
	}
	//ポーズ画面を開いている状態
	if (pauseclickuse)
	{


		//明るくするなら48暗くするなら4
		SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 1,
			D3DXVECTOR2(0, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		// 上からのマップ
		SetEffect(64, D3DXVECTOR2(50, 150), D3DXVECTOR2(50, 150), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);

		// 配置からやり直す
		SetEffect(65, D3DXVECTOR2(50, 250), D3DXVECTOR2(50, 250), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);

		// ミッション
		SetEffect(66, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);

		// ステージ選択
		SetEffect(67, D3DXVECTOR2(50, 450), D3DXVECTOR2(50, 450), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
			0.0f, 1.0f, 0, 1, 0, 30,
			0.0f, 0.0f, 0);

		if (ClickCool <= 0)
		{
			//ポーズ画面のボタンを押していなかったら（ポーズ画面は開いている状態）
			if (pauseopen == false)
			{
				///////上からのマップ/////////////
				if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 112.0f && mouse_pos_Y < 180.0f)
				{
					pausemouseuse = true;
					if (Above == false)
					{
						if (pausemouseuse && mouse_Lclick)
						{
							Above = true;
							ClickCool = CLICK_COOLTIME;
							pauseopen = true;
						}
					}
					if (ClickCool <= 0)
					{
						if (Above == true && pauseopen == true)
						{
							if (mouse_Lclick)
							{
								Above = false;
								ClickCool = CLICK_COOLTIME;
								pauseclickuse = false;

							}
						}
					}
				}

				/////////////配置からやり直す//////////////////
				if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 212.0f && mouse_pos_Y < 280.0f)
				{
					pausemouseuse = true;
					if (pausemouseuse && mouse_Lclick)
					{
						SceneTransition(SCENE_PLACEMENT);
						pauseclickuse = false;
						//pauseopen = true;
					}

				}

				////////ミッション/////////
				if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 312.0f && mouse_pos_Y < 380.0f)
				{
					pausemouseuse = true;
					if (pauseopen == false)
					{
						if (pausemouseuse && mouse_Lclick)
						{
							pauseopen = true;
							DrawMissionPause();
							ClickCool = CLICK_COOLTIME;
						}
					}
					if (pauseopen == true)
					{
						if (pausemouseuse && mouse_Lclick)
						{
							pauseopen = false;
							//DeleteMissionPause();
							ClickCool = CLICK_COOLTIME;
						}
					}
				}

				////////ステージ選択/////////
				if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 412.0f && mouse_pos_Y < 480.0f)
				{
					pausemouseuse = true;
					if (pausemouseuse && mouse_Lclick)
					{
						SceneTransition(SCENE_STAGE_SELECT);
						pauseclickuse = false;
						//pauseopen = true;
					}
				}

			}
		}/////////////////


		if (mouse_pos_X > 360.0f)
		{
			if (mouse_Lclick)
			{
				pauseclickuse = false;
			}
		}
		//}
	}

	//bool Change = false;
	//if (pauseopen && pauseclickuse && mouse_Lclick)
	//	Change = true;
	//// 変更があった場合、初期化と新しいもののセット
	//if (Change == true)
	//{
	//	ClickCool = CLICK_COOLTIME;
	//	EffectBreak(now_pause_select_EffectArray);
	//	DeleteMissionPause();
	//	pause_select_once = false;
	//	pause_select_once_time = 0;


	//}

	if (pause_cool > 0)
		pause_cool--;

	if (ClickCool > 0)
		ClickCool--;
	//// 毎フレームカウントを増やす
	//g_Pause.goaltime++;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPause(void)
{
	 //上から視点の表示
	if (Above)
	{
		DrawBGaboveForPlacement();
		DrawPlayerForPlacement();
	}
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