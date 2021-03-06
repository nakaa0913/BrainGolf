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
#include "result.h"
#include "scene.h"
#include "sound.h"
#include "fade.h"
#include "effect.h"
#include "mission.h"
#include "savedata.h"
#include "stagedata.h"
#include "keyboard.h"
#include "gameover.h"
#include "mouse.h"
#include "gamedata.h"
#include "game.h"

#define GOAL_H (50)
#define GOAL_W (50)
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static GAMEOVER g_Gameover;
static int g_GameoverSENo = 0;

int			onceSE;
bool result_click2 = false; //リザルト画面に行くかどうかの

//エフェクト関連
int map_back2 = -1;			// マップ戻る
int gameover = -1;				// ゲームクリア
int next2 = -1;				//	次へ
int result2 = -1;			//	リザルト
int placement2 = -1;			//	配置から
bool result_over_once = false;
int result_over_once_time = 0;

int fefffff = 0;
static int g_SENo = 0;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGameover(void)
{
	//テクスチャ読み込み

	result_over_once = false;
	g_Gameover.gameovertime = 0;
	g_Gameover.selectpush = 0;
	g_Gameover.resulttime2 = 0;

	//初期化
	g_GameoverSENo = LoadSound("data/SE/Phrase04-1.wav");
	onceSE = 0;
	result_click2 = false;
	map_back2 = -1;
	gameover = -1;
	next2 = -1;				//	次へ
	result2 = -1;			//	リザルト
	placement2 = -1;			//	配置から
	result_over_once_time = 0;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameover(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameover(void)
{
	if (onceSE == 0)
	{
		PlaySound(g_GameoverSENo, 0);
		onceSE = 1;
	}
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();
	GAMEDATA* p_Gamedata = GetGamedata();
	//マウスの座標を取得
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouseuse = false;

	// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
	int OldResultSelect = g_Gameover.selectpush;

	// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
	//int OldnowchoiceX = nowchoice.x;
	//int OldnowchoiceY = nowchoice.y;

	if (result_click2 == false)
	{
		if (g_Gameover.gameovertime == 1)
		{
			//暗闇4 明かりなら48
			SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
				D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
				0.0f, 0.5f, 100, 999, 0, 180,
				0.0f, 0.0f, 0);
			//横1440
			//縦810

			gameover =
			//ゲームオーバー
			SetEffect(55, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1300, 700), 1,
				0.0f, 1.0f, 30, 999, 0, 90,
				0.0f, 0.0f, 0);

		}
	

		if (g_Gameover.gameovertime == 90)
		{
			////明るくする暗くするなら4
			//SetEffect(4, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			//	D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			//	0.0f, 0.5f, 0, 1, 0, 1,
			//	0.0f, 0.0f, 0);

			////ステージ名
			//SetEffect(57, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
			//	D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 1,
			//	0.0f, 1.0f, 0, 999, 0, 1,
			//	0.0f, 0.0f, 0);

	

			next2 =
			//リスタート
			SetEffect(79, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 1,
				D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
				0.0f, 1.0f, 0, 999, 0, 1,
				0.0f, 0.0f, 0);

			placement2 =
			//プレイヤー配置に戻る
			SetEffect(99, D3DXVECTOR2(1100.0f, 700.0f), D3DXVECTOR2(1100.0f, 700.0f), 1,
				D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
				0.0f, 1.0f, 0, 999, 0, 1,
				0.0f, 0.0f, 0);

			map_back2 =
			//マップ？に戻る
			SetEffect(75, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
				D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
				0.0f, 1.0f, 0, 999, 0, 1,
				0.0f, 0.0f, 0);

			result2 =
			//リザルトに行く
			SetEffect(97, D3DXVECTOR2(700.0f, 550.0f), D3DXVECTOR2(700.0f, 550.0f), 1,
				D3DXVECTOR2(700.0f, 80.0f), D3DXVECTOR2(700.0f, 80.0f), 1,
				0.0f, 1.0f, 0, 999, 0, 1,
				0.0f, 0.0f, 0);
		}
			//横1440
			//縦810

			if (g_Gameover.gameovertime >= 90)
			{
				if (g_Gameover.selectpush == 0)
				{
					////next?次のステージへ的な
					//SetEffect(80, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 1,
					//	D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
					//	0.0f, 1.0f, 0, 1, 0, 1,
					//	0.0f, 0.0f, 0);


				}

				if (g_Gameover.selectpush == 1)
				{
					////ワールド選択に戻る
					//SetEffect(76, D3DXVECTOR2(90.0f, 700.0f), D3DXVECTOR2(90.0f, 700.0f), 1,
					//	D3DXVECTOR2(227.0f, 202.0f), D3DXVECTOR2(227.0f, 202.0f), 1,
					//	0.0f, 1.0f, 0, 1, 0, 1,
					//	0.0f, 0.0f, 0);
				}

				if (g_Gameover.selectpush == 2)
				{
					////プレイヤー配置に戻る
					//SetEffect(100, D3DXVECTOR2(1100.0f, 700.0f), D3DXVECTOR2(1100.0f, 700.0f), 1,
					//	D3DXVECTOR2(200.0f, 109.0f), D3DXVECTOR2(200.0f, 109.0f), 1,
					//	0.0f, 1.0f, 0, 1, 0, 1,
					//	0.0f, 0.0f, 0);
				}

				if (g_Gameover.selectpush == 3)
				{
					////リザルトに行く
					//SetEffect(98, D3DXVECTOR2(700.0f, 545.0f), D3DXVECTOR2(700.0f, 545.0f), 1,
					//	D3DXVECTOR2(725.0f, 85.0f), D3DXVECTOR2(725.0f, 85.0f), 1,
					//	0.0f, 1.0f, 0, 1, 0, 1,
					//	0.0f, 0.0f, 0);
				}

				/*if (g_Gameover.selectpush == 2)
				{
					SetEffect(3, D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 700.0f), 1,
						D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(350.0f, 120.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}*/


				//if (g_Gameover.selecttime <= 0)
				//{

				//	if (Keyboard_IsKeyDown(KK_RIGHT))
				//	{
				//		g_Gameover.selectpush++;
				//		g_Gameover.selecttime = 30;

				//	}
				//	if (g_Gameover.selectpush >= 3)
				//	{
				//		g_Gameover.selectpush = 0;
				//	}

				//	if (Keyboard_IsKeyDown(KK_LEFT))
				//	{
				//		g_Gameover.selectpush--;
				//		g_Gameover.selecttime = 30;

				//	}
				//	if (g_Gameover.selectpush < 0)
				//	{
				//		g_Gameover.selectpush = 2;
				//	}

				//	/*if (g_Gameover.gameovertime >= 9060)
				//	{
				//		if (Keyboard_IsKeyDown(KK_ENTER))
				//		{
				//			SceneTransition(SCENE_WORLD_SELECT);

				//		}
				//	}*/

				//	if (g_Gameover.selectpush == 0)
				//	{
				//		if (Keyboard_IsKeyDown(KK_ENTER))
				//		{
				//			SceneTransition(SCENE_GAME);

				//		}
				//	}

				//	if (g_Gameover.selectpush == 1)
				//	{
				//		if (Keyboard_IsKeyDown(KK_ENTER))
				//		{
				//			SceneTransition(SCENE_STAGE_SELECT);

				//		}
				//	}

				//	if (g_Gameover.selectpush == 2)
				//	{
				//		if (Keyboard_IsKeyDown(KK_ENTER))
				//		{
				//			SceneTransition(SCENE_PLACEMENT);

				//		}
				//	}

				//}

				//マウス操作
				//next				1200, 700
				if (mouse_pos_X > 1215.0f && mouse_pos_X < 1370.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Gameover.selectpush = 0;
					//next?次のステージへ的な
					SetEffect(80, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
					mouseuse = true;
				}
				//ワールド選択		100, 700
				if (mouse_pos_X > 22.0f && mouse_pos_X < 150.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Gameover.selectpush = 1;
					//ワールド選択に戻る
					SetEffect(76, D3DXVECTOR2(90.0f, 700.0f), D3DXVECTOR2(90.0f, 700.0f), 1,
						D3DXVECTOR2(227.0f, 202.0f), D3DXVECTOR2(227.0f, 202.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
					mouseuse = true;
				}
				//プレイヤー配置	600, 700
				if (mouse_pos_X > 1025.0f && mouse_pos_X < 1175.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Gameover.selectpush = 2;
					//プレイヤー配置に戻る
					SetEffect(100, D3DXVECTOR2(1100.0f, 700.0f), D3DXVECTOR2(1100.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 109.0f), D3DXVECTOR2(200.0f, 109.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
					mouseuse = true;
				}

				//リザルトにいく
				if (mouse_pos_X > 400.0f && mouse_pos_X < 950.0f && mouse_pos_Y > 500.0f && mouse_pos_Y < 600.0f)
				{
					g_Gameover.selectpush = 3;
					//リザルトに行く
					SetEffect(98, D3DXVECTOR2(700.0f, 545.0f), D3DXVECTOR2(700.0f, 545.0f), 1,
						D3DXVECTOR2(725.0f, 85.0f), D3DXVECTOR2(725.0f, 85.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
					mouseuse = true;
				}

				if (GetFadeState() == FADE_NONE)
				{
					if (mouseuse && mouse_Lclick)
					{
						g_SENo = LoadSound("data/SE/「ピロリ」決定のボタン音・アクセント音.wav");
						PlaySound(g_SENo, 0);
						if (g_Gameover.selectpush == 0)
						{
							// InitゲームでBGMを流すためtrueにしておく
							BGMonceTrue();
							SceneTransition(SCENE_GAME);
						}

						if (g_Gameover.selectpush == 1)
						{
							SceneTransition(SCENE_STAGE_SELECT);
						}

						if (g_Gameover.selectpush == 2)
						{
							SceneTransition(SCENE_PLACEMENT);
						}
					}
				}
				if (g_Gameover.selectpush == 3)
				{
					if (mouseuse && mouse_Lclick)
					{
						result_click2 = true;
						g_Gameover.gameovertime = 0;
						EffectBreak(map_back2);
						EffectBreak(gameover);
						EffectBreak(next2);
						EffectBreak(placement2);
						EffectBreak(result2);
					}
				}
			}
			if (g_Gameover.selecttime >= 0)
				g_Gameover.selecttime--;

	
		// 毎フレームカウントを増やす
		g_Gameover.gameovertime++;
	}

	if (result_click2 == true)
	{

		if (g_Gameover.resulttime2 == 10)
		{


			////暗闇4 明かりなら48
			//SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
			//	D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
			//	0.0f, 0.5f, 100, 999, 0, 180,
			//	0.0f, 0.0f, 0);
			//横1440
			//縦810
			//ゲームクリア
			/*SetEffect(5, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT / 2), 1,
				0.0f, 1.0f, 30, 120, 60, 90,
				0.0f, 0.0f, 0);*/

		}



		if (g_Gameover.resulttime2 == 30)
		{
			//（アドバイス？）
			/*SetEffect(1, D3DXVECTOR2(SCREEN_WIDTH / 2, 405), D3DXVECTOR2(SCREEN_WIDTH / 2, 405), 0,
				D3DXVECTOR2(590, 1000), D3DXVECTOR2(590, 1000), 1,
				0.0f, 1.0f, 100, 999, 0, 180,
				0.0f, 0.0f, 0);*/
			SetEffect(74, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				D3DXVECTOR2(1400, 800), D3DXVECTOR2(1400, 800), 1,
				0.0f, 1.0f, 100, 999, 0, 180,
				0.0f, 0.0f, 0);

			//キャラ絵
			SetEffect(101, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
				D3DXVECTOR2(1400, 750), D3DXVECTOR2(1400, 750), 1,
				0.0f, 1.0f, 100, 999, 0, 180,
				0.0f, 0.0f, 0);

			DrawNoteStageNum();

			// ミッション(文章)を表示する
			//DrawMissionResult();だとなぜか表示されない同じこと書いてるのに。。。
			SAVEDATA* p_Savedata = GetSavedata();

			// ステージデータからミッション内容などを読み取る
			STAGEDATA* p_Stagedata = GetStagedata();

			float sizebairitu = 0.7f;		// ステージセレクトの時の殻の倍率

			float size_x = 768.0f * sizebairitu;
			float size_y = 128.0f * sizebairitu;

			float interval_y = size_y;

			float base_pos1_x = 1110.0f;
			float base_pos1_y = 265.0f;

			float base_pos2_x = base_pos1_x;
			float base_pos2_y = base_pos1_y;

			// 数字の設定
			float interval_magnification = 0.35f;	// 数字表示の間隔の倍率

			float num_size_x = 60.0f;
			float num_size_y = 60.0f;

			int move_frame = 12;

			for (int i = 0; i < MAX_MISSION; i++)
			{
				// コンテンツのidを描写用に、エフェクトで設定されているidに変換
				int Content_Texid = ContentsNumToTexid(p_Stagedata->mission_ContentsNum[i]);
				// セットエフェクトで文字の描写
			/*	int Content_EffectArray =
					SetEffect(Content_Texid, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
						D3DXVECTOR2(size_x, size_y), D3DXVECTOR2(size_x, size_y), 0,
						0.0f, 1.0f, 100, 999, 0, 1,
						0.0f, 0.0f, 0);*/

				// ミッションのテクスチャIDから数字の座標がどれだけ真ん中からずれてるかをとってくる(xのみ)
				float number_gap_x = MissionTexIdToNumXGAP(Content_Texid) * sizebairitu;

				// 数字の描写		ミッションの番号ごとに数字を描く場所は決まってると思うので、それもswitch分で判別できると楽
			/*	int Number_EffectArray[2] = { 0,0 };
				int* p_Number_EffectArray = Number_EffectArray;
				SetEffectNumber(p_Stagedata->mission_JudgeNum[i], p_Number_EffectArray, D3DXVECTOR2(base_pos1_x - number_gap_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - number_gap_x, base_pos2_y + interval_y * i), 1,
					D3DXVECTOR2(num_size_x* sizebairitu, num_size_y* sizebairitu), D3DXVECTOR2(num_size_x, num_size_y), 0,
					0.0f, 1.0f, 100, 999, 0, 1,
					0.0f, 0.0f, 0, false, interval_magnification);*/
			}
		}

		if (g_Gameover.resulttime2 == 30)
		{

			//星(影)
			SetEffect(82, D3DXVECTOR2(800.0f, 280.0f), D3DXVECTOR2(800.0f, 280.0f), 0,
				D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
				0.0f, 1.0f, 60, 999, 0, 60,
				0.0f, 0.0f, 0);
			//星(影)
			SetEffect(82, D3DXVECTOR2(800.0f, 360.0f), D3DXVECTOR2(800.0f, 360.0f), 0,
				D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
				0.0f, 1.0f, 60, 999, 0, 60,
				0.0f, 0.0f, 0);
			//星(影)
			SetEffect(82, D3DXVECTOR2(800.0f, 440.0f), D3DXVECTOR2(800.0f, 440.0f), 0,
				D3DXVECTOR2(90.0f, 90.0f), D3DXVECTOR2(90.0f, 90.0f), 1,
				0.0f, 1.0f, 60, 999, 0, 60,
				0.0f, 0.0f, 0);

			// クリアタイムの表示 p_Gamedata  SetEffectTimeNumber
			int Number_EffectArray[2] = { 0,0 };
			int* p_Number_EffectArray = Number_EffectArray;
			SetEffectTimeNumber(p_Gamedata->game_time, p_Number_EffectArray, D3DXVECTOR2(850.0f, 600.0f), D3DXVECTOR2(800.0f, 540.0f), 0,
				D3DXVECTOR2(48.0f, 48.0f), D3DXVECTOR2(30.0f, 30.0f), 0,
				0.0f, 1.0f, 60, 999, 0, 60,
				0.0f, 0.0f, 0);

			// 最速タイムの表示 p_Gamedata  SetEffectTimeNumber
			SetEffectTimeNumber(p_Savedata[p_Stagedata->stagenum].clear_time, p_Number_EffectArray, D3DXVECTOR2(1112.0f, 600.0f), D3DXVECTOR2(1050.0f, 540.0f), 0,
				D3DXVECTOR2(48.0f, 48.0f), D3DXVECTOR2(30.0f, 30.0f), 0,
				0.0f, 1.0f, 60, 999, 0, 60,
				0.0f, 0.0f, 0);

		}

		if (g_Gameover.resulttime2 == 80)
		{
			//ふせん
			SetEffect(126, D3DXVECTOR2(1020.0f, 360.0f), D3DXVECTOR2(1020.0f, 360.0f), 0,
				D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(435.0f, 260.0f), 1,
				0.0f, 1.0f, 120, 999, 0, 60,
				0.0f, 0.0f, 0);
			// ミッションをクリアしているなら表示する
			if (p_Savedata[p_Stagedata->stagenum].mission_clear[0] == 1)
			{
				////星
				//SetEffect(83, D3DXVECTOR2(800.0f, 280.0f), D3DXVECTOR2(800.0f, 280.0f), 0,
				//	D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				//	0.0f, 1.0f, 120, 999, 0, 60,
				//	0.0f, 0.0f, 0);
				////バツ印
				//SetEffect(124, D3DXVECTOR2(795.0f, 380.0f), D3DXVECTOR2(800.0f, 380.0f), 0,
				//	D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				//	0.0f, 1.0f, 120, 999, 0, 60,
				//	0.0f, 0.0f, 0);
			}
			//横1440
			//縦810
		}

		if (g_Gameover.resulttime2 == 100)
		{
			// ミッションをクリアしているなら表示する
			if (p_Savedata[p_Stagedata->stagenum].mission_clear[1] == 1)
			{
				////星
				//SetEffect(84, D3DXVECTOR2(800.0f, 360.0f), D3DXVECTOR2(800.0f, 360.0f), 0,
				//	D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				//	0.0f, 1.0f, 120, 999, 0, 60,
				//	0.0f, 0.0f, 0);
				////バツ印
				//SetEffect(124, D3DXVECTOR2(795.0f, 360.0f), D3DXVECTOR2(800.0f, 360.0f), 0,
				//	D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
				//	0.0f, 1.0f, 120, 999, 0, 60,
				//	0.0f, 0.0f, 0);
			}
		}

		if (g_Gameover.resulttime2 == 120)
		{
			//// ミッションをクリアしているなら表示する
			//if (p_Savedata[p_Stagedata->stagenum].mission_clear[2] == 1)
			//{
			//	//星
			//	SetEffect(85, D3DXVECTOR2(800.0f, 440.0f), D3DXVECTOR2(800.0f, 440.0f), 0,
			//		D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
			//		0.0f, 1.0f, 120, 999, 0, 60,
			//		0.0f, 0.0f, 0);
			//	////バツ印
			//	//SetEffect(124, D3DXVECTOR2(795.0f, 440.0f), D3DXVECTOR2(800.0f, 440.0f), 0,
			//	//	D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
			//	//	0.0f, 1.0f, 120, 999, 0, 60,
			//	//	0.0f, 0.0f, 0);
			//}
		}


		if (g_Gameover.resulttime2 == 140)
		{
			//明るくする暗くするなら4
			/*SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
				D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
				0.0f, 0.5f, 0, 1, 0, 1,
				0.0f, 0.0f, 0);*/

				//	//next?次のステージへ的な
				//SetEffect(77, D3DXVECTOR2(1080.0f, 700.0f), D3DXVECTOR2(1080.0f, 700.0f), 0,
				//	D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 0,
				//	0.0f, 1.0f, 0, 1, 0, 0,
				//	0.0f, 0.0f, 0);

				//ワールド選択に戻る
			int asdfeff = 
			SetEffect(75, D3DXVECTOR2(400.0f, 700.0f), D3DXVECTOR2(400.0f, 700.0f), 0,
				D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(150.0f, 150.0f), 0,
				0.0f, 1.0f, 40, 999, 0, 0,
				0.0f, 0.0f, 0);

			//リトライ
			int fefeff = 
			SetEffect(79, D3DXVECTOR2(1100.0f, 700.0f), D3DXVECTOR2(1100.0f, 700.0f), 0,
				D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 0,
				0.0f, 1.0f, 40, 999, 0, 0,
				0.0f, 0.0f, 0);

			//プレイヤー配置に戻る
			SetEffect(99, D3DXVECTOR2(900.0f, 700.0f), D3DXVECTOR2(900.0f, 700.0f), 0,
				D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 0,
				0.0f, 1.0f, 40, 999, 0, 0,
				0.0f, 0.0f, 0);
		}
			//横1440
			//縦810
		if (g_Gameover.resulttime2 >= 160)
		{
			if (g_Gameover.selectpush == 0)
			{
				////リトライ
				//SetEffect(80, D3DXVECTOR2(1100.0f, 700.0f), D3DXVECTOR2(1100.0f, 700.0f), 1,
				//	D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
				//	0.0f, 1.0f, 0, 1, 0, 1,
				//	0.0f, 0.0f, 0);

			}

			if (g_Gameover.selectpush == 1)
			{
				////ワールド選択に戻る
				//SetEffect(76, D3DXVECTOR2(393.0f, 702.0f), D3DXVECTOR2(393.0f, 702.0f), 1,
				//	D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
				//	0.0f, 1.0f, 0, 1, 0, 1,
				//	0.0f, 0.0f, 0);
			}

			if (g_Gameover.selectpush == 2)
			{
				////プレイヤー配置に戻る
				//SetEffect(100, D3DXVECTOR2(900.0f, 700.0f), D3DXVECTOR2(900.0f, 700.0f), 1,
				//	D3DXVECTOR2(200.0f, 109.0f), D3DXVECTOR2(200.0f, 109.0f), 1,
				//	0.0f, 1.0f, 0, 1, 0, 1,
				//	0.0f, 0.0f, 0);
			}

		
			// マウスの座標を使っての入力処理
			//1 1200 700	300 300
			if (mouse_pos_X > 1020.0f && mouse_pos_X < 1175.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
			{
				g_Gameover.selectpush = 0;
				//リトライ
				SetEffect(80, D3DXVECTOR2(1100.0f, 700.0f), D3DXVECTOR2(1100.0f, 700.0f), 1,
					D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);
				mouseuse = true;
			}
			//2 100 700		200 200
			else if (mouse_pos_X > 340.0f && mouse_pos_X < 460.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
			{
				g_Gameover.selectpush = 1;
				//ワールド選択に戻る
				SetEffect(76, D3DXVECTOR2(393.0f, 702.0f), D3DXVECTOR2(393.0f, 702.0f), 1,
					D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);
				mouseuse = true;
			}
			else if (mouse_pos_X > 820.0f && mouse_pos_X < 975.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
			{
				g_Gameover.selectpush = 2;
				//プレイヤー配置に戻る
				SetEffect(100, D3DXVECTOR2(900.0f, 700.0f), D3DXVECTOR2(900.0f, 700.0f), 1,
					D3DXVECTOR2(200.0f, 109.0f), D3DXVECTOR2(200.0f, 109.0f), 1,
					0.0f, 1.0f, 0, 1, 0, 1,
					0.0f, 0.0f, 0);
				mouseuse = true;
			}

			if (GetFadeState() == FADE_NONE)
			{
				if (mouseuse && mouse_Lclick)
				{
					g_SENo = LoadSound("data/SE/「ピロリ」決定のボタン音・アクセント音.wav");
					PlaySound(g_SENo, 0);
					if (g_Gameover.selectpush == 0)
					{
						// InitゲームでBGMを流すためtrueにしておく
						BGMonceTrue();
						SceneTransition(SCENE_GAME);
					}

					if (g_Gameover.selectpush == 1)
					{
						SceneTransition(SCENE_STAGE_SELECT);
					}

					if (g_Gameover.selectpush == 2)
					{
						SceneTransition(SCENE_PLACEMENT);
					}

				}
			}
			//// マウスが押される位置にあって、左クリック押されていて、フェード処理中ではないとき
			//if (mouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
			//{
			//	//SetVolume(g_BGMNo, 0.1f);

			//	//STAGE_SELECTへ移行する
			//	SceneTransition(SCENE_GAME);
			//}


			// もし前のフレームから変化があった場合のみエフェクトなどを変化させる
			bool Change = false;
			if (OldResultSelect != g_Gameover.selectpush)
				Change = true;

			// 変更があった場合、初期化と新しいもののセット
			if (Change == true)
			{
				// 初期化と前回使われていたものの消去
				g_Gameover.selecttime = 30;
				//EffectBreak(now_result_select_EffectArray);		// 前の描写を消す
				result_over_once = false;						// 1回も描写してないよにする
				result_over_once_time = 0;						// 描写してからの時間のリセット
			}


			if (g_Gameover.selecttime >= 0)
				g_Gameover.selecttime--;

		}

		// 毎フレームカウントを増やす
		g_Gameover.resulttime2++;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGameover(void)
{

}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
GAMEOVER* GetGameover(void)
{
	return &g_Gameover;
}


void SetGameover(D3DXVECTOR2 pos)
{

}