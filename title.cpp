//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : 
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "effect.h"

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
HRESULT InitTitle(void)
{
	//�e�N�X�`������
	//g_TextureNo = LoadTexture("data/TEXTURE/title/titlerogo_4.png");

	g_BGMNo = LoadSound("data/BGM/morningroutine(title).wav");

	//255(-1)�����[�v�w�肷��Ɩ������[�v
	PlaySound(g_BGMNo, -1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	StopSoundAll();
	//UnloadTexture("data/TEXTURE/title/titlerogo_4.png");
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	bool mouse_Lclick = GetMouseLClick();

	// �X�e�[�W�Z���N�g�֔�ԁB���̎����[���h�P��I������Ă��邱�Ƃɂ���
	if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_STAGE_SELECT);
	}
	if (mouse_Lclick && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_STAGE_SELECT);
	}
	// �^�C�g���ڂ���
	SetEffect(95, D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, 1.0f, 0, 1, 0, 1,
		0.0f, 0.0f, 0);

	//���邭����Ȃ�48�Â�����Ȃ�4
	SetEffect(4, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0,
		0.0f, 0.5f, 0, 1, 0, 1,
		0.0f, 0.0f, 0);

	// �^�C�g���N���b�N�w��
	SetEffect(93, D3DXVECTOR2(720, 300), D3DXVECTOR2(720, 300), 0,
		D3DXVECTOR2(1200.0f, 1200.0f), D3DXVECTOR2(1200.0f, 1200.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 1,
		0.0f, 0.0f, 0);
	
	// �^�C�g�����S
	SetEffect(94, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0,
		D3DXVECTOR2(1000.0f, 500.0f), D3DXVECTOR2(1000.0f, 500.0f), 0,
		0.0f, 1.0f, 0, 1, 0, 1,
		0.0f, 0.0f, 0);



	/*if (Keyboard_IsKeyDown(KK_ENTER) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_WORLD_SELECT);
	}
	if (mouse_Lclick && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_WORLD_SELECT);
	}*/
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

}

