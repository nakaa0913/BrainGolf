//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : 
//
//=============================================================================
#include "enemy.h"
#include "texture.h"
#include "sprite.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static ENEMY g_Enemy[ENEMY_MAX];							// �G�l�~�[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	int texNo = LoadTexture("data/TEXTURE/tako.png");

	// �G�l�~�[�\���̂̏�����
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].use   = false;
		g_Enemy[i].w     = 50.0f;
		g_Enemy[i].h     = 50.0f;
		g_Enemy[i].pos   = D3DXVECTOR2(970.0f+i*15, 300.0f);
		g_Enemy[i].rot   = 0.0f;
		g_Enemy[i].texNo = texNo;
		g_Enemy[i].state = 0;
		g_Enemy[i].frame = 0;
	}
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)		// ���̃G�l�~�[���g���Ă���H
		{								// Yes	
			switch (g_Enemy[i].state)
			{
			case 0:
				g_Enemy[i].pos.x -= 3.0f;
				if(g_Enemy[i].frame > 180)
				{
					g_Enemy[i].state = 1;
					g_Enemy[i].frame = 0;
				}
				break;
			case 1:
				g_Enemy[i].pos.x += 3.0f;
				g_Enemy[i].pos.y += 3.0f;

				if (g_Enemy[i].frame > 20)
				{
					g_Enemy[i].state = 2;
					g_Enemy[i].frame = 0;
				}
				break;
			case 2:
				g_Enemy[i].pos.x -= 3.0f;
				if (g_Enemy[i].frame > 40)
				{
					g_Enemy[i].state = 3;
					g_Enemy[i].frame = 0;
				}
				break;
			case 3:
				g_Enemy[i].pos.x += 3.0f;
				g_Enemy[i].pos.y += 3.0f;
				if (g_Enemy[i].frame > 40)
				{
					g_Enemy[i].state = 4;
					g_Enemy[i].frame = 0;
				}
				break;
			case 4:
				g_Enemy[i].pos.x += 3.0f;
				if (g_Enemy[i].frame > 200)
				{
					g_Enemy[i].use = 0;
				}
				break;
			}
									
			// ��]������
			if ((i % 2) == 0)
			{
				g_Enemy[i].rot += 0.05f;
			}
			else
			{
				g_Enemy[i].rot -= 0.05f;
			}

			//�t���[���̒ǉ�
			g_Enemy[i].frame++;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)
		{
			//�G�l�~�[�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Enemy[i].pos.x;	// �G�l�~�[�̕\���ʒuX
			float py = g_Enemy[i].pos.y;	// �G�l�~�[�̕\���ʒuY
			float pw = g_Enemy[i].w;		// �G�l�~�[�̕\����
			float ph = g_Enemy[i].h;		// �G�l�~�[�̕\������
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			DrawSpriteColorRotate(g_Enemy[i].texNo, px, py, pw, ph, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Enemy[i].rot);
		}
	}
}

//=============================================================================
// �G�l�~�[�\���̂̐擪�A�h���X���擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_Enemy[0];
}


//=============================================================================
// �G�̔�������
//=============================================================================
void SetEnemy(D3DXVECTOR2 pos)
{
	// �������g�p�̃f�[�^��T��
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == false)		// ���g�p��Ԃ̓G�f�[�^��������
		{
			g_Enemy[i].use = true;			// �g�p��Ԃ֕ύX����
			g_Enemy[i].pos = pos;			// ���W���Z�b�g
			g_Enemy[i].rot = 0.0f;			// ��]�p�̃��Z�b�g
			g_Enemy[i].state = 0;			// ��Ԃ����Z�b�g
			g_Enemy[i].frame = 0;			// �t���[���̃��Z�b�g
			return;							// �G���Z�b�g�ł����̂ŏI������
		}
	}
}

