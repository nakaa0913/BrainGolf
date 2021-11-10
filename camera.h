#pragma once


#include "main.h"

struct CAMERA
{
	D3DXVECTOR2		pos;				// �J�����̃|�W�V����
	D3DXVECTOR2		move;				// �J�����̈ړ�����
	D3DXVECTOR2		movespeed;			// �J�����̈ړ����x
	float			magnification;		// �J�����̔{��



};



CAMERA* GetCamera(void);