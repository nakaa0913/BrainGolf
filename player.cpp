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
#include "FileDataManagement.h"
#include "camera.h"
#include "predictionbullet.h"
#include "gamedata.h"
#include "keyboard.h"
#include "placement.h"

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

static int tex_yazirushi = 0;

static float g_CharaUV = 0.0f;
static int g_AnimePtn = 0;
static int g_AnimeSpd = 0;
static int g_AnimeWaitFrame = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	//�e�N�X�`���ǂݍ���


	//
	g_ShotSENo = LoadSound("data/SE/shot000.wav");
	tex_yazirushi = LoadTexture("data/TEXTURE/game/player/yazirusi.png");

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_Player[i].texNo = LoadTexture("data/TEXTURE/game/player/majo.png");

		if(i == 0)
			g_Player[i].texNo = LoadTexture("data/TEXTURE/game/player/majo2.png");

		g_Player[i].pos.x = SCREEN_WIDTH / 2;
		g_Player[i].pos.y = 440;
		g_Player[i].nextpos = g_Player[i].pos;
		g_Player[i].w = PLAYER_W;
		g_Player[i].h = PLAYER_H;
		g_Player[i].use = false;


		g_Player[i].drawpos = g_Player[i].pos;
		g_Player[i].drawsize = D3DXVECTOR2(g_Player[i].w, g_Player[i].h);


		g_Player[i].act = 0;
		g_Player[i].direction = 0;
		g_Player[i].have = false;
		g_Player[i].catchwait = 0;
		g_Player[i].angle = 0.0f;
		g_Player[i].ShotPower = 0;
		g_Player[i].ConfirmAngle = false;
		g_Player[i].ConfirmCooltime = 10;

		for (int num = 0; num < ORDER_MAX; num++)
		{
			g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[num] = -1;
			g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[num] = -1;
		}
		g_Player[i].move_around = false;
		g_Player[i].move_speed = PLAYER_MOVE_SPEED;
		g_Player[i].now_array_num = 0;
		g_Player[i].order_max_num = 0;




	}

	g_Player[0].have = true;



	// �v���C���[�z�u�t�F�[�Y�Ŕz�u�������̂�ǂݍ���Ŕz�u����
	PLACEMENT* p_Placement = GetPlacement();

	for (int i = 0; i < PLACEMENT_MAX; i++)
	{
		if (p_Placement[i].isUse)
		{
			SetPlayerUseMapPos(p_Placement[i].placement_x, p_Placement[i].placement_y);
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	UnloadTexture("data/TEXTURE/game/player/yazirusi.png");
	UnloadTexture("data/TEXTURE/game/player/majo.png");
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	BULLET* bullet = GetBullet();
	CAMERA* p_Camera = GetCamera();
	GAMEDATA* p_Gamedata = GetGamedata();

	// �N����l�ł������Ă����Ԃ��ǂ���
	bool now_have = false;

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		// �O��̍��W�̕ۑ�
		g_Player[i].nextpos = g_Player[i].pos;

		//��
		if (Keyboard_IsKeyDown(KK_UP))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x, g_Player[i].pos.y - 3.0f)) != 1)
				g_Player[i].nextpos.y -= 3.0f;

			g_Player[i].direction = 3;
			//g_CharaUV = 0.75f;

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

		//��
		if (Keyboard_IsKeyDown(KK_DOWN))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x, g_Player[i].pos.y + 3.0f)) != 1)
				g_Player[i].nextpos.y += 3.0f;

			g_Player[i].direction = 0;
			//g_CharaUV = 0.0f;

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

		//��
		if (Keyboard_IsKeyDown(KK_LEFT))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x - 3.0f, g_Player[i].pos.y)) != 1)
				g_Player[i].nextpos.x -= 3.0f;

			g_Player[i].direction = 1;
			//g_CharaUV = 0.25f;

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
		

		//�E
		if (Keyboard_IsKeyDown(KK_RIGHT))
		{
			if (GetMapEnter(D3DXVECTOR2(g_Player[i].pos.x + 3.0f, g_Player[i].pos.y)) != 1)
				g_Player[i].nextpos.x += 3.0f;

			g_Player[i].direction = 2;
			//g_CharaUV = 0.5f;

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



		// �{�[���������Ă��Ȃ��āA�����ړ�������ꍇ�̏����B
		if (g_Player[i].have == false && g_Player[i].move_around == true)
		{
			for (int array_num = 0; array_num < g_Player[i].order_max_num; array_num++)
			{
				// ���z��̉��Ԗڂ̈ړ������Ă��邩���������Ă���(��F�z���0�Ԗڂ̈ړ������Ă����)
				if (g_Player[i].now_array_num == array_num)
				{
					// ���̔z��̔ԍ��𕪂���₷�����Ă���
					int next_array = g_Player[i].now_array_num + 1;
					if (next_array >= g_Player[i].order_max_num)
						next_array = 0;

					// �ǂ�����ture�ɂȂ����玟�̔z��̈ړ���
					bool	move_end_x = false;
					bool	move_end_y = false;

					// ���ۂ̈ړ�����
					// �������ɐi�ނ�������ɐi�ނ�
					if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[array_num] < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array])
					{
						// �������ɐi�ޏ���(+)
						g_Player[i].nextpos.y += g_Player[i].move_speed;
						// �ړ������̏����B
						if (g_Player[i].nextpos.y > g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2))
						{
							g_Player[i].nextpos.y = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);
							move_end_y = true;
						}
					}
					else if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[array_num] > g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array])
					{
						// ������ɐi�ޏ���(-)
						g_Player[i].nextpos.y -= g_Player[i].move_speed;
						// �ړ������̏����B
						if (g_Player[i].nextpos.y < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2))
						{
							g_Player[i].nextpos.y = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[next_array] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);
							move_end_y = true;
						}
					}
					else
					{
						// == �̏ꍇ
						move_end_y = true;
					}
					// �E�����ɐi�ނ��������ɐi�ނ�
					if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[array_num] < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array])
					{
						// �E�����ɐi�ޏ���(+)
						g_Player[i].nextpos.x += g_Player[i].move_speed;
						//�ړ������̏����B
						if (g_Player[i].nextpos.x > g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2))
						{
							g_Player[i].nextpos.x = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
							move_end_x = true;
						}
					}
					else if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[array_num] > g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array])
					{
						// �������ɐi�ޏ���(-)
						g_Player[i].nextpos.x -= g_Player[i].move_speed;
						// �ړ������̏����B
						if (g_Player[i].nextpos.x < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2))
						{
							g_Player[i].nextpos.x = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[next_array] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
							move_end_x = true;
						}
					}
					else
					{
						// == �̏ꍇ
						move_end_x = true;
					}

					if (move_end_x && move_end_y)
					{
						g_Player[i].now_array_num = next_array;
					}

					break;

				}
			}
		}

		// nextpos(�v�Z�p�̃|�W�V����)��pos(�����Ƃ����|�W�V����)�ɓK�p
		g_Player[i].pos = g_Player[i].nextpos;

		// pos �� drawpos �ɕϊ�		DRAW_GAP �́A�ォ�猩�����̕`�ʂł̃}�b�v�̕`�ʂ̓��t�g�g�b�v�ŁA�v���C���[�͂ǐ^�񒆂ł���Ă邩��A���̂���B
		g_Player[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Player[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Player[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
		g_Player[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Player[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Player[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
		g_Player[i].drawsize.x = g_Player[i].w * p_Camera->magnification;
		g_Player[i].drawsize.y = g_Player[i].h * p_Camera->magnification;


		int dffs = 5;



		//if (g_Player[i].have == false && g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[1] != -1) {

		//	//�����A�j���[�V����
		//	if (g_Player[i].animewaitframe2 > 10)
		//	{
		//		if (g_Player[i].animeptn2 > 2)
		//			g_Player[i].animeptn2 = 0;

		//		g_Player[i].animewaitframe2 = 0;
		//	}
		//	g_Player[i].animewaitframe2++;

		//	if (g_Player[i].roundtrip_x == 0) {
		//		if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[1] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) < g_Player[i].pos.x) {
		//			g_Player[i].pos.x -= 1.0f;
		//			g_Player[i].direction = 1;

		//			if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[1] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) >= g_Player[i].pos.x) {
		//				g_Player[i].roundtrip_x = 1;
		//			}
		//		}
		//	}

		//	if (g_Player[i].roundtrip_y == 0) {
		//		if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[1] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) < g_Player[i].pos.y) {
		//			g_Player[i].pos.y -= 1.0f;
		//			g_Player[i].direction = 1;

		//			if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[1] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2) >= g_Player[i].pos.y) {
		//				g_Player[i].roundtrip_y = 1;
		//			}
		//		}
		//	}

		//	if (g_Player[i].roundtrip_x == 1) {
		//		if (g_Player[i].pos.x < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2)) {
		//			g_Player[i].pos.x += 1.0f;
		//			g_Player[i].direction = 2;

		//			if (g_Player[i].pos.x >= g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2)) {
		//				g_Player[i].roundtrip_x = 0;
		//			}
		//		}
		//	}

		//	if (g_Player[i].roundtrip_y == 1) {
		//		if (g_Player[i].pos.y < g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2)) {
		//			g_Player[i].pos.y += 1.0f;
		//			g_Player[i].direction = 2;

		//			if (g_Player[i].pos.y >= g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2)) {
		//				g_Player[i].roundtrip_y = 0;
		//			}
		//		}
		//	}
		//}


			////�}�b�v1�֐؂�ւ���
			//if (GetKeyboardTrigger(DIK_L))
			//{
			//	SetCurrentMap(1);
			//}
			////�}�b�v0�֐؂�ւ���
			//if (GetKeyboardTrigger(DIK_K))
			//{
			//	SetCurrentMap(0);
			//}


		// �e����
		if (g_Player[i].have == true)
		{
			now_have = true;
			if (g_Player[i].ConfirmAngle == false)
			{
				// �v���C���[�̊p�x��ς��鏈��,��]�����鏈��
				g_Player[i].angle += 6.0f;
				if (g_Player[i].angle > 360.0f)
					g_Player[i].angle = 0.0f;
				g_Player[i].direction = 0;
				if (Keyboard_IsKeyDown(KK_SPACE))
				{
					g_Player[i].ConfirmAngle = true;
				}
			}

			if (g_Player[i].ConfirmAngle == true)
			{
				// �N�[���^�C���̌���
				if (g_Player[i].ConfirmCooltime >= 0)
					g_Player[i].ConfirmCooltime--;

				g_Player[i].direction = 0;
				// ShotPower�̕ϓ��̐ݒ�
				g_Player[i].ShotPower++;
				if (g_Player[i].ShotPower > 100)
					g_Player[i].ShotPower = 0;

				// �\��������score�Ɠ�������
				SetShotPower(g_Player[i].ShotPower);

				if (Keyboard_IsKeyDown(KK_ENTER) && g_Player[i].ConfirmCooltime < 0)
				{
					// �p�X�����񐔂𑝂₷
					p_Gamedata->pass_count++;
					
					g_Player[i].catchwait = 60;
					g_Player[i].have = false;

					PlaySound(g_ShotSENo, 0);

					SetVolume(g_ShotSENo, 0.1f);

					D3DXVECTOR2 pos = g_Player[i].pos;
					SetBullet(pos, g_Player[i].angle, g_Player[i].ShotPower);
				}

			}
		}

		if (g_Player[i].catchwait > 0)
			g_Player[i].catchwait--;
	}

	if (now_have == true)
	{
		PredictionUseTrue();
	}
	else
	{
		PredictionUseFalse();
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		//if (g_Player[i].use == true)
		//{
		//	float directionUV = 0.0f + 0.25f * g_Player[i].direction;

		//	float rot = AngleToRot(g_Player[i].angle);


		//	// ���̕`��
		//	if (g_Player[i].have == true)
		//	{
		//		// ShotPower�ɂ��{��
		//		float ShotBairitu = 0.5f + (g_Player[i].ShotPower / 100.0f);

		//		DrawSpriteColorRotate(tex_yazirushi, g_Player[i].drawpos.x, g_Player[i].drawpos.y, 500.0f * ShotBairitu, 500.0f * ShotBairitu,
		//			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
		//	}

		//	//DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].w, g_Player[i].h,
		//	//	g_Player[i].animeptn2 * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

		//	DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].w, g_Player[i].h,
		//		g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

		//	// �ォ�猩�����̕\��
		//	// ���̕`��
		//	if (g_Player[i].have == true)
		//	{
		//		// ShotPower�ɂ��{��
		//		float ShotBairitu = 0.5f + (g_Player[i].ShotPower / 100.0f);

		//		DrawSpriteColorRotate(tex_yazirushi, g_Player[i].pos.x, g_Player[i].pos.y, 500.0f * ShotBairitu, 500.0f * ShotBairitu,
		//			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
		//	}

		//	//DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
		//	//	g_Player[i].animeptn2 * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

		//	DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
		//		g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		//}
	}
}


void DrawPlayerSpecifyNum(int i)
{
	CAMERA* p_Camera = GetCamera();

	float directionUV = 0.0f + 0.25f * g_Player[i].direction;

	float rot = AngleToRot(g_Player[i].angle);


	////////// �Ƃ��������ł̖��̕`��
	////////if (g_Player[i].have == true)
	////////{
	////////	// ShotPower�ɂ��{��
	////////	float ShotBairitu = 0.5f + (g_Player[i].ShotPower / 100.0f);

	////////	DrawSpriteColorRotate(tex_yazirushi, g_Player[i].drawpos.x, g_Player[i].drawpos.y, 500.0f * ShotBairitu * p_Camera->magnification, 500.0f * ShotBairitu * p_Camera->magnification,
	////////		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
	////////}



	// �Ƃ��������ł̃v���C���[�̕\��
	DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].drawsize.x, g_Player[i].drawsize.y,
		g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

	// �ォ�猩�����̕\��
	// ���̕`��
	if (g_Player[i].have == true)
	{
		// ShotPower�ɂ��{��
		float ShotBairitu = 0.5f + (g_Player[i].ShotPower / 100.0f);

		DrawSpriteColorRotate(tex_yazirushi, g_Player[i].pos.x, g_Player[i].pos.y, 500.0f * ShotBairitu, 500.0f * ShotBairitu,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
	}

	DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
		g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

}

// �v���C���[�z�u�̎��̕`��
void DrawPlayerForPlacement(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if(g_Player[i].use == true)
		{
			float directionUV = 0.0f;		// �������̏�Ԃŕ\��

			DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x + TO_CENTER, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
				g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		}
	}
}


void DrawPlayerSpecifyNumForPlacement(int i)
{
	CAMERA* p_Camera = GetCamera();

	float directionUV = 0.0f + 0.25f * g_Player[i].direction;

	float rot = AngleToRot(g_Player[i].angle);

	// pos �� drawpos �ɕϊ�		DRAW_GAP �́A�ォ�猩�����̕`�ʂł̃}�b�v�̕`�ʂ̓��t�g�g�b�v�ŁA�v���C���[�͂ǐ^�񒆂ł���Ă邩��A���̂���B
	g_Player[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Player[i].pos.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Player[i].pos.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
	g_Player[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Player[i].pos.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Player[i].pos.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
	g_Player[i].drawsize.x = g_Player[i].w * p_Camera->magnification;
	g_Player[i].drawsize.y = g_Player[i].h * p_Camera->magnification;

	// �Ƃ��������ł̃v���C���[�̕\��
	DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].drawsize.x, g_Player[i].drawsize.y,
		g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

	//DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
	//	g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

}


// ������num�Ԃ̃v���C���[������
void DeletePlayer(int num)
{
	g_Player[num].use = false;

}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
PLAYER* GetPlayer(void)
{
	return &g_Player[0];
}


void SetPlayer(D3DXVECTOR2 pos)
{
	// �������g�p�̃v���C���[�����Ȃ�������ǉ��ł��Ȃ��B
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == false)		// ���g�p��Ԃ̃v���C���[��������
		{
			g_Player[i].use = true;			// �g�p��Ԃ֕ύX����
			g_Player[i].pos = pos;			// ���W���Z�b�g
			g_Player[i].h = PLAYER_H;
			g_Player[i].w = PLAYER_W;

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

void SetPlayerUseMapPos(int mappos_x, int mappos_y)
{
	// �������g�p�̃v���C���[�����Ȃ�������ǉ��ł��Ȃ��B��l���͏����̂�i=1����
	for (int i = 1; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == false)		// ���g�p��Ԃ̃v���C���[��������
		{
			// ���W���Z�b�g		�}�b�v�`�b�v�ł̍��W���炿���Ƃ������W�֕ϊ�
			g_Player[i].pos.x = mappos_x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
			g_Player[i].pos.y = mappos_y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

			g_Player[i].use = true;			// �g�p��Ԃ֕ύX����

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
	return;
}

// �\���̂��|�C���^�ł͂Ȃ����ʂɎ󂯎��ƒ��g�͏㏑���ł��Ȃ��B�Q�Ƃ͂ł���B
void SetPlayerUseFile(MAPCHIP_POS_STRUCT Receive_Mapchip_Pos_Struct, float movespeed)
{
	// �������g�p�̃v���C���[�����Ȃ�������ǉ��ł��Ȃ��B
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == false)		// ���g�p��Ԃ̃v���C���[��������
		{
			// �󂯎�����}�b�v�`�b�v�ł̍��W�Ɖ������鏇�Ԃ�n��
			// �����\���̂̂��̂����炱������Ď󂯎���
			g_Player[i].Mapchip_Pos_Struct = Receive_Mapchip_Pos_Struct;

			// ���W���Z�b�g		�}�b�v�`�b�v�ł̍��W���炿���Ƃ������W�֕ϊ�
			g_Player[i].pos.x = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[0] * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
			g_Player[i].pos.y = g_Player[i].Mapchip_Pos_Struct.mapchip_pos_y[0] * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);

			// �ړ�����p�ł�������ړ����邩�ǂ�����true��
			if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[1] != -1)
				g_Player[i].move_around = true;

			// �����̐ݒ�
			g_Player[i].order_max_num = 0;

			for (int order_num = 0; order_num < ORDER_MAX; order_num++)
			{
				if (g_Player[i].Mapchip_Pos_Struct.mapchip_pos_x[order_num] != -1)
					g_Player[i].order_max_num++;
				else
					break;
			}

			g_Player[i].move_speed = movespeed;

			g_Player[i].use = true;			// �g�p��Ԃ֕ύX����
			g_Player[i].h = PLAYER_H;
			g_Player[i].w = PLAYER_W;

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

// �v���C���[�z�u�t�F�[�Y�ł̃Z�b�g�v���C���[����,�߂�l�łǂ��Ƀv���C���[���Z�b�g��������Ԃ�
int SetPlayerForPlacement(int mappos_x, int mappos_y)
{
	// �������g�p�̃v���C���[�����Ȃ�������ǉ��ł��Ȃ��B��l���͏����̂�i=1����
	for (int i = 1; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == false)		// ���g�p��Ԃ̃v���C���[��������
		{

			// ���W���Z�b�g		�}�b�v�`�b�v�ł̍��W���炿���Ƃ������W�֕ϊ�
			g_Player[i].pos.x = mappos_x * MAP_CHIP_SIZE_X + (MAP_CHIP_SIZE_X / 2);
			g_Player[i].pos.y = mappos_y * MAP_CHIP_SIZE_Y + (MAP_CHIP_SIZE_Y / 2);



			g_Player[i].h = PLAYER_H;
			g_Player[i].w = PLAYER_W;

			g_Player[i].use = true;			// �g�p��Ԃ֕ύX����

			return i;							// 1���Z�b�g�����̂ŏI������
		}
	}
	return -1;
}


// ���ݒe�������Ă���v���C���[��Ԃ��B�����Ă��Ȃ����0
int returnHavePlayer()
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use == true)
		{
			if (g_Player[i].have == true)
				return i;
		}
	}

	return 0;
}