#pragma once

#include "main.h"
#include "bg.h"
#include "mission.h"

typedef struct {
	int mission_clear[MAX_MISSION];				// �~�b�V�������N���A���Ă��邩�ǂ���
	int clear_time;								//�N���A�^�C��


}SAVEDATA;


void InitSavedata();
void UninitSavedata();
void UpdateSavedata();

SAVEDATA* GetSavedata();