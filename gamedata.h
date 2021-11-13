#pragma once

#include "main.h"
#include "bg.h"

// ゲーム内での出来事を記録するcppとh
typedef struct {

	int pass_count;			// パス(ボールを発射)をした回数
	int hit_wall_count;		// 壁にぶつかった回数
	int game_time;			// ゲームスタートしてからの時間

	// ほかにもいろいろあるとおもう


}GAMEDATA;


void InitGamedata();
void UninitGamedata();
void UpdateGamedata();

GAMEDATA* GetGamedata();