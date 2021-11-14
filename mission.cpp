#include<iostream>
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
#include "mission.h"
#include "effect.h"
#include "savedata.h"

MISSION g_Mission;

void InitMission()
{
	g_Mission.mission_background_EffectArray = 0;
	for (int i = 0; i < MAX_MISSION; i++)
	{
		g_Mission.mission_ContentsNum_EffectArray[i] = 0;
		for (int j = 0; j < MAX_DIGIT; j++)
		{
			g_Mission.mission_JudgeNum_EffectArray[i][j] = 0;
		}
	}

	return;
}

void UninitMission()
{

	return;
}

void UpdateMission()
{



	return;
}


MISSION* GetMission()
{
	return &g_Mission;
}


// �~�b�V�������B������Ă邩��bool�^�ŕԂ��֐�true�ŃN���A
bool ClearorFailure(int ContentsNum, int JudgeNum)
{
	GAMEDATA p_Gamedata = *GetGamedata();

	switch (ContentsNum)
	{
	case 0:		// JudgeNum��ȓ��̃p�X�ŃN���A
		if (p_Gamedata.pass_count <= JudgeNum)
			return true;
		else
			return false;
	case 1:		// �ǂ�JudgeNum��ȏ㔽�˂����Ă���N���A
		if (p_Gamedata.hit_wall_count >= JudgeNum)
			return true;
		else
			return false;
	case 2:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;

	default:
		break;
	}


	// ContentsNum�����������ꍇ�����ɗ���
	exit(23);
	return false;
}

// �~�b�V�������B������Ă邩��bool�^�ŕԂ��֐�true�ŃN���A, �������͉��ڂ̃~�b�V�����������ł���
bool JudgeClearMission(int missionnum)
{
	bool judge = false;

	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	judge = ClearorFailure(p_Stagedata->stagenum, p_Stagedata->mission_ContentsNum[missionnum]);

	return judge;
}


// 999�\���Ȃ̂�1�񂾂��\�����Ă����Ă�
void DrawMissionStageSelect()
{
	// �X�e�[�W�f�[�^����~�b�V�������e�Ȃǂ�ǂݎ��
	STAGEDATA* p_Stagedata = GetStagedata();

	float size_x = 768.0f;
	float size_y = 128.0f;

	float background_size_y = size_y * 3;

	float interval_y = size_y;

	float base_pos1_x = SCREEN_WIDTH / 2;
	float base_pos1_y = SCREEN_HEIGHT + background_size_y;

	float base_pos2_x = SCREEN_WIDTH / 2;
	float base_pos2_y = SCREEN_HEIGHT / 2;

	// �~�b�V�����̔w�i��\��	Effect�ł�id��25		�~�b�V�����̒��g��\����3�����Ă����̐^�񒆂ɗ���悤�ɔz�u����->i�̂Ƃ���1�ɂ������OK
	int Background_EffectArray =
		SetEffect(25, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * 1), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * 1), 1,
			D3DXVECTOR2(size_x, background_size_y), D3DXVECTOR2(size_x, background_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, 20,
			0.0f, 0.0f, 0);

	// �G�t�F�N�g���������ꂽ�ꏊ�̔ԍ��̕ۑ�
	g_Mission.mission_background_EffectArray = Background_EffectArray;

	// �~�b�V�����̒��g��\��
	for (int i = 0; i < MAX_MISSION; i++)
	{
		// �R���e���c��id��`�ʗp�ɁA�G�t�F�N�g�Őݒ肳��Ă���id�ɕϊ�
		int Content_Texid = ContentsNumToTexid(p_Stagedata->mission_ContentsNum[i]);
		// �Z�b�g�G�t�F�N�g�ŕ����̕`��
		int Content_EffectArray =
			SetEffect(Content_Texid, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 1,
				D3DXVECTOR2(size_x, size_y), D3DXVECTOR2(size_x, size_y), 0,
				0.0f, 1.0f, 0, 999, 0, 20,
				0.0f, 0.0f, 0);

		// �����̕`��		�~�b�V�����̔ԍ����Ƃɐ�����`���ꏊ�͌��܂��Ă�Ǝv���̂ŁA�����switch���Ŕ��ʂł���Ɗy
		int Number_EffectArray[2] = { 0,0 };



		// �G�t�F�N�g���������ꂽ�ꏊ�̔ԍ��̕ۑ�
		g_Mission.mission_ContentsNum_EffectArray[i] = Content_EffectArray;
		//g_Mission.mission_JudgeNum_EffectArray[i][0] = 0;
		//g_Mission.mission_JudgeNum_EffectArray[i][1] = 0;
		//g_Mission.mission_JudgeNum_EffectArray[i][2] = 0;
	}
	return;
}

void DeleteMissionStageSelect()
{
	EffectBreak(g_Mission.mission_background_EffectArray);

	for (int i = 0; i < MAX_MISSION; i++)
	{
		EffectBreak(g_Mission.mission_ContentsNum_EffectArray[i]);

		//g_Mission.mission_JudgeNum_EffectArray[i][0] = 0;
		//g_Mission.mission_JudgeNum_EffectArray[i][1] = 0;
		//g_Mission.mission_JudgeNum_EffectArray[i][2] = 0;

	}
	return;
}

// mission_ContentsNum ��Effect.cpp�œǂݍ��߂�id�ɂ��Ă�����
int ContentsNumToTexid(int mission_ContentsNum)
{
	switch (mission_ContentsNum)
	{
	case 0:
		return 26;
	case 1:
		return 27;
	case 2:
		return 28;
	default:
		break;
	}

	exit(24);
	return -1;
}
