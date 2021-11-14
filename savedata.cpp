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
	// \‘¢‘Ì‚Ì‰Šú‰»
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





