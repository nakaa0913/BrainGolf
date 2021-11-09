//=============================================================================
//
// �w�i���� [bg.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"




//// �w�i�\����
//struct BACKGROUND
//{
//	bool					use;					// true:�g���Ă���  false:���g�p
//	D3DXVECTOR2				size;					// ���ƍ���
//	D3DXVECTOR2				pos;					// �|���S���̍��W
//	D3DXVECTOR2				nextpos;				// ���̗\��̍��W
//	D3DXVECTOR2				drawpos;				// ���̗\��̍��W
//	float					rot;					// �|���S���̉�]��
//	int						texNo;					// �e�N�X�`���ԍ�
//
//};






//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_CHIP_SIZE_X (40)
#define MAP_CHIP_SIZE_Y (40)

#define DRAW_MAP_CHIP_SIZE_X (80)
#define DRAW_MAP_CHIP_SIZE_Y (40)

#define GAME_ORIGIN_POINT_X		(SCREEN_WIDTH / 2 + 120.0f)					// �Q�[�����̌��_������Ƃ���B
#define GAME_ORIGIN_POINT_Y		(0.0f + 40.0f)							// �Q�[�����̌��_������Ƃ���B

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);

int GetMapEnter(D3DXVECTOR2 pos);
void SetCurrentMap(int next);

int CheckBlockdata(int BlockX, int BlockY);


