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
	// �\���̂̏�����
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

//////////// 0~2�~�b�V����,3�N���A�^�C���B�㏑������ꍇ�̂ݏ������ނ悤�ɂ���
//////////void WriteSaveData(int choicenum, int OverwriteNum)
//////////{
//////////	// ���ݑI������Ă���X�e�[�W�ԍ������Ă����B
//////////	STAGEDATA* p_Stagedata = GetStagedata();
//////////
//////////	// �X�e�[�W�̔ԍ���1������char�^�ɂ��č�������
//////////
//////////	char digit1[2] = "";
//////////	char digit2[2] = "";
//////////	char digit3[2] = "";
//////////	char stagename[128] = "data/SAVEDATA/savedata.txt";
//////////	char stagenameend[32] = ".txt";
//////////	char attachchar[32] = "";
//////////	int nownum = p_Stagedata->stagenum - 1;
//////////
//////////	if (nownum < 10)
//////////	{
//////////		// 1���̏���
//////////		digit1[0] = intTochar(nownum);
//////////		strcat(attachchar, digit1);
//////////		strcat(stagename, attachchar);
//////////	}
//////////	else if (nownum >= 10 && nownum < 100)
//////////	{
//////////		// 2���̏���
//////////		digit1[0] = intTochar(nownum / 10);
//////////		digit2[0] = intTochar(nownum % 10);
//////////		strcat(attachchar, digit1);
//////////		strcat(attachchar, digit2);
//////////		strcat(stagename, attachchar);
//////////
//////////	}
//////////	else
//////////	{
//////////		// 3���̏���	100�ȏ�̏ꍇ(�X�e�[�W���͑����Ă�3���z��Ƃ���)
//////////		digit3[0] = intTochar(nownum % 100);
//////////		nownum = nownum / 10;
//////////		digit2[0] = intTochar(nownum % 10);
//////////		digit1[0] = intTochar(nownum / 10);
//////////		strcat(attachchar, digit1);
//////////		strcat(attachchar, digit2);
//////////		strcat(attachchar, digit3);
//////////		strcat(stagename, attachchar);
//////////	}
//////////
//////////	strcat(stagename, stagenameend);
//////////
//////////
//////////	// �Ƃ肠�����e�X�g
//////////	LoadMapdataMain("data/STAGEDATA/stagetest.txt");
//////////
//////////	// �{�Ԃ͂�����
//////////	//LoadMapdataMain(stagename);
//////////
//////////	return;
//////////}


