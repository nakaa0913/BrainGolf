#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include "FileDataManagement.h"
#include "stagedata.h"

#define	length (3)


// fgets(1�s����) + sscanf
//void LoadMapdata(char* fileName)
//{
//	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
//	STAGEDATA *p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE�^�\����
//	char max_bite[256];			// 1�s�̍ő啶����(�o�C�g��)
//	int max_line = 20;			// �ǂݍ��ރt�@�C���̃f�[�^�̍s��
//	char x[14]{};					// 1�s�ɂ���A�ǂݍ��ށA�f�[�^�̐�
//
//	// �t�@�C���ǂݍ��ނŊJ��
//	fp = fopen(fileName, "r");
//
//	// �J���̂Ɏ��s�����ꍇ�̏����B�����I�������Ă���
//	if (fp == NULL) 
//	{
//		printf("%s file not open!\n", fileName);
//		exit(2);		// �t�@�C�����J�����肷��Ƃ��ɏo���G���[��(2)
//		return;
//	}
//
//
//	int i = 0;
//	while (fgets(max_bite, max_line, fp) != NULL)
//	{
//		int loadnum = 0;
//		// sscanf�͖߂�l�Ƃ��ēǂݎ��������Ԃ����K�v�Ȃ��̂őO��(void)��t���Ă�����ƃG���[���o�Ȃ��Ȃ�B
//		//loadnum = sscanf(max_bite, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]);
//		loadnum = sscanf(max_bite, "%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]);
//
//		int asasdafggg = 4;
//
//		 // �ǂݎ��������14�łȂ��ꍇ�G���[�Ƃ���
//		//if (loadnum != 14)
//		//{
//		//	exit(3);			// �ǂݎ�����������������̂ŃG���[
//		//}
//
//		// ��肭�����Ă�ꍇ�͌��݂̃X�e�[�W�f�[�^�̍X�V���s���B
//		for (int j = 0; j < 14; j++)
//		{
//			p_Stagedata->maparray[i][j] = x[j];
//		}
//
//		// ���̍s�֐i�ށB
//		i++;
//	}
//
//	fclose(fp); // �t�@�C�������
//
//	return;
//}





 // fgetc(1��������) + sscanf
//void LoadMapdata(char* fileName)
//{
//	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE�^�\����
//	int max_line = 20;			// �ǂݍ��ރt�@�C���̃f�[�^�̍s��
//
//
//	// �t�@�C���ǂݍ��ނŊJ��
//	fp = fopen(fileName, "r");
//
//	// �J���̂Ɏ��s�����ꍇ�̏����B�����I�������Ă���
//	if (fp == NULL)
//	{
//		printf("%s file not open!\n", fileName);
//		exit(2);		// �t�@�C�����J�����肷��Ƃ��ɏo���G���[��(2)
//		return;
//	}
//
//
//	int i = 0;		// y
//	int j = 0;		// x
//	//char getc = 'a';
//
//	// fgetc ��1���������ǂݍ���
//	// 1�����ǂݍ��݂� fgetc �u, �v���u���s�v���uEOF�v������܂ŌJ��Ԃ�
//	while (char getc = fgetc(fp) != NULL)
//	{
//
//		// ���s�����������玟�̍s�̏�����
//		if (getc == '\n')
//		{
//			i++;
//			j = 0;
//		}
//		// �J���}�������玟�̕����̌�����
//		if (getc == ',')
//			j++;
//
//		// EOF��������u���C�N������
//		if (getc == EOF)
//			break;
//
//		// �ǂݍ��݂����ő�s���܂ŗ�����u���C�N(�������͏����̕ω���������Ƃ�)
//		if (i == max_line)
//			break;
//
//		// ����(%c)�̐�������l(%d)�̐����֕ϊ�
//		 int mapdata = charToint(getc);
//
//
//	   // ��肭�����Ă�ꍇ�͌��݂̃X�e�[�W�f�[�^�̍X�V���s���B
//		p_Stagedata->maparray[i][j] = mapdata;
//		int aaaaa = 0;
//
//	}
//
//	fclose(fp); // �t�@�C�������
//
//	return;
//}




// fgets(1�s����) + sscanf
void LoadMapdata(char* fileName)
{
	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
	STAGEDATA* p_Stagedata = GetStagedata();

	FILE* fp; // FILE�^�\����
	char max_bite[256];			// 1�s�̍ő啶����(�o�C�g��)
	int max_line = 20;			// �ǂݍ��ރt�@�C���̃f�[�^�̍s��
	//int x[14]{};					// 1�s�ɂ���A�ǂݍ��ށA�f�[�^�̐�
	char x[14][length]{};					// 1�s�ɂ���A�ǂݍ��ށA�f�[�^�̐�

	// �t�@�C���ǂݍ��ނŊJ��
	//fp = fopen(fileName, "r");
	fopen_s(&fp, fileName, "r");

	// �J���̂Ɏ��s�����ꍇ�̏����B�����I�������Ă���
	if (fp == NULL)
	{
		printf("%s file not open!\n", fileName);
		exit(2);		// �t�@�C�����J�����肷��Ƃ��ɏo���G���[��(2)
		return;
	}

	int loadnum = 0;

	int i = 0;
	//while (loadnum = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d, ", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]) != EOF)
	while (loadnum = fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,], ", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]) != EOF)
	{



		// ����(%c)�̐�������l(%d)�̐����֕ϊ�
		for (int j = 0; j < 14; j++)
		{
			int len = strlen(x[j]);
			if (len == 1)
			{
				int mapdata = charToint(x[j][0]);
				p_Stagedata->maparray[i][j] = mapdata;
			}
			if (len == 2)
			{
				int mapdata = 10 * charToint(x[j][0]) + charToint(x[j][1]);
				p_Stagedata->maparray[i][j] = mapdata;
				int aaada = 0;
			}
			if (len == 3)
			{
				int mapdata = 100 * charToint(x[j][0]) + 10 * charToint(x[j][1]) + charToint(x[j][2]);
				p_Stagedata->maparray[i][j] = mapdata;
			}
		}

		// ���̃G���[�����̂��߂Ɉ�x����������B
		for (int j = 0; j < 14; j++)
		{
			x[j][0] = 'f';
		}

		// ���̍s�֐i�ށB
		i++;

		// �\��̍ő�s�ȏ�ɂȂ낤�Ƃ�����u���C�N����
		if (i >= max_line)
			break;

	}

	int sadadad = 1;
	fclose(fp); // �t�@�C�������

	return;
}



// char�^�̐���(1���̂�)����int�^�̐�����
int charToint(char c) 
{
	switch (c) 
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: 
		// �������}�b�v�̏������ɂȂ��Ă��Ȃ��ď\���Ȑ�(14)���ǂݍ��܂�Ȃ������ꍇ��ւ�ɕ��������ꍞ��ł����ꍇ
		exit(3);			// �����I���B�G���[3
		return 0;
	}
}

// char�^�̐���(1���̂�)����int�^�̐�����
//int shortToint(char c)
//{
//	switch (c)
//	{
//	case "0": return 0;
//	case '1': return 1;
//	case '2': return 2;
//	case '3': return 3;
//	case '4': return 4;
//	case '5': return 5;
//	case '6': return 6;
//	case '7': return 7;
//	case '8': return 8;
//	case '9': return 9;
//	default: 
		// �������}�b�v�̏������ɂȂ��Ă��Ȃ��ď\���Ȑ�(14)���ǂݍ��܂�Ȃ������ꍇ��ւ�ɕ��������ꍞ��ł����ꍇ
	//exit(3);			// �����I���B�G���[3
	//return 0;
//	}
//}





