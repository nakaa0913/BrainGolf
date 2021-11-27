/*==============================================================================

   �e�N�X�`���̕`�� [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#define MAP_X (14)
#define MAP_Y (20)

#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1440)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(810)				// �E�C���h�E�̍���

#define SCREEN_WIDTH_MOUSEGAP	(SCREEN_WIDTH / (SCREEN_WIDTH - 10.0f))				    // �E�C���h�E�̕��̃}�E�X�ł̂���̔{��
#define SCREEN_HEIGHT_MOUSEGAP	(SCREEN_HEIGHT / (SCREEN_HEIGHT - 10.0f))				// �E�C���h�E�̍����̃}�E�X�ł̂���̔{��


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float frand();

long GetMousePosX(void);
long GetMousePosY(void);
bool GetMouseLClick(void);
int GetMouseLClickNum(void);
bool GetMouseRClick(void);
int GetMouseRClickNum(void);
bool GetMouseScroll(void);
int  GetMouseScrollNum(void);