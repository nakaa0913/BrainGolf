#pragma once

#include "main.h"
#include "bg.h"

// �Q�[�����ł̏o�������L�^����cpp��h
typedef struct {

	int pass_count;			// �p�X(�{�[���𔭎�)��������
	int hit_wall_count;		// �ǂɂԂ�������
	int game_time;			// �Q�[���X�^�[�g���Ă���̎���

	// �ق��ɂ����낢�날��Ƃ�����


}GAMEDATA;


void InitGamedata();
void UninitGamedata();
void UpdateGamedata();

GAMEDATA* GetGamedata();