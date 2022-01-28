#pragma once

#include "main.h"
#include "renderer.h"

#define PREDICTION_MAX		(7)		// �\���e��Max��

#define PREDICTION_SIZE		(20)	// �\���e�̃x�[�X�̃T�C�Y


// �\���e�\���� 
struct PREDICTION
{
	
	D3DXVECTOR2				size;					// ���ƍ���
	D3DXVECTOR2				pos;					// �\���e�̍��W

	D3DXVECTOR2				drawpos;				// �\������ۂ̍��W
	D3DXVECTOR2				drawsize;				// �\������ۂ̃T�C�Y

	float					angle;					// �p�x
	D3DXVECTOR2				vector;					// �x�N�g��
	float					shotpower;				// ���̗͂̔{��

	int						tex;					// ���Ԗڂ̃e�N�X�`���[���g�p����̂�
	bool					isUse;					// true:�g���Ă���  false:���g�p

};


HRESULT InitPrediction(void);
void UninitPrediction(void);
void UpdatePrediction(void);
void DrawPrediction(void);
void DrawPredictionSpecifyNum(int i);

PREDICTION* GetPrediction(void);

void PredictionUseTrue();
void PredictionUseFalse();