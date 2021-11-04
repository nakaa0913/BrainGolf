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

static STAGEDATA g_Stagedata;


void InitStagedata()
{
	// 構造体の初期化
	g_Stagedata.stagenum = 0;
	g_Stagedata.maparray[MAP_Y][MAP_X] = {};
	g_Stagedata.mission1 = 0;
	g_Stagedata.mission2 = 1;
	g_Stagedata.mission3 = 2;

	SetStageDataMapArray(1);

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

void SetStageDataMapArray(int stage)
{
	// 引数でもらったステージの番号を1桁ずつchar型にして合成する
	

	// とりあえずテスト
	LoadMapdataMain("data/STAGEDATA/stagetest.txt");

	return;
}







