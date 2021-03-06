#pragma once

#include "main.h"
#include "bg.h"

#define MAX_MISSION (3)			// ミッション数の最大(最後尾)3つ固定
#define SAVEDATA_ELEMENTS	(4)			// ミッション数+クリアタイム
#define MAX_DIGIT	(3)			// 最大3桁まで
typedef struct {
	
	// セットエフェクトで使われる配列の番号を保管する
	int mission_background_EffectArray;					// 背景は1個なので1
	int mission_ContentsNum_EffectArray[MAX_MISSION];
	int mission_JudgeNum_EffectArray[MAX_MISSION][MAX_DIGIT];
	int	mission_star_EffectArray[MAX_MISSION];
	bool NewStar[MAX_MISSION];

}MISSION;

void InitMission();
void UninitMission();
void UpdateMission();

MISSION* GetMission();

void DrawMissionStageSelect();
void DeleteMissionStageSelect();

void DrawMissionResult();
void DeleteMissionResult();

void DrawMissionPause();
void DeleteMissionPause();

void DrawMissionPlacement();

bool ClearorFailure(int ContentsNum, int JudgeNum);
int ContentsNumToTexid(int mission_ContentsNum);
bool JudgeClearMission(int missionnum);
int DisplayLeftOrRight(int stagenum);
float MissionTexIdToNumXGAP(int texid);


void NewStarTrue(int missionnum);
bool GetNewStar(int missionnum);
void ClearNewStar();

void NewScoreTrue();
bool GetNewScore();
void ClearNewScore();