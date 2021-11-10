#pragma once


#define SELECT_MAX (5)

#define TIME (15)
// �v���C���[�\����
struct SELECT
{
	bool					use;					// true:�g���Ă���  false:���g�p
	float					w, h;					// ���ƍ���
	D3DXVECTOR2				pos;					// �|���S���̍��W
	float					rot;					// �|���S���̉�]��
	int						texNo;					// �e�N�X�`���ԍ�

	int						act;					// �e�N�X�`���̏�ԊǗ�
	int						direction;				// �v���C���[�̌����Ă���� 0:��,1:��,2:�E,3:��
	bool					have;					// �{�[���������Ă��邩�ǂ���
	int						catchwait;				// �{�[����ł��Ă��玟�ɃL���b�`�ł���܂ł̃N�[���^�C���Ǘ�
	float					angle;					// �ǂ̊p�x�������Ă��邩
	int						ShotPower;				// �e��ł��o������
	bool					ConfirmAngle;			// �p�x���m�肵�����ǂ���
	int						ConfirmCooltime;		// �m�肵�Ă���̃N�[���^�C��
	int						goaltime;				//�S�[�����Ă���̎���
	int						selectpush;				//�I�����Ă���
	int						selectvertical;			//�c�I��
	int						selectcooltime;			//�I���N�[���^�C��
	int						selecttime;				//�Z���N�g�t���[��
};

void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
