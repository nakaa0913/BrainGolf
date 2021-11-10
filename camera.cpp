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
	g_Camera.zoomspeed = 0.0f;

}

void UninitCamera(void)
{
	g_Camera.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.movespeed = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.magnification = 1.0f;
	g_Camera.zoomspeed = 0.0f;

}

void UpdateCamera(void)
{




	// �L�[���͂�������ړ����鏈��
	// L �E
	// J ��
	// I ��
	// K ��
	float movespeed_base = 0.5f;
	bool use_movekey_x = false;
	bool use_movekey_y = false;
	// �E�Ɉړ�
	if (GetKeyboardPress(DIK_L))
	{
		g_Camera.movespeed.x += movespeed_base;
		use_movekey_x = true;
	}
	// ���Ɉړ�
	if (GetKeyboardPress(DIK_J))
	{
		g_Camera.movespeed.x -= movespeed_base;
		use_movekey_x = true;
	}
	// ���Ɉړ�
	if (GetKeyboardPress(DIK_K))
	{
		g_Camera.movespeed.y += movespeed_base;
		use_movekey_y = true;
	}
	// ��Ɉړ�
	if (GetKeyboardPress(DIK_I))
	{
		g_Camera.movespeed.y -= movespeed_base;
		use_movekey_y = true;
	}



	// �����L�[�������Ă��Ȃ��ꍇ�ɃJ�����̈ړ����x��ቺ�����鏈��
	float rejectemovespeed = 1.0f;
	if (!use_movekey_x)
	{
		if (g_Camera.movespeed.x > 0)
		{
			g_Camera.movespeed.x -= rejectemovespeed;
			if (g_Camera.movespeed.x < 0)
				g_Camera.movespeed.x = 0;
		}
		if (g_Camera.movespeed.x < 0)
		{
			g_Camera.movespeed.x += rejectemovespeed;
			if (g_Camera.movespeed.x > 0)
				g_Camera.movespeed.x = 0;
		}
	}
	if (!use_movekey_y)
	{
		if (g_Camera.movespeed.y > 0)
		{
			g_Camera.movespeed.y -= rejectemovespeed;
			if (g_Camera.movespeed.y < 0)
				g_Camera.movespeed.y = 0;
		}
		if (g_Camera.movespeed.y < 0)
		{
			g_Camera.movespeed.y += rejectemovespeed;
			if (g_Camera.movespeed.y > 0)
				g_Camera.movespeed.y = 0;
		}
	}


	// �ő呬�x�ɍ��킹�鏈��
	if (g_Camera.movespeed.x > CAMERA_SPEED_MAX_X)
		g_Camera.movespeed.x = CAMERA_SPEED_MAX_X;
	if (g_Camera.movespeed.x < -CAMERA_SPEED_MAX_X)
		g_Camera.movespeed.x = -CAMERA_SPEED_MAX_X;
	if (g_Camera.movespeed.y > CAMERA_SPEED_MAX_Y)
		g_Camera.movespeed.y = CAMERA_SPEED_MAX_Y;
	if (g_Camera.movespeed.y < -CAMERA_SPEED_MAX_Y)
		g_Camera.movespeed.y = -CAMERA_SPEED_MAX_Y;


	// �ړ��X�s�[�h���J�����̃|�W�V�����ɓK�p�����鏈��
	g_Camera.pos.x += g_Camera.movespeed.x;
	g_Camera.pos.y += g_Camera.movespeed.y;







	// �g�嗦�̏���	======================================================


	// �L�[���͂�������g�嗦���ς�鏈��
	// U �Y�[���C��
	// H �Y�[���A�E�g
	float zoomspeed_base = 0.05f;
	bool use_zoomkey = false;
	if (GetKeyboardPress(DIK_U))
	{
		g_Camera.zoomspeed += zoomspeed_base;
		use_zoomkey = true;
	}
	if (GetKeyboardPress(DIK_H))
	{
		g_Camera.zoomspeed -= zoomspeed_base;
		use_zoomkey = true;
	}


	// �����L�[�������Ă��Ȃ��ꍇ�ɃJ�����̈ړ����x��ቺ�����鏈��
	float rejectezoomspeed = 0.01f;
	if (!use_zoomkey)
	{
		if (g_Camera.zoomspeed > 0)
		{
			g_Camera.zoomspeed -= rejectezoomspeed;
			if (g_Camera.zoomspeed < 0)
				g_Camera.zoomspeed = 0;
		}
		if (g_Camera.zoomspeed < 0)
		{
			g_Camera.zoomspeed += rejectezoomspeed;
			if (g_Camera.zoomspeed > 0)
				g_Camera.zoomspeed = 0;
		}
	}

	// �ő呬�x�ɍ��킹�鏈��
	if (g_Camera.zoomspeed > CAMERA_ZOOMSPEED_MAX)
		g_Camera.zoomspeed = CAMERA_ZOOMSPEED_MAX;
	if (g_Camera.zoomspeed < -CAMERA_ZOOMSPEED_MAX)
		g_Camera.zoomspeed = -CAMERA_ZOOMSPEED_MAX;

	// �Y�[���X�s�[�h���g�嗦�ɓK�p�����鏈��
	g_Camera.magnification += g_Camera.zoomspeed;

	// �g�嗦�̍ő�ƍŒ�𒴂��Ȃ��悤�ɂ��鏈��
	if (g_Camera.magnification > CAMERA_MAGNIFICATION_MAX)
		g_Camera.magnification = CAMERA_MAGNIFICATION_MAX;
	if (g_Camera.magnification < CAMERA_MAGNIFICATION_MIN)
		g_Camera.magnification = CAMERA_MAGNIFICATION_MIN;



	// �g�嗦�����������J�����̃|�W�V�����̌v�Z	===================================

	// �g��k�������Ƃ��ɁA����ɒǏ]����悤�ȓ����ɂ������B
	// �����炭�����ǁA�Ƃ�������������30�x�̊p�x�ł̓����ɂȂ�B
	
	//float 
	//g_Camera.pos.x = g_Camera.pos.x + 
	//g_Camera.pos.y = g_Camera.movespeed.y;


	// �X�e�[�W�𓮂����C���[�W�Ȃ̂��A�Q�[�����v���C���Ă���l���J�����������Ă��Ă��̃J�����𓮂����C���[�W�Ȃ̂��ǂ����H
	// ����ŃJ�����̈ړ������̃v���X�}�C�i�X�����܂�


}


CAMERA* GetCamera(void)
{
	return &g_Camera;
}


