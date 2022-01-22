#include<iostream>
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "gamedata.h"
#include "mission.h"
#include "effect.h"
#include "savedata.h"
#include "stageselect.h"

MISSION g_Mission;

void InitMission()
{
	g_Mission.mission_background_EffectArray = -1;
	for (int i = 0; i < MAX_MISSION; i++)
	{
		g_Mission.mission_ContentsNum_EffectArray[i] = -1;
		for (int j = 0; j < MAX_DIGIT; j++)
		{
			g_Mission.mission_JudgeNum_EffectArray[i][j] = -1;
		}
	}

	return;
}

void UninitMission()
{

	return;
}

void UpdateMission()
{



	return;
}


MISSION* GetMission()
{
	return &g_Mission;
}


// ミッションが達成されてるかをbool型で返す関数trueでクリア
bool ClearorFailure(int ContentsNum, int JudgeNum)
{
	GAMEDATA p_Gamedata = *GetGamedata();

	switch (ContentsNum)
	{
	case 0:		// JudgeNum回以内のパスでクリア
		if (p_Gamedata.pass_count <= JudgeNum)
			return true;
		else
			return false;
	case 1:		// 壁にJudgeNum回以上反射させてからクリア
		if (p_Gamedata.hit_wall_count >= JudgeNum)
			return true;
		else
			return false;
	case 2:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 3:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 4:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 5:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 6:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 7:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 8:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 9:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 10:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 11:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 12:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 13:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 14:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 15:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 16:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 17:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 18:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 19:		// JudgeNum秒以内でクリア
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;



	default:
		break;
	}


	// ContentsNumがおかしい場合ここに来る
	exit(23);
	return false;
}

// ミッションが達成されてるかをbool型で返す関数trueでクリア, こっちは何個目のミッションかだけでいい
bool JudgeClearMission(int missionnum)
{
	bool judge = false;

	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	//int stagenum_now = GetNowChoiceStageNum();			// 現在のステージをもらう1~20

	int mission_ContentsNum = p_Stagedata->mission_ContentsNum[missionnum];
	int mission_JudgeNum = p_Stagedata->mission_JudgeNum[missionnum];

	judge = ClearorFailure(p_Stagedata->mission_ContentsNum[missionnum], p_Stagedata->mission_JudgeNum[missionnum]);

	return judge;
}


// 999表示なので1回だけ表示してあげてね
void DrawMissionStageSelect()
{
	// ステージデータからミッション内容などを読み取る
	STAGEDATA* p_Stagedata = GetStagedata();

	float size_x = 768.0f;
	float size_y = 128.0f;

	float background_size_y = size_y * 3;

	float interval_y = size_y;

	float base_pos1_x = SCREEN_WIDTH / 2;
	float base_pos1_y = SCREEN_HEIGHT + background_size_y;

	float base_pos2_x = SCREEN_WIDTH / 2;
	float base_pos2_y = SCREEN_HEIGHT / 2;

	// 数字の設定
	float num_size_x = 40.0f;
	float num_size_y = 40.0f;


	// ミッションの背景を表示	Effectでのidは25		ミッションの中身を表示が3つあってそこの真ん中に来るように配置する->iのとこを1にかえるとOK
	int Background_EffectArray =
		SetEffect(25, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * 1), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * 1), 1,
			D3DXVECTOR2(size_x, background_size_y), D3DXVECTOR2(size_x, background_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, 20,
			0.0f, 0.0f, 0);

	// エフェクトが生成された場所の番号の保存
	g_Mission.mission_background_EffectArray = Background_EffectArray;

	// ミッションの中身を表示
	for (int i = 0; i < MAX_MISSION; i++)
	{
		// コンテンツのidを描写用に、エフェクトで設定されているidに変換
		int Content_Texid = ContentsNumToTexid(p_Stagedata->mission_ContentsNum[i]);
		// セットエフェクトで文字の描写
		int Content_EffectArray =
			SetEffect(Content_Texid, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
				D3DXVECTOR2(size_x, size_y), D3DXVECTOR2(size_x, size_y), 0,
				0.0f, 1.0f, 0, 999, 0, 20,
				0.0f, 0.0f, 0);

		// 数字の描写		ミッションの番号ごとに数字を描く場所は決まってると思うので、それもswitch分で判別できると楽
		int Number_EffectArray[2] = { 0,0 };
		int* p_Number_EffectArray = Number_EffectArray;
		SetEffectNumber(p_Stagedata->mission_JudgeNum[i], p_Number_EffectArray, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
			D3DXVECTOR2(num_size_x, num_size_y), D3DXVECTOR2(num_size_x, num_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, 20,
			0.0f, 0.0f, 0);

		// エフェクトが生成された場所の番号の保存
		g_Mission.mission_ContentsNum_EffectArray[i] = Content_EffectArray;
		g_Mission.mission_JudgeNum_EffectArray[i][0] = Number_EffectArray[0];
		g_Mission.mission_JudgeNum_EffectArray[i][1] = Number_EffectArray[1];		// 連番の保存
		int asd = 0;
	}
	return;
}

void DeleteMissionStageSelect()
{
	EffectBreak(g_Mission.mission_background_EffectArray);

	for (int i = 0; i < MAX_MISSION; i++)
	{
		EffectBreak(g_Mission.mission_ContentsNum_EffectArray[i]);
		EffectBreak(g_Mission.mission_JudgeNum_EffectArray[i][0], g_Mission.mission_JudgeNum_EffectArray[i][1]);	// 第2引数で連番の処理

	}
	return;
}

// mission_ContentsNum をEffect.cppで読み込めるidにしてあげる
int ContentsNumToTexid(int mission_ContentsNum)
{
	switch (mission_ContentsNum)
	{
	case 0:
		return 26;
	case 1:
		return 27;
	case 2:
		return 28;
	case 3:
		return 29;
	case 4:
		return 30;
	case 5:
		return 31;
	case 6:
		return 32;
	case 7:
		return 33;
	case 8:
		return 34;
	case 9:
		return 35;
	case 10:
		return 36;
	case 11:
		return 37;
	case 12:
		return 38;
	case 13:
		return 39;
	case 14:
		return 40;
	case 15:
		return 41;
	case 16:
		return 42;
	case 17:
		return 43;
	case 18:
		return 44;
	case 19:
		return 45;

	default:
		break;
	}

	exit(24);
	return -1;
}

void DrawMissionResult()
{
	// ステージデータからミッション内容などを読み取る
	STAGEDATA* p_Stagedata = GetStagedata();

	float size_x = 768.0f;
	float size_y = 128.0f;

	float background_size_y = size_y * 3;

	float interval_y = size_y;

	float base_pos1_x = SCREEN_WIDTH / 2;
	float base_pos1_y = SCREEN_HEIGHT + background_size_y;

	float base_pos2_x = SCREEN_WIDTH / 2;
	float base_pos2_y = SCREEN_HEIGHT / 2;

	// 数字の設定
	float num_size_x = 40.0f;
	float num_size_y = 40.0f;


	// ミッションの背景を表示	Effectでのidは25		ミッションの中身を表示が3つあってそこの真ん中に来るように配置する->iのとこを1にかえるとOK
	int Background_EffectArray =
		SetEffect(25, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * 1), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * 1), 1,
			D3DXVECTOR2(size_x, background_size_y), D3DXVECTOR2(size_x, background_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, 20,
			0.0f, 0.0f, 0);

	// エフェクトが生成された場所の番号の保存
	g_Mission.mission_background_EffectArray = Background_EffectArray;

	// ミッションの中身を表示
	for (int i = 0; i < MAX_MISSION; i++)
	{
		// コンテンツのidを描写用に、エフェクトで設定されているidに変換
		int Content_Texid = ContentsNumToTexid(p_Stagedata->mission_ContentsNum[i]);
		// セットエフェクトで文字の描写
		int Content_EffectArray =
			SetEffect(Content_Texid, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
				D3DXVECTOR2(size_x, size_y), D3DXVECTOR2(size_x, size_y), 0,
				0.0f, 1.0f, 0, 999, 0, 20,
				0.0f, 0.0f, 0);

		// 数字の描写		ミッションの番号ごとに数字を描く場所は決まってると思うので、それもswitch分で判別できると楽
		int Number_EffectArray[2] = { 0,0 };
		int* p_Number_EffectArray = Number_EffectArray;
		SetEffectNumber(p_Stagedata->mission_JudgeNum[i], p_Number_EffectArray, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
			D3DXVECTOR2(num_size_x, num_size_y), D3DXVECTOR2(num_size_x, num_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, 20,
			0.0f, 0.0f, 0);

		// エフェクトが生成された場所の番号の保存
		g_Mission.mission_ContentsNum_EffectArray[i] = Content_EffectArray;
		g_Mission.mission_JudgeNum_EffectArray[i][0] = Number_EffectArray[0];
		g_Mission.mission_JudgeNum_EffectArray[i][1] = Number_EffectArray[1];		// 連番の保存
	}
	return;
}

void DeleteMissionResult()
{
	EffectBreak(g_Mission.mission_background_EffectArray);

	for (int i = 0; i < MAX_MISSION; i++)
	{
		EffectBreak(g_Mission.mission_ContentsNum_EffectArray[i]);
		EffectBreak(g_Mission.mission_JudgeNum_EffectArray[i][0], g_Mission.mission_JudgeNum_EffectArray[i][1]);	// 第2引数で連番の処理

	}
	return;
}

void DrawMissionPause()
{
	// ステージデータからミッション内容などを読み取る
	STAGEDATA* p_Stagedata = GetStagedata();

	float size_x = 768.0f;
	float size_y = 128.0f;

	float background_size_y = size_y * 3;

	float interval_y = size_y;

	float base_pos1_x = SCREEN_WIDTH / 2;
	float base_pos1_y = SCREEN_HEIGHT + background_size_y;

	float base_pos2_x = SCREEN_WIDTH / 2;
	float base_pos2_y = SCREEN_HEIGHT / 2;

	// 数字の設定
	float num_size_x = 40.0f;
	float num_size_y = 40.0f;


	// ミッションの背景を表示	Effectでのidは25		ミッションの中身を表示が3つあってそこの真ん中に来るように配置する->iのとこを1にかえるとOK
	int Background_EffectArray =
		SetEffect(25, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * 1), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * 1), 1,
			D3DXVECTOR2(size_x, background_size_y), D3DXVECTOR2(size_x, background_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, 20,
			0.0f, 0.0f, 0);

	// エフェクトが生成された場所の番号の保存
	g_Mission.mission_background_EffectArray = Background_EffectArray;

	// ミッションの中身を表示
	for (int i = 0; i < MAX_MISSION; i++)
	{
		// コンテンツのidを描写用に、エフェクトで設定されているidに変換
		int Content_Texid = ContentsNumToTexid(p_Stagedata->mission_ContentsNum[i]);
		// セットエフェクトで文字の描写
		int Content_EffectArray =
			SetEffect(Content_Texid, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
				D3DXVECTOR2(size_x, size_y), D3DXVECTOR2(size_x, size_y), 0,
				0.0f, 1.0f, 0, 999, 0, 20,
				0.0f, 0.0f, 0);

		// 数字の描写		ミッションの番号ごとに数字を描く場所は決まってると思うので、それもswitch分で判別できると楽
		int Number_EffectArray[2] = { 0,0 };
		int* p_Number_EffectArray = Number_EffectArray;
		SetEffectNumber(p_Stagedata->mission_JudgeNum[i], p_Number_EffectArray, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
			D3DXVECTOR2(num_size_x, num_size_y), D3DXVECTOR2(num_size_x, num_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, 20,
			0.0f, 0.0f, 0);

		// エフェクトが生成された場所の番号の保存
		g_Mission.mission_ContentsNum_EffectArray[i] = Content_EffectArray;
		g_Mission.mission_JudgeNum_EffectArray[i][0] = Number_EffectArray[0];
		g_Mission.mission_JudgeNum_EffectArray[i][1] = Number_EffectArray[1];		// 連番の保存
	}
	return;
}

void DeleteMissionPause()
{
	EffectBreak(g_Mission.mission_background_EffectArray);

	for (int i = 0; i < MAX_MISSION; i++)
	{
		EffectBreak(g_Mission.mission_ContentsNum_EffectArray[i]);
		EffectBreak(g_Mission.mission_JudgeNum_EffectArray[i][0], g_Mission.mission_JudgeNum_EffectArray[i][1]);	// 第2引数で連番の処理

	}
	return;
}