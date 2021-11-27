#pragma once


#include "main.h"



#define CAMERA_SPEED_MAX_X	(5.0f)
#define CAMERA_SPEED_MAX_Y	(5.0f)

#define CAMERA_MAGNIFICATION_MAX	(1.5f)
#define CAMERA_MAGNIFICATION_MIN	(0.5f)

#define CAMERA_ZOOMSPEED_MAX	(0.5f)


struct CAMERA
{
	D3DXVECTOR2		pos;				// カメラのポジション
	D3DXVECTOR2		oldpos;				// カメラのポジション
	D3DXVECTOR2		move;				// カメラの移動距離
	D3DXVECTOR2		movespeed;			// カメラの移動速度
	float			magnification;		// カメラの倍率
	float			zoomspeed;		// カメラの倍率



};

void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

CAMERA* GetCamera(void);

bool CameraPosChanged();