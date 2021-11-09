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
	tex_yazirushi = LoadTexture("data/TEXTURE/yazirusi.png");

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_Player[i].texNo = LoadTexture("data/TEXTURE/majo.png");

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


	//������

	// ���́A�t�@�C������ǂݍ���Őݒ肵�Ă���BSetPlayerUseFile�֐�
	//////////SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 100));
	//////////SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 300));
	//////////SetPlayer(D3DXVECTOR2(SCREEN_WIDTH / 2, 500));

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
	BULLET bullet = *GetBullet();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		// �O��̍��W�̕ۑ�
		g_Player[i].nextpos = g_Player[i].pos;

		if (GetKeyboardPress(DIK_UP))
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

		if (GetKeyboardPress(DIK_DOWN))
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

		if (GetKeyboardPress(DIK_LEFT))
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

		if (GetKeyboardPress(DIK_RIGHT))
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

		// pos �� drawpos �ɕϊ�
		g_Player[i].drawpos.x = GAME_ORIGIN_POINT_X + ((g_Player[i].pos.x - DRAW_GAP) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((g_Player[i].pos.y - DRAW_GAP) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2);
		g_Player[i].drawpos.y = GAME_ORIGIN_POINT_Y + ((g_Player[i].pos.y - DRAW_GAP) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((g_Player[i].pos.x - DRAW_GAP) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2);


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
				if (g_Player[i].ConfirmAngle == false)
				{
					// �v���C���[�̊p�x��ς��鏈��,��]�����鏈��
					g_Player[i].angle += 6.0f;
					if (g_Player[i].angle > 360.0f)
						g_Player[i].angle = 0.0f;
					g_Player[i].direction = 0;
					if (GetKeyboardTrigger(DIK_SPACE))
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

					if (GetKeyboardTrigger(DIK_SPACE) && g_Player[i].ConfirmCooltime < 0)
					{
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
				float directionUV = 0.0f + 0.25f * g_Player[i].direction;

				float rot = AngleToRot(g_Player[i].angle);


				// ���̕`��
				if (g_Player[i].have == true)
				{
					// ShotPower�ɂ��{��
					float ShotBairitu = 0.5f + (g_Player[i].ShotPower / 100.0f);

					DrawSpriteColorRotate(tex_yazirushi, g_Player[i].drawpos.x, g_Player[i].drawpos.y, 500.0f * ShotBairitu, 500.0f * ShotBairitu,
						0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), -rot);
				}

				//DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].w, g_Player[i].h,
				//	g_Player[i].animeptn2 * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

				DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].drawpos.x, g_Player[i].drawpos.y, g_Player[i].w, g_Player[i].h,
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

				//DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
				//	g_Player[i].animeptn2 * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);

				DrawSpriteColorRotate(g_Player[i].texNo, g_Player[i].pos.x, g_Player[i].pos.y, g_Player[i].w, g_Player[i].h,
					g_AnimePtn * 0.33333f, directionUV, 0.3333f, 0.25f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			}
		}
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