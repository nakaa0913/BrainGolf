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
#include "mission.h"

static STAGEDATA g_Stagedata;


void InitStagedata()
{
	// 構造体の初期化
	g_Stagedata.stagenum = 0;
	g_Stagedata.maparray[MAP_Y - 1][MAP_X - 1] = {};
	for (int i = 0; i < MAX_MISSION; i++)
	{
		g_Stagedata.mission_ContentsNum[i] = 0;
		g_Stagedata.mission_JudgeNum[i]	   = 0;
	}
	g_Stagedata.NumberofPeople = 9;


	//SetStageData(1);				// テストでこれしてるだけ。実際はセットステージはInitGameが終わった後にする。
	//SetStageData(1);				// テストでこれしてるだけ。実際はセットステージはInitGameが終わった後にする。

	return;
}

void UninitStagedata()
{

	return;
}

void UpdateStagedata()
{



	return;
}


STAGEDATA* GetStagedata()
{
	return &g_Stagedata;
}

void SetStageData(int stagenum)
{
	// 現在選択されているステージ番号を入れておく。
	g_Stagedata.stagenum = stagenum - 1;

	// 引数でもらったステージの番号を1桁ずつchar型にして合成する

	char digit1[2] = "";
	char digit2[2] = "";
	char digit3[2] = "";
	char stagename[128] = "data/STAGEDATA/stage";
	char stagenameend[32] = ".txt";
	char attachchar[32] = "";
	int nownum = stagenum;

	if (nownum < 10)
	{
		// 1桁の処理
		digit1[0] = intTochar(nownum);
		strcat(attachchar, digit1);
		strcat(stagename, attachchar);
	}
	else if (nownum >= 10 && nownum < 100)
	{
		// 2桁の処理
		digit1[0] = intTochar(nownum / 10);
		digit2[0] = intTochar(nownum % 10);
		strcat(attachchar, digit1);
		strcat(attachchar, digit2);
		strcat(stagename, attachchar);

	}
	else
	{
		// 3桁の処理	100以上の場合(ステージ数は多くても3桁想定とする)
		digit3[0] = intTochar(nownum % 100);
		nownum = nownum / 10;
		digit2[0] = intTochar(nownum % 10);
		digit1[0] = intTochar(nownum / 10);
		strcat(attachchar, digit1);
		strcat(attachchar, digit2);
		strcat(attachchar, digit3);
		strcat(stagename, attachchar);
	}

	strcat(stagename, stagenameend);

	// とりあえずテスト
	//LoadMapdataMain("data/STAGEDATA/Iwadera 1.txt");
	
	// 本番はこっち
	LoadMapdataMain(stagename);

	return;
}







