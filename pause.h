/*==============================================================================

   ���_�Ǘ�[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SetPause(D3DXVECTOR2 pos);
void GameoverTrue_Pause();
void GoalTrue_Pause();
//PAUSE* GetPause(void);

//#define MAX_RESULT (3)			// �~�b�V�������̍ő�(�Ō��)3�Œ�
//#define SAVEDATA_ELEMENTS	(4)			// �~�b�V������+�N���A�^�C��
//#define MAX_DIGIT	(3)			// �ő�3���܂�
//
//typedef struct {
//
//	// �Z�b�g�G�t�F�N�g�Ŏg����z��̔ԍ���ۊǂ���
//	int mission_background_EffectArray;					// �w�i��1�Ȃ̂�1
//	int mission_ContentsNum_EffectArray[MAX_RESULT];
//	int mission_JudgeNum_EffectArray[MAX_RESULT][MAX_DIGIT];
//
//}RESULT;

//void DrawMissionPause();
//void DeleteMissionPause();