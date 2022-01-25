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
bool Abovemap = false;			//上から視点のボタン
bool pausemission = false;	//ミッションのボタン

bool pauseonce = false;
bool stretching = false;

bool gameover_pause = false;
bool goal2_pause = false;
bool deleteonce = false;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPause(void)
{
	deleteonce = false;

	//テクスチャ読み込み

	STAGEDATA* p_Stagedata = GetStagedata();
	pause = false;

	gameover_pause = false;
	goal2_pause = false;
	
	//初期化
	pause_select_once = false;
	now_pause_select_EffectArray = -1;
	pause_select_once_time = 0;



	//ポーズボタンの表示
	SetEffect(102, D3DXVECTOR2(50, 50), D3DXVECTOR2(50, 50), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
		0.0f, 1.0f, 30, 999, 0, 90,
		0.0f, 0.0f, 0);


	pauseclickuse = false;	//ポーズ画面を開いたかどうか
	Abovemap = false;			//上から視点のボタン
	pausemission = false;	//ミッションのボタン
	pause_cool = CLICK_COOLTIME;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPause(void)
{
	gameover_pause = false;
	goal2_pause = false;
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
	if (goal2_pause == false)
	{
		if (gameover_pause == false)
		{
			if (pauseclickuse == false)
			{
				if (pause_cool <= 0)
				{
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
							pause_cool = CLICK_COOLTIME;
						}
					}
				}
			}
			//ポーズ画面を開いている状態
			if (pauseclickuse)
			{
				if (stretching == false) {
					//明るくするなら48暗くするなら4
					now_pause_select_EffectArray =
						SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
							D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2), 0,
							0.0f, 0.25f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);
				}

				//ポーズボタンの表示
				SetEffect(103, D3DXVECTOR2(50, 50), D3DXVECTOR2(50, 50), 0,
					D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

				// 上からのマップ
				SetEffect(64, D3DXVECTOR2(50, 150), D3DXVECTOR2(50, 150), 0,
					D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

				// リトライ
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

				//プレイヤー配置に戻る
				SetEffect(99, D3DXVECTOR2(100.0f, 550.0f), D3DXVECTOR2(100.0f, 550.0f), 1,
					D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);

				if (pause_cool <= 0)
				{
					//ポーズ画面の中のボタン(上から視点、リトライ、ミッション、ステージ選択)

						///////上からのマップ/////////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 112.0f && mouse_pos_Y < 180.0f)
					{
						pausemouseuse = true;

						// 選択しましたマーク
						SetEffect(73, D3DXVECTOR2(50, 150), D3DXVECTOR2(50, 150), 0,
							D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);

						if (pausemouseuse && mouse_Lclick)
						{
							//Abovemap = !Abovemap;
							pause_cool = CLICK_COOLTIME;
							if (Abovemap)
							{
								pausemission = false;
								DeleteMissionPause();


								/*DrawBGaboveForPlacement();
								DrawPlayerForPlacement();*/
							}
							else
							{
								Abovemap = true;
							}
						}
					}

					/////////////リトライ//////////////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 212.0f && mouse_pos_Y < 280.0f)
					{

						pausemouseuse = true;

						// 選択しましたマーク
						SetEffect(73, D3DXVECTOR2(50, 250), D3DXVECTOR2(50, 250), 0,
							D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);

						if (pausemouseuse && mouse_Lclick)
						{
							SceneTransition(SCENE_GAME);
							//pauseclickuse = false;
							////上から視点かミッションを開いていたら閉じる
							//Abovemap = false;
							//pausemission = false;
							//DeleteMissionPause();
						}


					}

					////////ミッション/////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 312.0f && mouse_pos_Y < 380.0f)
					{
						pausemouseuse = true;
						if (pausemission == false)
						{
							// 選択しましたマーク
							SetEffect(73, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
								D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
								0.0f, 1.0f, 0, 1, 0, 1,
								0.0f, 0.0f, 0);
						}
						//ミッションを表示する
						if (pausemouseuse && mouse_Lclick)
						{
							//aboveを開いてたら閉じる
							Abovemap = false;
							stretching = !stretching;

							pausemission = !pausemission;
							pause_cool = CLICK_COOLTIME;

							if (pausemission)
							{
								/*SetEffect(70, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
									D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
									0.0f, 1.0f, 0, 1, 0, 1,
									0.0f, 0.0f, 0);*/
								DrawMissionPause();
							}
							else
							{
								pausemission = false;
								stretching = false;
								DeleteMissionPause();
							}

						}

					}

					////////ステージ選択/////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 412.0f && mouse_pos_Y < 480.0f)
					{
						pausemouseuse = true;

						// 選択しましたマーク
						SetEffect(73, D3DXVECTOR2(50, 450), D3DXVECTOR2(50, 450), 0,
							D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);

						if (pausemouseuse && mouse_Lclick && (Abovemap || pausemission))
						{
							SceneTransition(SCENE_STAGE_SELECT);
							/*pauseclickuse = false;
							Abovemap = false;
							pausemission = false;
							DeleteMissionPause();*/

						}
						if (pausemouseuse && mouse_Lclick)
						{
							SceneTransition(SCENE_STAGE_SELECT);
							pauseclickuse = false;
						}

					}

					////////配置から/////////
					if (mouse_pos_X > 10.0f && mouse_pos_X < 175.0f && mouse_pos_Y > 500.0f && mouse_pos_Y < 600.0f)
					{
						pausemouseuse = true;

						// 選択しましたマーク
						SetEffect(73, D3DXVECTOR2(100, 550), D3DXVECTOR2(100, 550), 0,
							D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 1, 0, 1,
							0.0f, 0.0f, 0);

						if (pausemouseuse && mouse_Lclick)
						{
							SceneTransition(SCENE_PLACEMENT);
							//pauseclickuse = false;
							////上から視点かミッションを開いていたら閉じる
							//Abovemap = false;
							//pausemission = false;
							//DeleteMissionPause();
						}

					}

					//ポーズボタン閉じる 1200 700	300 300
					if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 15.0f && mouse_pos_Y < 85.0f)
					{
						//g_Pause.selectpush = 0;
						pausemouseuse = true;

						// マウスが表示にあっている状態で左クリックをしたら
						if (pausemouseuse && mouse_Lclick)
						{
							//ポーズ画面を閉じる
							pauseclickuse = false;
							pausemission = false;
							Abovemap = false;
							DeleteMissionPause();
							stretching = false;
							pause_cool = CLICK_COOLTIME;
						}
					}

					
				}
				//バツ印の表示
				if (pausemission)
				{
					SetEffect(70, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				
					//画面の360より右を押したらポーズ画面をすべて閉じる
					if (mouse_pos_X > 360.0f)
					{
						
						if (mouse_Lclick)
						{
							pauseclickuse = false;
							pausemission = false;
							Abovemap = false;
							DeleteMissionPause();
							stretching = false;
							//pause_cool = CLICK_COOLTIME;
						}
					}
				

			}
		}
	}
	
	if (deleteonce == false)
	{
		if (gameover_pause == true || goal2_pause == true)
		{
			deleteonce = true;

			pauseclickuse = false;
			pausemission = false;
			Abovemap = false;
			DeleteMissionPause();
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
	if (Abovemap)
	{
		//明るくするなら48暗くするなら4
		ChangeEffect(now_pause_select_EffectArray, 4, D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
			0.0f, 0.5f, 0, 1, 0, 1,
			0.0f, 0.0f, 0);

			//バツ印の表示
			SetEffect(70, D3DXVECTOR2(50, 150), D3DXVECTOR2(50, 150), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				0.0f, 1.0f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);

			DrawBGaboveForPlacement();
			DrawPlayerForPlacement();
	}

	//ミッション
	if (pausemission)
	{
		if (stretching == true) {
			//明るくするなら48暗くするなら4
			ChangeEffect(now_pause_select_EffectArray, 4, D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), 0,
				D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
				0.0f, 0.5f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);
		
		}

		////バツ印の表示
		//SetEffect(70, D3DXVECTOR2(50, 350), D3DXVECTOR2(50, 350), 0,
		//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		//	0.0f, 1.0f, 0, 1, 0, 1,
		//	0.0f, 0.0f, 0);
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

void GoalTrue_Pause()
{
	goal2_pause = true;

	return;
}

void GameoverTrue_Pause()
{
	gameover_pause = true;

	return;
}
