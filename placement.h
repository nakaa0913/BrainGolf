#pragma once


#define PLACEMENT_MAX	(PLAYER_MAX - 1)


// ���Ɋ���Ă���}�b�v�B�𒆐S�Ɏ����Ă��邽�߂̃}�N��
#define TO_CENTER	((SCREEN_WIDTH / 2) - (MAP_X * MAP_CHIP_SIZE_X / 2))

// �L�[���͂̃N�[���^�C��
#define MOVEKEY_COOLTIME	(6)			// �ړ��L�[�̃N�[���^�C��
#define PUSHKEY_COOLTIME	(20)			// ����Ȃǂ̃L�[�̃N�[���^�C��


struct PLACEMENT
{
	int placement_x;
	int placement_y;

	int UsePlayerArray;

	bool isUse;
};


struct POS
{
	int x;
	int y;
};



void InitPlacement(void);
void UninitPlacement(void);
void UpdatePlacement(void);
void DrawPlacement(void);

PLACEMENT* GetPlacement(void);

void ResetPlacementArray(void);
bool SetPlacementAndPlayer(int x, int y);
bool SamePlacement(int x, int y);
bool DontPlaceForCharacter(int x, int y);
bool DontPlaceForBlock(int x, int y);