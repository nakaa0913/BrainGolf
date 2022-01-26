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
#include "gamedata.h"

GAMEDATA g_Gamedata;

void InitGamedata()
{
	// \‘¢‘Ì‚Ì‰Šú‰»
	g_Gamedata.pass_count = 0;
	g_Gamedata.hit_wall_count = 0;
	g_Gamedata.game_time = 0;
	g_Gamedata.warp_count = 0;
	g_Gamedata.acc_count = 0;
	g_Gamedata.switch_count = 0;
	g_Gamedata.break_floor_count = 0;

	return;
}

void UninitGamedata()
{

	return;
}

void UpdateGamedata()
{



	return;
}


GAMEDATA* GetGamedata()
{
	return &g_Gamedata;
}







