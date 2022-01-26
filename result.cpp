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
#include "fade.h"
#include "effect.h"
#include "mission.h"
#include "savedata.h"
#include "stagedata.h"
#include "keyboard.h"
#include "sound.h"
#include "mouse.h"
#include "gamedata.h"
#include "game.h"
#include "stageselect.h"
#include "placement.h"

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
static RESULT g_Result;

int now_result_select_EffectArray = -1;
bool result_select_once = false;
int result_select_once_time = 0;
//bool onlyOnce = true;
bool resultmouseuse = false;
bool result_click = false; //リザルト画面に行くかどうかの

//エフェクト関連
int map_back = -1;			// マップ戻る
int clear = -1;				// ゲームクリア
int next = -1;				//	次へ
int result = -1;			//	リザルト
int placement = -1;			//	配置から
int retry = -1;

bool resultfin = false;		// 全て終わったら何もしないように

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	resultfin = false;

	//テクスチャ読み込み


	g_Result.goaltime = 0;
	g_Result.selectpush = 0;
	g_Result.resulttime = 0;

	//初期化
	result_select_once = false;
	now_result_select_EffectArray = -1;
	result_select_once_time = 0;
	result_click = false;
	map_back = -1;
	clear = -1;
	next = -1;				//	次へ
	result = -1;			//	リザルト
	placement = -1;			//	配置から
	retry = -1;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();
	GAMEDATA* p_Gamedata = GetGamedata();

	//マウスの座標を取得
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();
	bool mouseuse = false;

	// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
	int OldResultSelect = g_Result.selectpush;

	if (resultfin == false)
	{
		if (result_click == false)
		{
			if (g_Result.goaltime == 10)
			{
				//暗闇4 明かりなら48
				SetEffect(48, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0,
					D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), D3DXVECTOR2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), 1,
					0.0f, 0.5f, 100, 999, 0, 180,
					0.0f, 0.0f, 0);
				clear =
					//ゲームクリア
					SetEffect(5, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
						D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1300, 700), 1,
						0.0f, 1.0f, 30, 999, 0, 90,
						0.0f, 0.0f, 0);
			}
			if (g_Result.goaltime == 90)
			{
				retry =
					//リトライ
					SetEffect(79, D3DXVECTOR2(800.0f, 700.0f), D3DXVECTOR2(800.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);

				placement =
					//プレイヤー配置に戻る
					SetEffect(99, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);

				map_back =
					//マップに戻る
					SetEffect(75, D3DXVECTOR2(100.0f, 700.0f), D3DXVECTOR2(100.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);

				result =
					//リザルトに行く
					SetEffect(97, D3DXVECTOR2(700.0f, 550.0f), D3DXVECTOR2(700.0f, 550.0f), 1,
						D3DXVECTOR2(700.0f, 80.0f), D3DXVECTOR2(700.0f, 80.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);

				next =
					//次のステージ
					SetEffect(77, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 1,
						D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
						0.0f, 1.0f, 0, 999, 0, 1,
						0.0f, 0.0f, 0);
			}

			if (g_Result.goaltime >= 90)
			{

				if (g_Result.selectpush == 0)
				{
					//next?次のステージへ的な
					SetEffect(80, D3DXVECTOR2(800.0f, 700.0f), D3DXVECTOR2(800.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);

				}

				if (g_Result.selectpush == 1)
				{
					//ワールド選択に戻る
					SetEffect(76, D3DXVECTOR2(90.0f, 700.0f), D3DXVECTOR2(90.0f, 700.0f), 1,
						D3DXVECTOR2(227.0f, 202.0f), D3DXVECTOR2(227.0f, 202.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 2)
				{
					//プレイヤー配置に戻る
					SetEffect(100, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 109.0f), D3DXVECTOR2(200.0f, 109.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 3)
				{
					//リザルトに行く
					SetEffect(98, D3DXVECTOR2(700.0f, 545.0f), D3DXVECTOR2(700.0f, 545.0f), 1,
						D3DXVECTOR2(725.0f, 85.0f), D3DXVECTOR2(725.0f, 85.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 4)
				{
					//次のステージ
					SetEffect(78, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 1,
						D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				//if (g_Result.selectpush == 3)
				//{
				//	//リザルトに行く
				//	SetEffect(98, D3DXVECTOR2(700.0f, 545.0f), D3DXVECTOR2(700.0f, 545.0f), 1,
				//		D3DXVECTOR2(725.0f, 85.0f), D3DXVECTOR2(725.0f, 85.0f), 1,
				//		0.0f, 1.0f, 0, 1, 0, 1,
				//		0.0f, 0.0f, 0);
				//}

				//マウス操作
				if (mouse_pos_X > 715.0f && mouse_pos_X < 870.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Result.selectpush = 0;
					mouseuse = true;
				}
				//ワールド選択		100, 700
				if (mouse_pos_X > 22.0f && mouse_pos_X < 150.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Result.selectpush = 1;
					mouseuse = true;
				}
				//プレイヤー配置	600, 700
				if (mouse_pos_X > 520.0f && mouse_pos_X < 675.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Result.selectpush = 2;
					mouseuse = true;
				}
				//リザルトにいく
				if (mouse_pos_X > 550.0f && mouse_pos_X < 840.0f && mouse_pos_Y > 500.0f && mouse_pos_Y < 600.0f)
				{
					g_Result.selectpush = 3;
					mouseuse = true;
				}
				//次のステージ
				if (mouse_pos_X > 1170.0f && mouse_pos_X < 1420.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 730.0f)
				{
					g_Result.selectpush = 4;
					mouseuse = true;
				}

				if (mouseuse && mouse_Lclick)
				{
					if (g_Result.selectpush == 0)
					{
						// InitゲームでBGMを流すためtrueにしておく
						BGMonceTrue();
						SceneTransition(SCENE_GAME);
					}

					if (g_Result.selectpush == 1)
					{
						SceneTransition(SCENE_STAGE_SELECT);
					}

					if (g_Result.selectpush == 2)
					{
						SceneTransition(SCENE_PLACEMENT);
					}

					if (g_Result.selectpush == 4)
					{
						// 次のステージへ
						resultfin = true;
						//GoalFalse();
						NextstageTrue();
						PushNextstage();
						NextNowChoiceStageNum();
						ResetPlacementArray();
						SceneTransition(SCENE_PLACEMENT);
					}
				}

				if (g_Result.selectpush == 3)
				{
					if (mouseuse && mouse_Lclick)
					{
						result_click = true;
						g_Result.goaltime = 0;
						EffectBreak(map_back);
						EffectBreak(clear);
						EffectBreak(next);
						EffectBreak(placement);
						EffectBreak(result);
						EffectBreak(retry);
					}
				}
			}
		}

		g_Result.goaltime++;

		//リザルト画面にいった状態
		if (result_click == true)
		{

			if (g_Result.resulttime == 10)
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



			if (g_Result.resulttime == 30)
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

				SetEffect(101, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
					D3DXVECTOR2(1400, 750), D3DXVECTOR2(1400, 750), 1,
					0.0f, 1.0f, 100, 999, 0, 180,
					0.0f, 0.0f, 0);

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
					int Content_EffectArray =
						SetEffect(Content_Texid, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
							D3DXVECTOR2(size_x, size_y), D3DXVECTOR2(size_x, size_y), 0,
							0.0f, 1.0f, 100, 999, 0, 1,
							0.0f, 0.0f, 0);

					// ミッションのテクスチャIDから数字の座標がどれだけ真ん中からずれてるかをとってくる(xのみ)
					float number_gap_x = MissionTexIdToNumXGAP(Content_Texid) * sizebairitu;

					// 数字の描写		ミッションの番号ごとに数字を描く場所は決まってると思うので、それもswitch分で判別できると楽
					int Number_EffectArray[2] = { 0,0 };
					int* p_Number_EffectArray = Number_EffectArray;
					SetEffectNumber(p_Stagedata->mission_JudgeNum[i], p_Number_EffectArray, D3DXVECTOR2(base_pos1_x - number_gap_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - number_gap_x, base_pos2_y + interval_y * i), 1,
						D3DXVECTOR2(num_size_x * sizebairitu, num_size_y * sizebairitu), D3DXVECTOR2(num_size_x, num_size_y), 0,
						0.0f, 1.0f, 100, 999, 0, 1,
						0.0f, 0.0f, 0, interval_magnification);
				}






			}

			if (g_Result.resulttime == 30)
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

			if (g_Result.resulttime == 80)
			{
				// ミッションをクリアしているなら表示する
				if (p_Savedata[p_Stagedata->stagenum].mission_clear[0] == 1)
				{
					////星
					SetEffect(83, D3DXVECTOR2(800.0f, 280.0f), D3DXVECTOR2(800.0f, 280.0f), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}
				//横1440
				//縦810
			}

			if (g_Result.resulttime == 100)
			{
				// ミッションをクリアしているなら表示する
				if (p_Savedata[p_Stagedata->stagenum].mission_clear[1] == 1)
				{
					//星
					SetEffect(84, D3DXVECTOR2(800.0f, 360.0f), D3DXVECTOR2(800.0f, 360.0f), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}
			}

			if (g_Result.resulttime == 120)
			{
				// ミッションをクリアしているなら表示する
				if (p_Savedata[p_Stagedata->stagenum].mission_clear[2] == 1)
				{
					//星
					SetEffect(85, D3DXVECTOR2(800.0f, 440.0f), D3DXVECTOR2(800.0f, 440.0f), 0,
						D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(100.0f, 100.0f), 1,
						0.0f, 1.0f, 120, 999, 0, 60,
						0.0f, 0.0f, 0);
				}
			}


			if (g_Result.resulttime == 160)
			{


				//next?次のステージへ的な
				SetEffect(77, D3DXVECTOR2(1080.0f, 700.0f), D3DXVECTOR2(1080.0f, 700.0f), 1,
					D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
					0.0f, 1.0f, 0, 999, 0, 1,
					0.0f, 0.0f, 0);

				//ワールド選択に戻る
				SetEffect(75, D3DXVECTOR2(400.0f, 700.0f), D3DXVECTOR2(400.0f, 700.0f), 1,
					D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
					0.0f, 1.0f, 0, 999, 0, 1,
					0.0f, 0.0f, 0);

				//リトライ
				SetEffect(79, D3DXVECTOR2(800.0f, 700.0f), D3DXVECTOR2(800.0f, 700.0f), 1,
					D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
					0.0f, 1.0f, 0, 999, 0, 1,
					0.0f, 0.0f, 0);

				//プレイヤー配置に戻る
				SetEffect(99, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
					D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
					0.0f, 1.0f, 0, 999, 0, 1,
					0.0f, 0.0f, 0);
			}
			//横1440
			//縦810

			if (g_Result.resulttime >= 160)
			{
				if (g_Result.selectpush == 0)
				{
					//next?次のステージへ的な
					SetEffect(78, D3DXVECTOR2(1080.0f, 700.0f), D3DXVECTOR2(1080.0f, 700.0f), 1,
						D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR2(300.0f, 150.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);

				}

				if (g_Result.selectpush == 1)
				{
					//ワールド選択に戻る
					SetEffect(76, D3DXVECTOR2(393.0f, 702.0f), D3DXVECTOR2(393.0f, 702.0f), 1,
						D3DXVECTOR2(150.0f, 150.0f), D3DXVECTOR2(150.0f, 150.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 2)
				{
					//リトライ
					SetEffect(80, D3DXVECTOR2(800.0f, 700.0f), D3DXVECTOR2(800.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 100.0f), D3DXVECTOR2(200.0f, 100.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				if (g_Result.selectpush == 3)
				{
					//プレイヤー配置に戻る
					SetEffect(100, D3DXVECTOR2(600.0f, 700.0f), D3DXVECTOR2(600.0f, 700.0f), 1,
						D3DXVECTOR2(200.0f, 109.0f), D3DXVECTOR2(200.0f, 109.0f), 1,
						0.0f, 1.0f, 0, 1, 0, 1,
						0.0f, 0.0f, 0);
				}

				// マウスの座標を使っての入力処理
				//1 1200 700	300 300
				if (mouse_pos_X > 950.0f && mouse_pos_X < 1200.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
				{
					g_Result.selectpush = 0;
					resultmouseuse = true;
				}
				//2 100 700		200 200
				if (mouse_pos_X > 340.0f && mouse_pos_X < 460.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
				{
					g_Result.selectpush = 1;
					resultmouseuse = true;
				}
				if (mouse_pos_X > 770.0f && mouse_pos_X < 930.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
				{
					g_Result.selectpush = 2;
					resultmouseuse = true;
				}
				if (mouse_pos_X > 480.0f && mouse_pos_X < 690.0f && mouse_pos_Y > 660.0f && mouse_pos_Y < 740.0f)
				{
					g_Result.selectpush = 3;
					resultmouseuse = true;
				}

				if (resultmouseuse && mouse_Lclick)
				{
					if (g_Result.selectpush == 0)
					{
						// 次のステージへ
						resultfin = true;
						//GoalFalse();
						NextstageTrue();
						PushNextstage();
						NextNowChoiceStageNum();
						ResetPlacementArray();
						SceneTransition(SCENE_PLACEMENT);
					}

					if (g_Result.selectpush == 1)
					{
						SceneTransition(SCENE_STAGE_SELECT);
					}

					if (g_Result.selectpush == 2)
					{
						// InitゲームでBGMを流すためtrueにしておく
						BGMonceTrue();
						SceneTransition(SCENE_GAME);
					}
					if (g_Result.selectpush == 3)
					{
						SceneTransition(SCENE_PLACEMENT);
					}
				}

				//// マウスが押される位置にあって、左クリック押されていて、フェード処理中ではないとき
				//if (resultmouseuse && mouse_Lclick && GetFadeState() == FADE_NONE)
				//{
				//	//SetVolume(g_BGMNo, 0.1f);

				//	//STAGE_SELECTへ移行する
				//	SceneTransition(SCENE_STAGE_SELECT);
				//}


				// もし前のフレームから変化があった場合のみエフェクトなどを変化させる
				bool Change = false;
				if (OldResultSelect != g_Result.selectpush)
					Change = true;

				// 変更があった場合、初期化と新しいもののセット
				if (Change == true)
				{
					// 初期化と前回使われていたものの消去
					g_Result.selecttime = 30;
					//EffectBreak(now_result_select_EffectArray);		// 前の描写を消す
					result_select_once = false;						// 1回も描写してないよにする
					result_select_once_time = 0;						// 描写してからの時間のリセット
				}


				if (g_Result.selecttime >= 0)
					g_Result.selecttime--;


			}

			// 毎フレームカウントを増やす
			g_Result.resulttime++;
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{

}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
RESULT* GetResult(void)
{
	return &g_Result;
}


void SetResult(D3DXVECTOR2 pos)
{

}

bool checkresult()
{
	return resultfin;
}