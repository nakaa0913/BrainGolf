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
#include "savedata.h"

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

	while (pattern != PATTERN_END)
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
		// MissiondataStart �̏ꍇ�~�b�V�����Ɋւ���ǂݍ��݂��J�n�����
		if (strstr(now_strings, "MissiondataStart") != NULL)
		{
			pattern = PATTERN_MISSION;

			// now_strings������������
			strcpy(now_strings, "");
		}


		// �t�@�C���ǂݍ��ݏI����ǂݎ��I������
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
			pattern = LoadPlayerdata(fp);
		}
		if (pattern == PATTERN_MISSION)
		{
			pattern = LoadMissiondata(fp);
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




void LoadSavedata(char* fileName)
{
	// �Z�[�u�f�[�^�ɓǂݍ���
	SAVEDATA* p_Savedata = GetSavedata();

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
	int pattern = PATTERN_SAVEDATA_NULL;			// �ǂݍ��񂾕����񂩂�A������ǂݍ���ł��邩�𔻕ʂ��邽�߂̂��́B

	int load_num = 0;					// ���ݓǂݍ���ł���ꏊ0~2:�~�b�V����,3�N���A�^�C��

	int now_load_stage = 0;

	while (pattern != PATTERN_END)
	{
		// �t�@�C����1�������ǂݍ���	fscanf�͕Ԃ�l�Ƃ��ēǂݍ��񂾐�(%s�Ƃ�%d�̐�)��Ԃ����A����͖�������̂�(void)������
		(void)fscanf(fp, "%1s", loadchar);

		// �X�e�[�W�̔ԍ���ǂݍ��ރt�F�[�Y�Ȃ�
		if (pattern == PATTERN_SAVEDATA_STAGENUM)
		{
			// �J���}��������ǂݍ��ރX�e�[�W���m�肳����
			if (strcmp(loadchar, ",") == 0)
			{
				// �e�L�X�g�t�@�C���ɂ̓X�e�[�W1~50�ŏ�����Ă���̂ŁA0~49�ɏC�����邽�߂�-1����
				now_load_stage = StringsToInt(now_strings) - 1;
				pattern = PATTERN_SAVEDATA_NULL;

				strcpy(now_strings, "");
				continue;
			}
			else
			{
				// �J���}�łȂ���Ε������q���Ă���
				strcat(now_strings, loadchar);
			}
		}

		// NULL�̃t�F�[�Y�Ȃ�(�X�e�[�W�I���ȊO�͂���)
		if (pattern == PATTERN_SAVEDATA_NULL)
		{
			// "s"��������A�ǂݍ��ރX�e�[�W������ɍX�V���A�폜���Ď��̕����̌����ցB
			if (strcmp(loadchar, "s") == 0)
			{
				pattern = PATTERN_SAVEDATA_STAGENUM;
				strcpy(now_strings, "");
				continue;
			}

			// �J���}�������當������m�肳����
			if (strcmp(loadchar, ",") == 0)
			{
				// ���݂̕����񂪃J���}�����������ꍇ�A�폜���Ď��̕����̌����ցB��������邱�Ƃɂ���āA(,1)�Ƃ��̐S�z���Ȃ��Ȃ�
				if (strcmp(now_strings, ",") == 0)
				{
					strcpy(now_strings, "");
					continue;
				}

				// �~�b�V�����Ȃ̂����ԂȂ̂�
				if (load_num < 3)
				{
					// �~�b�V�����̓ǂݍ���	0or1�ŋA���Ă���,1���N���A
					p_Savedata[now_load_stage].mission_clear[load_num] = StringsToInt(now_strings);
					strcpy(now_strings, "");
					load_num++;					// �ǂݍ��݌���+1����
				}
				else if (load_num == 3)
				{
					// ���Ԃ̓ǂ݂���
					p_Savedata[now_load_stage].clear_time = StringsToInt(now_strings);
					strcpy(now_strings, "");
					// ���ׂĂ̗v�f��ǂݍ��񂾂̂�loadnum��0�ɂ���
					load_num = 0;
				}

				continue;
			}
			else
			{
				// �J���}�łȂ���Ε������q���Ă���
				strcat(now_strings, loadchar);
			}
		}

		// �t�@�C���ǂݍ��ݏI����ǂݎ��I������
		if (strstr(now_strings, "EndLoadFile") != NULL)
		{
			pattern = PATTERN_END;

			// now_strings������������
			strcpy(now_strings, "");
		}

		// 50�����ȏ�̕�����ɂȂ��Ă��܂�����G���[�Ƃ݂Ȃ������I��������
		if (strlen(now_strings) > 50)
		{
			int dad = 0;
			fclose(fp); // �t�@�C�������
			exit(5);
		}
	}

	// �I���̏���
	fclose(fp); // �t�@�C�������
	return;
}






// �ꕔ�������������鏈�������݂��Ȃ��̂őS�Ă��㏑�����Ȃ���΂Ȃ�Ȃ�
void WriteSavedata(char* fileName)
{
	// ���݂̃Z�[�u�f�[�^��ǂݍ���
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	FILE* fp; // FILE�^�\����

	// �t�@�C���������݂ŊJ��
	fopen_s(&fp, fileName, "w");

	// �J���̂Ɏ��s�����ꍇ�̏����B�����I�������Ă���
	if (fp == NULL)
	{
		printf("%s file not open!\n", fileName);
		exit(2);		// �t�@�C�����J�����肷��Ƃ��ɏo���G���[��(2)
		return;
	}

	char bases[4] = "s";

	char stagenum[20] = "";
	char mission0char[20] = "";
	char mission1char[20] = "";
	char mission2char[20] = "";
	char cleartimechar[20] = "";

	for (int i = 0; i < MAX_STAGE; i++)
	{
		// �S�Ẵf�[�^��char�^�ɒ�������
		strcpy(stagenum, intTostrings(i + 1));
		strcpy(mission0char, intTostrings(p_Savedata[i].mission_clear[0]));
		strcpy(mission1char, intTostrings(p_Savedata[i].mission_clear[1]));
		strcpy(mission2char, intTostrings(p_Savedata[i].mission_clear[2]));
		strcpy(cleartimechar, intTostrings(p_Savedata[i].clear_time));

		// �������ޏ���
		fprintf(fp, "%s%s,%s,%s,%s,%s,\n", bases, stagenum, mission0char, mission1char, mission2char, cleartimechar);
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
			// ���݂̕����񂪃J���}�����������ꍇ�A�폜���Ď��̕����̌����ցB��������邱�Ƃɂ���āA(,1)�Ƃ��̐S�z���Ȃ��Ȃ�
			if (strcmp(now_strings, ",") == 0)
			{
				strcpy(now_strings, "");
				continue;
			}

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

		// MapdataEnd ���������ꍇ�����͏I���Ƃ݂Ȃ���NULL��Ԃ�
		if (strstr(now_strings, "MapdataEnd") != NULL)
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

int LoadPlayerdata(FILE* fp)
{
	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
	STAGEDATA* p_Stagedata = GetStagedata();

	// �\���̂�����āA���̃|�C���^���p�ӂ��Ă���
	MAPCHIP_POS_STRUCT s_mapchip_pos{};
	MAPCHIP_POS_STRUCT* p_mapchip_pos = &s_mapchip_pos;

	// �\���̂̏�����(-1)������
	for (int num = 0; num < ORDER_MAX; num++)
	{
		s_mapchip_pos.mapchip_pos_x[num] = -1;
		s_mapchip_pos.mapchip_pos_y[num] = -1;
	}

	char loadchar[4] = "";
	char now_strings[256] = "";

	int order = 0;		// �����Ă�������	�ő�ORDER_MAX(5)
	int XorY = 0;		// 0:X,1:Y	����X��Y�ǂ����̍��W�ɒl�����悤�Ƃ��Ă��邩
	float movespeed = PLAYER_MOVE_SPEED;
	int decimal_point = 0;		// �����_�̈ʒu�������牽�Ԗڂɂ��邩
	bool decision_decima = false;		// �����_�̈ʒu�����肵�����ǂ���

	int pattern = PATTERN_PLAYER_NULL;			// �ǂݍ��񂾕����񂩂�A������ǂݍ���ł��邩�𔻕ʂ��邽�߂̂��́B

	int x = 0;
	int y = 0;

	// Setplayer�ŃZ�b�g����̂́Ap�̐ݒ蒆�ɐV����p���ǂݍ��܂ꂽ���ƁA�Ŋ��I����������������2�p�^�[������B

	while (1)
	{
		// �t�@�C����1�������ǂݍ���	fscanf�͕Ԃ�l�Ƃ��ēǂݍ��񂾐�(%s�Ƃ�%d�̐�)��Ԃ����A����͖�������̂�(void)������
		(void)fscanf(fp, "%1s", loadchar);

		int fasf = 5;
		// �����𔭌�������p�^�[���ύX�Ə�����
		if (pattern == PATTERN_PLAYER_NULL)
		{
			// NULL�̏�Ԃ�p���������ꍇ(�ŏ���1���)
			if (strcmp(now_strings, "pos") == 0)
			{
				order = 0;
				XorY = 0;
				movespeed = PLAYER_MOVE_SPEED;
				decimal_point = 0;
				decision_decima = false;
				pattern = PATTERN_PLAYER_POS;
				strcpy(now_strings, "");
				continue;
			}
		}
		else
		{
			// �ݒ蒆�ɐV����pos���������ꍇ(PATTERN_PLAYER_POS�̎��ɂ������������ꍇ,��������PATTERN_PLAYER_MOVESPEED��)
			if (strcmp(now_strings, "pos") == 0)
			{
				//if (pattern == PATTERN_PLAYER_MOVESPEED)
				//	movespeed = SetMoveSpeed(decimal_point, now_strings);
				// SetPlayer�ŃZ�b�g���Ă��珉����
				SetPlayerUseFile(s_mapchip_pos, movespeed);
				// �\���̂̏�����(-1)������
				for (int num = 0; num < ORDER_MAX; num++)
				{
					s_mapchip_pos.mapchip_pos_x[num] = -1;
					s_mapchip_pos.mapchip_pos_y[num] = -1;
				}


				order = 0;
				XorY = 0;
				decimal_point = 0;
				decision_decima = false;
				movespeed = PLAYER_MOVE_SPEED;
				pattern = PATTERN_PLAYER_POS;
				strcpy(now_strings, "");
				continue;
			}
		}
		if (strcmp(now_strings, "nex") == 0)
		{
			order++;
			XorY = 0;
			// pattern = PATTERN_PLAYER_NEXTPOS;
			strcpy(now_strings, "");
			continue;
		}
		if (strcmp(now_strings, "spe") == 0)
		{
			pattern = PATTERN_PLAYER_MOVESPEED;
			strcpy(now_strings, "");
			continue;
		}

		// �J���}�������當������m�肳���Ď��̕������		// strcmp�͔�r���ē�������0��Ԃ��B
		if (strcmp(loadchar, ",") == 0)
		{
			// ���݂̕����񂪃J���}�����������ꍇ�A�폜���Ď��̕����̌����ցB��������邱�Ƃɂ���āA(,1)�Ƃ��̐S�z���Ȃ��Ȃ�
			if (strcmp(now_strings, ",") == 0)
			{
				strcpy(now_strings, "");
				continue;
			}

			// �m�肵��������𐔎��ɕϊ����f�[�^�ɔ��f�����鏈��
			if (pattern == PATTERN_PLAYER_POS)
			{
				// �\���̂̒��g���Z�b�g(SetPlayer�œn�����߂̃f�[�^�̕ۑ��ƍX�V)
				SetMAPCHIP_POS_STRUCT(p_mapchip_pos, now_strings, order, XorY);
				// now_strings������������
				strcpy(now_strings, "");

				// X�̐ݒ肪�I������玟��Y�̐ݒ�Ȃ̂�+1���Ă���
				XorY++;
				int sffd = 4;
			}
			// if (pattern == PATTERN_PLAYER_MOVESPEED) �͂����ł͉������Ȃ��̂ŏ����Ȃ�

		}
		else
		{
			// �J���}����Ȃ��ꍇ�������Ȃ���O�ɁAPATTERN_PLAYER_MOVESPEED�̏������̏ꍇ�̏������s��
			if (pattern == PATTERN_PLAYER_MOVESPEED)
			{
				if (strcmp(loadchar, ".") == 0)
				{
					// .�̏ꍇ�A.�𖳎����ē��͂𑱂���B.�������牽�ڂɂ������������ۑ����Ă���
					decision_decima = true;
					continue;

				}
				else if (strcmpNumber(loadchar) != 0)
				{
					// ��������Ȃ������������ꍇ�̏���
					//if (pattern == PATTERN_PLAYER_MOVESPEED)
				//	movespeed = SetMoveSpeed(decimal_point, now_strings);
				// SetPlayer�ŃZ�b�g���Ă��珉����
					SetPlayerUseFile(s_mapchip_pos, movespeed);
					// �\���̂̏�����(-1)������
					for (int num = 0; num < ORDER_MAX; num++)
					{
						s_mapchip_pos.mapchip_pos_x[num] = -1;
						s_mapchip_pos.mapchip_pos_y[num] = -1;
					}
					// now_strings������������
					strcpy(now_strings, "");
					pattern = PATTERN_PLAYER_NULL;
				}
				else if (decision_decima == false)
					decimal_point++;
			}


			// �J���}�łȂ���Ε������q���Ă����Bp,n,s�̏ꍇ�����܂ł��ǂ蒅���Ȃ��̂ő��v�B��������"."�̏ꍇ�������ɂ͗��Ȃ�
			strcat(now_strings, loadchar);
		}

		// PlayerdataEND ���������ꍇ�����͏I���Ƃ݂Ȃ���NULL��Ԃ�
		if (strstr(now_strings, "PlayerdataEnd") != NULL)
		{
			// PlayerdataEnd �܂œǂݍ���ł��܂��Ă��ԂȂ̂ŁA���������J�b�g���Ă�����
			int len = strlen(now_strings);
			strncpy(now_strings, now_strings, len - 13);

			//if (pattern == PATTERN_PLAYER_MOVESPEED)
			//	movespeed = SetMoveSpeed(decimal_point, now_strings);
			// SetPlayer�ŃZ�b�g���Ă��珉����
			SetPlayerUseFile(s_mapchip_pos, movespeed);
			// �\���̂̏�����(-1)������
			for (int num = 0; num < ORDER_MAX; num++)
			{
				s_mapchip_pos.mapchip_pos_x[num] = -1;
				s_mapchip_pos.mapchip_pos_y[num] = -1;
			}

			return PATTERN_NULL;
		}

		// 50�����ȏ�̕�����ɂȂ��Ă��܂�����G���[�Ƃ݂Ȃ������I��������
		if (strlen(now_strings) > 50)
		{
			int aaaaa = 5;
			exit(5);
		}


	}



	return PATTERN_NULL;
}

// �~�b�V�����f�[�^�̓ǂݍ���
int LoadMissiondata(FILE* fp)
{
	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
	STAGEDATA* p_Stagedata = GetStagedata();

	char loadchar[4] = "";
	char now_strings[256] = "";
	char decision_strings[256] = "";

	int addednumtime = 0;	// �ǂݍ���Œǉ�������

	int pattern = PATTERN_NULL;

	while (pattern != PATTERN_END)
	{
		// �t�@�C����1�������ǂݍ���	fscanf�͕Ԃ�l�Ƃ��ēǂݍ��񂾐�(%s�Ƃ�%d�̐�)��Ԃ����A����͖�������̂�(void)������
		(void)fscanf(fp, "%1s", loadchar);

		// �J���}�������當������m�肳���Ď��̕������		// strcmp�͔�r���ē�������0��Ԃ��B
		if (strcmp(loadchar, ",") == 0)
		{
			// ���݂̕����񂪃J���}�����������ꍇ�A�폜���Ď��̕����̌����ցB��������邱�Ƃɂ���āA(,1)�Ƃ��̐S�z���Ȃ��Ȃ�
			if (strcmp(now_strings, ",") == 0)
			{
				strcpy(now_strings, "");
				continue;
			}

			// �m�肵��������𐔎��ɕϊ����~�b�V�����ɂɔ��f�����鏈���B���e�Ȃ̂��g���l�Ȃ̂��̔��ʂ�����
			applyMissionArray(addednumtime, now_strings);

			// now_strings������������
			strcpy(now_strings, "");

			// �m�肵���̂Œǉ������񐔂�+1�񂷂�
			addednumtime++;

			// �}�b�v�z�񕪕�����ǂݏI�������I���Ƃ݂Ȃ���NULL��Ԃ�
			if (addednumtime == MAX_MISSION * 2)
			{
				return PATTERN_NULL;
			}

		}
		else
		{
			// �J���}�łȂ���Ε������q���Ă���
			strcat(now_strings, loadchar);
		}

		// MapdataEnd ���������ꍇ�����͏I���Ƃ݂Ȃ���NULL��Ԃ�
		if (strstr(now_strings, "MissiondataEnd") != NULL)
		{
			// now_strings������������
			strcpy(now_strings, "");

			return PATTERN_NULL;
		}

		// 50�����ȏ�̕�����ɂȂ��Ă��܂�����G���[�Ƃ݂Ȃ������I��������
		if (strlen(now_strings) > 50)
		{
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
	case 'f': return 0;
	default: 
		// �������}�b�v�̏������ɂȂ��Ă��Ȃ��ď\���Ȑ�(14)���ǂݍ��܂�Ȃ������ꍇ��ւ�ɕ��������ꍞ��ł����ꍇ
		exit(3);			// �����I���B�G���[3
		return 0;
	}
}

// char�^�̐���(1���̂�)����float�^�̐�����
float charTofloat(char *strings, int num)
{
	if (strcmp(&strings[0], "0") == 0)
		return 0.0f;
	if (strcmp(&strings[0], "1") == 0)
		return 1.0f;
	if (strcmp(&strings[0], "2") == 0)
		return 2.0f;
	if (strcmp(&strings[0], "3") == 0)
		return 3.0f;
	if (strcmp(&strings[0], "4") == 0)
		return 4.0f;
	if (strcmp(&strings[0], "5") == 0)
		return 5.0f;
	if (strcmp(&strings[0], "6") == 0)
		return 6.0f;
	if (strcmp(&strings[0], "7") == 0)
		return 7.0f;
	if (strcmp(&strings[0], "8") == 0)
		return 8.0f;
	if (strcmp(&strings[0], "9") == 0)
		return 9.0f;
	if (strcmp(&strings[0], "f") == 0)
		return 0.0f;

	return 0.0f;
}

// int�^�̐���(1���̂�)����char�^�̐����̕�����
char intTochar(int num)
{
	switch (num)
	{
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	}
	exit(6);
	return 'e';
}


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

float SetMoveSpeed(int decimal_point, char strings[])
{

	float speed = 0.0f;
	int below = 0;
	int len = strlen(strings);

	char* p_str = strings;

	// �����_����̌v�Z
	for (int num = 0; num < decimal_point; num++)
	{
		float movespeeddata = charTofloat(p_str, num);
		speed = speed + (movespeeddata * (pow(10, decimal_point - num)));
	}
	// �����_�ȉ��̌v�Z
	for (int num = decimal_point; num < len; num++)
	{
		float movespeeddata = charTofloat(p_str, num);
		speed = speed + (movespeeddata * (pow(0.1, below + 1)));
		below++;
	}

	return speed;
}

void SetMAPCHIP_POS_STRUCT(MAPCHIP_POS_STRUCT * s_mapchip_pos, char strings[] , int order, int XorY)
{
	// �����񂪉����������ׁA�������ɉ����Đ����ɕϊ������Ƃ��̌�����ς���
	int len = strlen(strings);
	if (len == 1)
	{
		int mapchip_pos = charToint(strings[0]);

		if(XorY == 0)
			s_mapchip_pos->mapchip_pos_x[order] = mapchip_pos;
		else
			s_mapchip_pos->mapchip_pos_y[order] = mapchip_pos;
	}
	if (len == 2)
	{
		int mapchip_pos = 10 * charToint(strings[0]) + charToint(strings[1]);

		if (XorY == 0)
			s_mapchip_pos->mapchip_pos_x[order] = mapchip_pos;
		else
			s_mapchip_pos->mapchip_pos_y[order] = mapchip_pos;
	}
	if (len == 3)
	{
		int mapchip_pos = 100 * charToint(strings[0]) + 10 * charToint(strings[1]) + charToint(strings[2]);

		if (XorY == 0)
			s_mapchip_pos->mapchip_pos_x[order] = mapchip_pos;
		else
			s_mapchip_pos->mapchip_pos_y[order] = mapchip_pos;
	}

	return;
}

// nowstrings����~�b�V�����ɒǉ����鏈��
void applyMissionArray(int addednumtime, char strings[])
{
	// addednumtime���牽�Ԗڂ̃~�b�V�����ɒǉ����邩�𒲂ׂĂ���
	int missionnum = addednumtime / 2;		// 2�Ŋ���̂ŁA0,1=0 2,3=1 4,5 = 2 �ƂȂ�


	// stagedata�ɏo�͂��Ă����̂ŁA�|�C���^�[�Ŏ����Ă��Ă���
	STAGEDATA* p_Stagedata = GetStagedata();

	// �����񂪉����������ׁA�������ɉ����Đ����ɕϊ������Ƃ��̌�����ς���
	int len = strlen(strings);
	if (len == 1)
	{
		int data = charToint(strings[0]);
		if (addednumtime % 2 == 0)
			p_Stagedata->mission_ContentsNum[missionnum] = data;
		else
			p_Stagedata->mission_JudgeNum[missionnum] = data;
	}
	if (len == 2)
	{
		int data = 10 * charToint(strings[0]) + charToint(strings[1]);
		if (addednumtime % 2 == 0)
			p_Stagedata->mission_ContentsNum[missionnum] = data;
		else
			p_Stagedata->mission_JudgeNum[missionnum] = data;
	}
	if (len == 3)
	{
		int data = 100 * charToint(strings[0]) + 10 * charToint(strings[1]) + charToint(strings[2]);
		if (addednumtime % 2 == 0)
			p_Stagedata->mission_ContentsNum[missionnum] = data;
		else
			p_Stagedata->mission_JudgeNum[missionnum] = data;
	}
	return;
}

// �������������(1,2,3���̐����^�̐����̂ݑΉ�)��int�^�ɂ��ĕԂ�
int StringsToInt(char strings[])
{
	int back_num = 0;

	// �����񂪉����������ׁA�������ɉ����Đ����ɕϊ������Ƃ��̌�����ς���
	int len = strlen(strings);
	if (len == 1)
	{
		int data = charToint(strings[0]);
		back_num = data;
	}
	if (len == 2)
	{
		int data = 10 * charToint(strings[0]) + charToint(strings[1]);
		back_num = data;
	}
	if (len == 3)
	{
		int data = 100 * charToint(strings[0]) + 10 * charToint(strings[1]) + charToint(strings[2]);
		back_num = data;
	}

	return back_num;
}


// �������int�^(���̐�3���܂�)�𕶎���(1,2,3���̐����^�̐����̂ݑΉ�)�ɂ��ĕԂ�
char* intTostrings(int num)
{
	int number = num;
	int digit = 0;

	int digitnum[3] = { 0,0,0 };

	// ��������������������̌v�Z
	while (number != 0)
	{
		number = number / 10;
		digit++;
	}
	// 0�P�̂̏ꍇ��̃��C�������ƌ���0�ɂȂ�̂ŁA���Ƃ�digit��1�ɂ��Ă�����
	if (num == 0)
		digit = 1;

	// �Ԃ�������
	char data[4] = "";
	char back_strings[20] = "";


	// �����񂪉����������ׁA�������ɉ����Đ����ɕϊ������Ƃ��̌�����ς���
	if (digit == 1)
	{
		digitnum[0] = num;
		data[0] = intTochar(digitnum[0]);

		strcat(back_strings, data);
		strcpy(data, "");
	}
	if (digit == 2)
	{
		digitnum[0] = num / 10;
		digitnum[1] = num - digitnum[0] * 10;

		data[0] = intTochar(digitnum[0]);
		strcat(back_strings, data);
		strcpy(data, "");
		data[0] = intTochar(digitnum[1]);
		strcat(back_strings, data);
		strcpy(data, "");
	}
	if (digit == 3)
	{
		digitnum[0] = num / 100;
		digitnum[1] = (num - digitnum[0] * 100) / 10;
		digitnum[2] = num - digitnum[0] * 100 - digitnum[1] * 10;

		data[0] = intTochar(digitnum[0]);
		strcat(back_strings, data);
		strcpy(data, "");
		data[0] = intTochar(digitnum[1]);
		strcat(back_strings, data);
		strcpy(data, "");
		data[0] = intTochar(digitnum[2]);
		strcat(back_strings, data);
		strcpy(data, "");
	}

	int dad = 0;
	return back_strings;
}

// �ǂݍ��񂾂P�����������ł��邩�ǂ���.�����ł����0��Ԃ�����ȊO��-1��Ԃ�
int strcmpNumber(char* strings)
{
	if (strcmp(&strings[0], "0") == 0)
		return 0;
	if (strcmp(&strings[0], "1") == 0)
		return 0;
	if (strcmp(&strings[0], "2") == 0)
		return 0;
	if (strcmp(&strings[0], "3") == 0)
		return 0;
	if (strcmp(&strings[0], "4") == 0)
		return 0;
	if (strcmp(&strings[0], "5") == 0)
		return 0;
	if (strcmp(&strings[0], "6") == 0)
		return 0;
	if (strcmp(&strings[0], "7") == 0)
		return 0;
	if (strcmp(&strings[0], "8") == 0)
		return 0;
	if (strcmp(&strings[0], "9") == 0)
		return 0;

	return -1;
}




