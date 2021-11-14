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

MISSION g_Mission;

void InitMission()
{
	g_Mission.mission_background_EffectArray = 0;
	for (int i = 0; i < MAX_MISSION; i++)
	{
		g_Mission.mission_ContentsNum_EffectArray[i] = 0;
		for (int j = 0; j < MAX_DIGIT; j++)
		{
			g_Mission.mission_JudgeNum_EffectArray[i][j] = 0;
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

	judge = ClearorFailure(p_Stagedata->stagenum, p_Stagedata->mission_ContentsNum[missionnum]);

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



		// エフェクトが生成された場所の番号の保存
		g_Mission.mission_ContentsNum_EffectArray[i] = Content_EffectArray;
		//g_Mission.mission_JudgeNum_EffectArray[i][0] = 0;
		//g_Mission.mission_JudgeNum_EffectArray[i][1] = 0;
		//g_Mission.mission_JudgeNum_EffectArray[i][2] = 0;
	}
	return;
}

void DeleteMissionStageSelect()
{
	EffectBreak(g_Mission.mission_background_EffectArray);

	for (int i = 0; i < MAX_MISSION; i++)
	{
		EffectBreak(g_Mission.mission_ContentsNum_EffectArray[i]);

		//g_Mission.mission_JudgeNum_EffectArray[i][0] = 0;
		//g_Mission.mission_JudgeNum_EffectArray[i][1] = 0;
		//g_Mission.mission_JudgeNum_EffectArray[i][2] = 0;

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
	default:
		break;
	}

	exit(24);
	return -1;
}
