#pragma once

#include "main.h"
#include "bg.h"

// ゲーム内での出来事を記録するcppとh
typedef struct {

	int pass_count;			// パス(ボールを発射)をした回数
	int hit_wall_count;		// 壁にぶつかった回数
	int game_time;			// ゲームスタートしてからの時間
	int warp_count;			// ワープを使った回数
	int acc_count;			// 加速版を使った回数
	int switch_count;		// すいっちを使った回数
	int break_floor_count;		// われるゆかを使った回数

	// ほかにもいろいろあるとおもう


}GAMEDATA;


void InitGamedata();
void UninitGamedata();
void UpdateGamedata();

GAMEDATA* GetGamedata();