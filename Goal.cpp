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
#include "effect.h"

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

static int aa;//��ʁi���j
static int bb;//���i�����j
static int cc;//���U���g
static int dd;//�I����ʁi�^�C�g���j
static int ee;//�^�C�g��
static int ff;//�N���A�`�i�^�C�g���j
//=============================================================================
// ����������
//=============================================================================
HRESULT InitGoal(void)
{
	//�e�N�X�`���ǂݍ���


	//
	/*g_ShotSENo = LoadSound("data/SE/shot000.wav");*/
	aa = LoadTexture("data/TEXTURE/aka.png");
	bb = LoadTexture("data/TEXTURE/tako.png");
	cc = LoadTexture("data/TEXTURE/title.png");
	dd = LoadTexture("data/TEXTURE/title.png");
	ee = LoadTexture("data/TEXTURE/title.png");
	ff = LoadTexture("data/TEXTURE/title.png");

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



		if (g_Goal[i].goaltime == 10)
		{
			//DrawSpriteColorRotate(aa, 275.0f, 500.0f, 500.0f, 600.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			//DrawSpriteColorRotate(ff, 275.0f, 60.0f, 400.0f, 200.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

			//SetEffect(1, D3DXVECTOR2(275.0f, 500.0f), D3DXVECTOR2(500.0f, 600.0f), D3DXVECTOR2(0.0f, 0.0f), 180, 999, 0, -1);
			SetEffect(1, D3DXVECTOR2(275.0f, 500.0f), D3DXVECTOR2(300.0f, 500.0f), 1,
				D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(500.0f, 600.0f), 1,
				0.0f, 1.0f, 180, 999, 0, 180,
				45.0f, 90.0f, 2);




			//SetEffect(3, D3DXVECTOR2(280.0f, 60.0f), D3DXVECTOR2(400.0f, 200.0f), D3DXVECTOR2(0.0f, 0.0f), 180, 999, 0, -1);

		}

		if (g_Goal[i].goaltime == 40)
		{
			//DrawSpriteColorRotate(bb, 160.0f, 180.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

			//SetEffect(2, D3DXVECTOR2(160.0f, 180.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), 180, 999, 0, -1);

		}

		if (g_Goal[i].goaltime == 80)
		{
			//DrawSpriteColorRotate(bb, 280.0f, 180.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			//SetEffect(2, D3DXVECTOR2(280.0f, 180.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), 180, 999, 0, -1);
		}

		if (g_Goal[i].goaltime == 120)
		{
			//DrawSpriteColorRotate(bb, 400.0f, 180.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			//SetEffect(2, D3DXVECTOR2(400.0f, 180.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), 180, 999, 0, -1);

		}

		if (g_Goal[i].goaltime == 160)
		{

			//DrawSpriteColorRotate(cc, 290.0f, 400.0f, 300.0f, 80.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			//DrawSpriteColorRotate(dd, 290.0f, 550.0f, 300.0f, 80.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			//DrawSpriteColorRotate(ee, 290.0f, 700.0f, 300.0f, 80.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

			

		}

		if (g_Goal[i].goaltime >= 160)
		{
			//SetEffect(3, D3DXVECTOR2(290.0f, 400.0f), D3DXVECTOR2(300.0f, 80.0f), D3DXVECTOR2(0.0f, 0.0f), 0, 1, 0, -1);
			//SetEffect(3, D3DXVECTOR2(290.0f, 550.0f), D3DXVECTOR2(300.0f, 80.0f), D3DXVECTOR2(0.0f, 0.0f), 0, 1, 0, -1);
			//SetEffect(3, D3DXVECTOR2(290.0f, 700.0f), D3DXVECTOR2(300.0f, 80.0f), D3DXVECTOR2(0.0f, 0.0f), 0, 1, 0, -1);


			
			if (g_Goal[i].selectpush == 0)
			{
				//DrawSpriteColorRotate(cc, 290.0f, 400.0f, 350.0f, 120.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
				//SetEffect(3, D3DXVECTOR2(290.0f, 400.0f), D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(0.0f, 0.0f), 0, 1, 0, -1);

			}

			if (g_Goal[i].selectpush == 1)
			{
				//DrawSpriteColorRotate(dd, 290.0f, 550.0f, 350.0f, 120.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
				//SetEffect(3, D3DXVECTOR2(290.0f, 550.0f), D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(0.0f, 0.0f), 0, 1, 0, -1);

			}

			if (g_Goal[i].selectpush == 2)
			{
				//DrawSpriteColorRotate(ee, 290.0f, 700.0f, 350.0f, 120.0f, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

				//SetEffect(3, D3DXVECTOR2(290.0f, 700.0f), D3DXVECTOR2(350.0f, 120.0f), D3DXVECTOR2(0.0f, 0.0f), 0, 1, 0, -1);
			}
		}



		g_Goal[i].goaltime++;

		if (g_Goal[i].selecttime <= 0)
		{

			if (GetKeyboardPress(DIK_DOWN))
			{
				g_Goal[i].selectpush++;
				g_Goal[i].selecttime = 30;

			}
			if (g_Goal[i].selectpush >= 3)
			{
				g_Goal[i].selectpush = 0;
			}

			if (GetKeyboardPress(DIK_UP))
			{
				g_Goal[i].selectpush--;
				g_Goal[i].selecttime = 30;

			}
			if (g_Goal[i].selectpush < 0)
			{
				g_Goal[i].selectpush = 2;
			}

			if (g_Goal[i].selectpush == 0)
			{
				if (GetKeyboardPress(DIK_RETURN))
				{
					SceneTransition(SCENE_RESULT);

				}
			}


			if (g_Goal[i].selectpush == 1)
			{
				if (GetKeyboardPress(DIK_RETURN))
				{
					SceneTransition(SCENE_SELECT);

				}
			}

			if (g_Goal[i].selectpush == 2)
			{
				if (GetKeyboardPress(DIK_RETURN))
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