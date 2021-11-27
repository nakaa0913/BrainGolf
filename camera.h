#pragma once


#include "main.h"



#define CAMERA_SPEED_MAX_X	(5.0f)
#define CAMERA_SPEED_MAX_Y	(5.0f)

#define CAMERA_MAGNIFICATION_MAX	(1.5f)
#define CAMERA_MAGNIFICATION_MIN	(0.5f)

#define CAMERA_ZOOMSPEED_MAX	(0.5f)


struct CAMERA
{
	D3DXVECTOR2		pos;				// �J�����̃|�W�V����
	D3DXVECTOR2		oldpos;				// �J�����̃|�W�V����
	D3DXVECTOR2		move;				// �J�����̈ړ�����
	D3DXVECTOR2		movespeed;			// �J�����̈ړ����x
	float			magnification;		// �J�����̔{��
	float			zoomspeed;		// �J�����̔{��



};

void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

CAMERA* GetCamera(void);

bool CameraPosChanged();