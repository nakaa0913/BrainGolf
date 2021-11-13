#pragma once

#include "main.h"
#include "bg.h"
#include "mission.h"

#define MAX_STAGE	(30)		//�ő�X�e�[�W

typedef struct {
	int stagenum;				//�X�e�[�W�ԍ�
	int maparray[MAP_Y][MAP_X];	// �}�b�v�̔z��f�[�^
	int mission_ContentsNum[MAX_MISSION];				//�~�b�V�����̓��e	�~�b�V������3�Œ�Ȃ̂�3
	int mission_JudgeNum[MAX_MISSION];					//�~�b�V�����̓��e�Ŏg���鐔��

	//bool clear1;				//�~�b�V�������N���A������
	//bool clear2;				// ����̓v���C���[�̃Z�[�u�f�[�^�̕��ŊǗ�
	//bool clear3;
	//float cleartime;			//�N���A�^�C��
}STAGEDATA;


void InitStagedata();
void UninitStagedata();
void UpdateStagedata();

STAGEDATA* GetStagedata();

void SetStageData(int stagenum);