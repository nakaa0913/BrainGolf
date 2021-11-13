#pragma once


//#define SELECT_MAX (5)

#define TIME (15)

#define WORLD_SELECT_MAX_X (5)       // select_x��MAX
#define WORLD_SELECT_MAX_Y (1)       // select_y��MAX

#define WORDL_SELECT_COOL (10)       // ���[���h�Z���N�g�̎��̃N�[���^�C��

// �v���C���[�\����
struct WORLDSELECT
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

void InitWorldSelect(void);
void UninitWorldSelect(void);
void UpdateWorldSelect(void);
void DrawWorldSelect(void);

WORLDSELECT* GetWorldSelect();
int GetNowWorld();

void StartWorldSelectScreen();