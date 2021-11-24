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
#define PLAYER_MAX (10)

#define ORDER_MAX			 (5)
#define INPUT_DIGIT_X_MAX	 (4)
#define INPUT_DIGIT_Y_MAX	 (4)

#define PLAYER_MOVE_SPEED	 (3.0f)

#define CLUB_CHANGECOOL	(12)			// �N���u�������ւ��̃N�[���^�C��


// �t�@�C���ǂݍ��݂���}�b�v�`�b�v�ł̍��W�Ɖ������鏇�Ԃ����₷�����邽�߂����̍\����
// PLAYER�\���̂Ŏg�p���Ă���̂ŁA�������ɏ����Ȃ��ƃ_���B�l�X�g�\��
struct MAPCHIP_POS_STRUCT
{			
	int						mapchip_pos_x[ORDER_MAX];
	int						mapchip_pos_y[ORDER_MAX];
};


// �v���C���[�\����
struct PLAYER
{
	bool					use;					// true:�g���Ă���  false:���g�p
	float					w, h;					// ���ƍ���
	D3DXVECTOR2				pos;					// �|���S���̍��W
	D3DXVECTOR2				nextpos;				// ���̗\��̍��W
	D3DXVECTOR2				drawpos;				// �\������ۂ̍��W
	D3DXVECTOR2				drawsize;				// �\������ۂ̃T�C�Y
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

	struct					MAPCHIP_POS_STRUCT Mapchip_Pos_Struct;
	bool					move_around;			// �v���C���[�������ʒu���瓮����邩�ǂ����B
	int						now_array_num;			// ���ݔz��̉��Ԃ̓��쒆��
	int						order_max_num;			// �����ƒ��g�������Ă����Ԃ��ǂ��܂ł�


	int						now_count;				////�ꎞ�I�Ȃ���
	int						moving_count;			////
	int						pos_moving_pattern;		// �����ʒu����I���ʒu�Ɉړ�����Ƃ��̓����� 0:pos1���瓮���Ȃ�
	float					move_speed;				// �v���C���[�̈ړ����x

	int						roundtrip_x;			// �v���C���[�����������鏈��X
	int						roundtrip_y;			// �v���C���[�����������鏈��Y
	float					animeptn2;				// �v���C���[�̕��s�A�j���[�V����
	int						animewaitframe2;		// �v���C���[�̕��s�A�j���[�V�����҂�����
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DrawPlayerSpecifyNum(int i);
void DrawPlayerForPlacement(void);
void DrawPlayerSpecifyNumForPlacement(int i);
void SetPlayer(D3DXVECTOR2 pos);
void SetPlayerUseMapPos(int mappos_x, int mappos_y);
PLAYER *GetPlayer(void);
int GetClubPattern(void);

void SetPlayerUseFile(MAPCHIP_POS_STRUCT Receive_Mapchip_Pos_Struct, float movespeed);
int SetPlayerForPlacement(int mappos_x, int mappos_y);
int returnHavePlayer();
void DeletePlayer(int num);
void DeletePlacementPlayer();