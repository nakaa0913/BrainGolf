

#include<iostream>
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "gamedata.h"
#include "mission.h"
#include "effect.h"
#include "savedata.h"
#include "gimmick_description.h"
#include "camera.h"




GIMMICKDESCRIPTION g_GimmickDescription[MAX_GIMMICKDESCRIPTION];

int GimmickDescription_x = -1;		// ���݃}�E�X�J�[�\��������Ƃ���̍��W
int GimmickDescription_y = -1;

int GimmickDescriptionCool = 30;

void InitGimmickDescription()
{
	for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
	{

		g_GimmickDescription[i].x = -1;
		g_GimmickDescription[i].y = -1;

		g_GimmickDescription[i].background_EffectArray = -1;
		g_GimmickDescription[i].text_EffectArray = -1;
		g_GimmickDescription[i].pickupBlock_EffectArray = -1;

		g_GimmickDescription[i].GeneratedTime = 0;

		g_GimmickDescription[i].isUse = false;
	}

	GimmickDescription_x = -1;
	GimmickDescription_y = -1;

	GimmickDescriptionCool = 30;

	return;
}

void UninitGimmickDescription()
{

	return;
}

// �Q�[����(�Ƃ�������)�ł̐������o�����
void UpdateGimmickDescription_Game()
{
	CAMERA* p_Camera = GetCamera();

	//�}�E�X�̍��W���擾
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Rclick = GetMouseRClick();

	bool mouseuse = false;

	// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
	int OldGimmickDescription_x = GimmickDescription_x;
	int OldGimmickDescription_y = GimmickDescription_y;

	//float interval_x = DRAW_MAP_CHIP_SIZE_X;
	//float interval_y = DRAW_MAP_CHIP_SIZE_Y;
	float interval_x = 80.0f;
	float interval_y = 40.0f;



	// �}�E�X�̍��W���獡�ǂ̃u���b�N�̏�ɃJ�[�\��������̂��̌v�Z
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			float draw_gap_up = 20.0f;					// �e�N�X�`���Ƃ̂���,�ׂ��������Ɏg���Ă��悵
			float draw_gap_down = -20.0f;

			float a = 0.5f;								// sin30���̂��� y = ax + b ��a
			float camera_gap_x = a * p_Camera->pos.x;
			float camera_gap_y = p_Camera->pos.y;
			float b_up = 460.0f + draw_gap_up + camera_gap_y + camera_gap_x;			// �E�オ��̐���y���ł�y				 y = ax + b ��b
			float b_down = -380.0f + draw_gap_down + camera_gap_y - camera_gap_x;		// ��������̐���y���ł�y				 y = ax + b ��b

			// �E�オ��̓�̐��̊ԂȂ�΁Ax�����܂�
			if (mouse_pos_Y > -a * mouse_pos_X + b_up + interval_y * (x + 0) &&
				mouse_pos_Y < -a * mouse_pos_X + b_up + interval_y * (x + 1))
			{
				// �E������̓�̐��̊ԂȂ�΁Ay�����܂�
				if (mouse_pos_Y > a * mouse_pos_X + b_down + interval_y * (y + 0) &&
					mouse_pos_Y < a * mouse_pos_X + b_down + interval_y * (y + 1))
				{
					mouseuse = true;

					GimmickDescription_x = x;
					GimmickDescription_y = y;

					break;
				}


			}
		}
	}

	// �}�E�X�J�[�\�����u���b�N�ɂ����ĂȂ��ꍇ
	if (mouseuse == false)
	{
		GimmickDescription_x = -1;
		GimmickDescription_y = -1;
	}

	SetScore2(GimmickDescription_x);
	SetScore3(GimmickDescription_y);

	bool DrawRequest = false;

	// �E�N���b�N�ł��̍��W���g���ĕ\���Ȃ� GimmickDescriptionCool
	if (GimmickDescriptionCool <= 0)
	{
		if (mouseuse && mouse_Rclick)
		{
			GimmickDescriptionCool = 30;
			DrawRequest = true;

		}
	}


	// ��������̂̏��������ƃJ�E���g��i�߂鏈��
	for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
	{
		if (g_GimmickDescription[i].isUse == true)
		{
			// �J�����ړ��ɂ��s�b�N�A�b�v�����̍X�V
			GimmickDescriptionPickupUpdata(i);

			if (g_GimmickDescription[i].GeneratedTime > GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME + GIMMICKDESCRIPTION_FADEOUT)
			{
				g_GimmickDescription[i].isUse = false;
			}
			else
				g_GimmickDescription[i].GeneratedTime++;		// �����Ȃ����̂̓J�E���g��i�߂�
		}
	}


	// �\���̗v�����������ꍇ�ɕ\���ƑO��̂��������
	if (DrawRequest == true)
	{
		// DrawRequest = false;		// �O���[�o���ϐ�����Ȃ��ă��[�J���ł����������������Ă�

		// ���W���牽�̃u���b�N���𒲂ׂ�
		int block_data = CheckBlockdata(GimmickDescription_x, GimmickDescription_y);


		// �u���b�N�f�[�^��0(��)or�ǃu���b�N(1)�������ꍇ�N�[���^�C����0�ɂ��ďI���
		if (block_data == 0 || block_data == 1)
		{
			GimmickDescriptionCool = 0;
		}
		else
		{
			// �O��g���Ă���(1�����\�������Ȃ��̂ŁA��x�S�Ă�)�M�~�b�N�����̃G�t�F�N�g������
			DeleteGimmickDescription();

			// �M�~�b�N�����̃G�t�F�N�g���쐬����
			GenerateGimmickDescription(block_data, GimmickDescription_x, GimmickDescription_y);
		}







	}




	if (GimmickDescriptionCool > 0)
		GimmickDescriptionCool--;


	return;
}




GIMMICKDESCRIPTION* GetGimmickDescription(void)
{
	return &g_GimmickDescription[0];
}




// �M�~�b�N�����̉摜�`�b�v�̏ꏊ(sx,sy)��Ԃ�
float CheckGimmickDescriptionChipPos(int block_data, int XorY)
{
	// 1�}�X�̕��ƍ���
	float tx = 0.25f;
	float ty = 0.25f;

	// ����
	float sx = 0.0f;
	float sy = 0.0f;



	switch (block_data)
	{
	case 0:					// ��(�Ȃ�)
		sx = tx * 0;
		sy = ty * 0;
		break;
	case 1:					// �u���b�N(�Ȃ�)
		sx = tx * 0;
		sy = ty * 0;
		break;
	case 2:					// �S�[��
		sx = tx * 1;
		sy = ty * 1;
		break;
	case 3:					// ������
	case 4:					
	case 5:					
	case 6:					
	case 7:					
	case 8:					
	case 9:					
	case 10:					
		sx = tx * 1;
		sy = ty * 0;
		break;
	case 11:					// ���[�v�z�[��
	case 12:
		sx = tx * 3;
		sy = ty * 0;
		break;
	case 13:					// �o���J�[
		sx = tx * 0;
		sy = ty * 1;
		break;
	case 14:					// ��������
		sx = tx * 2;
		sy = ty * 1;
		break;
	case 15:					// ���˔�
		sx = tx * 2;
		sy = ty * 0;
		break;

	default:
		break;
	}



	if (XorY == 0)
		return sx;
	else
		return sy;

}


void GenerateGimmickDescription(int block_data, int x, int y)
{
	// �u���b�N�f�[�^����`�b�v�̂ǂ��̕������g�����𒲂ׂ�
	float tx = 0.25f;					// �G�t�F�N�g��ID����68���M�~�b�N�����̃`�b�v�摜
	float ty = 0.25f;
	float background_sx = tx * 0;		// �ӂ�������UV�l(�w�i)
	float background_sy = ty * 0;
	float text_sx = CheckGimmickDescriptionChipPos(block_data, 0);		// �u���b�N������UV�l
	float text_sy = CheckGimmickDescriptionChipPos(block_data, 1);

	float size_x = 400;
	float size_y = size_x / 1.5f;		// �c���� 1.5:1 (����)	���ڒl�����Ă��������������̂�x�������͂ł����̂Ŋy

	float pos_x = 300.0f;				// �\�����W(�^�񒆂������ɗ���)
	float pos_y = 200.0f;

	for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
	{
		// �g���Ă��Ȃ����̂������Ďg��
		if (g_GimmickDescription[i].isUse == false)
		{
			// ���W�̕ۑ�
			g_GimmickDescription[i].x = x;
			g_GimmickDescription[i].y = y;

			// �ӂ�����(�w�i)
			g_GimmickDescription[i].background_EffectArray =
				SetEffect(68, D3DXVECTOR2(pos_x, pos_y), D3DXVECTOR2(pos_x, pos_y), 0,
					D3DXVECTOR2(0, 0), D3DXVECTOR2(size_x, size_y), 1,
					0.0f, 1.0f, GIMMICKDESCRIPTION_FADEIN, GIMMICKDESCRIPTION_DRAWTIME, GIMMICKDESCRIPTION_FADEOUT, 18,
					0.0f, 0.0f, 0,
					tx, ty, background_sx, background_sy);

			// �e�L�X�g�ƃA�C�R��
			g_GimmickDescription[i].text_EffectArray =
				SetEffect(68, D3DXVECTOR2(pos_x, pos_y), D3DXVECTOR2(pos_x, pos_y), 0,
					D3DXVECTOR2(0, 0), D3DXVECTOR2(size_x, size_y), 1,
					0.0f, 1.0f, GIMMICKDESCRIPTION_FADEIN, GIMMICKDESCRIPTION_DRAWTIME, GIMMICKDESCRIPTION_FADEOUT, 18,
					0.0f, 0.0f, 0,
					tx, ty, text_sx, text_sy);

			// �I�����Ă���u���b�N�̋����\���̌��_(���t�g�g�b�v�ȊO�ŉ��ł���Ă邩�킩��Ȃ��G�G�G�G)
			float pickuporigin_x = GAME_ORIGIN_POINT_X + 80.0f * 1 + 40.0f;
			float pickuporigin_y = GAME_ORIGIN_POINT_Y + 40.0f * 5 + 0.0f;

			CAMERA* p_Camera = GetCamera();
			float slanted_x = pickuporigin_x + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			float slanted_y = pickuporigin_y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
			g_GimmickDescription[i].pickupBlock_EffectArray =
				SetEffect(69, D3DXVECTOR2(slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y), D3DXVECTOR2(slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y), 0,
					D3DXVECTOR2(MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y), D3DXVECTOR2(MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y), 0,
					0.0f, 1.0f, GIMMICKDESCRIPTION_FADEIN, GIMMICKDESCRIPTION_DRAWTIME, GIMMICKDESCRIPTION_FADEOUT, 18,
					0.0f, 0.0f, 0,
					1.0f, 1.0f, 0.0f, 0.0f);


			// ��������Ă���̎��Ԃ̐ݒ�
			g_GimmickDescription[i].GeneratedTime = 0;

			g_GimmickDescription[i].isUse = true;

			return;		// 1�����������̂ŏI���
		}
	}

	exit(40);		// �S�Ďg���Ă�����G���[
}



// �M�~�b�N�����̍��o�Ă邷�ׂĂ̂��̂��t�F�[�h�A�E�g�ŏ���(���̏����̌�ɐV�������̂𐶐�������Ζ��Ȃ�)
void DeleteGimmickDescription()
{
	for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
	{
		// �g���Ă�����̂̒�����T��
		if (g_GimmickDescription[i].isUse == true)
		{
			// ����-1�������Ă�����ŏ��̓ǂݍ��݂Ƃ��Ȃ̂ŏ�����Ƃ����s�����ɏI���
			if (g_GimmickDescription[i].background_EffectArray == -1)
				return;

			// now_count���������ď����悤�ɂ���B���������������Ă��ԂȂ�Ȃɂ����Ȃ�
			int now = GetEffectnow_count(g_GimmickDescription[i].background_EffectArray);
			if (now > GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME)
				return;

			// �ӂ�����(�w�i)
			ChangeEffectCount(g_GimmickDescription[i].background_EffectArray, GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME);

			// �e�L�X�g�ƃA�C�R��
			ChangeEffectCount(g_GimmickDescription[i].text_EffectArray, GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME);

			// �����\��
			ChangeEffectCount(g_GimmickDescription[i].pickupBlock_EffectArray, GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME);


			// ��������Ă���̎��Ԃ̐ݒ�
			g_GimmickDescription[i].GeneratedTime = GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME;
		}
	}


}

// �����\���̃J�����ړ��ɂ��X�V
void GimmickDescriptionPickupUpdata(int i)
{
	CAMERA* p_Camera = GetCamera();

	// �O�񂩂�J�����������Ă��邩�ǂ����A�����Ă�������s����
	if (CameraPosChanged() == true)
	{
		// �I�����Ă���u���b�N�̋����\���̌��_(���t�g�g�b�v�ȊO�ŉ��ł���Ă邩�킩��Ȃ��G�G�G�G)
		//float pickuporigin_x = GAME_ORIGIN_POINT_X + 80.0f * 1 + 40.0f;
		//float pickuporigin_y = GAME_ORIGIN_POINT_Y + 40.0f * 5 + 0.0f;

		float pickuporigin_x = GAME_ORIGIN_POINT_X + 80.0f * 0 + 40.0f;
		float pickuporigin_y = GAME_ORIGIN_POINT_Y - 40.0f * 4 + 0.0f;

		// �J�����ړ��ɂ��s�b�N�A�b�v�����̍X�V
		float newpos_x = pickuporigin_x + g_GimmickDescription[i].x * (DRAW_MAP_CHIP_SIZE_X / 2) - g_GimmickDescription[i].y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
		float newpos_y = pickuporigin_y + g_GimmickDescription[i].y * (DRAW_MAP_CHIP_SIZE_Y / 2) + g_GimmickDescription[i].x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

		ChangeEffectPos(g_GimmickDescription[i].pickupBlock_EffectArray, newpos_x, newpos_y);
	}
}