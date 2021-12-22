/*==============================================================================

   頂点管理[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SetPause(D3DXVECTOR2 pos);
void GameoverTrue_Pause();
void GoalTrue_Pause();
//PAUSE* GetPause(void);

//#define MAX_RESULT (3)			// ミッション数の最大(最後尾)3つ固定
//#define SAVEDATA_ELEMENTS	(4)			// ミッション数+クリアタイム
//#define MAX_DIGIT	(3)			// 最大3桁まで
//
//typedef struct {
//
//	// セットエフェクトで使われる配列の番号を保管する
//	int mission_background_EffectArray;					// 背景は1個なので1
//	int mission_ContentsNum_EffectArray[MAX_RESULT];
//	int mission_JudgeNum_EffectArray[MAX_RESULT][MAX_DIGIT];
//
//}RESULT;

//void DrawMissionPause();
//void DeleteMissionPause();