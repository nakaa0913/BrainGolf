#pragma once


//#define SELECT_MAX (5)

#define TIME (15)

#define SELECT_MAX_X (5)       // select_x��MAX
#define SELECT_MAX_Y (2)       // select_y��MAX

// �v���C���[�\����
struct STAGESELECT
{
	bool					use;					// true:�g���Ă���  false:���g�p
	float					w, h;					// ���ƍ���
	D3DXVECTOR2				pos;					// �|���S���̍��W
	float					rot;					// �|���S���̉�]��
	int						texNo;					// �e�N�X�`���ԍ�

	int						select_x;				//���I��
	int						select_y;			    //�c�I��
	int						selectcooltime;			//�I���N�[���^�C��
	int						selecttime;				//�Z���N�g�t���[��

};

void InitStageSelect(void);
void UninitStageSelect(void);
void UpdateStageSelect(void);
void DrawStageSelect(void);