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
#include "stageselect.h"
#include "placement.h"

MISSION g_Mission;

void InitMission()
{
	g_Mission.mission_background_EffectArray = -1;
	for (int i = 0; i < MAX_MISSION; i++)
	{
		g_Mission.mission_ContentsNum_EffectArray[i] = -1;
		for (int j = 0; j < MAX_DIGIT; j++)
		{
			g_Mission.mission_JudgeNum_EffectArray[i][j] = -1;
		}

		g_Mission.mission_star_EffectArray[i] = -1;
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

	// �܂����l�z�u���Ă邩�����炤
	int PlacementNum = PlacementPlayerNum();

	switch (ContentsNum)
	{
	case 0:		// 0:�Z�p�X�ȓ��I
		if (p_Gamedata.pass_count <= JudgeNum)
			return true;
		else
			return false;
	case 1:		// 1:�Z�l�z�u�ȓ��I
		if (PlacementNum <= JudgeNum)
			return true;
		else
			return false;
	case 2:		// 2:�Z�b�ȓ��I
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 3:		// 3:�����Ŏg���ăN���A(1��ȏ�g���ăN���A)
		if (p_Gamedata.acc_count >= 1)
			return true;
		else
			return false;
	case 4:		// 4:���[�v���g���ăN���A(1��ȏ�g���ăN���A)
		if (p_Gamedata.warp_count >= 1)
			return true;
		else
			return false;
	case 5:		// 5:�X�C�b�`���g���ăN���A(1��ȏ�g���ăN���A)
		if (p_Gamedata.switch_count >= 1)
			return true;
		else
			return false;
	case 6:		// 6:�������炸�ɃN���A(0��ȉ��ŃN���A)
		if (p_Gamedata.break_floor_count <= 0)
			return true;
		else
			return false;
	case 7:		// 7:�ǂɁZ��ȏ㓖�ĂĂ���N���A(�g��Ȃ�����摜�͂���Ȃ�)
		if (p_Gamedata.hit_wall_count >= JudgeNum)
			return true;
		else
			return false;
	case 8:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 9:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 10:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 11:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 12:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 13:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 14:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 15:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 16:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 17:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 18:		// JudgeNum�b�ȓ��ŃN���A
		if (p_Gamedata.game_time <= JudgeNum)
			return true;
		else
			return false;
	case 19:		// JudgeNum�b�ȓ��ŃN���A
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

	//int stagenum_now = GetNowChoiceStageNum();			// ���݂̃X�e�[�W�����炤1~20

	int mission_ContentsNum = p_Stagedata->mission_ContentsNum[missionnum];
	int mission_JudgeNum = p_Stagedata->mission_JudgeNum[missionnum];

	judge = ClearorFailure(p_Stagedata->mission_ContentsNum[missionnum], p_Stagedata->mission_JudgeNum[missionnum]);

	return judge;
}


// 999�\���Ȃ̂�1�񂾂��\�����Ă����Ă�
void DrawMissionStageSelect()
{
	SAVEDATA* p_Savedata = GetSavedata();

	// �X�e�[�W�f�[�^����~�b�V�������e�Ȃǂ�ǂݎ��
	STAGEDATA* p_Stagedata = GetStagedata();

	float mozisizebairitu = 0.7f;

	float size_x = 768.0f;
	float size_y = 128.0f;

	float background_size_y = size_y * 3;

	float interval_y = size_y * mozisizebairitu;

	float base_pos1_x = SCREEN_WIDTH / 2;
	float base_pos1_y = SCREEN_HEIGHT + background_size_y;

	float base_pos2_x = SCREEN_WIDTH / 2;
	float base_pos2_y = SCREEN_HEIGHT / 2;

	float BGbase_pos1_x = SCREEN_WIDTH / 2;
	float BGbase_pos1_y = SCREEN_HEIGHT + background_size_y;

	float BGbase_pos2_x = SCREEN_WIDTH / 2;
	float BGbase_pos2_y = SCREEN_HEIGHT / 2;

	float star_pos1_x = 0.0f;
	float star_pos2_x= 0.0f;

	float star_gap = 420.0f * mozisizebairitu;

	int move_frame = 14;

	float textGapX = 190.0f * mozisizebairitu;

	// ���݂̃X�e�[�W����E�ƍ��ǂ���Ƀ~�b�V������\�������邩
	int LeftOrRight = DisplayLeftOrRight(GetNowChoiceStageNum());

	if (LeftOrRight == 0)
	{
		BGbase_pos2_x = 0.0f + 300.0f;
		BGbase_pos2_y = 450.0f;

		BGbase_pos1_x = BGbase_pos2_x - 500.0f;
		BGbase_pos1_y = BGbase_pos2_y;

		base_pos2_x = BGbase_pos2_x + textGapX;
		base_pos2_y = BGbase_pos2_y;

		base_pos1_x = BGbase_pos1_x + textGapX;
		base_pos1_y = BGbase_pos1_y;
	}
	else
	{
		BGbase_pos2_x = SCREEN_WIDTH - 300.0f;
		BGbase_pos2_y = 450.0f;

		BGbase_pos1_x = BGbase_pos2_x + 500.0f;
		BGbase_pos1_y = BGbase_pos2_y;

		base_pos2_x = BGbase_pos2_x + textGapX;
		base_pos2_y = BGbase_pos2_y;

		base_pos1_x = BGbase_pos1_x + textGapX;
		base_pos1_y = BGbase_pos1_y;
	}

	// �����̐ݒ�
	float interval_magnification = 0.38f;	// �����\���̊Ԋu�̔{��

	float num_size_x = 60.0f;
	float num_size_y = 60.0f;


	// �~�b�V�����̔w�i��\��	Effect�ł�id��25		�~�b�V�����̒��g��\����3�����Ă����̐^�񒆂ɗ���悤�ɔz�u����->i�̂Ƃ���1�ɂ������OK
	int Background_EffectArray =
		SetEffect(86, D3DXVECTOR2(BGbase_pos1_x, BGbase_pos1_y + interval_y * 1), D3DXVECTOR2(BGbase_pos2_x, BGbase_pos2_y + interval_y * 1), 1,
			D3DXVECTOR2(537.6f, background_size_y), D3DXVECTOR2(537.6f, background_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, move_frame,
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
				D3DXVECTOR2(size_x * mozisizebairitu, size_y * mozisizebairitu), D3DXVECTOR2(size_x, size_y), 0,
				0.0f, 1.0f, 0, 999, 0, move_frame,
				0.0f, 0.0f, 0);

		// �~�b�V�����̃e�N�X�`��ID���琔���̍��W���ǂꂾ���^�񒆂��炸��Ă邩���Ƃ��Ă���(x�̂�)
		float number_gap_x = MissionTexIdToNumXGAP(Content_Texid) * mozisizebairitu;

		// �����̕`��		�~�b�V�����̔ԍ����Ƃɐ�����`���ꏊ�͌��܂��Ă�Ǝv���̂ŁA�����switch���Ŕ��ʂł���Ɗy
		int Number_EffectArray[2] = { 0,0 };
		int* p_Number_EffectArray = Number_EffectArray;
		SetEffectNumber(p_Stagedata->mission_JudgeNum[i], p_Number_EffectArray, D3DXVECTOR2(base_pos1_x - number_gap_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - number_gap_x, base_pos2_y + interval_y * i), 1,
			D3DXVECTOR2(num_size_x * mozisizebairitu, num_size_y * mozisizebairitu), D3DXVECTOR2(num_size_x, num_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, move_frame,
			0.0f, 0.0f, 0, false, interval_magnification);

		// �G�t�F�N�g���������ꂽ�ꏊ�̔ԍ��̕ۑ�
		g_Mission.mission_ContentsNum_EffectArray[i] = Content_EffectArray;
		g_Mission.mission_JudgeNum_EffectArray[i][0] = Number_EffectArray[0];
		g_Mission.mission_JudgeNum_EffectArray[i][1] = Number_EffectArray[1];		// �A�Ԃ̕ۑ�


		// �~�b�V�������N���A���Ă���Ȃ�\������
		if (p_Savedata[GetNowChoiceStageNum() - 1].mission_clear[i] == 1)
		{
			//��
			g_Mission.mission_star_EffectArray[i] =
				SetEffect(83 + i, D3DXVECTOR2(base_pos1_x - star_gap, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - star_gap, base_pos2_y + interval_y * i), 1,
					D3DXVECTOR2(90.0f * mozisizebairitu, 90.0f * mozisizebairitu), D3DXVECTOR2(80.0f, 80.0f), 0,
					0.0f, 1.0f, 0, 999, 0, move_frame,
					0.0f, 0.0f, 0);
		}
		else
		{
			//��(����)
			g_Mission.mission_star_EffectArray[i] =
				SetEffect(82, D3DXVECTOR2(base_pos1_x - star_gap, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - star_gap, base_pos2_y + interval_y * i), 1,
					D3DXVECTOR2(90.0f * mozisizebairitu, 90.0f * mozisizebairitu), D3DXVECTOR2(80.0f, 80.0f), 0,
					0.0f, 1.0f, 0, 999, 0, move_frame,
					0.0f, 0.0f, 0);
		}


	}
	return;
}

void DeleteMissionStageSelect()
{
	EffectBreak(g_Mission.mission_background_EffectArray);

	for (int i = 0; i < MAX_MISSION; i++)
	{
		EffectBreak(g_Mission.mission_ContentsNum_EffectArray[i]);
		EffectBreak(g_Mission.mission_star_EffectArray[i]);
		EffectBreak(g_Mission.mission_JudgeNum_EffectArray[i][0], g_Mission.mission_JudgeNum_EffectArray[i][1]);	// ��2�����ŘA�Ԃ̏���

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
	case 3:
		return 29;
	case 4:
		return 30;
	case 5:
		return 31;
	case 6:
		return 32;
	case 7:
		return 33;
	case 8:
		return 34;
	case 9:
		return 35;
	case 10:
		return 36;
	case 11:
		return 37;
	case 12:
		return 38;
	case 13:
		return 39;
	case 14:
		return 40;
	case 15:
		return 41;
	case 16:
		return 42;
	case 17:
		return 43;
	case 18:
		return 44;
	case 19:
		return 45;

	default:
		break;
	}

	exit(24);
	return -1;
}

void DrawMissionResult()
{
	SAVEDATA* p_Savedata = GetSavedata();

	// �X�e�[�W�f�[�^����~�b�V�������e�Ȃǂ�ǂݎ��
	STAGEDATA* p_Stagedata = GetStagedata();

	float mozisizebairitu = 0.7f;

	float size_x = 768.0f;
	float size_y = 128.0f;

	float background_size_y = size_y * 3;

	float interval_y = size_y * mozisizebairitu;

	float base_pos1_x = SCREEN_WIDTH / 2;
	float base_pos1_y = SCREEN_HEIGHT + background_size_y;

	float base_pos2_x = SCREEN_WIDTH / 2;
	float base_pos2_y = SCREEN_HEIGHT / 2;

	float BGbase_pos1_x = SCREEN_WIDTH / 2;
	float BGbase_pos1_y = SCREEN_HEIGHT + background_size_y;

	float BGbase_pos2_x = SCREEN_WIDTH / 2;
	float BGbase_pos2_y = SCREEN_HEIGHT / 2;

	float star_pos1_x = 0.0f;
	float star_pos2_x= 0.0f;

	float star_gap = 420.0f * mozisizebairitu;

	int move_frame = 14;

	float textGapX = 190.0f * mozisizebairitu;

	// ���݂̃X�e�[�W����E�ƍ��ǂ���Ƀ~�b�V������\�������邩
	int LeftOrRight = DisplayLeftOrRight(GetNowChoiceStageNum());

	if (LeftOrRight == 0)
	{
		BGbase_pos2_x = 0.0f + 300.0f;
		BGbase_pos2_y = 450.0f;

		BGbase_pos1_x = BGbase_pos2_x - 500.0f;
		BGbase_pos1_y = BGbase_pos2_y;

		base_pos2_x = BGbase_pos2_x + textGapX;
		base_pos2_y = BGbase_pos2_y;

		base_pos1_x = BGbase_pos1_x + textGapX;
		base_pos1_y = BGbase_pos1_y;
	}
	else
	{
		BGbase_pos2_x = SCREEN_WIDTH - 300.0f;
		BGbase_pos2_y = 450.0f;

		BGbase_pos1_x = BGbase_pos2_x + 500.0f;
		BGbase_pos1_y = BGbase_pos2_y;

		base_pos2_x = BGbase_pos2_x + textGapX;
		base_pos2_y = BGbase_pos2_y;

		base_pos1_x = BGbase_pos1_x + textGapX;
		base_pos1_y = BGbase_pos1_y;
	}

	// �����̐ݒ�
	float interval_magnification = 0.24f;	// �����\���̊Ԋu�̔{��

	float num_size_x = 80.0f;
	float num_size_y = 80.0f;


	// �~�b�V�����̔w�i��\��	Effect�ł�id��25		�~�b�V�����̒��g��\����3�����Ă����̐^�񒆂ɗ���悤�ɔz�u����->i�̂Ƃ���1�ɂ������OK
	int Background_EffectArray =
		SetEffect(86, D3DXVECTOR2(BGbase_pos1_x, BGbase_pos1_y + interval_y * 1), D3DXVECTOR2(BGbase_pos2_x, BGbase_pos2_y + interval_y * 1), 1,
			D3DXVECTOR2(537.6f, background_size_y), D3DXVECTOR2(537.6f, background_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, move_frame,
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
				D3DXVECTOR2(size_x * mozisizebairitu, size_y * mozisizebairitu), D3DXVECTOR2(size_x, size_y), 0,
				0.0f, 1.0f, 0, 999, 0, move_frame,
				0.0f, 0.0f, 0);

		// �~�b�V�����̃e�N�X�`��ID���琔���̍��W���ǂꂾ���^�񒆂��炸��Ă邩���Ƃ��Ă���(x�̂�)
		float number_gap_x = MissionTexIdToNumXGAP(Content_Texid) * mozisizebairitu;

		// �����̕`��		�~�b�V�����̔ԍ����Ƃɐ�����`���ꏊ�͌��܂��Ă�Ǝv���̂ŁA�����switch���Ŕ��ʂł���Ɗy
		int Number_EffectArray[2] = { 0,0 };
		int* p_Number_EffectArray = Number_EffectArray;
		SetEffectNumber(p_Stagedata->mission_JudgeNum[i], p_Number_EffectArray, D3DXVECTOR2(base_pos1_x - number_gap_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - number_gap_x, base_pos2_y + interval_y * i), 1,
			D3DXVECTOR2(num_size_x * mozisizebairitu, num_size_y * mozisizebairitu), D3DXVECTOR2(num_size_x, num_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, move_frame,
			0.0f, 0.0f, 0, false, interval_magnification);

		// �G�t�F�N�g���������ꂽ�ꏊ�̔ԍ��̕ۑ�
		g_Mission.mission_ContentsNum_EffectArray[i] = Content_EffectArray;
		g_Mission.mission_JudgeNum_EffectArray[i][0] = Number_EffectArray[0];
		g_Mission.mission_JudgeNum_EffectArray[i][1] = Number_EffectArray[1];		// �A�Ԃ̕ۑ�


		// �~�b�V�������N���A���Ă���Ȃ�\������
		if (p_Savedata[GetNowChoiceStageNum() - 1].mission_clear[i] == 1)
		{
			//��
			g_Mission.mission_star_EffectArray[i] =
				SetEffect(83 + i, D3DXVECTOR2(base_pos1_x - star_gap, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - star_gap, base_pos2_y + interval_y * i), 1,
					D3DXVECTOR2(90.0f * mozisizebairitu, 90.0f * mozisizebairitu), D3DXVECTOR2(80.0f, 80.0f), 0,
					0.0f, 1.0f, 0, 999, 0, move_frame,
					0.0f, 0.0f, 0);
		}
		else
		{
			//��(����)
			g_Mission.mission_star_EffectArray[i] =
				SetEffect(82, D3DXVECTOR2(base_pos1_x - star_gap, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - star_gap, base_pos2_y + interval_y * i), 1,
					D3DXVECTOR2(90.0f * mozisizebairitu, 90.0f * mozisizebairitu), D3DXVECTOR2(80.0f, 80.0f), 0,
					0.0f, 1.0f, 0, 999, 0, move_frame,
					0.0f, 0.0f, 0);
		}


	}
	return;
}

void DeleteMissionResult()
{
	//EffectBreak(g_Mission.mission_background_EffectArray);

	for (int i = 0; i < MAX_MISSION; i++)
	{
		EffectBreak(g_Mission.mission_ContentsNum_EffectArray[i]);
		//EffectBreak(g_Mission.mission_star_EffectArray[i]);
		EffectBreak(g_Mission.mission_JudgeNum_EffectArray[i][0], g_Mission.mission_JudgeNum_EffectArray[i][1]);	// ��2�����ŘA�Ԃ̏���

	}
	return;
}

void DrawMissionPause()
{
	SAVEDATA* p_Savedata = GetSavedata();

	// �X�e�[�W�f�[�^����~�b�V�������e�Ȃǂ�ǂݎ��
	STAGEDATA* p_Stagedata = GetStagedata();

	float mozisizebairitu = 0.7f;

	float size_x = 768.0f;
	float size_y = 128.0f;

	float background_size_y = size_y * 3;

	float interval_y = size_y * mozisizebairitu;

	float base_pos1_x = SCREEN_WIDTH / 2;
	float base_pos1_y = SCREEN_HEIGHT + background_size_y;

	float base_pos2_x = SCREEN_WIDTH / 2;
	float base_pos2_y = SCREEN_HEIGHT / 2;

	float BGbase_pos1_x = SCREEN_WIDTH / 2;
	float BGbase_pos1_y = SCREEN_HEIGHT + background_size_y;

	float BGbase_pos2_x = SCREEN_WIDTH / 2;
	float BGbase_pos2_y = SCREEN_HEIGHT / 2;

	float star_pos1_x = 0.0f;
	float star_pos2_x = 0.0f;

	float star_gap = 420.0f * mozisizebairitu;

	int move_frame = 14;

	float textGapX = 190.0f * mozisizebairitu;

	BGbase_pos2_x = SCREEN_WIDTH / 2;
	BGbase_pos2_y = SCREEN_HEIGHT / 2 - 200.0f;

	BGbase_pos1_x = BGbase_pos2_x;
	BGbase_pos1_y = BGbase_pos2_y;

	base_pos2_x = BGbase_pos2_x + textGapX;
	base_pos2_y = BGbase_pos2_y;

	base_pos1_x = BGbase_pos1_x + textGapX;
	base_pos1_y = BGbase_pos1_y;

	// �����̐ݒ�
	float interval_magnification = 0.38f;	// �����\���̊Ԋu�̔{��

	float num_size_x = 60.0f;
	float num_size_y = 60.0f;


	// �~�b�V�����̔w�i��\��	Effect�ł�id��25		�~�b�V�����̒��g��\����3�����Ă����̐^�񒆂ɗ���悤�ɔz�u����->i�̂Ƃ���1�ɂ������OK
	int Background_EffectArray =
		SetEffect(86, D3DXVECTOR2(BGbase_pos1_x, BGbase_pos1_y + interval_y * 1), D3DXVECTOR2(BGbase_pos2_x, BGbase_pos2_y + interval_y * 1), 0,
			D3DXVECTOR2(537.6f, background_size_y), D3DXVECTOR2(537.6f, background_size_y), 0,
			0.0f, 1.0f, 0, 999, 0, move_frame,
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
			SetEffect(Content_Texid, D3DXVECTOR2(base_pos1_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x, base_pos2_y + interval_y * i), 0,
				D3DXVECTOR2(size_x * mozisizebairitu, size_y * mozisizebairitu), D3DXVECTOR2(size_x, size_y), 0,
				0.0f, 1.0f, 20, 999, 0, 1,
				0.0f, 0.0f, 0);

		// �~�b�V�����̃e�N�X�`��ID���琔���̍��W���ǂꂾ���^�񒆂��炸��Ă邩���Ƃ��Ă���(x�̂�)
		float number_gap_x = MissionTexIdToNumXGAP(Content_Texid) * mozisizebairitu;

		// �����̕`��		�~�b�V�����̔ԍ����Ƃɐ�����`���ꏊ�͌��܂��Ă�Ǝv���̂ŁA�����switch���Ŕ��ʂł���Ɗy
		int Number_EffectArray[2] = { 0,0 };
		int* p_Number_EffectArray = Number_EffectArray;
		SetEffectNumber(p_Stagedata->mission_JudgeNum[i], p_Number_EffectArray, D3DXVECTOR2(base_pos1_x - number_gap_x, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - number_gap_x, base_pos2_y + interval_y * i), 0,
			D3DXVECTOR2(num_size_x * mozisizebairitu, num_size_y * mozisizebairitu), D3DXVECTOR2(num_size_x, num_size_y), 0,
			0.0f, 1.0f, 20, 999, 0, 1,
			0.0f, 0.0f, 0, false, interval_magnification);

		// �G�t�F�N�g���������ꂽ�ꏊ�̔ԍ��̕ۑ�
		g_Mission.mission_ContentsNum_EffectArray[i] = Content_EffectArray;
		g_Mission.mission_JudgeNum_EffectArray[i][0] = Number_EffectArray[0];
		g_Mission.mission_JudgeNum_EffectArray[i][1] = Number_EffectArray[1];		// �A�Ԃ̕ۑ�


		// �~�b�V�������N���A���Ă���Ȃ�\������
		if (p_Savedata[GetNowChoiceStageNum() - 1].mission_clear[i] == 1)
		{
			//��
			g_Mission.mission_star_EffectArray[i] =
				SetEffect(83 + i, D3DXVECTOR2(base_pos1_x - star_gap, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - star_gap, base_pos2_y + interval_y * i), 1,
					D3DXVECTOR2(90.0f * mozisizebairitu, 90.0f * mozisizebairitu), D3DXVECTOR2(80.0f, 80.0f), 0,
					0.0f, 1.0f, 0, 999, 0, move_frame,
					0.0f, 0.0f, 0);
		}
		else
		{
			//��(����)
			g_Mission.mission_star_EffectArray[i] =
				SetEffect(82, D3DXVECTOR2(base_pos1_x - star_gap, base_pos1_y + interval_y * i), D3DXVECTOR2(base_pos2_x - star_gap, base_pos2_y + interval_y * i), 1,
					D3DXVECTOR2(90.0f * mozisizebairitu, 90.0f * mozisizebairitu), D3DXVECTOR2(80.0f, 80.0f), 0,
					0.0f, 1.0f, 0, 999, 0, move_frame,
					0.0f, 0.0f, 0);
		}



	}
	return;
}

void DeleteMissionPause()
{
	EffectBreak(g_Mission.mission_background_EffectArray);

	for (int i = 0; i < MAX_MISSION; i++)
	{
		EffectBreak(g_Mission.mission_ContentsNum_EffectArray[i]);
		EffectBreak(g_Mission.mission_star_EffectArray[i]);
		EffectBreak(g_Mission.mission_JudgeNum_EffectArray[i][0], g_Mission.mission_JudgeNum_EffectArray[i][1]);	// ��2�����ŘA�Ԃ̏���

	}
	return;
}

// �X�e�[�W�I���̎��A�~�b�V�����\�������E�ǂ����ɂ��邩 ����0�E��1
int DisplayLeftOrRight(int stagenum)
{
	switch (stagenum)
	{
	case 1:
		return 1;
		break;
	case 2:
		return 1;
		break;
	case 3:
		return 1;
		break;
	case 4:
		return 0;
		break;
	case 5:
		return 0;
		break;
	case 6:
		return 1;
		break;
	case 7:
		return 1;
		break;
	case 8:
		return 0;
		break;
	case 9:
		return 0;
		break;
	case 10:
		return 0;
		break;

	case 11:
		return 1;
		break;
	case 12:
		return 1;
		break;
	case 13:
		return 1;
		break;
	case 14:
		return 0;
		break;
	case 15:
		return 0;
		break;
	case 16:
		return 0;
		break;
	case 17:
		return 0;
		break;
	case 18:
		return 0;
		break;
	case 19:
		return 0;
		break;
	case 20:
		return 1;
		break;
	}
}


// �~�b�V�����̕��͂�ID���琔���̕\�����^�񒆂���ǂꂾ������Ă��邩�����߂�
float MissionTexIdToNumXGAP(int texid)
{
	switch (texid)
	{
	case 26:
		return 360;
	case 27:
		return 380;
	case 28:
		return 342.0f;
	case 29:
		return SCREEN_WIDTH*2;
	case 30:
		return SCREEN_WIDTH*2;
	case 31:
		return SCREEN_WIDTH*2;
	case 32:
		return SCREEN_WIDTH*2;
	case 33:
		return 0.0f;
	case 34:
		return 0.0f;
	case 35:
		return 0.0f;
	case 36:
		return 0.0f;
	case 37:
		return 0.0f;
	case 38:
		return 0.0f;
	case 39:
		return 0.0f;
	case 40:
		return 0.0f;
	case 41:
		return 0.0f;
	case 42:
		return 0.0f;
	case 43:
		return 0.0f;
	case 44:
		return 44;
	case 45:
		return 0.0f;

	default:
		break;
	}

	exit(24);
	return -1;
}