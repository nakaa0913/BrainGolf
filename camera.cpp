#include "bg.h"
#include "texture.h"
#include "sprite.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "bullet.h"
#include "camera.h"
#include "input.h"

CAMERA g_Camera;

void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.movespeed = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.magnification = 1.0f;

}

void UninitCamera(void)
{
	g_Camera.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.movespeed = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.magnification = 1.0f;

}

void UpdateCamera(void)
{
	// L âE
	// J ç∂
	// I è„
	// K â∫
	if (GetKeyboardPress(DIK_L))
	{

	}

}


CAMERA* GetCamera(void)
{
	return &g_Camera;
}


