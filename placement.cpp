
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "bg.h"
#include "camera.h"
#include "predictionbullet.h"
#include "gamedata.h"
#include "placement.h"
#include "keyboard.h"
#include "mouse.h"
#include "effect.h"
#include "stagedata.h"

/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
int placement_frame_time = 0;

PLACEMENT g_Placement[PLACEMENT_MAX];

POS nowchoice;

int MoveKeyCool = 0;
int PushKeyCool = PUSHKEY_COOLTIME;

int placement_pickup_EffectArray = -1;		// pickup_green�̃G�t�F�N�g�p

bool ViewAbove = true;

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitPlacement(void)
{
	STAGEDATA* p_Stagedata = GetStagedata();

	placement_frame_time = 0;


	//InitPlayer();
	//InitScore();
	//InitBG();
	InitCamera();
	//InitGamedata();

	// ���݂̔z�u�����g���ăv���C���[��z�u����	0�Ԗڂ͎�l�������łɂ���̂Ŗ�������1�Ԗڂ���

	// ��l���ȊO�̃v���C���[������
	DeletePlacementPlayer();
	// �X�e�[�W�ɂ���Ĕz�u�ł���l�����Ⴄ�̂ł����܂œǂݍ���
	for (int i = 0; i < p_Stagedata->NumberofPeople; i++)
	{
		// �ݒ肳��Ă�����V���ɃZ�b�g����
		if (g_Placement[i].isUse)
		{
			g_Placement[i].UsePlayerArray =
				SetPlayerForPlacement(g_Placement[i].placement_x, g_Placement[i].placement_y);
		}
	}

	// �I��ł���Ƃ�����������Ő^�񒆂ɂ���
	nowchoice.x = MAP_X / 2;
	nowchoice.y = MAP_Y / 2;

	MoveKeyCool = MOVEKEY_COOLTIME;
	PushKeyCool = PUSHKEY_COOLTIME;
	ViewAbove = true;


	// placement�ł�1�̑I�𒆂̃G�t�F�N�g�𓮂����Ďg��
	// �I�����Ă���ꏊ�̕\���̎��̌��_�ƂȂ�ꏊ
	float	origin_x = TO_CENTER + (MAP_CHIP_SIZE_X / 2);			    // x�̌��_(0,0��I�����Ă���Ƃ�)
	float	origin_y = MAP_CHIP_SIZE_Y / 2;			    // y�̌��_(0,0��I�����Ă���Ƃ�)
	// �I�����Ă���ꏊ�̕\���̎���1���ꂽ�炱�ꂾ����������Ă��
	float interval_x = MAP_CHIP_SIZE_X;
	float interval_y = MAP_CHIP_SIZE_Y;
	// �G�t�F�N�g���Z�b�g����
	placement_pickup_EffectArray =
		SetEffect(52, D3DXVECTOR2(origin_x + nowchoice.x * interval_x, origin_y + nowchoice.y * interval_y), D3DXVECTOR2(0, 0), 0,
			D3DXVECTOR2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y), D3DXVECTOR2(200.0f, 200.0f), 0,
			1.0f, 1.0f, 0, 999, 0, 0,
			0.0f, 0.0f, 0);


}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitPlacement()
{
	//�������Ƃ͋t���ɏI���������s��
	//UninitGamedata();
	UninitCamera();
	//UninitBG();
	//UninitScore();
	//UninitPlayer();
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdatePlacement(void)
{

	//�}�E�X�̍��W���擾
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouseuse = false;

	// 1�t���[���O�̃|�W�V�����̕ۑ��B���̌�L�[����ȂǂŕύX���������ꍇ�̂݃G�t�F�N�g���X�V������
	int OldnowchoiceX = nowchoice.x;
	int OldnowchoiceY = nowchoice.y;


	// �I�����Ă���ꏊ�̕\���̎��̌��_�ƂȂ�ꏊ
	float	origin_x = TO_CENTER + (MAP_CHIP_SIZE_X / 2);			    // x�̌��_(0,0��I�����Ă���Ƃ�)
	float	origin_y = MAP_CHIP_SIZE_Y / 2;								 // y�̌��_(0,0��I�����Ă���Ƃ�)
	// �I�����Ă���ꏊ�̕\���̎���1���ꂽ�炱�ꂾ����������Ă��
	float interval_x = MAP_CHIP_SIZE_X;
	float interval_y = MAP_CHIP_SIZE_Y;

	// �G���^�[�L�[�ŃQ�[���X�^�[�g
	if ((Keyboard_IsKeyDown(KK_ENTER)) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_GAME);
	}

	if (PushKeyCool <= 0)
	{
		// M�L�[�������ꂽ��}�b�v�\���ؑ�+�ォ�王�_�ł̑�������S�ɖ����ɂ���
		if (Keyboard_IsKeyDown(KK_M))
		{
			ViewAbove = !ViewAbove;
			if(ViewAbove)
				ChangeEffectClarity(placement_pickup_EffectArray, 1.0f);
			else
				ChangeEffectClarity(placement_pickup_EffectArray, 0.0f);
			PushKeyCool = PUSHKEY_COOLTIME;
		}
	}


	if (ViewAbove == true)
	{

		// �L�[���͂ɂ��ړ�
		if (MoveKeyCool <= 0)
		{
			if (Keyboard_IsKeyDown(KK_RIGHT))
			{
				nowchoice.x++;
			}
			if (Keyboard_IsKeyDown(KK_LEFT))
			{
				nowchoice.x--;
			}
			if (Keyboard_IsKeyDown(KK_UP))
			{
				nowchoice.y--;
			}
			if (Keyboard_IsKeyDown(KK_DOWN))
			{
				nowchoice.y++;
			}
		}

		// �}�E�X�̍��W����ǂ̃u���b�N�ɐG��Ă��邩�𒲂ׂ鏈��
		for (int x = 0; x < MAP_X + 1; x++)
		{
			for (int y = 0; y < MAP_Y + 1; y++)
			{
				if (x < MAP_X && y < MAP_Y)
				{
					float block_left  = 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER;
					float block_right = MAP_CHIP_SIZE_X + x * MAP_CHIP_SIZE_X + TO_CENTER;
					float block_up    = 0.0f + y * MAP_CHIP_SIZE_Y;
					float block_down  = MAP_CHIP_SIZE_Y + y * MAP_CHIP_SIZE_Y;

					// �}�E�X�̍��W�������ɂ���Ȃ�
					if (mouse_pos_X > block_left && mouse_pos_X < block_right && mouse_pos_Y > block_up && mouse_pos_Y < block_down)
					{
						nowchoice.x = x;
						nowchoice.y = y;

						break;
					}
				}
			}
		}




		// ���E�l�̏���
		if (nowchoice.x < 0)
			nowchoice.x = MAP_X - 1;
		if (nowchoice.x >= MAP_X)
			nowchoice.x = 0;
		if (nowchoice.y < 0)
			nowchoice.y = MAP_Y - 1;
		if (nowchoice.y >= MAP_Y)
			nowchoice.y = 0;





		// �O����ύX���������ꍇ�̏���
		if (OldnowchoiceX != nowchoice.x || OldnowchoiceY != nowchoice.y)
		{
			// �O�̍��W��ۑ�(�������)���Ď��̍��W���Z�b�g���ă`�F���W�G�t�F�N�g�ōX�V����
			D3DXVECTOR2 oldpos = GetEffectPos(placement_pickup_EffectArray);
			D3DXVECTOR2 nextpos = D3DXVECTOR2(origin_x + interval_x * nowchoice.x, origin_y + interval_y * nowchoice.y);
			ChangeEffect(placement_pickup_EffectArray, 52, D3DXVECTOR2(oldpos.x, oldpos.y), D3DXVECTOR2(nextpos.x, nextpos.y), 1,
				D3DXVECTOR2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y), D3DXVECTOR2(200.0f, 200.0f), 0,
				1.0f, 1.0f, 0, 999, 0, 6,
				0.0f, 0.0f, 0);

			MoveKeyCool = MOVEKEY_COOLTIME;
		}

		// �I�����Ă���Ƃ��낪�u���Ȃ��Ƃ���̏ꍇ�e�N�X�`����ς���
		if (DontPlaceForCharacter(nowchoice.x, nowchoice.y) || 
			DontPlaceForBlock(nowchoice.x, nowchoice.y)		||
			DontPlaceForNumberofPeople()						)
			ChangeEffectTexture(placement_pickup_EffectArray, 53);
		else
			ChangeEffectTexture(placement_pickup_EffectArray, 52);


		// �X�y�[�X�L�[�������ꂽ��v���C���[��z�u����
		if (PushKeyCool <= 0)
		{
			if (Keyboard_IsKeyDown(KK_SPACE) || mouse_Lclick)
			{
				PushKeyCool = PUSHKEY_COOLTIME;
				// �v���C���[�̔z�u����Ƃ��ɔ���Ă��Ȃ���΂��̂܂ܔz�u�A����Ă������菜������
				// SetPlacementAndPlayer�̒��ł���Ƀu���b�N�����������l����������Ŕz�u�ł��Ȃ��Ƃ��̏����B
				if (!SamePlacement(nowchoice.x, nowchoice.y))
					SetPlacementAndPlayer(nowchoice.x, nowchoice.y);
			}
		}


		//// �I�����Ă���ꏊ�̕\���̎��̌��_�ƂȂ�ꏊ
		//float	origin_x = TO_CENTER + (MAP_CHIP_SIZE_X / 2);			    // x�̌��_(0,0��I�����Ă���Ƃ�)
		//float	origin_y = MAP_CHIP_SIZE_Y / 2;			    // y�̌��_(0,0��I�����Ă���Ƃ�)
		//// �I�����Ă���ꏊ�̕\���̎���1���ꂽ�炱�ꂾ����������Ă��
		//float interval_x = MAP_CHIP_SIZE_X;
		//float interval_y = MAP_CHIP_SIZE_Y;

	}

	UpdateCamera();
	//UpdateBG();
	////UpdatePlayer();
	//UpdateScore();

	//UpdateGamedata();

	// �z�u�J�n���Ă���̃t���[�����Ԃ�+1����
	placement_frame_time++;

	// �L�[���̓N�[���^�C���̃J�E���g��������
	if (MoveKeyCool > 0)
		MoveKeyCool--;
	if (PushKeyCool > 0)
		PushKeyCool--;
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawPlacement(void)
{
	// �Ƃ����������_
	DrawBGsideForPlacement();

	// �ォ�王�_
	if (ViewAbove)
	{
		DrawBGaboveForPlacement();
		DrawPlayerForPlacement();
	}

	DrawScore();

}





PLACEMENT* GetPlacement(void)
{
	return &g_Placement[0];
}


// Init�Ƃ͕ʂō\���̂̒��g������������
// �Q�[�����N���A���Ď��̑I���������Ƃ���
// �X�e�[�W�I���ŃX�e�[�W��I�񂾎�	�Ȃǂɂ�����g���ď���������
//�@���j�b�g�ƕ����Ă��闝�R�́A�Q�[���I�[�o�[�ɂȂ������Ȃǂɖ߂��Ă����Ƃ��ɔz�u������������Ȃ��悤�ɂ��邽��
void ResetPlacementArray(void)
{
	for (int i = 0; i < PLACEMENT_MAX; i++)
	{
		g_Placement[i].placement_x = -1;
		g_Placement[i].placement_y = -1;

		g_Placement[i].UsePlayerArray = -1;

		g_Placement[i].isUse = false;
	}
}

// Placement�\���̂ɂŁ[��������Z�b�g�v���C���[���s���B���̍ۂǂ��ɓ����Ă��邩�̏����Ⴄ,�z�u�o������true
bool SetPlacementAndPlayer(int x, int y)
{
	STAGEDATA * p_Stagedata = GetStagedata();

	// ��l�������Đݒu�ł��Ȃ�����,����Ă�����true���Ԃ��Ă���̂ł�������
	if (DontPlaceForCharacter(x, y))
		return false;
	// �u���b�N�������Đݒu�ł��Ȃ�����,����Ă�����true���Ԃ��Ă���̂ł�������
	if(DontPlaceForBlock(x, y))
		return false;

	// �X�e�[�W�ɂ���Ĕz�u�ł���l�����Ⴄ�̂ł����܂łŒT��
	for (int i = 0; i < p_Stagedata->NumberofPeople; i++)
	{
		// �g���Ă��Ȃ����̂���g��
		if (g_Placement[i].isUse == false)
		{
			g_Placement[i].placement_x = x;
			g_Placement[i].placement_y = y;

			g_Placement[i].UsePlayerArray =
				SetPlayerForPlacement(x, y);

			g_Placement[i].isUse = true;

			return true;			// 1�l�Z�b�g�����̂ŏI������
		}
	}

	// �l���������ς��������ꍇfalse��Ԃ�
	return false;
}




// ���Ɏg���Ă���Ƃ���ɂ�����x�z�u���悤�Ƃ�����t�Ƀv���C���[���O�����Ƃ��ł���
bool SamePlacement(int x, int y)
{
	STAGEDATA* p_Stagedata = GetStagedata();

	for (int i = 0; i < p_Stagedata->NumberofPeople; i++)
	{
		if (g_Placement[i].isUse == true)
		{
			if (x == g_Placement[i].placement_x && y == g_Placement[i].placement_y)
			{

				DeletePlayer(g_Placement[i].UsePlayerArray);
				g_Placement[i].isUse = false;

				return true;			// 1�l��菜�����̂ŏI������
			}
		}
	}
	// �����̏ꏊ�ɒN�����Ȃ������ꍇ��菜�����ɏI��
	return false;
}


// ��l�������Đݒu�ł��Ȃ�����,����Ă�����true
bool DontPlaceForCharacter(int x, int y)
{
	PLAYER* p_player = GetPlayer();

	// ������l���Ɣ���Ă���Ȃ�
	if (x == p_player[0].Mapchip_Pos_Struct.mapchip_pos_x[0] && y == p_player[0].Mapchip_Pos_Struct.mapchip_pos_y[0])
		return true;

	return false;
}

// �u���b�N�������Đݒu�ł��Ȃ�����,����Ă�����true
bool DontPlaceForBlock(int x, int y)
{
	STAGEDATA* p_Stagedata = GetStagedata();

	// �����u���b�N�Ɣ���Ă���Ȃ�,0�ȊO�̃u���b�N�Ȃ����Ă��锻��
	if(p_Stagedata->maparray[y][x] != 0 )
		return true;

	return false;
}

// �v���C���[���ő�܂Ŕz�u���Ă����Đݒu�ł��Ȃ�����,�ł��Ȃ��Ȃ�true
bool DontPlaceForNumberofPeople()
{
	STAGEDATA* p_Stagedata = GetStagedata();

	// �����u���b�N�Ɣ���Ă���Ȃ�,0�ȊO�̃u���b�N�Ȃ����Ă��锻��
	for (int i = 0; i < p_Stagedata->NumberofPeople; i++)
	{
		if (g_Placement[i].isUse == false)
		{
			// �ő�z�u�܂ł��Ă��Ȃ��Ȃ�false��Ԃ�
			return false;
		}
	}

	// �����ő�܂Ŕz�u���Ă��Ă���Ȃ�z�u�ł��Ȃ��̂�true��Ԃ�
	return true;

}