#pragma once

// まずカーソルがどこのマスをさしているかを調べる
// 左クリックした床のブロックを強調表示+説明を出す
// 説明をクリックで消す


#define MAX_GIMMICKDESCRIPTION	(4)

#define GIMMICKDESCRIPTION_FADEIN		(18)		// 説明のフェードインとサイズ大きくなるのにかかる時間
#define GIMMICKDESCRIPTION_DRAWTIME		(160)		// 説明の表示時間
#define GIMMICKDESCRIPTION_FADEOUT		(18)		// 説明のフェードアウトにかかる時間

typedef struct {

	int x;
	int y;

	// セットエフェクトで使われる配列の番号を保管する
	int background_EffectArray;					// 背景
	int text_EffectArray;						// 文章とアイコン(1枚の画像として読み込む)
	int pickupBlock_EffectArray;				// 選択しているブロックのふちを光らせてるやつ

	int GeneratedTime;							// 生成されてからの経過時間

	bool isUse;									// 現在使われているかどうか

}GIMMICKDESCRIPTION;



void InitGimmickDescription();
void UninitGimmickDescription();
void UpdateGimmickDescription_Game();

GIMMICKDESCRIPTION* GetGimmickDescription(void);

float CheckGimmickDescriptionChipPos(int block_data, int XorY);
void GenerateGimmickDescription(int block_data, int x, int y);
void DeleteGimmickDescription();

void GimmickDescriptionPickupUpdata(int i);