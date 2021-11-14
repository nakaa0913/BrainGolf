#pragma once

#include "main.h"
#include "bg.h"
#include "mission.h"

typedef struct {
	int mission_clear[MAX_MISSION];				// ミッションをクリアしているかどうか
	int clear_time;								//クリアタイム


}SAVEDATA;


void InitSavedata();
void UninitSavedata();
void UpdateSavedata();

SAVEDATA* GetSavedata();