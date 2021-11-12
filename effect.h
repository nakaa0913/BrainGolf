//effect.h
#include "main.h"
#include "renderer.h"

#define MAX_EFFECT (100)

typedef struct 
{
	int				id;						//エフェクト番号

	D3DXVECTOR2		pos;					// 現在の位置
	D3DXVECTOR2		pos1;					// 初期位置
	D3DXVECTOR2		pos2;					// 終了位置
	int				pos_moving_pattern;		// 初期位置から終了位置に移動するときの動き方 0:pos1から動かない

	D3DXVECTOR2		size;					// 現在のサイズ
	D3DXVECTOR2		size1;					// サイズの初期値
	D3DXVECTOR2		size2;					// サイズの終了値
	int				size_moving_pattern;	// 初期サイズから終了サイズに変化するときの変化の仕方 0:size1から動かない

	D3DXVECTOR2				drawpos;				// 表示する際の座標
	D3DXVECTOR2				drawsize;				// 表示する際のサイズ

	int				fadeIn_count;			// 0カウントからフェードインが始まり、フェードインが完了するまでのカウント
	int				all_count;				// 999 に設定することで無限にエフェクトを表示する。fadeIn_count から透明度がMAXの状態になり、それを fadeOut_count+fadeIn_count まで維持する
	int				fadeOut_count;			// fadeOut_count+fadeIn_count からフェードアウトが始まり、フェードアウトが完了するまでのカウント
	int				now_count;				// 生成されてからのカウント

	int				moving_count;			// 1 から 2 に変化するまでのカウント。基本フェードアウトが終わるまでの3つの値を足した値でOK。
											// 逆にそれら3つを足した値より小さいと移動などの途中でエフェクトが消えてしまうので注意。
	float			Clarity;				// 現在の透明度
	float			Clarity_min;			// 透明度の最低値
	float			Clarity_max;			// 透明度の最大値

	float			rot;					// 現在の回転のラジアン
	float			rot_angle;				// 現在の回転の角度
	float			rot_angle1;				// 回転の角度の初期値
	float			rot_angle2;				// 回転の角度の終了値
	int				rot_moving_pattern;		// 回転のパターン。
	int				rot_count;				// 回転し始めてからのカウント。無限回転用。

	int				use_array_num;			// 配列の何番を使っているか

	bool			isUse;					// 使用フラグ
}EFFECT;

void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

EFFECT* GetEffect(void);

int SetEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern);

int SetGameEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern);

void ChangeEffect(int use_array_num, int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern);

float AngleToRadian(float angle);	// 角度をラジアンへ

void Fadeprocess(int i);
void PosMovingPattern(int i);
void SizeMovingPattern(int i);
void RotMovingPattern(int i);

int GetTextureData(int id);
void ChangeEffectCount(int use_array_num, int setcount);
void EffectBreak(int use_array_num);