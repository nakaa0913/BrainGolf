/*==============================================================================

   ���_�Ǘ�[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_MAX (5)

// �v���C���[�\����
struct RESULT
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
	int						goaltime;				// �S�[�����Ă���̎���
	int						selectpush;				// �I�����Ă���
	int						selecttime;				// �I���N�[���^�C��
	int						resulttime;				// ���U���g�\�����Ă���̎���
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(D3DXVECTOR2 pos);
RESULT* GetResult(void);

//#define MAX_RESULT (3)			// �~�b�V�������̍ő�(�Ō��)3�Œ�
//#define SAVEDATA_ELEMENTS	(4)			// �~�b�V������+�N���A�^�C��
//#define MAX_DIGIT	(3)			// �ő�3���܂�
//
//typedef struct {
//
//	// �Z�b�g�G�t�F�N�g�Ŏg����z��̔ԍ���ۊǂ���
//	int mission_background_EffectArray;					// �w�i��1�Ȃ̂�1
//	int mission_ContentsNum_EffectArray[MAX_RESULT];
//	int mission_JudgeNum_EffectArray[MAX_RESULT][MAX_DIGIT];
//
//}RESULT;

//void DrawMissionResult();
//void DeleteMissionResult();
bool checkresult();