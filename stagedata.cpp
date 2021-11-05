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

static STAGEDATA g_Stagedata;


void InitStagedata()
{
	// �\���̂̏�����
	g_Stagedata.stagenum = 0;
	g_Stagedata.maparray[MAP_Y - 1][MAP_X - 1] = {};
	g_Stagedata.mission1 = 0;
	g_Stagedata.mission2 = 1;
	g_Stagedata.mission3 = 2;


	SetStageData(1);				// �e�X�g�ł��ꂵ�Ă邾���B���ۂ̓Z�b�g�X�e�[�W��InitGame���I�������ɂ���B

	return;
}

void UninitStagedata()
{

	return;
}

void UpdateStagedata()
{



	return;
}


STAGEDATA* GetStagedata()
{
	return &g_Stagedata;
}

void SetStageData(int stagenum)
{
	// �����ł�������X�e�[�W�̔ԍ���1������char�^�ɂ��č�������

	char digit1[2] = "";
	char digit2[2] = "";
	char digit3[2] = "";
	char stagename[128] = "data/STAGEDATA/stage";
	char stagenameend[32] = ".txt";
	char attachchar[32] = "";
	int nownum = stagenum;

	if (stagenum < 10)
	{
		// 1���̏���
		digit1[0] = intTochar(nownum);
		strcat(attachchar, digit1);
		strcat(stagename, attachchar);
	}
	else if (nownum >= 10 && nownum < 100)
	{
		// 2���̏���
		digit1[0] = intTochar(nownum / 10);
		digit2[0] = intTochar(nownum % 10);
		strcat(attachchar, digit1);
		strcat(attachchar, digit2);
		strcat(stagename, attachchar);

	}
	else
	{
		// 3���̏���	100�ȏ�̏ꍇ(�X�e�[�W���͑����Ă�3���z��Ƃ���)
		digit3[0] = intTochar(nownum % 100);
		nownum = stagenum / 10;
		digit2[0] = intTochar(nownum % 10);
		digit1[0] = intTochar(nownum / 10);
		strcat(attachchar, digit1);
		strcat(attachchar, digit2);
		strcat(attachchar, digit3);
		strcat(stagename, attachchar);
	}

	strcat(stagename, stagenameend);

	// �Ƃ肠�����e�X�g
	LoadMapdataMain("data/STAGEDATA/stagetest.txt");
	
	// �{�Ԃ͂�����
	//LoadMapdataMain(stagename);

	return;
}






