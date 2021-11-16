#pragma once

#include "main.h"
#include "bg.h"

#define MAX_MISSION (3)			// �~�b�V�������̍ő�(�Ō��)3�Œ�
#define SAVEDATA_ELEMENTS	(4)			// �~�b�V������+�N���A�^�C��
#define MAX_DIGIT	(3)			// �ő�3���܂�
typedef struct {
	
	// �Z�b�g�G�t�F�N�g�Ŏg����z��̔ԍ���ۊǂ���
	int mission_background_EffectArray;					// �w�i��1�Ȃ̂�1
	int mission_ContentsNum_EffectArray[MAX_MISSION];
	int mission_JudgeNum_EffectArray[MAX_MISSION][MAX_DIGIT];

}MISSION;

// �����������g��Ȃ�����
//void InitMission();
//void UninitMission();
//void UpdateMission();

MISSION* GetMission();

void DrawMissionStageSelect();
void DeleteMissionStageSelect();

void DrawMissionResult();
void DeleteMissionResult();

bool ClearorFailure(int ContentsNum, int JudgeNum);
int ContentsNumToTexid(int mission_ContentsNum);
bool JudgeClearMission(int missionnum);