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
int tex_Page_background_EffectArray[2] = { -1, -1 };  //ページ背景のための配列
int tex_StageNum_background_EffectArray[2] = { -1, -1 };  //ステージ番号(1枚絵で扱う)のための配列
int tex_Pin_EffectArray = -1;			// ピンのエフェクト配列
int tex_Waku_EffectArray = -1;			// 白枠のエフェクト配列
int tex_NowWorld_stagechoice = -1; //ステージ選択の四角いやつ
int tex_NowWorld_mission = -1;     //ミッション

// 選択したときの処理で使う
int now_stage_select_EffectArray = -1;			// ピン
int now_stage_selectWaku_EffectArray = -1;			// 白枠
int now_stagenum_select_EffectArray[2] = { -1, -1 };
int* p_now_stagenum_select_EffectArray = now_stagenum_select_EffectArray;
int stage_EffectArray[USE_STAGE_MAX];
int Arrow_EffectArray[2];				// 左矢印右矢印のための配列
int stage_star_EffectArray[USE_STAGE_MAX][MAX_MISSION];
bool stage_select_once = false;
int stage_select_once_time = 0;

bool StageDecision = false;				// エンターか左クリックでステージを確定させたら他のとこに移動できなくする

int change_cool = 30;

int change_count = 0;

static int cahngetime = 1;		// 60フレームかけてページが変わる

static bool changing = false;			// ページチェンジ中かどうか

static int now_page = 0;		// 現在開いているページ

int now_stagenum = -1;			// 1~20での現在のステージ番号

float change_page_interval = 0.0f;


//int stageNumber_EffectArray[2] = { 0, 0 };
//int* p_stageNumber_EffectArray[20];				// 20ステージ分の配列をポインターで用意する


int stageNumber_EffectArray[20][2];
//int* p_stageNumber_EffectArray;				// 20ステージ分の配列をポインターで用意する

int BackTitle_EffectArray = -1;


bool title_display = false;								//タイトルの表示（最初の1回だけとタイトルに戻る押した場合のみ）
bool title_display_once = false;						//タイトルの表示（SetEffectを1回だけ行うため）
int title_count = 0;									// タイトル表示でのカウント
bool title_click = false;								// タイトル表示でのクリックしたかどうか
int title_clickcount = 0;								// タイトル表示でのクリックしてからのカウント
int title_display_EffectAray[4] = { -1, -1, -1, -1 };
static int title_fade_count = 40;

bool BackTitle = false;
int BackTitlecount = 00;
static int BackTitleTime = 70;

bool changeOneTime = false;

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitStageSelect(void)
{
	changeOneTime = false;
	BackTitlecount = 0;
	BackTitle = false;

	BackTitle_EffectArray = -1;

	for (int i = 0; i < 20; i++)
	{
		stageNumber_EffectArray[i][0] = 0;
		stageNumber_EffectArray[i][1] = 0;
	}
	now_stagenum_select_EffectArray[0] = -1;
	now_stagenum_select_EffectArray[1] = -1;

	// 配置シーンから戻ってきたときに音楽が二重にならないように。
	StopSoundAll();

	now_page = 0;
	change_page_interval = 0.0f;

	change_count = 0;

	changing = false;

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



	g_BGMNo = LoadSound("data/BGM/飛んでバタフライ.wav");
	SetVolume(g_BGMNo, 0.8f);
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

	// セーブデータからゲットしてる星の数を読み込む
	int StageStar = GetStar(NowWorld);

	int Number_EffectArray[2] = { 0,0 };
	int* p_Number_EffectArray = Number_EffectArray;
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

	stage_select_once = false;
	now_stage_select_EffectArray = -1;
	now_stage_selectWaku_EffectArray = -1;
	stage_select_once_time = 0;

	Arrow_EffectArray[0] = -1;
	Arrow_EffectArray[1] = -1;
	now_stagenum_select_EffectArray[0] = -1;
	now_stagenum_select_EffectArray[1] = -1;

	change_cool = 30;

	StartStageSelectScreen();

	if (now_stagenum >= 11)
		ChangePageOneTime(1);


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
	//マウスの座標を取得
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouseuse = false;

	// タイトルへ戻る中じゃないときだけ動く
	if (BackTitle == false)
	{
		if (title_display == false)
		{
			if (title_display_once == false)
			{
				title_display_once = true;

				//// ステージぼかし
				//title_display_EffectAray[0] =
				//	SetEffectInReverse(95, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				//		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
				//		0.0f, 1.0f, 0, 999, 0, 1,
				//		0.0f, 0.0f, 0);

				//// 明るくするなら48暗くするなら4
				//title_display_EffectAray[1] =
				//	SetEffectInReverse(4, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				//		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
				//		0.0f, 0.4f, 0, 999, 0, 1,
				//		0.0f, 0.0f, 0);

				//// タイトルクリック指示
				//title_display_EffectAray[2] =
				//	SetEffectInReverse(93, D3DXVECTOR2(720, 300), D3DXVECTOR2(720, 300), 0,
				//		D3DXVECTOR2(1200.0f, 1200.0f), D3DXVECTOR2(1200.0f, 1200.0f), 0,
				//		0.0f, 1.0f, 0, 999, 0, 1,
				//		0.0f, 0.0f, 0);

				//// タイトルロゴ
				//title_display_EffectAray[3] =
				//	SetEffectInReverse(94, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				//		D3DXVECTOR2(1000.0f, 500.0f), D3DXVECTOR2(1000.0f, 500.0f), 0,
				//		0.0f, 1.0f, 0, 999, 0, 1,
				//		0.0f, 0.0f, 0);

				// タイトルロゴ
				title_display_EffectAray[3] =
					SetEffectInReverse(94, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
						D3DXVECTOR2(1000.0f, 500.0f), D3DXVECTOR2(1000.0f, 500.0f), 0,
						0.0f, 1.0f, 30, 999, 0, 1,
						0.0f, 0.0f, 0);

				// タイトルクリック指示
				title_display_EffectAray[2] =
					SetEffectInReverse(93, D3DXVECTOR2(720, 300), D3DXVECTOR2(720, 300), 0,
						D3DXVECTOR2(1200.0f, 1200.0f), D3DXVECTOR2(1200.0f, 1200.0f), 0,
						0.0f, 1.0f, 30, 999, 0, 1,
						0.0f, 0.0f, 0);

				// 明るくするなら48暗くするなら4
				title_display_EffectAray[1] =
					SetEffectInReverse(4, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
						D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
						0.0f, 0.4f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);

				// ステージぼかし
				title_display_EffectAray[0] =
					SetEffectInReverse(95, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
						D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);
			}

			if (mouse_Lclick && title_count > 60 && !title_click)
			{
				title_click = true;

				for (int i = 0; i < 4; i++)
				{
					if (i == 1)
					{
						ChangeEffect(title_display_EffectAray[i], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0, 0), 0,
							D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0, 0), 0,
							0.0f, 0.4f, 0, 1, title_fade_count, title_fade_count + 1,
							0.0f, 0.0f, 0);
					}
					else
					{
						ChangeEffect(title_display_EffectAray[i], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0, 0), 0,
							D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0, 0), 0,
							0.0f, 1.0f, 0, 1, title_fade_count, title_fade_count + 1,
							0.0f, 0.0f, 0);
					}
				}

				//ChangeEffect(title_display_EffectAray[0], 95, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				//	D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
				//	0.0f, 1.0f, 0, 1, title_fade_count, title_fade_count + 1,
				//	0.0f, 0.0f, 0);

				//ChangeEffect(title_display_EffectAray[1], 4, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				//	D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
				//	0.0f, 1.0f, 0, 1, title_fade_count, title_fade_count + 1,
				//	0.0f, 0.0f, 0);

				//ChangeEffect(title_display_EffectAray[2], 93, D3DXVECTOR2(720, 300), D3DXVECTOR2(720, 300), 0,
				//	D3DXVECTOR2(1200.0f, 1200.0f), D3DXVECTOR2(1200.0f, 1200.0f), 0,
				//	0.0f, 1.0f, 0, 1, title_fade_count, title_fade_count + 1,
				//	0.0f, 0.0f, 0);

				//ChangeEffect(title_display_EffectAray[3], 94, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				//	D3DXVECTOR2(1000.0f, 500.0f), D3DXVECTOR2(1000.0f, 500.0f), 0,
				//	0.0f, 1.0f, 0, 1, title_fade_count, title_fade_count + 1,
				//	0.0f, 0.0f, 0);
			}

			title_count++;

			if (title_click)
			{
				if (title_clickcount > title_fade_count)
					title_display = true;

				title_clickcount++;
			}
		}




		if (change_cool <= 0)
			changing = false;
		else
			changing = true;

		if (change_cool > 0)
			change_cool--;


		// ページチェンジ中ではないときに普通に動く
		if (changing == false)
		{
			change_count = 0;		// チェンジ中の時のみ増える。ここでリセットしておく

			if (Keyboard_IsKeyDown(KK_E))
			{
				if (change_cool <= 0)
				{
					change_cool = 60;
					ChangePage(1);
					return;
				}
			}
			if (Keyboard_IsKeyDown(KK_Q))
			{
				if (change_cool <= 0)
				{
					change_cool = 60;
					ChangePage(-1);
					return;
				}
			}

			////マウスの座標を取得
			//float mouse_pos_X = GetMousePosX();
			//float mouse_pos_Y = GetMousePosY();
			//bool mouse_Lclick = GetMouseLClick();
			//bool mouseuse = false;

			// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
			int OldStageSelectX = g_StageSelect.select_x;
			int OldStageSelectY = g_StageSelect.select_y;


			// 移動キーが押された時の処理
			if (g_StageSelect.selectcooltime <= 0)
			{
				//if (Keyboard_IsKeyDown(KK_UP) && g_StageSelect.select_x != 5 && g_StageSelect.select_x != 6)
				//{
				//	if (g_StageSelect.select_y == 0 && g_StageSelect.select_x == 0)		// 0,0の時上を押すとタイトルへ行くになる
				//		g_StageSelect.select_y = 2;
				//	else if (g_StageSelect.select_y == 0)								// 最上段の時上を押すと最下層に行く
				//		g_StageSelect.select_y = 1;
				//	else
				//		g_StageSelect.select_y--;										// 通常
				//	g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
				//}
				//if (Keyboard_IsKeyDown(KK_DOWN) && g_StageSelect.select_x != 5 && g_StageSelect.select_x != 6)
				//{
				//	if (g_StageSelect.select_y == 2 && g_StageSelect.select_x == 0)		// タイトルの時押すと0,0になる
				//		g_StageSelect.select_y = 0;
				//	else if (g_StageSelect.select_y == 1 && g_StageSelect.select_x == 0)								// 0,1の時タイトルに行く
				//		g_StageSelect.select_y = 2;
				//	else if (g_StageSelect.select_y == 1)								// 最下層時上を押すと最上段行く
				//		g_StageSelect.select_y = 1;
				//	else
				//		g_StageSelect.select_y++;										// 通常
				//	g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
				//}
				//if (Keyboard_IsKeyDown(KK_RIGHT) && g_StageSelect.select_y != 2)
				//{
				//	if (g_StageSelect.select_x == 4)				// 端の時押すと矢印に行く
				//	{
				//		if (now_page == 0)
				//		{
				//			g_StageSelect.select_x = 6;
				//			g_StageSelect.select_y = 0;
				//		}
				//	}
				//	else if (g_StageSelect.select_x == 6)			// 矢印の時押すとページチェンジする
				//	{
				//		change_cool = 60;
				//		g_StageSelect.select_x = 0;
				//		g_StageSelect.select_y = 0;
				//		ChangePage(1);
				//		return;
				//	}
				//	else if (g_StageSelect.select_x == 5)				// 左矢印の時押すと0にいく
				//		g_StageSelect.select_x = 0;
				//	else
				//		g_StageSelect.select_x++;					// 通常
				//	g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
				//}
				//if (Keyboard_IsKeyDown(KK_LEFT) && g_StageSelect.select_y != 2)
				//{
				//	if (g_StageSelect.select_x == 0)				// 端の時押すと矢印に行く
				//	{
				//		if (now_page == 1)
				//		{
				//			g_StageSelect.select_x = 5;
				//			g_StageSelect.select_y = 0;
				//		}
				//	}
				//	else if (g_StageSelect.select_x == 5)			// 矢印の時押すとページチェンジする
				//	{
				//		change_cool = 60;
				//		g_StageSelect.select_x = 4;
				//		g_StageSelect.select_y = 0;
				//		ChangePage(-1);
				//		return;
				//	}
				//	else if (g_StageSelect.select_x == 6)				// 右矢印の時押すと4にいく
				//		g_StageSelect.select_x = 4;
				//	else
				//		g_StageSelect.select_x--;					// 通常
				//	g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
				//}







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
						// ステージの座標を求める
						int now_stage = x + y * SELECT_MAX_X + (now_page * 10);	// 0~19
						D3DXVECTOR2 Stage_Pos = GetStagePos(now_stage + 1);
						// 現在の座標を求める
						/*float effectnow_x = effectpos_x + while_x * x;
						float effectnow_y = effectpos_y + while_y * y;*/
						float effectnow_x = Stage_Pos.x;
						float effectnow_y = Stage_Pos.y;

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
					g_StageSelect.select_y = 2;
					mouseuse = true;
				}
				//左矢印
				D3DXVECTOR2 yazipos = D3DXVECTOR2(120.0f, 320.0f);
				D3DXVECTOR2 yazisize = D3DXVECTOR2(50.0f, 50.0f);
				if (now_page == 1)
				{
					if (mouse_pos_X > yazipos.x - yazisize.x && mouse_pos_X < yazipos.x + yazisize.x && mouse_pos_Y > yazipos.y - yazisize.y && mouse_pos_Y < yazipos.y + yazisize.y)
					{
						g_StageSelect.select_x = 5;
						if (g_StageSelect.select_y == 2)
							g_StageSelect.select_y = 0;
						mouseuse = true;
					}
				}
				//右矢印
				yazipos = D3DXVECTOR2(1320.0f, 320.0f);
				if (now_page == 0)
				{
					if (mouse_pos_X > yazipos.x - yazisize.x && mouse_pos_X < yazipos.x + yazisize.x && mouse_pos_Y > yazipos.y - yazisize.y && mouse_pos_Y < yazipos.y + yazisize.y)
					{
						g_StageSelect.select_x = 6;
						if (g_StageSelect.select_y == 2)
							g_StageSelect.select_y = 0;
						mouseuse = true;
					}
				}
			}

			// 変更を確認する処理

				// もし前のフレームから変化があった場合のみエフェクトなどを変化させる
			bool Change = false;
			if (OldStageSelectX != g_StageSelect.select_x ||
				OldStageSelectY != g_StageSelect.select_y)
				Change = true;

			// マウスがステージなどににあってない場合表示しない。
			if (!mouseuse)
			{
				if (now_stage_select_EffectArray != -1)
				{
					// もし消した場合は変更があったとする。
					Change = true;
					EffectBreak(now_stage_select_EffectArray);
					EffectBreak(now_stage_selectWaku_EffectArray);
					//EffectBreak(now_stagenum_select_EffectArray[0], now_stagenum_select_EffectArray[1]);
					DeleteMissionStageSelect();
				}
			}

			// 変更があった場合、初期化と新しいもののセット
			if (Change == true)
			{
				g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
				EffectBreak(now_stage_select_EffectArray);
				EffectBreak(now_stage_selectWaku_EffectArray);
				//EffectBreak(now_stagenum_select_EffectArray[0], now_stagenum_select_EffectArray[1]);
				DeleteMissionStageSelect();
				stage_select_once = false;
				stage_select_once_time = 0;
			}

			bool mouseclick = false;
			if (mouseuse && mouse_Lclick)
				mouseclick = true;

			if (title_display == true)
			{

				// マウスが表示にあっている状態で左クリックもしくはエンターキーをしたら
				if (GetFadeState() == FADE_NONE)
				{
					/*if (Keyboard_IsKeyDown(KK_ENTER) || mouseclick)*/
					if (mouseclick)
					{
						g_SENo = LoadSound("data/SE/「ピロリ」決定のボタン音・アクセント音.wav");
						PlaySound(g_SENo, 0);

						StageDecision = true;
						// 移動入力のとこですでにステージデータはもらっているのでこのままいってOK
						g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
						// プレイヤー配置フェーズに行く前に前回の配置情報をリセットする
						ResetPlacementArray();
						if (g_StageSelect.select_y == 2)
						{
							//change_cool = 999;				// 決定したので触れなくする
							//SceneTransition(SCENE_TITLE);
							// フェードさせる(黒い背景を出す)SetEffectInReverse
							SetEffectInReverse(4, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
								D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
								0.0f, 1.0f, 20, 20, 20, BackTitleTime,
								0.0f, 0.0f, 0);
							BackTitle = true;


						}
						else if (g_StageSelect.select_x == 5)
						{
							g_StageSelect.select_x = 4;
							ChangePage(-1);
							return;
						}
						else if (g_StageSelect.select_x == 6)
						{
							g_StageSelect.select_x = 0;
							ChangePage(1);
							return;
						}
						else
						{
							change_cool = 999;				// 決定したので触れなくする
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

				if (mouseuse)
				{

					if (stage_select_once == false)
					{
						stage_select_once = true;

						// ステージのとこだけステージデータを受け取る。
						if (g_StageSelect.select_x < SELECT_MAX_X && g_StageSelect.select_y < SELECT_MAX_Y)
						{
							// ステージデータを受け取る,ミッションやマップの表示で使うため。
							// xとyからマップの番号を計算する
							int stagenum = (now_page * 10) + (SELECT_MAX_X * g_StageSelect.select_y) + (g_StageSelect.select_x + 1);
							now_stagenum = stagenum;
							SetStageData(stagenum);		// 1~20の値を入れる

							// ステージデータを受け取った(更新された)のでミッションを表示させる
							DrawMissionStageSelect();
						}



						//ステージ選択
						for (int x = 0; x < SELECT_MAX_X + 2; x++)
						{
							for (int y = 0; y < SELECT_MAX_Y + 1; y++)
							{
								// ステージの座標を求める
								int now_stage = x + y * SELECT_MAX_X + (now_page * 10);	// 0~19
								D3DXVECTOR2 Stage_Pos = GetStagePos(now_stage + 1);

								// 現在の座標を求める
								/*float now_x = stage_origin_x + interval_x * x;
								float now_y = stage_origin_y + interval_y * y;*/
								float now_x = Stage_Pos.x;
								float now_y = Stage_Pos.y;

								// 検索。選択しているとこを見つけて大きいサイズで表示。
								if (g_StageSelect.select_x == x)
								{
									if (g_StageSelect.select_y == y)
									{
										if (x < SELECT_MAX_X && y < SELECT_MAX_Y)
										{
											int now_select_stage = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (now_page * 10);	// 0~19

											// 白枠
											now_stage_selectWaku_EffectArray =
												SetEffect(88, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
													D3DXVECTOR2(220.0f, 220.0f), D3DXVECTOR2(220.0f, 220.0f), 0,
													0.0f, 1.0f, 30, 999, 0, 30,
													0.0f, 0.0f, 0);

											// ピン
											now_stage_select_EffectArray =
												SetEffect(87, D3DXVECTOR2(now_x, now_y - 120), D3DXVECTOR2(now_x, now_y - 40), 1,
													D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
													0.0f, 1.0f, 30, 999, 0, 30,
													0.0f, 0.0f, 0);

											//// ステージの数字
											//SetEffectNumber(now_select_stage + 1, p_now_stagenum_select_EffectArray, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
											//	D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
											//	1.0f, 1.0f, 0, 999, 0, 60,
											//	0.0f, 0.0f, 0);

										}
										else if (y == 2)		// タイトルに戻る処理 (ワールド選択に戻るボタンの表示)
										{
											now_stage_select_EffectArray =
												SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
													D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
													0.0f, 1.0f, 0, 999, 0, 60,
													0.0f, 0.0f, 0);
											now_stage_selectWaku_EffectArray =
												SetEffect(61, D3DXVECTOR2(240.0f, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
													D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
													0.0f, 0.0f, 0, 999, 0, 60,
													0.0f, 0.0f, 0);			// 透明だけど出しておく
										}
										else if (x == 5)		// ページ変更の矢印の左
										{
											now_stage_select_EffectArray =
												SetEffect(103, D3DXVECTOR2(120.0f, 320.0f), D3DXVECTOR2(120.0f, 320.0f), 0,
													D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
													0.0f, 1.0f, 0, 999, 0, 60,
													0.0f, 0.0f, 0);
											now_stage_selectWaku_EffectArray =
												SetEffect(103, D3DXVECTOR2(120.0f, 320.0f), D3DXVECTOR2(120.0f, 320.0f), 0,
													D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
													0.0f, 0.0f, 0, 999, 0, 60,
													0.0f, 0.0f, 0);
										}
										else if (x == 6)		// ページ変更の矢印の右
										{
											now_stage_select_EffectArray =
												SetEffect(102, D3DXVECTOR2(1320.0f, 320.0f), D3DXVECTOR2(1320.0f, 320.0f), 0,
													D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
													0.0f, 1.0f, 0, 999, 0, 60,
													0.0f, 0.0f, 0);
											now_stage_selectWaku_EffectArray =
												SetEffect(102, D3DXVECTOR2(1320.0f, 320.0f), D3DXVECTOR2(1320.0f, 320.0f), 0,
													D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 0,
													0.0f, 0.0f, 0, 999, 0, 60,
													0.0f, 0.0f, 0);
										}

										g_SENo = LoadSound("data/SE/Accent03-1.wav");
										PlaySound(g_SENo, 0);
									}
								}
							}
						}
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



			SetScore2(now_page);
		}
		else
		{
			// チェンジ中の場合

			SAVEDATA* p_Savedata = GetSavedata();
			STAGEDATA* p_Stagedata = GetStagedata();

			// 真っ暗の時に画像を変える
			if (change_count == 24 || changeOneTime)
			{
				changeOneTime = false;
				//ステージ選択aa
				for (int page = 0; page < PAGE_MAX; page++)
				{

					// ページの背景
					ChangeEffect(tex_Page_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
						D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
						0.0f, 1.0f, 0, 999, 0, cahngetime,
						0.0f, 0.0f, 0);

					// ステージ番号
					ChangeEffect(tex_StageNum_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
						D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
						0.0f, 1.0f, 0, 999, 0, cahngetime,
						0.0f, 0.0f, 0);

					// tex_Page_background_EffectArray[page]
					// tex_StageNum_background_EffectArray


					for (int x = 0; x < SELECT_MAX_X; x++)
					{
						for (int y = 0; y < SELECT_MAX_Y; y++)
						{
							//int now_num = x + y * SELECT_MAX_X + (page * 10);
							int NowWorld_stagenum = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (page * 10);	// 0~19

							D3DXVECTOR2 now_stagePos = GetEffectPos(stage_EffectArray[NowWorld_stagenum]);
							D3DXVECTOR2 now_stage_starPos[3];
							now_stage_starPos[0] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][0]);
							now_stage_starPos[1] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][1]);
							now_stage_starPos[2] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][2]);

							// 選択されてないときの表示を出す(ステージすべて)
							//////////ChangeEffect(stage_EffectArray[NowWorld_stagenum], tex_NowWorld_stagechoice, now_stagePos, D3DXVECTOR2(now_stagePos.x + change_page_interval, now_stagePos.y), 1,
							//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
							//////////	0.0f, 0.0f, 0);

							//////////// 数字
							//////////// 現在の座標を求める
							//////////
							//////////ChangeEffect(stageNumber_EffectArray[NowWorld_stagenum][0], -1, D3DXVECTOR2(99999,99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
							//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
							//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
							//////////	0.0f, 0.0f, 0, stageNumber_EffectArray[NowWorld_stagenum][1]);

							// ミッションをクリアしているなら表示する p_stageNumber_EffectArray[NowWorld_stagenum]
							//if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
							//{
							//	//星
							//	ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][0], 83, now_stage_starPos[0], D3DXVECTOR2(now_stage_starPos[0].x + change_page_interval, now_stage_starPos[0].y), 1,
							//		D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
							//		0.0f, 1.0f, 120, 999, 0, cahngetime,
							//		0.0f, 0.0f, 0);
							//}

							//// ミッションをクリアしているなら表示する
							//if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
							//{
							//	//星
							//	ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][1], 84, now_stage_starPos[1], D3DXVECTOR2(now_stage_starPos[1].x + change_page_interval, now_stage_starPos[1].y), 1,
							//		D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
							//		0.0f, 1.0f, 120, 999, 0, cahngetime,
							//		0.0f, 0.0f, 0);
							//}

							//// ミッションをクリアしているなら表示する
							//if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
							//{
							//	//星
							//	ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][2], 85, now_stage_starPos[2], D3DXVECTOR2(now_stage_starPos[2].x + change_page_interval, now_stage_starPos[2].y), 1,
							//		D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
							//		0.0f, 1.0f, 120, 999, 0, cahngetime,
							//		0.0f, 0.0f, 0);
							//}
						}
					}
				}
				// 矢印の処理
				ChangeEffectClarity(Arrow_EffectArray[0], 1.0f);
				ChangeEffectClarity(Arrow_EffectArray[1], 1.0f);

				if (now_page == 0)
					ChangeEffectClarity(Arrow_EffectArray[0], 0.3f);

				if (now_page == 1)
					ChangeEffectClarity(Arrow_EffectArray[1], 0.3f);

			}

			change_count++;
		}
	}
	else
	{
		// タイトルへ戻る中なら

		// 画面が全部真っ暗なった時にいろいろ戻す
		if (BackTitlecount == 36)
		{
			InitPage();
			//StopSoundAll();
			UninitStageSelect();
		}

		// 戻る時間が終わったら戻す
		if (BackTitlecount > BackTitleTime - 30)
		{
			title_display = false;
			InitStageSelectForTitle();
			BackTitle = false;
			BackTitlecount = -1;
			InitStageSelect();
		}

		BackTitlecount++;
	}
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

	// テスト用
	float toumeido = 1.0f;
	float plusA = 0.0f;

	//背景表示
	// 1ページ目
	tex_Page_background_EffectArray[0] =
		SetEffect(89, D3DXVECTOR2(SCREEN_WIDTH / 2 + plusA, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
			0.0f, toumeido, 100, 999, 0, 60,
			0.0f, 0.0f, 0);
	// 2ページ目
	tex_Page_background_EffectArray[1] =
		SetEffect(90, D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH + plusA, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
			0.0f, toumeido, 100, 999, 0, 60,
			0.0f, 0.0f, 0);

	// 1ページ目
	tex_StageNum_background_EffectArray[0] =
		SetEffect(91, D3DXVECTOR2(SCREEN_WIDTH / 2 + plusA, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
			0.0f, toumeido, 100, 999, 0, 60,
			0.0f, 0.0f, 0);

	// 2ページ目
	tex_StageNum_background_EffectArray[1] =
		SetEffect(92, D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH + plusA, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH, SCREEN_HEIGHT / 2), 0,
			D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
			0.0f, toumeido, 100, 999, 0, 60,
			0.0f, 0.0f, 0);

	// ステージ選択の時の原点となる場所
	float	stage_origin_x = 240.0f;			    // xの原点(0,0を選択しているとき)
	float	stage_origin_y = 200.0f;			    // yの原点(0,0を選択しているとき)

	// ステージ選択の時1個離れたらこれだけ離れるよってやつ
	float interval_x = 240.0f;
	float interval_y = 240.0f;


	float page_interval_x = SCREEN_WIDTH;



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
				//////////stage_EffectArray[NowWorld_stagenum] =
				//////////	SetEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
				//////////		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				//////////		0.0f, 1.0f, 0, 999, 0, 0,
				//////////		0.0f, 0.0f, 0); 

				//////////int* p_stageNumber_EffectArray;				// 20ステージ分の配列をポインターで用意する
				//////////p_stageNumber_EffectArray = &stageNumber_EffectArray[NowWorld_stagenum][0];


				//////////SetEffectNumber(NowWorld_stagenum + 1, p_stageNumber_EffectArray, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
				//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				//////////	0.0f, 1.0f, 0, 999, 0, 0,
				//////////	0.0f, 0.0f, 0);

				/*stageNumber_EffectArray[NowWorld_stagenum][0] = 1;
				stageNumber_EffectArray[NowWorld_stagenum][1] = 1;*/

				// ミッションをクリアしているなら表示する
				//if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
				//{
				//	//星
				//	stage_star_EffectArray[NowWorld_stagenum][0] =
				//		SetEffect(83, D3DXVECTOR2(now_x - 40 + plusA, now_y), D3DXVECTOR2(now_x - 40, now_y), 0,
				//			D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
				//			0.0f, toumeido, 120, 999, 0, 60,
				//			0.0f, 0.0f, 0);
				//}

				//// ミッションをクリアしているなら表示する
				//if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
				//{
				//	//星
				//	stage_star_EffectArray[NowWorld_stagenum][1] =
				//		SetEffect(84, D3DXVECTOR2(now_x - 0 + plusA, now_y), D3DXVECTOR2(now_x - 0, now_y), 0,
				//			D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
				//			0.0f, toumeido, 120, 999, 0, 60,
				//			0.0f, 0.0f, 0);
				//}

				//// ミッションをクリアしているなら表示する
				//if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
				//{
				//	//星
				//	stage_star_EffectArray[NowWorld_stagenum][2] =
				//		SetEffect(85, D3DXVECTOR2(now_x + 50 + plusA, now_y), D3DXVECTOR2(now_x + 50, now_y), 0,
				//			D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
				//			0.0f, toumeido, 120, 999, 0, 60,
				//			0.0f, 0.0f, 0);
				//}
			}
		}
	}

	// タイトルに戻る処理
	BackTitle_EffectArray =
		SetEffect(61, D3DXVECTOR2(240.0f + plusA, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, toumeido, 0, 999, 0, 0,
			0.0f, 0.0f, 0);

	// ページ変更の矢印の左
	Arrow_EffectArray[0] =
		SetEffect(103, D3DXVECTOR2(120.0f + plusA, 320.0f), D3DXVECTOR2(120.0f, 320.0f), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, toumeido, 0, 999, 0, 60,
			0.0f, 0.0f, 0);

	// ページ変更の矢印の右
	Arrow_EffectArray[1] =
		SetEffect(102, D3DXVECTOR2(1320.0f + plusA, 320.0f), D3DXVECTOR2(1320.0f, 320.0f), 0,
			D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
			0.0f, toumeido, 0, 999, 0, 60,
			0.0f, 0.0f, 0);

	////どのこの星？
	//SetEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
	//	D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
	//	0.0f, toumeido, 0, 1, 0, 0,
	//	0.0f, 0.0f, 0);

	// セーブデータからゲットしてる星の数を読み込む
	// 多分左上のやつら？
	int StageStar = GetStar(NowWorld);

	int Number_EffectArray[2] = { 0,0 };
	int* p_Number_EffectArray = Number_EffectArray;
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

	// 矢印の透明度を下げる処理
	if (now_page == 0)
		ChangeEffectClarity(Arrow_EffectArray[0], 0.0f);

	if (now_page == 1)
		ChangeEffectClarity(Arrow_EffectArray[1], 0.0f);

	//// ピンのエフェクトを作っておく
	//tex_Pin_EffectArray =
	//	SetEffect(87, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
	//		D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 0,
	//		0.0f, 1.0f, 0, 1, 0, 0,
	//		0.0f, 0.0f, 0);

	//// 白枠のエフェクトを作っておく
	//tex_Waku_EffectArray =
	//	SetEffect(88, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
	//		D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 0,
	//		0.0f, 1.0f, 0, 1, 0, 0,
	//		0.0f, 0.0f, 0);

	return;
}

void ChangePage(int ToGoPage)
{
	// ページチェンジ中にする
	changing = true;

	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	// フェードさせる(黒い背景を出す)SetEffectInReverse
	SetEffectInReverse(4, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, 1.0f, 22, 4, 22, 48,
		0.0f, 0.0f, 0);


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

	float page_interval = SCREEN_WIDTH;
	change_page_interval = -ToGoPage * SCREEN_WIDTH;		// 移動距離

	////ステージ選択
	//for (int page = 0; page < PAGE_MAX; page++)
	//{
	//	// ページの背景
	//	ChangeEffect(tex_Page_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
	//		D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
	//		0.0f, 1.0f, 0, 999, 0, cahngetime,
	//		0.0f, 0.0f, 0);

	//	// ステージ番号
	//	ChangeEffect(tex_StageNum_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
	//		D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
	//		0.0f, 1.0f, 0, 999, 0, cahngetime,
	//		0.0f, 0.0f, 0);

	//	// tex_Page_background_EffectArray[page]
	//	// tex_StageNum_background_EffectArray


	//	for (int x = 0; x < SELECT_MAX_X; x++)
	//	{
	//		for (int y = 0; y < SELECT_MAX_Y; y++)
	//		{
	//			//int now_num = x + y * SELECT_MAX_X + (page * 10);
	//			int NowWorld_stagenum = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (page * 10);	// 0~19

	//			// 現在の座標を求める
	//			float now_x = stage_origin_x + interval_x * x + page * page_interval;
	//			float now_y = stage_origin_y + interval_y * y;

	//			D3DXVECTOR2 now_stagePos = GetEffectPos(stage_EffectArray[NowWorld_stagenum]);
	//			D3DXVECTOR2 now_stage_starPos[3];
	//			now_stage_starPos[0] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][0]);
	//			now_stage_starPos[1] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][1]);
	//			now_stage_starPos[2] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][2]);

	//			// 選択されてないときの表示を出す(ステージすべて)
	//			//////////ChangeEffect(stage_EffectArray[NowWorld_stagenum], tex_NowWorld_stagechoice, now_stagePos, D3DXVECTOR2(now_stagePos.x + change_page_interval, now_stagePos.y), 1,
	//			//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
	//			//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
	//			//////////	0.0f, 0.0f, 0);

	//			//////////// 数字
	//			//////////// 現在の座標を求める
	//			//////////
	//			//////////ChangeEffect(stageNumber_EffectArray[NowWorld_stagenum][0], -1, D3DXVECTOR2(99999,99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
	//			//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
	//			//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
	//			//////////	0.0f, 0.0f, 0, stageNumber_EffectArray[NowWorld_stagenum][1]);

	//			// ミッションをクリアしているなら表示する p_stageNumber_EffectArray[NowWorld_stagenum]
	//			if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
	//			{
	//				//星
	//				ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][0], 83, now_stage_starPos[0], D3DXVECTOR2(now_stage_starPos[0].x + change_page_interval, now_stage_starPos[0].y), 1,
	//					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
	//					0.0f, 1.0f, 120, 999, 0, cahngetime,
	//					0.0f, 0.0f, 0);
	//			}

	//			// ミッションをクリアしているなら表示する
	//			if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
	//			{
	//				//星
	//				ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][1], 84, now_stage_starPos[1], D3DXVECTOR2(now_stage_starPos[1].x + change_page_interval, now_stage_starPos[1].y), 1,
	//					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
	//					0.0f, 1.0f, 120, 999, 0, cahngetime,
	//					0.0f, 0.0f, 0);
	//			}

	//			// ミッションをクリアしているなら表示する
	//			if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
	//			{
	//				//星
	//				ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][2], 85, now_stage_starPos[2], D3DXVECTOR2(now_stage_starPos[2].x + change_page_interval, now_stage_starPos[2].y), 1,
	//					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
	//					0.0f, 1.0f, 120, 999, 0, cahngetime,
	//					0.0f, 0.0f, 0);
	//			}
	//		}
	//	}
	//}

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

	// 変更があった場合ので、初期化と新しいもののセット
	g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
	EffectBreak(now_stage_select_EffectArray);
	EffectBreak(now_stage_selectWaku_EffectArray);
	//EffectBreak(now_stagenum_select_EffectArray[0], now_stagenum_select_EffectArray[1]);
	DeleteMissionStageSelect();
	stage_select_once = false;
	stage_select_once_time = 0;

	change_cool = 48;
	now_page += ToGoPage;

	/*ChangeEffectClarity(Arrow_EffectArray[0], 1.0f);
	ChangeEffectClarity(Arrow_EffectArray[1], 1.0f);

	if(now_page == 0)
		ChangeEffectClarity(Arrow_EffectArray[0], 0.3f);

	if (now_page == 1)
		ChangeEffectClarity(Arrow_EffectArray[1], 0.3f);*/

	return;

}
// 1frameでチェンジする
void ChangePageOneTime(int ToGoPage)
{
	// ページチェンジ中にする
	changing = true;

	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	//// フェードさせる(黒い背景を出す)SetEffectInReverse
	//SetEffectInReverse(4, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
	//	D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
	//	0.0f, 1.0f, 0, 1, 0, 1,
	//	0.0f, 0.0f, 0);


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

	float page_interval = SCREEN_WIDTH;
	change_page_interval = -ToGoPage * SCREEN_WIDTH;		// 移動距離

	////ステージ選択
	//for (int page = 0; page < PAGE_MAX; page++)
	//{
	//	// ページの背景
	//	ChangeEffect(tex_Page_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
	//		D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
	//		0.0f, 1.0f, 0, 999, 0, cahngetime,
	//		0.0f, 0.0f, 0);

	//	// ステージ番号
	//	ChangeEffect(tex_StageNum_background_EffectArray[page], -1, D3DXVECTOR2(99999, 99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
	//		D3DXVECTOR2(99999, 99999), D3DXVECTOR2(0.0f, 0.0f), 0,
	//		0.0f, 1.0f, 0, 999, 0, cahngetime,
	//		0.0f, 0.0f, 0);

	//	// tex_Page_background_EffectArray[page]
	//	// tex_StageNum_background_EffectArray


	//	for (int x = 0; x < SELECT_MAX_X; x++)
	//	{
	//		for (int y = 0; y < SELECT_MAX_Y; y++)
	//		{
	//			//int now_num = x + y * SELECT_MAX_X + (page * 10);
	//			int NowWorld_stagenum = NowWorld * 10 - 10 + x + y * SELECT_MAX_X + (page * 10);	// 0~19

	//			// 現在の座標を求める
	//			float now_x = stage_origin_x + interval_x * x + page * page_interval;
	//			float now_y = stage_origin_y + interval_y * y;

	//			D3DXVECTOR2 now_stagePos = GetEffectPos(stage_EffectArray[NowWorld_stagenum]);
	//			D3DXVECTOR2 now_stage_starPos[3];
	//			now_stage_starPos[0] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][0]);
	//			now_stage_starPos[1] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][1]);
	//			now_stage_starPos[2] = GetEffectPos(stage_star_EffectArray[NowWorld_stagenum][2]);

	//			// 選択されてないときの表示を出す(ステージすべて)
	//			//////////ChangeEffect(stage_EffectArray[NowWorld_stagenum], tex_NowWorld_stagechoice, now_stagePos, D3DXVECTOR2(now_stagePos.x + change_page_interval, now_stagePos.y), 1,
	//			//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
	//			//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
	//			//////////	0.0f, 0.0f, 0);

	//			//////////// 数字
	//			//////////// 現在の座標を求める
	//			//////////
	//			//////////ChangeEffect(stageNumber_EffectArray[NowWorld_stagenum][0], -1, D3DXVECTOR2(99999,99999), D3DXVECTOR2(change_page_interval, 0.0f), 1,
	//			//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
	//			//////////	0.0f, 1.0f, 0, 999, 0, cahngetime,
	//			//////////	0.0f, 0.0f, 0, stageNumber_EffectArray[NowWorld_stagenum][1]);

	//			// ミッションをクリアしているなら表示する p_stageNumber_EffectArray[NowWorld_stagenum]
	//			if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
	//			{
	//				//星
	//				ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][0], 83, now_stage_starPos[0], D3DXVECTOR2(now_stage_starPos[0].x + change_page_interval, now_stage_starPos[0].y), 1,
	//					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
	//					0.0f, 1.0f, 120, 999, 0, cahngetime,
	//					0.0f, 0.0f, 0);
	//			}

	//			// ミッションをクリアしているなら表示する
	//			if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
	//			{
	//				//星
	//				ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][1], 84, now_stage_starPos[1], D3DXVECTOR2(now_stage_starPos[1].x + change_page_interval, now_stage_starPos[1].y), 1,
	//					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
	//					0.0f, 1.0f, 120, 999, 0, cahngetime,
	//					0.0f, 0.0f, 0);
	//			}

	//			// ミッションをクリアしているなら表示する
	//			if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
	//			{
	//				//星
	//				ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][2], 85, now_stage_starPos[2], D3DXVECTOR2(now_stage_starPos[2].x + change_page_interval, now_stage_starPos[2].y), 1,
	//					D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
	//					0.0f, 1.0f, 120, 999, 0, cahngetime,
	//					0.0f, 0.0f, 0);
	//			}
	//		}
	//	}
	//}

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

	// 変更があった場合ので、初期化と新しいもののセット
	g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
	EffectBreak(now_stage_select_EffectArray);
	EffectBreak(now_stage_selectWaku_EffectArray);
	//EffectBreak(now_stagenum_select_EffectArray[0], now_stagenum_select_EffectArray[1]);
	DeleteMissionStageSelect();
	stage_select_once = false;
	stage_select_once_time = 0;

	change_cool = 1;
	now_page += ToGoPage;

	changeOneTime = true;

	/*ChangeEffectClarity(Arrow_EffectArray[0], 1.0f);
	ChangeEffectClarity(Arrow_EffectArray[1], 1.0f);

	if(now_page == 0)
		ChangeEffectClarity(Arrow_EffectArray[0], 0.3f);

	if (now_page == 1)
		ChangeEffectClarity(Arrow_EffectArray[1], 0.3f);*/

	return;

}



void InitPage()
{
	changing = true;
	change_cool = 10;
	now_page = 0;
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	// テスト用
	float toumeido = 1.0f;
	float plusA = 0.0f;

	//背景表示
	// 1ページ目
	ChangeEffect(tex_Page_background_EffectArray[0], 89, D3DXVECTOR2(SCREEN_WIDTH / 2 + plusA, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, toumeido, 100, 999, 0, 60,
		0.0f, 0.0f, 0);
	// 2ページ目
	ChangeEffect(tex_Page_background_EffectArray[1], 90, D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH + plusA, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, toumeido, 100, 999, 0, 60,
		0.0f, 0.0f, 0);

	// 1ページ目
	ChangeEffect(tex_StageNum_background_EffectArray[0], 91, D3DXVECTOR2(SCREEN_WIDTH / 2 + plusA, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, toumeido, 100, 999, 0, 60,
		0.0f, 0.0f, 0);

	// 2ページ目
	ChangeEffect(tex_StageNum_background_EffectArray[1], 92, D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH + plusA, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2 + SCREEN_WIDTH, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, toumeido, 100, 999, 0, 60,
		0.0f, 0.0f, 0);

	// ステージ選択の時の原点となる場所
	float	stage_origin_x = 240.0f;			    // xの原点(0,0を選択しているとき)
	float	stage_origin_y = 200.0f;			    // yの原点(0,0を選択しているとき)

	// ステージ選択の時1個離れたらこれだけ離れるよってやつ
	float interval_x = 240.0f;
	float interval_y = 240.0f;


	float page_interval_x = SCREEN_WIDTH;



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
				//////////stage_EffectArray[NowWorld_stagenum] =
				//////////	ChangeEffect(tex_NowWorld_stagechoice, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
				//////////		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				//////////		0.0f, 1.0f, 0, 999, 0, 0,
				//////////		0.0f, 0.0f, 0); 

				//////////int* p_stageNumber_EffectArray;				// 20ステージ分の配列をポインターで用意する
				//////////p_stageNumber_EffectArray = &stageNumber_EffectArray[NowWorld_stagenum][0];


				//////////SetEffectNumber(NowWorld_stagenum + 1, p_stageNumber_EffectArray, D3DXVECTOR2(now_x, now_y), D3DXVECTOR2(now_x, now_y), 0,
				//////////	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
				//////////	0.0f, 1.0f, 0, 999, 0, 0,
				//////////	0.0f, 0.0f, 0);

				/*stageNumber_EffectArray[NowWorld_stagenum][0] = 1;
				stageNumber_EffectArray[NowWorld_stagenum][1] = 1;*/

				//// ミッションをクリアしているなら表示する
				//if (p_Savedata[NowWorld_stagenum].mission_clear[0] == 1)
				//{
				//	//星

				//	ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][0], 83, D3DXVECTOR2(now_x - 40 + plusA, now_y), D3DXVECTOR2(now_x - 40, now_y), 0,
				//		D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
				//		0.0f, toumeido, 120, 999, 0, 60,
				//		0.0f, 0.0f, 0);
				//}

				//// ミッションをクリアしているなら表示する
				//if (p_Savedata[NowWorld_stagenum].mission_clear[1] == 1)
				//{
				//	//星

				//	ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][1], 84, D3DXVECTOR2(now_x - 0 + plusA, now_y), D3DXVECTOR2(now_x - 0, now_y), 0,
				//		D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
				//		0.0f, toumeido, 120, 999, 0, 60,
				//		0.0f, 0.0f, 0);
				//}

				//// ミッションをクリアしているなら表示する
				//if (p_Savedata[NowWorld_stagenum].mission_clear[2] == 1)
				//{
				//	//星

				//	ChangeEffect(stage_star_EffectArray[NowWorld_stagenum][2], 85, D3DXVECTOR2(now_x + 50 + plusA, now_y), D3DXVECTOR2(now_x + 50, now_y), 0,
				//		D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(50.0f, 50.0f), 1,
				//		0.0f, toumeido, 120, 999, 0, 60,
				//		0.0f, 0.0f, 0);
				//}
			}
		}
	}

	// タイトルに戻る処理
	ChangeEffect(BackTitle_EffectArray, 61, D3DXVECTOR2(240.0f + plusA, 700.0f), D3DXVECTOR2(240.0f, 700.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, toumeido, 0, 999, 0, 0,
		0.0f, 0.0f, 0);

	// ページ変更の矢印の左

	ChangeEffect(Arrow_EffectArray[0], 61, D3DXVECTOR2(120.0f + plusA, 320.0f), D3DXVECTOR2(120.0f, 320.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, toumeido, 0, 999, 0, 60,
		0.0f, 0.0f, 0);

	// ページ変更の矢印の右

	ChangeEffect(Arrow_EffectArray[1], 61, D3DXVECTOR2(1320.0f + plusA, 320.0f), D3DXVECTOR2(1320.0f, 320.0f), 0,
		D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 0,
		0.0f, toumeido, 0, 999, 0, 60,
		0.0f, 0.0f, 0);

	////どのこの星？
	//ChangeEffect(9, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
	//	D3DXVECTOR2(500.0f, 150.0f), D3DXVECTOR2(500.0f, 150.0f), 0,
	//	0.0f, toumeido, 0, 1, 0, 0,
	//	0.0f, 0.0f, 0);

	// セーブデータからゲットしてる星の数を読み込む
	// 多分左上のやつら？
	int StageStar = GetStar(NowWorld);

	int Number_EffectArray[2] = { 0,0 };
	int* p_Number_EffectArray = Number_EffectArray;
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

	// 矢印の透明度を下げる処理
	if (now_page == 0)
		ChangeEffectClarity(Arrow_EffectArray[0], 0.3f);

	if (now_page == 1)
		ChangeEffectClarity(Arrow_EffectArray[1], 0.3f);

	//// ピンのエフェクトを作っておく
	//tex_Pin_EffectArray =
	//	ChangeEffect(87, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
	//		D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 0,
	//		0.0f, 1.0f, 0, 1, 0, 0,
	//		0.0f, 0.0f, 0);

	//// 白枠のエフェクトを作っておく
	//tex_Waku_EffectArray =
	//	ChangeEffect(88, D3DXVECTOR2(280.0f, 50.0f), D3DXVECTOR2(280.0f, 50.0f), 0,
	//		D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(500.0f, 500.0f), 0,
	//		0.0f, 1.0f, 0, 1, 0, 0,
	//		0.0f, 0.0f, 0);



// 変更があった場合ので、初期化と新しいもののセット
	g_StageSelect.selectcooltime = STAGE_SELECT_COOL;
	EffectBreak(now_stage_select_EffectArray);
	EffectBreak(now_stage_selectWaku_EffectArray);
	//EffectBreak(now_stagenum_select_EffectArray[0], now_stagenum_select_EffectArray[1]);
	DeleteMissionStageSelect();
	stage_select_once = false;
	stage_select_once_time = 0;

	change_cool = 0;
	now_page = 0;
	change_page_interval = 0.0f;

	return;

}



// 1~20での現在のステージ番号
int GetNowChoiceStageNum()
{
	return now_stagenum;
}

// 1~20での現在のステージ番号
void ChangeNowChoiceStageNum(int num)
{
	now_stagenum = num;
	return;
}

// 1~20での現在のステージ番号
void NextNowChoiceStageNum()
{
	now_stagenum = now_stagenum + 1;
	//InitGame();
	return;
}


D3DXVECTOR2 GetStagePos(int num)
{
	switch (num)
	{
	case 1:
		return D3DXVECTOR2(188.0f, 183.0f);
		break;
	case 2:
		return D3DXVECTOR2(462.0f, 310.0f);
		break;
	case 3:
		return D3DXVECTOR2(672.0f, 210.0f);
		break;
	case 4:
		return D3DXVECTOR2(972.0f, 120.0f);
		break;
	case 5:
		return D3DXVECTOR2(1228.0f, 300.0f);
		break;
	case 6:
		return D3DXVECTOR2(128.0f, 560.0f);
		break;
	case 7:
		return D3DXVECTOR2(536.0f, 668.0f);
		break;
	case 8:
		return D3DXVECTOR2(836.0f, 495.0f);
		break;
	case 9:
		return D3DXVECTOR2(1020.0f, 540.0f);
		break;
	case 10:
		return D3DXVECTOR2(1297.0f, 628.0f);
		break;

	case 11:
		return D3DXVECTOR2(152.0f, 470.0f);
		break;
	case 12:
		return D3DXVECTOR2(243.0f, 225.0f);
		break;
	case 13:
		return D3DXVECTOR2(592.0f, 200.0f);
		break;
	case 14:
		return D3DXVECTOR2(970.0f, 105.0f);
		break;
	case 15:
		return D3DXVECTOR2(1248.0f, 133.0f);
		break;
	case 16:
		return D3DXVECTOR2(1313.0f, 325.0f);
		break;
	case 17:
		return D3DXVECTOR2(1235.0f, 540.0f);
		break;
	case 18:
		return D3DXVECTOR2(903.0f, 405.0f);
		break;
	case 19:
		return D3DXVECTOR2(778.0f, 630.0f);
		break;
	case 20:
		return D3DXVECTOR2(478.0f, 660.0f);
		break;
	}
}

// タイトルのぼかしのための初期化
void InitStageSelectForTitle()
{
	title_display = false;			// タイトルのぼかしをもっかいやる
	title_display_once = false;			// タイトルのぼかしをもっかいやる
	title_click = false;
	title_clickcount = 0;
	title_count = 0;

	return;
}