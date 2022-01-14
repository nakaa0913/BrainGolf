/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :
														 Date   :a
--------------------------------------------------------------------------------

==============================================================================*/

#include<iostream>
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
#include "stagedata.h"
#include "FileDataManagement.h"
#include "worldselect.h"
#include "keyboard.h"
#include "mouse.h"
#include "placement.h"
#include "savedata.h"

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/
#define USE_STAGE_MAX	(20)	// 実際に実装されて使うステージの数
#define PAGE_MAX		(2)		// ページ数

/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static STAGESELECT g_StageSelect;

static int	g_TextureNo = 0;	// テクスチャ情報
static int	g_BGMNo = 0;		// BGM識別子
static int g_SENo = 0;

int			UseArrow;
int			UseEnter;


//static int world_1_background;
//static int world_2_background;
//static int world_3_background;
//static int world_4_background;
//static int world_5_background;
//
//static int world_1_stagechoice;
//static int world_2_stagechoice;
//static int world_3_stagechoice;
//static int world_4_stagechoice;
//static int world_5_stagechoice;
//
//static int world_1_mission;

int NowWorld = 0;				   //今選択してるやつ
int tex_NowWorld_background = -1;  //背景
int tex_NowWorld_stagechoice = -1; //ステージ選択の四角いやつ
int tex_NowWorld_mission = -1;     //ミッション

// 選択したときの処理で使う
int now_stage_select_EffectArray = -1;
int stage_EffectArray[USE_STAGE_MAX];
int stage_star_EffectArray[USE_STAGE_MAX][MAX_MISSION];
bool stage_select_once = false;
int stage_select_once_time = 0;

bool StageDecision = false;				// エンターか左クリックでステージを確定させたら他のとこに移動できなくする

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitStageSelect(void)
{

	g_StageSelect.select_x = 0;
	g_StageSelect.select_y = 0;

	StageDecision = false;

	UseArrow = 0;
	UseEnter = 0;

	// 並べたステージを表示するときのエフェクト配列の初期化
	for (int i = 0; i < USE_STAGE_MAX; i++)
	{
		stage_EffectArray[i] = -1;
		for (int j = 0; j < MAX_MISSION; j++)
		{
			stage_star_EffectArray[i][j] = -1;
		}
	}



	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)をループ指定すると無限ループ
	PlaySound(g_BGMNo, -1);

	g_StageSelect.selecttime = 0;

	NowWorld = GetNowWorld();


	//
	if (NowWorld == 1)
	{
		tex_NowWorld_background = 15;
		tex_NowWorld_stagechoice = 20;
		tex_NowWorld_mission = 25;
	}

	if (NowWorld == 2)
	{
		tex_NowWorld_background = 16;
		tex_NowWorld_stagechoice = 21;
		tex_NowWorld_mission = 26;
	}

	if (NowWorld == 3)
	{
		tex_NowWorld_background = 17;
		tex_NowWorld_stagechoice = 22;
		tex_NowWorld_mission = 27;
	}

	if (NowWorld == 4)
	{
		tex_NowWorld_background = 18;
		tex_NowWorld_stagechoice = 23;
		tex_NowWorld_mission = 28;
	}

	if (NowWorld == 5)
	{
		tex_NowWorld_background = 19;
		tex_NowWorld_stagechoice = 24;
		tex_NowWorld_mission = 29;
	}


	StartStageSelectScreen();

	// セーブデータからゲットしてる星の数を読み込む
	int StageStar = GetStar(NowWorld);

	int Number_EffectArray[2] = { 0,0 };
	int* p_Number_EffectArray = Number_EffectArray;
	// セーブデータから読み込んだ全ての星の数の表示
	SetEffectNumber(StageStar, p_Number_EffectArray, D3DXVECTOR2(250.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// 全ての星の数(30)の表示
	SetEffectNumber(30, p_Number_EffectArray, D3DXVECTOR2(400.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	stage_select_once = false;
	now_stage_select_EffectArray = -1;
	stage_select_once_time = 0;

	return;
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitStageSelect()
{
	UnloadTexture("data/TEXTURE/select/stage_select.png");
	StopSoundAll();
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateStageSelect(void)
{
	if (Keyboard_IsKeyDown(KK_Q))
		ChangePage();
	
	if (StageDecision == false)
	{
		//マウスの座標を取得
		float mouse_pos_X = GetMousePosX();
		float mouse_pos_Y = GetMousePosY();
		bool mouse_Lclick = GetMouseLClick();
		bool mouseuse = false;

		// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
		int OldStageSelectX = g_StageSelect.select_x;
		int OldStageSelectY = g_StageSelect.select_y;

		// 移動キーが押された時の処理
		if (g_StageSelect.selectcooltime <= 0)
		{

			if (g_StageSelect.select_x == 0) {
				
				if (g_StageSelect.select_y == 0)
				{
					//(0,0)の処理
					if (Keyboard_IsKeyDown(KK_UP))
					{
						g_StageSelect.select_y = 3;
					}

					if (Keyboard_IsKeyDown(KK_DOWN))
					{
						g_StageSelect.select_y = 1;
					}
				}
				//(0,1)の処理
				else if (g_StageSelect.select_y == 1)
				{
					if (Keyboard_IsKeyDown(KK_UP))
					{
						g_StageSelect.select_y = 0;
					}
					//下押したら「ワールド選択に戻るボタン」にいく
					if (Keyboard_IsKeyDown(KK_DOWN))
					{
						g_StageSelect.select_y = 3;
					}
				}

				//(0,3)の処理
				else if (g_StageSelect.select_y == 3)
				{
					if (Keyboard_IsKeyDown(KK_UP))
					{
						g_StageSelect.select_y = 1;
					}

					if (Keyboard_IsKeyDown(KK_DOWN))
					{
						g_StageSelect.select_y = 0;
					}
					//ENTERでタイトルへ戻る
					if (Keyboard_IsKeyDown(KK_ENTER))
					{
						SceneTransition(SCENE_TITLE);

						if (UseEnter == 0)
						{
							g_SENo = LoadSound("data/SE/Accent03-1.wav");
							PlaySound(g_SENo, 0);
							UseEnter = 1;
						}
					}
					////ENTERでシーンワールド選択にいく
					//if (Keyboard_IsKeyDown(KK_ENTER))
					//{
					//	SceneTransition(SCENE_WORLD_SELECT);
					//}
				}
				//y = 3以外の時に左右移動ができる（3は「ワールド選択に戻るボタン」）
				if (g_StageSelect.select_y != 3)
				{
					// 右
					if (Keyboard_IsKeyDown(KK_RIGHT))
					{
						g_StageSelect.select_x++;
					}
					// 左
					if (Keyboard_IsKeyDown(KK_LEFT))
					{
						g_StageSelect.select_x--;
					}
				}
			}
			//x = 0じゃないときの処理
			else {
				// 上
				if (Keyboard_IsKeyDown(KK_UP))
				{
					g_StageSelect.select_y--;
				}
				// 下
				if (Keyboard_IsKeyDown(KK_DOWN))
				{
					g_StageSelect.select_y++;
				}
				// 右
				if (Keyboard_IsKeyDown(KK_RIGHT))
				{
					g_StageSelect.select_x++;
				}
				// 左
				if (Keyboard_IsKeyDown(KK_LEFT))
				{
					g_StageSelect.select_x--;
				}
			}

			if (g_StageSelect.selecttime >= 1)
			{
				// マウスでの操作
				// ステージ選択の時の原点となる場所
				float	effectpos_x = 240.0f;			    // xの原点(0,0を選択しているとき)
				float	effectpos_y = 200.0f;			    // yの原点(0,0を選択しているとき)

				// ステージ選択の時1個離れたらこれだけ離れるよってやつ
				float while_x = 240.0f;
				float while_y = 240.0f;

				//ステージ選択
				for (int x = 0; x < SELECT_MAX_X; x++)
				{
					for (int y = 0; y < SELECT_MAX_Y; y++)
					{
						// 現在の座標を求める
						float effectnow_x = effectpos_x + while_x * x;
						float effectnow_y = effectpos_y + while_y * y;

						if (mouse_pos_X > effectnow_x - 50.0f && mouse_pos_X < effectnow_x + 50.0f && mouse_pos_Y > effectnow_y - 50.0f && mouse_pos_Y < effectnow_y + 50.0f)
						{
							g_StageSelect.select_x = x;
							g_StageSelect.select_y = y;
							mouseuse = true;
						}

					}
				}


				//ワールド選択へ戻る 240 700
				if (mouse_pos_X > 180.0f && mouse_pos_X < 280.0f && mouse_pos_Y > 650.0f && mouse_pos_Y < 750.0f)
				{
					g_StageSelect.select_x = 0;
					g_StageSelect.select_y = 3;
					mouseuse = true;
				}
			}


			// 限界値による修正の処理

			//xが5以上なら0にする（右から左）
			if (g_StageSelect.select_x >= SELECT_MAX_X)
				g_StageSelect.select_x = 0;

			//xが-1なら4にする（左から右）
			if (g_StageSelect.select_x < 0 && g_StageSelect.select_x >= -1)
				g_StageSelect.select_x = SELECT_MAX_X - 1;

			//yが2なら0にする（下から上）
			if (g_StageSelect.select_y > 1 && g_StageSelect.select_y <= SELECT_MAX_Y)
			{
				g_StageSelect.select_y = 0;
			}

			//yが4なら3にする（下から上）
			if (g_StageSelect.select_y < 5 && g_StageSelect.select_y >= 4)
			{
				g_StageSelect.select_y = 0;
			}
			//yが0未満なら1にする（上から下）
			if (g_StageSelect.select_y < 0)
				g_StageSelect.select_y = SELECT_MAX_Y - 1;

		}

		// 変更を確認する処理

		// もし前のフレームから変化があった場合のみエフェクトなどを変化させる
		bool Change = false;
		if (OldStageSelectX != g_StageSelect.select_x ||
			OldStageSelectY != g_StageSelect.select_y)
			Change = true;

		// 変更があった場合、初期化と新しいもののセット
		if (Change == true)
		{
			g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			EffectBreak(now_stage_select_EffectArray);
			DeleteMissionStageSelect();
			stage_select_once = false;
			stage_select_once_time = 0;
		}


		// 決定してシーンが変わる処理

		// エンターキーを押してゲームスタートをする処理
		if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
		{
			StageDecision = true;
			// 移動入力のとこですでにステージデータはもらっているのでこのままいってOK
			g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			// プレイヤー配置フェーズに行く前に前回の配置情報をリセットする
			ResetPlacementArray();
			SceneTransition(SCENE_PLACEMENT);

			g_SENo = LoadSound("data/SE/Accent03-1.wav");
			PlaySound(g_SENo, 0);
		}

		// マウスが表示にあっている状態で左クリックをしたら
		if (mouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
		{
			g_SENo = LoadSound("data/SE/Accent03-1.wav");
			PlaySound(g_SENo, 0);

			StageDecision = true;
			// 移動入力のとこですでにステージデータはもらっているのでこのままいってOK
			g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
			// プレイヤー配置フェーズに行く前に前回の配置情報をリセットする
			ResetPlacementArray();
			if (g_StageSelect.select_x == 0 && g_StageSelect.select_y == 3)
			{
				SceneTransition(SCENE_TITLE);
			}
			else
			{
				SceneTransition(SCENE_PLACEMENT);
			}
		}

	}


	// ステージ選択の時の原点となる場所
	float	stage_origin_x = 240.0f;			    // xの原点(0,0を選択しているとき)
	float	stage_origin_y = 200.0f;			    // yの原点(0,0を選択しているとき)

	// ステージ選択の時1個離れたらこれだけ離れるよってやつ
	float interval_x = 240.0f;
	float interval_y = 240.0f;

	if (stage_select_once == false)
	{
		stage_select_once = true;

		// ステージデータを受け取る,ミッションやマップの表示で使うため。
		// xとyからマップの番号を計算する
		int stagenum = (SELECT_MAX_X * g_StageSelect.select_y) + (g_StageSelect.select_x + 1);
		SetStageData(stagenum);

		if (g_StageSelect.select_y != 3)
		{
			// ステージデータを受け取った(更新された)のでミッションを表示させる
			DrawMissionStageSelect();
		}


		

		//ステージ選択
		for (int x = 0; x < SELECT_MAX_X; x++)
		{
			for (int y = 0; y < SELECT_MAX_Y; y++)
			{
				// 現在の座標を求める
				float now_x = stage_origin_x + interval_x * x;
				float now_y = stage_origin_y + interval_y * y;

				// 検索。選択しているとこを見つけて大きいサイズで表示。
				if (g_StageSelect.select_x == x)
				{
					if (g_StageSelect.select_y == y)
					{
						now_stage_select_EffectArray =
							SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
								D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
								1.0f, 1.0f, 0, 999, 0, 60,
								0.0f, 0.0f, 0);

						g_SENo = LoadSound("data/SE/Accent03-1.wav");
						PlaySound(g_SENo, 0);
					}
				}

				
			}


		}

		// タイトルに戻る処理 (ワールド選択に戻るボタンの表示)
		if (g_StageSelect.select_x == 0 && g_StageSelect.select_y == 3)
		{
			SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
				D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
				0.0f, 1.0f, 0, 999, 0, 60,
				0.0f, 0.0f, 0);
		}
	}


	// 選択した状態が続いてる場合trueなのでここをとおる
	if (stage_select_once == true)
	{
		if (stage_select_once_time % 60 == 0)
		{
			ChangeEffectCount(now_stage_select_EffectArray, 0);
		}


		// 選択されてからの時間が増えていく
		stage_select_once_time++;
	}




	if (g_StageSelect.selectcooltime > 0)
		g_StageSelect.selectcooltime--;


	g_StageSelect.selecttime++;

}

STAGESELECT* GetStageSelect()
{
	return &g_StageSelect;
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawStageSelect(void)
{



	//// １枚のポリゴンの頂点とテクスチャ座標を設定
	//DrawSpriteColorRotate(tex_NowWorld_background, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR (1.0f, 1.0f, 1.0f, 1.0f), 1.0f);

	/*static int world_1_background;
	static int world_2_stagechoice;
	static int world_3_mission;
	static int world_4_selectstar;*/

}

void StartStageSelectScreen()
{
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	//背景表示
	SetEffect(tex_NowWorld_background, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
		D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
		0.0f, 1.0f, 100, 999, 0, 180,
		0.0f, 0.0f, 0);

	// ステージ選択の時の原点となる場所
	float	stage_origin_x = 240.0f;			    // xの原点(0,0を選択しているとき)
	float	stage_origin_y = 200.0f;			    // yの原点(0,0を選択しているとき)

	// ステージ選択の時1個離れたらこれだけ離れるよってやつ
	float interval_x = 240.0f;
	float interval_y = 240.0f;


	float page_interval_x = 300.0f;



	//ステージ選択
	for (int page = 0; page < PAGE_MAX; page++)
	{
		for (int x = 0; x < SELECT_MAX_X; x++)
		{
			for (int y = 0; y < SELECT_MAX_Y; y++)
			{
				//int now_num = x + y * SELECT_MAX_X + (page * 10);
				int NowWorld_stagenum = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (page * 10);	// 0~19

				// 現在の座標を求める
				float now_x = stage_origin_x + interval_x * x + page * page_interval_x;
				float now_y = stage_origin_y + interval_y * y;

				// 選択されてないときの表示を出す(ステージすべて)
				stage_EffectArray[NowWorld_stagenum] =
					SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
						D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
						0.0f, 1.0f, 0, 999, 0, 0,
						0.0f, 0.0f, 0);

				// ミッションをクリアしているなら表示する
				if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
				{
					//星
					stage_star_EffectArray[NowWorld_stagenum][0] =
					SetEffect(83, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}

				// ミッションをクリアしているなら表示する
				if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
				{
					//星
					stage_star_EffectArray[NowWorld_stagenum][1] =
					SetEffect(84, D3DXVECTOR2(now_x - 50, now_y), D3DXVECTOR2(now_x - 50, now_y), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}

				// ミッションをクリアしているなら表示する
				if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
				{
					//星
					stage_star_EffectArray[NowWorld_stagenum][2] =
					SetEffect(85, D3DXVECTOR2(now_x + 50, now_y), D3DXVECTOR2(now_x + 50, now_y), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}
			}
		}
	}

	// タイトルに戻る処理
	SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	//どのこの星？
	SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 0,
		0.0f, 0.0f, 0);

	// セーブデータからゲットしてる星の数を読み込む
	// 多分左上のやつら？
	int StageStar = GetStar(NowWorld);

	int Number_EffectArray[2] = { 0,0 };
	int* p_Number_EffectArray = Number_EffectArray;
	// セーブデータから読み込んだ全ての星の数の表示
	SetEffectNumber(StageStar, p_Number_EffectArray, D3DXVECTOR2(250.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// 全ての星の数(30)の表示
	SetEffectNumber(30, p_Number_EffectArray, D3DXVECTOR2(400.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		0.0f, 1.0f, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	return;
}

void ChangePage()
{
	{
		SAVEDATA* p_Savedata = GetSavedata();
		STAGEDATA* p_Stagedata = GetStagedata();

		////背景表示
		//SetEffect(tex_NowWorld_background, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
		//	D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
		//	0.0f, 1.0f, 100, 999, 0, 180,
		//	0.0f, 0.0f, 0);

		// ステージ選択の時の原点となる場所
		float	stage_origin_x = 240.0f;			    // xの原点(0,0を選択しているとき)
		float	stage_origin_y = 200.0f;			    // yの原点(0,0を選択しているとき)

		// ステージ選択の時1個離れたらこれだけ離れるよってやつ
		float interval_x = 240.0f;
		float interval_y = 240.0f;


		float page_interval_x = 300.0f;
		float change_page_interval_x = interval_x * SELECT_MAX_X + page_interval_x;

		float change_page_interval = -change_page_interval_x;

		//ステージ選択
		for (int page = 0; page < PAGE_MAX; page++)
		{
			for (int x = 0; x < SELECT_MAX_X; x++)
			{
				for (int y = 0; y < SELECT_MAX_Y; y++)
				{
					//int now_num = x + y * SELECT_MAX_X + (page * 10);
					int NowWorld_stagenum = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (page * 10);	// 0~19

					// 現在の座標を求める
					float now_x = stage_origin_x + interval_x * x + page * page_interval_x;
					float now_y = stage_origin_y + interval_y * y;

					D3DXVECTOR2 now_stagePos	= GetEffectPos(stage_EffectArray[NowWorld_stagenum]);
					D3DXVECTOR2 now_stage_starPos[3];
					now_stage_starPos[0]= GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][0]);
					now_stage_starPos[1]= GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][1]);
					now_stage_starPos[2]= GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][2]);

					// 選択されてないときの表示を出す(ステージすべて)
						ChangeEffect(stage_EffectArray[NowWorld_stagenum], tex_NowWorld_stagechoice, now_stagePos, D3DXVECTOR2(now_stagePos.x + change_page_interval, now_stagePos.y), 1,
							D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							0.0f, 1.0f, 0, 999, 0, 0,
							0.0f, 0.0f, 0);

					// ミッションをクリアしているなら表示する
					if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
					{
						//星
						ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][0], 83, now_stage_starPos[0], D3DXVECTOR2(now_stage_starPos[0].x + change_page_interval, now_stage_starPos[0].y), 1,
								D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
								0.0f, 1.0f, 120, 999, 0, 60,
								0.0f, 0.0f, 0);
					}

					// ミッションをクリアしているなら表示する
					if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
					{
						//星
						ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][1], 84, now_stage_starPos[1], D3DXVECTOR2(now_stage_starPos[1].x + change_page_interval, now_stage_starPos[1].y), 1,
								D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
								0.0f, 1.0f, 120, 999, 0, 60,
								0.0f, 0.0f, 0);
					}

					// ミッションをクリアしているなら表示する
					if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
					{
						//星
						ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][2], 85, now_stage_starPos[2], D3DXVECTOR2(now_stage_starPos[2].x + change_page_interval, now_stage_starPos[2].y), 1,
								D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
								0.0f, 1.0f, 120, 999, 0, 60,
								0.0f, 0.0f, 0);
					}
				}
			}
		}

		//// タイトルに戻る処理
		//SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
		//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		//	0.0f, 1.0f, 0, 999, 0, 0,
		//	0.0f, 0.0f, 0);

		////どのこの星？
		//SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		//	D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
		//	0.0f, 1.0f, 0, 1, 0, 0,
		//	0.0f, 0.0f, 0);

		//// セーブデータからゲットしてる星の数を読み込む
		//// 多分左上のやつら？
		//int StageStar = GetStar(NowWorld);

		//int Number_EffectArray[2] = { 0,0 };
		//int* p_Number_EffectArray = Number_EffectArray;
		//// セーブデータから読み込んだ全ての星の数の表示
		//SetEffectNumber(StageStar, p_Number_EffectArray, D3DXVECTOR2(250.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		//	D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		//	0.0f, 1.0f, 0, 999, 0, 0,
		//	0.0f, 0.0f, 0);

		//// 全ての星の数(30)の表示
		//SetEffectNumber(30, p_Number_EffectArray, D3DXVECTOR2(400.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
		//	D3DXVECTOR2(60.0f, 50.0f), D3DXVECTOR2(60.0f, 50.0f), 0,
		//	0.0f, 1.0f, 0, 999, 0, 0,
		//	0.0f, 0.0f, 0);

		return;
	}
}