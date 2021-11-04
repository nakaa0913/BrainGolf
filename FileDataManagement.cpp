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

void LoadMapdataMain(char* fileName)
{
	//// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
	//STAGEDATA* p_Stagedata = GetStagedata();

	FILE* fp; // FILE�^�\����

	// �t�@�C���ǂݍ��ނŊJ��
	fopen_s(&fp, fileName, "r");

	// �J���̂Ɏ��s�����ꍇ�̏����B�����I�������Ă���
	if (fp == NULL)
	{
		printf("%s file not open!\n", fileName);
		exit(2);		// �t�@�C�����J�����肷��Ƃ��ɏo���G���[��(2)
		return;
	}

	char loadchar[4] = "";				// �ǂݍ��܂ꂽ������B�ǂݍ��ނ��тɏ㏑������Ă���B����̏ꍇ1����(���p)��������Ȃ�
	char now_strings[256] = "";			// �ǂݍ���ł������������A�������Ă���B
	int pattern = PATTERN_NULL;			// �ǂݍ��񂾕����񂩂�A������ǂݍ���ł��邩�𔻕ʂ��邽�߂̂��́B

	while (pattern == PATTERN_NULL)
	{
		// �t�@�C����1�������ǂݍ���	fscanf�͕Ԃ�l�Ƃ��ēǂݍ��񂾐�(%s�Ƃ�%d�̐�)��Ԃ����A����͖�������̂�(void)������
		(void)fscanf(fp, "%1s", loadchar);

		// �������q���Ă���
		strcat(now_strings, loadchar);


		// ���蕶���񂪗����炻�̕�����ɉ������p�^�[���ɕ�����Ă����B

		// strstr �͕�����@�̒��ɇA�����邩������(��������)�ł���B�߂�l�́A����:�@�ōŏ��ɏo�������A�ւ̃|�C���^�B���s:NULL
		// �悤�����NULL�łȂ���ΐ������Ă���B
		// MapdataStart �̏ꍇ�}�b�v�f�[�^�̓ǂݍ��݂��n�܂�
		if (strstr(now_strings, "MapdataStart") != NULL)
		{
			pattern = PATTERN_MAP;

			// now_strings������������
			strcpy(now_strings, "");
		}
		// PlayerdataStart �̏ꍇ�v���C���[���ǂ��ɔz�u����Ă��邩�ƁA�ǂ�ȓ��������邩�̓ǂݍ��݂��n�܂�
		if (strstr(now_strings, "PlayerdataStart") != NULL)
		{
			pattern = PATTERN_PLAYER;

			// now_strings������������
			strcpy(now_strings, "");
		}
		// PlayerdataStart �̏ꍇ�v���C���[���ǂ��ɔz�u����Ă��邩�ƁA�ǂ�ȓ��������邩�̓ǂݍ��݂��n�܂�
		if (strstr(now_strings, "EndLoadFile") != NULL)
		{
			pattern = PATTERN_END;

			// now_strings������������
			strcpy(now_strings, "");
		}


		// �p�^�[���ɉ���������

		if (pattern == PATTERN_MAP)
		{
			pattern = LoadMapdata(fp);			// �֐����I���������߂�l��PATTERN_NULL�����炤
		}

		if (pattern == PATTERN_PLAYER)
		{
			// pattern = LoadMapdata(fp);
		}



		// 50�����ȏ�̕�����ɂȂ��Ă��܂�����G���[�Ƃ݂Ȃ������I��������
		if (strlen(now_strings) > 50)
		{
			fclose(fp); // �t�@�C�������
			exit(5);
		}
	}

	// �I���̏���
	fclose(fp); // �t�@�C�������
	return;
}


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





// // fgetc(1��������) + sscanf
//void LoadMapdata(char* fileName)
//{
//	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE�^�\����
//	int max_line = 20;			// �ǂݍ��ރt�@�C���̃f�[�^�̍s��
//	int mapdata_max = MAP_X * MAP_Y;		// �ǂݍ��ރ}�b�v�f�[�^�̐�
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
//	int tessss = 0;
//
//	int strnum = 0;	// ������̐�
//	int i = 0;		// y
//	int j = 0;		// x
//	//char getc = 'a';
//	//char loadchar[1] = "";		// 64�o�C�g�܂ł̕��������邱�Ƃ��ł��锠
//	char loadchar[1] = "";		// 64�o�C�g�܂ł̕��������邱�Ƃ��ł��锠
//	//char *p_loadchar;		// 64�o�C�g�܂ł̕��������邱�Ƃ��ł��锠
//	//p_loadchar = &loadchar;		// �|�C���^�[�ŃA�h���X�����Ă���
//	char now_string[256] = "";		// 64�o�C�g�܂ł̕��������邱�Ƃ��ł��锠
//
//	// fgetc ��1���������ǂݍ���
//	// 1�����ǂݍ��݂� fgetc �u, �v���u���s�v���uEOF�v������܂ŌJ��Ԃ�
//	while (1)
//	{
//		loadchar[0] = fgetc(fp);
//
//		//p_loadchar = &loadchar;
//		// 
//		// �J���}�������玟�̕����̌�����
//		if (loadchar[0] == ',')
//			j++;
//
//		strcat(now_string, loadchar);
//
//
//		int cmp = 0;
//		cmp = strcmp(now_string, "1");
//		//{
//		//	tessss++;
//		//}
//
//
//
//		//// ���s�����������玟�̍s�̏�����
//		//if (loadchar == '\n')
//		//{
//		//	i++;
//		//	j = 0;
//		//}
//
//		//// EOF��������u���C�N������
//		//if (loadchar == EOF)
//		//	break;
//
//		//// ����(%c)�̐�������l(%d)�̐����֕ϊ�
//		// int mapdata = charToint(loadchar);
//
//
//	 //  // ��肭�����Ă�ꍇ�͌��݂̃X�e�[�W�f�[�^�̍X�V���s���B
//		//p_Stagedata->maparray[i][j] = mapdata;
//		i++;
//		int aaaaa = 0;
//
//	}
//
//	fclose(fp); // �t�@�C�������
//
//	return;
//}




//// fgets(1�s����) + sscanf
//void LoadMapdata(char* fileName)
//{
//	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE�^�\����
//	char max_bite[256];			// 1�s�̍ő啶����(�o�C�g��)
//	int max_line = 20;			// �ǂݍ��ރt�@�C���̃f�[�^�̍s��
//	//int x[14]{};					// 1�s�ɂ���A�ǂݍ��ށA�f�[�^�̐�
//	char x[14][length]{};					// 1�s�ɂ���A�ǂݍ��ށA�f�[�^�̐�
//
//	// �t�@�C���ǂݍ��ނŊJ��
//	//fp = fopen(fileName, "r");
//	fopen_s(&fp, fileName, "r");
//
//	// �J���̂Ɏ��s�����ꍇ�̏����B�����I�������Ă���
//	if (fp == NULL)
//	{
//		printf("%s file not open!\n", fileName);
//		exit(2);		// �t�@�C�����J�����肷��Ƃ��ɏo���G���[��(2)
//		return;
//	}
//
//	int loadnum = 0;
//
//	int i = 0;
//	//while (loadnum = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d, ", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]) != EOF)
//	while (loadnum = fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,], ", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]) != EOF)
//	{
//
//
//
		//// ����(%c)�̐�������l(%d)�̐����֕ϊ�
		//for (int j = 0; j < 14; j++)
		//{
		//	int len = strlen(x[j]);
		//	if (len == 1)
		//	{
		//		int mapdata = charToint(x[j][0]);
		//		p_Stagedata->maparray[i][j] = mapdata;
		//	}
		//	if (len == 2)
		//	{
		//		int mapdata = 10 * charToint(x[j][0]) + charToint(x[j][1]);
		//		p_Stagedata->maparray[i][j] = mapdata;
		//		int aaada = 0;
		//	}
		//	if (len == 3)
		//	{
		//		int mapdata = 100 * charToint(x[j][0]) + 10 * charToint(x[j][1]) + charToint(x[j][2]);
		//		p_Stagedata->maparray[i][j] = mapdata;
		//	}
		//}
//
//		// ���̃G���[�����̂��߂Ɉ�x����������B
//		for (int j = 0; j < 14; j++)
//		{
//			x[j][0] = 'f';
//		}
//
//		// ���̍s�֐i�ށB
//		i++;
//
//		// �\��̍ő�s�ȏ�ɂȂ낤�Ƃ�����u���C�N����
//		if (i >= max_line)
//			break;
//
//	}
//
//	int sadadad = 1;
//	fclose(fp); // �t�@�C�������
//
//	return;
//}



// fgetc��1�������ǂ����Ƃ�����"1�����,1�����"�ƂȂ��Ă��܂��̂ł�߂�����������Ȃ�
// fscanf(�t�H�[�}�b�g�w��)���g����1��������	"%1s"	�Ƃ��邱�Ƃ�1�������ǂ߂�B
// ���s����,���p�󔒓��̓X�L�b�v�����B�S�p�X�y�[�X���͓ǂݍ��߂Ȃ������Ƃ���"�J"�݂����ȕ����œǂ܂�Ă��܂����疳������悤�ɏ����B
// �e�L�X�g�̏I��肷����ǂ߂��A�Ŋ��̕�����ǂݍ��񂾏�ԂŎ~�܂��Ă��܂��̂ł���̑΍���G���[�ŏ����Ă����B
// �S�p�����͑S�Ďg���Ȃ��B�G���[�ɂȂ�̂Ő�Ύg���Ă͂����Ȃ��B�������͂���𖳎����鏈���������B
//void LoadMapdata(char* fileName)
//{
//	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE�^�\����
//
//	// �t�@�C���ǂݍ��ނŊJ��
//	fopen_s(&fp, fileName, "r");
//
//	// �J���̂Ɏ��s�����ꍇ�̏����B�����I�������Ă���
//	if (fp == NULL)
//	{
//		printf("%s file not open!\n", fileName);
//		exit(2);		// �t�@�C�����J�����肷��Ƃ��ɏo���G���[��(2)
//		return;
//	}
//
//	char loadchar[4] = "";
//	char now_strings[256] = "";
//	char decision_strings[256] = "";
//	bool decision = false;
//
//	int x = 0;
//	int y = 0;
//	while (1)
//	{
//		// �t�@�C����1�������ǂݍ���	fscanf�͕Ԃ�l�Ƃ��ēǂݍ��񂾐�(%s�Ƃ�%d�̐�)��Ԃ����A����͖�������̂�(void)������
//		(void)fscanf(fp,"%1s", loadchar);
//
//		// �J���}�������當������m�肳���Ď��̕������		// strcmp�͔�r���ē�������0��Ԃ��B
//		if (strcmp(loadchar, ",") == 0)
//		{
//			// �m�肵��������𐔎��ɕϊ����}�b�v�f�[�^�ɔ��f�����鏈��
//			applyMapArray(x, y, now_strings);
//
//			// now_strings������������
//			strcpy(now_strings, "");
//
//			// ���̕�����
//			x++;
//			// ���̍s��		x���}�b�v�̉������܂ŗ����玟��y+1�̂Ƃ����
//			if (x == MAP_X)
//			{
//				y++;
//				x = 0;
//				// �}�b�v�z�񕪕�����ǂݏI�������X�̃��[�v�𔲂��o��
//				if (y == MAP_Y)
//					break;
//			}
//		}
//		else
//		{
//			// �J���}�łȂ���Ε������q���Ă���
//			strcat(now_strings, loadchar);
//		}
//
//
//		// 50�����ȏ�̕�����ɂȂ��Ă��܂�����G���[�Ƃ݂Ȃ������I��������
//		if (strlen(now_strings) > 50)
//		{
//			exit(5);
//		}
//
//
//	}
//
//
//	fclose(fp); // �t�@�C�������
//
//	return;
//}


int LoadMapdata(FILE* fp)
{
	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
	STAGEDATA* p_Stagedata = GetStagedata();

	char loadchar[4] = "";
	char now_strings[256] = "";
	char decision_strings[256] = "";
	bool decision = false;

	int x = 0;
	int y = 0;
	while (1)
	{
		// �t�@�C����1�������ǂݍ���	fscanf�͕Ԃ�l�Ƃ��ēǂݍ��񂾐�(%s�Ƃ�%d�̐�)��Ԃ����A����͖�������̂�(void)������
		(void)fscanf(fp, "%1s", loadchar);

		// �J���}�������當������m�肳���Ď��̕������		// strcmp�͔�r���ē�������0��Ԃ��B
		if (strcmp(loadchar, ",") == 0)
		{
			// �m�肵��������𐔎��ɕϊ����}�b�v�f�[�^�ɔ��f�����鏈��
			applyMapArray(x, y, now_strings);

			// now_strings������������
			strcpy(now_strings, "");

			// ���̕�����
			x++;
			// ���̍s��		x���}�b�v�̉������܂ŗ����玟��y+1�̂Ƃ����
			if (x == MAP_X)
			{
				y++;
				x = 0;
				// �}�b�v�z�񕪕�����ǂݏI�������I���Ƃ݂Ȃ���NULL��Ԃ�
				if (y == MAP_Y)
				{
					return PATTERN_NULL;
				}
			}
		}
		else
		{
			// �J���}�łȂ���Ε������q���Ă���
			strcat(now_strings, loadchar);
		}

		// PlayerdataEND ���������ꍇ�����͏I���Ƃ݂Ȃ���NULL��Ԃ�
		if (strstr(now_strings, "PlayerdataEnd") != NULL)
		{
			// now_strings������������
			strcpy(now_strings, "");

			return PATTERN_NULL;
		}

		// 50�����ȏ�̕�����ɂȂ��Ă��܂�����G���[�Ƃ݂Ȃ������I��������
		if (strlen(now_strings) > 50)
		{
			int aaaaa = 5;
			//exit(5);
		}


	}



	return PATTERN_NULL;
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


void applyMapArray(int x, int y, char strings[])
{
	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
	STAGEDATA* p_Stagedata = GetStagedata();

	// �����񂪉����������ׁA�������ɉ����Đ����ɕϊ������Ƃ��̌�����ς���
	int len = strlen(strings);
	if (len == 1)
	{
		int mapdata = charToint(strings[0]);
		p_Stagedata->maparray[y][x] = mapdata;
		int fassa = 4;
	}
	if (len == 2)
	{
		int mapdata = 10 * charToint(strings[0]) + charToint(strings[1]);
		p_Stagedata->maparray[y][x] = mapdata;
		int aaada = 0;
	}
	if (len == 3)
	{
		int mapdata = 100 * charToint(strings[0]) + 10 * charToint(strings[1]) + charToint(strings[2]);
		p_Stagedata->maparray[y][x] = mapdata;
	}

	return;
}


