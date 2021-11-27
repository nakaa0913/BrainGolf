#pragma once

// �܂��J�[�\�����ǂ��̃}�X�������Ă��邩�𒲂ׂ�
// ���N���b�N�������̃u���b�N�������\��+�������o��
// �������N���b�N�ŏ���


#define MAX_GIMMICKDESCRIPTION	(4)

#define GIMMICKDESCRIPTION_FADEIN		(18)		// �����̃t�F�[�h�C���ƃT�C�Y�傫���Ȃ�̂ɂ����鎞��
#define GIMMICKDESCRIPTION_DRAWTIME		(160)		// �����̕\������
#define GIMMICKDESCRIPTION_FADEOUT		(18)		// �����̃t�F�[�h�A�E�g�ɂ����鎞��

typedef struct {

	int x;
	int y;

	// �Z�b�g�G�t�F�N�g�Ŏg����z��̔ԍ���ۊǂ���
	int background_EffectArray;					// �w�i
	int text_EffectArray;						// ���͂ƃA�C�R��(1���̉摜�Ƃ��ēǂݍ���)
	int pickupBlock_EffectArray;				// �I�����Ă���u���b�N�̂ӂ������点�Ă���

	int GeneratedTime;							// ��������Ă���̌o�ߎ���

	bool isUse;									// ���ݎg���Ă��邩�ǂ���

}GIMMICKDESCRIPTION;



void InitGimmickDescription();
void UninitGimmickDescription();
void UpdateGimmickDescription_Game();

GIMMICKDESCRIPTION* GetGimmickDescription(void);

float CheckGimmickDescriptionChipPos(int block_data, int XorY);
void GenerateGimmickDescription(int block_data, int x, int y);
void DeleteGimmickDescription();

void GimmickDescriptionPickupUpdata(int i);