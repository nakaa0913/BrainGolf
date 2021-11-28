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

bool pauseclickuse = false;	//ポーズ画面を開いたかどうか
bool pauseopen = false;		//ポーズ画面の中のボタンを押したかどうか
bool Above = false;			//上から視点のボタン
bool pausemission = false;	//ミッションのボタン



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


	pauseclickuse = false;	//ポーズ画面を開いたかどうか
	pauseopen = false;		//ポーズ画面の中のボタンを押したかどうか
	Above = false;			//上から視点のボタン
	pausemission = false;	//ミッションのボタン
	pause_cool = CLICK_COOLTIME;


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




	// マウスの座標を使っての入力処理

		//ポーズボタン 1200 700	300 300
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
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		// 配置からやり直す
		SetEffect(65, D3DXVECTOR2(50, 250), D3DXVECTOR2(50, 250), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		// ミッション
		SetEffect(66, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		// ステージ選択
		SetEffect(67, D3DXVECTOR2(50, 450), D3DXVECTOR2(50, 450), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		if (pause_cool <= 0)
		{
			//ポーズ画面の中のボタン(上から視点、リトライ、ミッション、ステージ選択)

				///////上からのマップ/////////////
			if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 112.0f && mouse_pos_Y < 180.0f)
			{
				pausemouseuse = true;

				if (pausemouseuse && mouse_Lclick)
				{
					Above = !Above;
					pause_cool = CLICK_COOLTIME;


					if (Above)
					{
						pauseopen = true;
					}
					else
					{
						pauseopen = false;
					}
				}


			}

			/////////////配置からやり直す//////////////////
			if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 212.0f && mouse_pos_Y < 280.0f)
			{
				//上から視点かミッションを開いていたら閉じる
				pausemouseuse = true;
				if (pausemouseuse && mouse_Lclick && (Above || pausemission))
				{
					SceneTransition(SCENE_PLACEMENT);
					pauseclickuse = false;
					Above = false;
					pausemission = false;
				}

				if (pausemouseuse && mouse_Lclick)
				{
					SceneTransition(SCENE_PLACEMENT);
					pauseclickuse = false;
				}

			}

			////////ミッション/////////
			if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 312.0f && mouse_pos_Y < 380.0f)
			{
				pausemouseuse = true;

				if (pausemouseuse && mouse_Lclick)
				{
					pausemission = !pausemission;
					pause_cool = CLICK_COOLTIME;

					if (pausemission)
					{
						DrawMissionPause();
						pauseopen = true;
					}
					else
					{
						DeleteMissionPause();
						pauseopen = false;
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



		//画面の360より右を押したらポーズ画面をすべて閉じる
		if (mouse_pos_X > 360.0f)
		{
			if (mouse_Lclick)
			{
				pauseclickuse = false;
				pauseopen = false;
				pausemission = false;
				Above = false;
				DeleteMissionPause();
			}
		}

	}






	if (pause_cool > 0)
		pause_cool--;


	

	/*if (ClickCool > 0)
		ClickCool--;*/
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
		/*void ChangeEffect(int use_array_num, int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
			float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
			float rot_angle1, float rot_angle2, int rot_moving_pattern, int SerialNumber);*/

		//明るくするなら48暗くするなら4
		SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 0.0f), 1,
			D3DXVECTOR2(0, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);
		
			DrawBGaboveForPlacement();
			DrawPlayerForPlacement();

			//バツ印の表示
			SetEffect(70, D3DXVECTOR2(50, 150), D3DXVECTOR2(50, 150), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		
	}

	//ミッション
	if (pausemission)
	{
		//明るくするなら48暗くするなら4
		SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 0.0f), 1,
			D3DXVECTOR2(0, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2), 1,
			0.0f, 0.5f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

		SetEffect(70, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, 1.0f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);
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