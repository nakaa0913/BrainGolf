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
#include "savedata.h"

static SAVEDATA g_Savedata[MAX_STAGE];


void InitSavedata()
{
	// 構造体の初期化
	for (int i = 0; i < MAX_STAGE; i++)
	{
		for (int j = 0; j < MAX_MISSION; j++)
		{
			g_Savedata[i].mission_clear[j] = 0;
		}
		g_Savedata[i].clear_time = 0;
	}

	LoadSavedata("data/SAVEDATA/savedata.txt");
		
	return;
}

void UninitSavedata()
{

	return;
}

void UpdateSavedata()
{



	return;
}


SAVEDATA* GetSavedata()
{
	return &g_Savedata[0];
}

//////////// 0~2ミッション,3クリアタイム。上書きする場合のみ書き込むようにする
//////////void WriteSaveData(int choicenum, int OverwriteNum)
//////////{
//////////	// 現在選択されているステージ番号を入れておく。
//////////	STAGEDATA* p_Stagedata = GetStagedata();
//////////
//////////	// ステージの番号を1桁ずつchar型にして合成する
//////////
//////////	char digit1[2] = "";
//////////	char digit2[2] = "";
//////////	char digit3[2] = "";
//////////	char stagename[128] = "data/SAVEDATA/savedata.txt";
//////////	char stagenameend[32] = ".txt";
//////////	char attachchar[32] = "";
//////////	int nownum = p_Stagedata->stagenum - 1;
//////////
//////////	if (nownum < 10)
//////////	{
//////////		// 1桁の処理
//////////		digit1[0] = intTochar(nownum);
//////////		strcat(attachchar, digit1);
//////////		strcat(stagename, attachchar);
//////////	}
//////////	else if (nownum >= 10 && nownum < 100)
//////////	{
//////////		// 2桁の処理
//////////		digit1[0] = intTochar(nownum / 10);
//////////		digit2[0] = intTochar(nownum % 10);
//////////		strcat(attachchar, digit1);
//////////		strcat(attachchar, digit2);
//////////		strcat(stagename, attachchar);
//////////
//////////	}
//////////	else
//////////	{
//////////		// 3桁の処理	100以上の場合(ステージ数は多くても3桁想定とする)
//////////		digit3[0] = intTochar(nownum % 100);
//////////		nownum = nownum / 10;
//////////		digit2[0] = intTochar(nownum % 10);
//////////		digit1[0] = intTochar(nownum / 10);
//////////		strcat(attachchar, digit1);
//////////		strcat(attachchar, digit2);
//////////		strcat(attachchar, digit3);
//////////		strcat(stagename, attachchar);
//////////	}
//////////
//////////	strcat(stagename, stagenameend);
//////////
//////////
//////////	// とりあえずテスト
//////////	LoadMapdataMain("data/STAGEDATA/stagetest.txt");
//////////
//////////	// 本番はこっち
//////////	//LoadMapdataMain(stagename);
//////////
//////////	return;
//////////}


