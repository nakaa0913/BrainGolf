//=============================================================================
//
// �^�C�g����ʏ��� [Prologue.cpp]
// Author : 
//
//=============================================================================
#include "Prologue.h"
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "enemy_emitter.h"
#include "bullet.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "bg.h"
#include "result.h"
#include"stageselect.h"
#include "Texture.h"
#include "sprite.h"
#include "effect.h"
#include "keyboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	g_TextureNo = 0;	// �e�N�X�`�����
static int	g_BGMNo = 0;		// BGM���ʎq

//=============================================================================
// ����������
//=============================================================================
void InitPrologue(void)
{
	//�e�N�X�`������
	g_TextureNo = LoadTexture("data/TEXTURE/logo/HEW2.png");

	g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)�����[�v�w�肷��Ɩ������[�v
	PlaySound(g_BGMNo, -1);

	return;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPrologue(void)
{
	StopSoundAll();
	UnloadTexture("data/TEXTURE/logo/HEW2.png");
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePrologue(void)
{
	bool mouse_Lclick = GetMouseLClick();

	if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_TITLE);
	}
	if (mouse_Lclick && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_TITLE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPrologue(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
}
