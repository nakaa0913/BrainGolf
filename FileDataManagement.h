#pragma once



// �t�@�C���ǂݍ��ݒ��ɁA�����̃f�[�^��ǂ�ł��邩�̔��ʂ��邽�߂̃p�^�[��
#define		PATTERN_NULL		(-1)
#define		PATTERN_MAP			(0)
#define		PATTERN_PLAYER		(1)
#define		PATTERN_END			(999)


void LoadMapdataMain(char* fileName);

int LoadMapdata(FILE* fp);
int charToint(char c);
void applyMapArray(int x, int y, char strings[]);