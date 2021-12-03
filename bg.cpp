//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : 
//
//=============================================================================
#include "bg.h"
#include "texture.h"
#include "sprite.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "bullet.h"
#include "camera.h"
#include "predictionbullet.h"
#include "placement.h"
#include "gimmick_description.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
struct MAP_DATA_T
{
	D3DXVECTOR2 uv;		//UV�l
	int			stop;	//�N���\�t���O(1�͐i���֎~)

};

MAP_DATA_T g_MapInfo[23] =
{
	{ {0.25f , 0.0f}, 0},//�Ȃɂ��Ȃ�		   0
	{ {0.125f, 0.125f}, 1},//block			   1
	{ {0.375f, 0.125f}, 1},//goal			   2
	{ {0.625f, 0.125f}, 1},//speedup��		   3
	{ {0.625f, 0.25f}, 1},//speedup��		   4
	{ {0.625f, 0.375f}, 1},//speedup�E		   5
	{ {0.625f, 0.5f}, 1},//speedup��	       6
	{ {0.875f, 0.25f}, 1},//speedup�E��		   7 
	{ {0.875f, 0.375f}, 1},//speedup�E��	   8
	{ {0.75f , 0.375f}, 1},//speedup����	   9
	{ {0.75f , 0.25f}, 1},//speedup����		   10
	{ {0.25f , 0.125f}, 1},//warp			   11
	{ {0.25f , 0.125f}, 1},//warp			   12
	{ {0.75f , 0.0f}, 1},//bunker			   13
	{ {0.75f , 0.125f}, 1},//switch			   14
	{ {0.5f  , 0.125f}, 1},//hansya			   15
	{ {0.5f  , 0.125f}, 1},//�j�i�X�C�b�`)     16 ���݂܂���摜�����ɍ��܂�
	{ {0.75f  , 0.125f}, 1},//�j�̌�?          17 (hansya)
	{ {0.875f, 0.125f}, 1},//�X�C�b�`��������  18 (block)
	{ {0.75f, 0.5f}, 1},//������u���b�N       19 (block)
	{ {0.875f , 0.5f}, 0},//������u���b�N�̏� 20
	{ {0.0f , 0.25f}, 0},//���񂾂�����鏰    21
	{ {0.125f , 0.25f}, 1},//��������̏�      22
};


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int g_map_base[MAP_Y][MAP_X] = {
	//�}�b�v�O
	{0,0,0,2,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	////�}�b�v�P
	//{0,0,0,0,0,1,0,0,0,0},
	//{0,0,0,0,0,1,0,0,0,0},
	//{0,0,0,0,0,1,0,0,0,0},
	//{1,1,1,1,1,1,1,1,1,1},
	//{0,0,0,0,0,1,0,0,0,0},
	//{0,0,0,0,0,1,0,0,0,0},
	//{0,0,0,0,0,1,0,0,0,0},
};

int g_map_obj[MAP_Y][MAP_X] = {
	//�}�b�v�O
		{1,1,1,1,1,1,2, 1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,3,0,0,0, 0,3,3,3,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0, 0,0,0,0,3,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,6,6,6,0,0,0, 0,0,0,0,0,5,1},
		{1,1,1,1,1,1,1, 1,1,1,1,1,1,1}

	////�}�b�v�P
	//{0,0,0,0,0,0,0,0,0,0},
	//{0,0,0,0,0,0,0,0,0,0},
	//{0,0,0,0,1,0,1,0,0,0},
	//{0,0,0,0,0,0,0,0,0,0},
	//{0,0,0,0,1,0,1,0,0,0},
	//{0,0,0,0,0,0,0,0,0,0},
	//{0,0,0,0,0,0,0,0,0,0},
};

//�}�b�v�̓����蔻��p�f�[�^
int g_map_hitchk[2][MAP_Y][MAP_X] =
{
	{//�}�b�v�O
		{1,1,1,1,1,1,2, 1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,3,0,0,0, 0,3,3,3,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0, 0,0,0,0,3,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,6,6,6,0,0,0, 0,0,0,0,0,5,1},
		{1,1,1,1,1,1,1, 1,1,1,1,1,1,1}
	},
	//{//�}�b�v�P
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,1,0,1,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,1,0,1,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//},
};


static int g_Ground = 0;		// �w�i�p�e�N�X�`�����
static int tex_mapchip_3d = 0;		// �w�i�p�e�N�X�`�����

static int tex_floor = 0;		// �w�i�p�e�N�X�`�����
static int tex_floor_mozinasi = 0;		// �w�i�p�e�N�X�`�����
static int tex_floor_huchinasi = 0;		// �w�i�p�e�N�X�`�����

static int tex_base_wall = 0;		// �w�i�p�e�N�X�`�����
static int tex_base_wall_center = 0;		// �w�i�p�e�N�X�`�����
static int tex_base_wall_left = 0;		// �w�i�p�e�N�X�`�����
static int tex_base_wall_right = 0;		// �w�i�p�e�N�X�`�����



static int g_CurrentPos = 0;	// ���݂̃}�b�v���W

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBG(void)
{
	//g_Ground = LoadTexture("data/TEXTURE/basechip.png");
	g_Ground = LoadTexture("data/TEXTURE/game/above/basechip_test.png");
	tex_mapchip_3d = LoadTexture("data/TEXTURE/game/side/mapchip_3d.png");

	tex_floor = LoadTexture("data/TEXTURE/game/side/floor.png");
	tex_floor_mozinasi = LoadTexture("data/TEXTURE/game/side/floor_mozinasi.png");
	tex_floor_huchinasi = LoadTexture("data/TEXTURE/game/side/floor_huchinasi.png");

	tex_base_wall = LoadTexture("data/TEXTURE/game/side/base_wall.png");
	tex_base_wall_center = LoadTexture("data/TEXTURE/game/side/base_wall_center.png");
	tex_base_wall_left = LoadTexture("data/TEXTURE/game/side/base_wall_left.png");
	tex_base_wall_right = LoadTexture("data/TEXTURE/game/side/base_wall_right.png");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{
	UnloadTexture("data/TEXTURE/game/above/basechip_test.png");
	UnloadTexture("data/TEXTURE/game/side/mapchip_3d.png");
	UnloadTexture("data/TEXTURE/game/side/floor.png");
	UnloadTexture("data/TEXTURE/game/side/floor_mozinasi.png");
	UnloadTexture("data/TEXTURE/game/side/floor_huchinasi.png");
	UnloadTexture("data/TEXTURE/game/side/base_wall.png");
	UnloadTexture("data/TEXTURE/game/side/base_wall_center.png");
	UnloadTexture("data/TEXTURE/game/side/base_wall_left.png");
	UnloadTexture("data/TEXTURE/game/side/base_wall_right.png");

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	STAGEDATA* p_Stagedata = GetStagedata();
	CAMERA* p_Camera = GetCamera();

	//�}�E�X�̍��W���擾
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();

	float offset_y;

	if (g_CurrentPos == 0)
		offset_y = 0.0f;
	else
		offset_y = -560.0f;

	int asdddddd = 0;

	//���C���[�O�̕\��
	for (int x = 0; x < MAP_X + 1; x++)
	{
		for(int y = 0; y < MAP_Y + 1; y++)
		{

			float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

			// �e�X�g�p��3��ނ̃e�N�X�`��
			// tex_floor
			// tex_floor_mozinasi
			// tex_floor_huchinasi
			// tex_base_wall

			if (x < MAP_X && y < MAP_Y)
			{
				// ���p�}�ł̏��̕`��
				DrawSpriteLeftTop(tex_floor_huchinasi, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
				// DrawSpriteColorRotate(tex_floor_huchinasi, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);


				// �ォ�王�_�B���܂ł�
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);

			}


			//// ��O(�����Ă鑤��)�̕ǂ̕`��
			//if (x == MAP_X || y == MAP_Y)
			//{
			//	// tex_base_wall
			//	// tex_base_wall_center
			//	// tex_base_wall_left
			//	// tex_base_wall_right

			//	// �^��	(x == MAP_X && y == MAP_Y)		// ���[	(x == 0 && y == MAP_Y)		// �E�[	(x == MAP_X && y == 0)		// ���S��
			//	if (x == MAP_X && y == MAP_Y)
			//		DrawSpriteLeftTop(tex_base_wall_center, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			//	else if (x == 0 && y == MAP_Y)
			//		DrawSpriteLeftTop(tex_base_wall_left, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			//	else if (x == MAP_X && y == 0)
			//		DrawSpriteLeftTop(tex_base_wall_right, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			//	else
			//		DrawSpriteLeftTop(tex_base_wall, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			//}

		

			//switch (p_Stagedata->maparray[y][x])
			//{
			//case 0://����
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 1://��
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 2://�S�[��
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 3://����
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 4://���[�v
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 5://���[�v
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 6://��
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 7://switch
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 8://hansya
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//default:
			//	exit(4);			// �ӂ������ɗ��邱�Ƃ͂Ȃ��̂ŃG���[�Ƃ��ċ������Ă���
			//						// ���̔w�i�I�u�W�F�N�g�̐ݒ�����Ă��Ȃ��ƁAcase10�Ƃ�11�Ƃ���ݒ肵�Ă����f����Ȃ��B
			//	break;
			//}
		}
	}


	// �Q�b�^�[�Ń|�C���^���󂯎��
	PLAYER		*p_player		 = GetPlayer();
	BULLET		*p_bullet	 	 = GetBullet();
	PREDICTION  * p_Prediction	 = GetPrediction();
	GIMMICKDESCRIPTION* p_GimmickDescription = GetGimmickDescription();


	// �u���b�N�̐F�̐ݒ�(���Z�b�g)		���ԓI��(0,0)�͓����x�͕ς����Ȃ��B���ǖ��Ȃ��B
	D3DXCOLOR color[10 * MAP_Y + MAP_X];
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			// �F�f�[�^�̃��Z�b�g�B
			color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	// �w�i�I�u�W�F�N�g�̕\��
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			MAP_DATA_T mapchip;
			mapchip = g_MapInfo[p_Stagedata->maparray[y][x]];

			// �}�b�v�̃f�[�^��0�̏ꍇ�����\�����Ȃ����v�Z�����Ȃ��B
			if (p_Stagedata->maparray[y][x] != 0)
			{
				// �F(�����x�̏�����)
				color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
				float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;



				// �v���C���[����ɂ��邩�̌����Ƃ��̎��u���b�N�𓧖��ɂ��鏈��
				for (int i = 0; i < PLAYER_MAX; i++)
				{
					if (p_player[i].use)
					{
						// �}�b�v�ł̍��W�ɕϊ�����
						D3DXVECTOR2 mappos = PosToMappos(p_player[i].pos);
						// �ϊ��������W�̏����_��؂�̂Ă�
						int mappos_x = mappos.x;
						int mappos_y = mappos.y;

						// �u���b�N�̎���Ƀv���C���[�������ꍇ�����x��������
						if (x - 1 == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
					}
				}
				// �o���b�g������ɂ��邩�̌����Ƃ��̎��u���b�N�𓧖��ɂ��鏈��
				for (int i = 0; i < BULLET_MAX; i++)
				{
					if (p_bullet[i].use)
					{
						// �}�b�v�ł̍��W�ɕϊ�����
						D3DXVECTOR2 mappos = PosToMappos(p_bullet[i].pos);
						// �ϊ��������W�̏����_��؂�̂Ă�
						int mappos_x = mappos.x;
						int mappos_y = mappos.y;

						// �u���b�N�̎���ɒe�������ꍇ�����x��������
						if (x - 1 == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
					}
				}
				// �����\��������ɂ��邩�̌����Ƃ��̎��u���b�N�𓧖��ɂ��鏈��
				for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
				{
					if (p_GimmickDescription[i].isUse)
					{
						// �}�b�v�ł̍��W�ɕϊ�����
						int mappos_x = p_GimmickDescription[i].x;
						int mappos_y = p_GimmickDescription[i].y;

						// �u���b�N�̎���ɋ����\���������ꍇ�����x��������
						if (x - 1 == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
					}
				}

				// ���ȊO�̃u���b�N�̕`��
				// �Ƃ����������_
				DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f, color[10 * y + x]);

				// ���܂ł̏ォ��̎��_
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
			}

			// �v���C���[�̕\���A�\�������厖
			for (int i = 0; i < PLAYER_MAX; i++)
			{
				if (p_player[i].use)
				{
					// �}�b�v�ł̍��W�ɕϊ�����
					D3DXVECTOR2 mappos = PosToMappos(p_player[i].pos);
					// �ϊ��������W�̏����_��؂�̂Ă�
					int mappos_x = mappos.x;
					int mappos_y = mappos.y;

					// �`�ʂ���^�C�~���O��������`�ʂ���
					if (x == mappos_x && y == mappos_y)
					{
						DrawPlayerSpecifyNum(i);			// i�̃v���C���[���`����邩�ǂ���(�g���Ă邩�ǂ���)�́A�����̊֐��̒��Ō��������B
					}
				}
			}
			// �o���b�g�̕\��
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (p_bullet[i].use)
				{
					// �}�b�v�ł̍��W�ɕϊ�����
					D3DXVECTOR2 mappos = PosToMappos(p_bullet[i].pos);
					// �ϊ��������W�̏����_��؂�̂Ă�
					int mappos_x = mappos.x;
					int mappos_y = mappos.y;

					// �`�ʂ���^�C�~���O��������`�ʂ���
					if (x == mappos_x && y == mappos_y)
					{
						DrawBulletSpecifyNum(i);			// i�̃o���b�g���`����邩�ǂ���(�g���Ă邩�ǂ���)�́A�����̊֐��̒��Ō��������B
					}
				}
			}
			// �\���e�̕\��
			for (int i = 0; i < PREDICTION_MAX; i++)
			{
				if (p_Prediction[i].isUse)
				{
					// �}�b�v�ł̍��W�ɕϊ�����
					D3DXVECTOR2 mappos = PosToMappos(p_Prediction[i].pos);
					// �ϊ��������W�̏����_��؂�̂Ă�
					int mappos_x = mappos.x;
					int mappos_y = mappos.y;

					// �`�ʂ���^�C�~���O��������`�ʂ���
					if (x == mappos_x && y == mappos_y)
					{
						DrawPredictionSpecifyNum(i);			// i�̗\���e���`����邩�ǂ���(�g���Ă邩�ǂ���)�́A�����̊֐��̒��Ō��������B
					}
				}
			}


		

		}
	}
}

int GetMapEnter(D3DXVECTOR2 pos)
{
	STAGEDATA* p_Stagedata = GetStagedata();

	int x, y;
	x = (int)(pos.x / MAP_CHIP_SIZE_X);//���W���}�b�v�`�b�v��̑傫���Ŋ���
	y = (int)(pos.y / MAP_CHIP_SIZE_Y);

	return p_Stagedata->maparray[y][x];
}

void SetCurrentMap(int next)
{
	g_CurrentPos = next;
}

int CheckBlockdata(int BlockX, int BlockY)
{
	//int BlockData = 0;
	//BlockData = g_map_hitchk[0][BlockY][BlockX];
	////BlockData = p_Stagedata->maparray[y][x];

	//return BlockData;

	STAGEDATA* p_Stagedata = GetStagedata();

	int BlockData = 0;
	BlockData = p_Stagedata->maparray[BlockY][BlockX];



	return BlockData;
}

D3DXVECTOR2 PosToMappos(D3DXVECTOR2 pos)
{
	D3DXVECTOR2 mappos;
	mappos.x = pos.x / MAP_CHIP_SIZE_X;
	mappos.y = pos.y / MAP_CHIP_SIZE_Y;

	return mappos;
}

D3DXVECTOR2 MapposToPos(D3DXVECTOR2 mappos)
{
	D3DXVECTOR2 pos;
	pos.x = mappos.x * MAP_CHIP_SIZE_X;
	pos.y = mappos.y * MAP_CHIP_SIZE_Y;

	return pos;
}

// num��min��max�̒l����͂ݏo���ꍇmin��num�ɒ������Ă����
int LimitRange(int num, int min, int max)
{
	if (num < min)
		num = min;
	if (num > max)
		num = max;

	return num;
}



// �v���C���[�z�u�t�F�[�Y�p�ォ�王�_
void DrawBGaboveForPlacement(void)
{
	// �Q�b�^�[�Ń|�C���^���󂯎��
	PLAYER* p_player = GetPlayer();
	BULLET* p_bullet = GetBullet();
	PREDICTION* p_Prediction = GetPrediction();
	STAGEDATA* p_Stagedata = GetStagedata();
	CAMERA* p_Camera = GetCamera();

	// �����̕\��
	for (int x = 0; x < MAP_X + 1; x++)
	{
		for (int y = 0; y < MAP_Y + 1; y++)
		{
			if (x < MAP_X && y < MAP_Y)
			{
				// �ォ�王�_�B���܂ł�
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER, y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			}
		}
	}

	// �w�i�I�u�W�F�N�g�̕\��
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			MAP_DATA_T mapchip;
			mapchip = g_MapInfo[p_Stagedata->maparray[y][x]];

			// �}�b�v�̃f�[�^��0�̏ꍇ�����\�����Ȃ����v�Z�����Ȃ��B
			if (p_Stagedata->maparray[y][x] != 0)
			{
				// ���܂ł̏ォ��̎��_
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER, y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
			}
		}
	}
}


// �v���C���[�z�u�t�F�[�Y�p�����王�_
void DrawBGsideForPlacement(void)
{
	STAGEDATA* p_Stagedata = GetStagedata();
	CAMERA* p_Camera = GetCamera();
	//���C���[�O�̕\��
	for (int x = 0; x < MAP_X + 1; x++)
	{
		for (int y = 0; y < MAP_Y + 1; y++)
		{

			float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

			if (x < MAP_X && y < MAP_Y)
			{
				// ���p�}�ł̏��̕`��
				DrawSpriteLeftTop(tex_floor_huchinasi, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			}
		}
	}


	// �Q�b�^�[�Ń|�C���^���󂯎��
	PLAYER* p_player = GetPlayer();
	BULLET* p_bullet = GetBullet();
	PREDICTION* p_Prediction = GetPrediction();


	// �u���b�N�̐F�̐ݒ�(���Z�b�g)		���ԓI��(0,0)�͓����x�͕ς����Ȃ��B���ǖ��Ȃ��B
	D3DXCOLOR color[10 * MAP_Y + MAP_X];
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			// �F�f�[�^�̃��Z�b�g�B
			color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	// �w�i�I�u�W�F�N�g�̕\��
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			MAP_DATA_T mapchip;
			mapchip = g_MapInfo[p_Stagedata->maparray[y][x]];

			// �}�b�v�̃f�[�^��0�̏ꍇ�����\�����Ȃ����v�Z�����Ȃ��B
			if (p_Stagedata->maparray[y][x] != 0)
			{
				// �F(�����x�̏�����)
				color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
				float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

				// �v���C���[����ɂ��邩�̌����Ƃ��̎��u���b�N�𓧖��ɂ��鏈��
				for (int i = 0; i < PLAYER_MAX; i++)
				{
					if (p_player[i].use)
					{
						// �}�b�v�ł̍��W�ɕϊ�����
						D3DXVECTOR2 mappos = PosToMappos(p_player[i].pos);
						// �ϊ��������W�̏����_��؂�̂Ă�
						int mappos_x = mappos.x;
						int mappos_y = mappos.y;

						// �u���b�N�̎���Ƀv���C���[�������ꍇ�����x��������
						if (x - 1 == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
					}
				}
				// �u���b�N�̕`��
				DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f, color[10 * y + x]);
			}

			// �v���C���[�̕\���A�\�������厖
			for (int i = 0; i < PLAYER_MAX; i++)
			{
				if (p_player[i].use)
				{
					// �}�b�v�ł̍��W�ɕϊ�����
					D3DXVECTOR2 mappos = PosToMappos(p_player[i].pos);
					// �ϊ��������W�̏����_��؂�̂Ă�
					int mappos_x = mappos.x;
					int mappos_y = mappos.y;

					// �`�ʂ���^�C�~���O��������`�ʂ���
					if (x == mappos_x && y == mappos_y)
					{
						DrawPlayerSpecifyNumForPlacement(i);			// i�̃v���C���[���`����邩�ǂ���(�g���Ă邩�ǂ���)�́A�����̊֐��̒��Ō��������B
					}
				}
			}
		}
	}
}


