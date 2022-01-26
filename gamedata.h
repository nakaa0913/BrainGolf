#pragma once

#include "main.h"
#include "bg.h"

// �Q�[�����ł̏o�������L�^����cpp��h
typedef struct {

	int pass_count;			// �p�X(�{�[���𔭎�)��������
	int hit_wall_count;		// �ǂɂԂ�������
	int game_time;			// �Q�[���X�^�[�g���Ă���̎���
	int warp_count;			// ���[�v���g������
	int acc_count;			// �����ł��g������
	int switch_count;		// �����������g������
	int break_floor_count;		// ����䂩���g������

	// �ق��ɂ����낢�날��Ƃ�����


}GAMEDATA;


void InitGamedata();
void UninitGamedata();
void UpdateGamedata();

GAMEDATA* GetGamedata();