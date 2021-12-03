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

//#define DRAW_GAP	 (0 * p_Camera->magnification)			// ���ʂ����t�g�g�b�v�ł���Ă������ŏo������
#define DRAW_GAP_X	 (20 * p_Camera->magnification)			// ���ʂ����t�g�g�b�v�ł���Ă������ŏo������
#define DRAW_GAP_Y	 (20 * p_Camera->magnification)			// ���ʂ����t�g�g�b�v�ł���Ă������ŏo������H
									// �����������ĕ\���𑫌��ɓ����蔻�肪����悤�ɂ���B
#define DRAW_GAP_BALL_X	 (-5 * p_Camera->magnification)			// ���DRAW_GAP�ɂ���Ƀv���X����
#define DRAW_GAP_BALL_Y	 (-5 * p_Camera->magnification)			// ���m�}�Ō������ɁA�{�[�����Y��Ɍ����邽�߂̂���


#define DRAW_MAP_CHIP_SIZE_X (80.0f)
#define DRAW_MAP_CHIP_SIZE_Y (40.0f)
//#define DRAW_MAP_CHIP_SIZE_X (80.0f * p_Camera->magnification)	// �J�����̃Y�[���{���g��Ȃ��Ȃ����̂ŁB
//#define DRAW_MAP_CHIP_SIZE_Y (40.0f * p_Camera->magnification)

#define MAP_CHIP3D_SIZE_X (240.0f)
#define MAP_CHIP3D_SIZE_Y (400.0f)

#define MAP_CHIP3D_GAP_X (80.0f)
#define MAP_CHIP3D_GAP_Y (360.0f)

#define GAME_ORIGIN_POINT_X		(720.0f + 40.0f * 2 + 0.0f)					// �Q�[�����̌��_������Ƃ���B
#define GAME_ORIGIN_POINT_Y		(0.0f	+ 40.0f * 2 + 0.0f)					// �Q�[�����̌��_������Ƃ���B

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
void DrawBGaboveForPlacement(void);
void DrawBGsideForPlacement(void);

int GetMapEnter(D3DXVECTOR2 pos);
void SetCurrentMap(int next);

int CheckBlockdata(int BlockX, int BlockY);

D3DXVECTOR2 PosToMappos(D3DXVECTOR2 pos);
D3DXVECTOR2 MapposToPos(D3DXVECTOR2 mappos);

int LimitRange(int num, int min, int max);