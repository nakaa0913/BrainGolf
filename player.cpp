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
#include "primitive.h"
#include "effect.h"
#include "gimmick_description.h"

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

int	club_pattern;			// �g���N���u(�ł���)0���]����A1���Ƃ�
int club_ChangeCool;		// �N���u�������ւ������̃N�[���^�C��

bool mouseuse = false;

bool pausemouseuse2 = false;

bool pauseclickuse2 = false;	//�|�[�Y��ʂ��J�������ǂ���

int pause_cool2;		// �|�[�Y�؂�ւ��̃N�[���^�C��
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	//�e�N�X�`���ǂݍ���

	pause_cool2 = 0;
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

	club_pattern = 1;		// �g���N���u�̏����ݒ�(�����͂ƂԂ�������Ă������Ƃɂ���)



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
	//�}�E�X�̍��W���擾
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();

	// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
	//int OldStageSelectX = g_StageSelect.select_x;
	//int OldStageSelectY = g_StageSelect.select_y;

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
		if (Keyboard_IsKeyDown(KK_W))
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
		if (Keyboard_IsKeyDown(KK_S))
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
		if (Keyboard_IsKeyDown(KK_A))
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
		if (Keyboard_IsKeyDown(KK_D))
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

		//float drawmosuepos_x = GAME_ORIGIN_POINT_X + ((mouse_pos_X + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((mouse_pos_X - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
		//float drawmosuepos_y = GAME_ORIGIN_POINT_Y + ((mouse_pos_Y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((mouse_pos_Y + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;


		//�|�[�Y�{�^�� 1200 700	300 300
		if (mouse_pos_X > 10.0f && mouse_pos_X < 85.0f && mouse_pos_Y > 15.0f && mouse_pos_Y < 85.0f)
		{
			//g_Pause.selectpush = 0;
			pausemouseuse2 = true;

			// �}�E�X���\���ɂ����Ă����Ԃō��N���b�N��������
			if (pausemouseuse2 && mouse_Lclick)
			{
				//�|�[�Y��ʂ��J��
				pauseclickuse2 = true;
			}
		}

		if (pausemouseuse2 || pauseclickuse2)
		{
			//��ʂ�360���E����������|�[�Y��ʂ����ׂĕ���
			if (mouse_pos_X > 360.0f)
			{
				if (mouse_Lclick)
				{
					pauseclickuse2 = false;
					pausemouseuse2 = false;
					pause_cool2 = 30;
				}
			}
		}

		
			// �e����
			if (g_Player[i].have == true)
			{
				now_have = true;
				if (g_Player[i].ConfirmAngle == false)
				{


					// �v���C���[�̊p�x��ς��鏈��,��]�����鏈�������������߂�
					if (Keyboard_IsKeyDown(KK_LEFT))
					{
						g_Player[i].angle += 3.0f;

						if (g_Player[i].angle > 360.0f)
							g_Player[i].angle = 0.0f;
						g_Player[i].direction = 0;
						mouseuse = false;
					}

					if (Keyboard_IsKeyDown(KK_RIGHT))
					{
						g_Player[i].angle -= 3.0f;

						if (g_Player[i].angle <= 0.0f)
							g_Player[i].angle = 360.0f;
						g_Player[i].direction = 0;
						mouseuse = false;
					}

					// �}�E�X�J�[�\���̏ꏊ�łƂ΂����������߂鏈��
					// mouse_pos_X  mouse_pos_Y
					// �}�E�X�̍��W����ォ�猩�����̍��W���o��
					// ���̍��W�ƃ{�[���������Ă�v���C���[�̍��W��2�_�Ԃ���p�x���o��

					// 2���T���ŏ��X�Ɍ������Ă���








						if (mouse_Rclick)
						{
							mouseuse = true;
						}

						if (mouseuse)
						{
							Float2 more_mousepos = Getmoremousepos();

							// �@�̓_����A���������̃��W�A�����v�Z����
							float mouse_rad = CalculateRadianFrom2Points(g_Player[i].pos.x / MAP_CHIP_SIZE_X, g_Player[i].pos.y / MAP_CHIP_SIZE_Y, more_mousepos.x, more_mousepos.y);
							mouse_rad = InversionYRadian(mouse_rad);
							float mouse_angle = RadianToDegree(mouse_rad);

							g_Player[i].angle = mouse_angle;

							if (g_Player[i].angle <= 0.0f)
								g_Player[i].angle = 360.0f;
							g_Player[i].direction = 0;
						}

						// �N���u�������ς��鏈��
						if (club_ChangeCool <= 0)
						{
							if (Keyboard_IsKeyDown(KK_UP))
							{
								club_pattern--;
								club_ChangeCool = CLUB_CHANGECOOL;
							}
							if (Keyboard_IsKeyDown(KK_DOWN))
							{
								club_pattern++;
								club_ChangeCool = CLUB_CHANGECOOL;
							}
						}

						// �N���u�����ւ��̌��E����
						if (club_pattern < 0)
							club_pattern = 1;
						if (club_pattern > 1)
							club_pattern = 0;

						//�N���u�̎�ނ̕\��
						if (club_pattern == 0)
						{
							SetEffect(71, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 0,
								D3DXVECTOR2(200.0f, 150.0f), D3DXVECTOR2(200.0f, 150.0f), 0,
								0.0f, 1.0f, 0, 1, 0, 0,
								0.0f, 0.0f, 0);
						}
						if (club_pattern == 1)
						{
							SetEffect(72, D3DXVECTOR2(1300.0f, 700.0f), D3DXVECTOR2(1300.0f, 700.0f), 0,
								D3DXVECTOR2(200.0f, 150.0f), D3DXVECTOR2(200.0f, 150.0f), 0,
								0.0f, 1.0f, 0, 1, 0, 0,
								0.0f, 0.0f, 0);
						}
						if (pauseclickuse2 == false && pausemouseuse2 == false)
						{
						if (pause_cool2 <= 0)
						{
							//ENTER�Œe����
							if (Keyboard_IsKeyDown(KK_ENTER) || mouse_Lclick && mouseuse)
							{
								// �p�X�����񐔂𑝂₷
								p_Gamedata->pass_count++;

								g_Player[i].catchwait = 60;
								g_Player[i].have = false;

								PlaySound(g_ShotSENo, 0);

								SetVolume(g_ShotSENo, 0.1f);

								D3DXVECTOR2 pos = g_Player[i].pos;
								SetBullet(pos, g_Player[i].angle, g_Player[i].ShotPower, club_pattern);
							}
						}
				}
			}


		}

		// �N�[���^�C�������炷����
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

	// �N�[���^�C�������炷����(���ꂼ��̂Ղꂢ��[����Ȃ����(for���̊O�ɏ����Ȃ��Ƃ����Ȃ����)
	if (club_ChangeCool > 0)
		club_ChangeCool--;

	//�|�[�Y��ʂ̃N�[���^�C��
	if (pause_cool2 > 0)
		pause_cool2--;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		
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

// �z�u�����v���C���[������(��l���ȊO)
void DeletePlacementPlayer()
{
	for (int i = 1; i < PLAYER_MAX; i++)
	{
		g_Player[i].use = false;
	}
}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
PLAYER* GetPlayer(void)
{
	return &g_Player[0];
}

int GetClubPattern(void)
{
	return club_pattern;
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