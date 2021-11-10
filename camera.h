#pragma once


#include "main.h"

struct CAMERA
{
	D3DXVECTOR2		pos;				// カメラのポジション
	D3DXVECTOR2		move;				// カメラの移動距離
	D3DXVECTOR2		movespeed;			// カメラの移動速度
	float			magnification;		// カメラの倍率



};



CAMERA* GetCamera(void);