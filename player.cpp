/*==============================================================================

   ���_�Ǘ� [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"

#define PLAYER_H (50)
#define PLAYER_W (50)
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER g_Player[PLAYER_MAX];
static int g_ShotSENo = 0;

static float g_CharaUV = 0.0f;
static int g_AnimePtn = 0;
static int g_AnimeWaitFrame = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	//�e�N�X�`���ǂݍ���
	

	//
	g_ShotSENo = LoadSound("data/SE/shot000.wav");
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_Player[i].texNo = LoadTexture("data/TEXTURE/majo.png");

		g_Player[i].pos.x = SCREEN_WIDTH / 2;
		g_Player[i].pos.y = 440;
		g_Player[i].w = PLAYER_W;
		g_Player[i].h = PLAYER_H;
		g_Player[i].use = false;
	}
	//������

	SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 400));
	SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 300));
	SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 500));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{


		if (GetKeyboardPress(DIK_UP))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x, g_Player[i].pos.y - 3.0f)) != 1)
				g_Player[i].pos.y -= 3.0f;

			g_CharaUV = 0.75f;
		}

		if (GetKeyboardPress(DIK_DOWN))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x, g_Player[i].pos.y + 3.0f)) != 1)
				g_Player[i].pos.y += 3.0f;

			g_CharaUV = 0.0f;
		}

		if (GetKeyboardPress(DIK_LEFT))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x - 3.0f, g_Player[i].pos.y)) != 1)
				g_Player[i].pos.x -= 3.0f;

			g_CharaUV = 0.25f;
		}

		if (GetKeyboardPress(DIK_RIGHT))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x + 3.0f, g_Player[i].pos.y)) != 1)
				g_Player[i].pos.x += 3.0f;

			g_CharaUV = 0.5f;
		}

		//�}�b�v1�֐؂�ւ���
		if (GetKeyboardTrigger(DIK_L))
		{
			SetCurrentMap(1);
		}
		//�}�b�v0�֐؂�ւ���
		if (GetKeyboardTrigger(DIK_K))
		{
			SetCurrentMap(0);
		}


		// �e����
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			PlaySound(g_ShotSENo, 0);

			SetVolume(g_ShotSENo, 0.1f);

			D3DXVECTOR2 pos = g_Player[i].pos;
			SetBullet(pos);		// �P����
			AddScore(123);
		}

		//�����A�j���[�V����
		if (g_AnimeWaitFrame > 10)
		{
			g_AnimePtn++;
			if (g_AnimePtn > 2)
				g_AnimePtn = 0;

			g_AnimeWaitFrame = 0;
		}
		g_AnimeWaitFrame++;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == true)
		{
			DrawSprite(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h, g_AnimePtn * 0.33333f, g_CharaUV, 0.3333f, 0.25f);
		}
	}
}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player[0];
}


void SetPlayer(D3DXVECTOR2 pos)
{
	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == false)		// ���g�p��Ԃ̃o���b�g��������
		{
			g_Player[i].use = true;			// �g�p��Ԃ֕ύX����
			g_Player[i].pos = pos;			// ���W���Z�b�g
			g_Player[i].h = PLAYER_H;
			g_Player[i].w = PLAYER_W;

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}