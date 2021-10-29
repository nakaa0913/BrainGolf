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
#include "Goal.h"
#include "scene.h"
#include "fade.h"

#define GOAL_H (50)
#define GOAL_W (50)
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static GOAL g_Goal[GOAL_MAX];

static int aa;
static int bb;//��
static int cc;//�l�N�X�g
static int dd;
static int ee;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitGoal(void)
{
	//�e�N�X�`���ǂݍ���


	//
	/*g_ShotSENo = LoadSound("data/SE/shot000.wav");*/
	aa = LoadTexture("data/TEXTURE/aa.png");
	bb = LoadTexture("data/TEXTURE/tako.png");
	cc = LoadTexture("data/TEXTURE/title.png");
	dd = LoadTexture("data/TEXTURE/title.png");
	ee = LoadTexture("data/TEXTURE/title.png");


	for (int i = 0; i < GOAL_MAX; i++)
	{
		g_Goal[i].goaltime = 0;
		g_Goal[i].selectpush = 0;
	}


	//������


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGoal(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGoal(void)
{
	for (int i = 0; i < GOAL_MAX; i++)
	{


		g_Goal[i].goaltime++;

		if (g_Goal[i].selecttime <= 0)
		{

			if (GetKeyboardPress(DIK_P))
			{
				g_Goal[i].selectpush++;
				g_Goal[i].selecttime = 30;

			}
			if (g_Goal[i].selectpush >= 3)
			{
				g_Goal[i].selectpush = 0;
			}


			if (g_Goal[i].selectpush == 0)
			{
				if (GetKeyboardPress(DIK_I))
				{
					SceneTransition(SCENE_RESULT);

				}
			}


			if (g_Goal[i].selectpush == 1)
			{
				if (GetKeyboardPress(DIK_I))
				{
					SceneTransition(SCENE_SELECT);

				}
			}

			if (g_Goal[i].selectpush == 2)
			{
				if (GetKeyboardPress(DIK_I))
				{
					SceneTransition(SCENE_TITLE);

				}
			}

		}



		if (g_Goal[i].selecttime >= 0)
			g_Goal[i].selecttime--;

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGoal(void)
{
	for (int i = 0; i < GOAL_MAX; i++)
	{


		if (g_Goal[i].goaltime >= 10)
		{
			DrawSpriteColorRotate(aa, 320.0f, 400.0f, 400.0f, 400.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

		}

		if (g_Goal[i].goaltime >= 40)
		{
			DrawSpriteColorRotate(bb, 210.0f, 180.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		}

		if (g_Goal[i].goaltime >= 80)
		{
			DrawSpriteColorRotate(bb, 290.0f, 180.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		}

		if (g_Goal[i].goaltime >= 120)
		{
			DrawSpriteColorRotate(bb, 370.0f, 180.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		}

		if (g_Goal[i].goaltime >= 160)
		{

			DrawSpriteColorRotate(cc, 290.0f, 200.0f, 300.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			DrawSpriteColorRotate(dd, 290.0f, 400.0f, 300.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			DrawSpriteColorRotate(ee, 290.0f, 600.0f, 300.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

			if (g_Goal[i].selectpush == 0)
			{
				DrawSpriteColorRotate(cc, 290.0f, 200.0f, 350.0f, 150.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			}

			if (g_Goal[i].selectpush == 1)
			{
				DrawSpriteColorRotate(dd, 290.0f, 400.0f, 350.0f, 150.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			}

			if (g_Goal[i].selectpush == 2)
			{
				DrawSpriteColorRotate(ee, 290.0f, 600.0f, 350.0f, 150.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			}
		}



	}
}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
GOAL* GetGoal(void)
{
	return &g_Goal[0];
}


void SetGoal(D3DXVECTOR2 pos)
{
	
}