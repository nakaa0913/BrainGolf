#include "main.h"
#include "bg.h"

#define MAX_STAGE (30)			//�ő�X�e�[�W

typedef struct {
	int stagenum;				//�X�e�[�W�ԍ�
	int maparray[MAP_Y][MAP_X];	// �}�b�v�̔z��f�[�^
	int mission1;				//�~�b�V�����͉���
	int mission2;
	int mission3;
	//bool clear1;				//�~�b�V�������N���A������
	//bool clear2;				// ����̓v���C���[�̃Z�[�u�f�[�^�̕��ŊǗ�
	//bool clear3;
	//float cleartime;			//�N���A�^�C��
}STAGEDATA;


void InitStagedata();
void UninitStagedata();
void UpdateStagedata();

STAGEDATA* GetStagedata();

void SetStageData(int stagenum);